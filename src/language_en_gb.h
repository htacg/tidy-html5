#ifndef language_en_gb_h
#define language_en_gb_h
/*
 * language_en_gb.h
 * Localization support for HTML Tidy.
 *
 * THIS FILE IS MACHINE GENERATED. It is a localization file for the
 * language (and maybe region) "en_gb" and it should not be
 * edited manually. The source of these strings is a gettext PO file,
 * probably called "language_en_gb.po" in Tidy's source.
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
 *   PO_REVISION_DATE=2016-01-23 16:04:27
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
    {/* This console output should be limited to 78 characters per line. */
      TEXT_USING_FONT,                 0,        
        "You are recommended to use CSS to specify the font and\n"
        "properties such as its size and colour. This will reduce\n"
        "the size of HTML files and make them easier to maintain\n"
        "compared with using <FONT> elements.\n\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_USING_BODY,                 0, "You are recommended to use CSS to specify page and link colours\n"
    },
    {/* This console output should be limited to 78 characters per line. 
      - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TEXT_GENERAL_INFO_PLEA,          0,        
        "\n"
        "Would you like to see Tidy in proper, British English? Please consider \n"
        "helping us to localise HTML Tidy. For details please see \n"
        "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md\n"
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

    {/* Please use _only_ <code></code>, <em></em>, <strong></strong>, and <br/>.
	    It's very important that <br/> be self-closing in this manner! 
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TidyMergeDivs,                   0,        
        "This option can be used to modify the behaviour of <code>clean</code> when "
        "set to <code>yes</code>."
        "<br/>"
        "This option specifies if Tidy should merge nested <code>&lt;div&gt;</code> "
        "such as <code>&lt;div&gt;&lt;div&gt;...&lt;/div&gt;&lt;/div&gt;</code>. "
        "<br/>"
        "If set to <code>auto</code> the attributes of the inner "
        "<code>&lt;div&gt;</code> are moved to the outer one. Nested "
        "<code>&lt;div&gt;</code> with <code>id</code> attributes are <em>not</em> "
        "merged. "
        "<br/>"
        "If set to <code>yes</code> the attributes of the inner "
        "<code>&lt;div&gt;</code> are discarded with the exception of "
        "<code>class</code> and <code>style</code>. "
    },
    {/* Please use _only_ <code></code>, <em></em>, <strong></strong>, and <br/>.
	    It's very important that <br/> be self-closing in this manner! 
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TidyMergeSpans,                  0,        
        "This option can be used to modify the behaviour of <code>clean</code> when "
        "set to <code>yes</code>."
        "<br/>"
        "This option specifies if Tidy should merge nested <code>&lt;span&gt;</code> "
        "such as <code>&lt;span&gt;&lt;span&gt;...&lt;/span&gt;&lt;/span&gt;</code>. "
        "<br/>"
        "The algorithm is identical to the one used by <code>merge-divs</code>. "
    },
    {/* Please use _only_ <code></code>, <em></em>, <strong></strong>, and <br/>.
	    It's very important that <br/> be self-closing in this manner! 
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TidyReplaceColor,                0,        
        "This option specifies if Tidy should replace numeric values in colour "
        "attributes with HTML/XHTML colour names where defined, e.g. replace "
        "<code>#ffffff</code> with <code>white</code>. "
    },

    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST,          0, NULL
    }

}};


#endif /* language_en_gb_h */
