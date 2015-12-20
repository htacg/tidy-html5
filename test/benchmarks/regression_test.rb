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
#  --output=<directory>, -o
#  --tidy=<path>, -t
#
###############################################################################

require 'rubygems'
require 'bundler/setup'
require 'thor'           # thor provides robust command line parameter parsing.
require 'ptools'         # provides additions to File:: we need for x-platform.


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


  #############################################################################
  # class TidyRegression
  #  The class that performs the core work of the testing
  #  suite.
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
      if name == nil
        puts 'All tests'
      else
        puts "Testing #{name}"
      end

      if options[:cases]
        @regression.cases = options[:cases]
      end

      if @regression.cases
        puts "Success with #{@regression.cases}."
      else
        puts "Fail with #{options[:cases]}"
      end


    end # rtest


    #########################################################
    # canonize
    #  Writes the -expects.
    #########################################################
    option :replace,
           :type => :boolean,
           :desc => 'Indicates whether or not canonize replaces existing files.',
           :aliases => '-r'
    desc 'canonize [<file>]', 'Builds expected output for <file>.'
    long_desc <<-LONG_DESC
      Will build the canonical output for <file> and put it into the default
      directory. Use without <file> to generate canonical reference material for
      all files. Use with --replace to force replacement of existing files.
    LONG_DESC
    def canonize(name = nil)

      set_options
      if name == nil
        puts 'All files generated.'
      else
        puts "Generating #{name}"
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
