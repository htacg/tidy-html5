#!/bin/sh
#< build-me.sh - 20140804
BN=`basename $0`

TMPSRC="../.."
BLDLOG="bldlog-1.txt"

if [ -f "$BLDLOG" ]; then
	rm -f $BLDLOG
fi

##############################################
### ***** NOTE THIS INSTALL LOCATION ***** ###
### Change to suit your taste, environment ###
##############################################
TMPINST="$HOME/projects/install/tidy"
TMPOPTS="-DCMAKE_INSTALL_PREFIX=$TMPINST"
#############################################
# Default to SHARED library in unix
TMPOPTS="$TMPOPTS -DBUILD_SHARED_LIB:BOOL=TRUE"

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
echo "$BN: Time for 'make install' IFF desired... to $TMPINST, unless changed..."
echo ""

# eof

