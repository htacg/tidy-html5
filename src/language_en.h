#ifndef language_en_h
#define language_en_h
/*
 * language_en.h
 * Localization support for HTML Tidy.
 *
 * This file consists of the strings for Tidy's base language and is a
 * required localization for Tidy to compile and work. Unlike the other
 * localization files this file is NOT machine-generated.
 *
 * This file also serves as the master template for generating additional
 * language localizations. As such do not edit PO files for this language;
 * modify this file directly.
 *
 * (c) 2015 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Created by Jim Derry on 11/28/15.
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
static uint whichPluralForm_en(uint n) {
    /* Plural-Forms: nplurals=2; */
    return n != 1;
}


/**
 *  This structure specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 *
 *  This file serves as the master template for generating `gettext`
 *  PO and POT files using our `potool.rb` script. Certain comments
 *  entered below will be included in the PO/POT files as developer
 *  comments. To enable this, use only standard C-style comments that
 *  begin immediately after the opening brace without whitespace.
 */

static languageDefinition language_en = { whichPluralForm_en, {
    /***************************************
     ** This MUST be present and first.
     ** Specify the code for this language.
     ***************************************/
    {/* Specify the ll or ll_cc language code here. */
      TIDY_LANGUAGE,                0,   "en"
    },
    
    /***************************************
     ** Miscellaneous Strings
     ***************************************/
    {/* Only translate if a URL to the target language can be found. */
      ACCESS_URL,                   0,   "http://www.w3.org/WAI/GL"
    },
    {/* Only translate if a URL to the target language can be found. */
      ATRC_ACCESS_URL,              0,   "http://www.html-tidy.org/accessibility/"
    },
    { FILE_CANT_OPEN,               0,   "Can't open \"%s\"\n"                                                     },
    { LINE_COLUMN_STRING,           0,   "line %d column %d - "                                                    },
    { STRING_CONTENT_LOOKS,         0,   "Document content looks like %s"                                          },
    {/* For example, "discarding invalid UTF-16 surrogate pair" */
      STRING_DISCARDING,            0,   "discarding"
    },
    { STRING_DOCTYPE_GIVEN,         0,   "Doctype given is \"%s\""                                                 },

    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      STRING_ERROR_COUNT,           0,   "Tidy found %u %s and %u %s!"
    },
    { STRING_ERROR_COUNT_ERROR,     0,   "error"                                                                   },
    { STRING_ERROR_COUNT_ERROR,     1,   "errors"                                                                  },
    { STRING_ERROR_COUNT_WARNING,   0,   "warning"                                                                 },
    { STRING_ERROR_COUNT_WARNING,   1,   "warnings"                                                                },
    { STRING_HELLO_ACCESS,          0,   "Accessibility Checks:"                                                   },
    {/* This is not a formal name and can be translated. */
      STRING_HTML_PROPRIETARY,      0,   "HTML Proprietary"
    },
    { STRING_MISSING_MALFORMED,     0,   "missing or malformed argument for option: %s"                            },
    { STRING_NO_ERRORS,             0,   "No warnings or errors were found."                                       },
    { STRING_NO_SYSID,              0,   "No system identifier in emitted doctype"                                 },
    { STRING_NOT_ALL_SHOWN,         0,   "Not all warnings/errors were shown."                                     },
    { STRING_PLAIN_TEXT,            0,   "plain text"                                                              },
    {/* For example, "replacing invalid UTF-8 bytes" */
      STRING_REPLACING,             0,   "replacing"
    },
    {/* For example, "you should avoid using the specified encoding." */
      STRING_SPECIFIED,             0,   "specified"
    },
    { STRING_UNKNOWN_FILE,          0,   "%s: can't open file \"%s\"\n"                                            },
    { STRING_UNKNOWN_OPTION,        0,   "unknown option: %s"                                                      },
    { STRING_UNRECZD_OPTION,        0,   "unrecognized option -%c use -help to list options\n"                     },
    { STRING_XML_DECLARATION,       0,   "XML declaration"                                                         },
    
    {/* This console output should be limited to 78 characters per line. */
      TEXT_HTML_T_ALGORITHM,        0,
        "\n"
        "      - First, search left from the cell's position to find row header cells.\n"
        "      - Then search upwards to find column header cells.\n"
        "      - The search in a given direction stops when the edge of the table is\n"
        "        reached or when a data cell is found after a header cell.\n"
        "      - Row headers are inserted into the list in the order they appear in\n"
        "        the table. \n"
        "      - For left-to-right tables, headers are inserted from left to right.\n"
        "      - Column headers are inserted after row headers, in \n"
        "        the order they appear in the table, from top to bottom. \n"
        "      - If a header cell has the headers attribute set, then the headers \n"
        "        referenced by this attribute are inserted into the list and the \n"
        "        search stops for the current direction.\n"
        "        TD cells that set the axis attribute are also treated as header cells.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_WINDOWS_CHARS,           0,
        "Characters codes for the Microsoft Windows fonts in the range\n"
        "128 - 159 may not be recognized on other platforms. You are\n"
        "instead recommended to use named entities, e.g. &trade; rather\n"
        "than Windows character code 153 (0x2122 in Unicode). Note that\n"
        "as of February 1998 few browsers support the new entities.\n\n"
    },
    {/* This console output should be limited to 78 characters per line.
        - %s represents a string-encoding name which may be localized in your language. */
      TEXT_VENDOR_CHARS,            0,
        "It is unlikely that vendor-specific, system-dependent encodings\n"
        "work widely enough on the World Wide Web; you should avoid using the \n"
        "%s character encoding, instead you are recommended to\n"
        "use named entities, e.g. &trade;.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line.
        - %s represents a string-encoding name which may be localized in your language.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TEXT_SGML_CHARS,              0,
        "Character codes 128 to 159 (U+0080 to U+009F) are not allowed in HTML;\n"
        "even if they were, they would likely be unprintable control characters.\n"
        "Tidy assumed you wanted to refer to a character with the same byte value in the \n"
        "%s encoding and replaced that reference with the Unicode \n"
        "equivalent.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_INVALID_UTF8,            0,
        "Character codes for UTF-8 must be in the range: U+0000 to U+10FFFF.\n"
        "The definition of UTF-8 in Annex D of ISO/IEC 10646-1:2000 also\n"
        "allows for the use of five- and six-byte sequences to encode\n"
        "characters that are outside the range of the Unicode character set;\n"
        "those five- and six-byte sequences are illegal for the use of\n"
        "UTF-8 as a transformation of Unicode characters. ISO/IEC 10646\n"
        "does not allow mapping of unpaired surrogates, nor U+FFFE and U+FFFF\n"
        "(but it does allow other noncharacters). For more information please refer to\n"
        "http://www.unicode.org/ and http://www.cl.cam.ac.uk/~mgk25/unicode.html\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_INVALID_UTF16,           0,
        "Character codes for UTF-16 must be in the range: U+0000 to U+10FFFF.\n"
        "The definition of UTF-16 in Annex C of ISO/IEC 10646-1:2000 does not allow the\n"
        "mapping of unpaired surrogates. For more information please refer to\n"
        "http://www.unicode.org/ and http://www.cl.cam.ac.uk/~mgk25/unicode.html\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TEXT_INVALID_URI,             0,
        "URIs must be properly escaped, they must not contain unescaped\n"
        "characters below U+0021 including the space character and not\n"
        "above U+007E. Tidy escapes the URI for you as recommended by\n"
        "HTML 4.01 section B.2.1 and XML 1.0 section 4.2.2. Some user agents\n"
        "use another algorithm to escape such URIs and some server-sided\n"
        "scripts depend on that. If you want to depend on that, you must\n"
        "escape the URI on your own. For more information please refer to\n"
        "http://www.w3.org/International/O-URL-and-ident.html\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_BAD_FORM,                0,
        "You may need to move one or both of the <form> and </form>\n"
        "tags. HTML elements should be properly nested and form elements\n"
        "are no exception. For instance you should not place the <form>\n"
        "in one table cell and the </form> in another. If the <form> is\n"
        "placed before a table, the </form> cannot be placed inside the\n"
        "table! Note that one form can't be nested inside another!\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_BAD_MAIN,                0,
        "Only one <main> element is allowed in a document.\n"
        "Subsequent <main> elements have been discarded, which may\n"
        "render the document invalid.\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_M_SUMMARY,               0,
        "The table summary attribute should be used to describe\n"
        "the table structure. It is very helpful for people using\n"
        "non-visual browsers. The scope and headers attributes for\n"
        "table cells are useful for specifying which headers apply\n"
        "to each table cell, enabling non-visual browsers to provide\n"
        "a meaningful context for each cell.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_M_IMAGE_ALT,             0,
        "The alt attribute should be used to give a short description\n"
        "of an image; longer descriptions should be given with the\n"
        "longdesc attribute which takes a URL linked to the description.\n"
        "These measures are needed for people using non-graphical browsers.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_M_IMAGE_MAP,             0,
        "Use client-side image maps in preference to server-side image\n"
        "maps as the latter are inaccessible to people using non-\n"
        "graphical browsers. In addition, client-side maps are easier\n"
        "to set up and provide immediate feedback to users.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_M_LINK_ALT,              0,
        "For hypertext links defined using a client-side image map, you\n"
        "need to use the alt attribute to provide a textual description\n"
        "of the link for people using non-graphical browsers.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_USING_FRAMES,            0,
        "Pages designed using frames present problems for\n"
        "people who are either blind or using a browser that\n"
        "doesn't support frames. A frames-based page should always\n"
        "include an alternative layout inside a NOFRAMES element.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_ACCESS_ADVICE1,          0,
        "For further advice on how to make your pages accessible\n"
        "see http://www.w3.org/WAI/GL"
    },
    {/* This console output should be limited to 78 characters per line.
        - The URL should not be translated unless you find a matching URL in your language. */
      TEXT_ACCESS_ADVICE2,          0,
        " and http://www.html-tidy.org/accessibility/"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_USING_LAYER,             0,
        "The Cascading Style Sheets (CSS) Positioning mechanism\n"
        "is recommended in preference to the proprietary <LAYER>\n"
        "element due to limited vendor support for LAYER.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_USING_SPACER,            0,
        "You are recommended to use CSS for controlling white\n"
        "space (e.g. for indentation, margins and line spacing).\n"
        "The proprietary <SPACER> element has limited vendor support.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_USING_FONT,              0,
        "You are recommended to use CSS to specify the font and\n"
        "properties such as its size and color. This will reduce\n"
        "the size of HTML files and make them easier to maintain\n"
        "compared with using <FONT> elements.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_USING_NOBR,              0,
        "You are recommended to use CSS to control line wrapping.\n"
        "Use \"white-space: nowrap\" to inhibit wrapping in place\n"
        "of inserting <NOBR>...</NOBR> into the markup.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line. */
      TEXT_USING_BODY,              0,
        "You are recommended to use CSS to specify page and link colors\n"
    },
    {/* This console output should be limited to 78 characters per line.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TEXT_NEEDS_INTERVENTION,      0,
        "This document has errors that must be fixed before\n"
        "using HTML Tidy to generate a tidied up version.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TEXT_GENERAL_INFO,            0,
        "About HTML Tidy: https://github.com/htacg/tidy-html5\n"
        "Bug reports and comments: https://github.com/htacg/tidy-html5/issues\n"
        "Official mailing list: https://lists.w3.org/Archives/Public/public-htacg/\n"
        "Latest HTML specification: http://dev.w3.org/html5/spec-author-view/\n"
        "Validate your HTML documents: http://validator.w3.org/nu/\n"
        "Lobby your company to join the W3C: http://www.w3.org/Consortium\n"
    },
    {/* This console output should be limited to 78 characters per line. 
      - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TEXT_GENERAL_INFO_PLEA,       0,
        "\n"
        "Do you speak a language other than English, or a different variant of \n"
        "English? Consider helping us to localize HTML Tidy. For details please see \n"
        "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md\n"
    },
    
    
    /***************************************
     ** Message Severity Level
     ***************************************/
    { TidyInfoString,               0,   "Info: "                                                                  },
    { TidyWarningString,            0,   "Warning: "                                                               },
    { TidyConfigString,             0,   "Config: "                                                                },
    { TidyAccessString,             0,   "Access: "                                                                },
    { TidyErrorString,              0,   "Error: "                                                                 },
    { TidyBadDocumentString,        0,   "Document: "                                                              },
    { TidyFatalString,              0,   "Panic: "                                                                 },
    
    /***************************************
     ** Warnings and Errors
     ***************************************/
    
    /* ReportEncodingWarning */
    {
      ENCODING_MISMATCH,            0,   "specified input encoding (%s) does not match actual input encoding (%s)" }, /* Warning */
    
    /* ReportEncodingError */
    { VENDOR_SPECIFIC_CHARS,        0,   "%s invalid character code %s"                                            }, /* Error */
    { INVALID_SGML_CHARS,           0,   "%s invalid character code %s"                                            }, /* Error */
    { INVALID_UTF8,                 0,   "%s invalid UTF-8 bytes (char. code %s)"                                  }, /* Error */
    { INVALID_UTF16,                0,   "%s invalid UTF-16 surrogate pair (char. code %s)"                        }, /* Error */
    { INVALID_NCR,                  0,   "%s invalid numeric character reference %s"                               }, /* Error */
    { BAD_SURROGATE_PAIR,           0,   "Have out-of-range surrogate pair U+%04X:U+%04X, replaced with U+FFFD value."}, /* warning */
    { BAD_SURROGATE_TAIL,           0,   "Leading (High) surrogate pair U+%04X, with no trailing (Low) entity, replaced with U+FFFD." }, /* warning */
    { BAD_SURROGATE_LEAD,           0,   "Trailing (Low) surrogate pair U+%04X, with no leading (High) entity, replaced with U+FFFD." }, /* warning */

    /* ReportEntityError */
    { MISSING_SEMICOLON,            0,   "entity \"%s\" doesn't end in ';'"                                        }, /* Warning in HTML, Error in XML/XHTML */
    { MISSING_SEMICOLON_NCR,        0,   "numeric character reference \"%s\" doesn't end in ';'"                   }, /* Warning in HTML, Error in XML/XHTML */
    { UNESCAPED_AMPERSAND,          0,   "unescaped & which should be written as &amp;"                            }, /* Warning in HTML, Error in XHTML */
    { UNKNOWN_ENTITY,               0,   "unescaped & or unknown entity \"%s\""                                    }, /* Error */
    { APOS_UNDEFINED,               0,   "named entity &apos; only defined in XML/XHTML"                           }, /* Error in HTML (should only occur for HTML input) */
    
    /* ReportAttrError - attribute name */
    { INSERTING_ATTRIBUTE,          0,   "%s inserting \"%s\" attribute"                                           }, /* Warning in CheckLINK, Error otherwise */
    { INSERTING_AUTO_ATTRIBUTE,     0,   "%s inserting \"%s\" attribute using value \"%s\""                        }, /* Warning */
    { MISSING_ATTR_VALUE,           0,   "%s attribute \"%s\" lacks value"                                         }, /* Warning in CheckUrl, Error otherwise */
    { UNKNOWN_ATTRIBUTE,            0,   "%s unknown attribute \"%s\""                                             }, /* Error */
    { PROPRIETARY_ATTRIBUTE,        0,   "%s proprietary attribute \"%s\""                                         }, /* Error */
    { MISMATCHED_ATTRIBUTE_ERROR,   0,   "%s attribute \"%s\" not allowed for %s"                                  }, /* Error */
    { MISMATCHED_ATTRIBUTE_WARN,    0,   "%s attribute \"%s\" not allowed for %s"                                  }, /* Warning */
    { JOINING_ATTRIBUTE,            0,   "%s joining values of repeated attribute \"%s\""                          }, /* Error */
    { XML_ATTRIBUTE_VALUE,          0,   "%s has XML attribute \"%s\""                                             }, /* Error (but deprecated) */
    
    /* ReportAttrError - attribute value */
    { XML_ID_SYNTAX,                0,   "%s ID \"%s\" uses XML ID syntax"                                         }, /* Warning if XHTML, Error if HTML */
    { ATTR_VALUE_NOT_LCASE,         0,   "%s attribute value \"%s\" must be lower case for XHTML"                  }, /* Error if XHTML input, Notice if HTML input and XHTML outpout */
    { PROPRIETARY_ATTR_VALUE,       0,   "%s proprietary attribute value \"%s\""                                   }, /* Error */
    { ANCHOR_NOT_UNIQUE,            0,   "%s anchor \"%s\" already defined"                                        }, /* Error */
    
    /* ReportAttrError - attribute name, attribute value */
    { BAD_ATTRIBUTE_VALUE,          0,   "%s attribute \"%s\" has invalid value \"%s\""                            }, /* Error */
    { BAD_ATTRIBUTE_VALUE_REPLACED, 0,   "%s attribute \"%s\" had invalid value \"%s\" and has been replaced"      }, /* Error */
    { INVALID_ATTRIBUTE,            0,   "%s attribute name \"%s\" (value=\"%s\") is invalid"                      }, /* Error */
    
    /* ReportAttrError - attribute value, attribute name */
    { REPEATED_ATTRIBUTE,           0,   "%s dropping value \"%s\" for repeated attribute \"%s\""                  }, /* Error */
    
    /* ReportAttrError - no arguments */
    { INVALID_XML_ID,               0,   "%s cannot copy name attribute to id"                                     }, /* Warning */
    { UNEXPECTED_GT,                0,   "%s missing '>' for end of tag"                                           }, /* Warning if HTML, Error if XML/XHTML */
    { UNEXPECTED_QUOTEMARK,         0,   "%s unexpected or duplicate quote mark"                                   }, /* Error */
    { MISSING_QUOTEMARK,            0,   "%s attribute with missing trailing quote mark"                           }, /* Error */
    { UNEXPECTED_END_OF_FILE_ATTR,  0,   "%s end of file while parsing attributes"                                 }, /* Error */
    { ID_NAME_MISMATCH,             0,   "%s id and name attribute value mismatch"                                 }, /* Error */
    { BACKSLASH_IN_URI,             0,   "%s URI reference contains backslash. Typo?"                              }, /* Error */
    { FIXED_BACKSLASH,              0,   "%s converting backslash in URI to slash"                                 }, /* Error */
    { ILLEGAL_URI_REFERENCE,        0,   "%s improperly escaped URI reference"                                     }, /* Error */
    { ESCAPED_ILLEGAL_URI,          0,   "%s escaping malformed URI reference"                                     }, /* Error */
    { NEWLINE_IN_URI,               0,   "%s discarding newline in URI reference"                                  }, /* Error */
    { WHITE_IN_URI,                 0,   "%s discarding whitespace in URI reference"                               }, /* Error */
    { UNEXPECTED_EQUALSIGN,         0,   "%s unexpected '=', expected attribute name"                              }, /* Error */
    { MISSING_IMAGEMAP,             0,   "%s should use client-side image map"                                     }, /* Warning (but deprecated) */
    
    /* ReportMissingAttr */
    { MISSING_ATTRIBUTE,            0,   "%s lacks \"%s\" attribute"                                               }, /* Error */
    
    /* ReportWarning */
    { NESTED_EMPHASIS,              0,   "nested emphasis %s"                                                      }, /* Warning */
    { NESTED_QUOTATION,             0,   "nested q elements, possible typo."                                       }, /* Warning */
    { OBSOLETE_ELEMENT,             0,   "replacing obsolete element %s with %s"                                   }, /* Warning */
    { COERCE_TO_ENDTAG_WARN,        0,   "<%s> is probably intended as </%s>"                                      }, /* Warning */
    { REMOVED_HTML5,                0,   "%s element removed from HTML5"                                           }, /* Warning */
    { BAD_SUMMARY_HTML5,            0,   "The summary attribute on the %s element is obsolete in HTML5"            }, /* Warning */
    
    /* ReportNotice */
    { TRIM_EMPTY_ELEMENT,           0,   "trimming empty %s"                                                       }, /* Notice */
    { REPLACING_ELEMENT,            0,   "replacing %s with %s"                                                    }, /* Notice */
    
    /* ReportError */
    { COERCE_TO_ENDTAG,             0,   "<%s> is probably intended as </%s>"                                      }, /* Error */
    { REPLACING_UNEX_ELEMENT,       0,   "replacing unexpected %s with %s"                                         }, /* Error */
    { MISSING_ENDTAG_FOR,           0,   "missing </%s>"                                                           }, /* Error */
    { MISSING_ENDTAG_BEFORE,        0,   "missing </%s> before %s"                                                 }, /* Error */
    { DISCARDING_UNEXPECTED,        0,   "discarding unexpected %s"                                                }, /* Error */
    { NON_MATCHING_ENDTAG,          0,   "replacing unexpected %s with </%s>"                                      }, /* Error */
    { TAG_NOT_ALLOWED_IN,           0,   "%s isn't allowed in <%s> elements"                                       }, /* Error */
    { MISSING_STARTTAG,             0,   "missing <%s>"                                                            }, /* Error */
    { UNEXPECTED_ENDTAG,            0,   "unexpected </%s>"                                                        }, /* Error */
    { TOO_MANY_ELEMENTS,            0,   "too many %s elements"                                                    }, /* Error */
    { USING_BR_INPLACE_OF,          0,   "using <br> in place of %s"                                               }, /* Error */
    { INSERTING_TAG,                0,   "inserting implicit <%s>"                                                 }, /* Error */
    { CANT_BE_NESTED,               0,   "%s can't be nested"                                                      }, /* Error */
    { PROPRIETARY_ELEMENT,          0,   "%s is not approved by W3C"                                               }, /* Error */
    { ELEMENT_VERS_MISMATCH_ERROR,  0,   "%s element not available in %s"                                          }, /* Error */
    { ELEMENT_VERS_MISMATCH_WARN,   0,   "%s element not available in %s"                                          }, /* Warning */
    { ILLEGAL_NESTING,              0,   "%s shouldn't be nested"                                                  }, /* Error */
    { NOFRAMES_CONTENT,             0,   "%s not inside 'noframes' element"                                        }, /* Error */
    { UNEXPECTED_END_OF_FILE,       0,   "unexpected end of file %s"                                               }, /* Error */
    { ELEMENT_NOT_EMPTY,            0,   "%s element not empty or not closed"                                      }, /* Error */
    { UNEXPECTED_ENDTAG_IN,         0,   "unexpected </%s> in <%s>"                                                }, /* Error */
    { TOO_MANY_ELEMENTS_IN,         0,   "too many %s elements in <%s>"                                            }, /* Error */
    { UNESCAPED_ELEMENT,            0,   "unescaped %s in pre content"                                             }, /* Error (but deprecated) */
    
    /* ReportError - no arguments */
    { DOCTYPE_AFTER_TAGS,           0,   "<!DOCTYPE> isn't allowed after elements"                                 }, /* Error */
    { MISSING_TITLE_ELEMENT,        0,   "inserting missing 'title' element"                                       }, /* Error */
    { INCONSISTENT_VERSION,         0,   "HTML DOCTYPE doesn't match content"                                      }, /* Error */
    { MISSING_DOCTYPE,              0,   "missing <!DOCTYPE> declaration"                                          }, /* Error */
    { CONTENT_AFTER_BODY,           0,   "content occurs after end of body"                                        }, /* Error */
    { MALFORMED_COMMENT,            0,   "adjacent hyphens within comment"                                         }, /* Error */
    { BAD_COMMENT_CHARS,            0,   "expecting -- or >"                                                       }, /* Error */
    { BAD_CDATA_CONTENT,            0,   "'<' + '/' + letter not allowed here"                                     }, /* Error */
    { INCONSISTENT_NAMESPACE,       0,   "HTML namespace doesn't match content"                                    }, /* Error */
    { SPACE_PRECEDING_XMLDECL,      0,   "removing whitespace preceding XML Declaration"                           }, /* Error */
    { MALFORMED_DOCTYPE,            0,   "discarding malformed <!DOCTYPE>"                                         }, /* Error */
    { BAD_XML_COMMENT,              0,   "XML comments can't contain --"                                           }, /* Error (but deprecated) */
    { DTYPE_NOT_UPPER_CASE,         0,   "SYSTEM, PUBLIC, W3C, DTD, EN must be upper case"                         }, /* Error (but deprecated) */
    { ENCODING_IO_CONFLICT,         0,   "Output encoding does not work with standard output"                      }, /* Error (but deprecated) */
    
    /* ReportFatal */
    { SUSPECTED_MISSING_QUOTE,      0,   "missing quote mark for attribute value"                                  }, /* Error? (not really sometimes) */
    { DUPLICATE_FRAMESET,           0,   "repeated FRAMESET element"                                               }, /* Error */
    { UNKNOWN_ELEMENT,              0,   "%s is not recognized!"                                                   }, /* Error */
    
    /* Info */
    { PREVIOUS_LOCATION,            0,   "<%s> previously mentioned"                                               }, /* Info */
    
#if SUPPORT_ACCESSIBILITY_CHECKS
    
    /***************************************
     ** ReportAccess
     ** List of error/warning messages. The
     ** error code corresponds to the check
     ** that is listed in the AERT (HTML
     ** specifications).
     ***************************************/
    { IMG_MISSING_ALT,                               0,   "[1.1.1.1]: <img> missing 'alt' text."                                     }, /* Access */
    { IMG_ALT_SUSPICIOUS_FILENAME,                   0,   "[1.1.1.2]: suspicious 'alt' text (filename)."                             }, /* Access */
    { IMG_ALT_SUSPICIOUS_FILE_SIZE,                  0,   "[1.1.1.3]: suspicious 'alt' text (file size)."                            }, /* Access */
    { IMG_ALT_SUSPICIOUS_PLACEHOLDER,                0,   "[1.1.1.4]: suspicious 'alt' text (placeholder)."                          }, /* Access */
    { IMG_ALT_SUSPICIOUS_TOO_LONG,                   0,   "[1.1.1.10]: suspicious 'alt' text (too long)."                            }, /* Access */
    { IMG_MISSING_LONGDESC_DLINK,                    0,   "[1.1.2.1]: <img> missing 'longdesc' and d-link."                          }, /* Access */
    { IMG_MISSING_DLINK,                             0,   "[1.1.2.2]: <img> missing d-link."                                         }, /* Access */
    { IMG_MISSING_LONGDESC,                          0,   "[1.1.2.3]: <img> missing 'longdesc'."                                     }, /* Access */
    { IMG_BUTTON_MISSING_ALT,                        0,   "[1.1.3.1]: <img> (button) missing 'alt' text."                            }, /* Access */
    { APPLET_MISSING_ALT,                            0,   "[1.1.4.1]: <applet> missing alternate content."                           }, /* Access */
    { OBJECT_MISSING_ALT,                            0,   "[1.1.5.1]: <object> missing alternate content."                           }, /* Access */
    { AUDIO_MISSING_TEXT_WAV,                        0,   "[1.1.6.1]: audio missing text transcript (wav)."                          }, /* Access */
    { AUDIO_MISSING_TEXT_AU,                         0,   "[1.1.6.2]: audio missing text transcript (au)."                           }, /* Access */
    { AUDIO_MISSING_TEXT_AIFF,                       0,   "[1.1.6.3]: audio missing text transcript (aiff)."                         }, /* Access */
    { AUDIO_MISSING_TEXT_SND,                        0,   "[1.1.6.4]: audio missing text transcript (snd)."                          }, /* Access */
    { AUDIO_MISSING_TEXT_RA,                         0,   "[1.1.6.5]: audio missing text transcript (ra)."                           }, /* Access */
    { AUDIO_MISSING_TEXT_RM,                         0,   "[1.1.6.6]: audio missing text transcript (rm)."                           }, /* Access */
    { FRAME_MISSING_LONGDESC,                        0,   "[1.1.8.1]: <frame> may require 'longdesc'."                               }, /* Access */
    { AREA_MISSING_ALT,                              0,   "[1.1.9.1]: <area> missing 'alt' text."                                    }, /* Access */
    { SCRIPT_MISSING_NOSCRIPT,                       0,   "[1.1.10.1]: <script> missing <noscript> section."                         }, /* Access */
    { ASCII_REQUIRES_DESCRIPTION,                    0,   "[1.1.12.1]: ascii art requires description."                              }, /* Access */
    { IMG_MAP_SERVER_REQUIRES_TEXT_LINKS,            0,   "[1.2.1.1]: image map (server-side) requires text links."                  }, /* Access */
    { MULTIMEDIA_REQUIRES_TEXT,                      0,   "[1.4.1.1]: multimedia requires synchronized text equivalents."            }, /* Access */
    { IMG_MAP_CLIENT_MISSING_TEXT_LINKS,             0,   "[1.5.1.1]: image map (client-side) missing text links."                   }, /* Access */
    { INFORMATION_NOT_CONVEYED_IMAGE,                0,   "[2.1.1.1]: ensure information not conveyed through color alone (image)."  }, /* Access */
    { INFORMATION_NOT_CONVEYED_APPLET,               0,   "[2.1.1.2]: ensure information not conveyed through color alone (applet)." }, /* Access */
    { INFORMATION_NOT_CONVEYED_OBJECT,               0,   "[2.1.1.3]: ensure information not conveyed through color alone (object)." }, /* Access */
    { INFORMATION_NOT_CONVEYED_SCRIPT,               0,   "[2.1.1.4]: ensure information not conveyed through color alone (script)." }, /* Access */
    { INFORMATION_NOT_CONVEYED_INPUT,                0,   "[2.1.1.5]: ensure information not conveyed through color alone (input)."  }, /* Access */
    { COLOR_CONTRAST_TEXT,                           0,   "[2.2.1.1]: poor color contrast (text)."                                   }, /* Access */
    { COLOR_CONTRAST_LINK,                           0,   "[2.2.1.2]: poor color contrast (link)."                                   }, /* Access */
    { COLOR_CONTRAST_ACTIVE_LINK,                    0,   "[2.2.1.3]: poor color contrast (active link)."                            }, /* Access */
    { COLOR_CONTRAST_VISITED_LINK,                   0,   "[2.2.1.4]: poor color contrast (visited link)."                           }, /* Access */
    { DOCTYPE_MISSING,                               0,   "[3.2.1.1]: <doctype> missing."                                            }, /* Access */
    { STYLE_SHEET_CONTROL_PRESENTATION,              0,   "[3.3.1.1]: use style sheets to control presentation."                     }, /* Access */
    { HEADERS_IMPROPERLY_NESTED,                     0,   "[3.5.1.1]: headers improperly nested."                                    }, /* Access */
    { POTENTIAL_HEADER_BOLD,                         0,   "[3.5.2.1]: potential header (bold)."                                      }, /* Access */
    { POTENTIAL_HEADER_ITALICS,                      0,   "[3.5.2.2]: potential header (italics)."                                   }, /* Access */
    { POTENTIAL_HEADER_UNDERLINE,                    0,   "[3.5.2.3]: potential header (underline)."                                 }, /* Access */
    { HEADER_USED_FORMAT_TEXT,                       0,   "[3.5.3.1]: header used to format text."                                   }, /* Access */
    { LIST_USAGE_INVALID_UL,                         0,   "[3.6.1.1]: list usage invalid <ul>."                                      }, /* Access */
    { LIST_USAGE_INVALID_OL,                         0,   "[3.6.1.2]: list usage invalid <ol>."                                      }, /* Access */
    { LIST_USAGE_INVALID_LI,                         0,   "[3.6.1.4]: list usage invalid <li>."                                      }, /* Access */
    { INDICATE_CHANGES_IN_LANGUAGE,                  0,   "[4.1.1.1]: indicate changes in language."                                 }, /* Access */
    { LANGUAGE_NOT_IDENTIFIED,                       0,   "[4.3.1.1]: language not identified."                                      }, /* Access */
    { LANGUAGE_INVALID,                              0,   "[4.3.1.2]: language attribute invalid."                                   }, /* Access */
    { DATA_TABLE_MISSING_HEADERS,                    0,   "[5.1.2.1]: data <table> missing row/column headers (all)."                }, /* Access */
    { DATA_TABLE_MISSING_HEADERS_COLUMN,             0,   "[5.1.2.2]: data <table> missing row/column headers (1 col)."              }, /* Access */
    { DATA_TABLE_MISSING_HEADERS_ROW,                0,   "[5.1.2.3]: data <table> missing row/column headers (1 row)."              }, /* Access */
    { DATA_TABLE_REQUIRE_MARKUP_COLUMN_HEADERS,      0,   "[5.2.1.1]: data <table> may require markup (column headers)."             }, /* Access */
    { DATA_TABLE_REQUIRE_MARKUP_ROW_HEADERS,         0,   "[5.2.1.2]: data <table> may require markup (row headers)."                }, /* Access */
    { LAYOUT_TABLES_LINEARIZE_PROPERLY,              0,   "[5.3.1.1]: verify layout tables linearize properly."                      }, /* Access */
    { LAYOUT_TABLE_INVALID_MARKUP,                   0,   "[5.4.1.1]: invalid markup used in layout <table>."                        }, /* Access */
    { TABLE_MISSING_SUMMARY,                         0,   "[5.5.1.1]: <table> missing summary."                                      }, /* Access */
    { TABLE_SUMMARY_INVALID_NULL,                    0,   "[5.5.1.2]: <table> summary invalid (null)."                               }, /* Access */
    { TABLE_SUMMARY_INVALID_SPACES,                  0,   "[5.5.1.3]: <table> summary invalid (spaces)."                             }, /* Access */
    { TABLE_SUMMARY_INVALID_PLACEHOLDER,             0,   "[5.5.1.6]: <table> summary invalid (placeholder text)."                   }, /* Access */
    { TABLE_MISSING_CAPTION,                         0,   "[5.5.2.1]: <table> missing <caption>."                                    }, /* Access */
    { TABLE_MAY_REQUIRE_HEADER_ABBR,                 0,   "[5.6.1.1]: <table> may require header abbreviations."                     }, /* Access */
    { TABLE_MAY_REQUIRE_HEADER_ABBR_NULL,            0,   "[5.6.1.2]: <table> header abbreviations invalid (null)."                  }, /* Access */
    { TABLE_MAY_REQUIRE_HEADER_ABBR_SPACES,          0,   "[5.6.1.3]: <table> header abbreviations invalid (spaces)."                }, /* Access */
    { STYLESHEETS_REQUIRE_TESTING_LINK,              0,   "[6.1.1.1]: style sheets require testing (link)."                          }, /* Access */
    { STYLESHEETS_REQUIRE_TESTING_STYLE_ELEMENT,     0,   "[6.1.1.2]: style sheets require testing (style element)."                 }, /* Access */
    { STYLESHEETS_REQUIRE_TESTING_STYLE_ATTR,        0,   "[6.1.1.3]: style sheets require testing (style attribute)."               }, /* Access */
    { FRAME_SRC_INVALID,                             0,   "[6.2.1.1]: <frame> source invalid."                                       }, /* Access */
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_APPLET,      0,   "[6.2.2.1]: text equivalents require updating (applet)."                   }, /* Access */
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_SCRIPT,      0,   "[6.2.2.2]: text equivalents require updating (script)."                   }, /* Access */
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_OBJECT,      0,   "[6.2.2.3]: text equivalents require updating (object)."                   }, /* Access */
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_SCRIPT,   0,   "[6.3.1.1]: programmatic objects require testing (script)."                }, /* Access */
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_OBJECT,   0,   "[6.3.1.2]: programmatic objects require testing (object)."                }, /* Access */
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_EMBED,    0,   "[6.3.1.3]: programmatic objects require testing (embed)."                 }, /* Access */
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_APPLET,   0,   "[6.3.1.4]: programmatic objects require testing (applet)."                }, /* Access */
    { FRAME_MISSING_NOFRAMES,                        0,   "[6.5.1.1]: <frameset> missing <noframes> section."                        }, /* Access */
    { NOFRAMES_INVALID_NO_VALUE,                     0,   "[6.5.1.2]: <noframes> section invalid (no value)."                        }, /* Access */
    { NOFRAMES_INVALID_CONTENT,                      0,   "[6.5.1.3]: <noframes> section invalid (content)."                         }, /* Access */
    { NOFRAMES_INVALID_LINK,                         0,   "[6.5.1.4]: <noframes> section invalid (link)."                            }, /* Access */
    { REMOVE_FLICKER_SCRIPT,                         0,   "[7.1.1.1]: remove flicker (script)."                                      }, /* Access */
    { REMOVE_FLICKER_OBJECT,                         0,   "[7.1.1.2]: remove flicker (object)."                                      }, /* Access */
    { REMOVE_FLICKER_EMBED,                          0,   "[7.1.1.3]: remove flicker (embed)."                                       }, /* Access */
    { REMOVE_FLICKER_APPLET,                         0,   "[7.1.1.4]: remove flicker (applet)."                                      }, /* Access */
    { REMOVE_FLICKER_ANIMATED_GIF,                   0,   "[7.1.1.5]: remove flicker (animated gif)."                                }, /* Access */
    { REMOVE_BLINK_MARQUEE,                          0,   "[7.2.1.1]: remove blink/marquee."                                         }, /* Access */
    { REMOVE_AUTO_REFRESH,                           0,   "[7.4.1.1]: remove auto-refresh."                                          }, /* Access */
    { REMOVE_AUTO_REDIRECT,                          0,   "[7.5.1.1]: remove auto-redirect."                                         }, /* Access */
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_SCRIPT, 0,   "[8.1.1.1]: ensure programmatic objects are accessible (script)."          }, /* Access */
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_OBJECT, 0,   "[8.1.1.2]: ensure programmatic objects are accessible (object)."          }, /* Access */
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_APPLET, 0,   "[8.1.1.3]: ensure programmatic objects are accessible (applet)."          }, /* Access */
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_EMBED,  0,   "[8.1.1.4]: ensure programmatic objects are accessible (embed)."           }, /* Access */
    { IMAGE_MAP_SERVER_SIDE_REQUIRES_CONVERSION,     0,   "[9.1.1.1]: image map (server-side) requires conversion."                  }, /* Access */
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_DOWN,  0,   "[9.3.1.1]: <script> not keyboard accessible (onMouseDown)."               }, /* Access */
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_UP,    0,   "[9.3.1.2]: <script> not keyboard accessible (onMouseUp)."                 }, /* Access */
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_CLICK,       0,   "[9.3.1.3]: <script> not keyboard accessible (onClick)."                   }, /* Access */
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OVER,  0,   "[9.3.1.4]: <script> not keyboard accessible (onMouseOver)."               }, /* Access */
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OUT,   0,   "[9.3.1.5]: <script> not keyboard accessible (onMouseOut)."                }, /* Access */
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_MOVE,  0,   "[9.3.1.6]: <script> not keyboard accessible (onMouseMove)."               }, /* Access */
    { NEW_WINDOWS_REQUIRE_WARNING_NEW,               0,   "[10.1.1.1]: new windows require warning (_new)."                          }, /* Access */
    { NEW_WINDOWS_REQUIRE_WARNING_BLANK,             0,   "[10.1.1.2]: new windows require warning (_blank)."                        }, /* Access */
    { FORM_CONTROL_REQUIRES_DEFAULT_TEXT,            0,   "[10.4.1.1]: form control requires default text."                          }, /* Access */
    { FORM_CONTROL_DEFAULT_TEXT_INVALID_NULL,        0,   "[10.4.1.2]: form control default text invalid (null)."                    }, /* Access */
    { FORM_CONTROL_DEFAULT_TEXT_INVALID_SPACES,      0,   "[10.4.1.3]: form control default text invalid (spaces)."                  }, /* Access */
    { REPLACE_DEPRECATED_HTML_APPLET,                0,   "[11.2.1.1]: replace deprecated html <applet>."                            }, /* Access */
    { REPLACE_DEPRECATED_HTML_BASEFONT,              0,   "[11.2.1.2]: replace deprecated html <basefont>."                          }, /* Access */
    { REPLACE_DEPRECATED_HTML_CENTER,                0,   "[11.2.1.3]: replace deprecated html <center>."                            }, /* Access */
    { REPLACE_DEPRECATED_HTML_DIR,                   0,   "[11.2.1.4]: replace deprecated html <dir>."                               }, /* Access */
    { REPLACE_DEPRECATED_HTML_FONT,                  0,   "[11.2.1.5]: replace deprecated html <font>."                              }, /* Access */
    { REPLACE_DEPRECATED_HTML_ISINDEX,               0,   "[11.2.1.6]: replace deprecated html <isindex>."                           }, /* Access */
    { REPLACE_DEPRECATED_HTML_MENU,                  0,   "[11.2.1.7]: replace deprecated html <menu>."                              }, /* Access */
    { REPLACE_DEPRECATED_HTML_S,                     0,   "[11.2.1.8]: replace deprecated html <s>."                                 }, /* Access */
    { REPLACE_DEPRECATED_HTML_STRIKE,                0,   "[11.2.1.9]: replace deprecated html <strike>."                            }, /* Access */
    { REPLACE_DEPRECATED_HTML_U,                     0,   "[11.2.1.10]: replace deprecated html <u>."                                }, /* Access */
    { FRAME_MISSING_TITLE,                           0,   "[12.1.1.1]: <frame> missing title."                                       }, /* Access */
    { FRAME_TITLE_INVALID_NULL,                      0,   "[12.1.1.2]: <frame> title invalid (null)."                                }, /* Access */
    { FRAME_TITLE_INVALID_SPACES,                    0,   "[12.1.1.3]: <frame> title invalid (spaces)."                              }, /* Access */
    { ASSOCIATE_LABELS_EXPLICITLY,                   0,   "[12.4.1.1]: associate labels explicitly with form controls."              }, /* Access */
    { ASSOCIATE_LABELS_EXPLICITLY_FOR,               0,   "[12.4.1.2]: associate labels explicitly with form controls (for)."        }, /* Access */
    { ASSOCIATE_LABELS_EXPLICITLY_ID,                0,   "[12.4.1.3]: associate labels explicitly with form controls (id)."         }, /* Access */
    { LINK_TEXT_NOT_MEANINGFUL,                      0,   "[13.1.1.1]: link text not meaningful."                                    }, /* Access */
    { LINK_TEXT_MISSING,                             0,   "[13.1.1.2]: link text missing."                                           }, /* Access */
    { LINK_TEXT_TOO_LONG,                            0,   "[13.1.1.3]: link text too long."                                          }, /* Access */
    { LINK_TEXT_NOT_MEANINGFUL_CLICK_HERE,           0,   "[13.1.1.4]: link text not meaningful (click here)."                       }, /* Access */
    { METADATA_MISSING,                              0,   "[13.2.1.1]: Metadata missing."                                            }, /* Access */
    { METADATA_MISSING_REDIRECT_AUTOREFRESH,         0,   "[13.2.1.3]: Metadata missing (redirect/auto-refresh)."                    }, /* Access */
    { SKIPOVER_ASCII_ART,                            0,   "[13.10.1.1]: skip over ascii art."                                        }, /* Access */
