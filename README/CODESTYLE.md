# HTML Tidy Code Style

The source code of **libTidy** and console app **tidy** mostly follow the preferences of the original maintainers. Perhaps some of these decisions were arbitrary and based on their sense of aesthetics at the time, but it is good to have all the code looking the same even if it is not exactly what everyone would prefer.

Developers adding code to HTML Tidy are urged to try to follow the existing code style. Code that does not follow these conventions may be accepted, but may be modified as time goes by to best fit the “Tidy Style.”

There has been a suggestion of using available utilities to make the style consistent, like [Uncrustify](https://github.com/uncrustify/uncrustify) - see [issue #245](https://github.com/htacg/tidy-html5/issues/245), and maybe others.

Others have suggested the [AStyle](http://astyle.sourceforge.net/) formatting program with say `-taOHUKk3 -M8` arguments, to conform, but there are a few bugs in AStyle.

But again, these and other tools may not produce code that everybody agrees with, and are presently not formally used in Tidy!

#### Known Conventions

From reading of the Tidy source, some things are self evident,  in no particular order...

 - Use of 4-space indenting, and no tabs.
 - No C++ single line comments using `//`.
 - The openning `{` is indented on the next newline.
 - While the maximum code line length varies, generally long `if`, `while`, ... statements are wrapped to newlines.
 - Pointer operators in declarations must precede any macro documentation, e.g, `const tidyLocaleMapItem* TIDY_CALL getNextWindowsLanguage( TidyIterator* iter )` instead of `const tidyLocaleMapItem TIDY_CALL *getNextWindowsLanguage( TidyIterator* iter )` in case `TIDY_CALL` is defined.



Look forward to this document being filled out in detail...

Date: 20150904
