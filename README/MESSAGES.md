# Message System

Tidy has a quite complex warning/error report and footnote messaging system, but most of this complexity is completely hidden away from you in order to make adding messages as simple as possible. This particular README instructs you how to add a new warning/error report to **libTidy**.

First assign the message a **key** value. This is done in `tidyenum.h`, in one of the two enumerations that are listed there.

 1. `tidyStrings` - starts with the value `TIDYSTRINGS_FIRST = 500`, and it must be first. This is the list of all strings available in Tidy with the exception of strings provided by other enumerations. **However** don't modify this enum directly. You'll modify a preprocessor macro instead.
 
 2. `TidyOptionId` - You probably won't need this unless you're adding new options, and there's another readme for that.
 
 3. `TidyConfigCategory` - You probably won't need this, either, unless you're adding a whole new category for options.
 
 4. `TidyReportLevel` - And you probably won't need this, either.

All enum values are only ever used by name within **libTidy** (and incidentally, should only ever be used by name in your client applications; never trust the value!), so feel free to enter new strings in English alphabetical order (this helps us audit all of the strings from time to time). 

As mentioned above, `tidyStrings` messages must be defined in one of the existing macros named like `FOREACH_...(FN)`, such as `FOREACH_DIALOG_MSG(FN)`. These macros ensure that another data structure used for localization and key lookup is updated automatically any time strings are added or removed, thus limiting the possibility of developer error.


## Step 1

So in this case I want to add 3 warning messages: `BAD_SURROGATE_PAIR`, `BAD_SURROGATE_TAIL`, and `BAD_SURROGATE_LEAD`. Because these are error reports, they belong in the `tidyStrings` enum, and they fit into nicely into the macro beginning `FOREACH_REPORT_MSG(FN)`. Add the message key values into this macro, ensuring they are nested in the `FN()` syntax.


## Step 2

The next step is adding a `format` string to `language_en.h`. This string may later be translated to various supported language strings, but even if you wish to support another language, it’s critical that you add the message format string to `language_en.h`, which serves as the base language for `LibTidy`.

Where to add this seems a bit of a mess, but in general things are grouped by where they're used in `libTidy`, and often in alphabetical order within those groups. Here I've added them in alphabetical order in the section where all of the other report messages are.

Depending on which of the output routines you use (consult `message.c`) you may be able to use parameters such as `%u` and `%s` in your format strings. The available data is currently limited to the available message output routines. Please don't use `printf` for message output within **libTidy**.

Note that Tidy doesn't currently support numbered `printf` parameters; parameters will be consumed in the order the report output function calls them.

## Step 3

The last step — hopefully — is adding the message key to the `dispatchTable[]` structure in `message.c`. This structure determines the `TidyReportLevel` (report severity) and message formatter (how to print the message). Then whenever you issue the report with `TY_(Report)()` or one of the existing convenience report functions, the correct message formatter will be used for the parameters that you specify.

Please read the source code in `message.c` for help on how to choose a message formatter, or how to modify one of the existing message formatters if you need to accomodate a new function signature for your report.

eof;