#endif /* SUPPORT_ACCESSIBILITY_CHECKS */
    
    
    /*********************************************************************
     ** Options Documentation
     **  As of 2016-January these descriptions are used uniquely by the
     **  console application but are made available for LibTidy users as
     **  well. Because we generate documentation from these descriptions
     **  it's important to use ONLY the following tags:
     **    <code>, <em>, <strong>, <br/>, <p>
     **  Note that the xslt processor requires <br/> to be self closing!
     *********************************************************************/
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyXmlDecl,                  0,
        "This option specifies if Tidy should add the XML declaration when "
        "outputting XML or XHTML. "
        "<br/>"
        "Note that if the input already includes an <code>&lt;?xml ... ?&gt;</code> "
        "declaration then this option will be ignored. "
        "<br/>"
        "If the encoding for the output is different from <var>ascii</var>, one "
        "of the <var>utf*</var> encodings, or <var>raw</var>, then the "
        "declaration is always added as required by the XML standard. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyXmlSpace,                 0,
        "This option specifies if Tidy should add "
        "<code>xml:space=\"preserve\"</code> to elements such as "
        "<code>&lt;pre&gt;</code>, <code>&lt;style&gt;</code> and "
        "<code>&lt;script&gt;</code> when generating XML. "
        "<br/>"
        "This is needed if the whitespace in such elements is to "
        "be parsed appropriately without having access to the DTD. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyAltText,                  0,
        "This option specifies the default <code>alt=</code> text Tidy uses for "
        "<code>&lt;img&gt;</code> attributes when the <code>alt=</code> attribute "
        "is missing. "
        "<br/>"
        "Use with care, as it is your responsibility to make your documents accessible "
        "to people who cannot see the images. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyXmlPIs,                   0,
        "This option specifies if Tidy should change the parsing of processing "
        "instructions to require <code>?&gt;</code> as the terminator rather than "
        "<code>&gt;</code>. "
        "<br/>"
        "This option is automatically set if the input is in XML. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyMakeBare,                 0,
        "This option specifies if Tidy should strip Microsoft specific HTML "
        "from Word 2000 documents, and output spaces rather than non-breaking "
        "spaces where they exist in the input. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyCSSPrefix,                0,
        "This option specifies the prefix that Tidy uses for styles rules. "
        "<br/>"
        "By default, <var>c</var> will be used. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyMakeClean,                0,
        "This option specifies if Tidy should perform cleaning of some legacy "
        "presentational tags (currently <code>&lt;i&gt;</code>, "
        "<code>&lt;b&gt;</code>, <code>&lt;center&gt;</code> when enclosed within "
        "appropriate inline tags, and <code>&lt;font&gt;</code>). If set to "
        "<var>yes</var> then legacy tags will be replaced with CSS "
        "<code>&lt;style&gt;</code> tags and structural markup as appropriate. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyGDocClean,                0,
        "This option specifies if Tidy should enable specific behavior for "
        "cleaning up HTML exported from Google Docs. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyDoctype,                  0,
        "This option specifies the DOCTYPE declaration generated by Tidy. "
        "<br/>"
        "If set to <var>omit</var> the output won't contain a DOCTYPE "
        "declaration. Note this this also implies <code>numeric-entities</code> is "
        "set to <var>yes</var>."
        "<br/>"
        "If set to <var>html5</var> the DOCTYPE is set to "
        "<code>&lt;!DOCTYPE html&gt;</code>."
        "<br/>"
        "If set to <var>auto</var> (the default) Tidy will use an educated guess "
        "based upon the contents of the document."
        "<br/>"
        "If set to <var>strict</var>, Tidy will set the DOCTYPE to the HTML4 or "
        "XHTML1 strict DTD."
        "<br/>"
        "If set to <var>loose</var>, the DOCTYPE is set to the HTML4 or XHTML1 "
        "loose (transitional) DTD."
        "<br/>"
        "Alternatively, you can supply a string for the formal public identifier "
        "(FPI)."
        "<br/>"
        "For example: "
        "<br/>"
        "<code>doctype: \"-//ACME//DTD HTML 3.14159//EN\"</code>"
        "<br/>"
        "If you specify the FPI for an XHTML document, Tidy will set the "
        "system identifier to an empty string. For an HTML document, Tidy adds a "
        "system identifier only if one was already present in order to preserve "
        "the processing mode of some browsers. Tidy leaves the DOCTYPE for "
        "generic XML documents unchanged. "
        "<br/>"
        "This option does not offer a validation of document conformance. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyDropEmptyElems,           0,
        "This option specifies if Tidy should discard empty elements. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyDropEmptyParas,           0,
        "This option specifies if Tidy should discard empty paragraphs. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyDropFontTags,             0,
        "Deprecated; <em>do not use</em>. This option is destructive to "
        "<code>&lt;font&gt;</code> tags, and it will be removed from future "
        "versions of Tidy. Use the <code>clean</code> option instead. "
        "<br/>"
        "If you do set this option despite the warning it will perform "
        "as <code>clean</code> except styles will be inline instead of put into "
        "a CSS class. <code>&lt;font&gt;</code> tags will be dropped completely "
        "and their styles will not be preserved. "
        "<br/>"
        "If both <code>clean</code> and this option are enabled, "
        "<code>&lt;font&gt;</code> tags will still be dropped completely, and "
        "other styles will be preserved in a CSS class instead of inline. "
        "<br/>"
        "See <code>clean</code> for more information. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyDropPropAttrs,            0,
        "This option specifies if Tidy should strip out proprietary attributes, "
        "such as Microsoft data binding attributes. Additionally attributes "
        "that aren't permitted in the output version of HTML will be dropped "
        "if used with <code>strict-tags-attributes</code>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyEncloseBlockText,         0,
        "This option specifies if Tidy should insert a <code>&lt;p&gt;</code> "
        "element to enclose any text it finds in any element that allows mixed "
        "content for HTML transitional but not HTML strict. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyEncloseBodyText,          0,
        "This option specifies if Tidy should enclose any text it finds in the "
        "body element within a <code>&lt;p&gt;</code> element."
        "<br/>"
        "This is useful when you want to take existing HTML and use it with a "
        "style sheet. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyEscapeCdata,              0,
        "This option specifies if Tidy should convert "
        "<code>&lt;![CDATA[]]&gt;</code> sections to normal text. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyFixComments,              0,
        "This option specifies if Tidy should replace unexpected hyphens with "
        "<code>=</code> characters when it comes across adjacent hyphens. "
        "<br/>"
        "The default is <var>yes</var>. "
        "<br/>"
        "This option is provided for users of Cold Fusion which uses the "
        "comment syntax: <code>&lt;!--- ---&gt;</code>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyFixUri,                   0,
        "This option specifies if Tidy should check attribute values that carry "
        "URIs for illegal characters and if such are found, escape them as HTML4 "
        "recommends. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyHideComments,             0,
        "This option specifies if Tidy should print out comments. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyCoerceEndTags,            0,
        "This option specifies if Tidy should coerce a start tag into an end tag "
        "in cases where it looks like an end tag was probably intended; "
        "for example, given "
        "<br/>"
        "<code>&lt;span&gt;foo &lt;b&gt;bar&lt;b&gt; baz&lt;/span&gt;</code> "
        "<br/>"
        "Tidy will output "
        "<br/>"
        "<code>&lt;span&gt;foo &lt;b&gt;bar&lt;/b&gt; baz&lt;/span&gt;</code> "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyOmitOptionalTags,         0,
        "This option specifies if Tidy should omit optional start tags and end tags "
        "when generating output. "
        "<br/>"
        "Setting this option causes all tags for the <code>&lt;html&gt;</code>, "
        "<code>&lt;head&gt;</code>, and <code>&lt;body&gt;</code> elements to be "
        "omitted from output, as well as such end tags as <code>&lt;/p&gt;</code>, "
        "<code>&lt;/li&gt;</code>, <code>&lt;/dt&gt;</code>, "
        "<code>&lt;/dd&gt;</code>, <code>&lt;/option&gt;</code>, "
        "<code>&lt;/tr&gt;</code>, <code>&lt;/td&gt;</code>, and "
        "<code>&lt;/th&gt;</code>. "
        "<br/>"
        "This option is ignored for XML output. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyHideEndTags,              0,
        "This option is an alias for <code>omit-optional-tags</code>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyIndentCdata,              0,
        "This option specifies if Tidy should indent "
        "<code>&lt;![CDATA[]]&gt;</code> sections. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyXmlTags,                  0,
        "This option specifies if Tidy should use the XML parser rather than the "
        "error correcting HTML parser. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyJoinClasses,              0,
        "This option specifies if Tidy should combine class names to generate "
        "a single, new class name if multiple class assignments are detected on "
        "an element. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyJoinStyles,               0,
        "This option specifies if Tidy should combine styles to generate a single, "
        "new style if multiple style values are detected on an element. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyLogicalEmphasis,          0,
        "This option specifies if Tidy should replace any occurrence of "
        "<code>&lt;i&gt;</code> with <code>&lt;em&gt;</code> and any occurrence of "
        "<code>&lt;b&gt;</code> with <code>&lt;strong&gt;</code>. Any attributes "
        "are preserved unchanged. "
        "<br/>"
        "This option can be set independently of the <code>clean</code> option. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyLowerLiterals,            0,
        "This option specifies if Tidy should convert the value of an attribute "
        "that takes a list of predefined values to lower case. "
        "<br/>"
        "This is required for XHTML documents. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyMergeEmphasis,            0,
        "This option specifies if Tidy should merge nested <code>&lt;b&gt;</code> "
        "and <code>&lt;i&gt;</code> elements; for example, for the case "
        "<br/>"
        "<code>&lt;b class=\"rtop-2\"&gt;foo &lt;b class=\"r2-2\"&gt;bar&lt;/b&gt; baz&lt;/b&gt;</code>, "
        "<br/>"
        "Tidy will output <code>&lt;b class=\"rtop-2\"&gt;foo bar baz&lt;/b&gt;</code>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyMergeDivs,                0,
        "This option can be used to modify the behavior of <code>clean</code> when "
        "set to <var>yes</var>."
        "<br/>"
        "This option specifies if Tidy should merge nested <code>&lt;div&gt;</code> "
        "such as <code>&lt;div&gt;&lt;div&gt;...&lt;/div&gt;&lt;/div&gt;</code>. "
        "<br/>"
        "If set to <var>auto</var> the attributes of the inner "
        "<code>&lt;div&gt;</code> are moved to the outer one. Nested "
        "<code>&lt;div&gt;</code> with <code>id</code> attributes are <em>not</em> "
        "merged. "
        "<br/>"
        "If set to <var>yes</var> the attributes of the inner "
        "<code>&lt;div&gt;</code> are discarded with the exception of "
        "<code>class</code> and <code>style</code>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyMergeSpans,               0,
        "This option can be used to modify the behavior of <code>clean</code> when "
        "set to <var>yes</var>."
        "<br/>"
        "This option specifies if Tidy should merge nested <code>&lt;span&gt;</code> "
        "such as <code>&lt;span&gt;&lt;span&gt;...&lt;/span&gt;&lt;/span&gt;</code>. "
        "<br/>"
        "The algorithm is identical to the one used by <code>merge-divs</code>. "
    },
