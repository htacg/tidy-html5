# About the Xcode Project

This Xcode project (developed using Xcode 6) serves as an alternative to `cmake` on
Mac OS X, and is intended for developers integrating lib-tidy into other products. For
the sake of completeness you can also build and install the tidy target.

The targets are

 - **tab2space**, builds the tab2space console application.
 - **tidy**, builds the tidy console application.
 - **lib-tidy**, builds the static library required by the other targets.

The non-install targets use the standard, modern Xcode out-of-source build destinations,
i.e., built items are located in your `DerivedData` folder.
 

## Build and Install

Xcode doesn’t offer a default way to install from the IDE. Instead you can use Terminal:

    sudo xcodebuild install -target tidy

…from within the `build/xcode` directory. This will install `tidy` in `/usr/local/bin`
and install the man page in `/usr/local/share`, which are appropriate locations. The
built-in `tidy` won’t be overwritten and will probably have priority over the newly
built version unless you update your `$PATH` in, e.g., your `.bash_profile` file.

There’s no install configuration for `tab2space` because there’s not really any point
in replacing the built-in version.


## How it works

All of the required compiler flags are in the project’s Build Settings, in the **Apple
LLVM 6.0 - Preprocessing** section. However in order to use the proper version number and
release date from the source code’s `version.txt` file, this file is “compiled” in the
`lib-tidy` target’s custom **Build Rules**. The build rule script creates the file
`xcode-version.h` that is used as the `lib-tidy` **Prefix Header** file in this target’s
build settings.


## Alternatives to this project

The **HTML Tidy** project uses `cmake` as its build system. You can [install `cmake` from
source very easily][1], and use the build instructions in **HTML Tidy**’s README file.

`cmake` is also capable of generating an Xcode project file for you. For example:

 - `cd build`
 - `mkdir xcode_build`
 - `cd xcode_build`
 - `cmake -G "Xcode" ../..`

The `build/xcode_build` folder will then contain all of the files that you need to build,
run, and install **HTML Tidy**. You can read a lot more information about this process
on [John Lamp’s CMake Tutorial][2].


   [1]: http://www.cmake.org/install/
   [2]: https://www.johnlamp.net/cmake-tutorial-2-ide-integration.html
