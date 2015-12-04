#ifndef language_es_mx_h
#define language_es_mx_h
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
static languageDictionary language_es_mx = {
	/* Specify the code for this language. */
	{ TIDY_LANGUAGE,               "es_mx"                                                                    },
	
	
	/*****************************
	 ** Localization test strings
	 *****************************/
	{ TEST_PRESENT_IN_REGION,      "This is es_mx region langauge (TEST_PRESENT_IN_REGION)."                  },
	
	
	/*****************************
	 ** Miscellaneous Strings
	 *****************************/
	
	{ TEXT_GENERAL_INFO_PLEA,
		"\n"
		"¿Le gustaría ver Tidy en adecuada, español mexicano? Por favor considere \n"
		"ayudarnos a localizar HTML Tidy. Para más detalles consulte \n"
		"https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md \n"
	},

	
	/* This MUST be present and last. */
	{ TIDY_MESSAGE_TYPE_LAST,      NULL                                                                       }
};


#endif /* language_es_mx_h */
