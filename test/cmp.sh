#!/bin/sh
#< cmp.sh - 20140805
# If you have the tidied HTML output from two version of 'tidy' then 
# this can COMPARE the files ONE BY ONE
#
BN=`basename $0`

TMPDIR1=$1
TMPDIR2=$2
OUTLOG="temp.diff"
TMPDOP="-ua"

usage()
{
	echo ""
	echo "Usage: ./$BN directory1 directory2"
	echo ""
	echo "$BN: If you have the tidied HTML output from two version of 'tidy' then "
	echo "$BN: this can COMPARE the output files ONE BY ONE, output to $OUTLOG"
	echo ""
}

d_now()
{
    date +%Y%m%d%H%M%S
}

if [ -z "$TMPDIR1" ] || [ -z "$TMPDIR2" ] || [ "$TMPDIR1" = "--help" ] || [ "$TMPDIR1" = "-h" ] || [ "$TMPDIR1" = "-?" ]; then
	usage
	exit 1
fi


if [ ! -d "$TMPDIR1" ]; then
	usage
	echo "$BN: Can NOT locate directory 1 '$TMPDIR1'!"
	exit 1
fi

if [ ! -d "$TMPDIR2" ]; then
	usage
	echo "$BN: Can NOT locate directory 2 '$TMPDIR2'!"
	exit 1
fi

shift
shift

TMPCNT1=0
TMPCNT2=0
SAMECNT=0
DIFFCNT=0
DIFFFILES=""

# 20150917 - Maybe should be ALL, not just html
TMPMASK="*"
# TMPMASK="*.html"

for fil in $TMPDIR1/$TMPMASK; do
	TMPCNT1=`expr $TMPCNT1 + 1`
done

for fil in $TMPDIR2/$TMPMASK; do
	TMPCNT2=`expr $TMPCNT2 + 1`
done

echo "$BN: Found $TMPCNT1 files in $TMPDIR1"
echo "$BN: Found $TMPCNT2 files in $TMPDIR2"

if [ -f "$OUTLOG" ]; then
	rm -f $OUTLOG
fi

TMPNOW=`d_now`
echo "$BN: Compare of '$TMPDIR1' and '$TMPDIR2' on $TMPNOW" >> $OUTLOG
echo "$BN: Found $TMPCNT1 files in $TMPDIR1" >> $OUTLOG
echo "$BN: Found $TMPCNT2 files in $TMPDIR2" >> $OUTLOG

for fil in $TMPDIR1/$TMPMASK; do
	bfil=`basename $fil`
	if [ -f "$TMPDIR2/$bfil" ]; then
		diff $TMPDOP $TMPDIR1/$bfil $TMPDIR2/$bfil >> $OUTLOG
		if [ "$?" = "0" ]; then
			echo "diff $TMPDOP $TMPDIR1/$bfil $TMPDIR2/$bfil are the SAME" >> $OUTLOG
			SAMECNT=`expr $SAMECNT + 1`
		else
			echo "diff $TMPDOP $TMPDIR1/$bfil $TMPDIR2/$bfil are DIFFERENT! *** CHECK DIFFERENCE ***" >> $OUTLOG
			DIFFCNT=`expr $DIFFCNT + 1`
			DIFFFILES="$DIFFFILES $bfil"
		fi
	else
		echo "$BN: File $bfil not found in dir 2 $TMPDIR2" >> $OUTLOG
	fi
done
TOTCNT=`expr $SAMECNT + $DIFFCNT`
echo "" >> $OUTLOG
echo "$BN: Of the $TOTCNT compares made, $SAMECNT are the SAME, $DIFFCNT are DIFFERENT"
echo "$BN: Of the $TOTCNT compares made, $SAMECNT are the SAME, $DIFFCNT are DIFFERENT" >> $OUTLOG
if [ ! "$DIFFCNT" = "0" ]; then
    echo "$BN: VERIFY $DIFFCNT $DIFFFILES"
    echo "$BN: VERIFY $DIFFCNT $DIFFFILES" >> $OUTLOG
fi
echo "" >> $OUTLOG

echo "$BN: Full results are in $OUTLOG"
echo ""

# eof

