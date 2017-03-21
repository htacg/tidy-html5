# HTML Tidy Versioning

This document provides an explanation of how to interpret HTML Tidy’s version number, e.g. from command line output as a result of `tidy -v`, and also addresses the role of the file `version.txt` in Tidy’s build process.

## Background

**HTML Tidy** uses a modified version of [Semantic Versioning](http://semver.org/), and so it’s important to understand what the version number of **HTML Tidy** means to you, and how it might impact your workflow.

When you execute `tidy -v` on the command line, you might see responses such as:

~~~
HTML Tidy for Mac OS X version 5.1.24
HTML Tidy for Mac OS X version 5.2.0
HTML Tidy for Mac OS X version 5.3.15
HTML Tidy for Mac OS X version 5.4.0
HTML Tidy for Mac OS X version 5.5.1
~~~

_Obviously_ 5.5.1 is higher than 5.2.0, right? This might lead you to consider replacing your stable installations of **HTML Tidy** 5.2.0 across the board in your production process, but this might lead you to trouble. A little word about the meaning of our version numbers might help clear things up.

## Major, Minor, Patch

### Major

When HTACG assumed responsibility of **HTML Tidy** from previous maintainers, we immediately declared that the first release would be version 5.0, in honor of finally being able to offer modern HTML5 support.

Barring some major, monumental, massive change to Tidy, or the [release of HTML6](https://blog.whatwg.org/html-is-the-new-html5), **HTML Tidy** will probably be major version 5 forever. Maybe future maintainers will want to be trendy and release **HTML Tidy 2025**, but that’s for them to decide.

### Minor

The minor version tells a lot more about the true version of Tidy that you have, but even so it’s not a simple matter that 5 > 2 and must be better. The minor number indicates **HTML Tidy** _release versions_ or _development versions_.

- **even numbered minor versions** indicate released versions of **HTML Tidy**. We provide binaries for releases, API documentation, and full support including cherry picking bug fixes back to them. In standard parlance, _released_ versions are _stable_ versions, meaning that the API is stable and you can generally expect Tidy’s output to be the same (other than as a result of bug fixes). 

- **odd numbered minor versions** are development versions, or as is considered in many contexts _bleeding edge_ or _next_ versions. HTACG do not provide binaries, and API documentation is not usually up to date, but you do have access to the latest bug fixes, newest features, and knowledge of where Tidy is going. The downside, though, is that we make absolutely no guarantees that:

  - Output remains the same as in previous release versions.
  - Output remains the same as in earlier patch versions in the same development series.
  - Configuration options may be added.
  - Configuration options may be deleted.
  - Parts of the C API may be added or deleted without warning.
  - In short, development versions are bleeding edge and likely to be unstable (in the API sense -- we try never commit code that will crash).

### Patch

The patch indicates the latest version of the current minor version number. As with minor version numbers, there is some variation in their meaning:

- **patches for even numbered minor versions** indicate whether the latest supported update for that released version. In general, we hope that the patch number remains at 0 forever, e.g., 5.2.0. However if we do backport one or more bug fixes, you might see, e.g., 5.2.1.

- **patches for odd numbered minor versions** indicate our progress in committing code that changes some aspect of **HTML Tidy**’s operation, such as the output it generates or a bug fix. Because **git** offers robust commit logging of its own, we won't generally bump the patch number for things such as documenting code, converting tabs to space, or even simplifying some piece of logic. You’ll see that lots of good things are happening if the patch number is really large, e.g., 5.7.289!


## Development

### The `version.txt` File

The **libTidy** version is controlled by the contents of `version.txt` in the root.

This file consists of two lines of dot (.) separated items. The first being the **major**, **minor**, and **patch** version values, and the second string is a date. Example:

~~~
5.3.15
2017.01.29
~~~

When **CMake** is run, this file is read and two macros are added to the compile flags:

~~~
add_definitions ( -DLIBTIDY_VERSION="${LIBTIDY_VERSION}" )
add_definitions ( -DRELEASE_DATE="${tidy_YEAR}/${tidy_MONTH}/${tidy_DAY}" )
~~~

And in `CMakeLists.txt` there is the posibility to define another macro, when and if required:

~~~
# add_definitions ( -DRC_NUMBER="D231" )
~~~

These macros are put in `static const char` strings in **libTidys**’s internal- only `src/version.h` file:

~~~
static const char TY_(release_date)[] = RELEASE_DATE;
#ifdef RC_NUMBER
static const char TY_(library_version)[] = LIBTIDY_VERSION "." RC_NUMBER;
#else
static const char TY_(library_version)[] = LIBTIDY_VERSION;
#endif
~~~

These strings are returned respectively by the **libTidy** API functions:

~~~
TIDY_EXPORT ctmbstr TIDY_CALL     tidyLibraryVersion(void);
TIDY_EXPORT ctmbstr TIDY_CALL     tidyReleaseDate(void);
~~~

### Git branches

Starting with HTML Tidy 5.4.0 release, our branching scheme aligns nicely with our version numbering scheme. Please consult [BRANCHES.md](BRANCHES.md).


Updated: 20170210  
   Date: 20150904
