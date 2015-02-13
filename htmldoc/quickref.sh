#!/bin/sh

cat << HEREDOC
  Build 'quickref.html'. This is distributed with the
  the Tidy source code and also used on Tidy's website.
  Be sure to distribute it with 'quickref.css' as well.
HEREDOC


# Set this to the complete path of the tidy for which you want to generate
# documentation. Relative path is okay. You shouldn't have to change this
# too often if your compiler always puts tidy in the same place.
TIDY_PATH="./tidy5"         # Current directory.
#TIDY_PATH="/usr/bin/tidy"  # the default on some operating systems.


# Check for a valid tidy.
if [ ! -x "$TIDY_PATH" ]; then
  echo "$TIDY_PATH not found. You should set TIDY_PATH in this script."
  exit 1
fi

# Check for xsltproc dependency.
hash xsltproc 2>/dev/null || { echo >&2 "This script requires xsltproc. Aborting."; exit 1; }

# Use the designated tidy to get its config and help.
# These temporary files will be cleaned up later.
$TIDY_PATH -xml-config > "tidy-config.xml"
#$TIDY_PATH -xml-help > "tidy-help.xml"

# 'quickref.html'
# This file is distributed with tidy and use on the website.
xsltproc "quickref.xsl" "tidy-config.xml" > "quickref.html"

# 'tidy.1'
# Build a manpage for *nix systems. Build only, no install.
# - requires `tidy-config.xml` (loaded by 'tidy1.xsl' directly)
#xsltproc "tidy1.xsl" "tidy-help.xml" > "tidy.1"

# Cleanup
rm "tidy-config.xml"
#rm "tidy-help.xml"

# Done
echo Done.
