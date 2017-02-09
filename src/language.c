/*
 * language.c
 * Localization support for HTML Tidy.
 *
 * (c) 2015 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Created by Jim Derry on 11/28/15.
 */

#include "language.h"
#include "language_en.h"
#if SUPPORT_LOCALIZATIONS
#include "language_en_gb.h"
#include "language_es.h"
#include "language_es_mx.h"
#include "language_zh_cn.h"
#include "language_fr.h"
#endif
#include "tmbstr.h"
#include "locale.h"


/**
 *  This structure type provides universal access to all of Tidy's strings.
 */
typedef struct {
    languageDefinition *currentLanguage;
    languageDefinition *fallbackLanguage;
    languageDefinition *languages[];
} tidyLanguagesType;


/**
 *  This single structure contains all localizations. Note that we preset
 *  `.currentLanguage` to language_en, which is Tidy's default language.
 */
static tidyLanguagesType tidyLanguages = {
    &language_en, /* current language */
    &language_en, /* first fallback language */
    {
        /* Required localization! */
        &language_en,
#if SUPPORT_LOCALIZATIONS
        /* These additional languages are installed. */
        &language_en_gb,
        &language_es,
        &language_es_mx,
        &language_zh_cn,
        &language_fr,
#endif
        NULL /* This array MUST be null terminated. */
    }
};


/**
 *  This structure maps old-fashioned Windows strings
 *  to proper POSIX names (modern Windows already uses
 *  POSIX names).
 */
static const tidyLocaleMapItem localeMappings[] = {
    { "america",                "en_us" },
    { "american english",       "en_us" },
    { "american-english",       "en_us" },
    { "american",               "en_us" },
    { "aus",                    "en_au" },
    { "australia",              "en_au" },
    { "australian",             "en_au" },
    { "austria",                "de_at" },
    { "aut",                    "de_at" },
    { "bel",                    "nl_be" },
    { "belgian",                "nl_be" },
    { "belgium",                "nl_be" },
    { "bra",                    "pt-br" },
    { "brazil",                 "pt-br" },
    { "britain",                "en_gb" },
    { "can",                    "en_ca" },
    { "canada",                 "en_ca" },
    { "canadian",               "en_ca" },
    { "che",                    "de_ch" },
    { "china",                  "zh_cn" },
    { "chinese-simplified",     "zh"    },
    { "chinese-traditional",    "zh_tw" },
    { "chinese",                "zh"    },
    { "chn",                    "zh_cn" },
    { "chs",                    "zh"    },
    { "cht",                    "zh_tw" },
    { "csy",                    "cs"    },
    { "cze",                    "cs_cz" },
    { "czech",                  "cs_cz" },
    { "dan",                    "da"    },
    { "danish",                 "da"    },
    { "dea",                    "de_at" },
    { "denmark",                "da_dk" },
    { "des",                    "de_ch" },
    { "deu",                    "de"    },
    { "dnk",                    "da_dk" },
    { "dutch-belgian",          "nl_be" },
    { "dutch",                  "nl"    },
    { "ell",                    "el"    },
    { "ena",                    "en_au" },
    { "enc",                    "en_ca" },
    { "eng",                    "eb_gb" },
    { "england",                "en_gb" },
    { "english-american",       "en_us" },
    { "english-aus",            "en_au" },
    { "english-can",            "en_ca" },
    { "english-nz",             "en_nz" },
    { "english-uk",             "eb_gb" },
    { "english-us",             "en_us" },
    { "english-usa",            "en_us" },
    { "english",                "en"    },
    { "enu",                    "en_us" },
    { "enz",                    "en_nz" },
    { "esm",                    "es-mx" },
    { "esn",                    "es"    },
    { "esp",                    "es"    },
    { "fin",                    "fi"    },
    { "finland",                "fi_fi" },
    { "finnish",                "fi"    },
    { "fra",                    "fr"    },
    { "france",                 "fr_fr" },
    { "frb",                    "fr_be" },
    { "frc",                    "fr_ca" },
    { "french-belgian",         "fr_be" },
    { "french-canadian",        "fr_ca" },
    { "french-swiss",           "fr_ch" },
    { "french",                 "fr"    },
    { "frs",                    "fr_ch" },
    { "gbr",                    "en_gb" },
    { "german-austrian",        "de_at" },
    { "german-swiss",           "de_ch" },
    { "german",                 "de"    },
    { "germany",                "de_de" },
    { "grc",                    "el_gr" },
    { "great britain",          "en_gb" },
    { "greece",                 "el_gr" },
    { "greek",                  "el"    },
    { "hkg",                    "zh_hk" },
    { "holland",                "nl_nl" },
    { "hong kong",              "zh_hk" },
    { "hong-kong",              "zh_hk" },
    { "hun",                    "hu"    },
    { "hungarian",              "hu"    },
    { "hungary",                "hu_hu" },
    { "iceland",                "is_is" },
    { "icelandic",              "is"    },
    { "ireland",                "en_ie" },
    { "irl",                    "en_ie" },
    { "isl",                    "is"    },
    { "ita",                    "it"    },
    { "ita",                    "it_it" },
    { "italian-swiss",          "it_ch" },
    { "italian",                "it"    },
    { "italy",                  "it_it" },
    { "its",                    "it_ch" },
    { "japan",                  "ja_jp" },
    { "japanese",               "ja"    },
    { "jpn",                    "ja"    },
    { "kor",                    "ko"    },
    { "korea",                  "ko_kr" },
    { "korean",                 "ko"    },
    { "mex",                    "es-mx" },
    { "mexico",                 "es-mx" },
    { "netherlands",            "nl_nl" },
    { "new zealand",            "en_nz" },
    { "new-zealand",            "en_nz" },
    { "nlb",                    "nl_be" },
    { "nld",                    "nl"    },
    { "non",                    "nn"    },
    { "nor",                    "nb"    },
    { "norway",                 "no"    },
    { "norwegian-bokmal",       "nb"    },
    { "norwegian-nynorsk",      "nn"    },
    { "norwegian",              "no"    },
    { "nz",                     "en_nz" },
    { "nzl",                    "en_nz" },
    { "plk",                    "pl"    },
    { "pol",                    "pl-pl" },
    { "poland",                 "pl-pl" },
    { "polish",                 "pl"    },
    { "portugal",               "pt-pt" },
    { "portuguese-brazil",      "pt-br" },
    { "portuguese",             "pt"    },
    { "pr china",               "zh_cn" },
    { "pr-china",               "zh_cn" },
    { "prt",                    "pt-pt" },
    { "ptb",                    "pt-br" },
    { "ptg",                    "pt"    },
    { "rus",                    "ru"    },
    { "russia",                 "ru-ru" },
    { "russian",                "ru"    },
    { "sgp",                    "zh_sg" },
    { "singapore",              "zh_sg" },
    { "sky",                    "sk"    },
    { "slovak",                 "sk"    },
    { "spain",                  "es-es" },
    { "spanish-mexican",        "es-mx" },
    { "spanish-modern",         "es"    },
    { "spanish",                "es"    },
    { "sve",                    "sv"    },
    { "svk",                    "sk-sk" },
    { "swe",                    "sv-se" },
    { "sweden",                 "sv-se" },
    { "swedish",                "sv"    },
    { "swiss",                  "de_ch" },
    { "switzerland",            "de_ch" },
    { "taiwan",                 "zh_tw" },
    { "trk",                    "tr"    },
    { "tur",                    "tr-tr" },
    { "turkey",                 "tr-tr" },
    { "turkish",                "tr"    },
    { "twn",                    "zh_tw" },
    { "uk",                     "en_gb" },
    { "united kingdom",         "en_gb" },
    { "united states",          "en_us" },
    { "united-kingdom",         "en_gb" },
    { "united-states",          "en_us" },
    { "us",                     "en_us" },
    { "usa",                    "en_us" },
    
    /* MUST be last. */
    { NULL,                     NULL    }
};


