Documentation HOWTO                 {#docs_howto}
========================
Instructions for generating documentation

\note For linking to these docs, the doxygen tag file is  `tidy.tags`

**HTML Tidy** provides several types of documentation to suit different purposes. This
document describes how to generate the following:

- `tidylib_api/` (directory)

 - This collection of documents describes the **TidyLib** API and is generated from the
   comments and code in the **Tidy** source code.
   
- `quickref.html`

 - This document provides a nice, readable HTML document describing all of the options and
   settings that you can use with **Tidy** and internally in **TidyLib**.
   
- `tidy.1`

 - This document is a Mac/Linux/Unix standard `man` page.
 
 
## The easy way

In this directory you can find the shell script `build_docs.sh`, and that will build all
of the documentation into the `temp/` directory (i.e., `{tidy}/build/documentation/temp`).

Please note these prerequisites:

- It's a Mac/Linux/Unix shell script.
- Doxygen is required to generate the API documentation.
- xsltproc is required to generate the man page and the `quickref.html` file.

If you prefer to understand how to do this manually (for example, for integration into
other scripts, build systems, or IDEs), read on.


## Manually

 
### `tidylib_api/` (directory)

If you want to build the API documentation you must have [doxygen][1] installed.
You can clone the [repository from github][2] if it is not currently installed.

Building as simple as:

~~~
cd {tidy}/build/documentation/
doxygen doxygen.cfg
~~~

This will result in a document set in `{tidy}/build/documentation/temp/tidylib_api`,
where you can find the main `index.html` file.


### `quickref.html`

Note that these instructions require the standard `xsltproc` utility to build the file,
but any XSLT processor of your choice should work, too.

- `tidy -xml-config > "tidy-config.xml"`

 - This uses your up-to-date version of **Tidy** to generate an XML file containing all
   of **Tidy**’s built-in settings and their descriptions. This file is only temporary,
   as it will be transformed in the next step.

- `xsltproc "quickref.xsl" "tidy-config.xml" > "quickref.html"`

 - This examples uses the `xsltproc` command to transform `tidy-config.xml` using the
   rules in the `quickref.xsl` stylesheet, and output it to `quickref.html`.
   


### `tidy.1`

Note that these instructions require the standard `xsltproc` utility to build the file,
but any XSLT processor of your choice should work, too.

- `tidy -xml-config > "tidy-config.xml"`

 - This uses your up-to-date version of **Tidy** to generate an XML file containing all
   of **Tidy**’s built-in settings and their descriptions. This file is only temporary,
   as it will be transformed in the third step.

- `tidy -xml-help > "tidy-help.xml"`

 - This uses your up-to-date version of **Tidy** to generate an XML file containing all
   of **Tidy**’s built-in help information. This file is only temporary,
   as it will be transformed in the next step.

- `xsltproc "tidy1.xsl" "tidy-help.xml" > "tidy.1"`

 - This examples uses the `xsltproc` command to transform `tidy-help.xml` using the
   rules in the `tidy1.xsl` stylesheet, and output it to `tidy.1`.
   
   \note Note that `tidy1.xls` includes the file `tidy-config.xml` as part of the stylesheet,
   and so although it does not appear in the command invocation, it is indeed required.



 [1]: http://www.stack.nl/~dimitri/doxygen/
 [2]: https://github.com/doxygen/doxygen
