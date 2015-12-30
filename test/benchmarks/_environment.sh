#!/usr/bin/env sh

# Setup a common environment for all shell scripts to use. This will ensure
# portability for all of the test scripts without having to figure out which
# items to always edit.

#############################################################################
# Change these:
#  project_root is the relative path from this script to the project root.
#  All other paths are relative to project_root.
#############################################################################

# Specify the relative path from this script to the top-level tidy-html directory.
project_root="../../"                  # Project root; everything else descends from here.

# These are *all* relative from the project_root directory.
build_dir="build/cmake/"               # Cmake's build output location.
test_dir="test/"                       # Location of the `test` directory.
cases_dir="test/benchmarks/"           # Top-level of where all of the `cases-` exist.
results_dir="test/benchmarks/results/" # Where to place results. This must exist.

# This can be a relative path from project_root or absolute starting with '/'.
tidy_path="build/cmake/tidy"           # Where is tidy?

# This is relative to the results_dir specified above. Just a filename.
results_filename="results.txt"         # What test report filename to use.


#############################################################################
# Don't change these:
#############################################################################

case $1 in

  # Support this in case sourced from the command line.
  unset)
    unset TY_PROJECT_ROOT
    unset TY_BUILD_DIR
    unset TY_TEST_DIR
    unset TY_CASES_DIR
    unset TY_RESULTS_DIR
    unset TY_TIDY_PATH
    unset TY_RESULTS_PATH
    exit 0
    ;;
  *)
    cwd=`pwd`
    cd "${project_root}"
    project_root="`pwd`/"
    cd "${cwd}"
    export TY_PROJECT_ROOT="${project_root}"
    export TY_BUILD_DIR="${project_root}${build_dir}"
    export TY_TEST_DIR="${project_root}${test_dir}"
    export TY_CASES_DIR="${project_root}${cases_dir}"
    export TY_RESULTS_DIR="${project_root}${results_dir}"
    export TY_RESULTS_PATH="${project_root}${results_dir}${results_filename}"
    case "${tidy_path}" in
      /*)
        export TY_TIDY_PATH="${tidy_path}"
        ;;
      *)
        export TY_TIDY_PATH="${project_root}${tidy_path}"
        ;;
    esac
    ;;
esac