/**
 *  LibTidy users may want to use `TidyReportFilter3` to enable their own
 *  localization lookup features. Because Tidy's errors codes are enums the
 *  specific values can change over time. This table will ensure that LibTidy
 *  users always have a static value available for use.
 */
static const tidyErrorFilterKeyItem tidyErrorFilterKeysStruct[] = {
    /* This blocks of codes comes from `tidyErrorCodes` enum. */
    { "CODES_TIDY_ERROR_FIRST",                        CODES_TIDY_ERROR_FIRST                        },
    { "MISSING_SEMICOLON",                             MISSING_SEMICOLON                             },
    { "MISSING_SEMICOLON_NCR",                         MISSING_SEMICOLON_NCR                         },
    { "UNKNOWN_ENTITY",                                UNKNOWN_ENTITY                                },
    { "UNESCAPED_AMPERSAND",                           UNESCAPED_AMPERSAND                           },
    { "APOS_UNDEFINED",                                APOS_UNDEFINED                                },
    { "MISSING_ENDTAG_FOR",                            MISSING_ENDTAG_FOR                            },
    { "MISSING_ENDTAG_BEFORE",                         MISSING_ENDTAG_BEFORE                         },
    { "DISCARDING_UNEXPECTED",                         DISCARDING_UNEXPECTED                         },
    { "NESTED_EMPHASIS",                               NESTED_EMPHASIS                               },
    { "NON_MATCHING_ENDTAG",                           NON_MATCHING_ENDTAG                           },
    { "TAG_NOT_ALLOWED_IN",                            TAG_NOT_ALLOWED_IN                            },
    { "MISSING_STARTTAG",                              MISSING_STARTTAG                              },
    { "UNEXPECTED_ENDTAG",                             UNEXPECTED_ENDTAG                             },
    { "USING_BR_INPLACE_OF",                           USING_BR_INPLACE_OF                           },
    { "INSERTING_TAG",                                 INSERTING_TAG                                 },
    { "SUSPECTED_MISSING_QUOTE",                       SUSPECTED_MISSING_QUOTE                       },
    { "MISSING_TITLE_ELEMENT",                         MISSING_TITLE_ELEMENT                         },
    { "DUPLICATE_FRAMESET",                            DUPLICATE_FRAMESET                            },
    { "CANT_BE_NESTED",                                CANT_BE_NESTED                                },
    { "OBSOLETE_ELEMENT",                              OBSOLETE_ELEMENT                              },
    { "PROPRIETARY_ELEMENT",                           PROPRIETARY_ELEMENT                           },
    { "ELEMENT_VERS_MISMATCH_ERROR",                   ELEMENT_VERS_MISMATCH_ERROR                   },
    { "ELEMENT_VERS_MISMATCH_WARN",                    ELEMENT_VERS_MISMATCH_WARN                    },
    { "UNKNOWN_ELEMENT",                               UNKNOWN_ELEMENT                               },
    { "TRIM_EMPTY_ELEMENT",                            TRIM_EMPTY_ELEMENT                            },
    { "COERCE_TO_ENDTAG",                              COERCE_TO_ENDTAG                              },
    { "ILLEGAL_NESTING",                               ILLEGAL_NESTING                               },
    { "NOFRAMES_CONTENT",                              NOFRAMES_CONTENT                              },
    { "CONTENT_AFTER_BODY",                            CONTENT_AFTER_BODY                            },
    { "INCONSISTENT_VERSION",                          INCONSISTENT_VERSION                          },
    { "MALFORMED_COMMENT",                             MALFORMED_COMMENT                             },
    { "BAD_COMMENT_CHARS",                             BAD_COMMENT_CHARS                             },
    { "BAD_XML_COMMENT",                               BAD_XML_COMMENT                               },
    { "BAD_CDATA_CONTENT",                             BAD_CDATA_CONTENT                             },
    { "INCONSISTENT_NAMESPACE",                        INCONSISTENT_NAMESPACE                        },
    { "DOCTYPE_AFTER_TAGS",                            DOCTYPE_AFTER_TAGS                            },
    { "MALFORMED_DOCTYPE",                             MALFORMED_DOCTYPE                             },
    { "UNEXPECTED_END_OF_FILE",                        UNEXPECTED_END_OF_FILE                        },
    { "DTYPE_NOT_UPPER_CASE",                          DTYPE_NOT_UPPER_CASE                          },
    { "TOO_MANY_ELEMENTS",                             TOO_MANY_ELEMENTS                             },
    { "UNESCAPED_ELEMENT",                             UNESCAPED_ELEMENT                             },
    { "NESTED_QUOTATION",                              NESTED_QUOTATION                              },
    { "ELEMENT_NOT_EMPTY",                             ELEMENT_NOT_EMPTY                             },
    { "ENCODING_IO_CONFLICT",                          ENCODING_IO_CONFLICT                          },
    { "MIXED_CONTENT_IN_BLOCK",                        MIXED_CONTENT_IN_BLOCK                        },
    { "MISSING_DOCTYPE",                               MISSING_DOCTYPE                               },
    { "SPACE_PRECEDING_XMLDECL",                       SPACE_PRECEDING_XMLDECL                       },
    { "TOO_MANY_ELEMENTS_IN",                          TOO_MANY_ELEMENTS_IN                          },
    { "UNEXPECTED_ENDTAG_IN",                          UNEXPECTED_ENDTAG_IN                          },
    { "REPLACING_ELEMENT",                             REPLACING_ELEMENT                             },
    { "REPLACING_UNEX_ELEMENT",                        REPLACING_UNEX_ELEMENT                        },
    { "COERCE_TO_ENDTAG_WARN",                         COERCE_TO_ENDTAG_WARN                         },
    { "UNKNOWN_ATTRIBUTE",                             UNKNOWN_ATTRIBUTE                             },
    { "INSERTING_ATTRIBUTE",                           INSERTING_ATTRIBUTE                           },
    { "INSERTING_AUTO_ATTRIBUTE",                      INSERTING_AUTO_ATTRIBUTE                      },
    { "MISSING_ATTR_VALUE",                            MISSING_ATTR_VALUE                            },
    { "BAD_ATTRIBUTE_VALUE",                           BAD_ATTRIBUTE_VALUE                           },
    { "UNEXPECTED_GT",                                 UNEXPECTED_GT                                 },
    { "PROPRIETARY_ATTRIBUTE",                         PROPRIETARY_ATTRIBUTE                         },
    { "MISMATCHED_ATTRIBUTE_ERROR",                    MISMATCHED_ATTRIBUTE_ERROR                    },
    { "MISMATCHED_ATTRIBUTE_WARN",                     MISMATCHED_ATTRIBUTE_WARN                     },
    { "PROPRIETARY_ATTR_VALUE",                        PROPRIETARY_ATTR_VALUE                        },
    { "REPEATED_ATTRIBUTE",                            REPEATED_ATTRIBUTE                            },
    { "MISSING_IMAGEMAP",                              MISSING_IMAGEMAP                              },
    { "XML_ATTRIBUTE_VALUE",                           XML_ATTRIBUTE_VALUE                           },
    { "UNEXPECTED_QUOTEMARK",                          UNEXPECTED_QUOTEMARK                          },
    { "MISSING_QUOTEMARK",                             MISSING_QUOTEMARK                             },
    { "ID_NAME_MISMATCH",                              ID_NAME_MISMATCH                              },
    { "BACKSLASH_IN_URI",                              BACKSLASH_IN_URI                              },
    { "FIXED_BACKSLASH",                               FIXED_BACKSLASH                               },
    { "ILLEGAL_URI_REFERENCE",                         ILLEGAL_URI_REFERENCE                         },
    { "ESCAPED_ILLEGAL_URI",                           ESCAPED_ILLEGAL_URI                           },
    { "NEWLINE_IN_URI",                                NEWLINE_IN_URI                                },
    { "ANCHOR_NOT_UNIQUE",                             ANCHOR_NOT_UNIQUE                             },
    { "JOINING_ATTRIBUTE",                             JOINING_ATTRIBUTE                             },
    { "UNEXPECTED_EQUALSIGN",                          UNEXPECTED_EQUALSIGN                          },
    { "ATTR_VALUE_NOT_LCASE",                          ATTR_VALUE_NOT_LCASE                          },
    { "XML_ID_SYNTAX",                                 XML_ID_SYNTAX                                 },
    { "INVALID_ATTRIBUTE",                             INVALID_ATTRIBUTE                             },
    { "BAD_ATTRIBUTE_VALUE_REPLACED",                  BAD_ATTRIBUTE_VALUE_REPLACED                  },
    { "INVALID_XML_ID",                                INVALID_XML_ID                                },
    { "UNEXPECTED_END_OF_FILE_ATTR",                   UNEXPECTED_END_OF_FILE_ATTR                   },
    { "MISSING_ATTRIBUTE",                             MISSING_ATTRIBUTE                             },
    { "WHITE_IN_URI",                                  WHITE_IN_URI                                  },
    { "REMOVED_HTML5",                                 REMOVED_HTML5                                 },
    { "BAD_SUMMARY_HTML5",                             BAD_SUMMARY_HTML5                             },
    { "PREVIOUS_LOCATION",                             PREVIOUS_LOCATION                             },
    { "VENDOR_SPECIFIC_CHARS",                         VENDOR_SPECIFIC_CHARS                         },
    { "INVALID_SGML_CHARS",                            INVALID_SGML_CHARS                            },
    { "INVALID_UTF8",                                  INVALID_UTF8                                  },
    { "INVALID_UTF16",                                 INVALID_UTF16                                 },
    { "ENCODING_MISMATCH",                             ENCODING_MISMATCH                             },
    { "INVALID_URI",                                   INVALID_URI                                   },
    { "INVALID_NCR",                                   INVALID_NCR                                   },
    { "BAD_SURROGATE_PAIR",                            BAD_SURROGATE_PAIR                            },
    { "BAD_SURROGATE_TAIL",                            BAD_SURROGATE_TAIL                            },
    { "BAD_SURROGATE_LEAD",                            BAD_SURROGATE_LEAD                            },
    { "CODES_TIDY_ERROR_LAST",                         CODES_TIDY_ERROR_LAST                         },
#if SUPPORT_ACCESSIBILITY_CHECKS
    /* This blocks of codes comes from `accessErrorCodes` enum. */
    { "FIRST_ACCESS_ERR",                              FIRST_ACCESS_ERR                              },
    { "IMG_MISSING_ALT",                               IMG_MISSING_ALT                               },
    { "IMG_ALT_SUSPICIOUS_FILENAME",                   IMG_ALT_SUSPICIOUS_FILENAME                   },
    { "IMG_ALT_SUSPICIOUS_FILE_SIZE",                  IMG_ALT_SUSPICIOUS_FILE_SIZE                  },
    { "IMG_ALT_SUSPICIOUS_PLACEHOLDER",                IMG_ALT_SUSPICIOUS_PLACEHOLDER                },
    { "IMG_ALT_SUSPICIOUS_TOO_LONG",                   IMG_ALT_SUSPICIOUS_TOO_LONG                   },
    { "IMG_MISSING_ALT_BULLET",                        IMG_MISSING_ALT_BULLET                        },
    { "IMG_MISSING_ALT_H_RULE",                        IMG_MISSING_ALT_H_RULE                        },
    { "IMG_MISSING_LONGDESC_DLINK",                    IMG_MISSING_LONGDESC_DLINK                    },
    { "IMG_MISSING_DLINK",                             IMG_MISSING_DLINK                             },
    { "IMG_MISSING_LONGDESC",                          IMG_MISSING_LONGDESC                          },
    { "LONGDESC_NOT_REQUIRED",                         LONGDESC_NOT_REQUIRED                         },
    { "IMG_BUTTON_MISSING_ALT",                        IMG_BUTTON_MISSING_ALT                        },
    { "APPLET_MISSING_ALT",                            APPLET_MISSING_ALT                            },
    { "OBJECT_MISSING_ALT",                            OBJECT_MISSING_ALT                            },
    { "AUDIO_MISSING_TEXT_WAV",                        AUDIO_MISSING_TEXT_WAV                        },
    { "AUDIO_MISSING_TEXT_AU",                         AUDIO_MISSING_TEXT_AU                         },
    { "AUDIO_MISSING_TEXT_AIFF",                       AUDIO_MISSING_TEXT_AIFF                       },
    { "AUDIO_MISSING_TEXT_SND",                        AUDIO_MISSING_TEXT_SND                        },
    { "AUDIO_MISSING_TEXT_RA",                         AUDIO_MISSING_TEXT_RA                         },
    { "AUDIO_MISSING_TEXT_RM",                         AUDIO_MISSING_TEXT_RM                         },
    { "FRAME_MISSING_LONGDESC",                        FRAME_MISSING_LONGDESC                        },
    { "AREA_MISSING_ALT",                              AREA_MISSING_ALT                              },
    { "SCRIPT_MISSING_NOSCRIPT",                       SCRIPT_MISSING_NOSCRIPT                       },
    { "ASCII_REQUIRES_DESCRIPTION",                    ASCII_REQUIRES_DESCRIPTION                    },
    { "IMG_MAP_SERVER_REQUIRES_TEXT_LINKS",            IMG_MAP_SERVER_REQUIRES_TEXT_LINKS            },
    { "MULTIMEDIA_REQUIRES_TEXT",                      MULTIMEDIA_REQUIRES_TEXT                      },
    { "IMG_MAP_CLIENT_MISSING_TEXT_LINKS",             IMG_MAP_CLIENT_MISSING_TEXT_LINKS             },
    { "INFORMATION_NOT_CONVEYED_IMAGE",                INFORMATION_NOT_CONVEYED_IMAGE                },
    { "INFORMATION_NOT_CONVEYED_APPLET",               INFORMATION_NOT_CONVEYED_APPLET               },
    { "INFORMATION_NOT_CONVEYED_OBJECT",               INFORMATION_NOT_CONVEYED_OBJECT               },
    { "INFORMATION_NOT_CONVEYED_SCRIPT",               INFORMATION_NOT_CONVEYED_SCRIPT               },
    { "INFORMATION_NOT_CONVEYED_INPUT",                INFORMATION_NOT_CONVEYED_INPUT                },
    { "COLOR_CONTRAST_TEXT",                           COLOR_CONTRAST_TEXT                           },
    { "COLOR_CONTRAST_LINK",                           COLOR_CONTRAST_LINK                           },
    { "COLOR_CONTRAST_ACTIVE_LINK",                    COLOR_CONTRAST_ACTIVE_LINK                    },
    { "COLOR_CONTRAST_VISITED_LINK",                   COLOR_CONTRAST_VISITED_LINK                   },
    { "DOCTYPE_MISSING",                               DOCTYPE_MISSING                               },
    { "STYLE_SHEET_CONTROL_PRESENTATION",              STYLE_SHEET_CONTROL_PRESENTATION              },
    { "HEADERS_IMPROPERLY_NESTED",                     HEADERS_IMPROPERLY_NESTED                     },
    { "POTENTIAL_HEADER_BOLD",                         POTENTIAL_HEADER_BOLD                         },
    { "POTENTIAL_HEADER_ITALICS",                      POTENTIAL_HEADER_ITALICS                      },
    { "POTENTIAL_HEADER_UNDERLINE",                    POTENTIAL_HEADER_UNDERLINE                    },
    { "HEADER_USED_FORMAT_TEXT",                       HEADER_USED_FORMAT_TEXT                       },
    { "LIST_USAGE_INVALID_UL",                         LIST_USAGE_INVALID_UL                         },
    { "LIST_USAGE_INVALID_OL",                         LIST_USAGE_INVALID_OL                         },
    { "LIST_USAGE_INVALID_LI",                         LIST_USAGE_INVALID_LI                         },
    { "INDICATE_CHANGES_IN_LANGUAGE",                  INDICATE_CHANGES_IN_LANGUAGE                  },
    { "LANGUAGE_NOT_IDENTIFIED",                       LANGUAGE_NOT_IDENTIFIED                       },
    { "LANGUAGE_INVALID",                              LANGUAGE_INVALID                              },
    { "DATA_TABLE_MISSING_HEADERS",                    DATA_TABLE_MISSING_HEADERS                    },
    { "DATA_TABLE_MISSING_HEADERS_COLUMN",             DATA_TABLE_MISSING_HEADERS_COLUMN             },
    { "DATA_TABLE_MISSING_HEADERS_ROW",                DATA_TABLE_MISSING_HEADERS_ROW                },
    { "DATA_TABLE_REQUIRE_MARKUP_COLUMN_HEADERS",      DATA_TABLE_REQUIRE_MARKUP_COLUMN_HEADERS      },
    { "DATA_TABLE_REQUIRE_MARKUP_ROW_HEADERS",         DATA_TABLE_REQUIRE_MARKUP_ROW_HEADERS         },
    { "LAYOUT_TABLES_LINEARIZE_PROPERLY",              LAYOUT_TABLES_LINEARIZE_PROPERLY              },
    { "LAYOUT_TABLE_INVALID_MARKUP",                   LAYOUT_TABLE_INVALID_MARKUP                   },
    { "TABLE_MISSING_SUMMARY",                         TABLE_MISSING_SUMMARY                         },
    { "TABLE_SUMMARY_INVALID_NULL",                    TABLE_SUMMARY_INVALID_NULL                    },
    { "TABLE_SUMMARY_INVALID_SPACES",                  TABLE_SUMMARY_INVALID_SPACES                  },
    { "TABLE_SUMMARY_INVALID_PLACEHOLDER",             TABLE_SUMMARY_INVALID_PLACEHOLDER             },
    { "TABLE_MISSING_CAPTION",                         TABLE_MISSING_CAPTION                         },
    { "TABLE_MAY_REQUIRE_HEADER_ABBR",                 TABLE_MAY_REQUIRE_HEADER_ABBR                 },
    { "TABLE_MAY_REQUIRE_HEADER_ABBR_NULL",            TABLE_MAY_REQUIRE_HEADER_ABBR_NULL            },
    { "TABLE_MAY_REQUIRE_HEADER_ABBR_SPACES",          TABLE_MAY_REQUIRE_HEADER_ABBR_SPACES          },
    { "STYLESHEETS_REQUIRE_TESTING_LINK",              STYLESHEETS_REQUIRE_TESTING_LINK              },
    { "STYLESHEETS_REQUIRE_TESTING_STYLE_ELEMENT",     STYLESHEETS_REQUIRE_TESTING_STYLE_ELEMENT     },
    { "STYLESHEETS_REQUIRE_TESTING_STYLE_ATTR",        STYLESHEETS_REQUIRE_TESTING_STYLE_ATTR        },
    { "FRAME_SRC_INVALID",                             FRAME_SRC_INVALID                             },
    { "TEXT_EQUIVALENTS_REQUIRE_UPDATING_APPLET",      TEXT_EQUIVALENTS_REQUIRE_UPDATING_APPLET      },
    { "TEXT_EQUIVALENTS_REQUIRE_UPDATING_SCRIPT",      TEXT_EQUIVALENTS_REQUIRE_UPDATING_SCRIPT      },
    { "TEXT_EQUIVALENTS_REQUIRE_UPDATING_OBJECT",      TEXT_EQUIVALENTS_REQUIRE_UPDATING_OBJECT      },
    { "PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_SCRIPT",   PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_SCRIPT   },
    { "PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_OBJECT",   PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_OBJECT   },
    { "PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_EMBED",    PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_EMBED    },
    { "PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_APPLET",   PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_APPLET   },
    { "FRAME_MISSING_NOFRAMES",                        FRAME_MISSING_NOFRAMES                        },
    { "NOFRAMES_INVALID_NO_VALUE",                     NOFRAMES_INVALID_NO_VALUE                     },
    { "NOFRAMES_INVALID_CONTENT",                      NOFRAMES_INVALID_CONTENT                      },
    { "NOFRAMES_INVALID_LINK",                         NOFRAMES_INVALID_LINK                         },
    { "REMOVE_FLICKER_SCRIPT",                         REMOVE_FLICKER_SCRIPT                         },
    { "REMOVE_FLICKER_OBJECT",                         REMOVE_FLICKER_OBJECT                         },
    { "REMOVE_FLICKER_EMBED",                          REMOVE_FLICKER_EMBED                          },
    { "REMOVE_FLICKER_APPLET",                         REMOVE_FLICKER_APPLET                         },
    { "REMOVE_FLICKER_ANIMATED_GIF",                   REMOVE_FLICKER_ANIMATED_GIF                   },
    { "REMOVE_BLINK_MARQUEE",                          REMOVE_BLINK_MARQUEE                          },
    { "REMOVE_AUTO_REFRESH",                           REMOVE_AUTO_REFRESH                           },
    { "REMOVE_AUTO_REDIRECT",                          REMOVE_AUTO_REDIRECT                          },
    { "ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_SCRIPT", ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_SCRIPT },
    { "ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_OBJECT", ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_OBJECT },
    { "ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_APPLET", ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_APPLET },
    { "ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_EMBED",  ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_EMBED  },
    { "IMAGE_MAP_SERVER_SIDE_REQUIRES_CONVERSION",     IMAGE_MAP_SERVER_SIDE_REQUIRES_CONVERSION     },
    { "SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_DOWN",  SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_DOWN  },
    { "SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_UP",    SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_UP    },
    { "SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_CLICK",       SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_CLICK       },
    { "SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OVER",  SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OVER  },
    { "SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OUT",   SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OUT   },
    { "SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_MOVE",  SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_MOVE  },
    { "NEW_WINDOWS_REQUIRE_WARNING_NEW",               NEW_WINDOWS_REQUIRE_WARNING_NEW               },
    { "NEW_WINDOWS_REQUIRE_WARNING_BLANK",             NEW_WINDOWS_REQUIRE_WARNING_BLANK             },
    { "LABEL_NEEDS_REPOSITIONING_BEFORE_INPUT",        LABEL_NEEDS_REPOSITIONING_BEFORE_INPUT        },
    { "LABEL_NEEDS_REPOSITIONING_AFTER_INPUT",         LABEL_NEEDS_REPOSITIONING_AFTER_INPUT         },
    { "FORM_CONTROL_REQUIRES_DEFAULT_TEXT",            FORM_CONTROL_REQUIRES_DEFAULT_TEXT            },
    { "FORM_CONTROL_DEFAULT_TEXT_INVALID_NULL",        FORM_CONTROL_DEFAULT_TEXT_INVALID_NULL        },
    { "FORM_CONTROL_DEFAULT_TEXT_INVALID_SPACES",      FORM_CONTROL_DEFAULT_TEXT_INVALID_SPACES      },
    { "REPLACE_DEPRECATED_HTML_APPLET",                REPLACE_DEPRECATED_HTML_APPLET                },
    { "REPLACE_DEPRECATED_HTML_BASEFONT",              REPLACE_DEPRECATED_HTML_BASEFONT              },
    { "REPLACE_DEPRECATED_HTML_CENTER",                REPLACE_DEPRECATED_HTML_CENTER                },
    { "REPLACE_DEPRECATED_HTML_DIR",                   REPLACE_DEPRECATED_HTML_DIR                   },
    { "REPLACE_DEPRECATED_HTML_FONT",                  REPLACE_DEPRECATED_HTML_FONT                  },
    { "REPLACE_DEPRECATED_HTML_ISINDEX",               REPLACE_DEPRECATED_HTML_ISINDEX               },
    { "REPLACE_DEPRECATED_HTML_MENU",                  REPLACE_DEPRECATED_HTML_MENU                  },
    { "REPLACE_DEPRECATED_HTML_S",                     REPLACE_DEPRECATED_HTML_S                     },
    { "REPLACE_DEPRECATED_HTML_STRIKE",                REPLACE_DEPRECATED_HTML_STRIKE                },
    { "REPLACE_DEPRECATED_HTML_U",                     REPLACE_DEPRECATED_HTML_U                     },
    { "FRAME_MISSING_TITLE",                           FRAME_MISSING_TITLE                           },
    { "FRAME_TITLE_INVALID_NULL",                      FRAME_TITLE_INVALID_NULL                      },
    { "FRAME_TITLE_INVALID_SPACES",                    FRAME_TITLE_INVALID_SPACES                    },
    { "ASSOCIATE_LABELS_EXPLICITLY",                   ASSOCIATE_LABELS_EXPLICITLY                   },
    { "ASSOCIATE_LABELS_EXPLICITLY_FOR",               ASSOCIATE_LABELS_EXPLICITLY_FOR               },
    { "ASSOCIATE_LABELS_EXPLICITLY_ID",                ASSOCIATE_LABELS_EXPLICITLY_ID                },
    { "LINK_TEXT_NOT_MEANINGFUL",                      LINK_TEXT_NOT_MEANINGFUL                      },
    { "LINK_TEXT_MISSING",                             LINK_TEXT_MISSING                             },
    { "LINK_TEXT_TOO_LONG",                            LINK_TEXT_TOO_LONG                            },
    { "LINK_TEXT_NOT_MEANINGFUL_CLICK_HERE",           LINK_TEXT_NOT_MEANINGFUL_CLICK_HERE           },
    { "LINK_TEXT_NOT_MEANINGFUL_MORE",                 LINK_TEXT_NOT_MEANINGFUL_MORE                 },
    { "LINK_TEXT_NOT_MEANINGFUL_FOLLOW_THIS",          LINK_TEXT_NOT_MEANINGFUL_FOLLOW_THIS          },
    { "METADATA_MISSING",                              METADATA_MISSING                              },
    { "METADATA_MISSING_LINK",                         METADATA_MISSING_LINK                         },
    { "METADATA_MISSING_REDIRECT_AUTOREFRESH",         METADATA_MISSING_REDIRECT_AUTOREFRESH         },
    { "SKIPOVER_ASCII_ART",                            SKIPOVER_ASCII_ART                            },
    { "LAST_ACCESS_ERR",                               LAST_ACCESS_ERR                               },
#endif
    /* This blocks of codes comes from `tidyMessagesMisc` enum. */
    { "STRING_UNKNOWN_OPTION",                         STRING_UNKNOWN_OPTION                         },
    { "STRING_MISSING_MALFORMED",                      STRING_MISSING_MALFORMED                      },
    { "STRING_DOCTYPE_GIVEN",                          STRING_DOCTYPE_GIVEN                          },
    { "STRING_HTML_PROPRIETARY",                       STRING_HTML_PROPRIETARY                       },
    { "STRING_CONTENT_LOOKS",                          STRING_CONTENT_LOOKS                          },
    { "STRING_NO_SYSID",                               STRING_NO_SYSID                               },
    { NULL,                                            0                                             },
};


