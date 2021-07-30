# The `LibTidy` API and Namespacing

## Introduction

If you're just getting started working with `LibTidy`, some of the design choices may seem overwhelming if you're not a seasoned C veteran. Hopefully this article will give a decent overview, encouraging you to explore and contribute to the `LibTidy` code.

This article will discuss briefly:

- How `LibTidy` achieves namespacing in C

- Explanations for some of the bizzarre, do-nothing macros.

- Opaque types

- How to add new functions to the `LibTidy` API.


# Namespacing

The C language does not support built in namespacing, but it is subject to namespace collision, especially when a library is statically linked. `LibTidy` tries to get around this by making a compromise between human-readable names and making the names random enough to avoid a collision.

As you browse Tidy's code, you'll notice many uses of a macro function – `TY_()` – applied to the function names of non-static functions. The preprocessor thus resolves all of these function names to `prvTidyFunction`, thus ensuring a clear namespace and avoiding the possibility of collisions (unless some other library has thoughtlessly borrowed our prefix for the same). For example, `TY_(getNextOptionPick)` will resolve to `prvTidygetNextOptionPick` when compiled.

Of course, `static` functions are immune to the issue of namespace pollution, so in general you will really only use this technique for functions that must be accessible from outside of your new file, such as functions that you want to expose to the API.


# Macros for documentation

`TIDY_EXPORT` and `TIDY_CALL` are defined to be `NULL`, i.e., when compiled they resolve to nothing. These are used exclusively for documenting functions that are part of the API defined in `tidy.h` and the implementation in `tidylib.c`. For example, in `tidy.h`:

~~~
TIDY_EXPORT TidyIterator TIDY_CALL getWindowsLanguageList();
~~~

The `TIDY_EXPORT` call clearly indicates that this function prototype is meant to be exported from the API, and `TIDY_CALL` clearly indicates that the function is called from within `LibTidy`.

Although this makes things obvious from the documentation perspective, the truth is a little murkier. In some environments one might define `TIDY_EXPORT` and `TIDY_CALL` differently in order to control compiler behavior, especially in environments that have special requirements for dynamic libraries. In general, though, you shouldn't have to worry about this.

The preferred use of pointer operators when documenting with macros is this:

~~~
const tidyLocaleMapItem* TIDY_CALL getNextWindowsLanguage( TidyIterator* iter )
~~~

…instead of this:

~~~
const tidyLocaleMapItem TIDY_CALL *getNextWindowsLanguage( TidyIterator* iter )
~~~


# External types are opaque

In several spots the source code indicates that a particular structure is "opaque." This simply means that API users cannot see inside of them, and they have to depend on accessor functions to gain access to the sweet fruit that is within. This is a design choice that makes `LibTidy` highly portable and makes it accessible to multitudes of other languages that can communicate with a C API.

Take `tidyDoc` for example, as it's the most fundamental datatype within `LibTidy`. As an API user, you can have a reference to a `tidyDoc`, and you're going to pass it around a lot to accessor functions (such as `tidyCleanAndRepair`), and you know that it contains lots of good stuff, but you're not allowed to peek inside of it unless an accessor function is provided. Think of it as a token that you pass around, and nothing more.

Internally, the type is cast to a native C structure of type `tidyDocImpl`, and so if you decide to become a Tidy developer, you have the choice to access the item fully.

If you extend Tidy's API, it's important to respect this design choice, even if only writing functionality for the console application (which is, of course, simply an implementor of `LibTidy`).


# How to add new functions to `LibTidy`

All of the information above is useful for anyone who wants to browse Tidy's source code, or use the API, or understand Tidy better, but it all comes together nicely when you want to extend the API. This quick lesson will show you how to do so, using `tidyLocalizedString()` as an example.

## Behind the scenes

The first thing we need to do is have the internal version of the function that we want to add. Tidy has a module that handles localization: `language.h/c`. In the header is where we define the interface to LibTidy, which should be namespaced according to the discussion above. We can declare:

~~~
ctmbstr TY_(tidyLocalizedString)( uint messageType );
~~~

…and of course implement it in the `.c` file.

Now you have a decision to make: if you plan to use this function internally, you're going to have to import the header into other modules that require the function. This can lead to painful compile-time consequences. However since we want to expose this particular function to the API, it will be visible within `TidyLib`, so we can use the public API internally, too.

## The API

Once implemented, we want a pretty, public-facing name for our `tidyLocalizedString()` function, which appropriately is `tidyLocalizedString()`. Add the declaration to `tidy.h`:

~~~
TIDY_EXPORT ctmbstr TIDY_CALL tidyLocalizedString( uint messageType );
~~~

…and now the publicly exposed interface knows that your function exists. All that's left to do is add the `language.h` header to `tidylib.c`, and then implement it there:

~~~
ctmbstr TIDY_CALL tidyLocalizedString( uint messageType )
{
    return TY_(tidyLocalizedString)( messageType );
}
~~~

Congratulations, you can now expose new functionality to the API.

## API functions for opaque types

For a more complicated example that demonstrates how to use opaque types (and also the `TidyIterator` type) have a look at the implementation of `getWindowsLanguageList()`, and its partners `*getNextWindowsLanguage()`, `TidyLangWindowsName()`, and `TidyLangPosixName()`. These demonstrate how to:

  - implement iteration for structures with multiple records.
  - write a function in `tidylib.c` that converts between the exposed, opaque type and the internal, implementation type.
  - further reinforce how functionality is added to the API.
