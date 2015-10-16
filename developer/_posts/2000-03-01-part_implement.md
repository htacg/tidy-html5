---
title:    "Implement"
bg:       "#CCCCCC"
color:    black    
style:    left
fa-icon:  coffee
---

## Implement TidyLib

Once you’ve built **TidyLib** following the README instructions for `cmake` in
**HTML Tidy**’s repository, you can get started using **TidyLib**. `cmake` will
have built both the console application and the library for you.

Perhaps the easiest way to understand how to use **TidyLib** is to see a simple
program that implements it. Such a simple program follows in the next section,
and don't forget that you can also study `console/tidy.c`, too.

Before we look at the code, it’s important to understand that API functions that
return an integer almost universally adhere to the following convention:

0  == Success

 : Good to go.

1  == Warnings, but no errors

 : Check the error buffer or track error messages for details.

2 == Errors (and maybe warnings)

 : By default, Tidy will not produce output. You can force output with the
   [`TidyForceOutput`][1] option. As with warnings, check the error buffer or
   track error messages for details.

<0 == Severe error

 : Usually value equals `-errno`. See `errno.h`.


Also, by default, warning and error messages are sent to `stderr`.
You can redirect diagnostic output using either `tidySetErrorFile()`
or `tidySetErrorBuffer()`. See `tidy.h` for details.


 [1]: /quickref#force-output.html
