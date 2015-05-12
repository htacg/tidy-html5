#!/bin/sh
#< build-me.sh - 20150212 - 20140804
BN=`basename $0`

TMPSRC="../.."
BLDLOG="bldlog-1.txt"

wait_for_input()
{
    if [ "$#" -gt "0" ] ; then
        echo "$1"
    fi
    echo -n "Enter y to continue : "
    read char
    if [ "$char" = "y" -o "$char" = "Y" ]
    then
        echo "Got $char ... continuing ..."
    else
        if [ "$char" = "" ] ; then
            echo "Aborting ... no input!"
        else
            echo "Aborting ... got $char!"
        fi
        exit 1
    fi
    # exit 0
}

if [ -f "$BLDLOG" ]; then
	rm -f $BLDLOG
fi

BLDDBG=0
TMPOPTS=""
##############################################
### ***** NOTE THIS INSTALL LOCATION ***** ###
### Change to suit your taste, environment ###
TMPINST="/usr"
TMPOPTS="$TMPOPTS -DCMAKE_INSTALL_PREFIX=$TMPINST"
##############################################

### Accept user argument
for arg in $@; do
      case $arg in
         VERBOSE) TMPOPTS="$TMPOPTS -DCMAKE_VERBOSE_MAKEFILE=ON" ;;
         DEBUG) BLDDBG=1 ;;
         SHARED) TMPOPTS="$TMPOPTS -DBUILD_SHARED_LIB:BOOL=TRUE" ;;
         *) TMPOPTS="$TMPOPTS $arg" ;;
      esac
done

if [ "$BLDDBG" = "1" ]; then
    TMPOPTS="$TMPOPTS -DCMAKE_BUILD_TYPE=Debug -DENABLE_DEBUG_SYMBOLS:BOOL=TRUE"
else
    TMPOPTS="$TMPOPTS -DCMAKE_BUILD_TYPE=Release"
fi

echo "$BN: Will do: 'cmake $TMPSRC $TMPOPTS' to $BLDLOG"
wait_for_input

echo "$BN: Doing: 'cmake $TMPSRC $TMPOPTS' to $BLDLOG"
cmake $TMPSRC $TMPOPTS >> $BLDLOG 2>&1
if [ ! "$?" = "0" ]; then
	echo "$BN: cmake confiuration, generation error"
	exit 1
fi

echo "$BN: Doing: 'make' to $BLDLOG"
make >> $BLDLOG 2>&1
if [ ! "$?" = "0" ]; then
	echo "$BN: make error - see $BLDLOG for details"
	exit 1
fi

echo ""
echo "$BN: appears a successful build... see $BLDLOG for details"
echo ""
echo "$BN: Time for '[sudo] make install' IFF desired..."
echo ""

# eof

