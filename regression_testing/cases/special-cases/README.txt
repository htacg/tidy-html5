About this test suite:
======================

These test files represent that standard regression testing that must be
performed prior to committing changes to Tidy's code. In some circumstances
results are platform specific and these notices will be displayed in the
testing results.

This test set is intended to collect tests that we **don't** want to run
automatically, either because they take a long time to complete, or their
expectations files are much too large for keeping the repository a reasonable
size.

Because there's no matching -expects directory, these cases will NOT be included
in the default testing service.
