#ifndef language_h
#define language_h
/*
 * language.h
 * Localization support for HTML Tidy.
 * This header provides the public (within libtidy) interface
 * to basic localization support. To add your own localization
 * create a new `language_xx.h` file and add it to the struct
 * in `language.c`.
 *
 * (c) 2015 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Created by Jim Derry on 11/28/15.
 */

#include "tidyplatform.h"


/** @name Exposed Data Structures */
/** @{ */

/**
 *  Describes a record for a localization string.
 *  - key must correspond with one of Tidy's enums (see `tidyMessageTypes`
 *    below)
 *  - pluralForm corresponds to gettext plural forms case (not singularity).
 *    Most entries should be case 0, representing the single case.:
 *    https://www.gnu.org/software/gettext/manual/html_node/Plural-forms.html
 */
typedef struct languageDictionaryEntry {
    uint key;
    uint pluralForm;
    ctmbstr value;
} languageDictionaryEntry;


/**
 *  For now we'll just use an array to hold all of the dictionary
 *  entries. In the future we can convert this to a hash structure
 *  which will make looking up strings faster.
 */
typedef languageDictionaryEntry const languageDictionary[600];


/**
 *  Finally, a complete language definition. The item `pluralForm`
 *  is a function pointer that will provide the correct plural
 *  form given the value `n`. The actual function is present in
 *  each language header and is language dependent.
 */
typedef struct languageDefinition {
    uint (*whichPluralForm)(uint n);
    languageDictionary messages;
} languageDefinition;


/**
 *  The function getNextWindowsLanguage() returns pointers to this type;
 *  it gives LibTidy implementors the ability to determine how Windows
 *  locale names are mapped to POSIX language codes.
 */
typedef struct tidyLocaleMapItem {
    ctmbstr winName;
    ctmbstr POSIXName;
} tidyLocaleMapItem;


/**
 *  The function getNextErrorCode() returns pointers to this type; it gives
 *  LibTidy implementors the ability to know what errors can be returned
 *  via `TidyReportFilter3`.
 *  Provides the mapping for LibTidy users to map between an opaque key
 *  and an error message value. See `tidyErrorFilterKeys[]` in `language.c`.
 *  The `key` string is guaranteed by the API (unless deleted entirely). The
 *  `value` is suitable for use in looking up Tidy's strings, but its value
 *  is not guaranteed between releases.
 */
typedef struct tidyErrorFilterKeyItem {
    ctmbstr key;
    int value;
} tidyErrorFilterKeyItem;


/**
 *  Defines all of the possible dictionary keys.
 *  The starting value is arbitrary but must prevent overlaps
 *  with other enums that are used for retrieving strings. The
 *  comprehensive list of enums for which we provides strings
 *  is as follows:
 *    - `tidyMessageTypes` in this file,         start == 4096.
 *    - `tidyErrorCodes` from `message.h`,       start == 200.
 *    - `accessErrorCodes` from `access.h`,      start == CODES_TIDY_ERROR_LAST+1.
 *    - `tidyMessagesMisc` from `message.h`,     start == 2048.
 *    - `TidyOptionId` from `tidyEnum.h`,        start == 0 (important!).
 *    - `TidyReportLevelKeys` from `tidyEnum.h`, start == 600.
 *    - ...
 *  You should never count on the value of a label being
 *  constant. Accordingly feel free to arrange new enum
 *  values in the most appropriate grouping below.
 */
typedef enum
{
    /* This MUST be present and first. */
    TIDY_MESSAGE_TYPE_FIRST = 4096,
    
    /* Specify the code for this language. */
    TIDY_LANGUAGE,
    
    /* Localization test strings. */
    TEST_PRESENT_IN_BASE,
    TEST_PRESENT_IN_REGION,
    
    /* Strings for the console application. */
    TC_CAT_DIAGNOSTICS,
    TC_CAT_ENCODING,
    TC_CAT_MARKUP,
    TC_CAT_MISC,
    TC_CAT_PRETTYPRINT,
    TC_LABEL_COL,
    TC_LABEL_FILE,
    TC_LABEL_LANG,
    TC_LABEL_LEVL,
    TC_LABEL_OPT,
    TC_MAIN_ERROR_LOAD_CONFIG,
    TC_OPT_ACCESS,
    TC_OPT_ASCII,
    TC_OPT_ASHTML,
    TC_OPT_ASXML,
    TC_OPT_BARE,
    TC_OPT_BIG5,
    TC_OPT_CLEAN,
    TC_OPT_CONFIG,
    TC_OPT_ERRORS,
    TC_OPT_FILE,
    TC_OPT_GDOC,
    TC_OPT_HELP,
    TC_OPT_HELPCFG,
    TC_OPT_HELPOPT,
    TC_OPT_IBM858,
    TC_OPT_INDENT,
    TC_OPT_ISO2022,
    TC_OPT_LANGUAGE,
    TC_OPT_LATIN0,
    TC_OPT_LATIN1,
    TC_OPT_MAC,
    TC_OPT_MODIFY,
    TC_OPT_NUMERIC,
    TC_OPT_OMIT,
    TC_OPT_OUTPUT,
    TC_OPT_QUIET,
    TC_OPT_RAW,
    TC_OPT_SHIFTJIS,
    TC_OPT_SHOWCFG,
    TC_OPT_UPPER,
    TC_OPT_UTF16,
    TC_OPT_UTF16BE,
    TC_OPT_UTF16LE,
    TC_OPT_UTF8,
    TC_OPT_VERSION,
    TC_OPT_WIN1252,
    TC_OPT_WRAP,
    TC_OPT_XML,
    TC_OPT_XMLCFG,
    TC_OPT_XMLSTRG,
    TC_OPT_XMLERRS,
    TC_OPT_XMLOPTS,
    TC_OPT_XMLHELP,
    TC_STRING_CONF_HEADER,
    TC_STRING_CONF_NAME,
    TC_STRING_CONF_TYPE,
    TC_STRING_CONF_VALUE,
    TC_STRING_CONF_NOTE,
    TC_STRING_OPT_NOT_DOCUMENTED,
    TC_STRING_OUT_OF_MEMORY,
    TC_STRING_FATAL_ERROR,
    TC_STRING_FILE_MANIP,
    TC_STRING_LANG_MUST_SPECIFY,
    TC_STRING_LANG_NOT_FOUND,
    TC_STRING_MUST_SPECIFY,
    TC_STRING_PROCESS_DIRECTIVES,
    TC_STRING_CHAR_ENCODING,
    TC_STRING_MISC,
    TC_STRING_XML,
    TC_STRING_UNKNOWN_OPTION,
    TC_STRING_UNKNOWN_OPTION_B,
    TC_STRING_VERS_A,
    TC_STRING_VERS_B,
    TC_TXT_HELP_1,
    TC_TXT_HELP_2A,
    TC_TXT_HELP_2B,
    TC_TXT_HELP_3,
    TC_TXT_HELP_CONFIG,
    TC_TXT_HELP_CONFIG_NAME,
    TC_TXT_HELP_CONFIG_TYPE,
    TC_TXT_HELP_CONFIG_ALLW,
    TC_TXT_HELP_LANG_1,
    TC_TXT_HELP_LANG_2,
    TC_TXT_HELP_LANG_3,
    
    /* This MUST be present and last. */
    TIDY_MESSAGE_TYPE_LAST
} tidyMessageTypes;


