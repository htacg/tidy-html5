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
require 'i18n'           # Cross-platform access to `locale`.
require 'digest'         # For computing checksums.
require 'git'            # For working with old versions of files.


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
  @@default_en = File.expand_path(File.join('..', 'src', 'language_en.h' ))
  @@header_template = File.expand_path(File.join('.', 'language_ll_cc.h.erb'))
  @@header_digest = '9e5c3bf0b02c20e6fe2068a8edc09de1bb091a14144b211f4c36b0f9d1ec5f97'


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
  # class PoPoFile
  #  This class contains information about a parsed PO file.
  #############################################################################
  class PoPoFile

    include PoConvertModule

    attr_accessor :language
    attr_accessor :plural_forms
    attr_accessor :plural_formula
    attr_accessor :po_revision_date
    attr_accessor :last_translator
    attr_accessor :items


    #########################################################
    # initialize
    #########################################################
    def initialize( file = nil )
      @source_file = nil       # File path of the header file
      @language = nil          # From the header
      @plural_forms = nil      # From the header
      @plural_formula = nil    # From the header
      @po_revision_date = nil  # String, from the header
      @last_translator = nil   # From the header
      @items = {}

      self.source_file = file if file
    end


    #########################################################
    # property source_file
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
      unless value && %w[.po].include?(File.extname(value))
        @@log.error "#{__method__}: Source file must be a *.po file."
        return
      end
      unless value && File.exists?(value)
        @@log.error "#{__method__}: Source file #{value} not found."
        return
      end
      @@log.info "#{__method__}: Source file #{value} will be used."

      if parse_po( value )
        @source_file = value
      else
        @@log.error "#{__method__}: Source file #{value} was not able to be parsed properly."
      end
    end


    #########################################################
    # parse_po( file )
    #  Parses a given PO file, returning true/false on
    #  success/failure.
    #########################################################
    def parse_po(file)
      content = File.open(file) { |f| f.read }

      # Get the stuff we want to keep from the PO header.
      tmp = content.match(/"Language: (.*?)\\n"/i)
      self.language = tmp[1].downcase if tmp

      tmp = content.match(/"(Plural-Forms: .*?;)\s*?plural=\s*?(.*?)\\n"/i)
      self.plural_forms = tmp[1] if tmp
      self.plural_formula = tmp[2] if tmp

      tmp = content.match(/"PO-Revision-Date: (.*?)\\n"/i)
      self.po_revision_date = tmp[1] if tmp

      tmp = content.match(/"Last-Translator: (.*?)\\n"/i)
      self.last_translator = tmp[1] if tmp

      # Build a catalogue of all items. Note that whitespace around blocks
      # is required in the PO files.
      content.scan(%r!((?:^#|^msgctxt).*?)(?:\z|^\n)!im) do | section |
        item = parse_po_section(section[0])
        if item
          self.items.merge!(item) unless item[item.keys[0]].empty? unless item.empty?
        else
          return false
        end
      end

      language && plural_forms && plural_formula && po_revision_date && last_translator && items

    end # parse_po


    #########################################################
    # parse_po_section( content )
    #  Parses a single PO section.
    #########################################################
    def parse_po_section( content )

      # Maybe this is a bit of overkill, but it's easy to extend
      # if we want to capture more PO stuff in the future.
      map = [
          [ :START,    :COMMENT,   :SET_COMMENT,  :START    ],
          [ :START,    :FLAG,      :SET_FLAG,     :START    ],
          [ :START,    :NEW_ITEM,  :SET_INIT,     :CONTINUE ],
          [ :START,    :OTHER,     :NOOP,         :START    ],
          [ :START,    :EMPTY,     :NOOP,         :START    ],
          [ :CONTINUE, :COMMENT,   :ERROR,        nil       ],
          [ :CONTINUE, :FLAG,      :ERROR,        nil       ],
          [ :CONTINUE, :NEW_ITEM,  :SET_FINAL,    :CONTINUE ],
          [ :CONTINUE, :EMPTY,     :SET_FINAL,    :START    ],
          [ :CONTINUE, :OTHER,     :ADD_TO,       :CONTINUE ],
      ].collect { |item| [:STATE, :CONDITION, :ACTION, :NEXT].zip(item).to_h }

      current_label = nil
      current_comment = nil
      current_flag = nil
      current_cases = {}     # 'case' => string
      state = :START
      buffer = ''
      item = ''

      content << "\n\n" # ensure that we have a final transition.
      content.each_line do |line|

        # Determine the input condition
        input = :OTHER
        input = :EMPTY if line == "\n"
        input = :COMMENT if line.start_with?('#.')
        input = :FLAG if line.start_with?('#,')
        input = :NEW_ITEM if line.start_with?('msgctxt', 'msgid', 'msgstr')

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
                if item == 'msgctxt'
                  current_label = buffer.tr('"', '')
                elsif item == 'msgstr'
                  current_cases['0'] = buffer
                elsif item.start_with?('msgstr')
                  subscript = item.match(/msgstr\[(.*)\]/)[1]
                  current_cases[subscript] = buffer
                end
                buffer = ''
                regex = line[/".*"/]
                buffer = regex unless regex == '""'
                item = line[/^(.*?)\s/, 1]
              when :SET_COMMENT
                current_comment = line.match(/#\.\s*(.*?)$/)[1]
              when :SET_FLAG
                current_flag = line.match(/#\,\s*(.*?)$/)[1]
              when :ERROR
                @@log.error "#{__method__}: Could NOT parse part of the PO file. Aborting!\n"
                @@log.error "#{__method__}: Last known label was \"#{current_label}\".\n"
                return nil
              else
                # consume, other
            end
            state = transition[:NEXT]
            break
          end # if
        end # do

      end # content.each

      # We have some nice local vars but let's put these into a hash
      # just like PoHeader file uses:
      # :keyword => { '#' => { :comment, :fuzzy, :case, :string } }
      # We will also reject items that have no string value.
      result = {}
      if current_label
        current_label = current_label.to_sym
        result[current_label] = {}
        current_cases.each do | key, value |
          unless value == ''
            fuzzy = ( current_flag =~ /fuzzy/i ) != nil
            result[current_label][key] = {}
            result[current_label][key][:comment] = fuzzy ? "(fuzzy) #{current_comment}" : current_comment
            result[current_label][key][:fuzzy] = fuzzy
            result[current_label][key][:if_group] = nil
            result[current_label][key][:case] = key
            result[current_label][key][:string] = value
          end
        end
      end
      result
    end # parse_po_section


  end # class PoPoFile


  #############################################################################
  # class PoHeaderFile
  #  This class contains information about a parsed header file.
  #############################################################################
  class PoHeaderFile

    include PoConvertModule

    attr_accessor :lang_name
    attr_accessor :items         #:keyword => { '#' => { :comment, :if_group, :case, :string } }
    attr_accessor :plural_count
    attr_accessor :plural_form


    #########################################################
    # initialize
    #########################################################
    def initialize( file = nil )
      @source_file = nil # File path of the header file
      @lang_name = nil   # Name of the languageDictionary instance in C.
      @items = nil
      @plural_count = 0
      @plural_form = nil

      self.source_file = file if file
    end


    #########################################################
    # property source_file
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
      unless value && %w[.h].include?(File.extname(value))
        @@log.error "#{__method__}: Source file must be a *.h file."
        return
      end
      unless value && File.exists?(value)
        @@log.error "#{__method__}: Source file #{value} not found."
        return
      end
      @@log.info "#{__method__}: Source file #{value} will be used."
      if parse_header( value )
        @source_file = value
      else
        @@log.error "#{__method__}: Source file #{value} was not able to be parsed properly."
      end

    end


    #########################################################
    # parse_header( file )
    #  Parses a given header file and returns the language
    #  plural count, form, name, and a hash of strings:
    #
    #  We don't want to set instance variables directly.
    #########################################################
    def parse_header(file)
      self.plural_count = 0
      self.plural_form = nil
      self.lang_name = nil
      self.items = {}

      content = File.open(file) { |f| f.read }

      # Get the plural form data from the correct location in the header.
      # These will be written to the header area of the PO/POT file.
      match = content.match(%r!^static uint whichPluralForm.*?\{.*?/\* Plural-Forms: nplurals=(.*?);.*?\*/.*return (.*?;).*?\}!m)
      if match
        self.plural_count = match[1]
        self.plural_form = match[2]
      else
        @@log.error "#{__method__}: Could not determine the plural form. Something wrong with source file?"
        return false
      end

      # The language name is used for file names and setting PO information.
      match = content.match(/^static languageDefinition (.*) =.*$/)
      if match
        self.lang_name = match[1]
      else
        @@log.error "#{__method__}: Could not determine the language name. Something wrong with source file?"
        return false
      end

      # Build a catalogue of all items.
      content.scan(%r!^\s*\{(?:/\* (.*?) \*/)?\s*(.*?),\s*(.*?),\s*(.*?)\s*\},?!m) do | comment, key, num_case, string |
        l_key = key.to_sym
        self.items[l_key] = {} unless items.has_key?(l_key)
        self.items[l_key][num_case] = {}
        self.items[l_key][num_case][:comment] = comment ? comment.sub( /\(fuzzy\) /i, '') : nil
        self.items[l_key][num_case][:fuzzy] = ( comment =~ /\(fuzzy\) /i ) != nil
        self.items[l_key][num_case][:case] = num_case
        self.items[l_key][num_case][:if_group] = nil
        # Reconstitute Hex Escapes
        tmp = string.each_line.collect do |line|
          line.lstrip.gsub(/\\x(..)/) { |g| [$1.hex].pack('c*').force_encoding('UTF-8') }
        end
        # Eliminate C double-double-quotes.
        tmp = tmp.join.gsub(/(?<!\\)""/) { |g| }
        self.items[l_key][num_case][:string] = tmp
      end
      if !self.items || self.items.empty?
        @@log.error "#{__method__}: Could not match language contents. Something wrong with source file?"
        self.items = {}
        return false
      end

      # Post-process things that are in #if blocks. This second pass is still
      # simpler than building a state machine to process the file line by line.
      # We'll have to group this hash by :if_group when we write it out, and
      # store it in a special developer comment in the PO file.
      content.scan(%r!^#if (.*?)#endif!m) do | found_block |
        found_block[0].scan(%r!^\s*\{(?:/\* .*? \*/)?\s*(.*?),\s*.*?,\s*.*?\s*\},?!m) do | item |
          self.items[item[0].to_sym].each_value do  | plural |
          plural[:if_group] = found_block[0].each_line("\n").to_a[0].rstrip
          end
        end
      end

      true
    end

  end # class PoHeaderFile


  #############################################################################
  # class PoConverter
  #  The class abstracts the tidy command line executable and provides its
  #  services within Ruby.
  #############################################################################
  class PoConverter

    include PoConvertModule

    attr_accessor :emacs_footer
    attr_accessor :plaintext
    attr_accessor :force_comments

    #########################################################
    # initialize
    #########################################################
    def initialize
      @po_locale = nil        # The locale to use to generate PO files.
      @known_locales = {}     # The locales we know about.
      @emacs_footer = false   # Indicates whether or not to add emacs instructions.
      @plaintext = true       # Indicates whether or not we should stick to plaintext.
      @force_comments = false # Force comments into non-English header files?
    end


    #########################################################
    # property po_locale
    #  The locale to use when generating msginit PO files.
    #  Returns nil if the set locale is invalid.
    #########################################################
    def po_locale
      @po_locale
    end

    def po_locale=(value)
      proposed_locale = value
      # Is the locale something we recognize?
        unless known_locales.has_key?(proposed_locale.to_sym)
          if known_locales.has_key?(proposed_locale[0..2].to_sym)
            proposed_locale = proposed_locale[0..2]
          else
            proposed_locale = '' # not nil! We still use this flag!
          end
        end

      if proposed_locale
        @@log.info "#{__method__}: Will use #{proposed_locale} as locale."
      else
        @@log.error "#{__method__}: Cannot set locale #{proposed_locale}."
        @@log.error "#{__method__}: We will still generate a PO file but be sure to edit the header manually."
      end

      @po_locale = proposed_locale
    end


    #########################################################
    # property known_locales
    #  A hash of known locales.
    #########################################################
    def known_locales
      if @known_locales.empty?
        [
            [ 'ja', 'Japanese',          'nplurals=1; plural=0;' ],
            [ 'vi', 'Vietnamese',        'nplurals=1; plural=0;' ],
            [ 'ko', 'Korean',            'nplurals=1; plural=0;' ],
            [ 'en', 'English',           'nplurals=2; plural=(n != 1);' ],
            [ 'de', 'German',            'nplurals=2; plural=(n != 1);' ],
            [ 'nl', 'Dutch',             'nplurals=2; plural=(n != 1);' ],
            [ 'sv', 'Swedish',           'nplurals=2; plural=(n != 1);' ],
            [ 'da', 'Danish',            'nplurals=2; plural=(n != 1);' ],
            [ 'no', 'Norwegian',         'nplurals=2; plural=(n != 1);' ],
            [ 'nb', 'Norwegian Bokmal',  'nplurals=2; plural=(n != 1);' ],
            [ 'nn', 'Norwegian Nynorsk', 'nplurals=2; plural=(n != 1);' ],
            [ 'fo', 'Faroese',           'nplurals=2; plural=(n != 1);' ],
            [ 'es', 'Spanish',           'nplurals=2; plural=(n != 1);' ],
            [ 'pt', 'Portuguese',        'nplurals=2; plural=(n != 1);' ],
            [ 'it', 'Italian',           'nplurals=2; plural=(n != 1);' ],
            [ 'bg', 'Bulgarian',         'nplurals=2; plural=(n != 1);' ],
            [ 'el', 'Greek',             'nplurals=2; plural=(n != 1);' ],
            [ 'fi', 'Finnish',           'nplurals=2; plural=(n != 1);' ],
            [ 'et', 'Estonian',          'nplurals=2; plural=(n != 1);' ],
            [ 'he', 'Hebrew',            'nplurals=2; plural=(n != 1);' ],
            [ 'eo', 'Esperanto',         'nplurals=2; plural=(n != 1);' ],
            [ 'hu', 'Hungarian',         'nplurals=2; plural=(n != 1);' ],
            [ 'tr', 'Turkish',           'nplurals=2; plural=(n != 1);' ],
            [ 'pt_BR', 'Brazilian',      'nplurals=2; plural=(n > 1);' ],
            [ 'fr', 'French',            'nplurals=2; plural=(n > 1);' ],
            [ 'lv', 'Latvian',           'nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n != 0 ? 1 : 2);' ],
            [ 'ga', 'Irish',             'nplurals=3; plural=n==1 ? 0 : n==2 ? 1 : 2;' ],
            [ 'ro', 'Romanian',          'nplurals=3; plural=n==1 ? 0 : (n==0 || (n%100 > 0 && n%100 < 20)) ? 1 : 2;' ],
            [ 'lt', 'Lithuanian',        'nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && (n%100<10 || n%100>=20) ? 1 : 2);' ],
            [ 'ru', 'Russian',           'nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);' ],
            [ 'uk', 'Ukrainian',         'nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);' ],
            [ 'be', 'Belarusian',        'nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);' ],
            [ 'sr', 'Serbian',           'nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);' ],
            [ 'hr', 'Croatian',          'nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);' ],
            [ 'cs', 'Czech',             'nplurals=3; plural=(n==1) ? 0 : (n>=2 && n<=4) ? 1 : 2;' ],
            [ 'sk', 'Slovak',            'nplurals=3; plural=(n==1) ? 0 : (n>=2 && n<=4) ? 1 : 2;' ],
            [ 'pl', 'Polish',            'nplurals=3; plural=(n==1 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);' ],
            [ 'sl', 'Slovenian',         'nplurals=4; plural=(n%100==1 ? 0 : n%100==2 ? 1 : n%100==3 || n%100==4 ? 2 : 3);' ]
        ].each do | array_item |
          key = array_item[0].to_sym
          lang = array_item[1]
          plural_form = array_item[2]
          @known_locales[key] = {}
          @known_locales[key][:lang] = lang
          @known_locales[key][:plural_form] = plural_form
        end
      end
      @known_locales
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
    # property header_template?
    #  Indicates whether or not the header template file
    #  can be found and hasn't been tampered with.
    #########################################################
    def header_template?
      result = File.exists?(@@header_template)
      if result
        @@log.info "#{__method__}: The header template was found at #{@@header_template}"
      else
        @@log.error "#{__method__}: Cannot find the header template file. Check the value of @@header_template in this script."
        return false
      end

      digest = Digest::SHA256.file(@@header_template.to_s)
      result = digest == @@header_digest
      unless result
        @@log.error "#{__method__}: Did someone tamper with the header template? If you"
        @@log.error "#{__method__}: meant to change the template and know what you're doing,"
        @@log.error "#{__method__}: then the new digest is:"
        @@log.error "#{__method__}: #{digest}"
      end
      result
    end


    #########################################################
    # property safe_backup_name( file )
    #  Determines a safe name for a backup file name.
    #########################################################
    def safe_backup_name( filename )
      file = filename
      orig_file = filename
      index = 1
      while File.exists?(file)
        index = index + 1
        file = "#{File.basename(orig_file, '.*')}-#{index}#{File.extname(orig_file)}"
      end
      file
    end


    #########################################################
    # convert_to_po( source_file_h, base_file, fuzzy_list )
    #  Perform the conversion for xgettext, msginit, and
    #  msgunfmt.
    #########################################################
    def convert_to_po( source_file_h = nil, base_file = nil, fuzzy_list = nil )
      return false unless english_header?

      # What we actually do depends on what was setup for us.
      # If source_file_h is nil and po_locale is nil, we are xgettext.
      # If source_file_h is nil and we have po_locale, we are msginit.
      # If we have a source_file_h, then we are msgunfmt.
      action = :msgunfmt
      action = :msginit if source_file_h.nil? && po_locale
      action = :xgettext if source_file_h.nil? && po_locale.nil?

      # lang_en serves as the master reference for all output, especially
      # comments and metadata.
      lang_en = PoHeaderFile.new(@@default_en)
      return false unless lang_en.source_file

      # untranslated_items serves as the source for *untranslated* strings.
      # This differs from lang_en in that we may overwrite some of the
      # lang_en strings from the base_file, later. This can help when
      # translating, e.g., regional formats.
      untranslated_items = lang_en.items.clone
      if base_file
        lang_base = PoHeaderFile.new(base_file)
        return false unless lang_base.source_file
        untranslated_items.merge!(lang_base.items)
      end

      # We will use lang_source if we have a source_file_h, i.e., msgunfmt,
      # as the source for *translated* strings.
      if source_file_h
        lang_source = PoHeaderFile.new(source_file_h)
        return false unless lang_source.source_file
      else
        lang_source = nil
      end


      # If we were given a fuzzy_list and we have a source_file, then
      # we have to mark appropriate items as fuzzy.
      if fuzzy_list && fuzzy_list.count > 0 && lang_source
        untranslated_items.each do |key, value|
          if fuzzy_list.include?(key)
            value.each_value do |v|
              v[:fuzzy] = true
            end
          end

        end
      end

      # The information in the PO header can come from a few different sources
      # depending on what we're doing.
      header_plural_forms = nil
      header_pot_line = nil
      header_translate_to = nil

      if action == :xgettext
        header_plural_forms = "Plural-Forms: nplurals=#{lang_en.plural_count}; plural=#{lang_en.plural_form}"
        header_pot_line = "POT-Creation-Date: #{DateTime.now.strftime('%Y-%m-%d %H:%M:%S')}"
        header_translate_to = lang_en.items[:TIDY_LANGUAGE]['0'][:string].tr('"', '')

      end
      if action == :msginit
        header_plural_forms = "Plural-Forms: #{known_locales[po_locale.to_sym][:plural_form]}"
        header_pot_line = "PO-Revision-Date: #{DateTime.now.strftime('%Y-%m-%d %H:%M:%S')}"
        header_translate_to = po_locale
      end
      if action == :msgunfmt
        header_plural_forms = "Plural-Forms: nplurals=#{lang_source.plural_count}; plural=#{lang_source.plural_form}"
        header_pot_line = "PO-Revision-Date: #{DateTime.now.strftime('%Y-%m-%d %H:%M:%S')}"
        header_translate_to = lang_source.items[:TIDY_LANGUAGE]['0'][:string].tr('"', '')
      end

      header_plural_count = header_plural_forms.match(/nplurals=(.*?);/i)[1].to_i - 1

      # We'll use this closure to perform a repetitive task in the report.
      item_output = lambda do | label, string |
        result = ''
        if string.lines.count > 1
          result << "#{label} \"\"\n"
          result << "#{string}\n"
        else
          result << "#{label} #{string}\n"
        end
        result
      end


      report = <<-HEREDOC
msgid ""
msgstr ""
"Content-Type: text/plain; charset=UTF-8\\n"
"Language: #{header_translate_to}\\n"
"#{header_plural_forms}\\n"
"X-Generator: HTML Tidy #{File.basename($0)}\\n"
"Project-Id-Version: \\n"
"#{header_pot_line}\\n"
"Last-Translator: #{ENV['USER']}#{ENV['USERNAME']}\\n"
"Language-Team: \\n"

      HEREDOC

      untranslated_items.delete(:TIDY_LANGUAGE)
      untranslated_items.delete(:TIDY_MESSAGE_TYPE_LAST)
      untranslated_items.each do |key, value|

        if value['0'][:comment]
          value['0'][:comment].each_line { |line| report << "#. #{line.strip}\n"}
        end

        attribs = []
        attribs << 'fuzzy' if value['0'][:fuzzy] && action == :msgunfmt
        attribs << 'c-format' if %w(%u %s %d).any? { | find | value['0'][:string].include?(find) }
        if attribs.count > 0
          report << "#, #{attribs.join(', ')}\n"
        end

        report << "msgctxt \"#{key.to_s}\"\n"

        # Handle the untranslated strings, with the possibility that there
        # are two forms. PO/POT is English-based and supports only a singular
        # and plural form.
        value.each_value do | subitem |
          label = subitem[:case] == '0' ? 'msgid' : 'msgid_plural'
          report << item_output.(label, subitem[:string])
        end

        # Handle translated strings, with the possibility that there
        # are multiple plural forms for them.
        en_is_singular = value.count == 1

        if lang_source && lang_source.items[key]
          # Print translated strings.
          if en_is_singular
            report << item_output.( 'msgstr', lang_source.items[key]['0'][:string])
          else
            # Print available plural forms and write blanks for the rest.
            (0..header_plural_count).each do |i|
              if lang_source.items[key].has_key?(i.to_s)
                report << item_output.( "msgstr[#{i}]", lang_source.items[key][i.to_s][:string])
              else
                report << "msgstr[#{i}] \"\"\n"
              end
            end
          end
        else
          # Print empty translated strings.
          if en_is_singular
          report << "msgstr \"\"\n"
          else
            (0..header_plural_count).each do |i|
              report << "msgstr[#{i}] \"\"\n"
            end
          end
        end

        report << "\n"
      end # do

      if emacs_footer
        report << <<-HEREDOC
# Local Variables:
# mode: po
# eval: (add-hook 'po-subedit-mode-hook '(lambda () (setq fill-column 78)))
# End:
        HEREDOC
      end

      output_file = action == :xgettext ? 'tidy.pot' : "language_#{header_translate_to}.po"
      if File.exists?(output_file)
        File.rename(output_file, safe_backup_name(output_file))
      end
      File.open(output_file, 'w') { |f| f.write(report) }
      @@log.info "#{__method__}: Results written to #{output_file}"
      puts "Wrote a new file to #{File.expand_path(output_file)}"
      true
    end # convert_to_po


    #########################################################
    # convert_to_h( file, base-file )
    #  Perform the conversion.
    #########################################################
    def convert_to_h( file, base_file )

      po_content = PoPoFile.new(file)
      return false unless po_content.source_file && english_header? && header_template?

      # We will use English to ensure that no English strings are
      # included in the translation.
      lang_en = PoHeaderFile.new(@@default_en)
      return false unless lang_en.source_file
      filter_items = lang_en.items.clone

      # We will also filter out items that are already the same
      # in the base language, in order to keep Tidy small. It's
      # actually possible to miss some English strings if, for
      # some reason, the PO has English strings that the base
      # language does not, but severity * likelihood == unimportant.
      if base_file
        lang_base = PoHeaderFile.new(base_file)
        return false unless lang_base.source_file
        filter_items.merge!(lang_base.items)
      end

      # We will hard code these into the generated file.
      filter_items.delete(:TIDY_LANGUAGE)
      filter_items.delete(:TIDY_MESSAGE_TYPE_LAST)

      # Eliminate PO items if they match inherited items (in the filter), or
      # if they're not included in English (i.e., entries not used by Tidy).
      # We are comparing _complete entries_ right here, with the PO as the
      # official source. Therefore all plurals are accounted for, #IF groups,
      # and comments.
      po_content.items.reject! do |key, value|
        ( (filter_items.has_key?(key) && filter_items[key] == value) ) || !filter_items.has_key?(key)
      end

      # #if groups and comments:
      # We need to know which translated items belong in #if groups. Since we
      #  don't store this metadata in the PO, find out which #if groups they
      #  belong to from the original language_en.h.
      # Additionally we will only use comments from language_en.h. Besides
      #  preventing us from having to format them, we ensure that only the
      #  canonical comments are put into the H file in the event of changes.
      # Additionally only include comments if enabled.
      # Finally add fuzzy notes to comments if the PO item is fuzzy.
      po_content.items.each do |key, value|
        value.each_value do |item_entry|
          item_entry[:if_group] = lang_en.items[key]['0'][:if_group]
          item_entry[:comment] = force_comments ? lang_en.items[key]['0'][:comment] : nil
          item_entry[:comment] = "(fuzzy) #{item_entry[:comment]}" if item_entry[:fuzzy]
        end
      end


      # Gather some information to format this nicely, and perform
      # UTF escaping if necessary.
      longest_key = 22   # length of TIDY_MESSAGE_TYPE_LAST.
      longest_value = 10 # reasonable default in case no single-line strings are found.
      po_content.items.each do |key, value|
        longest_key = key.length if key.length > longest_key
        value.each_value do |value_inner|
          # If we're not plaintext then escape UTF sequences.
          unless plaintext
            value_inner[:string].gsub!(/[^\u0000-\u007e][0-9a-fA-F]?/) do |c|
              esc = c[0].bytes.map{ |b| '\\x' + b.to_s(16) }.join('')
              if c[1]
                esc += '""' + c[1]
              end
              esc
            end
          end
          length = value_inner[:string].length
          longest_value = length if length > longest_value && !value_inner[:string].start_with?("\n")
        end
      end

      # Manually build the first line with the proper language code.
      report_body = "    {/* Specify the ll or ll_cc language code here. */\n"
      report_body << "      #{'TIDY_LANGUAGE,'.ljust(longest_key+2)}0, \"#{po_content.language}\"\n"
      report_body << "    },\n"

      # Generate the main header body. Although it's a machine-generated
      # document we still care that it's pretty-printed and readable. In
      # this respect we have four output formats: single line values;
      # single line values with developer comment; multiline values; and
      # multiline values with developer comment.
      if_group = nil
      po_content.items.each do |item_key, item_value|
        item_group = item_value[item_value.keys[0]][:if_group]
        unless item_group == if_group
          # The current if grouping has changed.
          unless if_group.nil?
            # Close current group.
            report_body << "#endif /* #{if_group} */\n\n"
          end
          if_group = item_group
          unless if_group.nil?
            # Open new group.
            report_body << "\n#if #{if_group}\n"
          end
        end

        # Handle each entry individually.
        item_value.each_value do |entry_value|
          if entry_value[:string].start_with?("\n")
            # Format a multiline value.
            if entry_value[:comment]
              report_body << "    {/* #{entry_value[:comment]} */\n"
              report_body << "      #{(item_key.to_s + ',').ljust(longest_key+2)}#{entry_value[:case]},"
            else
              report_body << "    { #{(item_key.to_s + ',').ljust(longest_key+2)}#{entry_value[:case]},"
            end
            entry_value[:string].lines.each do |line|
              report_body << "        #{line}"
            end
            report_body << "\n    },\n"
          else
            # Format a single line value.
            if entry_value[:comment]
              report_body << "    {/* #{entry_value[:comment]} */\n"
              report_body << "      #{(item_key.to_s + ',').ljust(longest_key+2)}#{entry_value[:case]}, #{entry_value[:string]}\n"
              report_body << "    },\n"
            else
              # known issue: ljust doesn't work for certain unicode characters, so no pretty-printing, e.g., Chinese.
              report_body << "    { #{(item_key.to_s + ',').ljust(longest_key+2)}#{entry_value[:case]}, #{entry_value[:string].ljust(longest_value+2)} },\n"
            end
          end
        end
      end # po_content.items.each

      # Close off current if_group if any, because there will
      # not be another state change to do so.
      unless if_group.nil?
        report_body << "#endif /* #{if_group} */\n"
      end

      # Force the final closing line manually; can't count on PO. We
      # could add this to the template, but let's give it the same
      # pretty-printing as the other items.
      report_body_last = "    {/* This MUST be present and last. */\n"
      report_body_last << "      #{'TIDY_MESSAGE_TYPE_LAST,'.ljust(longest_key+2)}0, NULL\n"
      report_body_last << "    }\n"

      # We are going to use an external ERB template to build the report file.
      # Although it's trivial to hard-code all of the required text into this
      # method directly, it will be more convenient to keep an external file
      # synchronized with changes to language_en.h if we make changes.
      header_file = File.open(@@header_template) { |f| f.read }
      report = ERB.new(header_file).result(binding) # will use in-context vars.

      # Save
      output_file = "language_#{po_content.language}.h"
      if File.exists?(output_file)
        File.rename(output_file, safe_backup_name(output_file))
      end
      File.open(output_file, 'w') do |f|
        f.write "\uFEFF" if plaintext # MSVC requires a BOM.
        f.write(report)
      end
      @@log.info "#{__method__}: Results written to #{output_file}"
      puts "Wrote a new header file to #{File.expand_path(output_file)}"
      true
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

This script (#{File.basename($0)}) converts back and forth between GNU gettext
PO files preferred by localizers and Tidy's language header H files which
ensure that Tidy stays small and cross-platform.

All output files are placed into the current working directory using a file name
appropriate to the operation being performed.

Complete Help:
--------------
        HEREDOC
      end

      super
    end # help


    #########################################################
    # xgettext
    #  See long_desc
    #########################################################
    desc 'xgettext [input_file.h]', 'Creates a POT file for use with HTML Tidy.'
    option :emacs,
           :type => :boolean,
           :desc => 'Appends emacs editor information to the end of the PO file.',
           :aliases => '-e'
    long_desc <<-LONG_DESC
      Creates an empty POT from Tidy's native English header, or optionally from
      a specified language using English as a backup source. POT files have no
      translated strings; they are empty templates.

      Use case: in the Tidy localization process there's probably no real reason
      to use this unless you prefer to set the header manually compared to how
      #{File.basename($0)} msginit does it.
    LONG_DESC
    def xgettext(input_file = nil)
      converter = PoConverter.new
      converter.emacs_footer = options[:emacs]
      set_options
      if converter.convert_to_po( nil, input_file)
        puts 'xgettext exited without errors.'
      else
        puts 'xgettext exited with errors. Consider using the --verbose or --debug options.'
        exit 1
      end

    end # xgettext


    #########################################################
    # msginit
    #  See long_desc
    #########################################################
    option :locale,
           :type => :string,
           :desc => 'Specifies the locale in ll or ll_CC format for the generated PO file.',
           :aliases => '-l'
    option :emacs,
           :type => :boolean,
           :desc => 'Appends emacs editor information to the end of the PO file.',
           :aliases => '-e'
    desc 'msginit [input_file.h]', 'Creates a blank PO file for the current or specified locale.'
    long_desc <<-LONG_DESC
      Creates an empty PO file and tries to set locale-specific header
      information. The untranslated strings are Tidy's native English strings
      unless [input_file.h] is specified (English will still be used as a
      backup). This tool will try to use the current locale to generate the PO
      file unless the --locale option specifies a different locale.

      Use case: use this to generate a PO file for a language that Tidy has not
      yet been translated to.
    LONG_DESC
    def msginit(input_file = nil)
      converter = PoConverter.new
      converter.emacs_footer = options[:emacs]
      set_options
      unless (converter.po_locale = options[:locale] ? options[:locale] : I18n.locale)
        puts 'msginit exited with errors. Consider using the --verbose or --debug options.'
        exit 1
      end

      if converter.convert_to_po(nil, input_file)
        puts 'msginit exited without errors.'
      else
        puts 'msginit exited with errors. Consider using the --verbose or --debug options.'
        exit 1
      end
    end # msginit


    #########################################################
    # msgunfmt
    #  See long_desc
    #########################################################
    option :baselang,
           :type => :string,
           :desc => 'Specifies a base language <file.h> from which to include untranslated strings.',
           :aliases => '-b'
    option :emacs,
           :type => :boolean,
           :desc => 'Appends emacs editor information to the end of the PO file.',
           :aliases => '-e'
    desc 'msgunfmt <input_file.h>', 'Converts an existing Tidy header H file to PO format.'
    long_desc <<-LONG_DESC
      Converts an existing Tidy header H file to a PO file using the locale
      specified in the H file. Specifying <input_file.h> is required, and
      multiple input files may be specified.

      The resulting file will consist of English original strings, the
      translated strings from the header, and blank translated strings if not
      specified in the header.

      You can use the --baselang option to gather the untranslated strings from
      a different header file. This may be useful for translators that want to
      implement a region-specific localization, for example, translating `es`
      to `es_mx`.

      Use case: create a PO file from an existing Tidy header H file using a
      combination of languages that are suitable to you.
    LONG_DESC
    def msgunfmt(*args)
      error_count = 0

      args.each do |input_file|
        converter = PoConverter.new
        converter.emacs_footer = options[:emacs]
        set_options
        error_count = converter.convert_to_po(input_file, options[:baselang]) ? error_count : error_count + 1
      end

      if error_count == 0
        puts 'msgunfmt exited without errors.'
      else
        puts "msgunfmt exited with errors #{error_count} time(s). Consider using the --verbose or --debug options."
        exit 1
      end
    end # msgunfmt


    #########################################################
    # msgfmt
    #  See long_desc
    #########################################################
    option :baselang,
           :type => :string,
           :desc => 'Specifies a base language <file.h> from which to exclude translated strings.',
           :aliases => '-b'
    option :hex,
           :type => :boolean,
           :desc => 'Specifies that the generated file contain hex escaped characters.',
           :aliases => '-h'
    option :force_comments,
           :type =>:boolean,
           :desc => 'Forces comments into the header file. Base language_en.h always has comments.',
           :aliases => '-f'
    desc 'msgfmt <input_file.po>', 'Creates a Tidy header H file from the given PO file.'
    long_desc <<-LONG_DESC
      Creates a Tidy header H file from the specified <input_file.po> PO file,
      which is a required argument. Multiple input files may be specified.

      You can use the --baselang option to exclude already translated strings from an
      inherited base language. This will help keep Tidy's library and executable size
      to a minimum. For example if you wish to generate a header for es_mx (which uses
      es as its base language), then you should specify the "--baselang es" option.
      This will ensure that the generated header includes only strings that are unique
      to es_mx.

      Use case: Tidy can only build H files, and so this command will convert
      PO files to something useful.
    LONG_DESC
    def msgfmt(*args)
      error_count = 0

      args.each do |input_file|
        converter = PoConverter.new
        converter.plaintext = !options[:hex]
        converter.force_comments = options[:force_comments]
        set_options
        error_count = converter.convert_to_h( input_file, options[:baselang] ) ? error_count : error_count + 1
      end

      if error_count == 0
        puts 'msgfmt exited without errors.'
      else
        puts "msgfmt exited with errors #{error_count} time(s). Consider using the --verbose or --debug options."
        exit 1
      end
    end # msgfmt


    #########################################################
    # rebase
    #  See long_desc
    #########################################################
    option :sha,
           :type =>:string,
           :desc => 'Specify the hash against which to check for changed strings.',
           :aliases => '-c'
    desc 'rebase [--sha=HASH]', 'Creates fresh POT, POs, and headers after updates to language_en.h.'
    long_desc <<-LONG_DESC
      After changing strings in language_en.h, this command will generate a fresh POT
      template, as well as regenerate POs for each language in src/. Finally, it will
      regenerate the language header files for each of the new PO files. Items that
      have changed in English will be appropriately marked as fuzzy in the PO files.

      Source files will *not* be overwritten. All generated files will be placed into
      the working directory. Please review them before committing them to source.

      If you specify the SHA-1 checksum of the commit for comparison purposes, then
      this command identifies fuzzy items by comparing language_en.h with a previous
      version as identified by the SHA-1.

      Use case: If you change language_en.h, this handy command updates everything
      else nearly automatically.
    LONG_DESC
    def rebase()
      error_count = 0
      fuzzy_list = nil

      pwd = File.expand_path( File.join(Dir.getwd, '..') )

      if options[:sha]
        sha = options[:sha]
        temp_file = "~#{sha}.h"
        project = Git.open(pwd)

        # We'll get the old version of the file from the specified commit,
        # and then write it to a temporary file. Then we can parse both
        # this temporary file as well as the current version of the file
        # and detect the differences.
        File.open( temp_file, 'w') { |f| f.write( project.show(sha, File.join('src', 'language_en.h')) ) }
        header_old = PoHeaderFile.new(temp_file)
        header_new = PoHeaderFile.new(@@default_en)
        File.delete( temp_file )


        # Compare each item in the current version with the value, if any,
        # in the previous version in order to build a list of fuzzy stuff.
        fuzzy_list = []
        header_new.items.each do |key, value|
          value.each do |plural_key, plural_value|
            new_value = plural_value[:string]
            old_value = header_old.items.include?(key) ? header_old.items[key][plural_key][:string] : nil
            unless old_value == new_value
              fuzzy_list << key
            end

          end
        end
        fuzzy_list.uniq!
      end


      # We're ready to generate the POT, which requires nothing special.
      converter = PoConverter.new
      unless converter.convert_to_po( nil, nil)
        error_count += 1
        puts 'There was an issue generating the POT. Will continue anyway.'
      end


      # Build a list of header files. Keep this list instead of counting
      # on reading the working directory later.
      header_path = File.join(pwd, 'src', 'language_*.h')
      header_list = nil
      Dir.chdir(File.join(pwd, 'src')) do
        header_list = Dir.glob('language_*.h')
      end
      header_list.delete('language_en.h')


      # Building the POs is straight forward.
      header_list.each do |input_file|
        filename = File.join(pwd, 'src', input_file)
        converter = PoConverter.new
        error_count = converter.convert_to_po( filename, nil, fuzzy_list ) ? error_count : error_count + 1
      end


      # Building the Headers is straight forward, too.
      header_list.each do |input_file|
        filename = "#{File.basename(input_file, '.*')}.po"
        converter = PoConverter.new
        error_count = converter.convert_to_h( filename, nil ) ? error_count : error_count + 1
      end

      if error_count == 0
        puts 'rebase exited without errors.'
      else
        puts "rebase exited with errors #{error_count} time(s). Consider using the --verbose or --debug options."
        exit 1
      end
    end # msgfmt


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