#if SUPPORT_ASIAN_ENCODINGS
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyNCR,                      0,
        "This option specifies if Tidy should allow numeric character references. "
    },
#endif
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyBlockTags,                0,
        "This option specifies new block-level tags. This option takes a space or "
        "comma separated list of tag names. "
        "<br/>"
        "Unless you declare new tags, Tidy will refuse to generate a tidied file if "
        "the input includes previously unknown tags. "
        "<br/>"
        "Note you can't change the content model for elements such as "
        "<code>&lt;table&gt;</code>, <code>&lt;ul&gt;</code>, "
        "<code>&lt;ol&gt;</code> and <code>&lt;dl&gt;</code>. "
        "<br/>"
        "This option is ignored in XML mode. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyEmptyTags,                0,
        "This option specifies new empty inline tags. This option takes a space "
        "or comma separated list of tag names. "
        "<br/>"
        "Unless you declare new tags, Tidy will refuse to generate a tidied file if "
        "the input includes previously unknown tags. "
        "<br/>"
        "Remember to also declare empty tags as either inline or blocklevel. "
        "<br/>"
        "This option is ignored in XML mode. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyInlineTags,               0,
        "This option specifies new non-empty inline tags. This option takes a "
        "space or comma separated list of tag names. "
        "<br/>"
        "Unless you declare new tags, Tidy will refuse to generate a tidied file if "
        "the input includes previously unknown tags. "
        "<br/>"
        "This option is ignored in XML mode. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyPreTags,                  0,
        "This option specifies new tags that are to be processed in exactly the "
        "same way as HTML's <code>&lt;pre&gt;</code> element. This option takes a "
        "space or comma separated list of tag names. "
        "<br/>"
        "Unless you declare new tags, Tidy will refuse to generate a tidied file if "
        "the input includes previously unknown tags. "
        "<br/>"
        "Note you cannot as yet add new CDATA elements. "
        "<br/>"
        "This option is ignored in XML mode. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyNumEntities,              0,
        "This option specifies if Tidy should output entities other than the "
        "built-in HTML entities (<code>&amp;amp;</code>, <code>&amp;lt;</code>, "
        "<code>&amp;gt;</code>, and <code>&amp;quot;</code>) in the numeric rather "
        "than the named entity form. "
        "<br/>"
        "Only entities compatible with the DOCTYPE declaration generated are used. "
        "<br/>"
        "Entities that can be represented in the output encoding are translated "
        "correspondingly. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyHtmlOut,                  0,
        "This option specifies if Tidy should generate pretty printed output, "
        "writing it as HTML. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyXhtmlOut,                 0,
        "This option specifies if Tidy should generate pretty printed output, "
        "writing it as extensible HTML. "
        "<br/>"
        "This option causes Tidy to set the DOCTYPE and default namespace as "
        "appropriate to XHTML, and will use the corrected value in output "
        "regardless of other sources. "
        "<br/>"
        "For XHTML, entities can be written as named or numeric entities according "
        "to the setting of <code>numeric-entities</code>. "
        "<br/>"
        "The original case of tags and attributes will be preserved, regardless of "
        "other options. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyXmlOut,                   0,
        "This option specifies if Tidy should pretty print output, writing it as "
        "well-formed XML. "
        "<br/>"
        "Any entities not defined in XML 1.0 will be written as numeric entities to "
        "allow them to be parsed by an XML parser. "
        "<br/>"
        "The original case of tags and attributes will be preserved, regardless of "
        "other options. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyQuoteAmpersand,           0,
        "This option specifies if Tidy should output unadorned <code>&amp;</code> "
        "characters as <code>&amp;amp;</code>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyQuoteMarks,               0,
        "This option specifies if Tidy should output <code>&quot;</code> characters "
        "as <code>&amp;quot;</code> as is preferred by some editing environments. "
        "<br/>"
        "The apostrophe character <code>'</code> is written out as "
        "<code>&amp;#39;</code> since many web browsers don't yet support "
        "<code>&amp;apos;</code>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyQuoteNbsp,                0,
        "This option specifies if Tidy should output non-breaking space characters "
        "as entities, rather than as the Unicode character value 160 (decimal). "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyDuplicateAttrs,           0,
        "This option specifies if Tidy should keep the first or last attribute, if "
        "an attribute is repeated, e.g. has two <code>align</code> attributes. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidySortAttributes,           0,
        "This option specifies that Tidy should sort attributes within an element "
        "using the specified sort algorithm. If set to <var>alpha</var>, the "
        "algorithm is an ascending alphabetic sort. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyReplaceColor,             0,
        "This option specifies if Tidy should replace numeric values in color "
        "attributes with HTML/XHTML color names where defined, e.g. replace "
        "<code>#ffffff</code> with <code>white</code>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyBodyOnly,                 0,
        "This option specifies if Tidy should print only the contents of the "
        "body tag as an HTML fragment. "
        "<br/>"
        "If set to <var>auto</var>, this is performed only if the body tag has "
        "been inferred. "
        "<br/>"
        "Useful for incorporating existing whole pages as a portion of another "
        "page. "
        "<br/>"
        "This option has no effect if XML output is requested. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyUpperCaseAttrs,           0,
        "This option specifies if Tidy should output attribute names in upper "
        "case. "
        "<br/>"
        "The default is <var>no</var>, which results in lower case attribute "
        "names, except for XML input, where the original case is preserved. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyUpperCaseTags,            0,
        "This option specifies if Tidy should output tag names in upper case. "
        "<br/>"
        "The default is <var>no</var> which results in lower case tag names, "
        "except for XML input where the original case is preserved. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyWord2000,                 0,
        "This option specifies if Tidy should go to great pains to strip out all "
        "the surplus stuff Microsoft Word 2000 inserts when you save Word "
        "documents as \"Web pages\". It doesn't handle embedded images or VML. "
        "<br/>"
        "You should consider using Word's \"Save As: Web Page, Filtered\". "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyAccessibilityCheckLevel,  0,
        "This option specifies what level of accessibility checking, if any, "
        "that Tidy should perform. "
        "<br/>"
        "Level <var>0 (Tidy Classic)</var> is equivalent to Tidy Classic's accessibility "
        "checking. "
        "<br/>"
        "For more information on Tidy's accessibility checking, visit "
        "<a href=\"http://www.html-tidy.org/accessibility/\"> Tidy's Accessibility Page</a>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyShowErrors,               0,
        "This option specifies the number Tidy uses to determine if further errors "
        "should be shown. If set to <var>0</var>, then no errors are shown. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyShowInfo,                 0,
        "This option specifies if Tidy should display info-level messages. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyShowWarnings,             0,
        "This option specifies if Tidy should suppress warnings. This can be "
        "useful when a few errors are hidden in a flurry of warnings. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyBreakBeforeBR,            0,
        "This option specifies if Tidy should output a line break before each "
        "<code>&lt;br&gt;</code> element. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyIndentContent,            0,
        "This option specifies if Tidy should indent block-level tags. "
        "<br/>"
        "If set to <var>auto</var> Tidy will decide whether or not to indent the "
        "content of tags such as <code>&lt;title&gt;</code>, "
        "<code>&lt;h1&gt;</code>-<code>&lt;h6&gt;</code>, <code>&lt;li&gt;</code>, "
        "<code>&lt;td&gt;</code>, or <code>&lt;p&gt;</code> "
        "based on the content including a block-level element. "
        "<br/>"
        "Setting <code>indent</code> to <var>yes</var> can expose layout bugs in "
        "some browsers. "
        "<br/>"
        "Use the option <code>indent-spaces</code> to control the number of spaces "
        "or tabs output per level of indent, and <code>indent-with-tabs</code> to "
        "specify whether spaces or tabs are used. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyIndentAttributes,         0,
        "This option specifies if Tidy should begin each attribute on a new line. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyIndentSpaces,             0,
        "This option specifies the number of spaces or tabs that Tidy uses to "
        "indent content when <code>indent</code> is enabled. "
        "<br/>"
        "Note that the default value for this option is dependent upon the value of "
        "<code>indent-with-tabs</code> (see also). "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyLiteralAttribs,           0,
        "This option specifies how Tidy deals with whitespace characters within "
        "attribute values. "
        "<br/>"
        "If the value is <var>no</var> Tidy normalizes attribute values by "
        "replacing any newline or tab with a single space, and further by replacing "
        "any contiguous whitespace with a single space. "
        "<br/>"
        "To force Tidy to preserve the original, literal values of all attributes "
        "and ensure that whitespace within attribute values is passed "
        "through unchanged, set this option to <var>yes</var>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyShowMarkup,               0,
        "This option specifies if Tidy should generate a pretty printed version "
        "of the markup. Note that Tidy won't generate a pretty printed version if "
        "it finds significant errors (see <code>force-output</code>). "
    },
