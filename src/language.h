#ifndef language_h
#define language_h
/*
 * language.h
 * Localization support for HTML Tidy.
 * This header provides the public (within libtidy) interface
 * to basic localization support. To add your own localization
 * create a new `language_xx.h` file copied from an existing
 * localization, and add it to the struct in `language.c`.
 *
 * (c) 2015 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Created by Jim Derry on 11/28/15.
*/

#include "tidyplatform.h"


/**
 *  Describes a record for a localization string. They key must
 *  correspond with one of Tidy's enums (see `tidyMessageTypes`
 *  below).
 */
typedef struct languageDictionaryEntry {
    uint key;
    ctmbstr value;
} languageDictionaryEntry;


/**
 *  For now we'll just use an array to hold all of the dictionary
 *  entries. In the future we can convert this to a hash structure
 *  which will make looking up strings faster.
 */
typedef languageDictionaryEntry const languageDictionary[600];


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

    /* Strings for the console application. */
	TC_LABEL_FILE,
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
	TC_OPT_XMLHELP,  
	TC_STRING_OUT_OF_MEMORY,
	TC_STRING_FILE_MANIP,
	TC_STRING_PROCESS_DIRECTIVES,
	TC_STRING_CHAR_ENCODING,
	TC_STRING_MISC,

    /* This MUST be present and last. */
    TIDY_MESSAGE_TYPE_LAST
} tidyMessageTypes;


/**
 *  Provides a string given `messageType` in the current
 *  localization.
 */
ctmbstr tidyLocalizedString( uint messageType );


/**
 *  Tells Tidy to use a different language for output. The
 *  parameter `languageCode` must match the TIDY_LANGUAGE for
 *  an included language. The result indicates the result of this
 *  setting.
 *  @todo: this will eventually be set via tidy's `--language`
 *  option, and the `console` app will set this based on user
 *  locale.
 */
Bool tidySetLanguage( ctmbstr languageCode );


#endif /* language_h */
