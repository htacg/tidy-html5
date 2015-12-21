#!/usr/bin/env ruby

###############################################################################
# Tidy Regression Test Suite
#  Run this script with help for more information (or examine this file.)
#
#  Commands:
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
###############################################################################

require 'rubygems'
require 'bundler/setup'
require 'thor'           # thor provides robust command line parameter parsing.
require 'ptools'         # provides additions to File:: we need for x-platform.
require 'logger'         # Log output simplified.
require 'open3'          # Run executables and capture output.
require 'fileutils'      # File utilities.


###############################################################################
# module TidyRegressionTesting
#  This module encapsulates module-level variables, the CLI handling class,
#  and the regression testing class.
###############################################################################
module TidyRegressionTesting

  ###########################################################
  # Setup
  #  Change these variables to specify different defaults.
  ###########################################################
  @@default_cases = 'cases'
  @@default_results = 'results'
  @@default_conf = 'config_default.conf'

  ###########################################################
  # Logging
  ###########################################################
  @@log = Logger.new(STDOUT)
  @@log.level = Logger::ERROR
  @@log.datetime_format = '%Y-%m-%d %H:%M:%S'

  ###########################################################
  # log_level=
  ###########################################################
  def self.log_level=(level)
    @@log.level = level
  end

  def self.log_level
    @@log.level
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
    attr_accessor :cases_valid          # Indicates that the cases dir was valid.
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

    @@test_records = [] # Array of test records.


    #########################################################
    # initialize
    #########################################################
    def initialize
      @tidy_path = nil
      @tidy_version = '0.0.0.'
      @tidy_valid = true
      @cases_valid = true
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
    end # initialize


    #########################################################
    # + test_records
    #     The singleton array of test records.
    #########################################################
    def self.test_records
      @@test_records
    end


    #########################################################
    # + make_report
    #     returns a test report.
    #########################################################
    def self.make_report
      record0 = @@test_records[0]
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


