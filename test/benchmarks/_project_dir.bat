@echo off
setlocal

rem # ALL of the batch files in this directory will refer to this file to obtain
rem # the Tidy project directory so that relative paths in individual scripts can
rem # be avoided. Change only the relative paths in *this* script instead of all
rem # of the others.


rem #####################################
rem # Change these:
rem #####################################
set project_root=..\..\
set build_dir=build\cmake\
set test_dir=test\
set this_dir=test\benchmarks\


rem #####################################
rem # Don't change these:
rem #####################################

IF "%1"=="project" (
  set "ncd=%project_root%"
) ELSE IF "%1"=="build" (
  set "ncd=%project_root%%build_dir%"
) ELSE IF "%1"=="test" (
  set "ncd=%project_root%%test_dir%"
) ELSE IF "%1"=="this" (
  set "ncd=%project_root%%this_dir%"
) ELSE (
  echo Usage: %0 {project^|build^|test^|this}
  GOTO:EOF
)

pushd %ncd%
set result=%CD%
popd
echo %result%