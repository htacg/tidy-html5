#ifndef language_en_gb_h
#define language_en_gb_h
/*
 * language_en_gb.h
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
 *     language (and maybe region) "en_gb". The source of
 *     these strings is a gettext PO file in Tidy's source, probably called 
 *     "language_en_gb.po".
 *
 * [ ] THIS FILE WAS HAND MODIFIED. Translators, please feel to edit this file
 *     directly (and check this box). If you prefer to edit PO files then use
 *     `poconvert.rb msgunfmt language_en_gb.h` (our own
 *     conversion tool) to generate a fresh PO from this file first!
 *
 * (c) 2015-2017 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Template Created by Jim Derry on 01/14/2016.
 *
 * Orginating PO file metadata:
 *   PO_LAST_TRANSLATOR=jderry
 *   PO_REVISION_DATE=2017-03-22 15:54:52
 */

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif


/**
 *  This language-specific function returns the correct pluralForm
 *  to use given n items, and is used as a member of each language
 *  definition.
 */
static uint whichPluralForm_en_gb(uint n) {
    /* Plural-Forms: nplurals=2; */
    return n != 1;
}


/**
 *  This structure specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 */
static languageDefinition language_en_gb = { whichPluralForm_en_gb, {
    /***************************************
     ** This MUST be present and first. 
     ** Specify the code for this language.
     ***************************************/
    {/* Specify the ll or ll_cc language code here. */
      TIDY_LANGUAGE,                   0, "en_gb"
    },
    { TidyMergeDivs,                   0,        
        "This option can be used to modify the behaviour of <code>clean</code> "
        "when set to <var>yes</var>."
        "<br/>"
        "This option specifies if Tidy should merge nested "
        "<code>&lt;div&gt;</code> "
        "such as "
        "<code>&lt;div&gt;&lt;div&gt;...&lt;/div&gt;&lt;/div&gt;</code>."
        "<br/>"
        "If set to <var>auto</var> the attributes of the inner "
        "<code>&lt;div&gt;</code> are moved to the outer one. Nested "
        "<code>&lt;div&gt;</code> with <code>id</code> attributes are "
        "<em>not</em> merged."
        "<br/>"
        "If set to <var>yes</var> the attributes of the inner "
        "<code>&lt;div&gt;</code> are discarded with the exception of "
        "<code>class</code> and <code>style</code>."
    },
    { TidyMergeSpans,                  0,
        "This option can be used to modify the behaviour of <code>clean</code> "
        "when set to <var>yes</var>."
        "<br/>"
        "This option specifies if Tidy should merge nested "
        "<code>&lt;span&gt;</code> such as "
        "<code>&lt;span&gt;&lt;span&gt;...&lt;/span&gt;&lt;/span&gt;</code>."
        "<br/>"
        "The algorithm is identical to the one used by <code>merge-divs</code>."
    },
    { TidyReplaceColor,                0,        
        "This option specifies if Tidy should replace numeric values in colour "
        "attributes with HTML/XHTML colour names where defined, e.g. replace "
        "<code>#ffffff</code> with <code>white</code>. "
    },
    { TEXT_USING_FONT,                 0,        
        "You are recommended to use CSS to specify the font and "
        "properties such as its size and colour. This will reduce "
        "the size of HTML files and make them easier to maintain "
        "compared with using <FONT> elements."
        "\n"
    },
    { TEXT_USING_BODY,                 0, "You are recommended to use CSS to specify page and link colours\n"           },
    { TEXT_GENERAL_INFO_PLEA,          0,        
        "Would you like to see Tidy in proper, British English? Please consider "
        "helping us to localise HTML Tidy. For details please see "
        "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md"
    },

#if SUPPORT_ACCESSIBILITY_CHECKS
    { INFORMATION_NOT_CONVEYED_IMAGE,  0, "[2.1.1.1]: ensure information not conveyed through colour alone (image)."    },
    { INFORMATION_NOT_CONVEYED_APPLET, 0, "[2.1.1.2]: ensure information not conveyed through colour alone (applet)."   },
    { INFORMATION_NOT_CONVEYED_OBJECT, 0, "[2.1.1.3]: ensure information not conveyed through colour alone (object)."   },
    { INFORMATION_NOT_CONVEYED_SCRIPT, 0, "[2.1.1.4]: ensure information not conveyed through colour alone (script)."   },
    { INFORMATION_NOT_CONVEYED_INPUT,  0, "[2.1.1.5]: ensure information not conveyed through colour alone (input)."    },
    { COLOR_CONTRAST_TEXT,             0, "[2.2.1.1]: poor colour contrast (text)."                                     },
    { COLOR_CONTRAST_LINK,             0, "[2.2.1.2]: poor colour contrast (link)."                                     },
    { COLOR_CONTRAST_ACTIVE_LINK,      0, "[2.2.1.3]: poor colour contrast (active link)."                              },
    { COLOR_CONTRAST_VISITED_LINK,     0, "[2.2.1.4]: poor colour contrast (visited link)."                             },
#endif /* SUPPORT_ACCESSIBILITY_CHECKS */

    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST,          0, NULL
    }

}};


#endif /* language_en_gb_h */
