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
 *  This language-specific fuction returns the correct pluralForm
 *  to use given n items, and is used as a member of each language
 *  definition.
 */
static uint whichPluralForm_es_mx(uint n) {
	return n != 1;
}


/**
 *  This array specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 */
static languageDefinition language_es_mx = { whichPluralForm_es_mx, {
	/* Specify the code for this language. */
	{ TIDY_LANGUAGE,               0,   "es_mx"                                                                    },
	
	
	/*****************************
	 ** Miscellaneous Strings
	 *****************************/
	
	{ TEXT_GENERAL_INFO_PLEA,      0,
		"\n"
		"¿Le gustaría ver Tidy en adecuada, español mexicano? Por favor considere \n"
		"ayudarnos a localizar HTML Tidy. Para más detalles consulte \n"
		"https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md \n"
	},

	
	/* This MUST be present and last. */
	{ TIDY_MESSAGE_TYPE_LAST,      0,   NULL                                                                       }
}};


#endif /* language_es_mx_h */
