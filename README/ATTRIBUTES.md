# Tidy Element Attributes

This is about adding a **new** HTML attribute to one or more HTML tags, i.e., a new attribute such as `attribute=value`.

Tidy’s large number of attributes are supported via number of files:

  - `tidyenum.h` is where you first define a new attribute in order to give it an internal value.
  - `attrs.c` is where you give a unique **string** name to the attribute, as well as a **function** to verify the **value**.
  - `attrdict.c` further refines the definition of your attribute, specifying which version(s) of HTML support this attribute.
  - `tags.c`, finally, determines which tags support the attribute, in the `tag_defs[]` table.

So, to add a new `attribute=value`, on one or more existing tags, consists of the following simple steps -

 1. `tidyenum.h` - Give the attribute an internal name, like `TidyAttr_XXXX`, and thus a value. Please try to keep this enumeration in alphabetical order.

 2. `attrs.c` - Assign the string value of the attribute. Of course this must be unique. And then assign a `function` to verify the attribute value. There are already a considerable number of defined functions to verify specific attribute values, but maybe this new attribute requires a new function, so that should be written, and defined.
 
 3. `attrdict.c` - If this attribute only relates to specific tags, then it should be added to their list. There are some general attributes that are allowed on every, or most tags, so this new attribute and value should be added accordingly.
 
 4. `tags.c` - Now the new attribute will be verified for each tag it is associated with in the `tag_defs[]` table. Like for example the `<button ...>`, `{ TidyTag_BUTTON, ...` has `&TY_(W3CAttrsFor_BUTTON)[0]` assigned.

So, normally, just changing 3 files, `tidyenum.h`, `attrs.c`, and `attrdict.c`, will already adjust `tags.c` to accept a new `attribute=value` for any tag, or all tags. Simple...

Now, one could argue that this is not the **best** way to verify every attribute and value, for every tag, but that is a moot point - that is how Tidy does it!

; eof 20170205
