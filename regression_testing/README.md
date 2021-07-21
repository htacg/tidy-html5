Tidy Regression Testing Specification
=====================================

Background
----------
HTML Tidy uses regression testing as its main means of quality control when 
implementing new features and fixing bugs. HTML Tidy has been in constant 
development since before unit testing and automated testing were in wide use,
and has proven effective in guiding the development of Tidy.

This repository is the regression testing tool used by Tidy for both 
continuous integration, and for development work, and consists for test 
cases split into multiple set sets, as well as tools for automating testing.

Testing consists of automatically running some version (of your choice) of HTML 
Tidy on various operating systems and architectures against the suite of 
test cases, and comparing the Tidy and report output against known, “good” 
versions thereof.

This testing process ensures that:

- No regressions occur as a result of the changes you make to HTML Tidy. 
  Everything that has passed in the past should continue to pass, regardless 
  of your changes. Changing test expectations for existing test cases must 
  result in a discussion on the pull request discussion thread, otherwise 
  regressions are _prima facie_ cause for rejecting your pull request.

- Although touted as a “regression test,” code changes should also be 
  furnished with a test case that demonstrates the issue being corrected or 
  the feature being added. Logically you are already informally using one or 
  most test cases during your development of the patch; this simply 
  formalizes the requirement for HTML Tidy, and makes it much easier for the 
  maintainers to understand the impact of your proposed change.

Additionally, when introducing new features or fixing bugs,
new test cases should be written to demonstrate that the fix works against 
the test case.


About the Test Tool (test.rb)
-----------------------------
The `test.rb` tool replaces the previous Windows shell and Bash testing 
scripts. This start-from-scratch approach is intended to provide a single 
script that’s platform agnostic, for the primary purpose of enabling 
automated testing, but with strong support for use as a manual tool during 
HTML Tidy development.

Ruby was chosen as the scripting language of choice because it is available 
on every platform, is easy to read (even if you're not a Ruby programmer), 
and is supported by the major continuous integration testing providers, such 
as Github.

We recognize that some developers have scripting environment preferences, 
and as such, please feel free write wrappers around `test.rb` as needed in 
order to suit your prefences. If additional CLI API is needed to enable your 
scripting environment wrapper, please feel free to request such.


Building Tidy, and Tidy Versions
--------------------------------
The testing tool works by executing `tidy` (or `tidy.exe`, referred to only 
as `tidy` continuing) on your platform. Naturally, you don’t want to conduct 
testing using the normal, installed version of `tidy`, but rather version(s)
that you’ve built for testing.

By default, the `tidy` used will be in the standard build folder of the 
`tidy-html5` directory that is a sibling to this `tidy-html5-tests` 
directory. The complete relative path from `test.rb`, then, is:

```
../tidy-html5/build/cmake/tidy[.exe]
```

This makes it convenient when performing testing on both repositories when 
they’re checked out. However you can also specify another build of HTML Tidy 
as an optional argument, too.


Static Build Considerations
---------------------------
By default, HTML Tidy is built as a console application statically linked to 
LibTidy. Although the option to link against a dylib or dll exist when 
building, it’s suggested that you no longer do so, because you might put 
yourself into a situation where you’re testing multiple command line 
executables that are all linked to the same dynamic library!

Although not formally deprecated, you should consider dynamic linking 
deprecated and treat it that way. In a world where entire Java Runtime 
Environments are shipped _per program_, the benefits of dynamic linking no 
longer exist on any modern computer or operating system. In some cases, 
modern security hardening even prevents dynamic linking, and we’re likely to 
see such restrictions become more common in the future.


Running Test Tests
------------------

### Preparing the Environment

Assuming that you have a working Ruby interpreter, version 2.7 or so, upon 
`CD`-ing into the `tidy-html5-test` directory, you should execute `bundle 
install`, which ensures that any dependencies that your environment doesn’t 
already have will be downloaded.

### Executing the Program

In Windows shell and powershell, simply typing

~~~
test 
~~~

will run the tool. Usually. Probably. If not, try `ruby test.rb` in case 
your environment is not configured to work directly.

Unix and Unix-like operating systems (including WSL and other Unix-like 
environments for Windows) can run the program like such:

~~~
test.rb
~~~ 

### Testing
When used without any arguments, help will be provided. In general, though, 
you can do the following:

| Command                        | Effect                            |
|--------------------------------|-----------------------------------|
| `./test.rb test`               | Tests all cases in all test sets. |
| `./test.rb only <setname>`     | Tests only in the given test set. |
| `./test.rb case <case_number>` | Tests only on a single case.      |


Input Specification
-------------------

### Test Sets

“Test sets” are groups of individual tests that are thematically related,
such as accessibility checks, XML-specific tests, historical tests, etc.
Each set of cases consists of directories and a text file within the `cases/`
directory. Each test set shall consist of the following directories/files, where
`setname` indicates the name of the testing set, e.g., `testbase` (our default
set of case files).

- `setname/`, which contains the HTML files to tidy, and an optional
  configuration file for each case.

  - Test files shall have the format `case-basename@n<.html|.xml|.xhtml>`, 
    where `nnn` represents the test case name, and the `@n` metadata 
    represents the required shell exit status code that HTML Tidy should 
    produce after running the test case. The case name cannot contain 
    hyphens or the `@` symbol, and should represent something meaningful 
    such a a Github issue number.

  - Optional Tidy configuration files shall be named `case-basename.conf`.

  - In the absence of a configuration file, the file `config_default.conf` in
    each directory will be used instead.

  - `README<.txt|.md>`, which describes the test set.

- `setname-expects/`, which contains the expected output from HTML Tidy.
  - Files in the format `case-nnn<.html|.xml|.xhtml>` represent the expected 
    HTML file as generated by Tidy.
  - Files in the format `case-nnn.txt` represent the expected warning/error
    output from Tidy.
      
#### Example

```
cases/
   testbase/
      config_default.cong
      case-427821.html
      case-427821.conf
   testbase-expects/
      case-427821.html
      case-427821.txt
```


Output Specification
--------------------

The output specification is written such that it makes it trivial to easily
`diff` a `setname-expects` directory with the output of a test in order
to check for differences.

Test results consist of Tidy's HTML output and Tidy's warning/error output.

Each set of results consists of directories within the `cases/` directory.

- `setname-results` contains Tidy's HTML and warning/error output.
  - Files in the format `case-nnn.html` are the HTML file generated by Tidy.
  - Files in the format `case-nnn.txt` are the warning/error output from Tidy.

### Example

~~~
cases/
   testbase-results/
      case-427821.html
      case-427821.txt
~~~