/**
 *  LibTidy users may want to use `TidyReportFilter3` to enable their own
 *  localization lookup features. Because Tidy's errors codes are enums the
 *  specific values can change over time. This function returns a string
 *  representing the enum value name that can be used as a lookup key
 *  independent of changing string values (TidyReportFiler2 is vulnerable
 *  to changing strings). `TidyReportFilter3` will return this general
 *  string as the error message indicator.
 */
ctmbstr tidyErrorCodeAsString(uint code);


/** @} */
/** @name Localization Related Functions */
/** @{ */


/**
 **  Determines the current locale without affecting the C locale.
 **  Tidy has always used the default C locale, and at this point
 **  in its development we're not going to tamper with that.
 **  @param  result The buffer to use to return the string.
 **          Returns NULL on failure.
 **  @return The same buffer for convenience.
 */
tmbstr tidySystemLocale(tmbstr result);

/**
 *  Tells Tidy to use a different language for output.
 *  @param  languageCode A Windows or POSIX language code, and must match
 *          a TIDY_LANGUAGE for an installed language.
 *  @result Indicates that a setting was applied, but not necessarily the
 *          specific request, i.e., true indicates a language and/or region
 *          was applied. If es_mx is requested but not installed, and es is
 *          installed, then es will be selected and this function will return
 *          true. However the opposite is not true; if es is requested but
 *          not present, Tidy will not try to select from the es_XX variants.
 */
Bool tidySetLanguage( ctmbstr languageCode );

/**
 *  Gets the current language used by Tidy.
 */
ctmbstr tidyGetLanguage();

/**
 *  Provides a string given `messageType` in the current
 *  localization for `quantity`.
 */
ctmbstr tidyLocalizedStringN( uint messageType, uint quantity );

/**
 *  Provides a string given `messageType` in the current
 *  localization for the single case.
 */
ctmbstr tidyLocalizedString( uint messageType );


/** @} */
/** @name Documentation Generation */
/** @{ */

/**
 *  Provides a string given `messageType` in the default
 *  localization (which is `en`).
 */
ctmbstr tidyDefaultString( uint messageType );

/*
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's list of localization string keys. Note that
 *  these are provided for documentation generation purposes
 *  and probably aren't useful for LibTidy implementors.
 */
TidyIterator getStringKeyList();

/*
 *  Provides the next key value in Tidy's list of localized
 *  strings. Note that these are provided for documentation
 *  generation purposes and probably aren't useful to
 *  libtidy implementors.
 */
uint getNextStringKey( TidyIterator* iter );

/**
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's structure of Windows<->POSIX local mapping.
 *  Items can be retrieved with getNextWindowsLanguage();
 */
TidyIterator getWindowsLanguageList();

/**
 *  Returns the next record of type `localeMapItem` in
 *  Tidy's structure of Windows<->POSIX local mapping.
 */
const tidyLocaleMapItem *getNextWindowsLanguage( TidyIterator* iter );

/**
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's list of installed language codes.
 *  Items can be retrieved with getNextInstalledLanguage();
 */
TidyIterator getInstalledLanguageList();

/**
 *  Returns the next installed language.
 */
ctmbstr getNextInstalledLanguage( TidyIterator* iter );


/**
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's list of error codes that can be return with
 *  `TidyReportFilter3`.
 *  Items can be retrieved with getNextErrorCode();
 */
TidyIterator getErrorCodeList();

/**
 *  Returns the next error code.
 */
const tidyErrorFilterKeyItem *getNextErrorCode( TidyIterator* iter );


/** @} */

#endif /* language_h */
