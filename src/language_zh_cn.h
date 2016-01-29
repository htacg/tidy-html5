#ifndef language_zh_cn_h
#define language_zh_cn_h
/*
 * language_zh_cn.h
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
 *     language (and maybe region) "zh_cn". The source of
 *     these strings is a gettext PO file in Tidy's source, probably called 
 *     "language_zh_cn.po".
 *
 * [ ] THIS FILE WAS HAND MODIFIED. Translators, please feel to edit this file
 *     directly (and check this box). If you prefer to edit PO files then use
 *     `poconvert.rb msgunfmt language_zh_cn.h` (our own
 *     conversion tool) to generate a fresh PO from this file first!
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
