Building with MinGW
===================

Currently building with MinGW on Windows is a bit complicated, and these
assumptions are made:

1. Using MinGW as distributed from [http://mingw.org](http://mingw.org).
2. Using default install path (C:\MinGW)


Pre-Build Instructions
----------------------

**Copy the file `specs` into `C:\MinGW\lib\gcc\<version>\specs`**

This file was generated with `gcc-dumpspecs > specs`, and then modified to add
`-lmsvcrt_tidy` to the `*libgcc:` linking section.


**Copy the file `libmsvcrt_tidy.a` into `C:\MinGW\lib\`** (or someplace else you
know is included in gcc's library search path).

This file is the import library for `msvcrt.dll` that includes the missing
definitions not included in MinGW's own import library. It was generated via
`dlltool -v -d msvcrt.def -l libmsvcrt_tidy.a --dllname %windir%\System32\msvcrt.dll`.
The `msvcrt.def` file is available in the `mingw` directory, too.

You can inspect MS' `msvcrt.dll` with `dumpbin /exports C:\Windows\System32\msvcrt.dll`
in the Visual Studio Command Prompt (not CMD).


Build
-----

`cmake ..\.. -G "MinGW Makefiles"`
`mingw32-make`


Todo
----

Obviously this isn't a fun solution. Some help configuring CMake to include the
import library would be appreciated.

Also I'm not certain we should be distributing the import library as part of the
source. Would it be better to distribute the `msvcrt.def` as part of the source
and build the import library with `dlltool` as part of the build process?