/**
 *  Given an error code, return the string associated with it.
 */
ctmbstr tidyErrorCodeAsString(uint code)
{
    uint i = 0;
    while (tidyErrorFilterKeysStruct[i].key) {
        if ( tidyErrorFilterKeysStruct[i].value == code )
            return tidyErrorFilterKeysStruct[i].key;
        i++;
    }
    return "UNDEFINED";
}


/**
 *  The real string lookup function.
 */
ctmbstr TY_(tidyLocalizedString)( uint messageType, languageDefinition *definition, uint plural )
{
    int i;
    languageDictionary *dictionary = &definition->messages;
    uint pluralForm = definition->whichPluralForm(plural);
    
    for (i = 0; (*dictionary)[i].value; ++i)
    {
        if ( (*dictionary)[i].key == messageType && (*dictionary)[i].pluralForm == pluralForm )
        {
            return (*dictionary)[i].value;
        }
    }
    return NULL;
}


/**
 *  Provides a string given `messageType` in the current
 *  localization, returning the correct plural form given
 *  `quantity`.
 *
 *  This isn't currently highly optimized; rewriting some
 *  of infrastructure to use hash lookups is a preferred
 *  future optimization.
 */
ctmbstr tidyLocalizedStringN( uint messageType, uint quantity )
{
    ctmbstr result;
    
    result  = TY_(tidyLocalizedString)( messageType, tidyLanguages.currentLanguage, quantity);
    
    if (!result && tidyLanguages.fallbackLanguage )
    {
        result = TY_(tidyLocalizedString)( messageType, tidyLanguages.fallbackLanguage, quantity);
    }
    
    if (!result)
    {
        /* Fallback to en which is built in. */
        result = TY_(tidyLocalizedString)( messageType, &language_en, quantity);
    }
    
    if (!result)
    {
        /* Last resort: Fallback to en singular which is built in. */
        result = TY_(tidyLocalizedString)( messageType, &language_en, 1);
    }
    
    return result;
}


