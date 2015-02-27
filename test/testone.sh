#! /bin/sh

#
# testone.sh - execute a single testcase
#
# (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
# See tidy.c for the copyright notice.
#
# <URL:http://www.html-tidy.org/>
#
# set -x
BN=`basename $0`
VERSION='$Id'

echo Testing $1

set +f

TESTNO=$1
EXPECTED=$2
#TIDY=../bin/tidy
TIDY=../build/cmake/tidy5
if [ ! -f "$TIDY" ]; then
	echo "$BN: Can NOT locate binary '$TIDY'!"
	echo "$BN: Fix me with the correct location of the binary to run."
	exit 1
fi
INFILES=./input/in_${TESTNO}.*ml
CFGFILE=./input/cfg_${TESTNO}.txt

TIDYFILE=./tmp/out_${TESTNO}.html
MSGFILE=./tmp/msg_${TESTNO}.txt

unset HTML_TIDY

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
  CFGFILE=./input/cfg_default.txt
fi

# Make sure output directory exists.
if [ ! -d ./tmp ]
then
  mkdir ./tmp
fi

echo "Doing: './$TIDY -f $MSGFILE -config $CFGFILE "$@" --tidy-mark no -o $TIDYFILE $INFILE'" >> tempall.txt
./$TIDY -f $MSGFILE -config $CFGFILE "$@" --tidy-mark no -o $TIDYFILE $INFILE
STATUS=$?

if [ $STATUS -ne $EXPECTED ]
then
  echo "== $TESTNO failed (Status received: $STATUS vs expected: $EXPECTED)" 
  cat $MSGFILE
  echo "== $TESTNO failed (Status received: $STATUS vs expected: $EXPECTED)" >> tempall.txt
  cat $MSGFILE >> tempall.txt
  exit 1
fi

exit 0

