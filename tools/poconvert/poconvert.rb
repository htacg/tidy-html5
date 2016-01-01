#!/usr/bin/env ruby

###############################################################################
# poconvert.rb
#  Run this script with `help` for more information (or examine this file.)
#
#  Commands:
#    file.po
#    file.h
###############################################################################

require 'bundler/setup'  # Provides environment for this script.
require 'logger'         # Log output simplified.
require 'fileutils'      # File utilities.
require 'date'           # Make sure DateTime works.
require 'fileutils'      # compare_file, etc.
require 'thor'           # thor provides robust command line parameter parsing.


################################################################################
# module PoConvertModule
#  This module encapsulates module-level variables, utilities, logging,
#  the CLI handling class, and the po<->h conversion class.
###############################################################################
module PoConvertModule

  ###########################################################
  # Setup
  ###########################################################
  @@module_var = 'sample'


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
      @source_file = nil
      @dest_file = nil
    end


    #########################################################
    # property something
    #########################################################
    def something

    end

    def something=( value )

    end


  end # class PoConverter


  #############################################################################
  # class PoConvertCLI
  #  This class provides handlers for CLI parameters.
  #############################################################################
  class PoConvertCLI < Thor

    include PoConvertModule

    default_task :convert

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
      @converter = PoConverter.new
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

This script (#{File.basename($0)}) is a Tidy regression testing script that will
comprehensively execute every test in the suite. It also has the ability to
generate new benchmark files into the suite.

Complete Help:
--------------
        HEREDOC
      end

      super
    end

    #########################################################
    # convert
    #  Converts a po file to h, or h file to po.
    #########################################################
    desc 'convert <file> [options]', 'Converts a *.po file to *.h, or *.h file to *.po.'
    long_desc <<-LONG_DESC
      Will run a regression test for <file> or <case_name>. Use this command without
      <file> or <case_name> to run all of the regression tests. Output will be placed
      into the default directory unless an alternate is specified with --output.
      <case_name> indicates the filename portion between "case-" and the file extension.
    LONG_DESC
    def rtest(name = nil)

      set_options

      if name.nil?
        puts 'No name!'
      else
        puts 'Good, a name!'
      end

    end # rtest


    #########################################################
    # method_missing
    #  Use ::convert as our default command, avoiding the
    #  command altogether.
    #########################################################
    def method_missing(method, *args)
      args = ['convert', method.to_s] + args
      PoConvertCLI.start(args)
    end


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
