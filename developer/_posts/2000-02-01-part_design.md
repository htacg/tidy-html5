---
title:    "Design"
bg:       "#DDDDDD"
color:    black    
style:    left
fa-icon:  lightbulb-o
---

# Design factors

- **TidyLib** is easy to integrate. Because of the near universal adoption
  of C linkage, a C interface may be called from a great number of programming
  languages.

- **TidyLib** was designed to use opaque types in the public interface. This
  allows the application to just pass an integer around and the need to
  transform data types in different languages is minimized. As a results it’s
  straight-forward to write very thin library wrappers for C++, Pascal,
  and COM/ATL.

- **TidyLib** eats its own dogfood. **HTML Tidy** links directly to **TidyLib**.

- **TidyLib** is Thread Safe and Re-entrant. Because there are many uses for
  HTML Tidy - from content validation, content scraping, conversion to XHTML -
  it was important to make **TidyLib** run reasonably well within server
  applications as well as client side.

- **TidyLib** uses adaptable I/O. As part of the larger integration strategy it
  was decided to fully abstract all I/O. This means a (relatively) clean
  separation between character encoding processing and shovelling
  bytes back and forth. Internally, the library reads from
  _sources_ and writes to _sinks_. This abstraction is used for
  both markup and configuration “files”. Concrete implementations
  are provided for file and memory I/O, and new sources and sinks
  may be provided via the public interface.
