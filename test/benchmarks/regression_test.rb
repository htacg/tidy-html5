#!/usr/bin/env ruby

###############################################################################
# Tidy Regression Test Suite
#  Run this script with `help` for more information (or examine this file.)
#
#  Commands:
#    help
#    rtest
#    rtest my_file.html
#    canonize
#    canonize my_file.html
#
#  Options:
#    --cases=<directory>, -c
#    --results=<directory>, -r
#    --tidy=<path>, -t
#    --replace, -f
#    --verbose, -v
#    --debug, -d
###############################################################################

require 'bundler/setup'  # Provides environment for this script.
require 'logger'         # Log output simplified.
require 'open3'          # Run executables and capture output.
require 'fileutils'      # File utilities.
require 'date'           # Make sure DateTime works.
require 'fileutils'      # compare_file, etc.
require 'thor'           # thor provides robust command line parameter parsing.


###############################################################################
# module Which
#  Cross-platform "which" utility for Ruby.
#  https://gist.github.com/steakknife/88b6c3837a5e90a08296
###############################################################################
module Which
  # similar to `which {{cmd}}`, except relative paths *are* always expanded
  # returns: first match absolute path (String) to cmd (no symlinks followed),
  #          or nil if no executable found
  def which(cmd)
    which0(cmd) do |abs_exe|
      return abs_exe
    end
    nil
  end

  # similar to `which -a {{cmd}}`, except relative paths *are* always expanded
  # returns: always an array, or [] if none found
  def which_all(cmd)
    results = []
    which0(cmd) do |abs_exe|
      results << abs_exe
    end
    results
  end

  def real_executable?(f)
    File.executable?(f) && !File.directory?(f)
  end

  def executable_file_extensions
    ENV['PATHEXT'] ? ENV['PATHEXT'].split(';') : ['']
  end

  def search_paths
    ENV['PATH'].split(File::PATH_SEPARATOR)
  end

  def find_executable(path, cmd, &_block)
    executable_file_extensions.each do |ext|
      # rubocop:disable Lint/AssignmentInCondition
      if real_executable?( (abs_exe = File.expand_path(cmd + ext, path) ))
        yield(abs_exe)
      end
      # rubocop:enable Lint/AssignmentInCondition
    end
  end

  # internal use only
  # +_found_exe+ is yielded to on *all* successful match(es),
  #              with path to absolute file (String)
  def which0(cmd, &found_exe)
    # call expand_path(f, nil) == expand_path(f) for relative/abs path cmd
    find_executable(nil, cmd, &found_exe) if File.basename(cmd) != cmd

    search_paths.each do |path|
      find_executable(path, cmd, &found_exe)
    end
  end

  module_function(*public_instance_methods) # `extend self`, sorta
end # module Which


################################################################################
# module TidyRegressionTesting
#  This module encapsulates module-level variables, utilities, logging,
#  the CLI handling class, and the regression testing class.
###############################################################################
module TidyRegressionTesting

  ###########################################################
  # Setup
  #  Change these variables to specify different defaults,
  #  although there's probably no good reason to change
  #  them.
  ###########################################################
  @@default_cases = 'cases'
  @@default_results = 'results'           # prefix only!
  @@default_conf = 'config_default.conf'


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
  # class TidyTestRecord
  #  This class defines a single Tidy test record and provides an interface
  #  for managing multiple instances of itself.
  #############################################################################
  class TidyTestRecord

    attr_accessor :tidy_path            # The path of the requested Tidy executable.
    attr_accessor :tidy_version         # The tidy version, if it was valid.
    attr_accessor :tidy_valid           # Indicates that requested tidy was valid.
    attr_accessor :results_dir          # The requested results directory.
    attr_accessor :results_valid        # Indicates that the results dir was valid.
    attr_accessor :case_file            # The path of the file being requested.
    attr_accessor :case_file_valid      # Indicates that the request case was valid.
    attr_accessor :config_file          # The path of the config file requested.
    attr_accessor :config_file_valid    # Indicates the requested config file was valid.
    attr_accessor :missing_txt          # The path of the missing -expect.txt file.
    attr_accessor :missing_htm          # The path of the missing -expect.xxx markup
    attr_accessor :tested               # Indicates that this test was executed.
    attr_accessor :passed_output        # Indicates the output test matched.
    attr_accessor :passed_errout        # Indicates the error output test matched.
    attr_accessor :passed_status        # Indicates tidy's exit code, 0, 1, or 2.
    attr_accessor :info_text_file       # Indicates explanatory text for a test config.

    @@test_records = [] # Array of test records.
    @@show_notes = true

    #########################################################
    # initialize
    #########################################################
    def initialize
      @tidy_path = nil
      @tidy_version = '0.0.0.'
      @tidy_valid = true
      @results_dir = nil
      @results_valid = true
      @case_file = nil
      @case_file_valid = true
      @config_file = nil
      @config_file_valid = true
      @missing_txt = nil
      @missing_htm = nil
      @tested = false
      @passed_output = false
      @passed_errout = false
      @passed_status = false
      @info_text_file = nil
    end # initialize


    #########################################################
    # + test_records
    #     The singleton array of test records.
    #########################################################
    def self.test_records
      @@test_records
    end

    #########################################################
    # + show_notes
    #     The command line parameter backing setter/getter.
    #########################################################
    def self.show_notes
      @@show_notes
    end

    def self.show_notes=( value )
      @@show_notes = value
    end


    #########################################################
    # + make_report
    #     returns a test report.
    #########################################################
    def self.make_report
      record0 = @@test_records[0]
      return false if record0.nil?
      max_case = [9, self.width_of_cases].max + 3
      max_conf = [17, self.width_of_configs].max + 3
      max_errs = [15, self.width_of_errors].max + 3
      max_mkup = [15, self.width_of_markup].max + 3
      output = <<-HEREDOC
