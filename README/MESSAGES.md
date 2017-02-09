# Message System

Tidy has quite complex warning/error messaging system. This is all about adding a **new** warning or error message to **libTidy**.

First assign the message a key value. This is done in `message.h`, and there are 2 enumerations listed there...

 1. `tidyErrorCodes` - starts with the value CODES_TIDY_ERROR_FIRST = 200 - must be first. This is the enum into which you should place new string keys. Enum values are only ever used by name, and so please try to find an appropriate category (denoted by comments) or create a new one if applicable.
 
 2. `tidyMessagesMisc` - starts with the value ACCESS_URL = 2048 - so, at present the above `tidyErrorCodes` must not exceed this. Do not add new message keys to this enum.

Note that the `tidyMessagesMisc` enum exists separately due to API exposure that meant some clients were using the values rather than the names. This is likely to change in Tidy HTML 5.5 where we feel it will be appropriate to disregard some old API's.

Because some clients retrieve error information via `libTidy`’s callback mechanism, it's also important to update the `language.c:tidyErrorFilterKeysStruct[]`, as well.


## Step 1

So in this case I want to add 3 warning messages: `BAD_SURROGATE_PAIR`, `BAD_SURROGATE_TAIL`, and `BAD_SURROGATE_LEAD`. So I add these 3 to the `tidyErrorCodes` where they fit into nicely into the "character encoding errors" category just before the **last** `CODES_TIDY_ERROR_LAST` in the `tidyErrorCodes` enum.


## Step 2

Update the `tidyErrorFilterKeysStruct` in `language.c` with the same key values, and with string representations thereof. You should put them in the same logical order as you inserted them into `tidyErrorCodes` enum.

Note that at some point when all of the enums are merged (probably Tidy 5.5) this kludge won't have to be used and we can have a nice, single enum exported to clients.

## Step 3

The next step is adding a `format` string to `language_en.h`. This string may later be translated to various supported language strings, but at present it is important that the other language translated strings, like `language_fr.h`, `language_es.h`, etc, keep the same format order.

Where to add this seems a bit of a mess, but in general things are grouped by where they're used in `libTidy`, and often in alphabetical order within those groups. Here I've added them relative to where they were placed in the other enums and structs.

Depending on which of the output routines you use (consult `message.c`) you may be able to use parameters such as `%u` and `%s` in your format strings. The available data is currently limited to the available message output routines, but perhaps generalizing this in order to make more data available will be a nice focus of Tidy 5.5

In this case I want to add showing the code point(s) in hex, so I need to add that also. (jim --??)







 