#if SUPPORT_ASIAN_ENCODINGS
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyPunctWrap,                0,
        "This option specifies if Tidy should line wrap after some Unicode or "
        "Chinese punctuation characters. "
    },
#endif
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyBurstSlides,              0,
        "This option has no function and is deprecated. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyTabSize,                  0,
        "This option specifies the number of columns that Tidy uses between "
        "successive tab stops. It is used to map tabs to spaces when reading the "
        "input. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyVertSpace,                0,
        "This option specifies if Tidy should add some extra empty lines for "
        "readability. "
        "<br/>"
        "The default is <var>no</var>. "
        "<br/>"
        "If set to <var>auto</var> Tidy will eliminate nearly all newline "
        "characters."
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyWrapLen,                  0,
        "This option specifies the right margin Tidy uses for line wrapping. "
        "<br/>"
        "Tidy tries to wrap lines so that they do not exceed this length. "
        "<br/>"
        "Set <code>wrap</code> to <var>0</var>(zero) if you want to disable line "
        "wrapping. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyWrapAsp,                  0,
        "This option specifies if Tidy should line wrap text contained within ASP "
        "pseudo elements, which look like: <code>&lt;% ... %&gt;</code>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyWrapAttVals,              0,
        "This option specifies if Tidy should line-wrap attribute values, meaning "
        "that if the value of an attribute causes a line to exceed the width "
        "specified by <code>wrap</code>, Tidy will add one or more line breaks to "
        "the value, causing it to be wrapped into multiple lines. "
        "<br/>"
        "Note that this option can be set independently of "
        "<code>wrap-script-literals</code>. "
        "By default Tidy replaces any newline or tab with a single space and "
        "replaces any sequences of whitespace with a single space. "
        "<br/>"
        "To force Tidy to preserve the original, literal values of all attributes, "
        "and ensure that whitespace characters within attribute values are passed "
        "through unchanged, set <code>literal-attributes</code> to "
        "<var>yes</var>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyWrapJste,                 0,
        "This option specifies if Tidy should line wrap text contained within "
        "JSTE pseudo elements, which look like: <code>&lt;# ... #&gt;</code>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyWrapPhp,                  0,
        "This option specifies if Tidy should line wrap text contained within PHP "
        "pseudo elements, which look like: <code>&lt;?php ... ?&gt;</code>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyWrapScriptlets,           0,
        "This option specifies if Tidy should line wrap string literals that "
        "appear in script attributes. "
        "<br/>"
        "Tidy wraps long script string literals by inserting a backslash character "
        "before the line break. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyWrapSection,              0,
        "This option specifies if Tidy should line wrap text contained within "
        "<code>&lt;![ ... ]&gt;</code> section tags. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyAsciiChars,               0,
        "Can be used to modify behavior of the <code>clean</code> option when set "
        "to <var>yes</var>. "
        "<br/>"
        "If set to <var>yes</var> when using <code>clean</code>, "
        "<code>&amp;emdash;</code>, <code>&amp;rdquo;</code>, and other named "
        "character entities are downgraded to their closest ASCII equivalents. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyCharEncoding,             0,
        "This option specifies the character encoding Tidy uses for both the input "
        "and output. "
        "<br/>"
        "For <var>ascii</var> Tidy will accept Latin-1 (ISO-8859-1) character "
        "values, but will use entities for all characters whose value &gt;127. "
        "<br/>"
        "For <var>raw</var>, Tidy will output values above 127 without "
        "translating them into entities. "
        "<br/>"
        "For <var>latin1</var>, characters above 255 will be written as entities. "
        "<br/>"
        "For <var>utf8</var>, Tidy assumes that both input and output are encoded "
        "as UTF-8. "
        "<br/>"
        "You can use <var>iso2022</var> for files encoded using the ISO-2022 "
        "family of encodings e.g. ISO-2022-JP. "
        "<br/>"
        "For <var>mac</var> and <var>win1252</var>, Tidy will accept vendor "
        "specific character values, but will use entities for all characters whose "
        "value &gt;127. "
        "<br/>"
        "For unsupported encodings, use an external utility to convert to and from "
        "UTF-8. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyInCharEncoding,           0,
        "This option specifies the character encoding Tidy uses for the input. See "
        "<code>char-encoding</code> for more info. "
    },
