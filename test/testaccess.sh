#! /bin/sh

#
# testaccess.sh - execute all testcases for regression testing
#
# (c) 2005 (W3C) MIT, ERCIM, Keio University
# See tidy.c for the copyright notice.
#
# <URL:http://tidy.sourceforge.net/>
#
# set -x

VERSION='$Id'

cat accesscases.txt | sed 1d | \
{
while read bugNo expected
do
  ./testaccessone.sh $bugNo $expected "$@" | tee -a testaccess.log
done
}
