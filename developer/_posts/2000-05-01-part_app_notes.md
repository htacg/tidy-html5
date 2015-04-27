---
title:    "App Notes"
bg:       "#AAAAAA"
color:    black    
style:    left
fa-icon:  comment-o
---


## Application Notes

Of course, there are functions to parse and save both markup and
configuration files. For the adventurous, it is possible to create
new input sources and output sinks. For example, a URL source could
pull the markup from a given URL.

It is also worth remembering that an application may instantiate
_**any number**_ of document and buffer objects. They are fairly
cheap to initialize and destroy (just memory allocation and zeroing,
really), so they may be created and destroyed locally, as needed.
There is no problem keeping them around a while for keeping state.
For example, a server app might keep a global document as a master
configuration. As documents are parsed, they can copy their
configuration data from the master instance.
See `tidyOptCopyConfig()`. If the master copy is initialized at
startup, no synchronization is necessary.