#if SUPPORT_ASIAN_ENCODINGS
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyLanguage,                 0,
        "Currently not used, but this option specifies the language Tidy would use "
        "if it were properly localized. For example: <var>en</var>. "
    },
#endif
#if SUPPORT_UTF16_ENCODINGS
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyOutputBOM,                0,
        "This option specifies if Tidy should write a Unicode Byte Order Mark "
        "character (BOM; also known as Zero Width No-Break Space; has value of "
        "U+FEFF) to the beginning of the output, and only applies to UTF-8 and "
        "UTF-16 output encodings. "
        "<br/>"
        "If set to <var>auto</var> this option causes Tidy to write a BOM to "
        "the output only if a BOM was present at the beginning of the input. "
        "<br/>"
        "A BOM is always written for XML/XHTML output using UTF-16 output "
        "encodings. "
    },
#endif
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyOutCharEncoding,          0,
        "This option specifies the character encoding Tidy uses for the output. "
        "<br/>"
        "Note that this may only be different from <code>input-encoding</code> for "
        "Latin encodings (<var>ascii</var>, <var>latin0</var>, "
        "<var>latin1</var>, <var>mac</var>, <var>win1252</var>, "
        "<var>ibm858</var>)."
        "<br/>"
        "See <code>char-encoding</code> for more information"
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyNewline,                  0,
        "The default is appropriate to the current platform. "
        "<br/>"
        "Genrally CRLF on PC-DOS, Windows and OS/2; CR on Classic Mac OS; and LF "
        "everywhere else (Linux, Mac OS X, and Unix). "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyErrFile,                  0,
        "This option specifies the error file Tidy uses for errors and warnings. "
        "Normally errors and warnings are output to <code>stderr</code>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyFixBackslash,             0,
        "This option specifies if Tidy should replace backslash characters "
        "<code>\\</code> in URLs with forward slashes <code>/</code>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyForceOutput,              0,
        "This option specifies if Tidy should produce output even if errors are "
        "encountered. "
        "<br/>"
        "Use this option with care; if Tidy reports an error, this "
        "means Tidy was not able to (or is not sure how to) fix the error, so the "
        "resulting output may not reflect your intention. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyEmacs,                    0,
        "This option specifies if Tidy should change the format for reporting "
        "errors and warnings to a format that is more easily parsed by GNU Emacs. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyEmacsFile,                0,
        "Used internally. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyKeepFileTimes,            0,
        "This option specifies if Tidy should keep the original modification time "
        "of files that Tidy modifies in place. "
        "<br/>"
        "Setting the option to <var>yes</var> allows you to tidy files without "
        "changing the file modification date, which may be useful with certain "
        "tools that use the modification date for things such as automatic server "
        "deployment."
        "<br/>"
        "Note this feature is not supported on some platforms. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyOutFile,                  0,
        "This option specifies the output file Tidy uses for markup. Normally "
        "markup is written to <code>stdout</code>. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyQuiet,                    0,
        "This option specifies if Tidy should output the summary of the numbers "
        "of errors and warnings, or the welcome or informational messages. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidySlideStyle,               0,
        "This option has no function and is deprecated. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyMark,                     0,
        "This option specifies if Tidy should add a <code>meta</code> element to "
        "the document head to indicate that the document has been tidied. "
        "<br/>"
        "Tidy won't add a meta element if one is already present. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyWriteBack,                0,
        "This option specifies if Tidy should write back the tidied markup to the "
        "same file it read from. "
        "<br/>"
        "You are advised to keep copies of important files before tidying them, as "
        "on rare occasions the result may not be what you expect. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyDecorateInferredUL,       0,
        "This option specifies if Tidy should decorate inferred "
        "<code>&lt;ul&gt;</code> elements with some CSS markup to avoid indentation "
        "to the right. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyPreserveEntities,         0,
        "This option specifies if Tidy should preserve well-formed entities "
        "as found in the input. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyAnchorAsName,             0,
        "This option controls the deletion or addition of the <code>name</code> "
        "attribute in elements where it can serve as anchor. "
        "<br/>"
        "If set to <var>yes</var> a <code>name</code> attribute, if not already "
        "existing, is added along an existing <code>id</code> attribute if the DTD "
        "allows it. "
        "<br/>"
        "If set to <var>no</var> any existing name attribute is removed if an "
        "<code>id</code> attribute exists or has been added. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyPPrintTabs,               0,
        "This option specifies if Tidy should indent with tabs instead of spaces, "
        "assuming <code>indent</code> is <var>yes</var>. "
        "<br/>"
        "Set it to <var>yes</var> to indent using tabs instead of the default "
        "spaces. "
        "<br/>"
        "Use the option <code>indent-spaces</code> to control the number of tabs "
        "output per level of indent. Note that when <code>indent-with-tabs</code> "
        "is enabled the default value of <code>indent-spaces</code> is reset to "
        "<var>1</var>. "
        "<br/>"
        "Note <code>tab-size</code> controls converting input tabs to spaces. Set "
        "it to zero to retain input tabs. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidySkipNested,               0,
        "This option specifies that Tidy should skip nested tags when parsing "
        "script and style data. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyStrictTagsAttr,           0,
        "This options ensures that tags and attributes are applicable for the "
        "version of HTML that Tidy outputs. When set to <var>yes</var> (the "
        "default) and the output document type is a strict doctype, then Tidy "
        "will report errors. If the output document type is a loose or "
        "transitional doctype, then Tidy will report warnings. "
        "<br/>"
        "Additionally if <code>drop-proprietary-attributes</code> is enabled, "
        "then not applicable attributes will be dropped, too. "
        "<br/>"
        "When set to <var>no</var>, these checks are not performed. "
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyEscapeScripts,          0,
        "This option causes items that look like closing tags, like <code>&lt;/g</code> to be escaped "
        "to <code>&lt;\\/g</code>. Set this option to 'no' if you do not want this."
    },

    /********************************************************
     ** Console Application
     **  Although these strings are not used within LibTidy
     **  and only for the console application, they are
     **  provided as part of LibTidy for convenience to
     **  developers.
     ********************************************************/
    { TC_CAT_DIAGNOSTICS,           0,   "diagnostics"                                                             },
    { TC_CAT_ENCODING,              0,   "encoding"                                                                },
    { TC_CAT_MARKUP,                0,   "markup"                                                                  },
    { TC_CAT_MISC,                  0,   "misc"                                                                    },
    { TC_CAT_PRETTYPRINT,           0,   "print"                                                                   },
    { TC_LABEL_COL,                 0,   "column"                                                                  },
    { TC_LABEL_FILE,                0,   "file"                                                                    },
    { TC_LABEL_LANG,                0,   "lang"                                                                    },
    { TC_LABEL_LEVL,                0,   "level"                                                                   },
    { TC_LABEL_OPT,                 0,   "option"                                                                  },
    { TC_MAIN_ERROR_LOAD_CONFIG,    0,   "Loading config file \"%s\" failed, err = %d"                             },
    { TC_OPT_ACCESS,                0,
        "do additional accessibility checks (<level> = 0, 1, 2, 3). 0 is "
        "assumed if <level> is missing."
    },
    { TC_OPT_ASCII,                 0,   "use ISO-8859-1 for input, US-ASCII for output"                           },
    { TC_OPT_ASHTML,                0,   "force XHTML to well formed HTML"                                         },
    { TC_OPT_ASXML,                 0,   "convert HTML to well formed XHTML"                                       },
    { TC_OPT_BARE,                  0,   "strip out smart quotes and em dashes, etc."                              },
    { TC_OPT_BIG5,                  0,   "use Big5 for both input and output"                                      },
    { TC_OPT_CLEAN,                 0,   "replace FONT, NOBR and CENTER tags with CSS"                             },
    { TC_OPT_CONFIG,                0,   "set configuration options from the specified <file>"                     },
    { TC_OPT_ERRORS,                0,   "show only errors and warnings"                                           },
    { TC_OPT_FILE,                  0,   "write errors and warnings to the specified <file>"                       },
    { TC_OPT_GDOC,                  0,   "produce clean version of html exported by Google Docs"                   },
    { TC_OPT_HELP,                  0,   "list the command line options"                                           },
    { TC_OPT_HELPCFG,               0,   "list all configuration options"                                          },
    { TC_OPT_HELPOPT,               0,   "show a description of the <option>"                                      },
    { TC_OPT_IBM858,                0,   "use IBM-858 (CP850+Euro) for input, US-ASCII for output"                 },
    { TC_OPT_INDENT,                0,   "indent element content"                                                  },
    { TC_OPT_ISO2022,               0,   "use ISO-2022 for both input and output"                                  },

    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_OPT_LANGUAGE,              0,
        "set Tidy's output language to <lang>. Specify '-language help' for more help. "
        "Use before output-causing arguments to ensure the language takes effect, e.g.,"
        "`tidy -lang es -lang help`."
    },

    { TC_OPT_LATIN0,                0,   "use ISO-8859-15 for input, US-ASCII for output"                          },
    { TC_OPT_LATIN1,                0,   "use ISO-8859-1 for both input and output"                                },
    { TC_OPT_MAC,                   0,   "use MacRoman for input, US-ASCII for output"                             },
    { TC_OPT_MODIFY,                0,   "modify the original input files"                                         },
    { TC_OPT_NUMERIC,               0,   "output numeric rather than named entities"                               },
    { TC_OPT_OMIT,                  0,   "omit optional start tags and end tags"                                   },
    { TC_OPT_OUTPUT,                0,   "write output to the specified <file>"                                    },
    { TC_OPT_QUIET,                 0,   "suppress nonessential output"                                            },
    { TC_OPT_RAW,                   0,   "output values above 127 without conversion to entities"                  },
    { TC_OPT_SHIFTJIS,              0,   "use Shift_JIS for both input and output"                                 },
    { TC_OPT_SHOWCFG,               0,   "list the current configuration settings"                                 },
    { TC_OPT_UPPER,                 0,   "force tags to upper case"                                                },
    { TC_OPT_UTF16,                 0,   "use UTF-16 for both input and output"                                    },
    { TC_OPT_UTF16BE,               0,   "use UTF-16BE for both input and output"                                  },
    { TC_OPT_UTF16LE,               0,   "use UTF-16LE for both input and output"                                  },
    { TC_OPT_UTF8,                  0,   "use UTF-8 for both input and output"                                     },

    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_OPT_VERSION,               0,   "show the version of Tidy"
    },

    { TC_OPT_WIN1252,               0,   "use Windows-1252 for input, US-ASCII for output"                         },
    { TC_OPT_WRAP,                  0,
        "wrap text at the specified <column>. 0 is assumed if <column> is "
        "missing. When this option is omitted, the default of the "
        "configuration option 'wrap' applies."
    },
    { TC_OPT_XML,                   0,   "specify the input is well formed XML"                                    },
    { TC_OPT_XMLCFG,                0,   "list all configuration options in XML format"                            },
    { TC_OPT_XMLHELP,               0,   "list the command line options in XML format"                             },

    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_OPT_XMLSTRG,               0,   "output all of Tidy's strings in XML format"
    },

    { TC_OPT_XMLERRS,               0,   "output error constants and strings in XML format"                        },

    { TC_OPT_XMLOPTS,               0,   "output option descriptions in XML format"                                },
    
    { TC_STRING_CONF_HEADER,        0,   "Configuration File Settings:"                                            },

    {/* Must be 27 characters or fewer. */
      TC_STRING_CONF_NAME,          0,   "Name"
    },
    {/* Must be 9 characters or fewer. */
      TC_STRING_CONF_TYPE,          0,   "Type"
    },
    {/* Must be 40 characters or fewer. */
      TC_STRING_CONF_VALUE,         0,   "Current Value"
    },
    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_STRING_CONF_NOTE,          0,   "Values marked with an *asterisk are calculated internally by HTML Tidy"
    },

    { TC_STRING_OPT_NOT_DOCUMENTED, 0,   "Warning: option `%s' is not documented."                                 },
    { TC_STRING_OUT_OF_MEMORY,      0,   "Out of memory. Bailing out."                                             },
    { TC_STRING_FATAL_ERROR,        0,   "Fatal error: impossible value for id='%d'."                              },
    { TC_STRING_FILE_MANIP,         0,   "File manipulation"                                                       },
    { TC_STRING_PROCESS_DIRECTIVES, 0,   "Processing directives"                                                   },
    { TC_STRING_CHAR_ENCODING,      0,   "Character encodings"                                                     },
    { TC_STRING_LANG_MUST_SPECIFY,  0,   "A POSIX or Windows locale must be specified."                            },

    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_STRING_LANG_NOT_FOUND,     0,   "Tidy doesn't have language '%s,' will use '%s' instead."
    },

    { TC_STRING_MISC,               0,   "Miscellaneous"                                                           },
    { TC_STRING_XML,                0,   "XML"                                                                     },
    { TC_STRING_MUST_SPECIFY,       0,   "A Tidy option name must be specified."                                   },

    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_STRING_UNKNOWN_OPTION,     0,   "HTML Tidy: unknown option: %c"
    },
    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_STRING_UNKNOWN_OPTION_B,   0,   "HTML Tidy: unknown option."
    },
    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_STRING_VERS_A,             0,   "HTML Tidy for %s version %s"
    },
    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_STRING_VERS_B,             0,   "HTML Tidy version %s"
    },

    {/* This console output should be limited to 78 characters per line.
        - %n represents the name of the executable from the file system, and is mostly like going to be "tidy".
        - %2 represents a version number, typically x.x.xx.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_1,                0,
        "\n"
        "%s [options...] [file...] [options...] [file...]\n"
        "Utility to clean up and pretty print HTML/XHTML/XML.\n"
        "\n"
        "This is modern HTML Tidy version %s.\n"
        "\n"
    },
    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated.
        - %s represents the platform, for example, "Mac OS X" or "Windows". */
      TC_TXT_HELP_2A,               0,
        "Command Line Arguments for HTML Tidy for %s:"
    },
    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_2B,               0,
        "Command Line Arguments for HTML Tidy:"
    },
    {/* This console output should be limited to 78 characters per line. 
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_3,                0,
        "\n"
        "Tidy Configuration Options\n"
        "==========================\n"
        "Use Tidy's configuration options as command line arguments in the form\n"
        "of \"--some-option <value>\", for example, \"--indent-with-tabs yes\".\n"
        "\n"
        "For a list of all configuration options, use \"-help-config\" or refer\n"
        "to the man page (if your OS has one).\n"
        "\n"
        "If your environment has an $HTML_TIDY variable set point to a Tidy \n"
        "configuration file then Tidy will attempt to use it.\n"
        "\n"
        "On some platforms Tidy will also attempt to use a configuration specified \n"
        "in /etc/tidy.conf or ~/.tidy.conf.\n"
        "\n"
        "Other\n"
        "=====\n"
        "Input/Output default to stdin/stdout respectively.\n"
        "\n"
        "Single letter options apart from -f may be combined\n"
        "as in:  tidy -f errs.txt -imu foo.html\n"
        "\n"
        "Information\n"
        "===========\n"
        "For more information about HTML Tidy, see\n"
        "  http://www.html-tidy.org/\n"
        "\n"
        "For more information on HTML, see the following:\n"
        "\n"
        "  HTML: Edition for Web Authors (the latest HTML specification)\n"
        "  http://dev.w3.org/html5/spec-author-view\n"
        "\n"
        "  HTML: The Markup Language (an HTML language reference)\n"
        "  http://dev.w3.org/html5/markup/\n"
        "\n"
        "File bug reports at https://github.com/htacg/tidy-html5/issues/\n"
        "or send questions and comments to public-htacg@w3.org.\n"
        "\n"
        "Validate your HTML documents using the W3C Nu Markup Validator:\n"
        "  http://validator.w3.org/nu/\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_CONFIG,           0,
        "\n"
        "HTML Tidy Configuration Settings\n"
        "\n"
        "Within a file, use the form:\n"
        "\n"
        "wrap: 72\n"
        "indent: no\n"
        "\n"
        "When specified on the command line, use the form:\n"
        "\n"
        "--wrap 72 --indent no\n"
        "\n"
    },
    { TC_TXT_HELP_CONFIG_NAME,      0,   "Name"                                                                    },
    { TC_TXT_HELP_CONFIG_TYPE,      0,   "Type"                                                                    },
    { TC_TXT_HELP_CONFIG_ALLW,      0,   "Allowable values"                                                        },
    {/* This console output should be limited to 78 characters per line.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_LANG_1,           0,
        "\n"
        "The --language (or --lang) option indicates which language Tidy \n"
        "should use to communicate its output. Please note that this is not \n"
        "a document translation service, and only affects the messages that \n"
        "Tidy communicates to you. \n"
        "\n"
        "When used from the command line the --language argument must \n"
        "be used before any arguments that result in output, otherwise Tidy \n"
        "will produce output before it knows which language to use. \n"
        "\n"
        "In addition to standard POSIX language codes, Tidy is capable of \n"
        "understanding legacy Windows language codes. Please note that this \n"
        "list indicates codes Tidy understands, and does not indicate that \n"
        "the language is currently installed. \n"
        "\n"
        "The rightmost column indicates how Tidy will understand the \n"
        "legacy Windows name.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_LANG_2,           0,
        "\n"
        "The following languages are currently installed in Tidy. Please \n"
        "note that there's no guarantee that they are complete; only that \n"
        "one developer or another started to add the language indicated. \n"
        "\n"
        "Incomplete localizations will default to \"en\" when necessary. \n"
        "Please report instances of incorrect strings to the Tidy team. \n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated.
        - The parameter %s is likely to be two to five characters, e.g., en or en_US. */
      TC_TXT_HELP_LANG_3,           0,
        "\n"
        "If Tidy is able to determine your locale then Tidy will use the \n"
        "locale's language automatically. For example Unix-like systems use a \n"
        "$LANG and/or $LC_ALL environment variable. Consult your operating \n"
        "system documentation for more information. \n"
        "\n"
        "Tidy is currently using locale %s. \n"
        "\n"
    },
    
    
    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST,      0,   NULL
    }
}};


#endif /* language_en_h */
