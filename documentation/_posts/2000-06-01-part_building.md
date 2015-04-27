---
title:    "Build"
bg:       "#7BC950"
color:    black    
style:    left
fa-icon:  cubes
---

# Building Tidy

## Source code

**Tidy**’s sourcecode can be found at [https://github.com/htacg/tidy-html5][1].
There are sometimes several branches, but in general **Master** is the most
recently updated version. Note that as “cutting edge,” it may have bugs or other
unstable behavior. If you prefer a stable, officially released version, be
sure to have a look at **Releases** on the github page.

In general you can use the **Download ZIP** button on the github page to
download the most recent version of a branch. If you prefer Git then you can
use, e.g.:

`git clone git@github.com:htacg/tidy-html5.git`

…to clone the repository to your working machine.


## Build the `tidy` command-line tool and `tidylib` library

For Linux/BSD/Mac platforms, you can build and install the `tidy` command-line
tool from the source code using the following steps:

1. `cd {your-tidy-html5-directory}/build/cmake`

2. `cmake ../.. [-DCMAKE_INSTALL_PREFIX=/path/for/install]`

3. Windows:  `cmake --build . --config Release`<br/>
   Unix/OS X: `make`

4. Install, if desired:<br/>
   Windows: `cmake --build . --config Release --target INSTALL`<br/>
   Unix/OS X: `[sudo] make install`

Note that you will either need to run `make install` as root,
or with `sudo make install`.


 [1]: https://github.com/htacg/tidy-html5