/**
 *  Provides a string given `messageType` in the current
 *  localization, in the non-plural form.
 *
 *  This isn't currently highly optimized; rewriting some
 *  of infrastructure to use hash lookups is a preferred
 *  future optimization.
 */
ctmbstr tidyLocalizedString( uint messageType )
{
    return tidyLocalizedStringN( messageType, 1 );
}


/**
 **  Determines the current locale without affecting the C locale.
 **  Tidy has always used the default C locale, and at this point
 **  in its development we're not going to tamper with that.
 **  @param  result The buffer to use to return the string.
 **          Returns NULL on failure.
 **  @return The same buffer for convenience.
 */
tmbstr tidySystemLocale(tmbstr result)
{
    ctmbstr temp;
    
    /* This should set the OS locale. */
    setlocale( LC_ALL, "" );
    
    /* This should read the current locale. */
    temp = setlocale( LC_ALL, NULL);
    
    /* Make a new copy of the string, because temp
     always points to the current locale. */
    if (( result = malloc( strlen( temp ) + 1 ) ))
        strcpy(result, temp);
    
    /* This should restore the C locale. */
    setlocale( LC_ALL, "C" );
    
    return result;
}


/**
 *  Retrieves the POSIX name for a string. Result is a static char so please
 *  don't try to free it. If the name looks like a cc_ll identifier, we will
 *  return it if there's no other match.
 */