Missing Expectations Files:
===========================

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

      # Show cases that have failed.
      output << "\n\nFailed Tests:\n"
      output << "=============\n\n"
      output << 'Case File'.ljust(max_case)
      output << 'For Configuration'.ljust(max_conf)
      output << 'Markup'.ljust(9)
      output << 'Errors'.ljust(9)
      output << "\n"
      output << '---------'.ljust(max_case)
      output << '-----------------'.ljust(max_conf)
      output << '------'.ljust(9)
      output << '-------'.ljust(9)
      output << "\n"

      @@test_records.select { |record| record.tested && !record.passed_test? }.each do | record |
        output << column(record.case_file, max_case)
        output << column(record.config_file, max_conf)
        output << (record.passed_output ? "PASSED" : "FAILED").ljust(9)
        output << (record.passed_errout ? "PASSED" : "FAILED").ljust(9)
        output << "\n"
      end

      output << "\nSee files in directory #{record0.results_dir} for failed results.\n\n"
      puts output
      outpath = File.join(record0.results_dir, 'all_results.txt')
      File.open(outpath, 'w') { |file| file.write(output)}

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
    # width_of_cases
    #  Indicates the length of the longest file name.
    #########################################################
    def self.width_of_cases
      temp = @@test_records.map { |record| File.basename(record.case_file)}
      temp.count > 0 ? temp.max_by(&:length).size : 0
    end


    #########################################################
    # width_of_configs
    #  Indicates the length of the longest file name.
    #########################################################
    def self.width_of_configs
      temp = @@test_records.select { |record| !record.config_file.nil? }
      temp = temp.map { |record| File.basename(record.config_file)}
      temp.count > 0 ? temp.max_by(&:length).size : 0
    end


    #########################################################
    # width_of_errors
    #  Indicates the length of the longest file name.
    #########################################################
    def self.width_of_errors
      temp = @@test_records.select { |record| !record.missing_txt.nil? }
      temp = temp.map { |record| File.basename(record.missing_txt)}
      temp.count > 0 ? temp.max_by(&:length).size : 0
    end


    #########################################################
    # width_of_markup
    #  Indicates the length of the longest file name.
    #########################################################
    def self.width_of_markup
      temp = @@test_records.select { |record| !record.missing_htm.nil? }
      temp = temp.map { |record| File.basename(record.missing_htm)}
      temp.count > 0 ? temp.max_by(&:length).size : 0
    end


    #########################################################
    # column( item, width )
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
      @tested && @passed_errout && passed_output
    end


  end # TidyTestRecord


  #############################################################################
  # class TidyRegression
  #  The class that performs the core work of the testing suite.
  #############################################################################
  class TidyRegression

    include TidyRegressionTesting

    #########################################################
    # initialize
    #########################################################
    def initialize
      @cases = nil
      @results = nil
      @tidy = nil
      @replace = false
      @reporter = TidyTestRecord.test_records
    end # initialize


    #########################################################
    # property cases
    #  Indicates the directory from which to read the test
    #  cases.
    #########################################################
    def cases
      if @cases.nil?
        self.cases = @@default_cases
      end
      @cases
    end # cases

    def cases=( value )
      @cases = File.expand_path(value)
    end


    #########################################################
    # property results
    #  Indicates the directory in which to write test pass
    #  and failure information. The value will be modified
    #  with the current tidy_version upon setting.
    #########################################################
    def results
      if @results.nil?
        self.results = @@default_results
      end
      @results
    end

    def results=( value )
      if tidy_version.nil?
        result = "#{value}-0.0.0"
      else
        result = "#{value}-#{tidy_version}"
      end
      @results = File.expand_path(result)
    end


    #########################################################
    # property conf_default
    #  Returns the path and file for the default
    #  configuration file used when no config file is
    #  specified for a test.
    #  nil value indicates that tidy is not found.
    #########################################################
    def conf_default
      File.join(cases, @@default_conf)
    end


    #########################################################
    # property tidy
    #  Indicates the complete path to the tidy executable
    #  to use for running tests and generating canonical
    #  reference material.
    #  nil value indicates that tidy is not found.
    #########################################################
    def tidy
      if @tidy.nil?
        self.tidy = File.which('tidy')
      end
      @tidy
    end

    def tidy=( value )
      if !value.nil? && File.basename( value, '.*').start_with?('tidy') && File.executable?( value )
        @tidy = File.expand_path(value)
      else
        @tidy = nil
      end
    end


    #########################################################
    # property tidy_version
    #  Returns the tidy version string of the executable.
    #  nil value indicates that tidy is not found.
    #########################################################
  def tidy_version
    if tidy.nil?
      nil
    else
      "#{IO.popen("#{tidy} -v").readline.split.last.scan(/\d+/).join('.')}"
    end
  end


    #########################################################
    # property replace
    #  Indicates the state of the --replace command line
    #  option, and specifies whether canonical files will
    #  be overwritten during the process.
    #########################################################
    def replace
      @replace
    end

    def replace=( value )
      @replace = value
    end


    #########################################################
    # property reporter
    #  Provides access to the TidyTestRecord instance.
    #########################################################
    def reporter
      @reporter
    end


    #########################################################
    # check_cases_dir
    #########################################################
    def check_cases_dir
      if File.exists?(cases) && File.readable?(cases)
        @@log.info "Will uses cases in #{cases}"
        true
      else
        @@log.error "Directory #{cases} does not exist or could not be read."
        false
      end
    end


    #########################################################
    # check_results_dir
    #########################################################
    def check_results_dir
      unless File.exists?(results)
        begin
          Dir.mkdir(results)
        rescue SystemCallError
          @@log.error "Directory #{results} could not be created."
          return false
        end
        @@log.info "Created results directory #{results}"
      end
      if File.readable?(results)
        @@log.info "Will place results into #{results}"
        true
      else
        @@log.error "Directory #{results} could not be read."
        false
      end
    end


    #########################################################
    # check_test_file( file )
    #########################################################
    def check_test_file( file )
      if File.exists?(file) && File.readable?(file)
        @@log.info "Will use file #{file}"
        true
      else
        @@log.error "File #{file} does not exist or could not be read."
        false
      end
    end


    #########################################################
    # check_conf_default
    #########################################################
    def check_conf_default
      if File.exists?(conf_default) && File.readable?(conf_default)
        @@log.info "Will use default configuration file #{conf_default}"
        true
      else
        @@log.warn "Default configuration file #{conf_default} does not exist or could not be read."
        false
      end
    end


    #########################################################
    # check_tidy
    #########################################################
    def check_tidy
      if tidy.nil?
        @@log.error "Tidy at #{tidy} was not found or is not executable."
        false
      else
        @@log.info "Will use Tidy located at #{tidy}"
        true
      end
    end


    #########################################################
    # check_expect_htm( expect )
    #########################################################
    def check_expect_htm( expect )
      if File.exists?( expect )
        @@log.info "Expectation file #{expect} was found."
        true
      else
        @@log.warn "Missing expectation file #{expect}."
        false
      end
    end


    #########################################################
    # check_expect_txt( expect )
    #########################################################
    def check_expect_txt( expect )
      if File.exists?(expect)
        @@log.info "Expectation file #{expect} was found."
        true
      else
        @@log.warn "Missing expectation file #{expect}."
        false
      end
    end


    #########################################################
    # clean_error_text( text )
    #  We want to discard everything after:
    #  - No warnings or errors were found.
    #  - were found!
    #  I wonder if we'd be happy with the --quiet output so
    #  that we can avoid this. It means regenerating the test
    #  cases, but they all seem to pass anyway.
    #########################################################
    def clean_error_text( text )
      terminator_1 = 'No warnings or errors were found.'
      terminator_2 = 'were found!'

      return nil if text.nil? || text == ''

      if text.index(terminator_1)
        terminator = terminator_1
      else
        if text.index(terminator_2)
          terminator = terminator_2
        else
          return text
        end
      end


      text.slice(0, text.index(terminator) + terminator.size + 1)

    end


    #########################################################
    # process_case( file )
    # canonize_case and test_case are nearly identical, so we'll
    # do most of the heavy lifting here.
    #########################################################
    def process_case( file, canonize=false )
      file = File.join( cases, file )
      basename = File.basename( file, '.*' )

      # Start a new testing record for this test iteration.
      record = TidyTestRecord.new

      # These are all showstoppers, but let's get as much information
      # for the test record as we can before aborting.
      record.tidy_path = tidy
      record.tidy_valid = check_tidy
      record.tidy_version = tidy_version
      record.cases_valid = check_cases_dir
      record.case_file = file
      record.case_file_valid = check_test_file( file )
      record.results_dir = results
      record.results_valid = check_results_dir

      unless record.tidy_valid && record.cases_valid && record.case_file_valid && record.results_valid
        reporter << record
        return false
      end

      # Get a list of all configuration files (if any) to use.
      # Use the default configuration file if required.
      configs = Dir.glob(File.join(cases, "#{basename}*.conf") )

      # If there are no configs for the test, attempt to use the default.
      if configs.count < 1
        record.config_file = conf_default
        record.config_file_valid = check_conf_default
        unless record.config_file_valid
          reporter << record
          return false
        end
        configs << conf_default
      end

      # Run through all of the configurations.
      configs.sort.each do | config_file |
        @@log.info "Testing with config file #{config_file}"

        # Duplicate the record so we have a new one each run of this inner loop
        inner_record = record.clone

        # Log the config file.
        inner_record.config_file = config_file

        # Build the expect filenames for this configuration
        if config_file == conf_default
          base_conf = File.join(cases, basename)
        else
          base_conf = File.join(cases, File.basename(config_file, '.*'))
        end
        expects_txt = "#{base_conf}-expect.txt"
        expects_htm = "#{base_conf}-expect#{File.extname(file)}"

        # Build the

        if canonize
          #################
          # CANONIZE
          #################

          # Let's run tidy
          execute = "#{tidy} -config #{config_file} --tidy-mark no #{file}"
          tidy_out, tidy_err, tidy_status = Open3.capture3(execute)

          # Write the results
          if File.exists?(expects_txt) && !replace
            @@log.warn "#{expects_txt} already exists and won't be replaced."
          else
            File.open(expects_txt, 'w') { |the_file| the_file.write(tidy_err)}
          end

          if File.exists?(expects_htm) && !replace
            @@log.warn "#{expects_htm} already exists and won't be replaced."
          else
            File.open(expects_htm, 'w') { |the_file| the_file.write(tidy_out)}
          end

        else
          #################
          # TEST
          #################

          # Make sure that the expectations are available for this config.
          m_expect_txt = check_expect_txt(expects_txt)
          m_expect_htm = check_expect_htm(expects_htm)
          inner_record.missing_txt = expects_txt unless m_expect_txt
          inner_record.missing_htm = expects_htm unless m_expect_htm

          if m_expect_htm && m_expect_txt
            expects_txt_txt = clean_error_text(IO.read(expects_txt))
            expects_htm_txt = IO.read(expects_htm)

            # Let's run tidy
            execute = "#{tidy} -config #{config_file} --tidy-mark no #{file}"
            tidy_out, tidy_err, tidy_status = Open3.capture3(execute)
            tidy_err = clean_error_text(tidy_err)
            inner_record.tested = true

            # Set comparison flags
            inner_record.passed_output = tidy_out == expects_htm_txt
            inner_record.passed_errout = tidy_err == expects_txt_txt

            # Write failing files.
            unless inner_record.passed_test?
              # In the case of multiple configurations, we need to get
              # the configuration number to append to the markup file.
              config_number = File.basename(config_file, '.*').match(/.*-.*-(.*)/)
              config_number = config_number.nil? ? nil : "-#{config_number[1]}"
              file_err = "#{File.basename(file, '.*')}#{config_number}-fail.txt"
              file_htm = "#{File.basename(file, '.*')}#{config_number}-fail#{File.extname(file)}"

              # Write results and copy the originals for convenience.
              File.open(File.join(results, file_err), 'w') { |the_file| the_file.write(tidy_err)}
              File.open(File.join(results, file_htm), 'w') { |the_file| the_file.write(tidy_out)}
              FileUtils.cp(expects_htm, results, { preserve: true })
              FileUtils.cp(expects_txt, results, { preserve: true })
              FileUtils.cp(file, results, { preserve: true })
            end # unless
          end # if
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
    # canonize_case( file )
    #  Generates the -expects information for a single file,
    #  and places them into the designated `results`
    #  directory. Existing files will NOT be replaced unless
    #  the --replace command line option is used.
    #  If multiple configuration files are present then the
    #  new files will be written using each configuration.
    #########################################################
    def canonize_case( file )
      process_case( file, true )
    end


    #########################################################
    # canonize_all
    #  Runs all HTML, XHTML, and XML files in the designated
    #  `cases` directory through the canonization process.
    #  Files will not be overwritten unless --replace is
    #  used on the command line.
    #########################################################
    def canonize_all
      pattern = File.join(cases, '*.{html,xml,xhtml}')
      tests = Dir[pattern].reject { |f| f[%r{-expect}] }.sort
      tests.each { |file| canonize_case(File.basename(file)) }
      puts "\n"
    end

    #########################################################
    # test_case( file )
    #  Runs a single file through regression testing. If
    #  multiple configuration files are present, then the
    #  single test case will be run for each configuration.
    #  Note that only the file basename will be taken into
    #  account. All tests must reside in the specified (or
    # default) cases directory.
    #########################################################
    def test_case(file)
      process_case( file, false )
    end


    #########################################################
    # test_all
    #  Runs all HTML, XHTML, and XML files in the designated
    #  `cases` directory through the testing process.
    #########################################################
    def test_all
      pattern = File.join(cases, '*.{html,xml,xhtml}')
      tests = Dir[pattern].reject { |f| f[%r{-expect}] }.sort
      tests.each { |file| test_case(File.basename(file)) }
      puts "\n"
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
        message_tidy = "version #{ @regression.tidy_version}"
        message_cases = File.exists?(@regression.cases) ? '' : '(directory not found; test will not run)'
        message_results = File.exists?(@regression.results) ? '(will try to use)' : '(will try to create)'
        puts <<-HEREDOC

