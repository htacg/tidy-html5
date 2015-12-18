#!/usr/bin/env ruby

###############################################################################
# Tidy Regression Test Suite
#  Look for the heredoc below, or run this script with help for more info.
#
#  test
#  test my_file.html
#  canonize
#  canonize my_file.html
#  --cases <directory>
#  --output <directory>
#
###############################################################################

require "thor"     # thor provides robust command line parameter parsing.

###########################################################
# Setup
###########################################################


###########################################################
# TidyRegressionCLI
#  This class provides handlers for CLI parameters.
###########################################################
class TidyRegressionCLI < Thor

  class_option :cases,
               :banner => '<directory>',
               :desc => 'Specifies the <directory> for canonical references.'
  class_option :output,
               :banner => '<directory>',
               :desc => 'Specifies the <directory> to report error output.'

  #####################################
  # test
  #  Tests a single file or all files.
  #####################################
  desc 'test [<file>]', 'Performs a regression test on <file>.'
  long_desc <<-LONG_DESC
    Will run a regression test for <file>. Use this command without <file>
    to run all of the regression tests. Output will be placed into the
    default directory unless an alternate is specified with --output.
  LONG_DESC
  def test(name = nil)

    if name == nil
      puts "All tests"
    else
      puts "Testing #{name}"
    end
  end # test


  #####################################
  # canonize
  #  Writes the -expects.
  #####################################
  option :replace,
         :type => :boolean,
         :desc => 'Indicates whether or not canonize replaces existing -expects.* files.'
  desc 'canonize [<file>]', 'Builds expected output for <file>.'
  long_desc <<-LONG_DESC
    Will build the canonical output for <file> and put it into the default
    directory. Use without <file> to generate canonical reference material for
    all files. Use with --replace to force replacement of existing -expects.*
    files.
  LONG_DESC
  def canonize(name = nil)

    if name == nil
      puts 'All files generated.'
    else
      puts "Generating #{name}"
    end

  end # canonize

end # TidyRegressionCLI


def hello( param )

  puts param

end # hello

###########################################################
# Main
###########################################################


# ARGV.each do |value|
#   hello( value )
# end

TidyRegressionCLI.start(ARGV)
