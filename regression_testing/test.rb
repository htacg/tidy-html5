#!/usr/bin/env ruby

###############################################################################
# test.rb
#  Run this script with `help` for more information (or examine this file.)
#
#  This script replaces the previous tools-cmd and tools-sh shell scripts,
#  as a single, cross-platform means of providing regression testing support
#  for HTML Tidy.
###############################################################################

require 'rubygems'       # Ensure bundler is used.
require 'bundler/setup'  # Make sure the Gemfile is recognized.
require 'logger'         # Log output simplified.
require 'fileutils'      # File utilities.
require 'thor'           # Thor provides robust command line parameter parsing.
require 'tty-editor'     # Cross-platform opening of files in default editor.


################################################################################
# module TidyRegressionTestModule
#  This module encapsulates module-level variables, utilities, logging,
#  and the CLI handling class.
###############################################################################
#noinspection RubyTooManyInstanceVariablesInspection
module TidyRegressionTestModule

  ###########################################################
  # Setup
  #  Change these variables in case directories are changed.
  #  Note that DIR_TIDY can be changed with input options.
  ###########################################################
  DIR_TEST_SETS = File.expand_path('cases')
  EXE_TIDY      = File.expand_path(File.join('..', 'build', 'cmake', 'tidy'))
  VERSION_FILE  = File.join(File.expand_path('..', File.dirname(__FILE__)), 'version.txt')


  ###########################################################
  # The shared logger.
  #  This is a module-level logger, shared amongst everyone
  #  in a singleton-like fashion.
  ###########################################################
  SHARED_LOGGER                 = Logger.new(STDOUT)
  SHARED_LOGGER.level           = Logger::ERROR
  SHARED_LOGGER.datetime_format = '%Y-%m-%d %H:%M:%S'

  WINDOWS_OS = (/cygwin|mswin|mingw|bccwin|wince|emx/ =~ RUBY_PLATFORM)


  #############################################################################
  # class TidyTestSet
  #  This class contains information a single test set.
  #############################################################################
  class TidyTestSet

    attr_reader   :test_set_name
    attr_accessor :dir_test_set
    attr_reader   :dir_expects
    attr_reader   :dir_results
    attr_reader   :case_paths
    attr_reader   :case_names
    attr_accessor :path_tidy_exe

    #########################################################
    # initialize
    #########################################################
    def initialize( with_directory:, path_to_tidy: )

      @dir_expects = nil
      @dir_results = nil
      @case_paths = nil

      self.dir_test_set = with_directory
      self.path_tidy_exe = path_to_tidy
    end


    #########################################################
    # property test_set_name
    #########################################################
    def test_set_name
      @test_set_name
    end


    #########################################################
    # property dir_test_set
    #########################################################
    def dir_test_set
      @dir_test_set
    end

    def dir_test_set=( test_set_directory )
      @test_set_name = File.basename(test_set_directory)[/(.*)-cases/,1]
      candidate_expects = File.join(File.dirname(test_set_directory), "#{@test_set_name}-expects")
      if File.exist?(candidate_expects)
        @dir_test_set = test_set_directory
      else
        SHARED_LOGGER.warn("Skipping test set #{test_set_directory} because expectations directory #{candidate_expects} does not exist.")
        @dir_test_set = nil
      end
    end


    #########################################################
    # property dir_expects
    #########################################################
    def dir_expects
      unless @dir_expects
        @dir_expects = File.join(File.dirname(self.dir_test_set), "#{@test_set_name}-expects")
      end
      @dir_expects
    end


    #########################################################
    # property dir_results
    #########################################################
    def dir_results
      unless @dir_results
        @dir_results = File.join(File.dirname(self.dir_test_set), "#{@test_set_name}-results")
      end
      @dir_results
    end


    #########################################################
    # property case_paths
    #########################################################
    def case_paths
      unless @case_paths
        @case_paths = []
        Dir.glob("#{self.dir_test_set}/*.{html,xml,xhtml,htm}").sort.each do |html_file|
          SHARED_LOGGER.info("Adding case path #{html_file}")
          case_name = File.basename( html_file[/(.*)@/,1] )
          candidate_expects_html = File.join( self.dir_expects, "#{case_name}#{File.extname(html_file)}" )
          candidate_expects_output = File.join( self.dir_expects, "#{case_name}.txt" )
          #noinspection RubyNilAnalysis -- this is a false positive, because we've explicitly made this an array.
          @case_paths.push(html_file)
          unless File.exist?(candidate_expects_html) && File.exist?(candidate_expects_output)
            SHARED_LOGGER.warn("Note: #{html_file} is missing some expectations files in #{self.dir_expects}.")
          end
        end
      end
      @case_paths
    end


    #########################################################
    # property case_names
    #########################################################
    def case_names
      #noinspection RubyNilAnalysis -- cannot be nil at this point.
      self.case_paths.map { |case_path| File.basename(case_path)[/^case-(.*)@.*$/,1] }
    end


    #########################################################
    # property path_tidy_exe
    #########################################################
    def path_tidy_exe
      @path_tidy_exe
    end

    def path_tidy_exe=( value )
      unless File.exist?( value )
        raise StandardError.new "The path #{value} to tidy doesn’t exist."
      end
      unless File.executable?( value )
        raise StandardError.new "The path #{value} to tidy is there, but isn’t executable."
      end
      @path_tidy_exe = value
    end

  end # class TidyTestSet


  #############################################################################
  # class TidyTestCase
  #  This class contains information a single test case.
  #############################################################################
  class TidyTestCase

    attr_accessor :path_file
    attr_reader   :name_test_set
    attr_reader   :name_case
    attr_reader   :path_config
    attr_reader   :expects_exit_code
    attr_reader   :dir_test_sets
    attr_reader   :dir_expects
    attr_reader   :dir_results
    attr_reader   :path_expects_html
    attr_reader   :path_expects_output
    attr_reader   :path_result_html
    attr_reader   :path_result_output
    attr_accessor :path_tidy_exe
    attr_reader   :test_passed
    attr_reader   :test_report
    attr_reader   :test_exit_status


    #########################################################
    # initialize
    #########################################################
    def initialize( with_file:, path_to_tidy: )

      @path_file = nil
      @name_test_set = nil
      @name_case = nil
      @path_config = nil
      @expects_exit_code = nil
      @dir_test_sets = nil
      @dir_expects = nil
      @dir_results = nil
      @path_expects_html = nil
      @path_expects_output = nil
      @path_result_html = nil
      @path_result_output = nil
      @path_tidy_exe = nil
      @test_report = nil
      @test_exit_status = nil

      @test_complete = false
      @test_diff_html = nil
      @test_diff_html_status = nil
      @test_diff_output = nil
      @test_diff_output_status = nil

      self.path_file = with_file
      self.path_tidy_exe = path_to_tidy
    end # initialize


    #############################################################################
    # Property Accessors
    #############################################################################

    #########################################################
    # property path_file
    #########################################################
    def path_file
      @path_file
    end

    def path_file=( value )
      if File.exist?(File.expand_path(value))
        @path_file = value
      else
        raise StandardError.new "File #{value} doesn’t exist."
      end

      valid_extensions = %w(.html .xhtml .htm .xml)
      unless valid_extensions.include?(File.extname(value).downcase)
        raise StandardError.new "File #{value} doesn’t have a correct extension (one of #{valid_extensions})."
      end

      @path_file = value
    end


    #########################################################
    # property name_test_set
    #   This is the enclosing directory name, without the
    #   -cases suffix.
    #########################################################
    def name_test_set
      unless @name_test_set
        @name_test_set = File.basename( File.dirname(self.path_file)[/(.*)-cases/,1] )
      end

      @name_test_set
    end


    #########################################################
    # property name_case
    #########################################################
    def name_case
      unless @name_case
        @name_case = File.basename(self.path_file)[/case-(.*)@/, 1]
      end

      @name_case
    end


    #########################################################
    # property path_config
    #   The config file is either the same as the test case
    #   file (without the exit code metadata) and the .conf
    #   extension, or the config_default.conf if not found.
    #########################################################
    def path_config
      unless @path_config
        directory = File.dirname(self.path_file)
        candidate = File.join( directory, "case-#{name_case}.conf" )

        unless File.exist?(candidate)
          candidate = File.join( directory, 'config_default.conf')
          unless File.exist?(candidate)
            raise StandardError.new "Case #{name_case} doesn’t have a configuration file."
          end
        end
        @path_config = candidate
      end

      @path_config
    end


    #########################################################
    # property expects_exit_code
    #   This is the metadata between the @ and extension.
    #########################################################
    def expects_exit_code
      unless @expects_exit_code
        @expects_exit_code = File.basename(self.path_file)[/case-.*@(.)./, 1]
      end

      @expects_exit_code
    end


    #########################################################
    # property dir_test_sets
    #   This is the directory containing the test sets.
    #########################################################
    def dir_test_sets
      unless @dir_test_sets
        @dir_test_sets = File.dirname( File.dirname(self.path_file) )
      end

      @dir_test_sets
    end


    #########################################################
    # property dir_expects
    #   This is the directory within the test sets that
    #   contains the expectations files.
    #########################################################
    def dir_expects
      unless @dir_expects
        @dir_expects = File.join( self.dir_test_sets, "#{self.name_test_set}-expects" )
        unless File.exist?(@dir_expects)
          raise StandardError.new "The expectations directory #{dir_expects} doesn’t seem to exist."
        end
      end

      @dir_expects
    end


    #########################################################
    # property dir_results
    #   This is the in-source directory where results will
    #   be generated.
    #########################################################
    def dir_results
      unless @dir_results
        @dir_results = File.join( self.dir_test_sets, "#{self.name_test_set}-results" )
        unless File.exist?(@dir_results)
          FileUtils.mkdir_p(@dir_results)
          unless File.exist?(@dir_results)
            raise StandardError.new "The expectations directory #{@dir_results} doesn’t seem to exist and couldn’t be created."
          end
        end
      end

      @dir_results
    end


    #########################################################
    # property path_expects_html
    #   A file in the expectations directory with the same
    #   name as the HTML file (without @ metadata).
    #########################################################
    def path_expects_html
      unless @path_expects_html
        basename = File.basename(self.path_file)[/(.*)@/,1] + File.extname(self.path_file)
        @path_expects_html = File.join( self.dir_expects, basename )
        unless File.exist?(@path_expects_html)
          SHARED_LOGGER.warn("The expectations file #{@path_expects_html} doesn’t seem to exist.")
        end
      end

      @path_expects_html
    end


    #########################################################
    # property path_expects_output
    #   A file in the expectations directory with the same
    #   name as the HTML file (without @ metadata), but
    #   of type .txt.
    #########################################################
    def path_expects_output
      unless @path_expects_output
        basename = File.basename(self.path_file)[/(.*)@/,1] + '.txt'
        @path_expects_output = File.join( self.dir_expects, basename )
        unless File.exist?(@path_expects_output)
          SHARED_LOGGER.warn("The expectations file #{@path_expects_output} doesn’t seem to exist.")
        end
      end

      @path_expects_output
    end


    #########################################################
    # property path_result_html
    #   A file in the results directory with the same
    #   name as the HTML file (without @ metadata). This
    #   file doesn't necessarily exist until the test is
    #   executed.
    #########################################################
    def path_result_html
      unless @path_result_html
        basename = File.basename(self.path_file)[/(.*)@/,1] + File.extname(self.path_file)
        @path_result_html = File.join( self.dir_results, basename )
      end

      @path_result_html
    end


    #########################################################
    # property path_result_output
    #   A file in the results directory with the same
    #   name as the HTML file (without @ metadata), but
    #   of type .txt. This file doesn't necessarily exist
    #   until the test is executed.
    #########################################################
    def path_result_output
      unless @path_result_output
        basename = File.basename(self.path_file)[/(.*)@/,1] + '.txt'
        @path_result_output = File.join( self.dir_results, basename )
      end

      @path_result_output
    end


    #########################################################
    # property path_tidy_exe
    #########################################################
    def path_tidy_exe
      @path_tidy_exe
    end

    def path_tidy_exe=( value )
      unless File.exist?( value )
        raise StandardError.new "The path #{value} to tidy doesn’t exist."
      end
      unless File.executable?( value )
        raise StandardError.new "The path #{value} to tidy is there, but isn’t executable."
      end
      @path_tidy_exe = value
    end


    #########################################################
    # property @test_passed
    #########################################################
    def test_passed
      unless @test_complete
        self.perform_test
      end
      @test_exit_status == self.expects_exit_code.to_i &&
          @test_diff_html_status == 0 &&
          @test_diff_output_status == 0
    end


    #########################################################
    # property @test_report
    #########################################################
    def test_report
      unless @test_complete
        self.perform_test
      end

      if self.test_passed
        result = "PASSED | status #{@test_exit_status} expected #{self.expects_exit_code} | #{self.path_file}\n"
      else
        result  = WINDOWS_OS ? "\n++++++++++++++++++++\n" : "\n⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓⇓\n"
        result += "FAILED | status #{@test_exit_status} expected #{self.expects_exit_code} | #{self.path_file}\n"
        result += "\n#{@test_diff_html}" unless @test_diff_html_status == 0
        result += "\n#{@test_diff_output}" unless @test_diff_output_status == 0
        result += WINDOWS_OS ? "^^^^^^^^^^^^^^^^^^^^\n\n" : "⇑⇑⇑⇑⇑⇑⇑⇑⇑⇑⇑⇑⇑⇑⇑⇑⇑⇑⇑⇑\n\n"
      end
      result
    end


    #########################################################
    # property @test_exit_status
    #########################################################
    def test_exit_status
      @test_exit_status
    end


    #############################################################################
    # Protected Methods
    #############################################################################

    protected

    #########################################################
    # perform_test
    #########################################################
    def perform_test

      #--------------------------------------------------
      # Remove existing output files, if any.
      #--------------------------------------------------
      File.delete(self.path_result_html) if File.exist?(self.path_result_html)
      File.delete(self.path_result_output) if File.exist?(self.path_result_output)

      #--------------------------------------------------
      # Run HTML Tidy on the input file.
      #--------------------------------------------------
      shell_command = %Q<"#{self.path_tidy_exe}" -lang en_us -f "#{self.path_result_output}" -config "#{self.path_config}" --tidy-mark no -o "#{self.path_result_html}" "#{self.path_file}">
      SHARED_LOGGER.info("Performing: #{shell_command}")
      %x(#{shell_command})
      @test_exit_status = $?.exitstatus
      SHARED_LOGGER.info("Tidy exited with status: #{@test_exit_status}")

      #--------------------------------------------------
      # Get the diffs for the html files.
      #--------------------------------------------------
      diff_cmd = WINDOWS_OS ? 'fc /l' : 'diff -ua'
      if File.exist?(self.path_expects_html)
        shell_command = %Q<#{diff_cmd} "#{possible_windows_shell_path(self.path_expects_html)}" "#{possible_windows_shell_path(self.path_result_html)}">
        SHARED_LOGGER.info("Performing: #{shell_command}")
        @test_diff_html = %x( #{shell_command} )
        @test_diff_html_status = $?.exitstatus
        SHARED_LOGGER.info("diff/fc exited with status: #{@test_diff_html_status}")
      else
        # Although the HTML -expects file is missing, that might be by design, because
        # some cases are Tidy failures and don't produce output. If the HTML -results
        # is also missing, then this is actually a match, so we'll give it a pass.
        if File.exist?(self.path_result_html)
          @test_diff_html = "diff: Expectations file #{self.path_expects_html} is missing!"
        else
          @test_diff_html = ""
          @test_diff_html_status = 0
        end
      end

      #--------------------------------------------------
      # Get the diffs for the output files.
      #--------------------------------------------------
      if File.exist?(self.path_expects_output)
        shell_command = %Q<#{diff_cmd} "#{possible_windows_shell_path(self.path_expects_output)}" "#{possible_windows_shell_path(self.path_result_output)}">
        SHARED_LOGGER.info("Performing: #{shell_command}")
        @test_diff_output = %x( #{shell_command} )
        @test_diff_output_status = $?.exitstatus
        SHARED_LOGGER.info("diff/fc exited with status: #{@test_diff_output_status}")
      else
        @test_diff_output = "diff: Expectations file #{self.path_expects_output} is missing!"
      end

      @test_complete = true
    end


    ###########################################################
    # Sometimes Windows still rejects normal file path
    # specifiers, such as the fc command, which thinks that
    # the file isn't found when using forward slashes.
    ###########################################################
    def possible_windows_shell_path(unix_path)
      if WINDOWS_OS
        unix_path.gsub(File::SEPARATOR, File::ALT_SEPARATOR || File::SEPARATOR)
      else
        unix_path
      end
    end


  end # class TidyTestCase


  #############################################################################
  # class TidyRegressionTestCLI
  #  This class provides handlers for CLI parameters. Because it's such a
  #  simple application, it also serves as our Application.
  #############################################################################
  class TidyRegressionTestCLI < Thor

    class_option :verbose,
                 :type => :boolean,
                 :desc => 'Provides verbose debug output.',
                 :aliases => '-v'

    class_option :debug,
                 :type => :boolean,
                 :desc => 'Provides really verbose debug output.',
                 :aliases => '-d'

    class_option :tidy,
                 :type => :string,
                 :desc => "Specify an alternate HTML Tidy binary instead of the default at #{EXE_TIDY}.",
                 :aliases => '-t'


    #########################################################
    # Property declarations
    #########################################################
    attr_accessor :tidy_path
    attr_reader   :all_test_sets # array of all test sets.


    #########################################################
    # Initialize
    #########################################################
    def initialize(args = nil, options = nil, config = nil)
      super
      set_options
    end


    #########################################################
    # exit_on_failure?
    #########################################################
    def self.exit_on_failure?
      true
    end


    #########################################################
    # help
    #  Override the default help in order to better describe
    #  what we're doing.
    #########################################################
    def help(*args)
      if args.count == 0
        puts <<~HEREDOC

          This script (#{File.basename($0)}) runs HTML Tidy’s regression tests. You can instruct
          it to run all test sets, a single test set, or even a single case.
          
          Complete Help:
          --------------
        HEREDOC
      end

      super
    end # help


    #########################################################
    # test
    #  See long_desc
    #########################################################
    desc 'test', 'Runs all test cases in all test sets.'
    option :omitpassed,
           :type => :boolean,
           :desc => 'Omits PASSED test cases to keep output quieter.',
           :aliases => '-q'
    long_desc <<-LONG_DESC
      Runs all test cases in all test sets. Any directory in
      #{DIR_TEST_SETS}
      ending with '-cases' and having a matching '-expects' counterpart is
      assumed to be a test set.

      This command will exit with a non-zero exit code if any of tests
      do no exit with the expected exit code, or if any of the output
      produced does not match the expectation in '-expects'. It will
      also fail if no test cases can be found.

      Summary data will be printed to stdout, as well as any diffs in
      the event of a regression test failure.

      Use case: this is the general test you should perform when
      deciding whether or not to accept changes to Tidy's source code.
    LONG_DESC
    def test
      total_tested = 0
      total_passed = 0
      self.all_test_sets.each do |test_set|
        test_set.case_paths.each do |case_file|
          test_run = TidyTestCase.new(with_file: case_file, path_to_tidy: self.tidy_path)
          puts test_run.test_report unless test_run.test_passed && options[:omitpassed]
          total_tested += 1
          total_passed += 1 if test_run.test_passed
        end
      end
      self.print_report_footer( total_tested, total_passed )
      raise Thor::Error, "Automated Testing Failed."  if total_passed < total_tested
    end # test


    #########################################################
    # only
    #  See long_desc
    #########################################################
    desc 'only <test_set_name>', 'Only runs all of the test cases in the test set given.'
    option :omitpassed,
           :type => :boolean,
           :desc => 'Omits PASSED test cases to keep output quieter.',
           :aliases => '-q'
    long_desc <<-LONG_DESC
      Runs all test cases in the given test set. Any directory in
      #{DIR_TEST_SETS}
      ending with '-cases' and having a matching '-expects' counterpart is
      assumed to be a test set. The name of the test set does not include
      the '-cases' suffix, and so do not provide it.

      This command will exit with a non-zero exit code if any of tests
      do no exit with the expected exit code, or if any of the output
      produced does not match the expectation in '-expects'. It will
      also fail if no test cases can be found.

      Summary data will be printed to stdout, as well as any diffs in
      the event of a regression test failure.

      Use case: Use this command if you want to speed up testing, especially
      if you already know that other test sets have already been tested
      successfully.
    LONG_DESC
    def only( test_set_name )
      total_tested = 0
      total_passed = 0
      test_set = all_test_sets.select { |test_case| test_case.test_set_name == test_set_name }.first
      if test_set
        test_set.case_paths.each do |case_file|
          test_run = TidyTestCase.new(with_file: case_file, path_to_tidy: self.tidy_path)
          puts test_run.test_report unless test_run.test_passed && options[:omitpassed]
          total_tested += 1
          total_passed += 1 if test_run.test_passed
        end
        self.print_report_footer( total_tested, total_passed )
      else
        puts "Test set #{test_set_name} could not be used, found, or does not meet conventions correctly."
      end
      raise Thor::Error, "Automated Testing Failed."  if total_passed < total_tested
    end # only

    #########################################################
    # case
    #  See long_desc
    #########################################################
    desc 'case <case_name>', 'Only tests a single case.'
    long_desc <<-LONG_DESC
      Run only the specific test case. If the same case name exists in
      multiple test sets, then they will be tested in the order that
      they are found. Don’t give your cases the same name if you do not
      wish to experience this behavior. Any directory in
      #{DIR_TEST_SETS}
      ending with '-cases' and having a matching '-expects' counterpart is
      assumed to be a test set. Do not provide any prefix or suffix parts
      of the case name.

      This command will exit with a non-zero exit code if the test
      does not exit with the expected exit code, or if any of the output
      produced does not match the expectation in '-expects'. It will
      also fail if the test cases cannot be found.

      Summary data will be printed to stdout, as well as any diffs in
      the event of a regression test failure.

      Use case: Use this command if you want to speed up testing, especially
      if you're adding a new test case.
    LONG_DESC
    def case( case_name )
      total_tested = 0
      total_passed = 0
      self.all_test_sets.each do |test_set|
        test_set.case_paths.select {|case_path| File.basename(case_path)[/^case-(.*)@.*$/,1] == case_name }.each do |case_file|
          test_run = TidyTestCase.new(with_file: case_file, path_to_tidy: self.tidy_path)
          puts test_run.test_report unless test_run.test_passed && options[:omitpassed]
          total_tested += 1
          total_passed += 1 if test_run.test_passed
        end
      end
      self.print_report_footer( total_tested, total_passed )
      raise Thor::Error, "Automated Testing Failed."  if total_passed < total_tested
    end # case


    #########################################################
    # qo
    #  See long_desc
    #########################################################
    desc 'qo <case_name>', 'Quick-Opens the case file, the -expects, and -results files.'
    long_desc <<-LONG_DESC
      Quick-Opens the specific test case in your environment‘s default
      text editor, as well as the corresponding -expects file and -results
      files if present. Additionally, it will print the diff commands for your
      operating system pointing to the html files and the output files,
      respectively. This makes it easy to copy and paste if you would like
      to see a diff view.

      Use case: Use this command if a test case fails, and you want to view all of the
      relevant files in your text editor for comparison.
    LONG_DESC
    def qo( case_name )

      if WINDOWS_OS
        diff_cmd = 'fc -l'
        editor = TTY::Editor.new
      else
        diff_cmd = 'diff -ua'
        # This means of instantiation is temporary until
        # tty-editor is patched to trust the
        program = File.basename(ENV['EDITOR'])
        editor = TTY::Editor.new(command: program )
      end

      self.all_test_sets.each do |test_set|
        test_set.case_paths.select {|case_path| File.basename(case_path)[/^case-(.*)@.*$/,1] == case_name }.each do |case_file|
          # This will *not* run the tests and overwrite the files; that would only occur
          # if we try to pull a test report. This makes it simple to get our paths.
          test_run = TidyTestCase.new(with_file: case_file, path_to_tidy: self.tidy_path)
          editor.open("#{test_run.path_file}") if File.exist?(test_run.path_file)
          editor.open("#{test_run.path_config}") if File.exist?(test_run.path_config)
          editor.open("#{test_run.path_expects_html}") if File.exist?(test_run.path_expects_html)
          editor.open("#{test_run.path_expects_output}") if File.exist?(test_run.path_expects_output)
          editor.open("#{test_run.path_result_html}") if File.exist?(test_run.path_result_html)
          editor.open("#{test_run.path_result_output}") if File.exist?(test_run.path_result_output)

          puts <<~HEREDOC
          #{diff_cmd} #{test_run.path_expects_html} #{test_run.path_result_html}
          #{diff_cmd} #{test_run.path_expects_output} #{test_run.path_result_output}
          HEREDOC
        end
      end
    end # qo


    protected


    #########################################################
    # set_options
    #  Handles command line options.
    #########################################################
    def set_options
      SHARED_LOGGER.level = Logger::WARN if options[:verbose]
      SHARED_LOGGER.level = Logger::DEBUG if options[:debug]
      self.tidy_path = options[:tidy] ? File.expand_path(options[:tidy]) : EXE_TIDY
    end # set_options


    #########################################################
    # print_report_footer
    #########################################################
    def print_report_footer( total_tested, total_passed )
      tidy_version = %x( #{self.tidy_path} --version )
      tidy_version = tidy_version[/^.*(\d+\.\d+\.\d+).*/,1]
      cases_version = File.open(VERSION_FILE).first.chomp

      puts
      puts "Note that no valid cases were found." if total_tested < 1
      puts "Ran #{total_tested} tests, of which #{total_passed} passed and #{total_tested - total_passed} failed."
      puts "Test conducted with HTML Tidy #{tidy_version} using test sets for version #{cases_version}."
    end


    #########################################################
    # property tidy_path
    #########################################################
    def tidy_path
      @tidy_path
    end

    def tidy_path=( value )
      value += '.exe' if WINDOWS_OS && File.extname(value) != '.exe'
      unless File.exist?( value )
        raise StandardError.new "The path #{value} to tidy doesn’t exist."
      end
      @tidy_path = value
    end


    #########################################################
    # property all_test_sets
    #########################################################
    def all_test_sets
      unless @all_test_sets
        @all_test_sets = []
        Dir.glob("#{DIR_TEST_SETS}/*-cases").select { |entry| File.directory? entry }.sort.each do |test_set_directory|
          new_test_set = TidyTestSet.new(with_directory: test_set_directory, path_to_tidy: self.tidy_path)
          unless new_test_set.dir_test_set.nil?
            @all_test_sets.push(new_test_set)
          end
        end
      end
      @all_test_sets
    end

  end # TidyRegressionTestCLI

end # TidyRegressionTestModule


###########################################################
# Main
###########################################################

TidyRegressionTestModule::TidyRegressionTestCLI.start(ARGV)
