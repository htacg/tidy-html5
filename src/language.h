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
 *  Defines all of the possible dictionary keys.
 *  The starting value is arbitrary but must prevent overlaps
 *  with other enums that are used for retrieving strings. The
 *  comprehensive list of enums for which we provides strings
 *  is as follows:
 *    - `tidyMessageTypes` in this file,         start == 4096.
 *    - `accessErrorCodes` from `access.h`,      start == 1000.
 *    - `tidyErrorCodes` from `message.h`,       start == 200.
 *    - `tidyMessagesMisc` from `message.h`,     start == 2048.
 *    - `TidyOptionId` from `tidyEnum.h`,        start == 0 (important!).
 *    - `TidyReportLevelKeys` from `tidyEnum.h`, start == 500.
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
 **  Determines the current locale without affecting the C locale.
 **  Tidy has always used the default C locale, and at this point
 **  in its development we're not going to tamper with that.
 **  @param  result The buffer to use to return the string.
 **          Returns NULL on failure.
 **  @return The same buffer for convenience.
 */
tmbstr tidySystemLocale(tmbstr result);


/**
 *  Tells Tidy to use a different language for output. The
 *  parameter `languageCode` must match the TIDY_LANGUAGE for
 *  an included language. The result indicates that a setting
 *  was applied, but not necessarily the specific request, i.e.,
 *  true indicates the language and/or region was applied.
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


/** @name Documentation Generation */
/** @{ */

/**
 *  Provides a string given `messageType` in the default
 *  localization (which is `en`).
 */
ctmbstr tidyDefaultString( uint messageType );


/**
 *  Provides the first key value in the localized strings
 *  list. Note that these are provided for documentation
 *  generation purposes and probably aren't useful to
 *  libtidy implementors.
 */
uint tidyFirstStringKey();

/**
 *  Provides the next key value in the localized strings
 *  list. This current position is static so don't count
 *  on multiple iterators running concurrently. Note that
 *  these are provided for documentation generation purposes
 *   and probably aren't useful to libtidy implementors.
 */
uint tidyNextStringKey();

/**
 *  Provides the last key value in the localized strings
 *  list. Note that these are provided for documentation
 *  generation purposes and probably aren't useful to
 *  libtidy implementors.
 */
uint tidyLastStringKey();

/**
 *  Prints the Windows language names that Tidy recognizes, 
 *  using the specified format string.
 */
void tidyPrintWindowsLanguageNames( ctmbstr format );

/**
 *  Prints the languages the are currently built into Tidy,
 *  using the specified format string.
 */
void tidyPrintTidyLanguageNames( ctmbstr format );

/** @} */

#endif /* language_h */
