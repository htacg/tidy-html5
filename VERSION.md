# Tidy Library Versioning

The **libTidy** version is controlled by the contents of `version.txt` in the root.

This file consists of two lines of dot (.) separated items. The first being the MAJOR, MINOR, and PATCH version values, and the second string is a date. Example -

```
5.1.8
2015.09.04
```

When cmake is run this file is read and two MACROS added to the compile flags -

```
add_definitions ( -DLIBTIDY_VERSION="${LIBTIDY_VERSION}" )
add_definitions ( -DRELEASE_DATE="${tidy_YEAR}/${tidy_MONTH}/${tidy_DAY}" )
```

And in CMakeLists.txt there is the posibility to define another MACRO, when and if required -

```
# add_definitions ( -DRC_NUMBER="D231" )
```

These MACROS are put in static const char strings in **libTidy's** `internal` only src/version.h file -

```
static const char TY_(release_date)[] = RELEASE_DATE;
#ifdef RC_NUMBER
static const char TY_(library_version)[] = LIBTIDY_VERSION "." RC_NUMBER;
#else
static const char TY_(library_version)[] = LIBTIDY_VERSION;
#endif
```

These strings are returned respectively by the **libTidy** API functions -

```
TIDY_EXPORT ctmbstr TIDY_CALL     tidyLibraryVersion(void);
TIDY_EXPORT ctmbstr TIDY_CALL     tidyReleaseDate(void);
```

**NOTE**: `tidyReleaseDate()` is marked deprecated!

The actual `versioning` of the library more or less follows the [Semantic Versioning](http://semver.org/) style.

When a `release` is done a release/5.0.0 **branch**, and a similar release/5.0.0 **tag** is created.

At that point the version.txt is set to the next, 5.1.0. 

That is the `master` branch will contain the ongoing development. Any subsequent good bug fixes found for some time after that will be carefully tested and push back (cherry picked I think is the correct term) into the release/5.0.0, making it 5.0.1...

And on just about each fix, or feature addition to the `master` will bump the version to 5.1.1, 5.1.2, 5.1.3, and so on... even 5.1.4567 if necessary ;=)).

When ready for the next release, say some 6 months or so later, then a branch `release/5.2.0` would be created, and tagged, and the master version.txt moved on to 5.3.0, and so on...

That is, each `release` will have an `even` second digit, followed by .0, unless any subsequent fixes are pushed back, making it .1, ... probably not many of those... while the `master` develoment HEAD will have an `odd` second digit, followed by .0, incremented for just about each significant code change...

The intial MAJOR digit, 5, will be maintained while the **libTidy** API remains fully compatible, although there may be additions, extensions, as and when these are identified...

And throughout this, every effort will be made to keep `master` **stable** at all times, but would expect package managers to eventually really only pick up on the `release` branches, tags. 

In cases of significant code re-writes, major featues added, these would be done in branches until they are `stable` enought, and tested enough, to be merge back to `master`.

Date: 20150904

; eof
