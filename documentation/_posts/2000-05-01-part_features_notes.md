---
title:    "Featured"
bg:       "#7CE577"
color:    black    
style:    left
fa-icon:  file-code-o
---

# Featured Options and Solutions

## Indenting output for readability

Indenting the source markup of an HTML document makes the markup easier
to read. **Tidy** can indent the markup for an HTML document while recognizing
elements whose contents should not be indented. In the example below, **Tidy**
indents the output while preserving the formatting of the `<pre>` element:

Input:

~~~
<html>
 <head>
 <title>Test document</title>
 </head>
 <body>
 <p>This example shows how Tidy can indent output while preserving
 formatting of particular elements.</p>

 <pre>This is
 <em>genuine
       preformatted</em>
    text
 </pre>
 </body>
 </html>
~~~

Output:

~~~
<html>
  <head>
    <title>Test document</title>
  </head>

  <body>
    <p>This example shows how Tidy can indent output while preserving
    formatting of particular elements.</p>
<pre>
This is
<em>genuine
       preformatted</em>
   text
</pre>
  </body>
</html>
~~~

**Tidy**’s indenting behavior is not perfect and can sometimes cause your
output to be rendered by browsers in a different way than the input.
You can avoid unexpected indenting-related rendering problems by setting
`indent:no` or `indent:auto` in a config file.


## Preserving original indenting not possible

**Tidy** is not capable of preserving the original indenting of the markup
from the input it receives. That’s because **Tidy** starts by building a clean
parse tree from the input, and that parse tree doesn’t contain any
information about the original indenting. **Tidy** then pretty-prints the parse
tree using the current config settings. Trying to preserve the original
indenting from the input would interact badly with the repair operations
needed to build a clean parse tree, and would considerably complicate the
code.


## Encodings and character references

**Tidy** defaults to assuming you want output to be encoded in UTF-8.
But **Tidy** offers you a choice of other character encodings: US ASCII, ISO
Latin-1, and the ISO 2022 family of 7 bit encodings.

**Tidy** doesn't yet recognize the use of the HTML `<meta>` element for
specifying the character encoding.

The full set of HTML character references are defined. Cleaned-up output
uses named character references for characters when appropriate. Otherwise,
characters outside the normal range are output as numeric character
references.


## Accessibility

**Tidy** offers advice on potential accessibility problems for people using
non-graphical browsers. Have a look at our rescued [HTML Tidy Accessibility
Checker page][1].


## Cleaning up presentational markup

Some tools generate HTML with presentational elements such as `<font>`,
`<nobr>`, and `<center>`. **Tidy**'s `‑clean` option will replace those elements
with `<style>` elements and CSS.

Some HTML documents rely on the presentational effects of `<p>` start
tags that are not followed by any content. **Tidy** deletes such `<p>` tags
(as well as any headings that don’t have content). So do not use `<p>`
tags simply for adding vertical whitespace; instead use CSS, or the
`<br>` element. However, note that **Tidy** won’t discard `<p>` tags that
are followed by any non-breaking space (that is, the `&nbsp;` named
character reference).


## Teaching Tidy about new tags

You can teach **Tidy** about new tags by declaring them in the
configuration file, the syntax is:

~~~
new-inline-tags: tag1, tag2, tag3
new-empty-tags: tag1, tag2, tag3
new-blocklevel-tags: tag1, tag2, tag3
new-pre-tags: tag1, tag2, tag3
~~~

The same tag can be defined as **empty** and as **inline**, or as **empty**
and as **block**.

These declarations can be combined to define a new empty
inline or empty block element, but you are not advised to declare
tags as being both **inline** and **block**.

Note that the new tags can only appear where **Tidy** expects inline
or block-level tags respectively. That means you can’t place
new tags within the document head or other contexts with restricted
content models.


## Ignoring PHP, ASP, and JSTE instructions

**Tidy** will gracefully ignore many cases of PHP, ASP, and JSTE
instructions within element content and as replacements for attributes,
and preserve them as-is in output; for example:

~~~
<option <% if rsSchool.Fields("ID").Value
  = session("sessSchoolID")
  then Response.Write("selected") %>
  value='<%=rsSchool.Fields("ID").Value%>'>
  <%=rsSchool.Fields("Name").Value%>
  (<%=rsSchool.Fields("ID").Value%>)
</option>
~~~

But note that **Tidy** may report missing attributes when those are “hidden”
within the PHP, ASP, or JSTE code. If you use PHP, ASP, or JSTE code to
create a start tag, but place the end tag explicitly in the HTML markup,
**Tidy** won’t be able to match them up, and will delete the end tag.  In that
case you are advised to make the start tag explicit and to use PHP, ASP, or
JSTE code for just the attributes; for example:

 `<a href="<%=random.site()%>">do you feel lucky?</a>`

**Tidy** can also get things wrong if the PHP, ASP, or JSTE code includes
quotation marks; for example:

`value="<%=rsSchool.Fields("ID").Value%>"`

**Tidy** will see the quotation mark preceding `ID` as ending the
attribute value, and proceed to complain about what follows.

**Tidy** allows you to control whether line wrapping on spaces within PHP, ASP,
and JSTE instructions is enabled; see the `wrap-php`, `wrap-asp`,
and `wrap-jste` config options.


## Correcting well-formedness errors in XML markup

**Tidy** can help you to correct well-formedness errors in XML markup. **Tidy**
doesn't yet recognize all XML features, though; for example, it doesn't
understand CDATA sections or DTD subsets.


 [1]: {{ site.baseurl }}/accessibility/