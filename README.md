# HTML Tidy for HTML5 (experimental)

This repo is an experimental fork of the code from [tidy.sourceforge.net][1].
This source code in this version supports processing of HTML5 documents. The
changes for HTML5 support started from a [patch developed by Björn Höhrmann][2].

   [1]: http://tidy.sourceforge.net

   [2]: http://lists.w3.org/Archives/Public/www-archive/2011Nov/0007.html

For more information, see [w3c.github.com/tidy-html5][3]

   [3]: http://w3c.github.com/tidy-html5/

For *nix platforms, you can build and install from the source code using the
following steps.

  1. `make -C build/gmake/`

  2. `make install -C build/gmake/`

Note that you will either need to run `make install` as root, or with `sudo make
install`.