HTML Tidy Regression Testing Exception Log
==========================================

Test conducted using #{record0.tidy_path}, version #{record0.tidy_version}
Results generated on #{DateTime.now}.

Summary:
========

     Number of case files: #{self.count_of_cases_requested}
Total test configurations: #{self.count_of_configs_requested}

        Case files tested: #{self.count_of_cases_tested}
    Configurations tested: #{self.count_of_configs_tested}
   Configurations aborted: #{self.count_of_configs_aborted}
    Configurations passed: #{self.count_of_configs_passed} of #{self.count_of_configs_tested}
    Configurations failed: #{self.count_of_configs_failed} of #{self.count_of_configs_tested}

      HEREDOC

      readme = File.join(File.dirname(record0.case_file), 'README.txt')
      if File.exists?( readme )
        output << "\n"
        IO.readlines(readme).each do |line|
          output << "#{line}"
          output << "\n" if line[-1] != "\n"
        end
        output << "\n"
      end

      if self.count_of_configs_aborted > 0
        output << <<-HEREDOC

Missing Expectations Files:
===========================
Tests for these files were not performed because they are missing files against
which to compare, as indicated below:

        HEREDOC

        # Show cases that are missing critical inputs:
        output << 'Case File'.ljust(max_case)
        output << 'For Configuration'.ljust(max_conf)
        output << 'Requires Errors'.ljust(max_errs)
        output << 'Requires Markup'.ljust(max_mkup)
        output << "\n"
        output << '---------'.ljust(max_case)
        output << '-----------------'.ljust(max_conf)
        output << '---------------'.ljust(max_errs)
        output << '---------------'.ljust(max_mkup)
        output << "\n"

        @@test_records.select { |record| !record.missing_txt.nil? || !record.missing_htm.nil? }.each do | record |
          output << column(record.case_file, max_case)
          output << column(record.config_file, max_conf)
          output << column(record.missing_txt, max_errs)
          output << column(record.missing_htm, max_mkup)
          output << "\n"
        end
        end # if count_of_configs_aborted

      if self.count_of_configs_failed > 0
        # Show cases that have failed.
        output << "\n\nFailed Tests:\n"
        output << "=============\n\n"
        output << 'Case File'.ljust(max_case)
        output << 'For Configuration'.ljust(max_conf)
        output << 'Markup'.ljust(9)
        output << 'Errors'.ljust(9)
        output << 'Exit Status'.ljust(14)
        output << "\n"
        output << '---------'.ljust(max_case)
        output << '-----------------'.ljust(max_conf)
        output << '------'.ljust(9)
        output << '-------'.ljust(9)
        output << '-----------'.ljust(14)
        output << "\n"

        @@test_records.select { |record| record.tested && !record.passed_test? }.each do | record |
          output << column(record.case_file, max_case)
          output << column(record.config_file, max_conf)
          output << (record.passed_output ? 'PASSED' : 'FAILED').ljust(9)
          output << (record.passed_errout ? 'PASSED' : 'FAILED').ljust(9)
          output << (record.passed_status ? 'PASSED' : 'FAILED').ljust(14)
          output << "\n"

          # Add explanatory notes (if any) for failing tests.
          unless record.info_text_file.nil? || !self.show_notes
            output << "\n"
            IO.readlines(record.info_text_file).each do |line|
              output << "     #{line}"
              output << "\n" if line[-1] != "\n"
            end
            output << "\n"
          end
        end
      end # count_of_configs_failed

      # if there are notes for records that did pass a test, then display them.
      if @@test_records.select { |record| record.tested && record.passed_test? && record.info_text_file}.count > 0 && self.show_notes
        output << <<-HEREDOC


