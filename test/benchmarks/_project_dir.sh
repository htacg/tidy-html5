#!/usr/bin/env sh

# ALL of the shell scripts in this directory will refer to this file to obtain
# the Tidy project directory so that relative paths in individual scripts can
# be avoided. Change only the relative paths in *this* script instead of all
# of the others.

#####################################
# Change these:
#####################################
project_root="../../"             # Relative path from this script to project root.
build_dir="build/cmake/"          # Relative path from project_root.
test_dir="test/"                  # Relative path from project_root.
this_dir="test/benchmarks/"       # Relative path from project_root.


#####################################
# Don't change these:
#####################################

case $1 in

  project)
    cd "${project_root}"
    ;;
  build)
    cd "${project_root}${build_dir}"
    ;;
  test)
    cd "${project_root}${test_dir}"
    ;;
  this)
    cd "${project_root}${this_dir}"
    ;;
  *)
    echo "Usage: $0 {project|build|test|this}"
    exit 1
    ;;
esac

echo `pwd`
