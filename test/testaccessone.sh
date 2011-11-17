#! /bin/sh

#
# execute a single testcase
#
# (c) 2005 (W3C) MIT, ERCIM, Keio University
# See tidy.c for the copyright notice.
#
# <URL:http://tidy.sourceforge.net/>
#
# CVS Info:
#
#    $Author: arnaud02 $
#    $Date: 2007/02/04 17:35:31 $
#    $Revision: 1.2 $
#
# set -x

VERSION='$Id'

echo Testing $1

set +f

TESTNO=$1
TESTEXPECTED=$2
ACCESSLEVEL=$3

TIDY=../bin/tidy
INFILES=./accessTest/$1.*ml
CFGFILE=./accessTest/cfg_$1.txt

TIDYFILE=./tmp/out_$1.html
MSGFILE=./tmp/msg_$1.txt

unset HTML_TIDY

shift
shift
shift

# Remove any pre-exising test outputs
for INFIL in $MSGFILE $TIDYFILE
do
  if [ -f $INFIL ]
  then
    rm $INFIL
  fi
done

for INFILE in $INFILES
do
    if [ -r $INFILE ]
    then
      break
    fi
done

# If no test specific config file, use default.
if [ ! -f $CFGFILE ]
then
  CFGFILE=./accessTest/cfg_default.txt
fi

# Make sure output directory exists.
if [ ! -d ./tmp ]
then
  mkdir ./tmp
fi

$TIDY -f $MSGFILE --accessibility-check $ACCESSLEVEL -config $CFGFILE "$@" --gnu-emacs yes --tidy-mark no -o $TIDYFILE $INFILE
STATUS=$?

if [ `grep -c -e ' \['$TESTEXPECTED'\]: ' $MSGFILE` = 0 ]
then
  echo "--- test '$TESTEXPECTED' not detected in file '$INFILE'"
  cat $MSGFILE
  exit 1
fi

exit 0

