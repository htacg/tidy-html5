# HTML Tidy with HTML5 support

This repository consists of the stable and development branches of HTML Tidy.

 - branch **develop-\*\*\*** consists of the current development and release candidate
   for **HTML Tidy**. Release Candidates can be identified with git tags.

 - branch **master** consists of the current, stable release of **HTML Tidy**. 


## Build the tidy library and command line tool

  1. `cd build/cmake`

  2. `cmake ../.. [-DCMAKE_INSTALL_PREFIX=/path/for/install]`

  3. Windows:  `cmake --build . --config Release`  
     Unix/OS X: `make`

  4. Install, if desired:  
     Windows: `cmake --build . --config Release --target INSTALL`  
     Unix/OS X: `[sudo] make install`


## History

This repository should be considered canonical for HTML Tidy as of 2015-January-15.

 - This repository originally transferred from [w3c.github.com/tidy-html5][1].
 
 - First moved to Github from [tidy.sourceforge.net][2].


   [1]: http://w3c.github.com/tidy-html5/

   [2]: http://tidy.sourceforge.net

