# Localize HTML Tidy

HTML Tidy is used worldwide but is not very friendly to non-English speakers.
The latest versions of HTML Tidy and `libtidy` now support other languages and
regional variations, but we need your help to make it accessible to these users
by using your knowledge of other languages to make Tidy better.

Help us translate HTML Tidy into another language and as part of our project
team you will certainly earn the admiration of fellow Tidy users worldwide.

## How to Contribute

If you've not already cloned the HTML Tidy source code repository that will be
your first step.

In the `src` directory you can find existing languages, e.g.,

  - `language_en.h` (Tidy's native, built in language).
  - `language_en_gb.h` (British English variants for the built in language)
  - …and perhaps more.

If the language that you want to work on is already present:

  - Simply open the file in your favorite text editor and then get to work.
  - You can reference `language_en.h` (or another completed language) in order
    to understand the context of each of the strings.
    
If the language that you want to work on is _not_ already present:

  - Create a new file in the form of `language_ll_rr.h` where `ll` represents
    the base language and `rr` represents the region, by duplicating one of
    existing languages. The region is optional and we hope very much that we can
    localize the base language first.
  - In the newly copied file please pay attention to the header include guards
    at the very top and bottom of the new file. Update the existing labels with
    new labels appropriate to the language.
  - Also pay attention to the array name on or near line 24, and change it to
    match your new language. For example, change 
    `static languageDictionary language_en` to `static languageDictionary language_en_ca`
    if you are working on a Canadian-English localization.
  - Finally also change the first array value with the `TIDY_LANGUAGE` key to
    the two or five character language code that you are working on.
  - If you want to build Tidy with your new language, add your new file to the
    `#include` section of `language.c` and add your array name to the
    `tidyLanguages.languages` array.

## Best Practices

### Language Inheritance

HTML Tidy will fallback from the specified language to the base language and
then finally to the default English as required. This means, for example, a
programmer might set `libtidy` to use “es_mx”, and if it doesn’t exist Tidy
will automatically use “es”. If that doesn’t exist `libtidy` will continue to
use whatever language it is currently using.

### String Inheritance

HTML Tidy will also fallback for individual strings. For example if `libtidy`
is set to use “es_mx” and a particular string is requested and not found, the
library will look for the string in “es”. If the string is not found there then
the “en” string will be given.

### Base language first

Because of this inheritance we hope to localize base languages first, as the
only strings then required for regional variants are the strings that differ.
This will help us keep HTML Tidy and `libtidy` small.

### Works in Progress (WIP)

In general we can accept WIPs but we would hope that you can submit complete
groups of strings, for example, all of the **Warnings and Errors** section so
that at least major portions of Tidy are consistent.


## Testing

We hope to develop a comprehensive test suite in the future, but in the meantime
you can test localized output like this.

### Command line option

Use the `-lang`/`-language` option and specify a POSIX or Windows language name.
This option should be first option used because the console application parses
and acts on options first-in, first-out.

### Changing your locale

On Unix/Mac and Linux operating systems you can change your shell’s locale
temporarily with:

`export LANG=en_GB`
`export LC_ALL=en_GB`

…substituting, of course the language of your choice.


## Using Git appropriately

 1. Fork the repository to your GitHub account.
 2. Optionally create a **topical branch** - a branch whose name is succint but
    explains what you're doing, such as "localize Portuguese".
 3. Make your changes, committing at logical breaks.
 4. Push your work to your personal account.
 5. [Create a pull request](https://help.github.com/articles/using-pull-requests).
 6. Watch for comments or acceptance.


## Help Tidy Get Better

It goes without saying **all help is appreciated**. We need to work together to
make Tidy! better...
