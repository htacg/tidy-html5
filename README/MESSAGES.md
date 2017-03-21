# Message System

Tidy has quite complex warning/error messaging system. This is all about adding a **new** warning or error message to **libTidy**.

First assign the message a key value. This is done in `tidyenum.h`, in one of the two enumerations that are listed there.

 1. `tidyStrings` - starts with the value `TIDYSTRINGS_FIRST = 500`, and it must be first. This is the list of all strings available in Tidy with the exception of strings provided by other enumerations. **However** don't modify this enum directly. You'll modify a preprocessor macro instead.
 
 2. `TidyOptionId` - You probably won't need this unless you're adding new options, and there's another readme for that.
 
 3. `TidyConfigCategory` - You probably won't need this, either, unless you're adding a whole new category for options.
 
 4. `TidyReportLevel` - And you probably won't need this, either.


All enum values are only ever used by name within **libTidy** (and incidentally, should only ever be used by name in your client applications; never trust the value!), so feel free to enter new strings wherever they make the most sense. 

As mentioned above, `tidyStrings` messages must be defined in one of the existing macros named like `FOREACH_...(FN)`, such as `FOREACH_DIALOG_MSG(FN)`. These macros ensure that another data structure used for localization and key lookup is updated automatically any time strings are added or removed, thus limiting the possibility of developer error.


## Step 1

So in this case I want to add 3 warning messages: `BAD_SURROGATE_PAIR`, `BAD_SURROGATE_TAIL`, and `BAD_SURROGATE_LEAD`. Because these are error messages, they belong in the `tidyStrings` enum, and they fit into nicely into the macro beginning `FOREACH_DIALOG_MSG(FN)`. Please look at the comments for the category which indicates which output routine is used to generate the error, and keep this list in order!


## Step 2

The next step is adding a `format` string to `language_en.h`. This string may later be translated to various supported language strings, but at present it is important that the other language translated strings, like `language_fr.h`, `language_es.h`, etc, keep the same format order.

Where to add this seems a bit of a mess, but in general things are grouped by where they're used in `libTidy`, and often in alphabetical order within those groups. Here I've added them relative to where they were placed in the other enums and structs.

Depending on which of the output routines you use (consult `message.c`) you may be able to use parameters such as `%u` and `%s` in your format strings. The available data is currently limited to the available message output routines. Please don't use `printf` for message output within **libTidy**.


eof;
