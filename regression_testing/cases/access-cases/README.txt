About this test suite:
======================

These files ensure that Tidy is presenting the correct accessibility information
when used with Tidy’s various levels of accessibility checking.

The original accessibility test script looked for a single line of output
present in Tidy's error output. Current treatment as a standard regression
test accomplishes the same result, in that testing the entire error output is
a superset of testing only the desired output anyway.
