# Message System

Tidy has quite complex warning/error messaging system. This is all about adding a **new** warning or error message to **libTidy**.

First assign the message a key value. This is done in `tidyenum.h`, in one of the two enumerations that are listed there.

 1. `tidyMessageCodes` - starts with the value `tidyMessageCodes_first = 500`, and it must be first. These are messages that appear in Tidy's report list, the list that's emitted telling you what Tidy did to your code. **However** don't modify this enum directly. You'll modify a preprocessor macro instead.
 
 2. `tidyMessagesMisc` - starts with the value `tidyMessagesMisc_first = tidyMessageCodes_last`. These are messages that are emitted that tell you general information, such as further advice.

All enum values are only ever used by name within **libTidy** (and incidentally, should only ever be used by name in your client applications; never trust the value!), so feel free to enter new strings wherever they make the most sense. There are already existing categories (marked by comments), or feel free to create a new category if that's best.

As mentioned above, `tidyMessageCodes` messaged must be defined in one of the existing macros named like `FOREACH_...(FN)`, such as `FOREACH_MSG_ENTITIES(FN)`. These macros ensure that another data structure used for localization and key lookup is updated automatically any time strings are added or removed, thus limiting the possibility of developer error.


## Step 1

So in this case I want to add 3 warning messages: `BAD_SURROGATE_PAIR`, `BAD_SURROGATE_TAIL`, and `BAD_SURROGATE_LEAD`. Because these are error messages, they belong in the `tidyErrorCodes` enum, and they fit into nicely into the macro beginning `FOREACH_MSG_ENCODING(FN)`. 


## Step 2

The next step is adding a `format` string to `language_en.h`. This string may later be translated to various supported language strings, but at present it is important that the other language translated strings, like `language_fr.h`, `language_es.h`, etc, keep the same format order.

Where to add this seems a bit of a mess, but in general things are grouped by where they're used in `libTidy`, and often in alphabetical order within those groups. Here I've added them relative to where they were placed in the other enums and structs.

Depending on which of the output routines you use (consult `message.c`) you may be able to use parameters such as `%u` and `%s` in your format strings. The available data is currently limited to the available message output routines, but perhaps generalizing this in order to make more data available will be a nice focus of Tidy 5.5. Please don't use `printf` for message output within **libTidy**.


eof;
