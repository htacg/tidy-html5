#!/usr/bin/env ruby

###############################################################################
# Tidy Regression Test Suite
#  Look for the heredoc below, or run this script with help for more info.
#
#  rtest
#  rtest my_file.html
#  canonize
#  canonize my_file.html
#  --cases=<directory>, -c
#  --results=<directory>, -r
#  --tidy=<path>, -t
#  --replace, -f
#
###############################################################################

require 'rubygems'
require 'bundler/setup'
require 'thor'           # thor provides robust command line parameter parsing.
require 'ptools'         # provides additions to File:: we need for x-platform.
require 'logger'
require 'open3'


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
  @@log.level = Logger::DEBUG
  @@log.datetime_format = '%Y-%m-%d %H:%M:%S'

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
      @@test_records.each do | record |
        puts "Tidy path = #{record.tidy_path}"
        puts "Tidy version = #{record.tidy_version}"
        puts "File requested = #{record.case_file}"
        puts "Passed Output = #{record.passed_output}"
        puts "Passed Errors = #{record.passed_errout}"
        puts "Passed Test = #{record.passed_test?}"
      end
      puts "===================="
      puts "Number of case files = #{self.count_of_cases_requested}"
      puts "Total Configs requested = #{self.count_of_configs_requested}"
      puts "Case files tested = #{self.count_of_cases_tested}"
      puts "Configs tested = #{self.count_of_configs_tested}"
      puts "Configs aborted = #{self.count_of_configs_aborted}"
      puts "Configs passed = #{self.count_of_configs_passed}"
      puts "Configs failed = #{self.count_of_configs_failed}"
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
        @@log.fatal "Directory #{cases} does not exist or could not be read."
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
        @@log.fatal "File #{file} does not exist or could not be read."
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
        @@log.fatal "Default configuration file #{conf_default} does not exist or could not be read."
        false
      end
    end


    #########################################################
    # check_tidy
    #########################################################
    def check_tidy
      if tidy.nil?
        @@log.fatal "Tidy at #{tidy} was not found or is not executable."
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
        @@log.fatal "Missing expectation file #{expect}."
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
        @@log.fatal "Missing expectation file #{expect}."
        false
      end
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

    end


    #########################################################
    # canonize_all
    #  Runs all HTML, XHTML, and XML files in the designated
    #  `cases` directory through the canonization process.
    #  Files will not be overwritten unless --replace is
    #  used on the command line.
    #########################################################
    def canonize_all

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

      unless record.tidy_valid && record.cases_valid && record.case_file_valid
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
      configs.each do | config_file |
        @@log.info "Testing with config file #{config_file}"

        # Duplicate the record so we have a new one each run of this inner loop
        inner_record = record.dup

        # Make sure that the expectations are available for this config.
        if config_file == conf_default
          base_conf = File.join(cases, basename)
        else
          base_conf = File.join(cases, File.basename(config_file, '.*'))
        end
        expects_txt = "#{base_conf}-expect.txt"
        expects_htm = "#{base_conf}-expect#{File.extname(file)}"
        inner_record.missing_txt = expects_txt unless check_expect_txt(expects_txt)
        inner_record.missing_htm = expects_htm unless check_expect_htm(expects_htm)
        unless check_expect_txt(expects_txt) && check_expect_htm(expects_htm)
          reporter << inner_record
          return false
        end

        expects_txt_txt = IO.read(expects_txt)
        expects_htm_txt = IO.read(expects_htm)

        # Let's run tidy
        execute = "#{tidy} -config #{config_file} --tidy-mark no -quiet #{file}"
        tidy_out, tidy_err, tidy_status = Open3.capture3(execute)
        inner_record.tested = true

        # Set comparison flags
        inner_record.passed_output = tidy_out == expects_htm_txt
        inner_record.passed_errout = tidy_err == expects_txt_txt

        # Write the final record
        reporter << inner_record

      end

      true

    end


    #########################################################
    # test_all
    #  Runs all HTML, XHTML, and XML files in the designated
    #  `cases` directory through the testing process.
    #########################################################
    def test_all
      pattern = File.join(cases, "*.{html,xml,xhtml}")
      tests = Dir[pattern].reject { |f| f[%r{-expect}] }
      tests.each { |file| test_case(File.basename(file)) }
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
    end # set_options


  end # TidyRegressionCLI

end # TidyRegressionTesting


###########################################################
# Main
###########################################################

TidyRegressionTesting::TidyRegressionCLI.start(ARGV)
