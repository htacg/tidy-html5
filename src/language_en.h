#ifndef language_en_h
#define language_en_h
/*
 * language_en.h
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
static languageDictionary language_en = {
	/* Specify the code for this language. */
	{ TIDY_LANGUAGE,                "en"                                                                      },
	
	/*****************************
	 ** Miscellaneous Strings
	 *****************************/
	{ ACCESS_URL,                   "http://www.w3.org/WAI/GL"                                                },
	{ ATRC_ACCESS_URL,              "http://www.html-tidy.org/accessibility/"                                 },
	{ FILE_CANT_OPEN,               "Can't open \"%s\"\n"                                                     },
	{ LINE_COLUMN_STRING,           "line %d column %d - "                                                    },
	{ STRING_CONTENT_LOOKS,         "Document content looks like %s"                                          },
	{ STRING_DISCARDING,            "discarding"                                                              },
	{ STRING_DOCTYPE_GIVEN,         "Doctype given is \"%s\""                                                 },
	{ STRING_ERROR,                 "error"                                                                   },
	{ STRING_ERROR_COUNT,           "%u %s, %u %s were found!"                                                },
	{ STRING_ERROR_PLURAL,          "errors"                                                                  },
	{ STRING_HELLO_ACCESS,          "\nAccessibility Checks: Version 0.1\n\n"                                 },
	{ STRING_HTML_PROPRIETARY,      "HTML Proprietary"                                                        },
	{ STRING_MISSING_MALFORMED,     "missing or malformed argument for option: %s"                            },
	{ STRING_NO_ERRORS,             "No warnings or errors were found.\n\n"                                   },
	{ STRING_NO_SYSID,              "No system identifier in emitted doctype"                                 },
	{ STRING_NOT_ALL_SHOWN,         " Not all warnings/errors were shown.\n\n"                                },
	{ STRING_PLAIN_TEXT,            "plain text"                                                              },
	{ STRING_REPLACING,             "replacing"                                                               },
	{ STRING_SPECIFIED,             "specified"                                                               },
	{ STRING_UNKNOWN_FILE,          "%s: can't open file \"%s\"\n"                                            },
	{ STRING_UNKNOWN_OPTION,        "unknown option: %s"                                                      },
	{ STRING_UNRECZD_OPTION,        "unrecognized option -%c use -help to list options\n"                     },
	{ STRING_WARNING,               "warning"                                                                 },
	{ STRING_WARNING_PLURAL,        "warnings"                                                                },
	{ STRING_XML_DECLARATION,       "XML declaration"                                                         },
	
	{ TEXT_HTML_T_ALGORITHM,
		" \n"
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
		" \n"
	},
	{ TEXT_WINDOWS_CHARS,
		"Characters codes for the Microsoft Windows fonts in the range\n"
		"128 - 159 may not be recognized on other platforms. You are\n"
		"instead recommended to use named entities, e.g. &trade; rather\n"
		"than Windows character code 153 (0x2122 in Unicode). Note that\n"
		"as of February 1998 few browsers support the new entities.\n\n"
	},
	{ TEXT_VENDOR_CHARS,
		"It is unlikely that vendor-specific, system-dependent encodings\n"
		"work widely enough on the World Wide Web; you should avoid using the \n"
		"%s character encoding, instead you are recommended to\n"
		"use named entities, e.g. &trade;.\n\n"
	},
	{ TEXT_SGML_CHARS,
		"Character codes 128 to 159 (U+0080 to U+009F) are not allowed in HTML;\n"
		"even if they were, they would likely be unprintable control characters.\n"
		"Tidy assumed you wanted to refer to a character with the same byte value in the \n"
		"%s encoding and replaced that reference with the Unicode equivalent.\n\n"
	},
	{ TEXT_INVALID_UTF8,
		"Character codes for UTF-8 must be in the range: U+0000 to U+10FFFF.\n"
		"The definition of UTF-8 in Annex D of ISO/IEC 10646-1:2000 also\n"
		"allows for the use of five- and six-byte sequences to encode\n"
		"characters that are outside the range of the Unicode character set;\n"
		"those five- and six-byte sequences are illegal for the use of\n"
		"UTF-8 as a transformation of Unicode characters. ISO/IEC 10646\n"
		"does not allow mapping of unpaired surrogates, nor U+FFFE and U+FFFF\n"
		"(but it does allow other noncharacters). For more information please refer to\n"
		"http://www.unicode.org/ and http://www.cl.cam.ac.uk/~mgk25/unicode.html\n\n"
	},
	{ TEXT_INVALID_UTF16,
		"Character codes for UTF-16 must be in the range: U+0000 to U+10FFFF.\n"
		"The definition of UTF-16 in Annex C of ISO/IEC 10646-1:2000 does not allow the\n"
		"mapping of unpaired surrogates. For more information please refer to\n"
		"http://www.unicode.org/ and http://www.cl.cam.ac.uk/~mgk25/unicode.html\n\n"
	},
	{ TEXT_INVALID_URI,
		"URIs must be properly escaped, they must not contain unescaped\n"
		"characters below U+0021 including the space character and not\n"
		"above U+007E. Tidy escapes the URI for you as recommended by\n"
		"HTML 4.01 section B.2.1 and XML 1.0 section 4.2.2. Some user agents\n"
		"use another algorithm to escape such URIs and some server-sided\n"
		"scripts depend on that. If you want to depend on that, you must\n"
		"escape the URI on your own. For more information please refer to\n"
		"http://www.w3.org/International/O-URL-and-ident.html\n\n"
	},
	{ TEXT_BAD_FORM,
		"You may need to move one or both of the <form> and </form>\n"
		"tags. HTML elements should be properly nested and form elements\n"
		"are no exception. For instance you should not place the <form>\n"
		"in one table cell and the </form> in another. If the <form> is\n"
		"placed before a table, the </form> cannot be placed inside the\n"
		"table! Note that one form can't be nested inside another!\n\n"
	},
	{ TEXT_BAD_MAIN,
		"Only one <main> element is allowed in a document.\n"
		"Subsequent <main> elements have been discarded, which may\n"
		"render the document invalid.\n"
	},
	{ TEXT_M_SUMMARY,
		"The table summary attribute should be used to describe\n"
		"the table structure. It is very helpful for people using\n"
		"non-visual browsers. The scope and headers attributes for\n"
		"table cells are useful for specifying which headers apply\n"
		"to each table cell, enabling non-visual browsers to provide\n"
		"a meaningful context for each cell.\n\n"
	},
	{ TEXT_M_IMAGE_ALT,
		"The alt attribute should be used to give a short description\n"
		"of an image; longer descriptions should be given with the\n"
		"longdesc attribute which takes a URL linked to the description.\n"
		"These measures are needed for people using non-graphical browsers.\n\n"
	},
	{ TEXT_M_IMAGE_MAP,
		"Use client-side image maps in preference to server-side image\n"
		"maps as the latter are inaccessible to people using non-\n"
		"graphical browsers. In addition, client-side maps are easier\n"
		"to set up and provide immediate feedback to users.\n\n"
	},
	{ TEXT_M_LINK_ALT,
		"For hypertext links defined using a client-side image map, you\n"
		"need to use the alt attribute to provide a textual description\n"
		"of the link for people using non-graphical browsers.\n\n"
	},
	{ TEXT_USING_FRAMES,
		"Pages designed using frames presents problems for\n"
		"people who are either blind or using a browser that\n"
		"doesn't support frames. A frames-based page should always\n"
		"include an alternative layout inside a NOFRAMES element.\n\n"
	},
	{ TEXT_ACCESS_ADVICE1,
		"For further advice on how to make your pages accessible\n"
		"see http://www.w3.org/WAI/GL"
	},
	{ TEXT_ACCESS_ADVICE2,
		" and http://www.html-tidy.org/accessibility/"
	},
	{ TEXT_USING_LAYER,
		"The Cascading Style Sheets (CSS) Positioning mechanism\n"
		"is recommended in preference to the proprietary <LAYER>\n"
		"element due to limited vendor support for LAYER.\n\n"
	},
	{ TEXT_USING_SPACER,
		"You are recommended to use CSS for controlling white\n"
		"space (e.g. for indentation, margins and line spacing).\n"
		"The proprietary <SPACER> element has limited vendor support.\n\n"
	},
	{ TEXT_USING_FONT,
		"You are recommended to use CSS to specify the font and\n"
		"properties such as its size and color. This will reduce\n"
		"the size of HTML files and make them easier to maintain\n"
		"compared with using <FONT> elements.\n\n"
	},
	{ TEXT_USING_NOBR,
		"You are recommended to use CSS to control line wrapping.\n"
		"Use \"white-space: nowrap\" to inhibit wrapping in place\n"
		"of inserting <NOBR>...</NOBR> into the markup.\n\n"
	},
	{ TEXT_USING_BODY,
		"You are recommended to use CSS to specify page and link colors\n"
	},
	{ TEXT_NEEDS_INTERVENTION,
		"This document has errors that must be fixed before\n"
		"using HTML Tidy to generate a tidied up version.\n\n"
	},
	{ TEXT_GENERAL_INFO,
		"About HTML Tidy: https://github.com/htacg/tidy-html5\n"
		"Bug reports and comments: https://github.com/htacg/tidy-html5/issues\n"
		"Or send questions and comments to: https://lists.w3.org/Archives/Public/public-htacg/\n"
		"Latest HTML specification: http://dev.w3.org/html5/spec-author-view/\n"
		"Validate your HTML documents: http://validator.w3.org/nu/\n"
		"Lobby your company to join the W3C: http://www.w3.org/Consortium\n"
	},
	{ TEXT_GENERAL_INFO_PLEA,
		"\n"
		"Do you speak a language other than English, or a different variant of \n"
		"English? Consider helping us to localize HTML Tidy. For details please see \n"
		"https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md\n"
	},

	
	/*****************************
	 ** Message Severity Level
	 *****************************/
	{ TidyInfoString,               "Info: "                                                                  },
	{ TidyWarningString,            "Warning: "                                                               },
	{ TidyConfigString,             "Config: "                                                                },
	{ TidyAccessString,             "Access: "                                                                },
	{ TidyErrorString,              "Error: "                                                                 },
	{ TidyBadDocumentString,        "Document: "                                                              },
	{ TidyFatalString,              "Panic: "                                                                 },
	
	/*****************************
	 ** Warnings and Errors
	 *****************************/
	
	/* ReportEncodingWarning */
	{ ENCODING_MISMATCH,            "specified input encoding (%s) does not match actual input encoding (%s)" }, /* Warning */
	
	/* ReportEncodingError */
	{ VENDOR_SPECIFIC_CHARS,        "%s invalid character code %s"                                            }, /* Error */
	{ INVALID_SGML_CHARS,           "%s invalid character code %s"                                            }, /* Error */
	{ INVALID_UTF8,                 "%s invalid UTF-8 bytes (char. code %s)"                                  }, /* Error */
	{ INVALID_UTF16,                "%s invalid UTF-16 surrogate pair (char. code %s)"                        }, /* Error */
	{ INVALID_NCR,                  "%s invalid numeric character reference %s"                               }, /* Error */
	
	/* ReportEntityError */
	{ MISSING_SEMICOLON,            "entity \"%s\" doesn't end in ';'"                                        }, /* Warning in HTML, Error in XML/XHTML */
	{ MISSING_SEMICOLON_NCR,        "numeric character reference \"%s\" doesn't end in ';'"                   }, /* Warning in HTML, Error in XML/XHTML */
	{ UNESCAPED_AMPERSAND,          "unescaped & which should be written as &amp;"                            }, /* Warning in HTML, Error in XHTML */
	{ UNKNOWN_ENTITY,               "unescaped & or unknown entity \"%s\""                                    }, /* Error */
	{ APOS_UNDEFINED,               "named entity &apos; only defined in XML/XHTML"                           }, /* Error in HTML (should only occur for HTML input) */
	
	/* ReportAttrError */
	
	/* attribute name */
	{ INSERTING_ATTRIBUTE,          "%s inserting \"%s\" attribute"                                           }, /* Warning in CheckLINK, Error otherwise */
	{ INSERTING_AUTO_ATTRIBUTE,     "%s inserting \"%s\" attribute using value \"%s\""                        }, /* Warning */
	{ MISSING_ATTR_VALUE,           "%s attribute \"%s\" lacks value"                                         }, /* Warning in CheckUrl, Error otherwise */
	{ UNKNOWN_ATTRIBUTE,            "%s unknown attribute \"%s\""                                             }, /* Error */
	{ PROPRIETARY_ATTRIBUTE,        "%s proprietary attribute \"%s\""                                         }, /* Error */
	{ JOINING_ATTRIBUTE,            "%s joining values of repeated attribute \"%s\""                          }, /* Error */
	{ XML_ATTRIBUTE_VALUE,          "%s has XML attribute \"%s\""                                             }, /* Error (but deprecated) */
	
	/* attribute value */
	{ XML_ID_SYNTAX,                "%s ID \"%s\" uses XML ID syntax"                                         }, /* Warning if XHTML, Error if HTML */
	{ ATTR_VALUE_NOT_LCASE,         "%s attribute value \"%s\" must be lower case for XHTML"                  }, /* Error if XHTML input, Notice if HTML input and XHTML outpout */
	{ PROPRIETARY_ATTR_VALUE,       "%s proprietary attribute value \"%s\""                                   }, /* Error */
	{ ANCHOR_NOT_UNIQUE,            "%s anchor \"%s\" already defined"                                        }, /* Error */
	
	/* attribute name, attribute value */
	{ BAD_ATTRIBUTE_VALUE,          "%s attribute \"%s\" has invalid value \"%s\""                            }, /* Error */
	{ BAD_ATTRIBUTE_VALUE_REPLACED, "%s attribute \"%s\" had invalid value \"%s\" and has been replaced"      }, /* Error */
	{ INVALID_ATTRIBUTE,            "%s attribute name \"%s\" (value=\"%s\") is invalid"                      }, /* Error */
	
	/* attribute value, attribute name */
	{ REPEATED_ATTRIBUTE,           "%s dropping value \"%s\" for repeated attribute \"%s\""                  }, /* Error */
	
	/* no arguments */
	{ INVALID_XML_ID,               "%s cannot copy name attribute to id"                                     }, /* Warning */
	{ UNEXPECTED_GT,                "%s missing '>' for end of tag"                                           }, /* Warning if HTML, Error if XML/XHTML */
	{ UNEXPECTED_QUOTEMARK,         "%s unexpected or duplicate quote mark"                                   }, /* Error */
	{ MISSING_QUOTEMARK,            "%s attribute with missing trailing quote mark"                           }, /* Error */
	{ UNEXPECTED_END_OF_FILE_ATTR,  "%s end of file while parsing attributes"                                 }, /* Error */
	{ ID_NAME_MISMATCH,             "%s id and name attribute value mismatch"                                 }, /* Error */
	{ BACKSLASH_IN_URI,             "%s URI reference contains backslash. Typo?"                              }, /* Error */
	{ FIXED_BACKSLASH,              "%s converting backslash in URI to slash"                                 }, /* Error */
	{ ILLEGAL_URI_REFERENCE,        "%s improperly escaped URI reference"                                     }, /* Error */
	{ ESCAPED_ILLEGAL_URI,          "%s escaping malformed URI reference"                                     }, /* Error */
	{ NEWLINE_IN_URI,               "%s discarding newline in URI reference"                                  }, /* Error */
	{ WHITE_IN_URI,                 "%s discarding whitespace in URI reference"                               }, /* Error */
	{ UNEXPECTED_EQUALSIGN,         "%s unexpected '=', expected attribute name"                              }, /* Error */
	{ MISSING_IMAGEMAP,             "%s should use client-side image map"                                     }, /* Warning (but deprecated) */
	
	/* ReportMissingAttr */
	{ MISSING_ATTRIBUTE,            "%s lacks \"%s\" attribute"                                               }, /* Error */
	/* ReportWarning */
	{ NESTED_EMPHASIS,              "nested emphasis %s"                                                      }, /* Warning */
	{ NESTED_QUOTATION,             "nested q elements, possible typo."                                       }, /* Warning */
	{ OBSOLETE_ELEMENT,             "replacing obsolete element %s with %s"                                   }, /* Warning */
	{ COERCE_TO_ENDTAG_WARN,        "<%s> is probably intended as </%s>"                                      }, /* Warning */
	/* HTML5 */
	{ REMOVED_HTML5,                "%s element removed from HTML5"                                           }, /* Warning */
	{ BAD_BODY_HTML5,               "Found attribute on body that is obsolete in HTML5. Use CSS"              }, /* Warning */
	{ BAD_ALIGN_HTML5,              "The align attribute on the %s element is obsolete. Use CSS"              }, /* Warning */
	{ BAD_SUMMARY_HTML5,            "The summary attribute on the %s element is obsolete in HTML5"            }, /* Warning */
	
	/* ReportNotice */
	{ TRIM_EMPTY_ELEMENT,           "trimming empty %s"                                                       }, /* Notice */
	{ REPLACING_ELEMENT,            "replacing %s with %s"                                                    }, /* Notice */
	
	/* ReportError */
	{ COERCE_TO_ENDTAG,             "<%s> is probably intended as </%s>"                                      }, /* Error */
	{ REPLACING_UNEX_ELEMENT,       "replacing unexpected %s with %s"                                         }, /* Error */
	{ MISSING_ENDTAG_FOR,           "missing </%s>"                                                           }, /* Error */
	{ MISSING_ENDTAG_BEFORE,        "missing </%s> before %s"                                                 }, /* Error */
	{ DISCARDING_UNEXPECTED,        "discarding unexpected %s"                                                }, /* Error */
	{ NON_MATCHING_ENDTAG,          "replacing unexpected %s with </%s>"                                      }, /* Error */
	{ TAG_NOT_ALLOWED_IN,           "%s isn't allowed in <%s> elements"                                       }, /* Error */
	{ MISSING_STARTTAG,             "missing <%s>"                                                            }, /* Error */
	{ UNEXPECTED_ENDTAG,            "unexpected </%s>"                                                        }, /* Error */
	{ TOO_MANY_ELEMENTS,            "too many %s elements"                                                    }, /* Error */
	{ USING_BR_INPLACE_OF,          "using <br> in place of %s"                                               }, /* Error */
	{ INSERTING_TAG,                "inserting implicit <%s>"                                                 }, /* Error */
	{ CANT_BE_NESTED,               "%s can't be nested"                                                      }, /* Error */
	{ PROPRIETARY_ELEMENT,          "%s is not approved by W3C"                                               }, /* Error */
	{ ILLEGAL_NESTING,              "%s shouldn't be nested"                                                  }, /* Error */
	{ NOFRAMES_CONTENT,             "%s not inside 'noframes' element"                                        }, /* Error */
	{ UNEXPECTED_END_OF_FILE,       "unexpected end of file %s"                                               }, /* Error */
	{ ELEMENT_NOT_EMPTY,            "%s element not empty or not closed"                                      }, /* Error */
	{ UNEXPECTED_ENDTAG_IN,         "unexpected </%s> in <%s>"                                                }, /* Error */
	{ TOO_MANY_ELEMENTS_IN,         "too many %s elements in <%s>"                                            }, /* Error */
	{ UNESCAPED_ELEMENT,            "unescaped %s in pre content"                                             }, /* Error (but deprecated) */
	
	/* no arguments */
	{ DOCTYPE_AFTER_TAGS,           "<!DOCTYPE> isn't allowed after elements"                                 }, /* Error */
	{ MISSING_TITLE_ELEMENT,        "inserting missing 'title' element"                                       }, /* Error */
	{ INCONSISTENT_VERSION,         "HTML DOCTYPE doesn't match content"                                      }, /* Error */
	{ MISSING_DOCTYPE,              "missing <!DOCTYPE> declaration"                                          }, /* Error */
	{ CONTENT_AFTER_BODY,           "content occurs after end of body"                                        }, /* Error */
	{ MALFORMED_COMMENT,            "adjacent hyphens within comment"                                         }, /* Error */
	{ BAD_COMMENT_CHARS,            "expecting -- or >"                                                       }, /* Error */
	{ BAD_CDATA_CONTENT,            "'<' + '/' + letter not allowed here"                                     }, /* Error */
	{ INCONSISTENT_NAMESPACE,       "HTML namespace doesn't match content"                                    }, /* Error */
	{ SPACE_PRECEDING_XMLDECL,      "removing whitespace preceding XML Declaration"                           }, /* Error */
	{ MALFORMED_DOCTYPE,            "discarding malformed <!DOCTYPE>"                                         }, /* Error */
	{ BAD_XML_COMMENT,              "XML comments can't contain --"                                           }, /* Error (but deprecated) */
	{ DTYPE_NOT_UPPER_CASE,         "SYSTEM, PUBLIC, W3C, DTD, EN must be upper case"                         }, /* Error (but deprecated) */
	{ ENCODING_IO_CONFLICT,         "Output encoding does not work with standard output"                      }, /* Error (but deprecated) */
	
	/* ReportFatal */
	{ SUSPECTED_MISSING_QUOTE,      "missing quote mark for attribute value"                                  }, /* Error? (not really sometimes) */
	{ DUPLICATE_FRAMESET,           "repeated FRAMESET element"                                               }, /* Error */
	{ UNKNOWN_ELEMENT,              "%s is not recognized!"                                                   }, /* Error */
	
	/* */
	{ PREVIOUS_LOCATION,            "<%s> previously mentioned"                                               }, /* Info */
	
