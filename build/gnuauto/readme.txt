To use GNU "Auto" tools (AutoConf/AutoMake/LibTool), run
/bin/sh build/gnuauto/setup.sh from the top-level Tidy
directory.  This script will copy the appropriate 
Makefile.am files into each source directory, along with
configure.in.

If the script was successful you should now be able
to build in the usual way:

	$ ./configure --prefix=/usr
	$ make
	$ make install

to get a list of configure options type: ./configure --help

Alternatively, you should be able to build outside of the source
tree. e.g.:

 	$ mkdir ../build-tidy
 	$ cd ../build-tidy
 	$ ../tidy/configure --prefix=/usr
 	$ make
 	$ make install