tmbstr tidyNormalizedLocaleName( ctmbstr locale )
{
    uint i;
    uint len;
    static char result[6] = "xx_yy";
    tmbstr search = strdup(locale);
    search = TY_(tmbstrtolower)(search);
    
    /* See if our string matches a Windows name. */
    for (i = 0; localeMappings[i].winName; ++i)
    {
        if ( strcmp( localeMappings[i].winName, search ) == 0 )
        {
            free(search);
            search = strdup(localeMappings[i].POSIXName);
            break;
        }
    }
    
    /* We're going to be stupid about this and trust the user, and
     return just the first two characters if they exist and the
     4th and 5th if they exist. The worst that can happen is a
     junk language that doesn't exist and won't be set. */
    
    len = strlen( search );
    len = ( len <= 5 ? len : 5 );
    
    for ( i = 0; i < len; i++ )
    {
        if ( i == 2 )
        {
            /* Either terminate the string or ensure there's an underscore */
            if (len == 5) {
                result[i] = '_';
            }
            else {
                result[i] = '\0';
                break;      /* no need to copy after null */
            }
        }
        else
        {
            result[i] = tolower( search[i] );
        }
    }
    
    free( search );
    return result;
}


/**
 *  Returns the languageDefinition if the languageCode is installed in Tidy,
 *  otherwise return NULL
 */
