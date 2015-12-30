@echo off

rem # Setup a common environment for all batch scripts to use. This will ensure
rem # portability for all of the test scripts without having to figure out which
rem # items to always edit.

rem ###########################################################################
rem # Change these:
rem #  project_root is the relative path from this script to the project root.
rem #  All other paths are relative to project_root.
rem ###########################################################################

rem # Project root; everything else descends from here. Must be relative to this script.
set TY_PROJECT_ROOT=..\..\

rem # Cmake's build output location. Relative to project_root.
set TY_BUILD_DIR=build\cmake\

rem # Location of the `test` directory. Relative to project_root.
set TY_TEST_DIR=test\

rem # Top-level of where all of the `cases-` exist. Relative to project_root.
set TY_CASES_DIR=test\benchmarks\
 
rem # Where to place results. This must exist. Relative to project_root.
set TY_RESULTS_DIR=test\benchmarks\results\

rem # This can be a relative path from project_root or absolute starting with 'X:\'.
set TY_TIDY_PATH=build\cmake\tidy.exe

rem # This is relative to the results_dir specified above. Just a filename.
set TY_RESULTS_PATH=results.txt


rem ###########################################################################
rem # Don't change these:
rem ###########################################################################

pushd %TY_PROJECT_ROOT%
set TY_PROJECT_ROOT=%CD%\
popd
set TY_BUILD_DIR=%TY_PROJECT_ROOT%%TY_BUILD_DIR%
set TY_TEST_DIR=%TY_PROJECT_ROOT%%TY_TEST_DIR%
set TY_CASES_DIR=%TY_PROJECT_ROOT%%TY_CASES_DIR%
set TY_RESULTS_DIR=%TY_PROJECT_ROOT%%TY_RESULTS_DIR%
set TY_RESULTS_PATH=%TY_PROJECT_ROOT%%TY_RESULTS_DIR%%TY_RESULTS_PATH%

IF "%TY_TIDY_PATH:~1,2%"==":\" (
  set TY_TIDY_PATH=%TY_TIDY_PATH%
) ELSE (
  set TY_TIDY_PATH=%TY_PROJECT_ROOT%%TY_TIDY_PATH%
)
