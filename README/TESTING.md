# Testing

It‘s critical that changes you introduce do not cause regressions, i.e., that
Tidy’s output remains consistent with the introduction of your changes, except
for very specific circumstances.

Additionally, changes that you introduce to Tidy must usually be accompanied by
one or more test cases demonstrating the new feature or changed behavior.

Both of these concerns can be addressed with the Tidy repository’s automated
regression testing features, which are enabled by Github Actions. Any pull
request you make will automatically test your PR against the existing set of
test cases, and any failures are prima facie grounds for rejecting the PR. 

You _must_ test your changes locally using the tools and test cases provided in
the `regression_testing/` directory prior to submitting a PR, including adding
test cases to this directory as needed.


## Changes to Existing Output

If your changes affect existing output, it’s critical to understand _why_, and
if necessary, regenerate the `-expects` files so that the regression testing
tool will pass with your new changes. These `-expects` changes, of course,
become part of your Pull Request, and will be subject to review and conversation
in the Pull Request thread.

If you do cause such regressions, please be prepared to defend why they are
needed.

## New Tests

If you’re adding new features to Tidy, code reviewers need to be able to see the
intended effect of your changes via some type of demonstration. As such, please
write at least one test case in `github-cases` and put the expected results in
`github-expects`. These also constitute a part of your Pull Request, and more
importantly, will become part of the standard regression testing suite once the
PR is merged.

Try to keep your test case(s) as succinct as possible, and do try to put some HTML
comments in the file explaining the purpose of the test case, and if applicable,
the Github issue and/or PR number.

Note that the files generated in `github-results` for your new test cases are
suitable for use in `github-expects` when you are satisfied with the results.

A sample `case-123a@0.html` might represent issue #123, test **a** in a series
of multiple tests for this issue number, expecting Tidy exit code 0, and might
look something like this:

```
<!DOCTYPE html>
<html>
<!--
This test case represents HTML Tidy issue #123, and demonstrates
the use of new feature #xxx. Tidy should exit with status code 0.
The reason this change is needed is because WHATWG suddently
determined that a standards change #yyyy impacts us because of zzz.
 -->
<head>
<title>Case #123a</title>
</head>
<p>The quick brown fox jumps over the lazy dog.<//p>
<body>
</body>
</html>
```


## Regression Testing Specifics

The regression testing mechanism is described more fully in [regression_testing/README.md](../regression_testing/README.md).
