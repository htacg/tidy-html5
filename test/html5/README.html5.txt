README.html5.txt - 20140805

This folder contains about 30 HTML5 coded examples, using each of the 'new' tags
added in HTML5.

Running these files through standard 2009 tidy should produce errors/warnings
like Error: <article> is not recognized, and will probably declare -
Info: Document content looks like HTML Proprietary.

A batch file, testhtml5.cmd is provided to run these tests using the tidy5.exe 
built using build/cmake... system, namely expects the EXE to be at
 ..\..\build\cmake\Release\tidy5.exe.

If you have used some 'other' build system, then the batch file may have to be 
adjusted to find the correct EXE to use.

At the end it will report the number of tests taht failed, which should be ZERO 
for a successful run.

Enjoy.

# eof

