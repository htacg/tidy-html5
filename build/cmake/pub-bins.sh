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

# while read LINE; do
#    TMPVER="$LINE"
#done <$TMPFIL
#TMPVER=$(<$TMPFIL)
TMPVER=$(cat $TMPFIL)

echo "$BN: Version $TMPVER"

ask()
{
    pause
    if [ ! "$?" = "0" ]; then
        exit 1
    fi
}


TMPBIN="$HOME/projects/html_tidy/tidy-bin"
TMPBINS="$TMPBIN/binaries"
if [ ! -d "$TMPBINS" ]; then
    echo "$BN: Can NOT location '$TMPBINS'! *** FIX ME ***"
    exit 1
fi
TMPDD="$TMPBINS/tidy-$TMPVER"
if [ ! -d "$TMPDD" ]; then 
    echo ""
    echo "$BN: This is a NEW installation in $TMPDD"
fi

TMPFIL1="tidy5-$TMPVER-$TMPWV.deb"
TMPFIL2="tidy5-$TMPVER-$TMPWV.rpm"
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
