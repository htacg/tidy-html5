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

      items = content.scan(/^\s*\{\s*(.*?),\s*(.*?),?\s*\},?/m).to_h
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
    # parse_po
    #  Parses a PO file.
    #########################################################
    def parse_po

      map = [
        [ :DECIDING,         :DECIDE,         nil              ],
        [ :PARSING_GARBAGE,  :CONSUME,        :DECIDING        ],
        [ :START_CONTEXT,    :START_CONTEXT,  :PARSING_CONTEXT ],
        [ :PARSING_CONTEXT,  :ADD_CONTEXT,    :PARSING_CONTEXT ],
        [ :START_ID,         :START_ID,       :PARSING_ID      ],
        [ :PARSING_ID,       :ADD_ID,         :PARSING_ID      ],
        [ :START_STR,        :START_STR,      :PARSING_STR     ],
        [ :PARSING_STR,      :ADD_STR,        :PARSING_STR     ],
      ]

      items = {}
      state = :DECIDING
      File.open(source_file).each do |line|
        context = ''
        id = ''
        str = ''

        # READ A LINE




        new_state = :SKIP if line.start_with?('#') || line.empty?
        new_state = :IN_CONTEXT if line.start_with('msgctxt')
        new_state = :IN_ID if line.start_with('msgid')
        new_state = :IN_STR if line.start_with?('msgstr')

        # Finish off the old state.
        unless state == new_state


          buffer << line
          items[buffer] =


        end

        if new_state == :IN_CONTEXT
          key = line.match(/(".*")/)[1]

        end


      end # File.open
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
      puts report
    end # convert_to_po


    #########################################################
    # convert_to_h
    #  Perform the conversion.
    #########################################################
    def convert_to_h
      return false unless source_file && english_header?

      # Read the PO and convert it to a hash.
      File.open(source_file).each do |line|


      end




      # Filter out the English and base stuff that's the same, and the nil items.

      template = File.open('header_template.h.erb') { |f| f.read }


      header_guard = "language_#{}_h"
      header_filename = File.basename(source_file)

      renderer = ERB.new(template)
      output = renderer.result(binding)
      puts output


      return

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
      puts report
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
