# README.md - Localize HTML Tidy

Thank you for your interest in helping us localize HTML Tidy and LibTidy. Users
throughout the world will thank you.

The document describes Tidy's localization philosophy and instructs you on how
you can use standard `gettext` tools to generate language and region
localizations that will work with Tidy. Optionally instructions are included in
the event that you want to build Tidy with your new language.

## How to Contribute

### Find or Create the Translation Files
If you've not already cloned the HTML Tidy source code repository that will be
your first step.

In the `localize\translations` directory you can find existing languages, e.g.,

  - `tidy.pot` (Tidy's POT template for translations).
  - `language_en_gb.po` (British English variants for the built in language)
  - …and perhaps more.

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
friendly developer will convert your PO into a format useful to Tidy.

You are also welcome to perform the conversion yourself, add the language to
Tidy, and issue a PR for the whole change.


### Using Git appropriately

 1. Fork the repository to your GitHub account.
 2. Optionally create a **topical branch** - a branch whose name is succinct but
    explains what you're doing, such as "localize Portuguese".
 3. Make your changes, committing at logical breaks.
 4. Push your work to your personal account.
 5. [Create a pull request](https://help.github.com/articles/using-pull-requests).
 6. Watch for comments or acceptance.


#### Repository Notes

Please **only** commit PO files with _English_ `msgid` fields. The `gettext`
convention specifies only English `msgid`, and other translators may not
understand the original strings.

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

  - Generate the header files:
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
use `poconvert.rb help` for more information (`ruby poconvert.rb help` on
Windows).


## Help Tidy Get Better

It goes without saying **all help is appreciated**. We need to work together to
make Tidy better!
