README.html4.txt - 20140805

## Tests 1

This folder contains about dozen HTML files, each using a tag or tags REMOVED from HTML5,
all named *4.html

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

## Tests 2

This folder contains about 14 HTML files, each using a tag or tags REMOVED from HTML5,
all named *5.html. A lot of the tests came from reading -
 http://www.whatwg.org/specs/web-apps/current-work/multipage/obsolete.html
A text copy, obsolete.txt is included in this folder.

These were use to test an develop the CheckHTML5(doc,node) service. And there are
a set of batch file to run these tests, named test*.bat, and some 'special' 
batch file like -

setexe.bat - This is called by all others to set the location of the EXE to use. This 
 file will need to be ADJUST to point to where the Tidy EXE that you want to use.
 
testone.bat - After setting the input file, each test????.bat calls this to conduct
 four (4) tests -
 Using configure DOCTYPE AND CLEAN
 Using configure DOCTYPE but NO CLEAN
 Using configure CLEAN but NO DOCTYPE
 Using configure NO CLEAN and NO DOCTYPE

All the output is redirected to tempinfo.html
 
The set of test batch files is -
testacro.bat testbig.bat testbody.bat testcent.bat testcent2.bat testdir.bat 
testfont.bat testi2.bat teststrike.bat testtt.bat

The name generally indicates the tag or attribute being tested...

Enjoy.

# eof
