# Tidy Element Attributes

This is about adding a **new** `attribute=value` for one or more html `element`, here called `tags`.

Tidy supports a large number of `attributes`, first defined in `tidyenum.h`, to give it a value, then defined in `attrs.c` to give it a unique **string** name, and a `function` to verify the atrribute **value**. Then in `attrdict.c` the attribute is defined, giving what version(s) of html support this attribute. Finally, what tags support this attrinute, is done in `tags.c`, where each attribute is allowed on that tag, or not, in the `tag_defs[]` table.

So, to add a new `attribute=value`, on one or more existing tags, consists of the following simple steps -

 1. tidyenum.h - Give the attribute an internal name, like `TidyAttr_XXXX`, and thus a value. While there were some initial steps to keep this `TidyAttrId` enumeration alphabetic, now just add the new `TidyAttr_XXXX` just before the last entry 'N_TIDY_ATTRIBS'.

 2. attrs.c - Assign the string value of the attribute. Of course this must be unique. And then assign a `function` to verify the attribute value. There are already a considerable number of defined functions to verify specific attribute values, but maybe this new attribute requires a new function, so that should be written, and defined.
 
 3. attrdict.c - If this attribute only relates to specific `tags`, then it should be added to their list. There are some `general` attributes that are allowed on every, or most tags, so this new attribute and value should be added accordingly.
 
 4. tags.c - Now the new attribute will be verified for each tag it is associate with in the `tag_defs[]` table. Like for example the `<button ...>`, `{ TidyTag_BUTTON, ...` has `&TY_(W3CAttrsFor_BUTTON)[0]` assigned.

So, normally, just changing 3 files, `tidyenum.h`, `attrs.c`, and `attrdict.c`, will already adjust `tags.c` to accept a new `attribute=value` for any tag, or all tags. Simple...

Now, one could argue that this is not the **best** way to verify every attribute and value, for every tag, but that is a mute point - that is how tidy does it!

; eof 20170205