languageDefinition *TY_(tidyTestLanguage)( ctmbstr languageCode )
{
    uint i;
    languageDefinition *testLang;
    languageDictionary *testDict;
    ctmbstr testCode;
    
    for (i = 0; tidyLanguages.languages[i]; ++i)
    {
        testLang = tidyLanguages.languages[i];
        testDict = &testLang->messages;
        testCode = (*testDict)[0].value;
        
        if ( strcmp(testCode, languageCode) == 0 )
            return testLang;
    }
    
    return NULL;
}


/**
 *  Tells Tidy to use a different language for output.
 *  @param  languageCode A Windows or POSIX language code, and must match
 *          a TIDY_LANGUAGE for an installed language.
 *  @result Indicates that a setting was applied, but not necessarily the
 *          specific request, i.e., true indicates a language and/or region
 *          was applied. If es_mx is requested but not installed, and es is
 *          installed, then es will be selected and this function will return
 *          true. However the opposite is not true; if es is requested but
 *          not present, Tidy will not try to select from the es_XX variants.
 */
Bool tidySetLanguage( ctmbstr languageCode )
{
    languageDefinition *dict1 = NULL;
    languageDefinition *dict2 = NULL;
    tmbstr wantCode = NULL;
    char lang[3] = "";
    
    if ( !languageCode || !(wantCode = tidyNormalizedLocaleName( languageCode )) )
    {
        return no;
    }
    
    /* We want to use the specified language as the currentLanguage, and set
     fallback language as necessary. We have either a two or five digit code,
     either or both of which might be installed. Let's test both of them:
     */
    
    dict1 = TY_(tidyTestLanguage( wantCode ));  /* WANTED language */
    
    if ( strlen( wantCode ) > 2 )
    {
        strncpy(lang, wantCode, 2);
        lang[2] = '\0';
        dict2 = TY_(tidyTestLanguage( lang ) ); /* BACKUP language? */
    }
    
    if ( dict1 && dict2 )
    {
        tidyLanguages.currentLanguage = dict1;
        tidyLanguages.fallbackLanguage = dict2;
    }
    if ( dict1 && !dict2 )
    {
        tidyLanguages.currentLanguage = dict1;
        tidyLanguages.fallbackLanguage = NULL;
    }
    if ( !dict1 && dict2 )
    {
        tidyLanguages.currentLanguage = dict2;
        tidyLanguages.fallbackLanguage = NULL;
    }
    if ( !dict1 && !dict2 )
    {
        /* No change. */
    }
    
    return dict1 || dict2;
}


