#!/bin/sh

# See cat << HEREDOC for file description.


# Set this to the complete path of the tidy for which you want to generate
# documentation. Relative path is okay. You shouldn't have to change this
# too often if your compiler always puts tidy in the same place.

TIDY_PATH="../build/cmake/tidy"          # Build directory.

TIDY_VERSION=`head -n 1 ../version.txt`  # In project root directory.


cat << HEREDOC

  Build 'tidy.1', which is a man page suitable for installation
  in all Unix-like operating systems. This script will build
  it, but not install it.
  
  Build 'quickref.html'. This is distributed with the
  the Tidy source code and also used on Tidy's website.
  Be sure to distribute it with 'quickref.css' as well.

  Build the 'tidylib_api' directory, which contains a website
  with the documentation for TidyLib’s headers.
  
  These files will be built into '{current_dir}/temp'.
  
HEREDOC


# Output and flags' declarations.
DOXY_CFG="./doxygen.cfg"
OUTP_DIR="./temp"
BUILD_XSLT=1
BUILD_API=1


##
# Ensure the output dir exists.
##
if [ ! -d "$OUTP_DIR" ]; then
	mkdir $OUTP_DIR
fi


##
# Preflight
##

# Check for a valid tidy.
if [ ! -x "$TIDY_PATH" ]; then
  BUILD_XSLT=0
  echo "- '$TIDY_PATH' not found. You should set TIDY_PATH in this script."
fi

# Check for xsltproc dependency.
hash xsltproc 2>/dev/null || { echo "- xsltproc not found. You require an XSLT processor."; BUILD_XSLT=0; }


##
# Build 'quickref.html' and 'tidy.1'.
##

if [ "$BUILD_XSLT" -eq 1 ]; then
	# Use the designated tidy to get its config and help.
	# These temporary files will be cleaned up later.
	$TIDY_PATH -xml-config > "$OUTP_DIR/tidy-config.xml"
	$TIDY_PATH -xml-help > "$OUTP_DIR/tidy-help.xml"

	# 'quickref.html' and 'quickref_include.html' for the Doxygen build.
	xsltproc "./quickref.xsl" "$OUTP_DIR/tidy-config.xml" > "$OUTP_DIR/quickref.html"
	xsltproc "./quickref.include.xsl" "$OUTP_DIR/tidy-config.xml" > ./examples/quickref_include.html

	# Well, duh, we should tidy quickref.html
	$TIDY_PATH -config "./tidy.cfg" -modify "$OUTP_DIR/quickref.html"

	# 'tidy.1'; create a valid tidy1.xsl first by subbing CMAKE's variable.
	sed "s|@TIDYCONFIG@|./tidy-config.xml|g" < ./tidy1.xsl.in > "$OUTP_DIR/tidy1.xsl"
	xsltproc "$OUTP_DIR/tidy1.xsl" "$OUTP_DIR/tidy-help.xml" > "$OUTP_DIR/tidy.1"

	# Cleanup
	rm "$OUTP_DIR/tidy-config.xml"
	rm "$OUTP_DIR/tidy-help.xml"
	rm "$OUTP_DIR/tidy1.xsl"
	
	echo "'quickref.html' and 'tidy.1' have been built.\n"
else
  echo "* tidy.1 was skipped because not all dependencies were satisfied."
fi


##
# Preflight
##

# Check for the doxygen.cfg file.
if [ ! -f "$DOXY_CFG" ]; then
  BUILD_API=0
  echo "- 'DOXY_CFG' not found. It is required to configure doxygen."
fi

# Check for doxygen dependency.
hash doxygen 2>/dev/null || { echo "- doxygen not found. This script requires doxygen."; BUILD_XSLT=0; }


##
# Build the doxygen project.
##

if [ "$BUILD_API" -eq 1 ]; then
  echo "The following is doxygen's stderr output. It doesn't indicate errors with this script:\n"
  
  # echo the output of tidy5 --help so we can include
  $TIDY_PATH -h > "./examples/tidy5.help.txt"
  $TIDY_PATH -help-config > "./examples/tidy5.config.txt"
  
  
  ## copy license file to examples for includsing
  cp ../README/LICENSE.md ./examples/
  
  ## this lot 
  # - echoes and catches output of the doxygen config
  # - overwrites some vars but appending some to config at end
  # - which are then passed to doxygen as stdin (instead of the path to a config.file)
  ( cat "$DOXY_CFG"; \
    echo "PROJECT_NUMBER=$TIDY_VERSION"; \
    echo "GENERATE_TAGFILE=$OUTP_DIR/tidylib_api/tidy.tags"; \
    echo "HTML_EXTRA_FILES= ./examples/tidy5.help.txt ./examples/tidy5.config.txt"; ) \
    | doxygen - > /dev/null
    
    # cleanup
    rm "./examples/tidy5.help.txt"
    rm "./examples/tidy5.config.txt"
    rm "./examples/LICENSE.md"
    
  echo "\nTidyLib API documentation has been built."
else
  echo "* $OUTP_DIR/tidylib_api/ was skipped because not all dependencies were satisfied."
fi


##
# Done
##

echo "\nDone.\n"

