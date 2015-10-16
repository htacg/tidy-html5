---
title:    "Configure"
bg:       "#9CFFD9"
color:    black    
style:    left
fa-icon:  gears
---

# Tidy Options and Configuration

## From the Terminal (Console)

To get a list of available options, use:

`tidy -help`

To get a list of all configuration settings, use:

`tidy -help-config`

To read the help output a page at time, pipe it to a pager, e.g.,:

~~~
tidy -help | less
tidy -help-config | less
~~~

Single-letter options other than `-f` may be combined; for example:

`tidy -f errs.txt -imu foo.html`


## Using a configuration file

The most convenient way to configure **Tidy** is by using separate configuration
file.

Assuming you have created a **Tidy** configuration file named **config.txt**
(the name and extension don’t matter), you can instruct **Tidy** to use it via
the command line option `-config config.txt`; for example:

`tidy -config config.txt file1.html file2.html`

Alternatively, you can name the default config file via the environment variable
named `HTML_TIDY`, the value of which is the absolute path for the config file.

You can also set config options on the command line by preceding the name of the
option immediately (no intervening space) with the string "`--`"; for example:

`tidy --break-before-br true --show-warnings false`

You can find Quick Reference documentation for your version of **Tidy** that describe the
full set of configuration options on our [API and Quick Reference Page][1].


## Sample Configuration File

The following is an example of a **Tidy** config file.

~~~
// sample config file for HTML tidy
indent: auto
indent-spaces: 2
wrap: 72
markup: yes
output-xml: no
input-xml: no
show-warnings: yes
numeric-entities: yes
quote-marks: yes
quote-nbsp: yes
quote-ampersand: no
break-before-br: no
uppercase-tags: no
uppercase-attributes: no
char-encoding: latin1
new-inline-tags: cfif, cfelse, math, mroot,
  mrow, mi, mn, mo, msqrt, mfrac, msubsup, munderover,
  munder, mover, mmultiscripts, msup, msub, mtext,
  mprescripts, mtable, mtr, mtd, mth
new-blocklevel-tags: cfoutput, cfquery
new-empty-tags: cfelse
~~~

[1]: {{ site.baseurl }}/api/#part_quickref