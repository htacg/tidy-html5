---
title:    "Use"
bg:       "#B6EFD4"
color:    black    
style:    left
fa-icon:  play-circle
---

# Running Tidy

## Running Tidy in a Terminal (Console)

This is the syntax for invoking **Tidy** from the command line:

`tidy [[options] filename]`

**Tidy** defaults to reading from standard input, so if you run **Tidy** without
specifying the `filename` argument, it will just sit there waiting for input
to read.

**Tidy** defaults to writing to standard output. So you can pipe output
from **Tidy** to other programs, as well as pipe output from other programs to
**Tidy**. You can page through the output from **Tidy** by piping it to a
pager, e.g.:

`tidy file.html | less`

To have **Tidy** write its output to a file instead, either use the

`-o filename` or `-output filename`

option, or redirect standard output to the file. For example:

~~~
tidy -o output.html index.html
tidy index.html > output.html
~~~

Both of those run **Tidy** on the file **index.html** and write the
output to the file **output.html**, while writing any error messages to
standard error.

**Tidy** defaults to writing its error messages to standard error (that is, to
the console where you’re running **Tidy**). To page through the error messages
along with the output, redirect standard error to standard output, and pipe
it to your pager:

`tidy index.html 2>&1 | less`

To have **Tidy** write the errors to a file instead, either use the

`-f filename` or `-file filename`

option, or redirect standard error to a file:

~~~
tidy -o output.html -f errs.txt index.html
tidy index.html > output.html 2> errs.txt
~~~

Both of those run **Tidy** on the file **index.html** and write the
output to the file **output.html**, while writing any error messages to
the file **errs.txt**.

Writing the error messages to a file is especially useful if the file you
are checking has many errors; reading them from a file instead of the
console or pager can make it easier to review them.

You can use the or `-m` or `-modify` option to modify (in-place) the contents
of the input file you are checking; that is, to overwrite those contents with
the output from **Tidy**. For example:

`tidy -f errs.txt -m index.html`

That runs **Tidy** on the file **index.html**, modifying it in place
and writing the error messages to the file **errs.txt**.

**Caution:** If you use the `-m` option, you should first ensure that you have a
backup copy of your file.


## Running Tidy in Scripts

If you want to run **Tidy** from a Perl, bash, or other scripting language
you may find it of value to inspect the result returned by **Tidy**
when it exits: `0` if everything is fine, `1` if there were warnings
and `2` if there were errors. This is an example using Perl:

~~~
if (close(TIDY) == 0) {
  my $exitcode = $? &gt;&gt; 8;
  if ($exitcode == 1) {
    printf STDERR "tidy issued warning messages\n";
  } elsif ($exitcode == 2) {
    printf STDERR "tidy issued error messages\n";
  } else {
    die "tidy exited with code: $exitcode\n";
  }
} else {
  printf STDERR "tidy detected no errors\n";
}
~~~