This script (#{File.basename($0)}) is a Tidy regression testing script that will
comprehensively execute every test in the suite. It also has the ability to
generate new benchmark files into the suite.

Default Locations:
------------------
  Tidy:    #{ @regression.tidy }, #{ message_tidy }
  Cases:   #{ @regression.cases } #{ message_cases }
  Results: #{ @regression.results } #{ message_results }

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
    desc 'rtest [<file>]', 'Performs a regression test on <file>.'
    long_desc <<-LONG_DESC
      Will run a regression test for <file>. Use this command without <file>
      to run all of the regression tests. Output will be placed into the
      default directory unless an alternate is specified with --output.
    LONG_DESC
    def rtest(name = nil)

      set_options

      if name.nil?
        @regression.test_all
      else
        if @regression.test_case(name)
          puts "\nThe test ended without any execution errors."
          puts "See #{@regression.results} for testing results.\n\n"
        else
          puts "\nThe test ended with one or more execution errors.\n\n"
        end
      end

      TidyTestRecord.make_report

    end # rtest


    #########################################################
    # canonize
    #  Writes the -expects.
    #########################################################
    option :replace,
           :type => :boolean,
           :desc => 'Indicates whether or not canonize replaces existing files.',
           :aliases => '-f'
    desc 'canonize [<file>]', 'Builds expected output for <file>.'
    long_desc <<-LONG_DESC
      Will build the canonical output for <file> and put it into the default
      directory. Use without <file> to generate canonical reference material for
      all files. Use with --replace to force replacement of existing files.
    LONG_DESC
    def canonize(name = nil)

      set_options
      @regression.replace = options[:replace] unless options[:replace].nil?

      if name.nil?
        @regression.canonize_all
      else
        @regression.canonize_case(name)
      end

    end # canonize


    #########################################################
    # set_options
    #  Handles command line options.
    #########################################################
    protected
    def set_options
        @regression.tidy = options[:tidy] unless options[:tidy].nil?
        @regression.cases = options[:cases] unless options[:cases].nil?
        @regression.results = options[:results] unless options[:results].nil?

        TidyRegressionTesting::log_level = Logger::WARN if options[:verbose]
        TidyRegressionTesting::log_level = Logger::DEBUG if options[:debug]
    end # set_options


  end # TidyRegressionCLI

end # TidyRegressionTesting


###########################################################
# Main
###########################################################

TidyRegressionTesting::TidyRegressionCLI.start(ARGV)
