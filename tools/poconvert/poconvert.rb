#!/usr/bin/env ruby

###############################################################################
# poconvert.rb
#  Run this script with `help` for more information (or examine this file.)
###############################################################################

require 'bundler/setup'  # Provides environment for this script.
require 'logger'         # Log output simplified.
require 'fileutils'      # File utilities.
require 'date'           # Make sure DateTime works.
require 'fileutils'      # compare_file, etc.
require 'erb'            # Needed for templating.
require 'thor'           # thor provides robust command line parameter parsing.


################################################################################
# module PoConvertModule
#  This module encapsulates module-level variables, utilities, logging,
#  the CLI handling class, and the po<->h conversion class.
###############################################################################
module PoConvertModule

  ###########################################################
  # Setup
  #  Change these variables in case directories are changed.
  ###########################################################
  @@default_en = File.expand_path(File.join('..', '..', 'src', 'language_en.h' ))


  ###########################################################
  # Logging
  ###########################################################
  @@log = Logger.new(STDOUT)
  @@log.level = Logger::ERROR
  @@log.datetime_format = '%Y-%m-%d %H:%M:%S'


  ###########################################################
  # property log_level
  ###########################################################
  def self.log_level
    @@log.level
  end

  def self.log_level=(level)
    @@log.level = level
  end


  #############################################################################
  # class PoHeaderFile
  #  This class contains information about a header file.
  #############################################################################
  class PoHeaderFile

    include PoConvertModule

    attr_accessor :lang_name
    attr_accessor :items


    #########################################################
    # initialize
    #########################################################
    def initialize( file = nil )
      @source_file = nil # File path of the header file
      @lang_name = nil   # Name of the languageDictionary instance in C.
      @items = nil

      self.source_file = file if file
    end


    #########################################################
    # property source_file
    #########################################################
    def source_file
      @source_file
    end

    def source_file=( value )
      @lang_name, @items = parse_header( value )
      @source_file = value
    end


    #########################################################
    # parse_header( file )
    #  Parses a given header file and returns the language
    # name and a hash of strings:
    #  :keyword => string
    #########################################################
    def parse_header(file)
      content = File.open(file) { |f| f.read }

      match = content.match(/^static languageDictionary (.*) =.*$/)
      unless match
        @@log.error "#{__method__}: Could not determine the language name. Something wrong with source file?"
        return nil
      end
      lang_name = match[1]

      items = content.scan(%r!^\s*\{\s*(.*?),\s*(?:/\*.*?\*/)?\s*(.*?),?\s*\},?!m).to_h
      if !items || items.empty?
        @@log.error "#{__method__}: Could not match language contents. Something wrong with source file?"
        return nil, nil
      end

      stripped_items = {}
      items.each do |key, value|
        tmp = ''
        value.each_line { |line| tmp << line.lstrip }
        stripped_items[key.to_sym] = tmp
      end

      [lang_name, stripped_items]
    end

  end # PoHeaderFile


  #############################################################################
  # class PoConverter
  #  The class abstracts the tidy command line executable and provides its
  #  services within Ruby.
  #############################################################################
  class PoConverter

    include PoConvertModule

    #########################################################
    # initialize
    #########################################################
    def initialize
      @source_file = nil      # File path of the source file
      @base_file = nil        # File path of the base language header file.
    end


    #########################################################
    # property source_file
    #  Property will be nil if invalid.
    #########################################################
    def source_file
      @source_file
    end

    def source_file=( value )
      @source_file = nil
      unless value
        @@log.error "#{__method__}: A source file must be specified."
        return
      end
      unless value && %w[.po .h].include?(File.extname(value))
        @@log.error "#{__method__}: Source file must be a *.po or *.h file."
        return
      end
      unless value && File.exists?(value)
        @@log.error "#{__method__}: Source file #{value} not found."
        return
      end
      @@log.info "#{__method__}: Source file #{value} will be used."
      @source_file = value
    end


    #########################################################
    # property base_file
    #  Property will be nil if invalid.
    #########################################################
    def base_file
      @base_file
    end

    def base_file=(value)
      @base_file = nil
      unless value
        @@log.error "#{__method__}: A base language header file should be specified when using this option. No base language will be used."
        return
      end
      unless value && File.extname(value) == '.h'
        @@log.error "#{__method__}: Base language file must be an *.h file. No base language will be used."
        return
      end
      unless value && File.exists?(value)
        @@log.error "#{__method__}: Base language file #{value} not found. No base language will be used."
        return
      end
      if value == @@default_en
        @@log.info "#{__method__}: English base language already included, so this option value is not needed."
        return
      end
      @@log.info "#{__method__}: Base language file #{value} will be used."
      @base_file = value
    end


    #########################################################
    # property english_header?
    #  Indicates whether or not the default en header file
    #  can be found.
    #########################################################
    def english_header?
      result = File.exists?(@@default_en)
      if result
        @@log.info "#{__method__}: Default English was found at #{@@default_en}"
      else
        @@log.error "#{__method__}: Cannot find the default English localization file. Check the value of @@default_en in this script."
      end
      result
    end


    #########################################################
    # parse_po( file )
    #  Parses a PO file and returns an array of records.
    #########################################################
    def parse_po( file )

      # Maybe this is a bit of overkill, but it's easy
      # to extend if we want to capture more PO stuff
      # in the future.
      map = [
        [ :START,   :EOF,     :DONE,        nil    ],
        [ :START,   :JUNK,    :CONSUME,     :START ],
        [ :START,   :KEEP,    :SET_INIT,    :OPEN  ],
        [ :OPEN,    :KEEP,    :SET_FINAL,   :OPEN  ],
        [ :OPEN,    :JUNK,    :SET_FINAL,   :START ],
        [ :OPEN,    :OTHER,   :ADD_TO,      :OPEN  ],
      ].collect { |item| [:STATE, :CONDITION, :ACTION, :NEXT].zip(item).to_h }

      all_items = []
      current_record = {}
      state = :START
      buffer = ''
      item = ''

      content = File.open(file) { |f| f.readlines }
      content << "\n" # cheat a final transition.
      content.each do |line|

        # Determine the input condition
        input = :OTHER
        input = :JUNK if line.start_with?('#', '/*') || line == "\n"
        input = :KEEP if line.start_with?('msgctxt', 'msgid', 'msgstr')

        # Find our current state-input pair
        map.each do | transition |

          if transition[:STATE] == state && transition[:CONDITION] == input
            case transition[:ACTION]
              when :SET_INIT
                regex = line[/".*"/]
                buffer = regex unless regex == '""'
                item = line[/^(.*?)\s/, 1]
              when :ADD_TO
                buffer << "\n#{line[/".*"/]}"
              when :SET_FINAL
                current_record[item.to_sym] = buffer
                all_items << current_record.clone if item == 'msgstr'
                buffer = ''
                regex = line[/".*"/]
                buffer = regex unless regex == '""'
                item = line[/^(.*?)\s/, 1]
              else
                # consume, other
            end
            state = transition[:NEXT]
            break
          end # if
        end # do

      end # File.open
      all_items
    end


    #########################################################
    # normalize_po( records )
    #  Normalizes the records provided by ::parse_po so that
    #  they are key:value pairs. While we could do this as
    #  part of ::parse_po, this second stages keeps
    #  ::parse_po flexible and adaptable, which getting what
    #  we really need here.
    #########################################################
    def normalize_po( records )
      result = {}
      records.each do | record |
        result[record[:msgctxt][1..-2].to_sym] = record[:msgstr] if record.include?(:msgctxt)
      end
      result
    end


    #########################################################
    # convert_to_po
    #  Perform the conversion.
    #########################################################
    def convert_to_po
      return false unless source_file && english_header?

      language_base = nil
      language_english = PoHeaderFile.new(@@default_en)
      language_target = PoHeaderFile.new(source_file)
      target_items = language_english.items.clone

      if base_file
        language_base = PoHeaderFile.new(base_file)
        target_items.merge!(language_base.items)
      end

      translate_from = (language_base ? language_base.items[:TIDY_LANGUAGE] : language_english.items[:TIDY_LANGUAGE]).tr('"', '')
      translate_to = language_target.items[:TIDY_LANGUAGE].tr('"', '')
      report = <<-HEREDOC
