#!/bin/sh

if ! test -f build/gnuauto/setup.sh; then

   echo ""
   echo "* * * Execute this script from the top source directory, e.g.:"
   echo ""
   echo "	$ /bin/sh build/gnuauto/setup.sh"
   echo ""

else

   for i in libtoolize glibtoolize 
   do 
      ( $i --version) < /dev/null > /dev/null 2>&1 && 
      LIBTOOLIZE=$i 
   done 
   if test -z "$LIBTOOLIZE" ; then 
      echo "You need libtoolize to continue" 
      exit 1; 
   fi
   top_srcdir=`pwd`
   echo ""
   echo "Generating the build system in $top_srcdir"
   echo ""
   echo "copying files into place: cd build/gnuauto && cp -R -f * $top_srcdir"
   (cd build/gnuauto && cp -R -f * $top_srcdir)
   echo "running: $LIBTOOLIZE --force --copy"
   $LIBTOOLIZE --force --copy
   echo "running: aclocal"
   aclocal
   echo "running: automake -a -c --foreign"
   automake -a -c --foreign
   echo "running: autoconf"
   autoconf
   echo ""
   echo "If the above commands were successful you should now be able"
   echo "to build in the usual way:"
   echo ""
   echo "	$ ./configure --prefix=/usr"
   echo "	$ make"
   echo "	$ make install"
   echo ""
   echo "to get a list of configure options type: ./configure --help"
   echo ""
   echo "Alternatively, you should be able to build outside of the source"
   echo "tree. e.g.:"
   echo ""
   echo "	$ mkdir ../build-tidy"
   echo "	$ cd ../build-tidy"
   echo "	$ ../tidy/configure --prefix=/usr"
   echo "	$ make"
   echo "	$ make install"
   echo ""

fi