/**
 *  Gets the current language used by Tidy.
 */
ctmbstr tidyGetLanguage()
{
    languageDefinition *langDef = tidyLanguages.currentLanguage;
    languageDictionary *langDict = &langDef->messages;
    return (*langDict)[0].value;
}


/**
 *  Provides a string given `messageType` in the default
 *  localization (which is `en`), for single plural form.
 */
ctmbstr tidyDefaultString( uint messageType )
{
    return TY_(tidyLocalizedString)( messageType, &language_en, 1);
}


/**
 *  Determines the true size of the `language_en` array indicating the
 *  number of items in the array, _not_ the highest index.
 */
const uint TY_(tidyStringKeyListSize)()
{
    static uint array_size = 0;
    
    if ( array_size == 0 )
    {
        while ( language_en.messages[array_size].value != NULL ) {
            array_size++;
        }
    }
    
    return array_size;
}


/*
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's list of localization string keys. Note that
 *  these are provided for documentation generation purposes
 *  and probably aren't useful for LibTidy implementors.
 */
TidyIterator getStringKeyList()
{
    return (TidyIterator)(size_t)1;
}

/*
 *  Provides the next key value in Tidy's list of localized
 *  strings. Note that these are provided for documentation
 *  generation purposes and probably aren't useful to
 *  libtidy implementors.
 */