Notes about passing tests:
==========================
Some of the passing tests have notes about them that may affect how you wish
to interpret the results, such as operating-specific results, etc.

        HEREDOC

        @@test_records.select { |record| record.tested && record.passed_test? && record.info_text_file }.each do | record |
          output << "\n#{File.basename(record.case_file)}:\n\n"
          IO.readlines(record.info_text_file).each do |line|
            output << "     #{line}"
            output << "\n" if line[-1] != "\n"
          end
          output << "\n"
        end
      end

      output << "\nSee files in directory #{record0.results_dir} for failed results.\n\n"
      puts output
      out_path = File.join(record0.results_dir, 'all_results.txt')
      File.open(out_path, 'w') { |file| file.write(output)}

    end


    #########################################################
    # + make_canon_report
    #     returns a canonize process report.
    #########################################################
    def self.make_canon_report
      record0 = @@test_records[0]
      return false if record0.nil?
      max_case = [9, self.width_of_cases].max + 3
      max_conf = [17, self.width_of_configs].max + 3
      max_errs = [14, self.width_of_errors].max + 3
      max_mkup = [14, self.width_of_markup].max + 3
      output = <<-HEREDOC
HTML Tidy Canonization Log
==========================

Records generated using #{record0.tidy_path}, version #{record0.tidy_version}
Report generated on #{DateTime.now}.

Summary:
========

     Number of case files: #{self.count_of_cases_requested}
Total test configurations: #{self.count_of_configs_requested}


Generated Expectations Files:
=============================

