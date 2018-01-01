#ifndef language_es_mx_h
#define language_es_mx_h
/*
 * language_es_mx.h
 * Localization support for HTML Tidy.
 *
 *
 * This file is a localization file for HTML Tidy. It will have been machine
 * generated or created and/or edited by hand. Both are valid options, but
 * please help keep our localization efforts simple to maintain by maintaining
 * the structure of this file, and changing the check box below if you make
 * changes (so others know the file origin):
 *
 * [X] THIS FILE IS MACHINE GENERATED. It is a localization file for the
 *     language (and maybe region) "es_mx". The source of
 *     these strings is a gettext PO file in Tidy's source, probably called 
 *     "language_es_mx.po".
 *
 * [ ] THIS FILE WAS HAND MODIFIED. Translators, please feel to edit this file
 *     directly (and check this box). If you prefer to edit PO files then use
 *     `poconvert.rb msgunfmt language_es_mx.h` (our own
 *     conversion tool) to generate a fresh PO from this file first!
 *
 * (c) 2015-2017 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Template Created by Jim Derry on 01/14/2016.
 *
 * Orginating PO file metadata:
 *   PO_LAST_TRANSLATOR=jderry
 *   PO_REVISION_DATE=2017-10-03 12:44:37
 */

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif


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
    { TEXT_GENERAL_INFO_PLEA, 0,        
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

