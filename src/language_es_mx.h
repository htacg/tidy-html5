#ifndef language_es_mx_h
#define language_es_mx_h
/*
 * language_es_mx.h
 * Localization support for HTML Tidy.
 *
 * THIS FILE IS MACHINE GENERATED. It is a localization file for the
 * language (and maybe region) "es_mx" and it should not be
 * edited manually. The source of these strings is a gettext PO file,
 * probably called "language_es_mx.po" in Tidy's source.
 *
 * Tidy's source distribution also includes a script to convert PO files
 * into this file. Because PO files are friendly to translators and a
 * standard industry tool, please translate ONLY the PO files.
 *
 * (c) 2015 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Template Created by Jim Derry on 01/14/2016.
 *
 * Orginating PO file metadata:
 *   PO_LAST_TRANSLATOR=jderry
 *   PO_REVISION_DATE=2016-01-26 14:38:30
 */

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include "language.h"
#include "access.h"
#include "message.h"


/**
 *  This language-specific function returns the correct pluralForm
 *  to use given n items, and is used as a member of each language
 *  definition.
 */
static uint whichPluralForm_es_mx(uint n) {
	/* Plural-Forms: nplurals=2; */
	return n != 1;
}


/**
 *  This structure specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 */
static languageDefinition language_es_mx = { whichPluralForm_es_mx, {
	/***************************************
	 ** This MUST be present and first. 
	 ** Specify the code for this language.
	 ***************************************/
    {/* Specify the ll or ll_cc language code here. */
      TIDY_LANGUAGE,          0, "es_mx"
    },
    {/* This console output should be limited to 78 characters per line. 
      - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TEXT_GENERAL_INFO_PLEA, 0,        
        "\n"
        "¿Le gustaría ver Tidy en adecuada, español mexicano? Por favor considere \n"
        "ayudarnos a localizar HTML Tidy. Para más detalles consulte \n"
        "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md \n"
    },

    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST, 0, NULL
    }

}};


#endif /* language_es_mx_h */
