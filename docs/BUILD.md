# HTACG HTML Tidy

## Prerequisites

  1. git - [https://git-scm.com/book/en/v2/Getting-Started-Installing-Git][1]
  
  2. cmake - [https://cmake.org/download/][2]
  
  3. appropriate build tools for the platform
  
  4. the [xsltproc][3] tool is required to build and install the `tidy.1` man page on Unix-like platforms.
  
CMake comes in two forms - command line and GUI. Some installations only install one or the other, but sometimes both. The build commands below are only for command line use.

Also the actual build tools vary for each platform. But that is one of the great features of CMake, it can generate various 'native' build files. Running `cmake --help` should list the generators available on that platform. For sure one of the common ones is "Unix Makefiles", which needs autotools make installed, but many other generators are supported.

In Windows CMake offers various versions for MSVC. Again below only the command line use of MSVC is shown, but the tidy solution (*.sln) file can be loaded into the MSVC IDE, and the building done in there.


## Build the tidy library and command line tool

### macOS/Linux/Unix

~~~
    cd build/cmake
    cmake ../.. -DCMAKE_BUILD_TYPE=Release [-DCMAKE_INSTALL_PREFIX=/path/for/install]
    make
    [sudo] make install
~~~

### macOS (multi-architecture)

~~~
    cd build/cmake
    cmake ../.. -DCMAKE_BUILD_TYPE=Release "-DCMAKE_OSX_ARCHITECTURES=x86_64;arm64"
    make
    [sudo] make install
~~~

### Windows

~~~
    cd build/cmake
    cmake ../.. -DCMAKE_BUILD_TYPE=Release [-DCMAKE_INSTALL_PREFIX=/path/for/install]
    cmake --build . --config Release
    cmake --build . --config Release --target INSTALL
~~~

### Build options

By default cmake sets the install path to `/usr/local/bin` in Unix. If you wanted the binary in say `/usr/bin` instead, then in the second step, use `-DCMAKE_INSTALL_PREFIX=/usr`.

Also, in Unix if you want to build the release library without any debug `assert` in the code then add `-DCMAKE_BUILD_TYPE=Release` in the second step. This adds a `-DNDEBUG` macro to the compile switches. This is normally added in windows build for the `Release` config.

In Windows the default install is to `C:\Program Files\tidy`, or `C:/Program Files (x86)/tidy`, which is  not very useful. After the build the `tidy.exe` is in the `Release` directory, and can be copied to any directory in your `PATH` environment variable for global use.

On macOS, you can build for both Intel and Apple Silicon by adding "-DCMAKE_OSX_ARCHITECTURES=x86_64;arm64" in the second step.

If you do **not** need the tidy library built as a 'shared' (DLL) library, then in the second step add the command `-DBUILD_SHARED_LIB:BOOL=OFF`. This option is **ON** by default. The static library is always built and linked with the command line tool for convenience in Windows, and so the binary can be run as part of the man page build without the shared library being installed in unix.

See the `CMakeLists.txt` file for other CMake **options** offered.

## Build the tidy packages

  1. `cd build/cmake`

  2. `cmake ../.. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr`

  3. Unix/OS X: `make package`

## Build PHP with the tidy-html5 library

Before PHP 7.1, due to API changes in the PHP source, `buffio.h` needs to be renamed to `tidybuffio.h` in the file `ext/tidy/tidy.c` in PHP's source.

That is - prior to configuring PHP run this in the PHP source directory:
~~~
sed -i 's/buffio.h/tidybuffio.h/' ext/tidy/*.c
~~~

And then continue with (just an example here, use your own PHP config options):

~~~
./configure --with-tidy=/usr/local
make
make test
make install
~~~

  [1]: https://git-scm.com/book/en/v2/Getting-Started-Installing-Git
  [2]: https://cmake.org/download/
  [3]: http://xmlsoft.org/XSLT/xsltproc2.html
