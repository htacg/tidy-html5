#!/bin/sh
#< rentidy.sh - 20160201
BN=`basename $0`

ask()
{
    pause
    if [ ! "$?" = "0" ]; then
        exit 1
    fi
}

TMPEXE="/usr/bin/tidy"
if [ ! -f "$TMPEXE" ]; then
    echo "$BN: Can not locate '$TMPEXE'"
    exit 1
fi
# tidy -v
$TMPEXE -v
if [ ! "$?" = "0" ]; then
    echo "$BN: Can not run $TMPEXE!"
    exit 1
fi
TMPVER=`$TMPEXE -v | awk '{ print $6 }'`
# echo "$BN: Version $TMPVER"
TMPFIL2="$TMPEXE-$TMPVER"
if [ -f "$TMPFIL2" ]; then
    echo "$BN: New name already exists!"
    exit 1
fi
echo "$BN: Rename $TMPEXE to $TMPFIL2?"

ask

sudo mv $TMPEXE $TMPFIL2


# eof

