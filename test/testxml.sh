#! /bin/sh

#
# testxml.sh - execute all XML testcases
#
# (c) 1998-2005 (W3C) MIT, ERCIM, Keio University
# See tidy.c for the copyright notice.
#
# <URL:http://tidy.sourceforge.net/>
#
# CVS Info:
#
#    $Author: arnaud02 $
#    $Date: 2005/03/08 12:08:00 $
#    $Revision: 1.5 $
#
# set -x

VERSION='$Id'

BUGS="427837 431956 433604 433607 433670 434100\
 480406 480701 500236 503436 537604 616744 640474 646946"

while read bugNo expected
do
#  echo Testing $bugNo | tee -a testxml.log
  ./testone.sh "$bugNo" "$expected" "$@" | tee -a testxml.log
  if test -f "./tmp/out_$bugNo.html"
  then
    mv "./tmp/out_$bugNo.html" "./tmp/out_$bugNo.xml"
  fi
done < xmlcases.txt

