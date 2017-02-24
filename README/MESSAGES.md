# Message System

Tidy has quite complex warning/error messaging system. This is all about adding a **new** warning or error message to **libTidy**.

First assign the message a key value. This is done in `message.h`, in one of the two enumerations that are listed there.

 1. `tidyErrorCodes` - starts with the value `CODES_TIDY_ERROR_FIRST = 200`, and it must be first. 
 
 2. `tidyMessagesMisc` - starts with the value ACCESS_URL = 2048 - so, at present the above `tidyErrorCodes` must not exceed this.
 
 3. For the sake of completeness, there's also a third enum present in `access.h` called `accessErrorCodes`; you should only ever be concerned about this if you are working on new strings for Tidy's accessibility module.
 
If your message is something that will appear in the error list, then its key should be defined in the `tidyErrorCodes` enum, unless you are adding errors to the accessibility module (see point 3, above). If you are adding strings that are _not_ intended for the error list, then they belong in `tidyMessagesMisc`. These are strings that are typically output with Tidy's CLI.
 
All enum values are only ever used by name within **libTidy** (and incidentally, should only ever be used by name in your client applications; never trust the value!), so feel free to enter new strings wherever they make the most sense. There are already existing categories (marked by comments), or feel free to create a new category if that's best.

Because some clients retrieve error information via `libTidy`’s callback mechanism, it's also important to update the `language.c:tidyErrorFilterKeysStruct[]`, as well, if your new messages are intended for the error list.


## Step 1

So in this case I want to add 3 warning messages: `BAD_SURROGATE_PAIR`, `BAD_SURROGATE_TAIL`, and `BAD_SURROGATE_LEAD`. Because these are error messages, they belong in the `tidyErrorCodes` enum, and they fit into nicely into the "character encoding errors" category just before the **last** `CODES_TIDY_ERROR_LAST`.


## Step 2

Because the new messages are error code, update the `tidyErrorFilterKeysStruct` in `language.c` with the same key values, and with string representations thereof. You should put them in the same logical order as you inserted them into `tidyErrorCodes` enum.

Note that at some point when all of the error enums are merged (probably Tidy 5.5) this kludge won't have to be used and we can have a nice, single enum exported to clients.

## Step 3

The next step is adding a `format` string to `language_en.h`. This string may later be translated to various supported language strings, but at present it is important that the other language translated strings, like `language_fr.h`, `language_es.h`, etc, keep the same format order.

Where to add this seems a bit of a mess, but in general things are grouped by where they're used in `libTidy`, and often in alphabetical order within those groups. Here I've added them relative to where they were placed in the other enums and structs.

Depending on which of the output routines you use (consult `message.c`) you may be able to use parameters such as `%u` and `%s` in your format strings. The available data is currently limited to the available message output routines, but perhaps generalizing this in order to make more data available will be a nice focus of Tidy 5.5. Please don't use `printf` for message output within **libTidy**.


eof;
