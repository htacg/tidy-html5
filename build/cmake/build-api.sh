#!/bin/sh
#< build-api.sh - 20151020 - build the API documentation for publishing...
BN=`basename $0`
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
TMPZIP="tidylib_api-$TMPVER.zip"

ask()
{
    pause
    if [ ! "$?" = "0" ]; then
        exit 1
    fi
}

TMPDIR="../../documentation/temp"
TMPZFIL="../../documentation/$TMPZIP"

if [ -f "$TMPZFIL" ]; then
    ls -l $TMPZFIL
    echo "$BN: WARNING: Current ZIP will be overwritten!"
    echo "$BN: DO you want to coninue?"
    ask
fi

TMPFIL="build-me.sh"
if [ ! -x "$TMPFIL" ]; then
    echo "$BN: Can NOT locate '$TMPFIL'! *** FIX ME ***"
    echo "$BN: This is a simple build script, that accepts parameters..."
    exit 1
fi

if [ -d "$TMPDIR" ]; then
    echo "$BN: Directory '$TMPDIR' will be deleted prior the documentaion build..."
fi

./$TMPFIL -DBUILD_DOCUMENTATION:BOOL=YES
if [ ! "$?" = "0" ]; then
    echo "$BN: The running of $TMPFIL failed! ????"
    exit 1
fi

if [ -d "$TMPDIR" ]; then
    echo "$BN: Deleting '$TMPDIR'..."
    cd $TMPDIR
    rm -rf *
    cd -
fi

echo "$BN: Doing 'make documentation'..."
make documentation

if [ -d "$TMPDIR" ]; then
    echo "$BN: Generated a new '$TMPDIR'..."
    if [ -f "$TMPZFIL" ]; then
        rm -fv $TMPZFIL
    fi
    cd $TMPDIR
    echo "$BN: Generating ../$TMPZIP..."
    zip -r ../$TMPZIP * >/dev/null
    ls -l ../$TMPZIP
    cd -
else
    echo "$BN: WARNING '$TMPDIR' not generated!"
    exit 1
fi

exit 0

# eof

