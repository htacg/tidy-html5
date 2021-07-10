About this test suite:
======================

These test files represent that standard regression testing that must be
performed prior to committing changes to Tidy's code. In some circumstances
results are platform specific and these notices will be displayed in the
testing results.

This test set is intended to collect tests that have been added since
the migration of HTML Tidy from Sourceforge, and the base names should
be the issue/PR number associated with the test. Multiple tests for the
same issue should be a, b, c, etc., e.g., 119a, 119b, and so on.

Some of the test cases for big fixes _may_ be in the “legacy” test set,
but we’re not going to dig into the commit history to find out. In
general, new tests should go into this directory.