#if SUPPORT_ACCESSIBILITY_CHECKS
	
	/* ReportAccess */
	/*
	 List of error/warning messages.  The error code corresponds to
	 the check that is listed in the AERT (HTML specifications).
	 */
	{ IMG_MISSING_ALT,                               "[1.1.1.1]: <img> missing 'alt' text."                                     }, /* Access */
	{ IMG_ALT_SUSPICIOUS_FILENAME,                   "[1.1.1.2]: suspicious 'alt' text (filename)."                             }, /* Access */
	{ IMG_ALT_SUSPICIOUS_FILE_SIZE,                  "[1.1.1.3]: suspicious 'alt' text (file size)."                            }, /* Access */
	{ IMG_ALT_SUSPICIOUS_PLACEHOLDER,                "[1.1.1.4]: suspicious 'alt' text (placeholder)."                          }, /* Access */
	{ IMG_ALT_SUSPICIOUS_TOO_LONG,                   "[1.1.1.10]: suspicious 'alt' text (too long)."                            }, /* Access */
	{ IMG_MISSING_LONGDESC_DLINK,                    "[1.1.2.1]: <img> missing 'longdesc' and d-link."                          }, /* Access */
	{ IMG_MISSING_DLINK,                             "[1.1.2.2]: <img> missing d-link."                                         }, /* Access */
	{ IMG_MISSING_LONGDESC,                          "[1.1.2.3]: <img> missing 'longdesc'."                                     }, /* Access */
	{ IMG_BUTTON_MISSING_ALT,                        "[1.1.3.1]: <img> (button) missing 'alt' text."                            }, /* Access */
	{ APPLET_MISSING_ALT,                            "[1.1.4.1]: <applet> missing alternate content."                           }, /* Access */
	{ OBJECT_MISSING_ALT,                            "[1.1.5.1]: <object> missing alternate content."                           }, /* Access */
	{ AUDIO_MISSING_TEXT_WAV,                        "[1.1.6.1]: audio missing text transcript (wav)."                          }, /* Access */
	{ AUDIO_MISSING_TEXT_AU,                         "[1.1.6.2]: audio missing text transcript (au)."                           }, /* Access */
	{ AUDIO_MISSING_TEXT_AIFF,                       "[1.1.6.3]: audio missing text transcript (aiff)."                         }, /* Access */
	{ AUDIO_MISSING_TEXT_SND,                        "[1.1.6.4]: audio missing text transcript (snd)."                          }, /* Access */
	{ AUDIO_MISSING_TEXT_RA,                         "[1.1.6.5]: audio missing text transcript (ra)."                           }, /* Access */
	{ AUDIO_MISSING_TEXT_RM,                         "[1.1.6.6]: audio missing text transcript (rm)."                           }, /* Access */
	{ FRAME_MISSING_LONGDESC,                        "[1.1.8.1]: <frame> may require 'longdesc'."                               }, /* Access */
	{ AREA_MISSING_ALT,                              "[1.1.9.1]: <area> missing 'alt' text."                                    }, /* Access */
	{ SCRIPT_MISSING_NOSCRIPT,                       "[1.1.10.1]: <script> missing <noscript> section."                         }, /* Access */
	{ ASCII_REQUIRES_DESCRIPTION,                    "[1.1.12.1]: ascii art requires description."                              }, /* Access */
	{ IMG_MAP_SERVER_REQUIRES_TEXT_LINKS,            "[1.2.1.1]: image map (server-side) requires text links."                  }, /* Access */
	{ MULTIMEDIA_REQUIRES_TEXT,                      "[1.4.1.1]: multimedia requires synchronized text equivalents."            }, /* Access */
	{ IMG_MAP_CLIENT_MISSING_TEXT_LINKS,             "[1.5.1.1]: image map (client-side) missing text links."                   }, /* Access */
	{ INFORMATION_NOT_CONVEYED_IMAGE,                "[2.1.1.1]: ensure information not conveyed through color alone (image)."  }, /* Access */
	{ INFORMATION_NOT_CONVEYED_APPLET,               "[2.1.1.2]: ensure information not conveyed through color alone (applet)." }, /* Access */
	{ INFORMATION_NOT_CONVEYED_OBJECT,               "[2.1.1.3]: ensure information not conveyed through color alone (object)." }, /* Access */
	{ INFORMATION_NOT_CONVEYED_SCRIPT,               "[2.1.1.4]: ensure information not conveyed through color alone (script)." }, /* Access */
	{ INFORMATION_NOT_CONVEYED_INPUT,                "[2.1.1.5]: ensure information not conveyed through color alone (input)."  }, /* Access */
	{ COLOR_CONTRAST_TEXT,                           "[2.2.1.1]: poor color contrast (text)."                                   }, /* Access */
	{ COLOR_CONTRAST_LINK,                           "[2.2.1.2]: poor color contrast (link)."                                   }, /* Access */
	{ COLOR_CONTRAST_ACTIVE_LINK,                    "[2.2.1.3]: poor color contrast (active link)."                            }, /* Access */
	{ COLOR_CONTRAST_VISITED_LINK,                   "[2.2.1.4]: poor color contrast (visited link)."                           }, /* Access */
	{ DOCTYPE_MISSING,                               "[3.2.1.1]: <doctype> missing."                                            }, /* Access */
	{ STYLE_SHEET_CONTROL_PRESENTATION,              "[3.3.1.1]: use style sheets to control presentation."                     }, /* Access */
	{ HEADERS_IMPROPERLY_NESTED,                     "[3.5.1.1]: headers improperly nested."                                    }, /* Access */
	{ POTENTIAL_HEADER_BOLD,                         "[3.5.2.1]: potential header (bold)."                                      }, /* Access */
	{ POTENTIAL_HEADER_ITALICS,                      "[3.5.2.2]: potential header (italics)."                                   }, /* Access */
	{ POTENTIAL_HEADER_UNDERLINE,                    "[3.5.2.3]: potential header (underline)."                                 }, /* Access */
	{ HEADER_USED_FORMAT_TEXT,                       "[3.5.3.1]: header used to format text."                                   }, /* Access */
	{ LIST_USAGE_INVALID_UL,                         "[3.6.1.1]: list usage invalid <ul>."                                      }, /* Access */
	{ LIST_USAGE_INVALID_OL,                         "[3.6.1.2]: list usage invalid <ol>."                                      }, /* Access */
	{ LIST_USAGE_INVALID_LI,                         "[3.6.1.4]: list usage invalid <li>."                                      }, /* Access */
	{ INDICATE_CHANGES_IN_LANGUAGE,                  "[4.1.1.1]: indicate changes in language."                                 }, /* Access */
	{ LANGUAGE_NOT_IDENTIFIED,                       "[4.3.1.1]: language not identified."                                      }, /* Access */
	{ LANGUAGE_INVALID,                              "[4.3.1.2]: language attribute invalid."                                   }, /* Access */
	{ DATA_TABLE_MISSING_HEADERS,                    "[5.1.2.1]: data <table> missing row/column headers (all)."                }, /* Access */
	{ DATA_TABLE_MISSING_HEADERS_COLUMN,             "[5.1.2.2]: data <table> missing row/column headers (1 col)."              }, /* Access */
	{ DATA_TABLE_MISSING_HEADERS_ROW,                "[5.1.2.3]: data <table> missing row/column headers (1 row)."              }, /* Access */
	{ DATA_TABLE_REQUIRE_MARKUP_COLUMN_HEADERS,      "[5.2.1.1]: data <table> may require markup (column headers)."             }, /* Access */
	{ DATA_TABLE_REQUIRE_MARKUP_ROW_HEADERS,         "[5.2.1.2]: data <table> may require markup (row headers)."                }, /* Access */
	{ LAYOUT_TABLES_LINEARIZE_PROPERLY,              "[5.3.1.1]: verify layout tables linearize properly."                      }, /* Access */
	{ LAYOUT_TABLE_INVALID_MARKUP,                   "[5.4.1.1]: invalid markup used in layout <table>."                        }, /* Access */
	{ TABLE_MISSING_SUMMARY,                         "[5.5.1.1]: <table> missing summary."                                      }, /* Access */
	{ TABLE_SUMMARY_INVALID_NULL,                    "[5.5.1.2]: <table> summary invalid (null)."                               }, /* Access */
	{ TABLE_SUMMARY_INVALID_SPACES,                  "[5.5.1.3]: <table> summary invalid (spaces)."                             }, /* Access */
	{ TABLE_SUMMARY_INVALID_PLACEHOLDER,             "[5.5.1.6]: <table> summary invalid (placeholder text)."                   }, /* Access */
	{ TABLE_MISSING_CAPTION,                         "[5.5.2.1]: <table> missing <caption>."                                    }, /* Access */
	{ TABLE_MAY_REQUIRE_HEADER_ABBR,                 "[5.6.1.1]: <table> may require header abbreviations."                     }, /* Access */
	{ TABLE_MAY_REQUIRE_HEADER_ABBR_NULL,            "[5.6.1.2]: <table> header abbreviations invalid (null)."                  }, /* Access */
	{ TABLE_MAY_REQUIRE_HEADER_ABBR_SPACES,          "[5.6.1.3]: <table> header abbreviations invalid (spaces)."                }, /* Access */
	{ STYLESHEETS_REQUIRE_TESTING_LINK,              "[6.1.1.1]: style sheets require testing (link)."                          }, /* Access */
	{ STYLESHEETS_REQUIRE_TESTING_STYLE_ELEMENT,     "[6.1.1.2]: style sheets require testing (style element)."                 }, /* Access */
	{ STYLESHEETS_REQUIRE_TESTING_STYLE_ATTR,        "[6.1.1.3]: style sheets require testing (style attribute)."               }, /* Access */
	{ FRAME_SRC_INVALID,                             "[6.2.1.1]: <frame> source invalid."                                       }, /* Access */
	{ TEXT_EQUIVALENTS_REQUIRE_UPDATING_APPLET,      "[6.2.2.1]: text equivalents require updating (applet)."                   }, /* Access */
	{ TEXT_EQUIVALENTS_REQUIRE_UPDATING_SCRIPT,      "[6.2.2.2]: text equivalents require updating (script)."                   }, /* Access */
	{ TEXT_EQUIVALENTS_REQUIRE_UPDATING_OBJECT,      "[6.2.2.3]: text equivalents require updating (object)."                   }, /* Access */
	{ PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_SCRIPT,   "[6.3.1.1]: programmatic objects require testing (script)."                }, /* Access */
	{ PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_OBJECT,   "[6.3.1.2]: programmatic objects require testing (object)."                }, /* Access */
	{ PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_EMBED,    "[6.3.1.3]: programmatic objects require testing (embed)."                 }, /* Access */
	{ PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_APPLET,   "[6.3.1.4]: programmatic objects require testing (applet)."                }, /* Access */
	{ FRAME_MISSING_NOFRAMES,                        "[6.5.1.1]: <frameset> missing <noframes> section."                        }, /* Access */
	{ NOFRAMES_INVALID_NO_VALUE,                     "[6.5.1.2]: <noframes> section invalid (no value)."                        }, /* Access */
	{ NOFRAMES_INVALID_CONTENT,                      "[6.5.1.3]: <noframes> section invalid (content)."                         }, /* Access */
	{ NOFRAMES_INVALID_LINK,                         "[6.5.1.4]: <noframes> section invalid (link)."                            }, /* Access */
	{ REMOVE_FLICKER_SCRIPT,                         "[7.1.1.1]: remove flicker (script)."                                      }, /* Access */
	{ REMOVE_FLICKER_OBJECT,                         "[7.1.1.2]: remove flicker (object)."                                      }, /* Access */
	{ REMOVE_FLICKER_EMBED,                          "[7.1.1.3]: remove flicker (embed)."                                       }, /* Access */
	{ REMOVE_FLICKER_APPLET,                         "[7.1.1.4]: remove flicker (applet)."                                      }, /* Access */
	{ REMOVE_FLICKER_ANIMATED_GIF,                   "[7.1.1.5]: remove flicker (animated gif)."                                }, /* Access */
	{ REMOVE_BLINK_MARQUEE,                          "[7.2.1.1]: remove blink/marquee."                                         }, /* Access */
	{ REMOVE_AUTO_REFRESH,                           "[7.4.1.1]: remove auto-refresh."                                          }, /* Access */
	{ REMOVE_AUTO_REDIRECT,                          "[7.5.1.1]: remove auto-redirect."                                         }, /* Access */
	{ ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_SCRIPT, "[8.1.1.1]: ensure programmatic objects are accessible (script)."          }, /* Access */
	{ ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_OBJECT, "[8.1.1.2]: ensure programmatic objects are accessible (object)."          }, /* Access */
	{ ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_APPLET, "[8.1.1.3]: ensure programmatic objects are accessible (applet)."          }, /* Access */
	{ ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_EMBED,  "[8.1.1.4]: ensure programmatic objects are accessible (embed)."           }, /* Access */
	{ IMAGE_MAP_SERVER_SIDE_REQUIRES_CONVERSION,     "[9.1.1.1]: image map (server-side) requires conversion."                  }, /* Access */
	{ SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_DOWN,  "[9.3.1.1]: <script> not keyboard accessible (onMouseDown)."               }, /* Access */
	{ SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_UP,    "[9.3.1.2]: <script> not keyboard accessible (onMouseUp)."                 }, /* Access */
	{ SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_CLICK,       "[9.3.1.3]: <script> not keyboard accessible (onClick)."                   }, /* Access */
	{ SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OVER,  "[9.3.1.4]: <script> not keyboard accessible (onMouseOver)."               }, /* Access */
	{ SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OUT,   "[9.3.1.5]: <script> not keyboard accessible (onMouseOut)."                }, /* Access */
	{ SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_MOVE,  "[9.3.1.6]: <script> not keyboard accessible (onMouseMove)."               }, /* Access */
	{ NEW_WINDOWS_REQUIRE_WARNING_NEW,               "[10.1.1.1]: new windows require warning (_new)."                          }, /* Access */
	{ NEW_WINDOWS_REQUIRE_WARNING_BLANK,             "[10.1.1.2]: new windows require warning (_blank)."                        }, /* Access */
	{ FORM_CONTROL_REQUIRES_DEFAULT_TEXT,            "[10.4.1.1]: form control requires default text."                          }, /* Access */
	{ FORM_CONTROL_DEFAULT_TEXT_INVALID_NULL,        "[10.4.1.2]: form control default text invalid (null)."                    }, /* Access */
	{ FORM_CONTROL_DEFAULT_TEXT_INVALID_SPACES,      "[10.4.1.3]: form control default text invalid (spaces)."                  }, /* Access */
	{ REPLACE_DEPRECATED_HTML_APPLET,                "[11.2.1.1]: replace deprecated html <applet>."                            }, /* Access */
	{ REPLACE_DEPRECATED_HTML_BASEFONT,              "[11.2.1.2]: replace deprecated html <basefont>."                          }, /* Access */
	{ REPLACE_DEPRECATED_HTML_CENTER,                "[11.2.1.3]: replace deprecated html <center>."                            }, /* Access */
	{ REPLACE_DEPRECATED_HTML_DIR,                   "[11.2.1.4]: replace deprecated html <dir>."                               }, /* Access */
	{ REPLACE_DEPRECATED_HTML_FONT,                  "[11.2.1.5]: replace deprecated html <font>."                              }, /* Access */
	{ REPLACE_DEPRECATED_HTML_ISINDEX,               "[11.2.1.6]: replace deprecated html <isindex>."                           }, /* Access */
	{ REPLACE_DEPRECATED_HTML_MENU,                  "[11.2.1.7]: replace deprecated html <menu>."                              }, /* Access */
	{ REPLACE_DEPRECATED_HTML_S,                     "[11.2.1.8]: replace deprecated html <s>."                                 }, /* Access */
	{ REPLACE_DEPRECATED_HTML_STRIKE,                "[11.2.1.9]: replace deprecated html <strike>."                            }, /* Access */
	{ REPLACE_DEPRECATED_HTML_U,                     "[11.2.1.10]: replace deprecated html <u>."                                }, /* Access */
	{ FRAME_MISSING_TITLE,                           "[12.1.1.1]: <frame> missing title."                                       }, /* Access */
	{ FRAME_TITLE_INVALID_NULL,                      "[12.1.1.2]: <frame> title invalid (null)."                                }, /* Access */
	{ FRAME_TITLE_INVALID_SPACES,                    "[12.1.1.3]: <frame> title invalid (spaces)."                              }, /* Access */
	{ ASSOCIATE_LABELS_EXPLICITLY,                   "[12.4.1.1]: associate labels explicitly with form controls."              }, /* Access */
	{ ASSOCIATE_LABELS_EXPLICITLY_FOR,               "[12.4.1.2]: associate labels explicitly with form controls (for)."        }, /* Access */
	{ ASSOCIATE_LABELS_EXPLICITLY_ID,                "[12.4.1.3]: associate labels explicitly with form controls (id)."         }, /* Access */
	{ LINK_TEXT_NOT_MEANINGFUL,                      "[13.1.1.1]: link text not meaningful."                                    }, /* Access */
	{ LINK_TEXT_MISSING,                             "[13.1.1.2]: link text missing."                                           }, /* Access */
	{ LINK_TEXT_TOO_LONG,                            "[13.1.1.3]: link text too long."                                          }, /* Access */
	{ LINK_TEXT_NOT_MEANINGFUL_CLICK_HERE,           "[13.1.1.4]: link text not meaningful (click here)."                       }, /* Access */
	{ METADATA_MISSING,                              "[13.2.1.1]: Metadata missing."                                            }, /* Access */
	{ METADATA_MISSING_REDIRECT_AUTOREFRESH,         "[13.2.1.3]: Metadata missing (redirect/auto-refresh)."                    }, /* Access */
	{ SKIPOVER_ASCII_ART,                            "[13.10.1.1]: skip over ascii art."                                        }, /* Access */
