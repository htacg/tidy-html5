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
      TIDY_LANGUAGE,                    0, "en_gb"
    },
    { TidyAsciiChars,                   0,        
        "Can be used to modify behaviour of the <code>clean</code> option when set "
        "to <var>yes</var>. "
        "<br/>"
        "If set to <var>yes</var> when using <code>clean</code>, "
        "<code>&amp;emdash;</code>, <code>&amp;rdquo;</code>, and other named "
        "character entities are downgraded to their closest ASCII equivalents. "
    },
    { TidyGDocClean,                    0,        
        "This option specifies if Tidy should enable specific behaviour for "
        "cleaning up HTML exported from Google Docs. "
    },
    { TidyLiteralAttribs,               0,        
        "This option specifies how Tidy deals with whitespace characters within "
        "attribute values. "
        "<br/>"
        "If the value is <var>no</var> Tidy normalises attribute values by "
        "replacing any newline or tab with a single space, and further by replacing "
        "any contiguous whitespace with a single space. "
        "<br/>"
        "To force Tidy to preserve the original, literal values of all attributes "
        "and ensure that whitespace within attribute values is passed "
        "through unchanged, set this option to <var>yes</var>. "
    },
    { TidyMergeDivs,                    0,        
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
    { TidyMergeSpans,                   0,        
        "This option can be used to modify the behaviour of <code>clean</code> when "
        "set to <code>yes</code>."
        "<br/>"
        "This option specifies if Tidy should merge nested <code>&lt;span&gt;</code> "
        "such as <code>&lt;span&gt;&lt;span&gt;...&lt;/span&gt;&lt;/span&gt;</code>. "
        "<br/>"
        "The algorithm is identical to the one used by <code>merge-divs</code>. "
    },
    { TidyReplaceColor,                 0,        
        "This option specifies if Tidy should replace numeric values in colour "
        "attributes with HTML/XHTML colour names where defined, e.g. replace "
        "<code>#ffffff</code> with <code>white</code>. "
    },
    { TidyUseCustomTags,                0,        
        "This option enables the use of tags for autonomous custom elements, "
        "e.g. &lt;flag-icon&gt; with Tidy. Custom tags are disabled if this "
        "value is <var>no</var>. Other settings - <var>blocklevel</var>, "
        "<var>empty</var>, <var>inline</var>, and <var>pre</var> will treat "
        "<em>all</em> detected custom tags accordingly. "
        "<br/>"
        "The use of <code>new-blocklevel-tags</code>, "
        "<code>new-empty-tags</code>, <code>new-inline-tags</code>, or "
        "<code>new-pre-tags</code> will override the treatment of custom tags "
        "by this configuration option. This may be useful if you have "
        "different types of custom tags."
        "<br/>"
        "When enabled these tags are determined during the processing of your "
        "document using opening tags; matching closing tags will be recognised "
        "accordingly, and unknown closing tags will be discarded. "
    },
    { TEXT_USING_FONT,                  0,        
        "You are recommended to use CSS to specify the font and\n"
        "properties such as its size and colour. This will reduce\n"
        "the size of HTML files and make them easier to maintain\n"
        "compared with using <FONT> elements.\n\n"
    },
    { TEXT_USING_BODY,                  0, "You are recommended to use CSS to specify page and link colours\n"           },
    { TEXT_GENERAL_INFO_PLEA,           0,        
        "\n"
        "Would you like to see Tidy in proper, British English? Please consider \n"
        "helping us to localise HTML Tidy. For details please see \n"
        "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md\n"
    },
    { UNKNOWN_ELEMENT_LOOKS_CUSTOM,     0, "%s is not recognised! Did you mean to enable the custom-tags option?"        },
    { UNKNOWN_ELEMENT,                  0, "%s is not recognised!"                                                       },
    { MULTIMEDIA_REQUIRES_TEXT,         0, "[1.4.1.1]: multimedia requires synchronised text equivalents."               },
    { INFORMATION_NOT_CONVEYED_IMAGE,   0, "[2.1.1.1]: ensure information not conveyed through colour alone (image)."    },
    { INFORMATION_NOT_CONVEYED_APPLET,  0, "[2.1.1.2]: ensure information not conveyed through colour alone (applet)."   },
    { INFORMATION_NOT_CONVEYED_OBJECT,  0, "[2.1.1.3]: ensure information not conveyed through colour alone (object)."   },
    { INFORMATION_NOT_CONVEYED_SCRIPT,  0, "[2.1.1.4]: ensure information not conveyed through colour alone (script)."   },
    { INFORMATION_NOT_CONVEYED_INPUT,   0, "[2.1.1.5]: ensure information not conveyed through colour alone (input)."    },
    { COLOR_CONTRAST_TEXT,              0, "[2.2.1.1]: poor colour contrast (text)."                                     },
    { COLOR_CONTRAST_LINK,              0, "[2.2.1.2]: poor colour contrast (link)."                                     },
    { COLOR_CONTRAST_ACTIVE_LINK,       0, "[2.2.1.3]: poor colour contrast (active link)."                              },
    { COLOR_CONTRAST_VISITED_LINK,      0, "[2.2.1.4]: poor colour contrast (visited link)."                             },
    { LAYOUT_TABLES_LINEARIZE_PROPERLY, 0, "[5.3.1.1]: verify layout tables linearise properly."                         },

#if SUPPORT_CONSOLE_APP
    { TC_TXT_HELP_LANG_2,               0,        
        "\n"
        "The following languages are currently installed in Tidy. Please \n"
        "note that there's no guarantee that they are complete; only that \n"
        "one developer or another started to add the language indicated. \n"
        "\n"
        "Incomplete localisations will default to \"en\" when necessary. \n"
        "Please report instances of incorrect strings to the Tidy team. \n"
        "\n"
    },
#endif /* SUPPORT_CONSOLE_APP */

    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST,           0, NULL
    }

}};


#endif /* language_en_gb_h */

