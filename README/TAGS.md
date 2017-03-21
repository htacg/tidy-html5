# Tidy HTML Elements

This is about adding a new HTML **tag**.

Tidy tries to support all **tags** supported by the W3C. To add a new supported **tag**, the defintion begins in `tidyenum.h`, to give it a value. Then it is added to the `tag_defs[]` table in `tags.c`, where it is given a unique string, supported html versions, attributes support, and a bit `type`.

Note, there are a group of configuration options to add **tags** not yet approved by the W3C. These are [new-blocklevel-tags](http://api.html-tidy.org/tidy/quickref_5.2.0.html#new-blocklevel-tags), [new-empty-tags](http://api.html-tidy.org/tidy/quickref_5.2.0.html#new-empty-tags), [new-inline-tags](http://api.html-tidy.org/tidy/quickref_5.2.0.html#new-inline-tags). and [new-pre-tags](http://api.html-tidy.org/tidy/quickref_5.2.0.html#new-pre-tags). This provides a way to extend the `tag_defs[]` table just for that tidy session.

So, adding a new HTML **tag** consists of the following simple steps:

 1. `tidyenum.h` - Give the element an internal name, like `TidyTag_XXXX`, and thus a value. Please keep this list in alphabetical order.

 2. `tags.c` - Add a line to the `tag_defs[]` table. This assigns the unique string value of the element. Then the html versions that support the element, a pointer to the attributes supported by that elelment, and a bit field of the elements characteristics, inline, block, etc.
 
So, just changing 2 files, `tidyenum.h` and `tags.c`, and libTidy will now support that element, tag, as W3C approved. Simple... And at times, there is some case for adding **tags** that are still in the `Working Draft` stage, especially when there has been wide spread support in the community, even before it reaches `REC` stage.

Now, one could argue that this is not the **best** way to verify every attribute and value, for every tag, but that is a moot point - that is how tidy does it!

; eof 20170205