#endif /* SUPPORT_ACCESSIBILITY_CHECKS */
	
	/*****************************
	 ** Options Documentation
	 *****************************/
	/*
	 * As of 2015-November these descriptions are used uniquely by
	 * printXMLDescription from which quickref.html and the Unix
	 * man pages are generated. The xslt for building all
	 * documentation now supports the following tags in descriptions:
	 *    <code>, <em>, <strong>, <br />, <p>
	 * Note that the xslt processor requires <br /> to be self closing!
	 */
	{ TidyXmlDecl,
		"This option specifies if Tidy should add the XML declaration when "
		"outputting XML or XHTML. "
		"<br/>"
		"Note that if the input already includes an <code>&lt;?xml ... ?&gt;</code> "
		"declaration then this option will be ignored. "
		"<br/>"
		"If the encoding for the output is different from <code>ascii</code>, one "
		"of the utf encodings or <code>raw</code>, the declaration is always added "
		"as required by the XML standard. "
	},
	{ TidyXmlSpace,
		"This option specifies if Tidy should add "
		"<code>xml:space=\"preserve\"</code> to elements such as "
		"<code>&lt;pre&gt;</code>, <code>&lt;style&gt;</code> and "
		"<code>&lt;script&gt;</code> when generating XML. "
		"<br/>"
		"This is needed if the whitespace in such elements is to "
		"be parsed appropriately without having access to the DTD. "
	},
	{ TidyAltText,
		"This option specifies the default <code>alt=</code> text Tidy uses for "
		"<code>&lt;img&gt;</code> attributes when the <code>alt=</code> attribute "
		"is missing. "
		"<br/>"
		"Use with care, as it is your responsibility to make your documents accessible "
		"to people who cannot see the images. "
	},
	{ TidyXmlPIs,
		"This option specifies if Tidy should change the parsing of processing "
		"instructions to require <code>?&gt;</code> as the terminator rather than "
		"<code>&gt;</code>. "
		"<br/>"
		"This option is automatically set if the input is in XML. "
	},
	{ TidyMakeBare,
		"This option specifies if Tidy should strip Microsoft specific HTML "
		"from Word 2000 documents, and output spaces rather than non-breaking "
		"spaces where they exist in the input. "
	},
	{ TidyCSSPrefix,
		"This option specifies the prefix that Tidy uses for styles rules. "
		"<br/>"
		"By default, <code>c</code> will be used. "
	},
	{ TidyMakeClean,
		"This option specifies if Tidy should perform cleaning of some legacy "
		"presentational tags (currently <code>&lt;i&gt;</code>, "
		"<code>&lt;b&gt;</code>, <code>&lt;center&gt;</code> when enclosed within "
		"appropriate inline tags, and <code>&lt;font&gt;</code>). If set to "
		"<code>yes</code> then legacy tags will be replaced with CSS "
		"<code>&lt;style&gt;</code> tags and structural markup as appropriate. "
	},
	{ TidyGDocClean,
		"This option specifies if Tidy should enable specific behavior for "
		"cleaning up HTML exported from Google Docs. "
	},
	{ TidyDoctype,
		"This option specifies the DOCTYPE declaration generated by Tidy. "
		"<br/>"
		"If set to <code>omit</code> the output won't contain a DOCTYPE "
		"declaration. Note this this also implies <code>numeric-entities</code> is "
		"set to <code>yes</code>."
		"<br/>"
		"If set to <code>html5</code> the DOCTYPE is set to "
		"<code>&lt;!DOCTYPE html&gt;</code>."
		"<br/>"
		"If set to <code>auto</code> (the default) Tidy will use an educated guess "
		"based upon the contents of the document."
		"<br/>"
		"If set to <code>strict</code>, Tidy will set the DOCTYPE to the HTML4 or "
		"XHTML1 strict DTD."
		"<br/>"
		"If set to <code>loose</code>, the DOCTYPE is set to the HTML4 or XHTML1 "
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
	{ TidyDropEmptyElems,
		"This option specifies if Tidy should discard empty elements. "
	},
	{ TidyDropEmptyParas,
		"This option specifies if Tidy should discard empty paragraphs. "
	},
	{ TidyDropFontTags,
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
	{ TidyDropPropAttrs,
		"This option specifies if Tidy should strip out proprietary attributes, "
		"such as Microsoft data binding attributes. "
	},
	{ TidyEncloseBlockText,
		"This option specifies if Tidy should insert a <code>&lt;p&gt;</code> "
		"element to enclose any text it finds in any element that allows mixed "
		"content for HTML transitional but not HTML strict. "
	},
	{ TidyEncloseBodyText,
		"This option specifies if Tidy should enclose any text it finds in the "
		"body element within a <code>&lt;p&gt;</code> element."
		"<br/>"
		"This is useful when you want to take existing HTML and use it with a "
		"style sheet. "
	},
	{ TidyEscapeCdata,
		"This option specifies if Tidy should convert "
		"<code>&lt;![CDATA[]]&gt;</code> sections to normal text. "
	},
	{ TidyFixComments,
		"This option specifies if Tidy should replace unexpected hyphens with "
		"<code>=</code> characters when it comes across adjacent hyphens. "
		"<br/>"
		"The default is <code>yes</code>. "
		"<br/>"
		"This option is provided for users of Cold Fusion which uses the "
		"comment syntax: <code>&lt;!--- ---&gt;</code>. "
	},
	{ TidyFixUri,
		"This option specifies if Tidy should check attribute values that carry "
		"URIs for illegal characters and if such are found, escape them as HTML4 "
		"recommends. "
	},
	{ TidyHideComments,
		"This option specifies if Tidy should print out comments. "
	},
	{ TidyCoerceEndTags,
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
	{ TidyOmitOptionalTags,
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
	{ TidyHideEndTags,
		"This option is an alias for <code>omit-optional-tags</code>. "
	},
	{ TidyIndentCdata,
		"This option specifies if Tidy should indent "
		"<code>&lt;![CDATA[]]&gt;</code> sections. "
	},
	{ TidyXmlTags,
		"This option specifies if Tidy should use the XML parser rather than the "
		"error correcting HTML parser. "
	},
	{ TidyJoinClasses,
		"This option specifies if Tidy should combine class names to generate "
		"a single, new class name if multiple class assignments are detected on "
		"an element. "
	},
	{ TidyJoinStyles,
		"This option specifies if Tidy should combine styles to generate a single, "
		"new style if multiple style values are detected on an element. "
	},
	{ TidyLogicalEmphasis,
		"This option specifies if Tidy should replace any occurrence of "
		"<code>&lt;i&gt;</code> with <code>&lt;em&gt;</code> and any occurrence of "
		"<code>&lt;b&gt;</code> with <code>&lt;strong&gt;</code>. Any attributes "
		"are preserved unchanged. "
		"<br/>"
		"This option can be set independently of the <code>clean</code> option. "
	},
	{ TidyLowerLiterals,
		"This option specifies if Tidy should convert the value of an attribute "
		"that takes a list of predefined values to lower case. "
		"<br/>"
		"This is required for XHTML documents. "
	},
	{ TidyMergeEmphasis,
		"This option specifies if Tidy should merge nested <code>&lt;b&gt;</code> "
		"and <code>&lt;i&gt;</code> elements; for example, for the case "
		"<br/>"
		"<code>&lt;b class=\"rtop-2\"&gt;foo &lt;b class=\"r2-2\"&gt;bar&lt;/b&gt; baz&lt;/b&gt;</code>, "
		"<br/>"
		"Tidy will output <code>&lt;b class=\"rtop-2\"&gt;foo bar baz&lt;/b&gt;</code>. "
	},
	{ TidyMergeDivs,
		"This option can be used to modify the behavior of <code>clean</code> when "
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
	{ TidyMergeSpans,
		"This option can be used to modify the behavior of <code>clean</code> when "
		"set to <code>yes</code>."
		"<br/>"
		"This option specifies if Tidy should merge nested <code>&lt;span&gt;</code> "
		"such as <code>&lt;span&gt;&lt;span&gt;...&lt;/span&gt;&lt;/span&gt;</code>. "
		"<br/>"
		"The algorithm is identical to the one used by <code>merge-divs</code>. "
	},
#if SUPPORT_ASIAN_ENCODINGS
	{ TidyNCR,
		"This option specifies if Tidy should allow numeric character references. "
	},
#endif
	{ TidyBlockTags,
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
	{ TidyEmptyTags,
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
	{ TidyInlineTags,
		"This option specifies new non-empty inline tags. This option takes a "
		"space or comma separated list of tag names. "
		"<br/>"
		"Unless you declare new tags, Tidy will refuse to generate a tidied file if "
		"the input includes previously unknown tags. "
		"<br/>"
		"This option is ignored in XML mode. "
	},
	{ TidyPreTags,
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
	{ TidyNumEntities,
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
	{ TidyHtmlOut,
		"This option specifies if Tidy should generate pretty printed output, "
		"writing it as HTML. "
	},
	{ TidyXhtmlOut,
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
	{ TidyXmlOut,
		"This option specifies if Tidy should pretty print output, writing it as "
		"well-formed XML. "
		"<br/>"
		"Any entities not defined in XML 1.0 will be written as numeric entities to "
		"allow them to be parsed by an XML parser. "
		"<br/>"
		"The original case of tags and attributes will be preserved, regardless of "
		"other options. "
	},
	{ TidyQuoteAmpersand,
		"This option specifies if Tidy should output unadorned <code>&amp;</code> "
		"characters as <code>&amp;amp;</code>. "
	},
	{ TidyQuoteMarks,
		"This option specifies if Tidy should output <code>&quot;</code> characters "
		"as <code>&amp;quot;</code> as is preferred by some editing environments. "
		"<br/>"
		"The apostrophe character <code>'</code> is written out as "
		"<code>&amp;#39;</code> since many web browsers don't yet support "
		"<code>&amp;apos;</code>. "
	},
	{ TidyQuoteNbsp,
		"This option specifies if Tidy should output non-breaking space characters "
		"as entities, rather than as the Unicode character value 160 (decimal). "
	},
	{ TidyDuplicateAttrs,
		"This option specifies if Tidy should keep the first or last attribute, if "
		"an attribute is repeated, e.g. has two <code>align</code> attributes. "
	},
	{ TidySortAttributes,
		"This option specifies that Tidy should sort attributes within an element "
		"using the specified sort algorithm. If set to <code>alpha</code>, the "
		"algorithm is an ascending alphabetic sort. "
	},
	{ TidyReplaceColor,
		"This option specifies if Tidy should replace numeric values in color "
		"attributes with HTML/XHTML color names where defined, e.g. replace "
		"<code>#ffffff</code> with <code>white</code>. "
	},
	{ TidyBodyOnly,
		"This option specifies if Tidy should print only the contents of the "
		"body tag as an HTML fragment. "
		"<br/>"
		"If set to <code>auto</code>, this is performed only if the body tag has "
		"been inferred. "
		"<br/>"
		"Useful for incorporating existing whole pages as a portion of another "
		"page. "
		"<br/>"
		"This option has no effect if XML output is requested. "
	},
	{ TidyUpperCaseAttrs,
		"This option specifies if Tidy should output attribute names in upper "
		"case. "
		"<br/>"
		"The default is <code>no</code>, which results in lower case attribute "
		"names, except for XML input, where the original case is preserved. "
	},
	{ TidyUpperCaseTags,
		"This option specifies if Tidy should output tag names in upper case. "
		"<br/>"
		"The default is <code>no</code> which results in lower case tag names, "
		"except for XML input where the original case is preserved. "
	},
	{ TidyWord2000,
		"This option specifies if Tidy should go to great pains to strip out all "
		"the surplus stuff Microsoft Word 2000 inserts when you save Word "
		"documents as \"Web pages\". It doesn't handle embedded images or VML. "
		"<br/>"
		"You should consider using Word's \"Save As: Web Page, Filtered\". "
	},
	{ TidyAccessibilityCheckLevel,
		"This option specifies what level of accessibility checking, if any, "
		"that Tidy should perform. "
		"<br/>"
		"Level <code>0 (Tidy Classic)</code> is equivalent to Tidy Classic's accessibility "
		"checking. "
		"<br/>"
		"For more information on Tidy's accessibility checking, visit "
		"<a href=\"http://www.html-tidy.org/accessibility/\"> Tidy's Accessibility Page</a>. "
	},
	{ TidyShowErrors,
		"This option specifies the number Tidy uses to determine if further errors "
		"should be shown. If set to <code>0</code>, then no errors are shown. "
	},
	{ TidyShowInfo,
		"This option specifies if Tidy should display info-level messages. "
	},
	{ TidyShowWarnings,
		"This option specifies if Tidy should suppress warnings. This can be "
		"useful when a few errors are hidden in a flurry of warnings. "
	},
	{ TidyBreakBeforeBR,
		"This option specifies if Tidy should output a line break before each "
		"<code>&lt;br&gt;</code> element. "
	},
	{ TidyIndentContent,
		"This option specifies if Tidy should indent block-level tags. "
		"<br/>"
		"If set to <code>auto</code> Tidy will decide whether or not to indent the "
		"content of tags such as <code>&lt;title&gt;</code>, "
		"<code>&lt;h1&gt;</code>-<code>&lt;h6&gt;</code>, <code>&lt;li&gt;</code>, "
		"<code>&lt;td&gt;</code>, or <code>&lt;p&gt;</code> "
		"based on the content including a block-level element. "
		"<br/>"
		"Setting <code>indent</code> to <code>yes</code> can expose layout bugs in "
		"some browsers. "
		"<br/>"
		"Use the option <code>indent-spaces</code> to control the number of spaces "
		"or tabs output per level of indent, and <code>indent-with-tabs</code> to "
		"specify whether spaces or tabs are used. "
	},
	{ TidyIndentAttributes,
		"This option specifies if Tidy should begin each attribute on a new line. "
	},
	{ TidyIndentSpaces,
		"This option specifies the number of spaces or tabs that Tidy uses to "
		"indent content when <code>indent</code> is enabled. "
		"<br/>"
		"Note that the default value for this option is dependent upon the value of "
		"<code>indent-with-tabs</code> (see also). "
	},
	{ TidyLiteralAttribs,
		"This option specifies how Tidy deals with whitespace characters within "
		"attribute values. "
		"<br/>"
		"If the value is <code>no</code> Tidy normalizes attribute values by "
		"replacing any newline or tab with a single space, and further by replacing "
		"any contiguous whitespace with a single space. "
		"<br/>"
		"To force Tidy to preserve the original, literal values of all attributes "
		"and ensure that whitespace within attribute values is passed "
		"through unchanged, set this option to <code>yes</code>. "
	},
	{ TidyShowMarkup,
		"This option specifies if Tidy should generate a pretty printed version "
		"of the markup. Note that Tidy won't generate a pretty printed version if "
		"it finds significant errors (see <code>force-output</code>). "
	},
#if SUPPORT_ASIAN_ENCODINGS
	{ TidyPunctWrap,
		"This option specifies if Tidy should line wrap after some Unicode or "
		"Chinese punctuation characters. "
	},
#endif
	{ TidyBurstSlides,
		"This option has no function and is deprecated. "
	},
	{ TidyTabSize,
		"This option specifies the number of columns that Tidy uses between "
		"successive tab stops. It is used to map tabs to spaces when reading the "
		"input. "
	},
	{ TidyVertSpace,   /* Issue #228 - changed to tri-state */
		"This option specifies if Tidy should add some extra empty lines for "
		"readability. "
		"<br/>"
		"The default is <code>no</code>. "
		"<br/>"
		"If set to <code>auto</code> Tidy will eliminate nearly all newline "
		"characters."
	},
	{ TidyWrapLen,
		"This option specifies the right margin Tidy uses for line wrapping. "
		"<br/>"
		"Tidy tries to wrap lines so that they do not exceed this length. "
		"<br/>"
		"Set <code>wrap</code> to <code>0</code>(zero) if you want to disable line "
		"wrapping. "
	},
	{ TidyWrapAsp,
		"This option specifies if Tidy should line wrap text contained within ASP "
		"pseudo elements, which look like: <code>&lt;% ... %&gt;</code>. "
	},
	{ TidyWrapAttVals,
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
		"<code>yes</code>. "
	},
	{ TidyWrapJste,
		"This option specifies if Tidy should line wrap text contained within "
		"JSTE pseudo elements, which look like: <code>&lt;# ... #&gt;</code>. "
	},
	{ TidyWrapPhp,
		"This option specifies if Tidy should line wrap text contained within PHP "
		"pseudo elements, which look like: <code>&lt;?php ... ?&gt;</code>. "
	},
	{ TidyWrapScriptlets,
		"This option specifies if Tidy should line wrap string literals that "
		"appear in script attributes. "
		"<br/>"
		"Tidy wraps long script string literals by inserting a backslash character "
		"before the line break. "
	},
	{ TidyWrapSection,
		"This option specifies if Tidy should line wrap text contained within "
		"<code>&lt;![ ... ]&gt;</code> section tags. "
	},
	{ TidyAsciiChars,
		"Can be used to modify behavior of the <code>clean</code> option when set "
		"to <code>yes</code>. "
		"<br/>"
		"If set to <code>yes</code> when <code>clean</code>, "
		"<code>&amp;emdash;</code>, <code>&amp;rdquo;</code>, and other named "
		"character entities are downgraded to their closest ASCII equivalents. "
	},
	{ TidyCharEncoding,
		"This option specifies the character encoding Tidy uses for both the input "
		"and output. "
		"<br/>"
		"For <code>ascii</code> Tidy will accept Latin-1 (ISO-8859-1) character "
		"values, but will use entities for all characters whose value &gt;127. "
		"<br/>"
		"For <code>raw</code>, Tidy will output values above 127 without "
		"translating them into entities. "
		"<br/>"
		"For <code>latin1</code>, characters above 255 will be written as entities. "
		"<br/>"
		"For <code>utf8</code>, Tidy assumes that both input and output are encoded "
		"as UTF-8. "
		"<br/>"
		"You can use <code>iso2022</code> for files encoded using the ISO-2022 "
		"family of encodings e.g. ISO-2022-JP. "
		"<br/>"
		"For <code>mac</code> and <code>win1252</code>, Tidy will accept vendor "
		"specific character values, but will use entities for all characters whose "
		"value &gt;127. "
		"<br/>"
		"For unsupported encodings, use an external utility to convert to and from "
		"UTF-8. "
	},
	{ TidyInCharEncoding,
		"This option specifies the character encoding Tidy uses for the input. See "
		"<code>char-encoding</code> for more info. "
	},
#if SUPPORT_ASIAN_ENCODINGS
	{ TidyLanguage,
		"Currently not used, but this option specifies the language Tidy would use "
		"if it were properly localized. For example: <code>en</code>. "
	},
#endif
#if SUPPORT_UTF16_ENCODINGS
	{ TidyOutputBOM,
		"This option specifies if Tidy should write a Unicode Byte Order Mark "
		"character (BOM; also known as Zero Width No-Break Space; has value of "
		"U+FEFF) to the beginning of the output, and only applies to UTF-8 and "
		"UTF-16 output encodings. "
		"<br/>"
		"If set to <code>auto</code> this option causes Tidy to write a BOM to "
		"the output only if a BOM was present at the beginning of the input. "
		"<br/>"
		"A BOM is always written for XML/XHTML output using UTF-16 output "
		"encodings. "
	},
#endif
	{ TidyOutCharEncoding,
		"This option specifies the character encoding Tidy uses for the output. "
		"<br/>"
		"Note that this may only be different from <code>input-encoding</code> for "
		"Latin encodings (<code>ascii</code>, <code>latin0</code>, "
		"<code>latin1</code>, <code>mac</code>, <code>win1252</code>, "
		"<code>ibm858</code>)."
		"<br/>"
		"See <code>char-encoding</code> for more information"
	},
	{ TidyNewline,
		"The default is appropriate to the current platform. "
		"<br/>"
		"Genrally CRLF on PC-DOS, Windows and OS/2; CR on Classic Mac OS; and LF "
		"everywhere else (Linux, Mac OS X, and Unix). "
	},
	{ TidyErrFile,
		"This option specifies the error file Tidy uses for errors and warnings. "
		"Normally errors and warnings are output to <code>stderr</code>. "
	},
	{ TidyFixBackslash,
		"This option specifies if Tidy should replace backslash characters "
		"<code>\\</code> in URLs with forward slashes <code>/</code>. "
	},
	{ TidyForceOutput,
		"This option specifies if Tidy should produce output even if errors are "
		"encountered. "
		"<br/>"
		"Use this option with care; if Tidy reports an error, this "
		"means Tidy was not able to (or is not sure how to) fix the error, so the "
		"resulting output may not reflect your intention. "
	},
	{ TidyEmacs,
		"This option specifies if Tidy should change the format for reporting "
		"errors and warnings to a format that is more easily parsed by GNU Emacs. "
	},
	{ TidyEmacsFile,
		"Used internally. "
	},
	{ TidyKeepFileTimes,
		"This option specifies if Tidy should keep the original modification time "
		"of files that Tidy modifies in place. "
		"<br/>"
		"Setting the option to <code>yes</code> allows you to tidy files without "
		"changing the file modification date, which may be useful with certain "
		"tools that use the modification date for things such as automatic server "
		"deployment."
		"<br/>"
		"Note this feature is not supported on some platforms. "
	},
	{ TidyOutFile,
		"This option specifies the output file Tidy uses for markup. Normally "
		"markup is written to <code>stdout</code>. "
	},
	{ TidyQuiet,
		"This option specifies if Tidy should output the summary of the numbers "
		"of errors and warnings, or the welcome or informational messages. "
	},
	{ TidySlideStyle,
		"This option has no function and is deprecated. "
	},
	{ TidyMark,
		"This option specifies if Tidy should add a <code>meta</code> element to "
		"the document head to indicate that the document has been tidied. "
		"<br/>"
		"Tidy won't add a meta element if one is already present. "
	},
	{ TidyWriteBack,
		"This option specifies if Tidy should write back the tidied markup to the "
		"same file it read from. "
		"<br/>"
		"You are advised to keep copies of important files before tidying them, as "
		"on rare occasions the result may not be what you expect. "
	},
	{ TidyDecorateInferredUL,
		"This option specifies if Tidy should decorate inferred "
		"<code>&lt;ul&gt;</code> elements with some CSS markup to avoid indentation "
		"to the right. "
	},
	{ TidyPreserveEntities,
		"This option specifies if Tidy should preserve well-formed entities "
		"as found in the input. "
	},
	{ TidyAnchorAsName,
		"This option controls the deletion or addition of the <code>name</code> "
		"attribute in elements where it can serve as anchor. "
		"<br/>"
		"If set to <code>yes</code> a <code>name</code> attribute, if not already "
		"existing, is added along an existing <code>id</code> attribute if the DTD "
		"allows it. "
		"<br/>"
		"If set to <code>no</code> any existing name attribute is removed if an "
		"<code>id</code> attribute exists or has been added. "
	},
	{ TidyPPrintTabs,
		"This option specifies if Tidy should indent with tabs instead of spaces, "
		"assuming <code>indent</code> is <code>yes</code>. "
		"<br/>"
		"Set it to <code>yes</code> to indent using tabs instead of the default "
		"spaces. "
		"<br/>"
		"Use the option <code>indent-spaces</code> to control the number of tabs "
		"output per level of indent. Note that when <code>indent-with-tabs</code> "
		"is enabled the default value of <code>indent-spaces</code> is reset to "
		"<code>1</code>. "
		"<br/>"
		"Note <code>tab-size</code> controls converting input tabs to spaces. Set "
		"it to zero to retain input tabs. "
	},
	{ TidySkipNested,
		"This option specifies that Tidy should skip nested tags when parsing "
		"script and style data. "
	},
	
	/*****************************
	 ** Console Application
	 *****************************/
	{ TC_CAT_DIAGNOSTICS,           "diagnostics"                                                             },
	{ TC_CAT_ENCODING,              "encoding"                                                                },
	{ TC_CAT_MARKUP,                "markup"                                                                  },
	{ TC_CAT_MISC,                  "misc"                                                                    },
	{ TC_CAT_PRETTYPRINT,           "print"                                                                   },
	{ TC_LABEL_COL,                 "column"                                                                  },
	{ TC_LABEL_FILE,                "file"                                                                    },
	{ TC_LABEL_LANG,                "lang"                                                                    },
	{ TC_LABEL_LEVL,                "level"                                                                   },
	{ TC_LABEL_OPT,                 "option"                                                                  },
	{ TC_MAIN_ERROR_LOAD_CONFIG,    "Loading config file \"%s\" failed, err = %d\n"                           },
	{ TC_OPT_ACCESS,
		"do additional accessibility checks (<level> = 0, 1, 2, 3). 0 is "
		"assumed if <level> is missing."
	},
	{ TC_OPT_ASCII,                 "use ISO-8859-1 for input, US-ASCII for output"                           },
	{ TC_OPT_ASHTML,                "force XHTML to well formed HTML"                                         },
	{ TC_OPT_ASXML,                 "convert HTML to well formed XHTML"                                       },
	{ TC_OPT_BARE,                  "strip out smart quotes and em dashes, etc."                              },
	{ TC_OPT_BIG5,                  "use Big5 for both input and output"                                      },
	{ TC_OPT_CLEAN,                 "replace FONT, NOBR and CENTER tags with CSS"                             },
	{ TC_OPT_CONFIG,                "set configuration options from the specified <file>"                     },
	{ TC_OPT_ERRORS,                "show only errors and warnings"                                           },
	{ TC_OPT_FILE,                  "write errors and warnings to the specified <file>"                       },
	{ TC_OPT_GDOC,                  "produce clean version of html exported by Google Docs"                   },
	{ TC_OPT_HELP,                  "list the command line options"                                           },
	{ TC_OPT_HELPCFG,               "list all configuration options"                                          },
	{ TC_OPT_HELPOPT,               "show a description of the <option>"                                      },
	{ TC_OPT_IBM858,                "use IBM-858 (CP850+Euro) for input, US-ASCII for output"                 },
	{ TC_OPT_INDENT,                "indent element content"                                                  },
	{ TC_OPT_ISO2022,               "use ISO-2022 for both input and output"                                  },
	{ TC_OPT_LANGUAGE,
		"set tidy's output language to <lang>. Specify '-language help' for more help. "
		"Use before output-causing arguments to ensure the language takes effect, e.g.,"
		"`tidy -lang es -lang help`."
	},
	{ TC_OPT_LATIN0,                "use ISO-8859-15 for input, US-ASCII for output"                          },
	{ TC_OPT_LATIN1,                "use ISO-8859-1 for both input and output"                                },
	{ TC_OPT_MAC,                   "use MacRoman for input, US-ASCII for output"                             },
	{ TC_OPT_MODIFY,                "modify the original input files"                                         },
	{ TC_OPT_NUMERIC,               "output numeric rather than named entities"                               },
	{ TC_OPT_OMIT,                  "omit optional start tags and end tags"                                   },
	{ TC_OPT_OUTPUT,                "write output to the specified <file>"                                    },
	{ TC_OPT_QUIET,                 "suppress nonessential output"                                            },
	{ TC_OPT_RAW,                   "output values above 127 without conversion to entities"                  },
	{ TC_OPT_SHIFTJIS,              "use Shift_JIS for both input and output"                                 },
	{ TC_OPT_SHOWCFG,               "list the current configuration settings"                                 },
	{ TC_OPT_UPPER,                 "force tags to upper case"                                                },
	{ TC_OPT_UTF16,                 "use UTF-16 for both input and output"                                    },
	{ TC_OPT_UTF16BE,               "use UTF-16BE for both input and output"                                  },
	{ TC_OPT_UTF16LE,               "use UTF-16LE for both input and output"                                  },
	{ TC_OPT_UTF8,                  "use UTF-8 for both input and output"                                     },
	{ TC_OPT_VERSION,               "show the version of Tidy"                                                },
	{ TC_OPT_WIN1252,               "use Windows-1252 for input, US-ASCII for output"                         },
	{ TC_OPT_WRAP,
		"wrap text at the specified <column>. 0 is assumed if <column> is "
		"missing. When this option is omitted, the default of the "
		"configuration option 'wrap' applies."
	},
	{ TC_OPT_XML,                   "specify the input is well formed XML"                                    },
	{ TC_OPT_XMLCFG,                "list all configuration options in XML format"                            },
	{ TC_OPT_XMLHELP,               "list the command line options in XML format"                             },
	{ TC_OPT_XMLSTRG,               "output all of tidy's strings in XML format"                              },
	{ TC_OPT_XMLOPTS,               "output all option descriptions cleaned XML format"                       },
	
	{ TC_STRING_OUT_OF_MEMORY,      "Out of memory. Bailing out."                                             },
	{ TC_STRING_FATAL_ERROR,        "Fatal error: impossible value for id='%d'.\n"                            },
	{ TC_STRING_FILE_MANIP,         "File manipulation"                                                       },
	{ TC_STRING_PROCESS_DIRECTIVES, "Processing directives"                                                   },
	{ TC_STRING_CHAR_ENCODING,      "Character encodings"                                                     },
	{ TC_STRING_LANG_MUST_SPECIFY,  "A POSIX or Windows locale must be specified.\n"                          },
	{ TC_STRING_LANG_NOT_FOUND,     "Tidy doesn't have language '%s,' will use '%s' instead.\n"               },
	{ TC_STRING_MISC,               "Miscellaneous"                                                           },
	{ TC_STRING_XML,                "XML"                                                                     },
	{ TC_STRING_MUST_SPECIFY,       "A Tidy option name must be specified."                                   },
	{ TC_STRING_UNKNOWN_OPTION,     "HTML Tidy: unknown option: %c\n"                                         },
	{ TC_STRING_UNKNOWN_OPTION_B,   "HTML Tidy: unknown option."                                              },
	{ TC_STRING_VERS_A,             "HTML Tidy for %s version %s\n"                                           },
	{ TC_STRING_VERS_B,             "HTML Tidy version %s\n"                                                  },
	{ TC_TXT_HELP_1,
		"\n"
		"%s [options...] [file...] [options...] [file...]\n"
		"Utility to clean up and pretty print HTML/XHTML/XML.\n"
		"\n"
		"This is modern HTML Tidy version %s.\n"
		"\n"
	},
	{ TC_TXT_HELP_2A,
		"Command Line Arguments for HTML Tidy for %s:\n"
	},
	{ TC_TXT_HELP_2B,
		"Command Line Arguments for HTML Tidy:\n"
	},
	{ TC_TXT_HELP_3,
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
		"  http://validator.w3.org/nu/"
		"\n\n"
	},
	{ TC_TXT_HELP_CONFIG,
		"\nHTML Tidy Configuration Settings\n\n"
		"Within a file, use the form:\n\n"
		"wrap: 72\n"
		"indent: no\n\n"
		"When specified on the command line, use the form:\n\n"
		"--wrap 72 --indent no\n\n"
	},
	{ TC_TXT_HELP_CONFIG_NAME,      "Name"                                                                    },
	{ TC_TXT_HELP_CONFIG_TYPE,      "Type"                                                                    },
	{ TC_TXT_HELP_CONFIG_ALLW,      "Allowable values"                                                        },
	{ TC_TXT_HELP_LANG_1,
		"\nThe --language (or --lang) option indicates which language Tidy \n"
		"should use to communicate its output. Please note that this is not \n"
		"a document translation service, and only affects the messages that \n"
		"Tidy communicates to you. \n"
		"\nWhen used from the command line the --language argument must \n"
		"be used before any arguments that result in output, otherwise Tidy \n"
		"will produce output before it knows which language to use. \n"
		"\nIn addition to standard POSIX language codes, Tidy is capable of \n"
		"understanding legacy Windows language codes. Please note that this \n"
		"list indicates codes Tidy understands, and does not indicate that \n"
		"the language is currently installed. \n"
		"\nThe rightmost column indicates how Tidy will understand the \n"
		"legacy Windows name.\n\n"
	},
	{ TC_TXT_HELP_LANG_2,
		"\nThe following languages are currently installed in Tidy. Please \n"
		"note that there's no guarantee that they are complete; only that \n"
		"one developer or another started to add the language indicated. \n"
		"\nIncomplete localizations will default to \"en\" when necessary. \n"
		"Please report instances of incorrect strings to the Tidy team. \n\n"
	},
	{ TC_TXT_HELP_LANG_3,
		"\nIf Tidy is able to determine your locale then Tidy will use the \n"
		"locale's language automatically. For example Unix-like systems use a \n"
		"$LANG and/or $LC_ALL environment variable. Consult your operating \n"
		"system documentation for more information. \n\n"
	},
	
	
	/* This MUST be present and last. */
	{ TIDY_MESSAGE_TYPE_LAST,      NULL                                                                       }
};


#endif /* language_en_h */
