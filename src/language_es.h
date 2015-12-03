#ifndef language_es_h
#define language_es_h
/*
 * language_es.h
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
static languageDictionary language_es = {
	/* Specify the code for this language. */
	{ TIDY_LANGUAGE,                "es"                                                                      },
	
	
	/*****************************
	 ** Localization test strings
	 *****************************/
	{ TEST_PRESENT_IN_BASE,         "This is es base language (TEST_PRESENT_IN_BASE)."                        },
	
	
	/* This MUST be present and last. */
	{ TIDY_MESSAGE_TYPE_LAST,       NULL                                                                      }
};


#endif /* language_es_h */