msgid ""
msgstr ""
"Content-Type: text/plain; charset=UTF-8\\n"
"Language: #{translate_to}\\n"
"X-Generator: HTML Tidy poconvert.rb\\n"
"Project-Id-Version: \\n"
"POT-Creation-Date: \\n"
"PO-Revision-Date: #{DateTime.now.strftime('%Y-%m-%d %H:%M:%S')}\\n"
"Last-Translator: #{ENV['USER']}#{ENV['USERNAME']}\\n"
"Language-Team: \\n"

      HEREDOC

      target_items.delete(:TIDY_MESSAGE_TYPE_LAST)
      target_items.each do |key, value|
        report << "#\n"
        report << "#. Translate from #{translate_from} to #{translate_to}.\n"
        report << "#: #{source_file}:#{key.to_s}\n"
        report << "msgctxt \"#{key.to_s}\"\n"
        if value.lines.count > 1
          report << "msgid \"\"\n"
          report << "#{value}\n"
        else
          report << "msgid #{value}\n"
        end
        if language_target.items[key]
          if language_target.items[key].lines.count > 1
            report << "msgstr \"\"\n"
            report << "#{language_target.items[key]}"
          else
            report << "msgstr #{language_target.items[key]}\n"
          end
        else
          report << "msgstr \"\"\n"
        end
        report << "\n"
      end
      output_file = "language_#{translate_to}.po"
      File.open(output_file, 'w') { |f| f.write(report) }
      @@log.info "#{__method__}: Results written to #{output_file}"
      puts "Wrote a new PO file to #{File.expand_path(output_file)}"
    end # convert_to_po


    #########################################################
    # convert_to_h
    #  Perform the conversion.
    #########################################################
    def convert_to_h
      return false unless source_file && english_header?

      language_english = PoHeaderFile.new(@@default_en)
      target_items = language_english.items.clone

      if base_file
        language_base = PoHeaderFile.new(base_file)
        target_items.merge!(language_base.items)
      end
      target_items.delete(:TIDY_MESSAGE_TYPE_LAST)

      # Parse the file and make it the same format as our other structures.
      final_items = normalize_po(parse_po(source_file))

      # Eliminate items matching English, the base language (if any) and nil
      # items, since we don't need them inflating Tidy's executable size.
      final_items.reject! do |key, value|
        (target_items.has_key?(key) && target_items[key] == value) || value == ''
      end

      template = File.open('header_template.h.erb') { |f| f.read }

      header_guard = "language_#{}_h"
      header_filename = File.basename(source_file)

      renderer = ERB.new(template)
      output = renderer.result(binding)
      puts output

    end # convert_to_h


  end # class PoConverter


  #############################################################################
  # class PoConvertCLI
  #  This class provides handlers for CLI parameters.
  #############################################################################
  class PoConvertCLI < Thor

    include PoConvertModule

    class_option :verbose,
                 :type => :boolean,
                 :desc => 'Provides verbose debug output.',
                 :aliases => '-v'

    class_option :debug,
                 :type => :boolean,
                 :desc => 'Provides really, really verbose debug output.',
                 :aliases => '-d'

    #########################################################
    # initialize
    #########################################################
    def initialize(*args)
      super
    end


    #########################################################
    # help
    #  Override the default help in order to better describe
    #  what we're doing.
    #########################################################
    def help(*args)
      if args.count == 0
        puts <<-HEREDOC

