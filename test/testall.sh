#! /bin/sh
#
# testall.sh - execute all testcases for regression testing
#
# (c) 1998-2015 (W3C) MIT, ERCIM, Keio University
# See tidy.c for the copyright notice.
#
# <URL:http://www.html-tidy.org/>
#
# set -x
BN=`basename $0`

d_now()
{
    date +%Y%m%d%H%M%S
}

# testone.sh uses tempall.txt, so
TMPLOG="tempall.txt"
# same EXE
TMPTIDY=../build/cmake/tidy

TMPNOW=`d_now`
TMPINP="testcases.txt"

if [ ! -f "testone.sh" ]; then
    echo "$BN: Can not locate testone.sh script!"
    exit 1
fi
if [ ! -f "$TMPINP" ]; then
    echo "$BN: Can not locate $TMPINP file!"
    exit 1
fi

# count the tests
TMPCNT=0
while read bugNo expected
do
    TMPCNT=`expr $TMPCNT + 1`
done < $TMPINP

# output a header
if [ -f "$TMPLOG" ]; then
	rm -f $TMPLOG
fi
echo "$BN: Will process $TMPCNT tests from $TMPINP on $TMPNOW"
echo "$BN: Will process $TMPCNT tests from $TMPINP on $TMPNOW" > $TMPLOG
echo "$BN: Tidy version in use..." >> $TMPLOG
$TMPTIDY -v >> $TMPLOG
if [ ! "$?" = "0" ]; then
    echo "$BN: Error $? running $TMPTIDY!"
    exit 1
fi

echo "========================================" >> $TMPLOG
# do the tests
while read bugNo expected
do
#  echo Testing $bugNo | tee -a $TMPLOG
  ./testone.sh $bugNo $expected | tee -a $TMPLOG
done < $TMPINP
echo "========================================" >> $TMPLOG

echo "$BN: Done $TMPCNT tests..." >> $TMPLOG
echo "# eof"
echo "$BN: Done $TMPCNT tests - see $TMPLOG"


# eof