Note that blank filenames indicate files that already existed and were not
replaced. You can use the `replace` option for overwrite existing files.

      HEREDOC

      # Show all case-config combinations and status:
      output << 'Case File'.ljust(max_case)
      output << 'For Configuration'.ljust(max_conf)
      output << 'Created Errors'.ljust(max_errs)
      output << 'Created Markup'.ljust(max_mkup)
      output << "\n"
      output << '---------'.ljust(max_case)
      output << '-----------------'.ljust(max_conf)
      output << '--------------'.ljust(max_errs)
      output << '--------------'.ljust(max_mkup)
      output << "\n"

      @@test_records.each do | record |
        output << column(record.case_file, max_case)
        output << column(record.config_file, max_conf)
        output << column(record.missing_txt, max_errs)
        output << column(record.missing_htm, max_mkup)
        output << "\n"
      end

      output << "\nFiles were written into directory #{File.dirname(record0.case_file)}.\n\n"
      puts output

    end


    #########################################################
    # + count_of_cases_requested
    #    returns the number of HTML/XML/XHTML files that
    #    were requested for testing.
    #########################################################
    def self.count_of_cases_requested
      temp = @@test_records.map { |record| record.case_file }
      temp.uniq.count
    end


    #########################################################
    # + count_of_configs_requested
    #    returns the number of total configurations
    #    requested for testing.
    #########################################################
    def self.count_of_configs_requested
      @@test_records.count
    end


    #########################################################
    # + count_of_cases_tested
    #     returns the number of HTML/XML/XHTML files that
    #     were actually run through a test.
    #########################################################
    def self.count_of_cases_tested
      temp = @@test_records.select { |record| record.tested }
      temp = temp.map { |record| record.case_file }
      temp.uniq.count
    end


    #########################################################
    # + count_of_configs_tested
    #     returns the number of actual tests performed,
    #     considering multiple configurations.
    #########################################################
    def self.count_of_configs_tested
      temp = @@test_records.select { |record| record.tested }
      temp.count
    end


    #########################################################
    # + count_of_configs_aborted
    #     returns the number of tests that were aborted due
    #     to missing requirements.
    #########################################################
    def self.count_of_configs_aborted
      temp = @@test_records.select { |record| !record.tested }
      temp.count
    end


    #########################################################
    # + count_of_configs_passed
    #     returns the number of tests that passed.
    #########################################################
    def self.count_of_configs_passed
      temp = @@test_records.select { |record| record.tested && record.passed_test? }
      temp.count
    end


    #########################################################
    # + count_of_configs_failed
    #     returns the number of tests that failed.
    #########################################################
    def self.count_of_configs_failed
      temp = @@test_records.select { |record| record.tested && !record.passed_test? }
      temp.count
    end


    #########################################################
    # + width_of_cases
    #  Indicates the length of the longest file name.
    #########################################################
    def self.width_of_cases
      temp = @@test_records.map { |record| File.basename(record.case_file)}
      temp.count > 0 ? temp.max_by(&:length).size : 0
    end


    #########################################################
    # + width_of_configs
    #  Indicates the length of the longest file name.
    #########################################################
    def self.width_of_configs
      temp = @@test_records.select { |record| !record.config_file.nil? }
      temp = temp.map { |record| File.basename(record.config_file)}
      temp.count > 0 ? temp.max_by(&:length).size : 0
    end


    #########################################################
    # + width_of_errors
    #  Indicates the length of the longest file name.
    #########################################################
    def self.width_of_errors
      temp = @@test_records.select { |record| !record.missing_txt.nil? }
      temp = temp.map { |record| File.basename(record.missing_txt)}
      temp.count > 0 ? temp.max_by(&:length).size : 0
    end


    #########################################################
    # + width_of_markup
    #  Indicates the length of the longest file name.
    #########################################################
    def self.width_of_markup
      temp = @@test_records.select { |record| !record.missing_htm.nil? }
      temp = temp.map { |record| File.basename(record.missing_htm)}
      temp.count > 0 ? temp.max_by(&:length).size : 0
    end


    #########################################################
    # + column( item, width )
    #  Implements .ljustify taking into account nil strings.
    #########################################################
    def self.column( item, width )
      if item.nil?
        ' '.ljust(width)
      else
        File.basename(item).ljust(width)
      end
    end


    #########################################################
    # passed_test?
    #  Indicates tests were run and all tests matched.
    #########################################################
    def passed_test?
      @tested && @passed_errout && @passed_output && @passed_status
    end

  end # class TidyTestRecord


  #############################################################################
  # class TidyExe
  #  The class abstracts the tidy command line executable and provides its
  #  services within Ruby.
  #############################################################################
  class TidyExe

    include TidyRegressionTesting

    #########################################################
    # initialize
    #########################################################
    def initialize
      @path = nil
      @version = nil
      @source_file = nil
      @config_file = nil
      @config_file_content = nil
    end


    #########################################################
    # property path
    #  Indicates the complete path to the tidy executable.
    #  If not set then the default is the OS default, if
    #  found. Value is nil when the path is not valid.
    #########################################################
    def path
      if @path.nil?
        self.path = Which::which('tidy')
      end
      @path
    end

    def path=(value)
      if !value.nil? && File.basename(value, '.*').start_with?('tidy') && File.executable?(value)
        @path = File.expand_path(value)
        @@log.info "#{__method__}: Will use Tidy at #{value}"
      else
        @path = nil
        @@log.error "#{__method__}: No valid Tidy at #{value}"
      end
      @version = nil
    end

    def path?
      !self.path.nil?
    end


    #########################################################
    # property version
    #  Returns the tidy version string of the executable.
    #  nil value indicates that tidy is not found.
    #########################################################
    def version
      if path.nil?
        @@log.info "#{__method__}: Tried to get Tidy version with no valid Tidy specified."
        nil
      else
        if @version.nil?
          pwd = Dir.pwd
          Dir.chdir(File.dirname(path))
          result = Open3.capture3("#{File.join('.',File.basename(path))} -v")
          Dir.chdir(pwd)
          result[0].split.last if result
        else
          @version
        end
      end
    end

    def version?
      !self.version.nil?
    end


    #########################################################
    # property source_file
    #  Indicates the path to the input file to be processed.
    #  If the file is not present or readable then value
    #  will be nil.
    #########################################################
    def source_file
      @source_file
    end

    def source_file=( file )
      if File.exists?(file) && File.readable?(file)
        @@log.info "#{__method__}: Source file is #{file}"
        @source_file = file
      else
        @@log.error "#{__method__}: Source file #{file} does not exist or could not be read."
        @source_file = nil
        false
      end
    end


    #########################################################
    # property config_file
    #  Indicates the path to the config file to be used.
    #  If the file is not present or readable then value
    #  will be nil.
    #########################################################
      def config_file
        @config_file
      end

      def config_file=(file)
        if File.exists?(file) && File.readable?(file)
          @@log.info "#{__method__}: Config file is #{file}"
          @config_file = file
          # Buffer this in memory, because we read from it twice.
          @config_file_content = File.open(self.config_file) { |f| f.read }
        else
          @@log.error "#{__method__}: Config file #{file} does not exist or could not be read."
          @config_file = nil
          @config_file_content = nil
          false
        end
      end


    #########################################################
    # execute( file, config ) | output_file, error_file, status |
    # execute | output_file, error_file, status |
    #  Sets source_file to file and config_file to config,
    #  and then executes tidy using a block for the results.
    #########################################################
    def execute( file = nil, config = nil )
      self.source_file = file unless file.nil?
      if self.source_file.nil?
        @@log.error "#{__method__}: Source file is nil or invalid."
        return false
      end

      self.config_file = config unless config.nil?
      if self.config_file.nil?
        @@log.error "#{__method__}: Config file is nil or invalid."
        return false
      end

      if self.path.nil?
        @@log.error "#{__method__}: No valid Tidy has been set or could be found."
        return false
      end

      # Check the config_file for cases of write-back: yes, in which case we
      # will create a backup for restoration after the Tidy process.
      writes_back = config_matches?('write-back', 'yes')

      Dir.mktmpdir do | tmp | # temp stuff cleaned up automatically.
        if writes_back
          @@log.info "#{__method__}: Dealing with write-back: yes by creating backup of original file."
          FileUtils.cp(self.source_file, "#{self.source_file}.bak")
        end
        err_path = "#{File.join(tmp, 'tidy_err.tmp')}"
        tdy_path = "#{File.join(tmp, 'tidy_out.tmp')}"
        command = "#{File.join('.', File.basename(self.path))} -o #{tdy_path} -f #{err_path} -config #{self.config_file} --tidy-mark no #{self.source_file}"
        pwd = Dir.pwd
        Dir.chdir(File.dirname(self.path))
        @@log.info "#{__method__}: performing #{command}"
        tidy_result = Open3.capture3(command)
        Dir.chdir(pwd)
        if writes_back
          # The original source_file is now tidy'd, so put it where the rest of the
          # test suite expects to find tidy results files, and restore the original.
          @@log.info "#{__method__}: Restoring original source file after write-back: yes."
          FileUtils.mv(self.source_file, tdy_path)
          FileUtils.mv("#{self.source_file}.bak", self.source_file)
        end
        yield tdy_path, err_path, tidy_result[2].exitstatus if block_given?
      end
      true
    end


    #########################################################
    # compare_html
    #  Tries to compare HTML files without respect to line
    #  endings.
    #########################################################
    def compare_html( file1, file2 )
      content1 = File.exists?(file1) ? File.open(file1) { |f| f.read } : nil
      content2 = File.exists?(file2) ? File.open(file2) { |f| f.read } : nil
      content1 = content1.empty? ? nil : content1.encode(content1.encoding, :universal_newline => true) unless content1.nil?
      content2 = content2.empty? ? nil : content2.encode(content2.encoding, :universal_newline => true) unless content2.nil?
      content1 == content2
    end


    #########################################################
    # compare_errs( file1, file2 )
    #  Tries to compare error output without respect to
    #  line endings, and ignoring everything after the
    #  error summary output line.
    #########################################################
    def compare_errs( file1, file2 )
      pattern = /^(No warnings or errors were found\.)|(\d warnings?, \d errors? were found!)/
      content1 = nil
      content2 = nil

      gnu_emacs = config_matches?('gnu-emacs', 'yes')
      emacs_pattern = /^.*(#{File.basename(self.source_file)}:.*)/i

      if File.exists?(file1)
        tmp = File.open(file1) { |f| f.readlines }
        content1 = tmp.take_while { |line| line !~ pattern }
        content1 << tmp[content1.count] unless tmp[content1.count].nil?
        if gnu_emacs
          content1.map! do |line|
            line.match(emacs_pattern) { |m| m[1] }
          end
        end
      end

      if File.exists?(file2)
        tmp = File.open(file2) { |f| f.readlines }
        content2 = tmp.take_while { |line| line !~ pattern }
        content2 << tmp[content2.count] unless tmp[content2.count].nil?
        if gnu_emacs
          content2.map! do |line|
            line.match(emacs_pattern) { |m| m[1] }
          end
        end
      end

      content1 == content2
    end


    #########################################################
    # status_from_err_file( file )
    #  Given a path to an error output file, will return the
    #  Tidy exit status. This avoids having to create a
    #  database of Tidy exits codes and avoids having to
    #  create extra files, although the fallback/override
    #  .err file is checked here, too.
    #########################################################
    def status_from_err_file(file)
      # The -expect.txt file may be empty for certain tests based
      # on the configuration used, so we will reluctantly support
      # the use of -expect.err to contain Tidy's expected exit status.
      err_file = File.join(File.dirname(file), "#{File.basename(file, '.*')}.err")
      if File.exists?(err_file)
        return File.open(err_file) { |f| f.read }.to_i
      end

      pattern1 = /No warnings or errors were found\./
      pattern2 = /(\d) warnings?, (\d) errors? were found!/

      content = File.exists?(file) ? File.open(file) { |f| f.read } : nil

      return 0 if content =~ pattern1

      if ( matches = content.match(pattern2) )
        if ( matches = matches.captures.to_a )
          if matches.count > 1
            return 1 if matches[1].to_i == 0 # no errors, so only warnings.
            return 2 if matches[1].to_i > 0 # errors.
          end
        end
      end
      nil
    end

    private

    #########################################################
    # property config_matches?( option, value )
    #  Returns true if the current config file contains the
    #  specified option with the value (as string).
    #  @todo: match synonyms, e.g., yes, true, etc.
    #########################################################
    def config_matches?(option, value)
      pattern = /^#{option}: *?#{value}.*?/i
      !(@config_file_content =~ pattern).nil?
    end

  end # class TidyExe



  #############################################################################
  # class TidyRegression
  #  The class that performs the core work of the testing suite.
  #############################################################################
  class TidyRegression

    include TidyRegressionTesting

    attr_accessor :tidy       # local instance of TidyExe class
    attr_accessor :replace    # value of the --replace command line option.
    attr_reader   :reporter   # Provides access to the TidyTestRecord instance.

    #########################################################
    # initialize
    #########################################################
    def initialize
      @dir_cases = nil
      @dir_results = nil
      @tidy = TidyExe.new
      @replace = false
      @reporter = TidyTestRecord.test_records
    end # initialize


    #########################################################
    # property dir_cases
    #  Indicates the directory from which to read the test
    #  cases.
    #########################################################
    def dir_cases
      if @dir_cases.nil?
        self.dir_cases = @@default_cases
      end
      @dir_cases
    end

    def dir_cases=( value )
      @dir_cases = File.expand_path(value)
    end

    def dir_cases?
      if File.exists?(dir_cases) && File.readable?(dir_cases)
        @@log.info "#{__method__}: Will uses cases directory #{dir_cases}"
        true
      else
        @@log.error "#{__method__}: Cases directory #{dir_cases} does not exist or could not be read."
        false
      end
    end

    #########################################################
    # property dir_results
    #  Indicates the directory in which to write test pass
    #  and failure information. The value will be modified
    #  with the current tidy_version upon setting.
    #########################################################
    def dir_results
      if @dir_results.nil?
        self.dir_results = @@default_results
      end
      @dir_results
    end

    def dir_results=( value )
      if self.tidy.version?
        result = "#{value}-#{self.tidy.version}"
      else
        result = "#{value}-0.0.0"
      end
      @dir_results = File.expand_path(result)
    end

    def dir_results?
      unless File.exists?(dir_results)
        begin
          Dir.mkdir(dir_results)
        rescue SystemCallError
          @@log.error "#{__method__}: Directory #{dir_results} could not be created."
          return false
        end
        @@log.info "#{__method__}: Created results directory #{dir_results}"
      end
      if File.readable?(dir_results)
        @@log.info "#{__method__}: Will place results into #{dir_results}"
        true
      else
        @@log.error "#{__method__}: Directory #{dir_results} could not be read."
        false
      end
    end


    #########################################################
    # property conf_default
    #  Returns the path and file for the default
    #  configuration file used when no config file is
    #  specified for a test.
    #  nil value indicates that tidy is not found.
    #########################################################
    def conf_default
      File.join(dir_cases, @@default_conf)
    end

    def conf_default?
      if File.exists?(conf_default) && File.readable?(conf_default)
        @@log.info "#{__method__}: Will use default configuration file #{conf_default}"
        true
      else
        @@log.warn "#{__method__}: Default configuration file #{conf_default} does not exist or could not be read."
        false
      end
    end


    #########################################################
    # case_file?( file )
    #########################################################
    def case_file?( file )
      if File.exists?(file) && File.readable?(file)
        @@log.info "#{__method__}: Will use file #{file}"
        true
      else
        @@log.error "#{__method__}: File #{file} does not exist or could not be read."
        false
      end
    end


    #########################################################
    # expects_file?( file )
    #########################################################
    def expects_file?( file )
      if File.exists?(file )
        @@log.info "#{__method__}: Expectation file #{file} was found."
        true
      else
        @@log.warn "#{__method__}: Missing expectation file #{file}."
        false
      end
    end


    #########################################################
    # process_case( file, canonize )
    #   Will either run a test against file, or generate the
    #   canonical reference files for `file`, depending on
    #   the value of `canonize`.
    #########################################################
    def process_case( file, canonize=false )
      basename = File.basename( file, '.*' )
      case_dir = File.dirname( file )
      record = TidyTestRecord.new

      ### These are all showstoppers, but let's get as much information
      ### for the test record as we can before aborting.
      record.tidy_path = tidy.path
      record.tidy_valid = tidy.path?
      record.tidy_version = tidy.version
      record.results_dir = dir_results
      record.results_valid = dir_results?
      record.case_file = file
      record.case_file_valid = case_file?(file)
      unless tidy.path? && case_file?(file) && dir_results?
        reporter << record
        return false
      end

      ### Get a list of all configuration files (if any) to use.
      configs = []
      Dir.glob(File.join(case_dir, "#{basename}.conf") ).each { |entry| configs << entry }
      Dir.glob(File.join(case_dir, "#{basename}-*.conf") ).each { |entry| configs << entry }

      # If there are no configs for the test, attempt to use the default.
      if configs.count < 1
        record.config_file = conf_default
        record.config_file_valid = conf_default?
        unless record.config_file_valid
          reporter << record
          return false
        end
        configs << conf_default
      end

      ### Run through all of the configurations.
      configs.sort.each do | config_file |
        @@log.info "Processing with config file #{config_file}"

        inner_record = record.clone
        inner_record.config_file = config_file

        # Build the expect filenames for this configuration.
        if config_file == conf_default
          base_conf = File.join(case_dir, basename)  # e.g., path/hello
        else
          base_conf = File.join(case_dir, File.basename(config_file, '.*')) # e.g., path/hello-1
        end
        expects_txt_path = "#{base_conf}-expect.txt"
        expects_htm_path = "#{base_conf}-expect#{File.extname(file)}"


        if canonize
          #################
          # CANONIZE
          # @todo look through the configuration for write-back to handle specially.
          #################

          # Let's run tidy
          self.tidy.source_file = file
          self.tidy.config_file = config_file
          self.tidy.execute do |output_htm_path, output_txt_path, tidy_exit_code|

            if File.exists?(expects_htm_path) && !replace
              @@log.warn "#{expects_htm_path} already exists and won't be replaced."
            else
              if File.exists?(output_htm_path)
                FileUtils.cp(output_htm_path, expects_htm_path, :preserve => true) if File.exists?(output_htm_path)
              else
                FileUtils.touch(expects_htm_path)
              end
              inner_record.missing_htm = expects_htm_path
            end

            if File.exists?(expects_txt_path) && !replace
              @@log.warn "#{expects_txt_path} already exists and won't be replaced."
            else
              if File.exists?(output_txt_path)
                FileUtils.cp(output_txt_path, expects_txt_path, :preserve => true)
                inner_record.missing_txt = expects_txt_path
              end
            end

            if File.exists?(expects_txt_path) && File.zero?(expects_txt_path)
              err_file = File.join(File.dirname(expects_txt_path), "#{File.basename(expects_txt_path, '.*')}.err")
              File.open(err_file, 'w') { |f| f.write tidy_exit_code.to_s }
            end



          end # tidy.execute

        else
          #################
          # TEST
          #################

          # Make sure that the expectations are available for this config...
          inner_record.missing_txt = expects_file?(expects_txt_path) ? nil : expects_txt_path
          inner_record.missing_htm = expects_file?(expects_htm_path) ? nil : expects_htm_path

          # ...and only go through the process if they are available.
          if expects_file?(expects_txt_path) && expects_file?(expects_htm_path)

            # Let's run tidy
            self.tidy.source_file = file
            self.tidy.config_file = config_file
            self.tidy.execute do | output_htm_path, output_txt_path, exit_status |

              ## Make comparisons and set report flags
              inner_record.tested = true
              inner_record.passed_output = self.tidy.compare_html(output_htm_path, expects_htm_path)
              inner_record.passed_errout = self.tidy.compare_errs(output_txt_path, expects_txt_path)
              inner_record.passed_status = exit_status == self.tidy.status_from_err_file(expects_txt_path)

              ## Build file names
              # In the case of multiple configurations, we need to get
              # the configuration number to append to the markup file.
              config_number = File.basename(config_file, '.*').match(/.*-.*-(.*)/)
              config_number = config_number.nil? ? nil : "-#{config_number[1]}"
              file_htm = "#{File.basename(file, '.*')}#{config_number}-fail#{File.extname(file)}"
              file_err = "#{File.basename(file, '.*')}#{config_number}-fail.txt"
              file_nfo = File.join(case_dir, "#{File.basename(file, '.*')}#{config_number}-expect.nfo")

              ## Log an information file if it exists.
              if File.exists?(file_nfo)
                inner_record.info_text_file = file_nfo if File.exists?(file_nfo)
              end

              ## Write results and copy the originals for convenience.
              unless inner_record.passed_test?
                if File.exists?(output_htm_path)
                  FileUtils.cp(output_htm_path, File.join(dir_results, file_htm), :preserve => true)
                else
                  FileUtils.touch(File.join(dir_results, file_htm))
                end
                if File.exists?(output_txt_path)
                  FileUtils.cp(output_txt_path, File.join(dir_results, file_err), :preserve => true)
                else
                  FileUtils.touch(File.join(dir_results, file_err))
                end
                FileUtils.cp( expects_htm_path, dir_results, :preserve => true )
                FileUtils.cp( expects_txt_path, dir_results, :preserve => true )
                FileUtils.cp( file, dir_results, :preserve => true )
                FileUtils.cp( file_nfo, dir_results, :preserve => true ) if File.exists?(file_nfo)
              end # unless

            end # self.tidy.execute

          end # if expects_file?

        end # if canonize

        # Write the final record
        reporter << inner_record
        if TidyRegressionTesting::log_level >= Logger::ERROR
          print '.'
          STDOUT.flush
        end

      end # config loop

      true

    end


    #########################################################
    # process_all( canonize )
    #  Runs all HTML, XHTML, and XML files in the designated
    #  `cases` directory through the process_case process,
    #  performing canonization based on `canonize`.
    #########################################################
    def process_all(canonize=false)
      return false unless dir_cases?
      result = true
      pattern = File.join(self.dir_cases, '**', '*.{html,xml,xhtml}')
      tests = Dir[pattern].reject { |f| f[%r{-expect}] }.sort
      tests.each { |file| result = (process_case(file, canonize) && result) }
      print "\n" # clear the final period.
      result
    end


    #########################################################
    # process_one( canonize )
    #  Process a single HTML, XHTML, or XML file, either in
    #  the designated cases directory (if only a filename is)
    #  given, or using the path of the given file.
    #########################################################
    def process_one(file, canonize=false)
      # We will assume that unless a full path is provided, then the case
      # file should exist in `cases`, otherwise the case file and its
      # supporting files are in the full path provided.
      dirname = File.dirname(file)
      if dirname.nil? || dirname == '.'
        if dir_cases?
          # No dirname, so there's the possibility we've asked for a case name
          # without the cases-*.*ml qualifier. If that's the case, we'll try
          # to find a matching cases-case_name-*.ml file to use.
          if file !~ /case-.*\..*ml/
            %w[xml xhtml html].each do |ext|
              file = "case-#{file}.#{ext}" if File.exists?(File.join(self.dir_cases, "case-#{file}.#{ext}"))
            end
          end
          file = File.join(self.dir_cases, file)
        else
          return false
        end
      end
      # If the file doesn't actually exist, process_case will deal with it.
      result = process_case(file, canonize)
      print "\n" # clear the final period.
      result
    end

  end # TidyRegression


  #############################################################################
  # class TidyRegressionCLI
  #  This class provides handlers for CLI parameters.
  #############################################################################
  class TidyRegressionCLI < Thor

    include TidyRegressionTesting

    class_option :cases,
                 :banner => '<directory>',
                 :desc => 'Specifies the <directory> for canonical references.',
                 :aliases => '-c'

    class_option :results,
                 :banner => '<directory>',
                 :desc => 'Specifies the <directory> prefix to report results.',
                 :aliases => '-r'

    class_option :tidy,
                 :banner => '<path>',
                 :desc => 'Specifies the <path> to the Tidy executable to use.',
                 :aliases => '-t'

    class_option :verbose,
                 :type => :boolean,
                 :desc => 'Provides verbose output.',
                 :aliases => '-v'

    class_option :debug,
                 :type => :boolean,
                 :desc => 'Provides really, really verbose output.',
                 :aliases => '-d'

    #########################################################
    # initialize
    #########################################################
    def initialize(*args)
      @regression = TidyRegression.new
      super
    end


    #########################################################
    # help
    #  Override the default help in order to better describe
    #  what we're doing.
    #########################################################
    def help(*args)
      if args.count == 0
        set_options
        message_tidy = "version #{ @regression.tidy.version}"
        message_cases = File.exists?(@regression.dir_cases) ? '' : '(directory not found; test will not run)'
        message_results = File.exists?(@regression.dir_results) ? '(will try to use)' : '(will try to create)'
        puts <<-HEREDOC

This script (#{File.basename($0)}) is a Tidy regression testing script that will
comprehensively execute every test in the suite. It also has the ability to
generate new benchmark files into the suite.

Default Locations:
------------------
  Tidy:    #{ @regression.tidy.path }, #{ message_tidy }
  Cases:   #{ @regression.dir_cases } #{ message_cases }
  Results: #{ @regression.dir_results } #{ message_results }

Complete Help:
--------------
        HEREDOC
      end

      super
    end

    #########################################################
    # rtest
    #  Tests a single file or all files.
    #########################################################
    option :notes,
           :type => :boolean,
           :desc => 'Indicates whether or not to display notes in the test report.',
           :aliases => '-n'
    desc 'rtest [<file>|<case_name>] [options]', 'Performs a regression test on <file> or <case_name>.'
    long_desc <<-LONG_DESC
      Will run a regression test for <file> or <case_name>. Use this command without
      <file> or <case_name> to run all of the regression tests. Output will be placed
      into the default directory unless an alternate is specified with --output.
      <case_name> indicates the filename portion between "case-" and the file extension.
    LONG_DESC
    def rtest(name = nil)

      set_options

      if name.nil?
        execution_ok = @regression.process_all(false)
      else
        execution_ok = @regression.process_one(name, false)
      end

      if execution_ok
        TidyTestRecord.make_report
        puts "\nThe test ended without any execution errors."
      else
        puts "\nThe test ended with one or more execution errors."
        puts "Try to run again with --verbose or --debug for details.\n\n"
      end

    end # rtest


    #########################################################
    # canonize
    #  Writes the -expects.
    #########################################################
    option :replace,
           :type => :boolean,
           :desc => 'Indicates whether or not canonize replaces existing files.',
           :aliases => '-f'
    desc 'canonize [<file>|<case_name>] [options]', 'Builds expected output for <file> or <case_name>.'
    long_desc <<-LONG_DESC
      Will build the canonical output for <file> or <case_name> and put it into the default
      directory. Use without <file> or <case_name> to generate canonical reference material for
      all files. Use with --replace to force replacement of existing files.
      <case_name> indicates the filename portion between "case-" and the file extension.
    LONG_DESC
    def canonize(name = nil)

      set_options

      if name.nil?
        @regression.process_all(true)
      else
        @regression.process_one(name, true)
      end
      
      TidyTestRecord.make_canon_report

    end # canonize


    #########################################################
    # set_options
    #  Handles command line options.
    #########################################################
    protected
    def set_options
      @regression.tidy.path = options[:tidy] unless options[:tidy].nil?
      @regression.dir_cases = options[:cases] unless options[:cases].nil?
      @regression.dir_results = options[:results] unless options[:results].nil?
      @regression.replace = options[:replace] unless options[:replace].nil?

      TidyTestRecord::show_notes = options[:notes] unless options[:notes].nil?

      TidyRegressionTesting::log_level = Logger::WARN if options[:verbose]
      TidyRegressionTesting::log_level = Logger::DEBUG if options[:debug]
    end # set_options


  end # TidyRegressionCLI

end # TidyRegressionTesting


###########################################################
# Main
###########################################################

TidyRegressionTesting::TidyRegressionCLI.start(ARGV)
