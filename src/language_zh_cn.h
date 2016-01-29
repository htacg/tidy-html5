#ifndef language_zh_cn_h
#define language_zh_cn_h
/*
 * language_zh_cn.h
 * Localization support for HTML Tidy.
 *
 * THIS FILE IS MACHINE GENERATED. It is a localization file for the
 * language (and maybe region) "zh_cn" and it should not be
 * edited manually. The source of these strings is a gettext PO file,
 * probably called "language_zh_cn.po" in Tidy's source.
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
 *   PO_REVISION_DATE=2016-01-29 10:54:42
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
static uint whichPluralForm_zh_cn(uint n) {
    /* Plural-Forms: nplurals=1; */
    return 0;
}


/**
 *  This structure specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 */
static languageDefinition language_zh_cn = { whichPluralForm_zh_cn, {
    /***************************************
     ** This MUST be present and first. 
     ** Specify the code for this language.
     ***************************************/
    {/* Specify the ll or ll_cc language code here. */
      TIDY_LANGUAGE,          0, "zh_cn"
    },
    { FILE_CANT_OPEN,         0, "\xe6\x97\xa0\xe6\xb3\x95\xe6\x89\x93\xe5\xbc\x80\xe2\x80\x9d%s\xe2\x80\x9d\n"                          },
    { LINE_COLUMN_STRING,     0, "\xe8\xa1\x8c %d \xe5\x88\x97 %d - "                                                                    },
    { STRING_CONTENT_LOOKS,   0, "\xe6\x96\x87\xe6\xa1\xa3\xe5\x86\x85\xe5\xae\xb9\xe7\x9c\x8b\xe8\xb5\xb7\xe6\x9d\xa5\xe5\x83\x8f %s"   },
    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_STRING_VERS_A,       0, "HTML Tidy \xe7\x94\xa8\xe4\xba\x8e %s \xe7\x89\x88\xe6\x9c\xac %s"
    },
    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_STRING_VERS_B,       0, "HTML Tidy \xe7\x89\x88\xe6\x9c\xac %s"
    },

    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST, 0, NULL
    }

}};


#endif /* language_zh_cn_h */
