# README.md - Localize HTML Tidy

Thank you for your interest in helping us localize HTML Tidy and LibTidy. Users
throughout the world will thank you.

The document describes Tidy's localization philosophy and instructs you on how
you can use standard `gettext` tools to generate language and region
localizations that will work with Tidy. Optionally instructions are included in
the event that you want to build Tidy with your new language.

## Contents:
- [Introduction](#introduction)
  - [PO and POT files](#po-and-pot-files)
  - [H files](#h-files)
  - [Differences for translators](#differences-for-translators)
  - [`poconvert.rb` versus `gettext`' tools](#poconvertrb-versus-gettext-tools)
- [How to Contribute](#how-to-contribute)
  - [Find or Create the Translation Files](#find-or-create-the-translation-files)
  - [Issue a Pull Request to HTML Tidy](#issue-a-pull-request-to-html-tidy)
  - [Using Git appropriately](#using-git-appropriately)
  - [Repository Notes](#repository-notes)
- [Adding Languages to Tidy](#adding-languages-to-tidy)
- [Best Practices](#best-practices)
  - [Language Inheritance](#language-inheritance)
  - [String Inheritance](#string-inheritance)
  - [Base Language First and Regional Variants](#base-language-first-and-regional-variants)
  - [Positional Parameters](#positional-parameters)
- [Testing](#testing)
  - [Command line option](#command-line-option)
  - [Changing your locale](#changing-your-locale)
  - [East Asian Languages](#east-asian-languages)
- [gettext](#gettext)
- [poconvert.rb](#poconvertrb)
  - [Create a new POT file](#create-a-new-pot-file)
  - [Create a new POT file with non-English `msgid` strings](#create-a-new-pot-file-with-non-english-msgid-strings)
  - [Convert an existing H to PO](#convert-an-existing-h-to-po)
  - [Convert an existing H to PO using a different `msgid` language](#convert-an-existing-h-to-po-using-a-different-msgid-language)
  - [Create a blank PO file for a particular region](#create-a-blank-po-file-for-a-particular-region)
  - [Create a Tidy Language Header H file](#create-a-tidy-language-header-h-file)
  - [Prepare your non-English PO for a PR](#prepare-your-non-english-po-for-a-pr)
  - [Update your PO to match the new POT](#update-your-po-to-match-the-new-pot)
- [Help Tidy Get Better](#help-tidy-get-better)

  
## Introduction

HTML Tidy is built around the localization file `language_en.h`; without this
file HTML Tidy will not work. As such _all_ language localization work
originates from this single file.

Language localizations use header files that are identical to `language_en.h`,
except that they have different strings. For the convenience of language
translators, though, Tidy source code includes a Ruby `poconvert.rb` script
that enables _optional_ gettext PO/POT work streams that may be more comfortable
to them.


### PO and POT files
HTML Tidy provides PO and POT files for language translations. The file 
`tidy.pot` is the correct template to use as a basis for new translations. In a
typical `gettext` workflow a translator will use the `tidy.pot` file to create a
language translation PO file that contains original English strings and the
translated strings.

If a language has already been translated (or if the translation has begun) then
PO files may already exist. These files are named `language_ll.po` or
`langage_ll_CC.po`, where `ll` represents the language code, and optionally,
`CC` represents the region code of the translation.

Tidy does not use MO files that `gettext` tools generate from PO files.

Please note that these PO and POT files are provided for translator convenience
only. Tidy's [header files](#h-files) constitute the true, controlled source
code for Tidy.


### H files

Tidy does not use `gettext` to display strings and so `gettext`-generated MO
files are not necessary. Instead translated PO files must be converted to Tidy's
language header H file format. Translators are not required to perform this
step, but we provide a tool to perform this function if desired.


### Differences for translators

Experienced users and translators of PO files may note that we use the PO file's
`msgctxt` field a bit uniquely. Rather than point to a line in the source code,
it contains a reference to the string's identifier. Because the PO format does
not allow for arbitrary metadata this is a requirement for generating our
header files.

If you're the type of translator the does dig into the source code, then this
`msgtext` symbol is still useful to you and adds a single extra step to finding
where a string is in context: a symbol or string search using the `msgctxt`
value will reveal the context in source code.

Finally the `msgid` field is a throwaway; Tidy's language tools do not use this
value and so it's only for the translator's convenience. This fact makes it
convenient for translators to translate from languages other than English,
which is fully supported by our tools.


### `poconvert.rb` versus `gettext`' tools

Please don't use `gettext`' tools with our PO and POT files (unless you are
using our strings for a different project). Instead all workflows can be
accomplished with our `poconvert.rb` tool.

[More information about this tool](#h-files) can be found below.


## How to Contribute

### Find or Create the Translation Files
If you've not already cloned the HTML Tidy source code repository that will be
your first step.

In the `localize\translations\` directory you can find existing languages, e.g.,

  - `tidy.pot` (Tidy's POT template for translations).
  - `language_en_gb.po` (British English variants for the built in language)
  - …and perhaps more.
  
In the `src\` directory you can find the master files for existing languages,
e.g.,

 - `language_en.h` (Tidy's native, built-in language, mostly U.S. English)
 - `language_en_gb.po` (British English variants for the built in language)
 - …and perhaps more.
 
Although the header files are the master files for HTML Tidy, we understand that
not all potential translators want to edit C files directly. Therefore as an
option, the following workflow to use POT and PO files is offered.

If the language that you want to work on is already present:

  - Simply open the file in your favorite PO editor and then get to work.
  - Note that although you can use a text editor, we recommend that you use a
    dedicated PO editor so that you don't accidentally make the file illegible
    to our conversion utility.
    
If the language that you want to work on is _not_ already present:

  - You can open `tidy.pot` in your favorite PO editor and use its functions
    to begin a new translation into your desired language.
  - Note that although you can use a text editor, we recommend that you use a
    dedicated PO editor so that you don't accidentally make the file illegible
    to our conversion utility.
  - To perform the work manually:
    - Copy `tidy.pot` to `language_ll.po` (for a non-regional variant, or base
      language), or to `language_ll_cc.po` (for a region-specific variant),
      where `ll` indicates the two letter language code and `cc` indicates the
      two letter region or country code.
    - Change the pertinent PO header section accordingly.
  - Use `poconvert.rb` to generate a PO:
    - `poconvert.rb msginit --locale ll`, where `ll` indicates the language
      code for the language you want to translate to. The tool recognizes the
      same languages as `gettext`' `msginit`. If your chosen language is not
      supported, then please see the manual method, above.
    - See also `poconvert.rb help` for more options.
  - See GNU's [The Format of PO Files](https://www.gnu.org/software/gettext/manual/html_node/PO-Files.html)
    for more specific instructions and important information.

### Issue a Pull Request to HTML Tidy

Once your translation is complete commit your entire HTML Tidy repository to
GitHub and issue a pull request (PR) against the `master` branch. If accepted a
friendly developer will convert your PO into a format useful to Tidy if your
PR is a PO, or will simply merge your changed header file if you changed it
directly.

You are also welcome to perform any conversions yourself, add new languages to
Tidy, and issue a PR for the whole change.


### Using Git appropriately

 1. Fork the repository to your GitHub account.
 2. Optionally create a **topical branch** - a branch whose name is succinct but
    explains what you're doing, such as "localize Portuguese".
 3. Make your changes, committing at logical breaks.
 4. Push your work to your personal account.
 5. [Create a pull request](https://help.github.com/articles/using-pull-requests).
 6. Watch for comments or acceptance.


### Repository Notes

If you are working with PO files then please **only** commit PO files with 
_English_ `msgid` fields. The `gettext` convention specifies only English 
`msgid`, and other translators may not understand the original strings.

Our `poconvert.rb` script can generate PO files using another language as
`msgid`. This can be very useful if it's easier for you to translate from
another language instead of English. It can also be useful for translating from
a base language to a regional variant, such as from Spanish to Mexican Spanish.

If you choose to work locally with a non-English PO, you can easily convert
your PO to a Tidy header file and back to an English-based PO using our
`poconvert.rb` script. See its documentation (`poconvert.rb help`) for
instructions.


## Adding Languages to Tidy

Although we don't require you to follow these steps to contribute a language
to Tidy, you may want to add the language to Tidy yourself to test the
translation, or to save one of the developer team a few extra steps.

  - Generate the header files if necessary:
    - Convert your PO file to a Tidy header file by executing
      `poconvert.rb msgfmt <path_to_your_file.po>`. Note that on Windows you
      will likely have to preface this line with `ruby`.
    - The tool should generate a file named `language_ll_cc.h` in the working
      directory, where `ll_cc` will be replaced with the language/region of your
      translation.
    - Copy this `.h` file into `src\`.
  - Modify Tidy's source:
    - Edit the file `src\language.c` to ensure that the new `.h` file you added
      is in the `#include` section.
    - Look for the `static tidyLanguagesType tidyLanguages` structure starting
      near line 40, and look for the comment `These languages are installed.`.
      You can add your new language to the list along with the other languages
      present, following the same format.
  - Build Tidy:
    - Build Tidy per the usual instructions, and try it out using the `-lang`
      option.
    

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


### Base Language First and Regional Variants

Because of this inheritance we hope to localize base languages first, as the
only strings then required for regional variants are the strings that differ.
This will help us keep HTML Tidy and `libtidy` small.

If you are working on a regional variation (such as “us_CA”) please only
localize strings that are actually _different_ from the base language!


### Positional Parameters

Please note that HTML Tidy does not currently support positional parameters. Due
to the nature of most of Tidy's output, it's not expected that they will be
required. In any case, please translate strings so that substitution values are
in the same order as the original string.


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

### East Asian Languages

East Asian languages are completely supported and have been tested on Linux,
Mac OS X, and Windows, although Windows requires you to set your operating
system (not the console locale!) to an East Asian locale to enable this in
Windows Console and PowerShell. Note that PowerShell ISE always supports East
Asian languages without requiring you to change your operating system locale.


## gettext

Although HTML Tidy uses `gettext`-compatible tools and PO files for language
localization, Tidy itself does _not_ use `gettext`. Tidy's build philosophy is
build it anywhere and build it with anything. As `gettext` is not universally
available on every platform under the sun, Tidy cannot count on `gettext`.

Instead Tidy builds all translations into its library (and command line
executable if built monolithically), and can run on virtually any general
purpose computer with any operating system.

While this does not pose a significant problem for storage or execution space
on modern PC's, we understand that certain applications may still be space
critical. As such it's trivial to build Tidy without this extra language
support using the `-DSUPPORT_LOCALIZATIONS=NO` switch.


## poconvert.rb

Tidy's source code includes a Ruby batch file called `poconvert.rb` which can be
used to generate POT, PO, and H files, and convert them back and forth. It has
been designed to work in a similar fashion as `gettext`'s tools, and includes
conveniences that let translators work in different source languages. Please
use `poconvert.rb help` for complete information (`ruby poconvert.rb help` on
Windows).

Note that you must install Ruby on your system, as well as install the required
dependencies. These can be manually installed with `[sudo] gem install xxx`,
where `xxx` represents the packages listed in `Gemfile`. For convenience, if you
have the Bundler gem installed, you can `bundle install` for automated
dependency installation.

Also take note of these two important characteristics:

- `poconvert.rb` is currently dependent on its current path. You can move it
  from its current location, but you will have to change the values of the
  `@@default_en` and `@@header_template` variables within the script.
- All files will be output in the current working directory. This will prevent
  accidental overwrites of important files while we all get used to the
  workflows.

Below are some sample workflows.


### Create a new POT file

Although we provide `tidy.pot` in the source, you can generate your own.

`./poconvert.rb xgettext`

This will put a fresh, new copy of `tidy.pot` in the working directory.


### Create a new POT file with non-English `msgid` strings

Although `gettext` officially recognizes English as the one, true source
language for PO and POT files, if you're more comfortable translating from a
non-English language, we can support you.

`./poconvert.rb xgettext <language_cc_ll.h>`

Where `<language_cc_ll.h>` is the path to an existing Tidy language header file.
This will produce a `tidy.pot` using the translated strings as `msgid`, using
English as a backup when translated strings are not present.

This can be valuable in producing regional variant translations, e.g., when
translating from `es` to `es_mx`.


### Convert an existing H to PO

In many cases you may want to have a fresh PO generated from a Tidy H file.
This can be accomplished with:

`./poconvert.rb msgunfmt <language_cc_ll.h>`


### Convert an existing H to PO using a different `msgid` language

If you want to generate a fresh PO file from a Tidy H file, but _also_ want to
have untranslated strings from a language other than English, try:

`./poconvert.rb msgunfmt <language_cc_ll.h> --baselang=<other-language_cc_ll.h>`


### Create a blank PO file for a particular region

`./poconvert.rb msginit`
or
`./poconvert.rb msginit --locale=LOCALE`

The first example will try to guess your current region, and the second will
use a region specified.

Tidy only knows about the same regions that `gettext` knows; if our `msginit`
does not recognize the region you specify, you will have to create a new PO
and modify the region settings yourself.

To create the blank PO using `msgid` strings from a different Tidy language,
you can use:

`./poconvert.rb msginit <language_cc_ll.h> [--locale=LOCALE]`


### Create a Tidy Language Header H file

When you're ready to include the language in Tidy, you can generate its header
file with:

`./poconvert.rb msgfmt <language_cc_ll.po>`

In the event you are creating a regional variant of a language, it's an
excellent idea to have Tidy exclude strings that are already present in the
parent language in order to reduce library and executable size. For example
if `es` already includes the string "archivo" there is no reason for your
translation to `es_mx` to include it, too. You can tell `poconvert.rb` to
exclude strings matching another localization like so:

`./poconvert.rb msgfmt <language_cc_ll.po> --baselang=<other-language_cc_ll.h>`


### Prepare your non-English PO for a PR

Although we have provided tools to allow you to work in languages other than
English, we can only accept PO's in the repository that have English `msgid` 
fields. It's easy to convert your PO back to English:

`./poconvert msgfmt <language_cc_ll.po>` 

`./poconvert msgunfmt <language_cc_ll.h>`

The first command converts your non-standard PO into a Tidy Language Header
file, and the second will create a fresh, new PO file from the header that
you've just created.


### Update your PO to match the new POT

If Tidy's POT changes, e.g., new strings are added, new comments, etc., the
simplest way to update your PO is to convert it to a header (which normalizes
it to the latest Tidy standard), and then convert the header to a new PO again.

`./poconvert msgfmt <language_cc_ll.po>` 

`./poconvert msgunfmt <language_cc_ll.h>`


## Help Tidy Get Better

It goes without saying **all help is appreciated**. We need to work together to
make Tidy better!
