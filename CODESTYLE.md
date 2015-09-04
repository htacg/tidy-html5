# HTML Tidy Code Style

The source code of **libTidy**, and console Tidy, follow the preferences of the original maintainers. Perhaps some of these decisions were arbitrary and based on their sense of aesthetics but it is good to have all the code look the same even if its not exactly how everyone would prefer.

Developers adding code to Tidy! are urged to try to follow the existing code style. Code that does not follow these conventions will be accepted, but will be modified as time goes by to best fit the `Tidy Style`.

There has been a suggestion of using available utilities to make the style consistent, like [Uncrusty](https://github/bengardener/uncrusty)...

Others have suggested the [AStyle](http://astyle.sourceforge.net/) formatting program with '-taOHUKk3 -M8' arguments formats code in much the right way although there are a few bugs in AStyle.

But again these, and other tools may not produce code that everybody agrees with... and are presently not formally used in Tidy!

#### Known Conventions

From reading of the Tidy source, some things are self evident... in no particular order...

 - Use of 4-space indenting, and no tabs.
 - No C++ single line comments using `//`.
 - The openning `{` is indented on the next newline.
 - While the maximum code line length varies, generally long `if`, `while`, ... statements are wrapped to newlines.


Look forward to this document being filled out in detail...

Date: 20150904

; eof
