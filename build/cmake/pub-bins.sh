#!/bin/sh
#< pub-bins.sh - copy binaries to repo for update
BN=`basename $0`
TMPWV="64bit"
TMPSRC="../.."
TMPFIL="$TMPSRC/version.txt"
if [ ! -f "$TMPFIL" ]; then
    echo "Can NOT locate $TMPFIL! *** FIX ME ***"
    exit 1
fi
echo "$BN: Read file $TMPFIL"
ls -l $TMPFIL

TMPCNT=0
while read LINE; do
    if [ "$TMPCNT" = "0" ]; then
        TMPVER="$LINE"
    fi
    TMPCNT=`expr $TMPCNT + 1`
done <$TMPFIL
#TMPVER=$(<$TMPFIL)
#TMPVER=$(cat $TMPFIL)

echo "$BN: Version $TMPVER"

ask()
{
    pause
    if [ ! "$?" = "0" ]; then
        exit 1
    fi
}


TMPBIN="$HOME/projects/html_tidy/binaries"
TMPBINS="$TMPBIN/binaries"
if [ ! -d "$TMPBINS" ]; then
    echo "$BN: Can NOT location '$TMPBINS'! *** FIX ME ***"
    exit 1
fi
TMPDD="$TMPBINS/tidy-$TMPVER"
    echo ""
if [ -d "$TMPDD" ]; then 
    echo "$BN: Destination is $TMPDD"
else
    echo "$BN: This is a NEW installation in $TMPDD"
fi

TMPFIL1="tidy-$TMPVER-$TMPWV.deb"
TMPFIL2="tidy-$TMPVER-$TMPWV.rpm"
if [ ! -f "$TMPFIL1" ]; then
    echo "$BN: $TMPFIL1 does not exits"
    echo "$BN: Have you run '[sudo] make package'?"
    exit 1
fi
if [ ! -f "$TMPFIL2" ]; then
    echo "$BN: $TMPFIL2 does not exits"
    echo "$BN: Have you run '[sudo] make package'?"
    exit 1
fi
echo ""
echo "$BN: Will publish..."
echo "$TMPFIL1"
echo "$TMPFIL2"
if [ ! -d "$TMPDD" ]; then 
    echo "$BN: Will create dir $TMPDD"
else
    echo "$BN: Destination $TMPDD"
fi
echo ""
echo "$BN: *** CONTINUE? ***"
ask

if [ ! -d "$TMPDD" ]; then 
    mkdir $TMPDD
    if [ ! -d "$TMPDD" ]; then 
        echo "$BN: Failed to create folder $TMPDD"
        exit 1
    fi
fi

TMPSRC="$TMPFIL1"
TMPDST="$TMPDD/$TMPFIL1"
echo "$BN: Copying $TMPSRC to $TMPDST"
cp -u -v $TMPSRC $TMPDST
if [ ! -f "$TMPDST" ]; then
    echo "$BN: Copy $TMPSRC FAILED!"
    exit 1
fi
TMPSRC="$TMPFIL2"
TMPDST="$TMPDD/$TMPFIL2"
echo "$BN: Copying $TMPSRC to $TMPDST"
cp -u -v $TMPSRC $TMPDST
if [ ! -f "$TMPDST" ]; then
    echo "$BN: Copy $TMPSRC FAILED!"
    exit 1
fi

# @REM eof
