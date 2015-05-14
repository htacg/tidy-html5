# test directory 20150513

It seems very little has been written about what is in this directory!

All of the test input files, some with their own config file, are in the `'input` directory. These tests can be run using the various cmd/bat and sh script files supplied.

#### Files: alltest.cmd / testall.sh

In essence it was/is an attempt to automate some regression testing. The idea is/was that before making a code change to tidy, the alltest.cmd would be run using the current executable. This would produce a 'base' set of outputs in the temp-5 folder.

This folder should then be renamed say 'testbase'. Now you can make the desired code changes, and build a new executable, and run the alltest.cmd again, getting a 'new' output into the temp-5 folder.

Comparing the 'testbase' folder with the new 'temp-5' folder will show you what file output was changed by your code modification.

Difficult, and tedious! Yes, but is a sure way to see if your changes adversely effected tidy. Unfortunately, only such a visual comparison would show the results. If the output changes are fully acceptable, then this would become the new base.

Of course some of the tests were to say avoid a segfault found. Other tests were to visually compare the original input test file in a browser, with how the new output displayed in a browser. This is a purely VISUAL compare, and can not be done in code.

And what about if there was NO current test existing to test what you were trying to fix. Well that means a NEW test should be added. Its output added to the 'base', then there would be a comparison.

The chain is alltest.cmd runs alltest1.cmd, which then uses onetest.cmd for each test. And a similar chain for unix stating with testall.sh which uses testone.sh.

Both tool chains use the testcases.txt file for the list of some 227 cases. There is now a `testinfo.txt` file which give some desciption of the test. Well actually the title of the original bug report filed at https://sourceforge.net/p/tidy/bugs/#number/

Additionally there are some 27 xml tests, runby xmltest.cmd, reading the test list from xmlcases.txt, and using the same onetest.cmd for each test...

#### Files: acctest.cmd / testaccess.sh

Another series of tests in this folder are the accessability tests, executed by running the acctest.cmd.

It uses onetesta.cmd to process each of the some 118 tests in accesscases.txt. 

The test files for these accessability tests are in the `accessTest` directory.

There is a similar unix tool chain of testaccess.sh, which uses testaccessone.sh for each test, from the same accesscases.txt list.

#### Files: alltestc.bat

This is essentially similar to the above, except it includes a COMPARE of the previous established output in the `testbase` folder with the NEW output in temp-5, hence the addition of a 'c'.

As indicated above, this is an attempt to create such a BASE set of output files when tidy is run on the input test cases.

Then when alltestc.bat is run, it runs alltest2.bat, whihc like the above it reads the tests from testcases.txt, and uses onetest2.bat for each test.

So the difference between this and the above is, it further immediately compares the output of tidy, if there is one, with the equivalent file in the `testbase` directory using a windows port of diff.

It is a success if there is NO diff! A difference means this newer version of tidy has modified the output. That modification needs to be carefully inspected, and if it is though exact and suitable, then that new output should be copied to the `testbase` folder for future compares.

#### Directory html5:

A series of some 31 test html5 files were added for HTML5 support to this directory.

In this folder there is a testhtml5.cmd, which uses testone.cmd to run each test. Similarly a testhtml5.sh for unix.

Each of the *.org.html files will be process, with the output witten to a `tempout` directory.

This was just to ensure tidy5 had support for many new tags introduced in HTML5.


; eof
