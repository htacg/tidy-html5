#!/bin/sh
#< gen-html.sh 2021/03/26, from gen-html.bat
BN=`basename $0`

ask()
{
	pause
	if [ ! "$?" = "0" ]; then
		exit 1
	fi
}

# @REM Build HTML from log of 'version.txt'
# @REM Versify the tools used
echo "$BN: Doing: 'verhist.pl -? >/dev/null'"
verhist.pl -? >/dev/null
if [ ! "$?" = "0" ]; then
    echo "Unable to run 'verhist.pl'! *** FIX ME ***"
    exit 1
fi
echo "$BN: Doing: 'emailobfuscate.pl -? >/dev/null'"
emailobfuscate.pl -? >/dev/null
if [ ! "$?" = "0" ]; then
    echo "Unable to run 'emailobfuscate.pl'! *** FIX ME ***"
    exit 1
fi

TMPFIL1="../../version.txt"
if [ ! -f "$TMPFIL1" ]; then
    echo "Can NOT locate $TMPFIL1, in $(pwd) - *** FIX ME ***"
    exit 1
fi

echo "$BN: Doing: 'dirmin $TMPFIL1'"
ls -l "$TMPFIL1"

# TMPVER=$(cat $TMPFIL1)
TMPCNT=0
while read -r a; do
	TMPCNT=`expr $TMPCNT + 1`;
	if [ ! -z "$a" ]; then
		echo "$TMPCNT: '$a'"
		if [ "$TMPCNT" = "1" ]; then
			export TMPVER="$a";
		fi
		break;
	fi
done < $TMPFIL1

echo "Current version '$TMPVER' ..."
TMPLOG1="../../../temp-$TMPVER.log"
TMPLOG2="../../../temp2-$TMPVER.log"
TMPLOG3="../../../temp3-$TMPVER.log"

if [ ! -f "$TMPLOG1" ]; then
echo "$BN: Doing: 'git log -p $TMPFIL1 > $TMPLOG1'"
git log -p $TMPFIL1 > $TMPLOG1
if [ ! -f "$TMPLOG1" ]; then
echo "Gen of $TMPLOG1 FAILED! *** FIX ME ***"
exit 1
fi
fi

echo "$BN: Got log 1 '$TMPLOG1' ..."
ls -l "$TMPLOG1"

if [ ! -f "$TMPLOG2" ]; then
echo "$BN: Doing: 'verhist.pl $TMPLOG1 -o $TMPLOG2'"
verhist.pl $TMPLOG1 -o $TMPLOG2
if [ ! -f "$TMPLOG2" ]; then
echo "Gen of $TMPLOG2 FAILED! *** FIX ME ***"
exit 1
fi
fi

echo "$BN: Got log 2 '$TMPLOG2' ..."
ls -l $TMPLOG2

TMPV="$1"
if [ -z "$TMPV" ]; then
echo "Give the cut-off version, like 5.6.0, to continue.."
exit 1
fi

echo "$BN: Doing: 'grep $TMPV $TMPLOG2'"
grep $TMPV $TMPLOG2
if [ ! "$?" = "0" ]; then
echo "Failed to find '$TMPV'... check the file '$TMPLOG2'"
exit 1
fi

TMPD="$2"
if [ -z "$TMPD" ]; then
echo "Give the DATE of the cut-off, like 'Sat Nov 25 14:50:00 2017 +0100', to continue..."
exit 1
fi

if [ ! -f "$TMPLOG3" ]; then
echo "$BN: Doing: 'git log "--decorate=full" "--since=$TMPD" > $TMPLOG3'"
git log "--decorate=full" "--since=$TMPD" > $TMPLOG3
if [ ! -f "$TMPLOG3" ]; then
echo "Failed to generate 'git log ...' - *** FIX ME ***"
exit 1
fi
fi

echo "$BN: Got log 3 '$TMPLOG3' ..."
ls -l "$TMPLOG3"

# @REM at last generate the release HTML

TMPHTM="../../../temp-$TMPVER.html"
if [ ! -f "$TMPHTM" ]; then
echo "$BN: Doing: 'emailobfuscate.pl $TMPLOG3 -o $TMPHTM -a $TMPVER -i'"
emailobfuscate.pl $TMPLOG3 -o $TMPHTM -a $TMPVER -i
if [ ! -f "$TMPHTM" ]; then
echo "FAILED to generate $TMPHTM! *** FIX ME ***"
exit 1
fi
fi

echo "$BN: Got HTML file '$TMPHTM' ..."
ls -l "$TMPHTM"

echo "$BN: Generation appears ok, check file '$TMPHTM' in browser..."
### start $TMPHTM
TMPVFIL="../../README/verhist.log"
if [ ! -f "$TMPVFIL" ]; then
    echo ""
    echo "$BN: *** WARNING *** - Missing existing '$TMPVFIL'"
    echo ""
fi
echo ""
echo "$BN: Is all OK, final actions, for release are -"
echo "copy $TMPLOG2 to $TMPVFIL - push this to repo..."
echo "copy $TMPHTM to the binaries repo..."
echo ""

# @REM eof
