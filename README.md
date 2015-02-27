# HTML Tidy with HTML5 support

## Prerequisites

  1. git - http://git-scm.com/book/en/v2/Getting-Started-Installing-Git
  
  2. cmake - http://www.cmake.org/download/
  
  3. appropriate build tools for the platform
  
CMake comes in two forms - command line and gui. Some installations only install one or the other, but sometimes both. The build commands below are only for the command line use.

Also the actual build tools vary for each platform. But that is one of the great features of cmake, it can generate variuous 'native' build files. Running cmake without any parameters will list the generators available on that platform. For sure one of the common ones is "Unix Makefiles", which needs autotools make installed, but many other generators are supported.

In windows cmake offers various versions of MSVC. Again below only the command line use of MSVC is shown, but the tidy solution (*.sln) file can be loaded into the MSVC IDE, and the building done in there.


## Build the tidy library and command line tool

  1. `cd build/cmake`

  2. `cmake ../.. [-DCMAKE_INSTALL_PREFIX=/path/for/install]`

  3. Windows:  `cmake --build . --config Release`  
     Unix/OS X: `make`

  4. Install, if desired:  
     Windows: `cmake --build . --config Release --target INSTALL`  
     Unix/OS X: `[sudo] make install`

By default cmake sets the install path to /usr/local in unix. If you wanted the binary in say /usr/bin instead, then in 2. above use -DCMAKE_INSTALL_PREFIX=/usr

In windows the default install is to C:\Program Files\tidy5, or C:/Program Files (x86)/tidy5, which is  not very useful. After the build the tidy[n].exe is in the Release directory, and can be copied to any directory in your PATH environment variable, for global use.

If you need the tidy library built as a 'shared' (DLL) library, then in 2. add the command -DBUILD_SHARED_LIB:BOOL=ON. This option is OFF by default, so the static library is built and linked with the command line tool for convenience.

## History

This repository should be considered canonical for HTML Tidy as of 2015-January-15.

 - This repository originally transferred from [w3c.github.com/tidy-html5][1].
 
 - First moved to Github from [tidy.sourceforge.net][2].


   [1]: http://w3c.github.com/tidy-html5/

   [2]: http://tidy.sourceforge.net

