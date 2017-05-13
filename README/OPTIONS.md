# Tidy Config Options

Tidy supports a quite large number of configuration options. The full list can be output using `-help-config`. This will show the option to be used either on the command line or in a configuration file, the type of option, and the value(s) that can be used. The current default value for each option can be seen using `-show-config`.

The options can also be listed in xml format. `-xml-help` will output each option plus a description. `-xml-config` will not only output the option and a desciption, but will include the type, default and examples. These xml outputs are used, with the aid of `xsltproc` and `doxygen`, to generate the [API Documentation](http://api.html-tidy.org/).

These options can also be used by application linking with `libtidy`. For each option there is a `TidyOptionId` enumeration in the `tidyenum.h` file, and get/set functions for each option type.

This file indicates how to add a new option to tidy, here adding an option `TidyEscapeScripts`. In essence it consists of 4 steps:

 1. Add the option `ID` to `tidyenum.h`.
 2. Add to the `table` `TidyOptionImpl option_defs[]` in `config.c`
 3. Add the id, with a `description` to `language_en.h`
 4. Use the option in the code.
 
#### 1. Option ID

In `tidyenum.h` the `TidyOptionId` can be in any order, but please try to keep things alphabetical, and keep in mind that `N_TIDY_OPTIONS` must remain the last. Choosing the id name can be any string, but by convention it will commence with `Tidy` followed by brief descriptive text.

Naturally it can not be the same as any exisitng option. That is, it must be unique. And it will be followed by a brief descriptive special doxygen formatted comment. So for this new option I have chosen -

~~~
  TidyEscapeScripts,       /**< Escape items that look like closing tags */
~~~

#### 2. Table Definition

In `config.c`, added in `TidyOptionImpl option_defs[]`. Again it can be in any order, but normally a new option would be added just before the last `N_TIDY_OPTIONS`, which must remain the last.

The structure definition of the table entries is simple -

~~~
struct _tidy_option
{
    TidyOptionId        id;
    TidyConfigCategory  category;   /* put 'em in groups */
    ctmbstr             name;       /* property name */
    TidyOptionType      type;       /* string, int or bool */
    ulong               dflt;       /* default for TidyInteger and TidyBoolean */
    ParseProperty*      parser;     /* parsing method, read-only if NULL */
    PickListItems*      pickList;   /* pick list */
    ctmbstr             pdflt;      /* default for TidyString */
};
~~~

Naturally it will commence with the above chosen unique `id`.

The `category` will be one of this enumeration -

~~~
typedef enum
{
  TidyMarkup,          /**< Markup options: (X)HTML version, etc */
  TidyDiagnostics,     /**< Diagnostics */
  TidyPrettyPrint,     /**< Output layout */
  TidyEncoding,        /**< Character encodings */
  TidyMiscellaneous,   /**< File handling, message format, etc. */
  TidyInternalCategory /**< Option is internal only. */
} TidyConfigCategory;
~~~

Care, each of these enumeration strings have been equated to 2 uppercase letters. If you feel there should be another `category` or group then this can be discussed, and added.

The `name` can be anything, but should try to be somewhat descriptive of the option. Again this string must be unique. It should be lowercase alphanumeric characters, and can contain a `-` separator. Remember this is the name places on the command line, or in a configuration file to set the option.

The `type` is one of the following enumeration items -

~~~
typedef enum
{
  TidyString,          /**< String */
  TidyInteger,         /**< Integer or enumeration */
  TidyBoolean          /**< Boolean flag */
} TidyOptionType;
~~~

Care, each of these enumeration strings have been equated to two uppercase letters. If you feel there should be another `type` then this can be discussed, but would require other additional things. And also note the `TidyTriState` is the same as a `TidyInteger` except uses its own parser.

The next item is the `default` value for a boolean, tristate or integer. Note tidy set `no=0` and `yes=1` as its own `Bool` enumeration.

There are a number of `parser` for the options. Likewise a number of `pickList`. Find another option similar to your new option and use the same values. The `parser` is the function that parses config file or command line text input, and the `picklist` constitutes the canonical values for the option. Some types of values logically don't have picklists, such as strings or pure integers.

Presently no options have the final `default` string, and it is left out of the table. The compiler will add a NULL.

The final table entry added. Note in here the spacing has been compressed, but in the actual code the current column settings should be maintained if possible -

~~~
  { TidyEscapeScripts, PP, "escape-scripts", BL, yes, ParseBool, boolPicks[, NULL] }, /* 20160227 - Issue #348 */
~~~

#### 3. Option Description

In `language_en.h`, in the section labelled **Options Documentation**. Please try to keep this in alphabetical order.

Each entry is a structure with 3 members -
~~~
typedef struct languageDictionaryEntry {
    uint key;
    uint pluralForm;
    ctmbstr value;
} languageDictionaryEntry;
~~~

The `key` is the option `ID`; The `pluralForm` is not used for options, and should be `0`; The `value` is the description string.

Some care has to be taken with the description string. The only html allowed here is `<code>...</code>`, `<var>...</var>`, `<em>...</em>`, `<strong>...</strong>`, and `<br/>`. Entities, tags, attributes, etc., should be enclosed in `<code>...</code>`. Option values should be enclosed in `<var>...</var>`. It's very important that `<br/>` be self-closing! This string is processed to build the API documentation.

This is the desription added for this new option.

~~~
    {
      TidyEscapeScripts,          0,
        "This option causes items that look like closing tags, like <code>&lt;/g</code> to be "
        "escaped to <code>&lt;\\/g</code>. Set this option to 'no' if you do not want this."
    },
~~~

#### 4. Use in Code

This can be added anywhere in the code to change the current code action. While the testing of the option depends on the option type, the most common is `cfgBool( doc, id )`. Here is an example of where this new option is used -

~~~
    /*\ if javascript insert backslash before / 
     *  Issue #348 - Add option, escape-scripts, to skip
    \*/
    if ((TY_(IsJavaScript)(container)) && cfgBool(doc, TidyEscapeScripts))
    {
~~~

#### Summary

That's about it. Just 4 places. Obviously the best idea it to search for an existing option `ID`, and follow where it is all defined and used, and copy that. It is not difficult.

; eof 20160310
