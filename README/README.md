# HTML Tidy with HTML5 support

## Prerequisites

  1. git - http://git-scm.com/book/en/v2/Getting-Started-Installing-Git
  
  2. cmake - http://www.cmake.org/download/
  
  3. appropriate build tools for the platform
  
  4. the [xsltproc](http://xmlsoft.org/XSLT/xsltproc2.html) tool is required to build and install the tidy.1 man page.
  
CMake comes in two forms - command line and gui. Some installations only install one or the other, but sometimes both. The build commands below are only for the command line use.

Also the actual build tools vary for each platform. But that is one of the great features of cmake, it can generate variuous 'native' build files. Running `cmake --help` should list the generators available on that platform. For sure one of the common ones is "Unix Makefiles", which needs autotools make installed, but many other generators are supported.

In windows cmake offers various versions of MSVC. Again below only the command line use of MSVC is shown, but the tidy solution (*.sln) file can be loaded into the MSVC IDE, and the building done in there.


## Build the tidy library and command line tool

  1. `cd build/cmake`

  2. `cmake ../.. -DCMAKE_BUILD_TYPE=Release [-DCMAKE_INSTALL_PREFIX=/path/for/install]`

  3. Windows:  `cmake --build . --config Release`  
     Unix/OS X: `make`

  4. Install, if desired:  
     Windows: `cmake --build . --config Release --target INSTALL`  
     Unix/OS X: `[sudo] make install`

By default cmake sets the install path to `/usr/local/bin` in unix. If you wanted the binary in say `/usr/bin` instead, then in 2. above use -DCMAKE_INSTALL_PREFIX=/usr

Also, in unix if you want to build the release library without any debug `assert` in the code then add `-DCMAKE_BUILD_TYPE=Release` in step 2. This adds a `-DNDEBUG` macro to the compile switches. This is normally added in windows build for the `Release` config.

In windows the default install is to `C:\Program Files\tidy`, or `C:/Program Files (x86)/tidy`, which is  not very useful. After the build the `tidy.exe` is in the Release directory, and can be copied to any directory in your **PATH** environment variable, for global use.

If you do **not** need the tidy library built as a 'shared' (DLL) library, then in 2. add the command -DBUILD_SHARED_LIB:BOOL=OFF. This option is ON by default. The static library is always built and linked with the command line tool for convenience in windows, and so the binary can be run as part of the man page build without the shared library being installed in unix.

See the `CMakeLists.txt` file for other cmake **options** offered.

## Build PHP with the tidy-html5 library

Due to API changes in the PHP source, "buffio.h" needs to be changed to "tidybuffio.h" in the file ext/tidy/tidy.c.

That is - prior to configuring php run this in the php source directory:
```
sed -i 's/buffio.h/tidybuffio.h/' ext/tidy/*.c
```

And then continue with (just an example here, use your own php config options):

```
./configure --with-tidy=/usr/local
make
make test
make install
```

## Important Links

 - site: http://www.html-tidy.org/
 - source: https://github.com/htacg/tidy-html5
 - binaries: http://binaries.html-tidy.org
 - bugs: https://github.com/htacg/tidy-html5/issues
 - list: https://lists.w3.org/Archives/Public/html-tidy/
 - api and quickref: http://api.html-tidy.org/

## Development

The default branch of this repository is `master`. This is the development branch, hopefully always `stable` source.

It will identify as library version X.odd.X. Use it to help us on the forever `bug` quest, addition of new features, options, ..., etc.

However, if you seek **release** code, then do `git branch -r`, and choose one of the `release/X.even.0` branches for your build and install...

This will always be the latest release branch. Important `bug` fixes thought relevant to this release, pushed back, may bump the library version to X.even.1, ..., etc, but will be remain known as `X.even`...

Some more details of the `Tidy Version` can be found in [VERSION.md](VERSION.md).

Concerning the `Tidy Code Style`, some notes can be found in [CODESTYLE.md](CODESTYLE.md).

If you want to contribute to Tidy, then read [CONTRIBUTING.md](CONTRIBUTING.md).

If you want to add a new configuration **option** to tidy, see [OPTIONS.md](OPTIONS.md).

Tidy is moving towards `localization` of the message string. To help in this effort see [LOCALIZE.md](LOCALIZE.md).

Tidy API documents, and quick reference generation has been moved to its own repo [html-tidy.org.api](https://github.com/htacg/html-tidy.org.api). Likewise, release binary generation has been moved to [html-tidy.org.binaries](https://github.com/htacg/html-tidy.org.binaries). Consult the respective `readmes` there for further details.

## History

This repository should be considered canonical for HTML Tidy as of 2015-January-15.

 - This repository originally transferred from [w3c.github.com/tidy-html5](http://w3c.github.com/tidy-html5/), now redirected to the current site.
 
 - First moved to Github from [tidy.sourceforge.net](http://tidy.sourceforge.net). Note, this site is kept only for historic reasons, and is not now well maintained.

**Tidy is the granddaddy of HTML tools, with support for modern standards.** Have fun...

; eof
