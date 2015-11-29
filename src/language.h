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

    /* Miscelleneous Strings */
    ACCESS_URL,                              /* Used to point to Web Accessibility Guidelines. */
    ATRC_ACCESS_URL,                         /* Points to Tidy's accessibility page. */


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