uint getNextStringKey( TidyIterator* iter )
{
    uint item = 0;
    size_t itemIndex;
    assert( iter != NULL );
    
    itemIndex = (size_t)*iter;
    
    if ( itemIndex > 0 && itemIndex <= TY_(tidyStringKeyListSize)() )
    {
        item = language_en.messages[ itemIndex - 1 ].key;
        itemIndex++;
    }
    
    *iter = (TidyIterator)( itemIndex <= TY_(tidyStringKeyListSize)() ? itemIndex : (size_t)0 );
    return item;
}


/**
 *  Determines the true size of the `localeMappings` array indicating the
 *  number of items in the array, _not_ the highest index.
 */
const uint TY_(tidyLanguageListSize)()
{
    static uint array_size = 0;
    
    if ( array_size == 0 )
    {
        while ( localeMappings[array_size].winName ) {
            array_size++;
        }
    }
    
    return array_size;
}

/**
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's structure of Windows<->POSIX local mapping.
 *  Items can be retrieved with getNextWindowsLanguage();
 */
TidyIterator getWindowsLanguageList()
{
    return (TidyIterator)(size_t)1;
}

/**
 *  Returns the next record of type `localeMapItem` in
 *  Tidy's structure of Windows<->POSIX local mapping.
 */
const tidyLocaleMapItem *getNextWindowsLanguage( TidyIterator *iter )
{
    const tidyLocaleMapItem *item = NULL;
    size_t itemIndex;
    assert( iter != NULL );
    
    itemIndex = (size_t)*iter;
    
    if ( itemIndex > 0 && itemIndex <= TY_(tidyLanguageListSize)() )
    {
        item = &localeMappings[ itemIndex -1 ];
        itemIndex++;
    }
    
    *iter = (TidyIterator)( itemIndex <= TY_(tidyLanguageListSize)() ? itemIndex : (size_t)0 );
    return item;
}


/**
 *  Determines the number of languages installed in Tidy.
 */
const uint TY_(tidyInstalledLanguageListSize)()
{
    static uint array_size = 0;
    
    if ( array_size == 0 )
    {
        while ( tidyLanguages.languages[array_size] ) {
            array_size++;
        }
    }
    
    return array_size;
}

/**
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's list of installed language codes.
 *  Items can be retrieved with getNextInstalledLanguage();
 */
TidyIterator getInstalledLanguageList()
{
    return (TidyIterator)(size_t)1;
}

/**
 *  Returns the next installed language.
 */
ctmbstr getNextInstalledLanguage( TidyIterator* iter )
{
    ctmbstr item = NULL;
    size_t itemIndex;
    assert( iter != NULL );
    
    itemIndex = (size_t)*iter;
    
    if ( itemIndex > 0 && itemIndex <= TY_(tidyInstalledLanguageListSize)() )
    {
        item = tidyLanguages.languages[itemIndex - 1]->messages[0].value;
        itemIndex++;
    }
    
    *iter = (TidyIterator)( itemIndex <= TY_(tidyInstalledLanguageListSize)() ? itemIndex : (size_t)0 );
    return item;
}


/**
 *  Determines the number of error codes used by Tidy.
 */
const uint TY_(tidyErrorCodeListSize)()
{
    static uint array_size = 0;
    
    if ( array_size == 0 )
    {
        while ( tidyErrorFilterKeysStruct[array_size].key ) {
            array_size++;
        }
    }
    
    return array_size;
}

/**
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's list of error codes that can be return with
 *  `TidyReportFilter3`.
 *  Items can be retrieved with getNextErrorCode();
 */
TidyIterator getErrorCodeList()
{
    return (TidyIterator)(size_t)1;
}

/**
 *  Returns the next error code.
 */
const tidyErrorFilterKeyItem *getNextErrorCode( TidyIterator* iter )
{
    const tidyErrorFilterKeyItem *item = NULL;
    size_t itemIndex;
    assert( iter != NULL );
    
    itemIndex = (size_t)*iter;
    
    if ( itemIndex > 0 && itemIndex <= TY_(tidyErrorCodeListSize)() )
    {
        item = &tidyErrorFilterKeysStruct[itemIndex - 1];
        itemIndex++;
    }
    
    *iter = (TidyIterator)( itemIndex <= TY_(tidyErrorCodeListSize)() ? itemIndex : (size_t)0 );
    return item;
}
