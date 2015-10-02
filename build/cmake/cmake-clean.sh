#!/bin/sh
#< cmake-clean.sh for tidy - remove tidylib...

FILES="libtidy*"
TMPCNT=0

for f in $FILES; do
    TMPCNT=`expr $TMPCNT + 1`
    echo "$TMPCNT: File $f"
done

echo "Will delete the above $TMPCNT files ater a 5 seconds sleep!"

sleep 5

echo "Deleting the above $TMPCNT files!"

for f in $FILES; do
    rm -fv $f
done

echo "all done..."

# eof

