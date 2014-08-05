README.html4.txt - 20140805

This folder contains about dozen HTML files, each using a tag or tags REMOVED from HTML5

Running these files through standard 2009 tidy should mostly produce no errors or warnings.

However if a HTML 5 aware tidy is used, and doctype: html5 is configured, EACH should
have warnings and/or errors...

A batch file, testhtml4.cmd is provided to run these tests using the tidy5.exe 
built using build/cmake... system, namely expects the EXE to be at -

 ..\..\..\build\cmake\Release\tidy5.exe.

If you have used some 'other' build system, then the batch file may have to be 
adjusted to find the correct EXE to use.

At the end it will report the number of tests that failed, which should be ZERO 
for a successful run. Remember here success is when a warning or error is produced, 
and a FAILURE if a clean run.

There is also a cleanup.bat to delete the products produced by this test.

Enjoy.

# eof
