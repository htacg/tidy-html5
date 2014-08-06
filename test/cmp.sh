#!/bin/sh
#< cmp.sh - 20140805
# If you have the tidied HTML output from two version of 'tidy' then 
# this can COMPARE the files ONE BY ONE
#
BN=`basename $0`

TMPDIR1=$1
TMPDIR2=$2
OUTLOG="temp.diff"

usage()
{
	echo ""
	echo "Usage: ./$BN directory1 directory2"
	echo ""
	echo "$BN: If you have the tidied HTML output from two version of 'tidy' then "
	echo "$BN: this can COMPARE the html files ONE BY ONE, output to $OUTLOG"
	echo ""
}

if [ -z "$TMPDIR1" ] || [ -z "$TMPDIR2" ] || [ "$TMPDIR1" = "--help" ] || [ "$TMPDIR1" = "-h" ] || [ "$TMPDIR1" = "-?" ]; then
	usage
	exit 1
fi


if [ ! -d "$TMPDIR1" ]; then
	usage
	echo "$BN: Can NOT locate directory '$TMPDIR1'!"
	exit 1
fi

if [ ! -d "$TMPDIR2" ]; then
	usage
	exit 1
fi

shift
shift

TMPCNT1=0
TMPCNT2=0
SAMECNT=0
DIFFCNT=0

for fil in $TMPDIR1/*.html; do
	TMPCNT1=`expr $TMPCNT1 + 1`
done

for fil in $TMPDIR2/*.html; do
	TMPCNT2=`expr $TMPCNT2 + 1`
done

echo "$BN: Found $TMPCNT1 html files in $TMPDIR1"
echo "$BN: Found $TMPCNT2 html files in $TMPDIR2"

if [ -f "$OUTLOG" ]; then
	rm -f $OUTLOG
fi

echo "$BN: Found $TMPCNT1 html files in $TMPDIR1" >> $OUTLOG
echo "$BN: Found $TMPCNT2 html files in $TMPDIR2" >> $OUTLOG

for fil in $TMPDIR1/*.html; do
	bfil=`basename $fil`
	if [ -f "$TMPDIR2/$bfil" ]; then
		diff -uw $TMPDIR1/$bfil $TMPDIR2/$bfil >> $OUTLOG
		if [ "$?" = "0" ]; then
			echo "diff -uw $TMPDIR1/$bfil $TMPDIR2/$bfil are the SAME" >> $OUTLOG
			SAMECNT=`expr $SAMECNT + 1`
		else
			DIFFCNT=`expr $DIFFCNT + 1`
		fi
	else
		echo "$BN: File $bfil not found the 2" >> $OUTLOG
	fi
done
TOTCNT=`expr $SAMECNT + $DIFFCNT`
echo "$BN: Of the $TOTCNT compares made, $SAMECNT are the SAME, $DIFFCNT are DIFFERENT"
echo "$BN: Of the $TOTCNT compares made, $SAMECNT are the SAME, $DIFFCNT are DIFFERENT" >> $OUTLOG

echo "$BN: Results are in $OUTLOG"


# eof

