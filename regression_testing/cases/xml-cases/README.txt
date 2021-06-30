README for XML Test Cases:
==========================

This test suite contains files for regression testing HTML Tidy's XML output.
Note that the following tests are duplicated in the standard test cases, and
are present here because they were present in the original XML testing script,
despite their being non-XML files:

Case    Exit Code  Duplicates
------  ---------  ----------
432677  0          cases
434100  2          cases
473490  1          cases
542029  1          cases
586555  1          cases
634889  1          cases

The original XML testing script only checked Tidy’s exit status. All of the
current testing checks exit status as well as performs an output comparison.
