#ifndef language_en_gb_h
#define language_en_gb_h
/*
 * language_en_gb.h
 * Localization support for HTML Tidy.
 *
 * (c) 2015 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Created by Jim Derry on 11/28/15.
 */

#include "language.h"
#include "access.h"
#include "message.h"


/**
 *  This array specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 */
static languageDictionary language_en_gb = {
    /* Specify the code for this language. */
    { TIDY_LANGUAGE,               "en_gb"                                    },


    /* This MUST be present and last. */
    { TIDY_MESSAGE_TYPE_LAST,      NULL                                       }
};


#endif /* language_en_gb_h */
