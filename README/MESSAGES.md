# Message System

Tidy has quite complex warning/error messaging system. This is all about adding a **new** warning or error message to **libTidy**.

First assigning the message a value. This is done in `message.h`, and there are 2 enumerations listed there...

 1. `tidyErrorCodes` - starts with the value CODES_TIDY_ERROR_FIRST = 200 - must be first.
 2. `tidyMessagesMisc` - starts with the value ACCESS_URL = 2048 - so, at present the above `tidyErrorCodes` must not exceed this.

Not sure why this separation into two enumerations, and this only deals with adding new `tidyErrorCodes`. Maybe one day this should be a single enumeration, or maybe there is an important distinction between these two types that I do not understand.

So in this case I want to add 3 warning messages, BAD_SURROGATE_PAIR, BAD_SURROGATE_TAIL, and BAD_SURROGATE_LEAD. So I add these 3 to the `tidyErrorCodes`, just before the **last** `CODES_TIDY_ERROR_LAST`. Step 1 done...

The next step is adding a `format` string to `language_en.h`. This string may later be translated to various supported language strings, but at present it is important that the other language translated strings, like `language_fr..h`, `language_es.h`, etc, keep the same format order.

Where to add this seems a bit of a mess, **and** if the format includes more that the `usual` format things like `%u`, `%s`, then you need to account for this...

In this case I want to add showing the code point(s) in hex, so I need to add that also.






 