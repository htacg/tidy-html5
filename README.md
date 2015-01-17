# HTML Tidy with HTML5 support

This repo is a fork of the code from [w3c.github.com/tidy-html5][3], which itself
is a fork of [tidy.sourceforge.net][1].

This source code in this version supports processing of HTML5 documents. The
changes for HTML5 support started from a [patch developed by Björn Höhrmann][2].

   [1]: http://tidy.sourceforge.net

   [2]: http://lists.w3.org/Archives/Public/www-archive/2011Nov/0007.html

For more information, see [w3c.github.com/tidy-html5][3]

   [3]: http://w3c.github.com/tidy-html5/


## Build the tidy library and command line tool

  1. cd build/cmake

  2. cmake ../.. [-DCMAKE_INSTALL_PREFIX=/path/for/install]

  3. Windows:  cmake --build . --config Release
     Unix/OSX: make

  4. Install, if desired
     Windows: cmake --build . --config Release --target INSTALL
     UNix/OSX: [sudo] make install

;eof
