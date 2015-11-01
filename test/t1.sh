#!/bin/sh
BN=`basename $0`
# @setlocal
#@REM =================================================================
#@REM A convenient run one test giving the number and expected exit
#@REM
#@REM This is to run just one, like "t1 1642186-1 0"
#@REM
#@REM Note it uses a relative path to the built exe file, and
#@REM expects the ouput folder has to exist.
#@REM
#@REM Obviously you may want to adjust this file, like seen below to test
#@REM different versions of tidy.exe...
#@REM Rather than altering this file, which will be flagged by git,
#@REM I copy it to say a temp1.bat, and modify that to suit my testing
#@REM
#@REM There is also an 'alltest.cmd' which runs some 227 tests that 
#@REM gets the case listed in 'testcases.txt' file.
#@REM
#@REM =================================================================

#@REM setup the ENVIRONMENT
TIDY="../build/cmake/tidy"
TIDYOUT="tmp"
TMPLOG="temptest1.txt"

if [ ! -d "$TIDYOUT" ]; then
    echo ""
    echo "$BN: Error: Can NOT locate $TIDYOUT! This MUST be created!"
    echo "$BN: This script does NOT create any directories..."
    echo ""
    exit 1
fi

if [ ! -x "$TIDY" ]; then
    echo ""
    echo "$BN: Error: Unable to locate file '$TIDY'! Has it been built? *** FIX ME ***"
    echo ""
    exit 1
fi

give_help()
{
    echo ""
    echo "- Usage: $0 \"value\" \"expected exit value\""
    echo "- That is give test number, and expected result, like"
    echo "$0 1642186 1"
    echo "- Missing expected value. See testcases.txt for list available..."
    echo ""
}
d_now()
{
    date +%Y%m%d%H%M%S
}

#@REM Check user input
TMPCASE="$1"
TMPEXIT="$2"
TMPNOW=`d_now`

if [ -z "$TMPCASE" ]; then
    give_help
    exit 1
fi    
if [ -z "$TMPEXIT" ]; then
    give_help
    exit 1
fi

TMPFIL="input/in_$TMPCASE.xhtml"
if [ ! -f "$TMPFIL" ]; then
TMPFIL="input/in_$TMPCASE.html"
fi
TMPCFG="input/cfg_$TMPCASE.txt"
if [ ! -f "$TMPCFG" ]; then
TMPCFG="input/cfg_default.txt"
fi

if [ ! -f "$TMPFIL" ]; then
    echo ""
    # @dir input/*%1*
    # @echo.
    echo "$BN: Error: Can NOT locate $TMPFIL! Is number correct? "
    echo ""
    exit 1
fi
 
if [ ! -f "$TMPCFG" ]; then
    echo ""
    echo "$BN: Error: Can NOT locate $TMPCFG!"
    echo ""
    exit 1
fi
if [ -f "$TMPLOG" ]; then
    rm -f $TMPLOG
fi
echo "$BN: Test 1 case $TMPCASE $TMPEXIT on $TMPNOW" > $TMPLOG
echo "$BN: Version of tidy in use..." >> $TMPLOG
./$TIDY -v >> $TMPLOG
if [ ! "$?" = "0" ]; then
    echo ""
    echo "$BN: Error: Unable to run '$TIDY -v' successfully! *** FIX ME ***"
    echo ""
    exit 1
fi

echo ""
echo "$BN: Doing './testone.sh $TMPCASE $TMPEXIT'"
echo "$BN: Doing './testone.sh $TMPCASE $TMPEXIT'" >> $TMPLOG
echo "$BN: testone.sh run '$TIDY ... -config $TMPCFG $TMPFIL'" >> $TMPLOG

if [ -f "tempall.txt" ]; then
    rm -f tempall.txt
fi

./testone.sh $TMPCASE $TMPEXIT
if [ -f "tempall.txt" ]; then
    echo "==========================" >> $TMPLOG
    cat tempall.txt >> $TMPLOG
    echo "==========================" >> $TMPLOG
else
    echo "Why no tempall.txt created???" >> $TMPLOG    
fi

echo "$BN: See ouput in $TMPLOG"
echo "$BN: Checking for compare phase..." >> $TMPLOG

TMPFIL1="testbase/out_$TMPCASE.html"
TMPOUT1="testbase/msg_$TMPCASE.txt"
TMPFIL2="$TIDYOUT/out_$TMPCASE.html"
TMPOUT2="$TIDYOUT/msg_$TMPCASE.txt"

if [ ! -f "$TMPFIL1" ]; then
    echo ""
    echo "$BN: NOT locate $TMPFIL1 "
    echo "$BN: needed for the compare... but this may not be a problem..."
    echo "$BN: Maybe there is no 'testbase' file for test $TMPCASE!"
    echo ""
    exit 1
fi
if [ ! -f "$TMPFIL2" ]; then
    echo ""
    echo "$BN: NOT locate $TMPFIL2 "
    echo "$BN: needed for the compare... but this may not be a problem..."
    echo "$BN: Maybe there is no 'testbase' file for test $TMPCASE!"
    echo ""
    exit 1
fi

no_file2()
{
    echo ""
    echo "$BN: Can NOT locate  $TMPOUT1 or $TMPOUT2"
    echo "$BN: needed for the compare... but this may not be a problem..."
    echo "$BN: but it is strange one or both were not created!!! *** NEEDS CHECKING ***"
    echo ""
}

if [ ! -f "$TMPOUT1" ]; then
    no_file2
    exit 1
fi
if [ ! -f "$TMPOUT2" ]; then
    no_file2
    exit 1
fi

is_diff()
{
    echo ""
    echo "$BN: Check the above diff carefully. This may indicate a 'testbase', or"
    echo "$BN: a 'regression' in tidy output."
    echo ""
}


#@REM Compare the outputs, exactly
TMPOPTS="-ua"
ERRCNT=0

echo ""
echo "$BN: Doing: 'diff $TMPOPTS $TMPFIL1 $TMPFIL2'"
echo "$BN: Doing: 'diff $TMPOPTS $TMPFIL1 $TMPFIL2'" >> $TMPLOG
diff $TMPOPTS $TMPFIL1 $TMPFIL2
if [ "$?" = "0" ]; then
    echo "Files appear exactly the same..."
else
    is_diff
    ERRCNT=`expr $ERRCNT + 1`
fi

echo ""
echo "$BN: Doing: 'diff $TMPOPTS $TMPOUT1 $TMPOUT2'"
echo "$BN: Doing: 'diff $TMPOPTS $TMPOUT1 $TMPOUT2'" >> $TMPLOG
diff $TMPOPTS $TMPOUT1 $TMPOUT2
if [ "$?" = "0" ]; then
    echo "$BN: Files appear exactly the same..."
else
    is_diff
    ERRCNT=`expr $ERRCNT + 1`
fi

echo ""
if [ "$ERRCNT" = "0" ]; then
    echo "$BN: Appears a successful test of $TMPCASE $TMPEXIT"
    echo "$BN: Appears a successful test of $TMPCASE $TMPEXIT" >> $TMPLOG
else
    echo "$BN: Carefully REVIEW the above differences on $TMPCASE $TMPEXIT! *** ACTION REQUIRED ***"
    echo "$BN: Carefully REVIEW the above differences on $TMPCASE $TMPEXIT! *** ACTION REQUIRED ***" >> $TMPLOG
fi
echo ""
echo "# eof" >> $TMPLOG
echo "$BN: See full ouput in $TMPLOG"

# eof :END