This script (#{File.basename($0)}) converts back and fort between GNU gettext
.po files preferred by localizers and Tidy's language header .h files which
ensure that Tidy stays small and cross-platform.

Complete Help:
--------------
        HEREDOC
      end

      super
    end # help


    #########################################################
    # h2po
    #  Converts a Tidy language header to gettext po format.
    #########################################################
    option :baselang,
           :type => :string,
           :desc => 'Specifies a base language <file.h> from which to translate.',
           :aliases => '-b'
    desc 'h2po <file.h> [options]', 'Converts an *.h file to a *.po file.'
    long_desc <<-LONG_DESC
      Will convert a Tidy language header file into a gettext PO file, using
      Tidy's built-in English as the base language to translate from. Optionally
      specify a base language header file using --base-language.

      The PO file will be placed into the current working directory.
    LONG_DESC
    def h2po(name = nil)

      converter = PoConverter.new
      set_options
      converter.source_file = name
      converter.base_file = options[:baselang] if options[:baselang]
      converter.convert_to_po

    end # h2po


    #########################################################
    # po2h
    #  Converts a gettext po file to Tidy language header.
    #########################################################
    option :baselang,
           :type => :string,
           :desc => 'Specifies a base language <file.h> that the translation is based upon.',
           :aliases => '-b'
    desc 'po2h <file.po> [options]', 'Converts a *.po file to an *.h file.'
    long_desc <<-LONG_DESC
      Will convert a gettext PO file into a Tidy language header file, optionally
      specifying a base language header file using --base-language. Certain strings
      will be discarded before writing them to the header. If the translated
      string matches Tidy's built-in English, the base language, or is empty
      they will not be written in order to reduce Tidy's executable size.

      The header file will be placed into the current working directory.
    LONG_DESC
    def po2h(name = nil)

      converter = PoConverter.new
      set_options
      converter.source_file = name
      converter.base_file = options[:baselang] if options[:baselang]
      converter.convert_to_h

    end # po2h


    #########################################################
    # newpo
    #  Creates a new po based on a specified base-language.
    #########################################################
    desc 'newpo <lang_code> <base_language.h>', 'Creates a new PO file using <base_language.h>.'
    long_desc <<-LONG_DESC
      Will create a new gettext PO file based on <base_language.h>, for language
      code <lang_code>.

      The new PO file will be placed into the current working directory.
    LONG_DESC
    def newpo(lang_code = nil, base_file = nil)


    end # newpo


    #########################################################
    # set_options
    #  Handles command line options.
    #########################################################
    protected
    def set_options
      PoConvertModule::log_level = Logger::WARN if options[:verbose]
      PoConvertModule::log_level = Logger::DEBUG if options[:debug]
    end # set_options


  end # PoConvertCLI

end # PoConvertModule


###########################################################
# Main
###########################################################

PoConvertModule::PoConvertCLI.start(ARGV)
