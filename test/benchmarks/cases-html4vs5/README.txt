About this test suite:
======================

This test suite is largely a development test suite used to ensure the proper
behavior of various elements when Tidy is given an HTML4, HTML5, or automatic
document type. Each document is processed with each of the doctypes to ensure
proper output.

As these functions are largely stable they're not included in the standard
set of regression tests, but are still available for sanity checking.

Each case file targets primarily a single element that is treated differently
in HTML5 versus older HTML. Each case file has multiple configurations for
which regressions are tested, ensuring that Tidy treats them properly.
