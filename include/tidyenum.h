#ifndef __TIDYENUM_H__
#define __TIDYENUM_H__

/*********************************************************************
 * Separated public enumerations header
 *
 * Simplifies enum re-use in various wrappers, e.g. SWIG, generated
 * wrappers, and COM IDL files.
 *
 * This file also contains macros to generate additional enums for
 * use in Tidy's language localizations. See detailed information in
 * comments.
 *
 * Enumeration use: LibTidy does *not* guarantee the integer value
 * of any enumeration label, including the starting integer value.
 * Always use enums by label in your code, and never by value.
 *
 * Enums that have starting values have starting values for a good
 * reason, mainly to prevent message overlap, because many of these
 * enums are used for string retrieval.
 *
 * (c) 1998-2017 (W3C) MIT, ERCIM, Keio University, HTACG
 * See tidy.h for the full copyright notice.
 *
 * Created 2001-05-20 by Charles Reitzel
 * Updated 2002-07-01 by Charles Reitzel - 1st Implementation 
 * Further modifications: consult git log.
 *********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/* Enumerate configuration options
*/

/** Categories of Tidy configuration options. They are used principally
 ** by the console application to generate documentation, and also have
 ** associated localized strings to describe them.
*/
typedef enum
{
  TidyMarkup = 300,    /**< Markup options: (X)HTML version, etc */
  TidyDiagnostics,     /**< Diagnostics */
  TidyPrettyPrint,     /**< Output layout */
  TidyEncoding,        /**< Character encodings */
  TidyMiscellaneous    /**< File handling, message format, etc. */
} TidyConfigCategory;


/** Option IDs Used to get/set option values.

    These TidyOptionId are used throughout libtidy, and also
    have associated localized strings to describe them.
*/
typedef enum
{
  TidyUnknownOption = 0,   /**< Unknown option! */
  TidyIndentSpaces,        /**< Indentation n spaces/tabs */
  TidyWrapLen,             /**< Wrap margin */
  TidyTabSize,             /**< Expand tabs to n spaces */

  TidyCharEncoding,        /**< In/out character encoding */
  TidyInCharEncoding,      /**< Input character encoding (if different) */
  TidyOutCharEncoding,     /**< Output character encoding (if different) */
  TidyNewline,             /**< Output line ending (default to platform) */

  TidyDoctypeMode,         /**< See doctype property */
  TidyDoctype,             /**< User specified doctype */

  TidyDuplicateAttrs,      /**< Keep first or last duplicate attribute */
  TidyAltText,             /**< Default text for alt attribute */

  TidyErrFile,             /**< File name to write errors to */
  TidyOutFile,             /**< File name to write markup to */
  TidyWriteBack,           /**< If true then output tidied markup */
  TidyShowMarkup,          /**< If false, normal output is suppressed */
  TidyShowInfo,            /**< If true, info-level messages are shown */
  TidyShowWarnings,        /**< However errors are always shown */
  TidyQuiet,               /**< No 'Parsing X', guessed DTD or summary */
  TidyIndentContent,       /**< Indent content of appropriate tags */
                           /**< "auto" does text/block level content indentation */
  TidyCoerceEndTags,       /**< Coerce end tags from start tags where probably intended */
  TidyOmitOptionalTags,    /**< Suppress optional start tags and end tags */
  TidyHideEndTags,         /**< Legacy name for TidyOmitOptionalTags */
  TidyXmlTags,             /**< Treat input as XML */
  TidyXmlOut,              /**< Create output as XML */
  TidyXhtmlOut,            /**< Output extensible HTML */
  TidyHtmlOut,             /**< Output plain HTML, even for XHTML input.
                               Yes means set explicitly. */
  TidyXmlDecl,             /**< Add <?xml?> for XML docs */
  TidyUpperCaseTags,       /**< Output tags in upper not lower case */
  TidyUpperCaseAttrs,      /**< Output attributes in upper not lower case */
  TidyMakeBare,            /**< Make bare HTML: remove Microsoft cruft */
  TidyMakeClean,           /**< Replace presentational clutter by style rules */
  TidyGDocClean,           /**< Clean up HTML exported from Google Docs */
  TidyLogicalEmphasis,     /**< Replace i by em and b by strong */
  TidyDropPropAttrs,       /**< Discard proprietary attributes */
  TidyDropFontTags,        /**< Discard presentation tags */
  TidyDropEmptyElems,      /**< Discard empty elements */
  TidyDropEmptyParas,      /**< Discard empty p elements */
  TidyFixComments,         /**< Fix comments with adjacent hyphens */
  TidyBreakBeforeBR,       /**< Output newline before <br> or not? */

  TidyNumEntities,         /**< Use numeric entities */
  TidyQuoteMarks,          /**< Output " marks as &quot; */
  TidyQuoteNbsp,           /**< Output non-breaking space as entity */
  TidyQuoteAmpersand,      /**< Output naked ampersand as &amp; */
  TidyWrapAttVals,         /**< Wrap within attribute values */
  TidyWrapScriptlets,      /**< Wrap within JavaScript string literals */
  TidyWrapSection,         /**< Wrap within <![ ... ]> section tags */
  TidyWrapAsp,             /**< Wrap within ASP pseudo elements */
  TidyWrapJste,            /**< Wrap within JSTE pseudo elements */
  TidyWrapPhp,             /**< Wrap within PHP pseudo elements */
  TidyFixBackslash,        /**< Fix URLs by replacing \ with / */
  TidyIndentAttributes,    /**< Newline+indent before each attribute */
  TidyXmlPIs,              /**< If set to yes PIs must end with ?> */
  TidyXmlSpace,            /**< If set to yes adds xml:space attr as needed */
  TidyEncloseBodyText,     /**< If yes text at body is wrapped in P's */
  TidyEncloseBlockText,    /**< If yes text in blocks is wrapped in P's */
  TidyKeepFileTimes,       /**< If yes last modied time is preserved */
  TidyWord2000,            /**< Draconian cleaning for Word2000 */
  TidyMark,                /**< Add meta element indicating tidied doc */
  TidyEmacs,               /**< If true format error output for GNU Emacs */
  TidyEmacsFile,           /**< Name of current Emacs file */
  TidyLiteralAttribs,      /**< If true attributes may use newlines */
  TidyBodyOnly,            /**< Output BODY content only */
  TidyFixUri,              /**< Applies URI encoding if necessary */
  TidyLowerLiterals,       /**< Folds known attribute values to lower case */
  TidyHideComments,        /**< Hides all (real) comments in output */
  TidyIndentCdata,         /**< Indent <!CDATA[ ... ]]> section */
  TidyForceOutput,         /**< Output document even if errors were found */
  TidyShowErrors,          /**< Number of errors to put out */
  TidyAsciiChars,          /**< Convert quotes and dashes to nearest ASCII char */
  TidyJoinClasses,         /**< Join multiple class attributes */
  TidyJoinStyles,          /**< Join multiple style attributes */
  TidyEscapeCdata,         /**< Replace <![CDATA[]]> sections with escaped text */

#if SUPPORT_ASIAN_ENCODINGS
  TidyNCR,                 /**< Allow numeric character references */
#else
  TidyNCRNotUsed,
#endif
#if SUPPORT_UTF16_ENCODINGS
  TidyOutputBOM,           /**< Output a Byte Order Mark (BOM) for UTF-16 encodings */
                           /**< auto: if input stream has BOM, we output a BOM */
#else
  TidyOutputBOMNotUsed,
#endif

  TidyReplaceColor,        /**< Replace hex color attribute values with names */
  TidyCSSPrefix,           /**< CSS class naming for -clean option */

  TidyInlineTags,          /**< Declared inline tags */
  TidyBlockTags,           /**< Declared block tags */
  TidyEmptyTags,           /**< Declared empty tags */
  TidyPreTags,             /**< Declared pre tags */

  TidyAccessibilityCheckLevel, /**< Accessibility check level
                                   0 (old style), or 1, 2, 3 */

  TidyVertSpace,           /**< degree to which markup is spread out vertically */
#if SUPPORT_ASIAN_ENCODINGS
  TidyPunctWrap,           /**< consider punctuation and breaking spaces for wrapping */
#else
  TidyPunctWrapNotUsed,
#endif
  TidyMergeEmphasis,       /**< Merge nested B and I elements */
  TidyMergeDivs,           /**< Merge multiple DIVs */
  TidyDecorateInferredUL,  /**< Mark inferred UL elements with no indent CSS */
  TidyPreserveEntities,    /**< Preserve entities */
  TidySortAttributes,      /**< Sort attributes */
  TidyMergeSpans,          /**< Merge multiple SPANs */
  TidyAnchorAsName,        /**< Define anchors as name attributes */
  TidyPPrintTabs,          /**< Indent using tabs istead of spaces */
  TidySkipNested,          /**< Skip nested tags in script and style CDATA */
  TidyStrictTagsAttr,      /**< Ensure tags and attributes match output HTML version */
  TidyEscapeScripts,       /**< Escape items that look like closing tags in script tags */
  N_TIDY_OPTIONS           /**< Must be last */
} TidyOptionId;

    
/** Option data types
*/
typedef enum
{
  TidyString,          /**< String */
  TidyInteger,         /**< Integer or enumeration */
  TidyBoolean          /**< Boolean flag */
} TidyOptionType;


/** AutoBool values used by ParseBool, ParseTriState, ParseIndent, ParseBOM
*/
typedef enum
{
   TidyNoState,     /**< maps to 'no' */
   TidyYesState,    /**< maps to 'yes' */
   TidyAutoState    /**< Automatic */
} TidyTriState;

/** TidyNewline option values to control output line endings.
*/
typedef enum
{
    TidyLF,         /**< Use Unix style: LF */
    TidyCRLF,       /**< Use DOS/Windows style: CR+LF */
    TidyCR          /**< Use Macintosh style: CR */
} TidyLineEnding;


/** Mode controlling treatment of doctype
*/
typedef enum
{
    TidyDoctypeHtml5,   /**< <!DOCTYPE html> */
    TidyDoctypeOmit,    /**< Omit DOCTYPE altogether */
    TidyDoctypeAuto,    /**< Keep DOCTYPE in input.  Set version to content */
    TidyDoctypeStrict,  /**< Convert document to HTML 4 strict content model */
    TidyDoctypeLoose,   /**< Convert document to HTML 4 transitional
                             content model */
    TidyDoctypeUser     /**< Set DOCTYPE FPI explicitly */
} TidyDoctypeModes;

/** Mode controlling treatment of duplicate Attributes
*/
typedef enum
{
    TidyKeepFirst,
    TidyKeepLast
} TidyDupAttrModes;

/** Mode controlling treatment of sorting attributes
*/
typedef enum
{
    TidySortAttrNone,
    TidySortAttrAlpha
} TidyAttrSortStrategy;


/* I/O and Message handling interface
**
** By default, Tidy will define, create and use instances of input and output
** handlers for standard C buffered I/O (i.e. FILE* stdin, ** FILE* stdout and
** FILE* stderr for content input, content output and diagnostic output,
** respectively.  A FILE* cfgFile input handler will be used for config files.
** Command line options will just be set directly.
*/

/** Message severity level. These are used throughout LibTidy to indicate the
 *  severity of a message, and they also have associated localized strings to
 *  describe them.
 */
typedef enum
{
  TidyInfo = 350,       /**< Information about markup usage */
  TidyWarning,          /**< Warning message */
  TidyConfig,           /**< Configuration error */
  TidyAccess,           /**< Accessibility message */
  TidyError,            /**< Error message - output suppressed */
  TidyBadDocument,      /**< I/O or file system error */
  TidyFatal             /**< Crash! */
} TidyReportLevel;


/* Document tree traversal functions
*/

/** Node types
*/
typedef enum
{
  TidyNode_Root,        /**< Root */
  TidyNode_DocType,     /**< DOCTYPE */
  TidyNode_Comment,     /**< Comment */
  TidyNode_ProcIns,     /**< Processing Instruction */
  TidyNode_Text,        /**< Text */
  TidyNode_Start,       /**< Start Tag */
  TidyNode_End,         /**< End Tag */
  TidyNode_StartEnd,    /**< Start/End (empty) Tag */
  TidyNode_CDATA,       /**< Unparsed Text */
  TidyNode_Section,     /**< XML Section */
  TidyNode_Asp,         /**< ASP Source */
  TidyNode_Jste,        /**< JSTE Source */
  TidyNode_Php,         /**< PHP Source */
  TidyNode_XmlDecl      /**< XML Declaration */
} TidyNodeType;


/** Known HTML element types
*/
typedef enum
{
  TidyTag_UNKNOWN,  /**< Unknown tag! */
  TidyTag_A,        /**< A */
  TidyTag_ABBR,     /**< ABBR */
  TidyTag_ACRONYM,  /**< ACRONYM */
  TidyTag_ADDRESS,  /**< ADDRESS */
  TidyTag_ALIGN,    /**< ALIGN */
  TidyTag_APPLET,   /**< APPLET */
  TidyTag_AREA,     /**< AREA */
  TidyTag_B,        /**< B */
  TidyTag_BASE,     /**< BASE */
  TidyTag_BASEFONT, /**< BASEFONT */
  TidyTag_BDO,      /**< BDO */
  TidyTag_BGSOUND,  /**< BGSOUND */
  TidyTag_BIG,      /**< BIG */
  TidyTag_BLINK,    /**< BLINK */
  TidyTag_BLOCKQUOTE,   /**< BLOCKQUOTE */
  TidyTag_BODY,     /**< BODY */
  TidyTag_BR,       /**< BR */
  TidyTag_BUTTON,   /**< BUTTON */
  TidyTag_CAPTION,  /**< CAPTION */
  TidyTag_CENTER,   /**< CENTER */
  TidyTag_CITE,     /**< CITE */
  TidyTag_CODE,     /**< CODE */
  TidyTag_COL,      /**< COL */
  TidyTag_COLGROUP, /**< COLGROUP */
  TidyTag_COMMENT,  /**< COMMENT */
  TidyTag_DD,       /**< DD */
  TidyTag_DEL,      /**< DEL */
  TidyTag_DFN,      /**< DFN */
  TidyTag_DIR,      /**< DIR */
  TidyTag_DIV,      /**< DIF */
  TidyTag_DL,       /**< DL */
  TidyTag_DT,       /**< DT */
  TidyTag_EM,       /**< EM */
  TidyTag_EMBED,    /**< EMBED */
  TidyTag_FIELDSET, /**< FIELDSET */
  TidyTag_FONT,     /**< FONT */
  TidyTag_FORM,     /**< FORM */
  TidyTag_FRAME,    /**< FRAME */
  TidyTag_FRAMESET, /**< FRAMESET */
  TidyTag_H1,       /**< H1 */
  TidyTag_H2,       /**< H2 */
  TidyTag_H3,       /**< H3 */
  TidyTag_H4,       /**< H4 */
  TidyTag_H5,       /**< H5 */
  TidyTag_H6,       /**< H6 */
  TidyTag_HEAD,     /**< HEAD */
  TidyTag_HR,       /**< HR */
  TidyTag_HTML,     /**< HTML */
  TidyTag_I,        /**< I */
  TidyTag_IFRAME,   /**< IFRAME */
  TidyTag_ILAYER,   /**< ILAYER */
  TidyTag_IMG,      /**< IMG */
  TidyTag_INPUT,    /**< INPUT */
  TidyTag_INS,      /**< INS */
  TidyTag_ISINDEX,  /**< ISINDEX */
  TidyTag_KBD,      /**< KBD */
  TidyTag_KEYGEN,   /**< KEYGEN */
  TidyTag_LABEL,    /**< LABEL */
  TidyTag_LAYER,    /**< LAYER */
  TidyTag_LEGEND,   /**< LEGEND */
  TidyTag_LI,       /**< LI */
  TidyTag_LINK,     /**< LINK */
  TidyTag_LISTING,  /**< LISTING */
  TidyTag_MAP,      /**< MAP */
  TidyTag_MATHML,   /**< MATH  (HTML5) [i_a]2 MathML embedded in [X]HTML */
  TidyTag_MARQUEE,  /**< MARQUEE */
  TidyTag_MENU,     /**< MENU */
  TidyTag_META,     /**< META */
  TidyTag_MULTICOL, /**< MULTICOL */
  TidyTag_NOBR,     /**< NOBR */
  TidyTag_NOEMBED,  /**< NOEMBED */
  TidyTag_NOFRAMES, /**< NOFRAMES */
  TidyTag_NOLAYER,  /**< NOLAYER */
  TidyTag_NOSAVE,   /**< NOSAVE */
  TidyTag_NOSCRIPT, /**< NOSCRIPT */
  TidyTag_OBJECT,   /**< OBJECT */
  TidyTag_OL,       /**< OL */
  TidyTag_OPTGROUP, /**< OPTGROUP */
  TidyTag_OPTION,   /**< OPTION */
  TidyTag_P,        /**< P */
  TidyTag_PARAM,    /**< PARAM */
  TidyTag_PICTURE,  /**< PICTURE (HTML5) */
  TidyTag_PLAINTEXT,/**< PLAINTEXT */
  TidyTag_PRE,      /**< PRE */
  TidyTag_Q,        /**< Q */
  TidyTag_RB,       /**< RB */
  TidyTag_RBC,      /**< RBC */
  TidyTag_RP,       /**< RP */
  TidyTag_RT,       /**< RT */
  TidyTag_RTC,      /**< RTC */
  TidyTag_RUBY,     /**< RUBY */
  TidyTag_S,        /**< S */
  TidyTag_SAMP,     /**< SAMP */
  TidyTag_SCRIPT,   /**< SCRIPT */
  TidyTag_SELECT,   /**< SELECT */
  TidyTag_SERVER,   /**< SERVER */
  TidyTag_SERVLET,  /**< SERVLET */
  TidyTag_SMALL,    /**< SMALL */
  TidyTag_SPACER,   /**< SPACER */
  TidyTag_SPAN,     /**< SPAN */
  TidyTag_STRIKE,   /**< STRIKE */
  TidyTag_STRONG,   /**< STRONG */
  TidyTag_STYLE,    /**< STYLE */
  TidyTag_SUB,      /**< SUB */
  TidyTag_SUP,      /**< SUP */
  TidyTag_SVG,      /**< SVG  (HTML5) */
  TidyTag_TABLE,    /**< TABLE */
  TidyTag_TBODY,    /**< TBODY */
  TidyTag_TD,       /**< TD */
  TidyTag_TEXTAREA, /**< TEXTAREA */
  TidyTag_TFOOT,    /**< TFOOT */
  TidyTag_TH,       /**< TH */
  TidyTag_THEAD,    /**< THEAD */
  TidyTag_TITLE,    /**< TITLE */
  TidyTag_TR,       /**< TR */
  TidyTag_TT,       /**< TT */
  TidyTag_U,        /**< U */
  TidyTag_UL,       /**< UL */
  TidyTag_VAR,      /**< VAR */
  TidyTag_WBR,      /**< WBR */
  TidyTag_XMP,      /**< XMP */
  TidyTag_NEXTID,   /**< NEXTID */

  TidyTag_ARTICLE,
  TidyTag_ASIDE,
  TidyTag_AUDIO,
  TidyTag_BDI,
  TidyTag_CANVAS,
  TidyTag_COMMAND,
  TidyTag_DATALIST,
  TidyTag_DETAILS,
  TidyTag_DIALOG,
  TidyTag_FIGCAPTION,
  TidyTag_FIGURE,
  TidyTag_FOOTER,
  TidyTag_HEADER,
  TidyTag_HGROUP,
  TidyTag_MAIN,
  TidyTag_MARK,
  TidyTag_MENUITEM,
  TidyTag_METER,
  TidyTag_NAV,
  TidyTag_OUTPUT,
  TidyTag_PROGRESS,
  TidyTag_SECTION,
  TidyTag_SOURCE,
  TidyTag_SUMMARY,
  TidyTag_TEMPLATE,
  TidyTag_TIME,
  TidyTag_TRACK,
  TidyTag_VIDEO,

  N_TIDY_TAGS       /**< Must be last */
} TidyTagId;

/* Attribute interrogation
*/

/** Known HTML attributes
*/
typedef enum
{
  TidyAttr_UNKNOWN,           /**< UNKNOWN= */
  TidyAttr_ABBR,              /**< ABBR= */
  TidyAttr_ACCEPT,            /**< ACCEPT= */
  TidyAttr_ACCEPT_CHARSET,    /**< ACCEPT_CHARSET= */
  TidyAttr_ACCESSKEY,         /**< ACCESSKEY= */
  TidyAttr_ACTION,            /**< ACTION= */
  TidyAttr_ADD_DATE,          /**< ADD_DATE= */
  TidyAttr_ALIGN,             /**< ALIGN= */
  TidyAttr_ALINK,             /**< ALINK= */
  TidyAttr_ALLOWFULLSCREEN,   /**< ALLOWFULLSCREEN= */
  TidyAttr_ALT,               /**< ALT= */
  TidyAttr_ARCHIVE,           /**< ARCHIVE= */
  TidyAttr_AXIS,              /**< AXIS= */
  TidyAttr_BACKGROUND,        /**< BACKGROUND= */
  TidyAttr_BGCOLOR,           /**< BGCOLOR= */
  TidyAttr_BGPROPERTIES,      /**< BGPROPERTIES= */
  TidyAttr_BORDER,            /**< BORDER= */
  TidyAttr_BORDERCOLOR,       /**< BORDERCOLOR= */
  TidyAttr_BOTTOMMARGIN,      /**< BOTTOMMARGIN= */
  TidyAttr_CELLPADDING,       /**< CELLPADDING= */
  TidyAttr_CELLSPACING,       /**< CELLSPACING= */
  TidyAttr_CHAR,              /**< CHAR= */
  TidyAttr_CHAROFF,           /**< CHAROFF= */
  TidyAttr_CHARSET,           /**< CHARSET= */
  TidyAttr_CHECKED,           /**< CHECKED= */
  TidyAttr_CITE,              /**< CITE= */
  TidyAttr_CLASS,             /**< CLASS= */
  TidyAttr_CLASSID,           /**< CLASSID= */
  TidyAttr_CLEAR,             /**< CLEAR= */
  TidyAttr_CODE,              /**< CODE= */
  TidyAttr_CODEBASE,          /**< CODEBASE= */
  TidyAttr_CODETYPE,          /**< CODETYPE= */
  TidyAttr_COLOR,             /**< COLOR= */
  TidyAttr_COLS,              /**< COLS= */
  TidyAttr_COLSPAN,           /**< COLSPAN= */
  TidyAttr_COMPACT,           /**< COMPACT= */
  TidyAttr_CONTENT,           /**< CONTENT= */
  TidyAttr_COORDS,            /**< COORDS= */
  TidyAttr_DATA,              /**< DATA= */
  TidyAttr_DATAFLD,           /**< DATAFLD= */
  TidyAttr_DATAFORMATAS,      /**< DATAFORMATAS= */
  TidyAttr_DATAPAGESIZE,      /**< DATAPAGESIZE= */
  TidyAttr_DATASRC,           /**< DATASRC= */
  TidyAttr_DATETIME,          /**< DATETIME= */
  TidyAttr_DECLARE,           /**< DECLARE= */
  TidyAttr_DEFER,             /**< DEFER= */
  TidyAttr_DIR,               /**< DIR= */
  TidyAttr_DISABLED,          /**< DISABLED= */
  TidyAttr_ENCODING,          /**< ENCODING= */
  TidyAttr_ENCTYPE,           /**< ENCTYPE= */
  TidyAttr_FACE,              /**< FACE= */
  TidyAttr_FOR,               /**< FOR= */
  TidyAttr_FRAME,             /**< FRAME= */
  TidyAttr_FRAMEBORDER,       /**< FRAMEBORDER= */
  TidyAttr_FRAMESPACING,      /**< FRAMESPACING= */
  TidyAttr_GRIDX,             /**< GRIDX= */
  TidyAttr_GRIDY,             /**< GRIDY= */
  TidyAttr_HEADERS,           /**< HEADERS= */
  TidyAttr_HEIGHT,            /**< HEIGHT= */
  TidyAttr_HREF,              /**< HREF= */
  TidyAttr_HREFLANG,          /**< HREFLANG= */
  TidyAttr_HSPACE,            /**< HSPACE= */
  TidyAttr_HTTP_EQUIV,        /**< HTTP_EQUIV= */
  TidyAttr_ID,                /**< ID= */
  TidyAttr_ISMAP,             /**< ISMAP= */
  TidyAttr_ITEMID,            /**< ITEMID= */
  TidyAttr_ITEMPROP,          /**< ITEMPROP= */
  TidyAttr_ITEMREF,           /**< ITEMREF= */
  TidyAttr_ITEMSCOPE,         /**< ITEMSCOPE= */
  TidyAttr_ITEMTYPE,          /**< ITEMTYPE= */
  TidyAttr_LABEL,             /**< LABEL= */
  TidyAttr_LANG,              /**< LANG= */
  TidyAttr_LANGUAGE,          /**< LANGUAGE= */
  TidyAttr_LAST_MODIFIED,     /**< LAST_MODIFIED= */
  TidyAttr_LAST_VISIT,        /**< LAST_VISIT= */
  TidyAttr_LEFTMARGIN,        /**< LEFTMARGIN= */
  TidyAttr_LINK,              /**< LINK= */
  TidyAttr_LONGDESC,          /**< LONGDESC= */
  TidyAttr_LOWSRC,            /**< LOWSRC= */
  TidyAttr_MARGINHEIGHT,      /**< MARGINHEIGHT= */
  TidyAttr_MARGINWIDTH,       /**< MARGINWIDTH= */
  TidyAttr_MAXLENGTH,         /**< MAXLENGTH= */
  TidyAttr_MEDIA,             /**< MEDIA= */
  TidyAttr_METHOD,            /**< METHOD= */
  TidyAttr_MULTIPLE,          /**< MULTIPLE= */
  TidyAttr_NAME,              /**< NAME= */
  TidyAttr_NOHREF,            /**< NOHREF= */
  TidyAttr_NORESIZE,          /**< NORESIZE= */
  TidyAttr_NOSHADE,           /**< NOSHADE= */
  TidyAttr_NOWRAP,            /**< NOWRAP= */
  TidyAttr_OBJECT,            /**< OBJECT= */
  TidyAttr_OnAFTERUPDATE,     /**< OnAFTERUPDATE= */
  TidyAttr_OnBEFOREUNLOAD,    /**< OnBEFOREUNLOAD= */
  TidyAttr_OnBEFOREUPDATE,    /**< OnBEFOREUPDATE= */
  TidyAttr_OnBLUR,            /**< OnBLUR= */
  TidyAttr_OnCHANGE,          /**< OnCHANGE= */
  TidyAttr_OnCLICK,           /**< OnCLICK= */
  TidyAttr_OnDATAAVAILABLE,   /**< OnDATAAVAILABLE= */
  TidyAttr_OnDATASETCHANGED,  /**< OnDATASETCHANGED= */
  TidyAttr_OnDATASETCOMPLETE, /**< OnDATASETCOMPLETE= */
  TidyAttr_OnDBLCLICK,        /**< OnDBLCLICK= */
  TidyAttr_OnERRORUPDATE,     /**< OnERRORUPDATE= */
  TidyAttr_OnFOCUS,           /**< OnFOCUS= */
  TidyAttr_OnKEYDOWN,         /**< OnKEYDOWN= */
  TidyAttr_OnKEYPRESS,        /**< OnKEYPRESS= */
  TidyAttr_OnKEYUP,           /**< OnKEYUP= */
  TidyAttr_OnLOAD,            /**< OnLOAD= */
  TidyAttr_OnMOUSEDOWN,       /**< OnMOUSEDOWN= */
  TidyAttr_OnMOUSEMOVE,       /**< OnMOUSEMOVE= */
  TidyAttr_OnMOUSEOUT,        /**< OnMOUSEOUT= */
  TidyAttr_OnMOUSEOVER,       /**< OnMOUSEOVER= */
  TidyAttr_OnMOUSEUP,         /**< OnMOUSEUP= */
  TidyAttr_OnRESET,           /**< OnRESET= */
  TidyAttr_OnROWENTER,        /**< OnROWENTER= */
  TidyAttr_OnROWEXIT,         /**< OnROWEXIT= */
  TidyAttr_OnSELECT,          /**< OnSELECT= */
  TidyAttr_OnSUBMIT,          /**< OnSUBMIT= */
  TidyAttr_OnUNLOAD,          /**< OnUNLOAD= */
  TidyAttr_PROFILE,           /**< PROFILE= */
  TidyAttr_PROMPT,            /**< PROMPT= */
  TidyAttr_RBSPAN,            /**< RBSPAN= */
  TidyAttr_READONLY,          /**< READONLY= */
  TidyAttr_REL,               /**< REL= */
  TidyAttr_REV,               /**< REV= */
  TidyAttr_RIGHTMARGIN,       /**< RIGHTMARGIN= */
  TidyAttr_ROLE,              /**< ROLE= */
  TidyAttr_ROWS,              /**< ROWS= */
  TidyAttr_ROWSPAN,           /**< ROWSPAN= */
  TidyAttr_RULES,             /**< RULES= */
  TidyAttr_SCHEME,            /**< SCHEME= */
  TidyAttr_SCOPE,             /**< SCOPE= */
  TidyAttr_SCROLLING,         /**< SCROLLING= */
  TidyAttr_SELECTED,          /**< SELECTED= */
  TidyAttr_SHAPE,             /**< SHAPE= */
  TidyAttr_SHOWGRID,          /**< SHOWGRID= */
  TidyAttr_SHOWGRIDX,         /**< SHOWGRIDX= */
  TidyAttr_SHOWGRIDY,         /**< SHOWGRIDY= */
  TidyAttr_SIZE,              /**< SIZE= */
  TidyAttr_SPAN,              /**< SPAN= */
  TidyAttr_SRC,               /**< SRC= */
  TidyAttr_SRCSET,            /**< SRCSET= (HTML5) */
  TidyAttr_STANDBY,           /**< STANDBY= */
  TidyAttr_START,             /**< START= */
  TidyAttr_STYLE,             /**< STYLE= */
  TidyAttr_SUMMARY,           /**< SUMMARY= */
  TidyAttr_TABINDEX,          /**< TABINDEX= */
  TidyAttr_TARGET,            /**< TARGET= */
  TidyAttr_TEXT,              /**< TEXT= */
  TidyAttr_TITLE,             /**< TITLE= */
  TidyAttr_TOPMARGIN,         /**< TOPMARGIN= */
  TidyAttr_TRANSLATE,         /**< TRANSLATE= */
  TidyAttr_TYPE,              /**< TYPE= */
  TidyAttr_USEMAP,            /**< USEMAP= */
  TidyAttr_VALIGN,            /**< VALIGN= */
  TidyAttr_VALUE,             /**< VALUE= */
  TidyAttr_VALUETYPE,         /**< VALUETYPE= */
  TidyAttr_VERSION,           /**< VERSION= */
  TidyAttr_VLINK,             /**< VLINK= */
  TidyAttr_VSPACE,            /**< VSPACE= */
  TidyAttr_WIDTH,             /**< WIDTH= */
  TidyAttr_WRAP,              /**< WRAP= */
  TidyAttr_XML_LANG,          /**< XML_LANG= */
  TidyAttr_XML_SPACE,         /**< XML_SPACE= */
  TidyAttr_XMLNS,             /**< XMLNS= */

  TidyAttr_EVENT,             /**< EVENT= */
  TidyAttr_METHODS,           /**< METHODS= */
  TidyAttr_N,                 /**< N= */
  TidyAttr_SDAFORM,           /**< SDAFORM= */
  TidyAttr_SDAPREF,           /**< SDAPREF= */
  TidyAttr_SDASUFF,           /**< SDASUFF= */
  TidyAttr_URN,               /**< URN= */

  TidyAttr_ASYNC,
  TidyAttr_AUTOCOMPLETE,
  TidyAttr_AUTOFOCUS,
  TidyAttr_AUTOPLAY,
  TidyAttr_CHALLENGE,
  TidyAttr_CONTENTEDITABLE,
  TidyAttr_CONTEXTMENU,
  TidyAttr_CONTROLS,
  TidyAttr_CROSSORIGIN,       /**< CROSSORIGIN= */
  TidyAttr_DEFAULT,
  TidyAttr_DIRNAME,
  TidyAttr_DRAGGABLE,
  TidyAttr_DROPZONE,
  TidyAttr_FORM,
  TidyAttr_FORMACTION,
  TidyAttr_FORMENCTYPE,
  TidyAttr_FORMMETHOD,
  TidyAttr_FORMNOVALIDATE,
  TidyAttr_FORMTARGET,
  TidyAttr_HIDDEN,
  TidyAttr_HIGH,
  TidyAttr_ICON,
  TidyAttr_KEYTYPE,
  TidyAttr_KIND,
  TidyAttr_LIST,
  TidyAttr_LOOP,
  TidyAttr_LOW,
  TidyAttr_MANIFEST,
  TidyAttr_MAX,
  TidyAttr_MEDIAGROUP,
  TidyAttr_MIN,
  TidyAttr_NOVALIDATE,
  TidyAttr_OPEN,
  TidyAttr_OPTIMUM,
  TidyAttr_OnABORT,
  TidyAttr_OnAFTERPRINT,
  TidyAttr_OnBEFOREPRINT,
  TidyAttr_OnCANPLAY,
  TidyAttr_OnCANPLAYTHROUGH,
  TidyAttr_OnCONTEXTMENU,
  TidyAttr_OnCUECHANGE,
  TidyAttr_OnDRAG,
  TidyAttr_OnDRAGEND,
  TidyAttr_OnDRAGENTER,
  TidyAttr_OnDRAGLEAVE,
  TidyAttr_OnDRAGOVER,
  TidyAttr_OnDRAGSTART,
  TidyAttr_OnDROP,
  TidyAttr_OnDURATIONCHANGE,
  TidyAttr_OnEMPTIED,
  TidyAttr_OnENDED,
  TidyAttr_OnERROR,
  TidyAttr_OnHASHCHANGE,
  TidyAttr_OnINPUT,
  TidyAttr_OnINVALID,
  TidyAttr_OnLOADEDDATA,
  TidyAttr_OnLOADEDMETADATA,
  TidyAttr_OnLOADSTART,
  TidyAttr_OnMESSAGE,
  TidyAttr_OnMOUSEWHEEL,
  TidyAttr_OnOFFLINE,
  TidyAttr_OnONLINE,
  TidyAttr_OnPAGEHIDE,
  TidyAttr_OnPAGESHOW,
  TidyAttr_OnPAUSE,
  TidyAttr_OnPLAY,
  TidyAttr_OnPLAYING,
  TidyAttr_OnPOPSTATE,
  TidyAttr_OnPROGRESS,
  TidyAttr_OnRATECHANGE,
  TidyAttr_OnREADYSTATECHANGE,
  TidyAttr_OnREDO,
  TidyAttr_OnRESIZE,
  TidyAttr_OnSCROLL,
  TidyAttr_OnSEEKED,
  TidyAttr_OnSEEKING,
  TidyAttr_OnSHOW,
  TidyAttr_OnSTALLED,
  TidyAttr_OnSTORAGE,
  TidyAttr_OnSUSPEND,
  TidyAttr_OnTIMEUPDATE,
  TidyAttr_OnUNDO,
  TidyAttr_OnVOLUMECHANGE,
  TidyAttr_OnWAITING,
  TidyAttr_PATTERN,
  TidyAttr_PLACEHOLDER,
  TidyAttr_POSTER,
  TidyAttr_PRELOAD,
  TidyAttr_PUBDATE,
  TidyAttr_RADIOGROUP,
  TidyAttr_REQUIRED,
  TidyAttr_REVERSED,
  TidyAttr_SANDBOX,
  TidyAttr_SCOPED,
  TidyAttr_SEAMLESS,
  TidyAttr_SIZES,
  TidyAttr_SPELLCHECK,
  TidyAttr_SRCDOC,
  TidyAttr_SRCLANG,
  TidyAttr_STEP,
  TidyAttr_ARIA_ACTIVEDESCENDANT,
  TidyAttr_ARIA_ATOMIC,
  TidyAttr_ARIA_AUTOCOMPLETE,
  TidyAttr_ARIA_BUSY,
  TidyAttr_ARIA_CHECKED,
  TidyAttr_ARIA_CONTROLS,
  TidyAttr_ARIA_DESCRIBEDBY,
  TidyAttr_ARIA_DISABLED,
  TidyAttr_ARIA_DROPEFFECT,
  TidyAttr_ARIA_EXPANDED,
  TidyAttr_ARIA_FLOWTO,
  TidyAttr_ARIA_GRABBED,
  TidyAttr_ARIA_HASPOPUP,
  TidyAttr_ARIA_HIDDEN,
  TidyAttr_ARIA_INVALID,
  TidyAttr_ARIA_LABEL,
  TidyAttr_ARIA_LABELLEDBY,
  TidyAttr_ARIA_LEVEL,
  TidyAttr_ARIA_LIVE,
  TidyAttr_ARIA_MULTILINE,
  TidyAttr_ARIA_MULTISELECTABLE,
  TidyAttr_ARIA_ORIENTATION,
  TidyAttr_ARIA_OWNS,
  TidyAttr_ARIA_POSINSET,
  TidyAttr_ARIA_PRESSED,
  TidyAttr_ARIA_READONLY,
  TidyAttr_ARIA_RELEVANT,
  TidyAttr_ARIA_REQUIRED,
  TidyAttr_ARIA_SELECTED,
  TidyAttr_ARIA_SETSIZE,
  TidyAttr_ARIA_SORT,
  TidyAttr_ARIA_VALUEMAX,
  TidyAttr_ARIA_VALUEMIN,
  TidyAttr_ARIA_VALUENOW,
  TidyAttr_ARIA_VALUETEXT,

  /* SVG attributes (SVG 1.1) */
  TidyAttr_X,                   /**< X= */
  TidyAttr_Y,                   /**< Y= */
  TidyAttr_VIEWBOX,             /**< VIEWBOX= */
  TidyAttr_PRESERVEASPECTRATIO, /**< PRESERVEASPECTRATIO= */
  TidyAttr_ZOOMANDPAN,          /**< ZOOMANDPAN= */
  TidyAttr_BASEPROFILE,         /**< BASEPROFILE= */
  TidyAttr_CONTENTSCRIPTTYPE,   /**< CONTENTSCRIPTTYPE= */
  TidyAttr_CONTENTSTYLETYPE,    /**< CONTENTSTYLETYPE= */
  /* MathML <math> attributes */
  TidyAttr_DISPLAY,             /**< DISPLAY= (html5) */

  /* RDFa global attributes */
  TidyAttr_ABOUT,             /**< ABOUT= */
  TidyAttr_DATATYPE,          /**< DATATYPE= */
  TidyAttr_INLIST,            /**< INLIST= */
  TidyAttr_PREFIX,            /**< PREFIX= */
  TidyAttr_PROPERTY,          /**< PROPERTY= */
  TidyAttr_RESOURCE,          /**< RESOURCE= */
  TidyAttr_TYPEOF,            /**< TYPEOF= */
  TidyAttr_VOCAB,             /**< VOCAB= */

  TidyAttr_INTEGRITY,         /**< INTEGRITY= */

  TidyAttr_AS,               /**< AS= */

  TidyAttr_XMLNSXLINK,        /**< svg xmls:xlink="url" */

  N_TIDY_ATTRIBS              /**< Must be last */
} TidyAttrId;

    
/*********************************************************************
 * Code Generation
 *
 * Tidy aims to provide a consistent API for library users, and so we
 * go to some lengths to provide a `tidyMessagesCodes` enum that
 * consists of the message code for every warning/error/info message
 * tha Tidy can emit, and a `tidyErrorFilterKeysStruct[]` array with
 * string representations of each message code.
 *
 * We also support the addition of message codes from other modules,
 * such as from Tidy's accessibility module.
 *
 * In order to keep code maintainable and make it simple to add new
 * messages, the `tidyMessageCodes` and `tidyErrorFilterKeysStruct[]`
 * are generated dynamically with preprocessor macros defined below,
 * or in respective modules (e.g., `access.h`).
 *
 * Any visible FOREACH_MSG_* macro (including new ones) must be
 * applied to the `tidyMessageCodes` enum with the MAKE_ENUM() macro
 * in this file, and to the `tidyErrorFilterKeysStruct[]` with 
 * MAKE_STRUCT in this file.
 *
 * Modern IDE's will dynamically pre-process all of these macros,
 * enabling code-completion of these enums and array of structs.
 *********************************************************************/

#define MAKE_ENUM(MESSAGE) MESSAGE,
#define MAKE_STRUCT(MESSAGE) {#MESSAGE, MESSAGE},

/*********************************************************************
 * These `tidyMessageCodes` are used throughout libtidy, and also have
 * associated localized strings to describe them.
 *
 * These message codes comprise every possible message that can be
 * output by Tidy in its report table and via the message filter
 * callback.
 *********************************************************************/

/* message codes for entities/numeric character references */
#define FOREACH_MSG_ENTITIES(FN)    \
        FN(APOS_UNDEFINED)          \
        FN(MISSING_SEMICOLON_NCR)   \
        FN(MISSING_SEMICOLON)       \
        FN(UNESCAPED_AMPERSAND)     \
        FN(UNKNOWN_ENTITY)

/* error codes for element messages */
#define FOREACH_MSG_ELEMENT(FN)           \
        FN(BAD_CDATA_CONTENT)             \
        FN(BAD_COMMENT_CHARS)             \
        FN(BAD_XML_COMMENT)               \
        FN(CANT_BE_NESTED)                \
        FN(COERCE_TO_ENDTAG_WARN)         \
        FN(COERCE_TO_ENDTAG)              \
        FN(CONTENT_AFTER_BODY)            \
        FN(DISCARDING_UNEXPECTED)         \
        FN(DOCTYPE_AFTER_TAGS)            \
        FN(DTYPE_NOT_UPPER_CASE)          \
        FN(DUPLICATE_FRAMESET)            \
        FN(ELEMENT_NOT_EMPTY)             \
        FN(ELEMENT_VERS_MISMATCH_ERROR)   \
        FN(ELEMENT_VERS_MISMATCH_WARN)    \
        FN(ENCODING_IO_CONFLICT)          \
        FN(ILLEGAL_NESTING)               \
        FN(INCONSISTENT_NAMESPACE)        \
        FN(INCONSISTENT_VERSION)          \
        FN(INSERTING_TAG)                 \
        FN(MALFORMED_COMMENT)             \
        FN(MALFORMED_DOCTYPE)             \
        FN(MISSING_DOCTYPE)               \
        FN(MISSING_ENDTAG_BEFORE)         \
        FN(MISSING_ENDTAG_FOR)            \
        FN(MISSING_STARTTAG)              \
        FN(MISSING_TITLE_ELEMENT)         \
        FN(MIXED_CONTENT_IN_BLOCK)        \
        FN(NESTED_EMPHASIS)               \
        FN(NESTED_QUOTATION)              \
        FN(NOFRAMES_CONTENT)              \
        FN(NON_MATCHING_ENDTAG)           \
        FN(OBSOLETE_ELEMENT)              \
        FN(PROPRIETARY_ELEMENT)           \
        FN(REPLACING_ELEMENT)             \
        FN(REPLACING_UNEX_ELEMENT)        \
        FN(SPACE_PRECEDING_XMLDECL)       \
        FN(SUSPECTED_MISSING_QUOTE)       \
        FN(TAG_NOT_ALLOWED_IN)            \
        FN(TOO_MANY_ELEMENTS_IN)          \
        FN(TOO_MANY_ELEMENTS)             \
        FN(TRIM_EMPTY_ELEMENT)            \
        FN(UNESCAPED_ELEMENT)             \
        FN(UNEXPECTED_END_OF_FILE)        \
        FN(UNEXPECTED_ENDTAG_IN)          \
        FN(UNEXPECTED_ENDTAG)             \
        FN(UNKNOWN_ELEMENT)               \
        FN(USING_BR_INPLACE_OF)

/* error codes used for attribute messages */
#define FOREACH_MSG_ATTRIBUTE(FN)          \
        FN(ANCHOR_NOT_UNIQUE)              \
        FN(ATTR_VALUE_NOT_LCASE)           \
        FN(BACKSLASH_IN_URI)               \
        FN(BAD_ATTRIBUTE_VALUE_REPLACED)   \
        FN(BAD_ATTRIBUTE_VALUE)            \
        FN(BAD_SUMMARY_HTML5)              \
        FN(ESCAPED_ILLEGAL_URI)            \
        FN(FIXED_BACKSLASH)                \
        FN(ID_NAME_MISMATCH)               \
        FN(ILLEGAL_URI_REFERENCE)          \
        FN(INSERTING_ATTRIBUTE)            \
        FN(INSERTING_AUTO_ATTRIBUTE)       \
        FN(INVALID_ATTRIBUTE)              \
        FN(INVALID_XML_ID)                 \
        FN(JOINING_ATTRIBUTE)              \
        FN(MISMATCHED_ATTRIBUTE_ERROR)     \
        FN(MISMATCHED_ATTRIBUTE_WARN)      \
        FN(MISSING_ATTR_VALUE)             \
        FN(MISSING_ATTRIBUTE)              \
        FN(MISSING_IMAGEMAP)               \
        FN(MISSING_QUOTEMARK)              \
        FN(NEWLINE_IN_URI)                 \
        FN(PREVIOUS_LOCATION)              \
        FN(PROPRIETARY_ATTR_VALUE)         \
        FN(PROPRIETARY_ATTRIBUTE)          \
        FN(REMOVED_HTML5)                  \
        FN(REPEATED_ATTRIBUTE)             \
        FN(UNEXPECTED_END_OF_FILE_ATTR)    \
        FN(UNEXPECTED_EQUALSIGN)           \
        FN(UNEXPECTED_GT)                  \
        FN(UNEXPECTED_QUOTEMARK)           \
        FN(UNKNOWN_ATTRIBUTE)              \
        FN(WHITE_IN_URI)                   \
        FN(XML_ATTRIBUTE_VALUE)            \
        FN(XML_ID_SYNTAX)

/* character encoding errors */
#define FOREACH_MSG_ENCODING(FN)    \
        FN(BAD_SURROGATE_LEAD)      \
        FN(BAD_SURROGATE_PAIR)      \
        FN(BAD_SURROGATE_TAIL)      \
        FN(ENCODING_MISMATCH)       \
        FN(INVALID_NCR)             \
        FN(INVALID_SGML_CHARS)      \
        FN(INVALID_URI)             \
        FN(INVALID_UTF8)            \
        FN(INVALID_UTF16)           \
        FN(VENDOR_SPECIFIC_CHARS)

/* miscellaneous config and info messages */
#define FOREACH_MSG_MISC(FN)  \
        FN(STRING_CONTENT_LOOKS)      /* `Document content looks like %s`. */                   \
        FN(STRING_DOCTYPE_GIVEN)      /* `Doctype given is \"%s\". */                           \
        FN(STRING_HTML_PROPRIETARY)   /* `HTML Proprietary`/ */                                 \
        FN(STRING_MISSING_MALFORMED)  /* For `missing or malformed argument for option: %s`. */ \
        FN(STRING_NO_SYSID)           /* `No system identifier in emitted doctype`. */          \
        FN(STRING_UNKNOWN_OPTION)     /* For retrieving a string `unknown option: %s`. */

/* accessibility module contributions */
#define FOREACH_MSG_ACCESS(FN)                                          \
/* [1.1.1.1] */     FN(IMG_MISSING_ALT)                                 \
/* [1.1.1.2] */     FN(IMG_ALT_SUSPICIOUS_FILENAME)                     \
/* [1.1.1.3] */     FN(IMG_ALT_SUSPICIOUS_FILE_SIZE)                    \
/* [1.1.1.4] */     FN(IMG_ALT_SUSPICIOUS_PLACEHOLDER)                  \
/* [1.1.1.10] */    FN(IMG_ALT_SUSPICIOUS_TOO_LONG)                     \
/* [1.1.1.11] */    FN(IMG_MISSING_ALT_BULLET)                          \
/* [1.1.1.12] */    FN(IMG_MISSING_ALT_H_RULE)                          \
/* [1.1.2.1] */     FN(IMG_MISSING_LONGDESC_DLINK)                      \
/* [1.1.2.2] */     FN(IMG_MISSING_DLINK)                               \
/* [1.1.2.3] */     FN(IMG_MISSING_LONGDESC)                            \
/* [1.1.2.5] */     FN(LONGDESC_NOT_REQUIRED)                           \
/* [1.1.3.1] */     FN(IMG_BUTTON_MISSING_ALT)                          \
/* [1.1.4.1] */     FN(APPLET_MISSING_ALT)                              \
/* [1.1.5.1] */     FN(OBJECT_MISSING_ALT)                              \
/* [1.1.6.1] */     FN(AUDIO_MISSING_TEXT_WAV)                          \
/* [1.1.6.2] */     FN(AUDIO_MISSING_TEXT_AU)                           \
/* [1.1.6.3] */     FN(AUDIO_MISSING_TEXT_AIFF)                         \
/* [1.1.6.4] */     FN(AUDIO_MISSING_TEXT_SND)                          \
/* [1.1.6.5] */     FN(AUDIO_MISSING_TEXT_RA)                           \
/* [1.1.6.6] */     FN(AUDIO_MISSING_TEXT_RM)                           \
/* [1.1.8.1] */     FN(FRAME_MISSING_LONGDESC)                          \
/* [1.1.9.1] */     FN(AREA_MISSING_ALT)                                \
/* [1.1.10.1] */    FN(SCRIPT_MISSING_NOSCRIPT)                         \
/* [1.1.12.1] */    FN(ASCII_REQUIRES_DESCRIPTION)                      \
/* [1.2.1.1] */     FN(IMG_MAP_SERVER_REQUIRES_TEXT_LINKS)              \
/* [1.4.1.1] */     FN(MULTIMEDIA_REQUIRES_TEXT)                        \
/* [1.5.1.1] */     FN(IMG_MAP_CLIENT_MISSING_TEXT_LINKS)               \
/* [2.1.1.1] */     FN(INFORMATION_NOT_CONVEYED_IMAGE)                  \
/* [2.1.1.2] */     FN(INFORMATION_NOT_CONVEYED_APPLET)                 \
/* [2.1.1.3] */     FN(INFORMATION_NOT_CONVEYED_OBJECT)                 \
/* [2.1.1.4] */     FN(INFORMATION_NOT_CONVEYED_SCRIPT)                 \
/* [2.1.1.5] */     FN(INFORMATION_NOT_CONVEYED_INPUT)                  \
/* [2.2.1.1] */     FN(COLOR_CONTRAST_TEXT)                             \
/* [2.2.1.2] */     FN(COLOR_CONTRAST_LINK)                             \
/* [2.2.1.3] */     FN(COLOR_CONTRAST_ACTIVE_LINK)                      \
/* [2.2.1.4] */     FN(COLOR_CONTRAST_VISITED_LINK)                     \
/* [3.2.1.1] */     FN(DOCTYPE_MISSING)                                 \
/* [3.3.1.1] */     FN(STYLE_SHEET_CONTROL_PRESENTATION)                \
/* [3.5.1.1] */     FN(HEADERS_IMPROPERLY_NESTED)                       \
/* [3.5.2.1] */     FN(POTENTIAL_HEADER_BOLD)                           \
/* [3.5.2.2] */     FN(POTENTIAL_HEADER_ITALICS)                        \
/* [3.5.2.3] */     FN(POTENTIAL_HEADER_UNDERLINE)                      \
/* [3.5.3.1] */     FN(HEADER_USED_FORMAT_TEXT)                         \
/* [3.6.1.1] */     FN(LIST_USAGE_INVALID_UL)                           \
/* [3.6.1.2] */     FN(LIST_USAGE_INVALID_OL)                           \
/* [3.6.1.4] */     FN(LIST_USAGE_INVALID_LI)                           \
/* [4.1.1.1] */     FN(INDICATE_CHANGES_IN_LANGUAGE)                    \
/* [4.3.1.1] */     FN(LANGUAGE_NOT_IDENTIFIED)                         \
/* [4.3.1.1] */     FN(LANGUAGE_INVALID)                                \
/* [5.1.2.1] */     FN(DATA_TABLE_MISSING_HEADERS)                      \
/* [5.1.2.2] */     FN(DATA_TABLE_MISSING_HEADERS_COLUMN)               \
/* [5.1.2.3] */     FN(DATA_TABLE_MISSING_HEADERS_ROW)                  \
/* [5.2.1.1] */     FN(DATA_TABLE_REQUIRE_MARKUP_COLUMN_HEADERS)        \
/* [5.2.1.2] */     FN(DATA_TABLE_REQUIRE_MARKUP_ROW_HEADERS)           \
/* [5.3.1.1] */     FN(LAYOUT_TABLES_LINEARIZE_PROPERLY)                \
/* [5.4.1.1] */     FN(LAYOUT_TABLE_INVALID_MARKUP)                     \
/* [5.5.1.1] */     FN(TABLE_MISSING_SUMMARY)                           \
/* [5.5.1.2] */     FN(TABLE_SUMMARY_INVALID_NULL)                      \
/* [5.5.1.3] */     FN(TABLE_SUMMARY_INVALID_SPACES)                    \
/* [5.5.1.6] */     FN(TABLE_SUMMARY_INVALID_PLACEHOLDER)               \
/* [5.5.2.1] */     FN(TABLE_MISSING_CAPTION)                           \
/* [5.6.1.1] */     FN(TABLE_MAY_REQUIRE_HEADER_ABBR)                   \
/* [5.6.1.2] */     FN(TABLE_MAY_REQUIRE_HEADER_ABBR_NULL)              \
/* [5.6.1.3] */     FN(TABLE_MAY_REQUIRE_HEADER_ABBR_SPACES)            \
/* [6.1.1.1] */     FN(STYLESHEETS_REQUIRE_TESTING_LINK)                \
/* [6.1.1.2] */     FN(STYLESHEETS_REQUIRE_TESTING_STYLE_ELEMENT)       \
/* [6.1.1.3] */     FN(STYLESHEETS_REQUIRE_TESTING_STYLE_ATTR)          \
/* [6.2.1.1] */     FN(FRAME_SRC_INVALID)                               \
/* [6.2.2.1] */     FN(TEXT_EQUIVALENTS_REQUIRE_UPDATING_APPLET)        \
/* [6.2.2.2] */     FN(TEXT_EQUIVALENTS_REQUIRE_UPDATING_SCRIPT)        \
/* [6.2.2.3] */     FN(TEXT_EQUIVALENTS_REQUIRE_UPDATING_OBJECT)        \
/* [6.3.1.1] */     FN(PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_SCRIPT)     \
/* [6.3.1.2] */     FN(PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_OBJECT)     \
/* [6.3.1.3] */     FN(PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_EMBED)      \
/* [6.3.1.4] */     FN(PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_APPLET)     \
/* [6.5.1.1] */     FN(FRAME_MISSING_NOFRAMES)                          \
/* [6.5.1.2] */     FN(NOFRAMES_INVALID_NO_VALUE)                       \
/* [6.5.1.3] */     FN(NOFRAMES_INVALID_CONTENT)                        \
/* [6.5.1.4] */     FN(NOFRAMES_INVALID_LINK)                           \
/* [7.1.1.1] */     FN(REMOVE_FLICKER_SCRIPT)                           \
/* [7.1.1.2] */     FN(REMOVE_FLICKER_OBJECT)                           \
/* [7.1.1.3] */     FN(REMOVE_FLICKER_EMBED)                            \
/* [7.1.1.4] */     FN(REMOVE_FLICKER_APPLET)                           \
/* [7.1.1.5] */     FN(REMOVE_FLICKER_ANIMATED_GIF)                     \
/* [7.2.1.1] */     FN(REMOVE_BLINK_MARQUEE)                            \
/* [7.4.1.1] */     FN(REMOVE_AUTO_REFRESH)                             \
/* [7.5.1.1] */     FN(REMOVE_AUTO_REDIRECT)                            \
/* [8.1.1.1] */     FN(ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_SCRIPT)   \
/* [8.1.1.2] */     FN(ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_OBJECT)   \
/* [8.1.1.3] */     FN(ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_APPLET)   \
/* [8.1.1.4] */     FN(ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_EMBED)    \
/* [9.1.1.1] */     FN(IMAGE_MAP_SERVER_SIDE_REQUIRES_CONVERSION)       \
/* [9.3.1.1] */     FN(SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_DOWN)    \
/* [9.3.1.2] */     FN(SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_UP)      \
/* [9.3.1.3] */     FN(SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_CLICK)         \
/* [9.3.1.4] */     FN(SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OVER)    \
/* [9.3.1.5] */     FN(SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OUT)     \
/* [9.3.1.6] */     FN(SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_MOVE)    \
/* [10.1.1.1] */    FN(NEW_WINDOWS_REQUIRE_WARNING_NEW)                 \
/* [10.1.1.2] */    FN(NEW_WINDOWS_REQUIRE_WARNING_BLANK)               \
/* [10.2.1.1] */    FN(LABEL_NEEDS_REPOSITIONING_BEFORE_INPUT)          \
/* [10.2.1.2] */    FN(LABEL_NEEDS_REPOSITIONING_AFTER_INPUT)           \
/* [10.4.1.1] */    FN(FORM_CONTROL_REQUIRES_DEFAULT_TEXT)              \
/* [10.4.1.2] */    FN(FORM_CONTROL_DEFAULT_TEXT_INVALID_NULL)          \
/* [10.4.1.3] */    FN(FORM_CONTROL_DEFAULT_TEXT_INVALID_SPACES)        \
/* [11.2.1.1] */    FN(REPLACE_DEPRECATED_HTML_APPLET)                  \
/* [11.2.1.2] */    FN(REPLACE_DEPRECATED_HTML_BASEFONT)                \
/* [11.2.1.3] */    FN(REPLACE_DEPRECATED_HTML_CENTER)                  \
/* [11.2.1.4] */    FN(REPLACE_DEPRECATED_HTML_DIR)                     \
/* [11.2.1.5] */    FN(REPLACE_DEPRECATED_HTML_FONT)                    \
/* [11.2.1.6] */    FN(REPLACE_DEPRECATED_HTML_ISINDEX)                 \
/* [11.2.1.7] */    FN(REPLACE_DEPRECATED_HTML_MENU)                    \
/* [11.2.1.8] */    FN(REPLACE_DEPRECATED_HTML_S)                       \
/* [11.2.1.9] */    FN(REPLACE_DEPRECATED_HTML_STRIKE)                  \
/* [11.2.1.10] */   FN(REPLACE_DEPRECATED_HTML_U)                       \
/* [12.1.1.1] */    FN(FRAME_MISSING_TITLE)                             \
/* [12.1.1.2] */    FN(FRAME_TITLE_INVALID_NULL)                        \
/* [12.1.1.3] */    FN(FRAME_TITLE_INVALID_SPACES)                      \
/* [12.4.1.1] */    FN(ASSOCIATE_LABELS_EXPLICITLY)                     \
/* [12.4.1.2] */    FN(ASSOCIATE_LABELS_EXPLICITLY_FOR)                 \
/* [12.4.1.3] */    FN(ASSOCIATE_LABELS_EXPLICITLY_ID)                  \
/* [13.1.1.1] */    FN(LINK_TEXT_NOT_MEANINGFUL)                        \
/* [13.1.1.2] */    FN(LINK_TEXT_MISSING)                               \
/* [13.1.1.3] */    FN(LINK_TEXT_TOO_LONG)                              \
/* [13.1.1.4] */    FN(LINK_TEXT_NOT_MEANINGFUL_CLICK_HERE)             \
/* [13.1.1.5] */    FN(LINK_TEXT_NOT_MEANINGFUL_MORE)                   \
/* [13.1.1.6] */    FN(LINK_TEXT_NOT_MEANINGFUL_FOLLOW_THIS)            \
/* [13.2.1.1] */    FN(METADATA_MISSING)                                \
/* [13.2.1.2] */    FN(METADATA_MISSING_LINK)                           \
/* [13.2.1.3] */    FN(METADATA_MISSING_REDIRECT_AUTOREFRESH)           \
/* [13.10.1.1] */   FN(SKIPOVER_ASCII_ART)


/** @} */
/** @name Data Structures */
/** @{ */


/*********************************************************************
 * `tidyMessageCodes`
 *
 * The actual definition of the enumeration, generated dynamically
 * per the notes above.
 *********************************************************************/
typedef enum
{
    /* This MUST be present and first. */
    tidyMessageCodes_first = 500,
    
    FOREACH_MSG_ENTITIES(MAKE_ENUM)
    FOREACH_MSG_ELEMENT(MAKE_ENUM)
    FOREACH_MSG_ATTRIBUTE(MAKE_ENUM)
    FOREACH_MSG_ENCODING(MAKE_ENUM)
    FOREACH_MSG_MISC(MAKE_ENUM)
    
#if SUPPORT_ACCESSIBILITY_CHECKS
    /* Defined in `access.h` */
    FOREACH_MSG_ACCESS(MAKE_ENUM)
#endif
    
    /* This MUST be present and last. */
    tidyMessageCodes_last
} tidyMessageCodes;


/*********************************************************************
 * These `tidyMessagesMisc` are used throughout libtidy, and also have
 * associated localized strings to describe them.
 *
 * These message codes comprise every possible message that can be
 * output by Tidy that are *not* diagnostic style messages available
 * in the message filter callback, and are *not* console application
 * specific messages.
 *********************************************************************/
typedef enum
{
    /* This MUST be present and first. */
    tidyMessagesMisc_first = tidyMessageCodes_last,
    
    ACCESS_URL,                             /* Used to point to Web Accessibility Guidelines. */
    ATRC_ACCESS_URL,                        /* Points to Tidy's accessibility page. */
    FILE_CANT_OPEN,                         /* For retrieving a string when a file can't be opened. */
    LINE_COLUMN_STRING,                     /* For retrieving localized `line %d column %d` text. */
    STRING_DISCARDING,                      /* For `discarding`. */
    STRING_ERROR_COUNT,                     /* `%u %s, %u %s were found!`. */
    STRING_ERROR_COUNT_ERROR,               /* `error` and `errors`. */
    STRING_ERROR_COUNT_WARNING,             /* `warning` and `warnings`. */
    STRING_HELLO_ACCESS,                    /* Accessibility hello message. */
    STRING_NO_ERRORS,                       /* `No warnings or errors were found.\n\n`. */
    STRING_NOT_ALL_SHOWN,                   /* ` Not all warnings/errors were shown.\n\n`. */
    STRING_PLAIN_TEXT,                      /* For retrieving a string `plain text`. */
    STRING_REPLACING,                       /* For `replacing`. */
    STRING_SPECIFIED,                       /* For `specified`. */
    STRING_XML_DECLARATION,                 /* For retrieving a string `XML declaration`. */
    TEXT_ACCESS_ADVICE1,                    /* Explanatory text. */
    TEXT_ACCESS_ADVICE2,                    /* Explanatory text. */
    TEXT_BAD_FORM,                          /* Explanatory text. */
    TEXT_BAD_MAIN,                          /* Explanatory text. */
    TEXT_GENERAL_INFO,                      /* Explanatory text. */
    TEXT_GENERAL_INFO_PLEA,                 /* Explanatory text. */
    TEXT_HTML_T_ALGORITHM,                  /* Paragraph for describing the HTML table algorithm. */
    TEXT_INVALID_URI,                       /* Explanatory text. */
    TEXT_INVALID_UTF16,                     /* Explanatory text. */
    TEXT_INVALID_UTF8,                      /* Explanatory text. */
    TEXT_M_IMAGE_ALT,                       /* Explanatory text. */
    TEXT_M_IMAGE_MAP,                       /* Explanatory text. */
    TEXT_M_LINK_ALT,                        /* Explanatory text. */
    TEXT_M_SUMMARY,                         /* Explanatory text. */
    TEXT_NEEDS_INTERVENTION,                /* Explanatory text. */
    TEXT_SGML_CHARS,                        /* Explanatory text. */
    TEXT_USING_BODY,                        /* Explanatory text. */
    TEXT_USING_FONT,                        /* Explanatory text. */
    TEXT_USING_FRAMES,                      /* Explanatory text. */
    TEXT_USING_LAYER,                       /* Explanatory text. */
    TEXT_USING_NOBR,                        /* Explanatory text. */
    TEXT_USING_SPACER,                      /* Explanatory text. */
    TEXT_VENDOR_CHARS,                      /* Explanatory text. */
    TEXT_WINDOWS_CHARS,                     /* Explanatory text. */
    
    /* This MUST be present and last. */
    tidyMessagesMisc_last
} tidyMessagesMisc;


#if SUPPORT_CONSOLE_APP
/*********************************************************************
 * These `tidyConsoleMessages` are used throughout libtidy, and also
 * have associated localized strings to describe them.
 *
 * These message codes comprise every message is exclusive to the
 * Tidy console application. It it possible to build LibTidy without
 * these strings.
 *********************************************************************/
typedef enum
{
    /* This MUST be present and first. */
    tidyConsoleMessages_first = tidyMessagesMisc_last,
    
    TC_LABEL_COL,
    TC_LABEL_FILE,
    TC_LABEL_LANG,
    TC_LABEL_LEVL,
    TC_LABEL_OPT,
    TC_MAIN_ERROR_LOAD_CONFIG,
    TC_OPT_ACCESS,
    TC_OPT_ASCII,
    TC_OPT_ASHTML,
    TC_OPT_ASXML,
    TC_OPT_BARE,
    TC_OPT_BIG5,
    TC_OPT_CLEAN,
    TC_OPT_CONFIG,
    TC_OPT_ERRORS,
    TC_OPT_FILE,
    TC_OPT_GDOC,
    TC_OPT_HELP,
    TC_OPT_HELPCFG,
    TC_OPT_HELPOPT,
    TC_OPT_IBM858,
    TC_OPT_INDENT,
    TC_OPT_ISO2022,
    TC_OPT_LANGUAGE,
    TC_OPT_LATIN0,
    TC_OPT_LATIN1,
    TC_OPT_MAC,
    TC_OPT_MODIFY,
    TC_OPT_NUMERIC,
    TC_OPT_OMIT,
    TC_OPT_OUTPUT,
    TC_OPT_QUIET,
    TC_OPT_RAW,
    TC_OPT_SHIFTJIS,
    TC_OPT_SHOWCFG,
    TC_OPT_UPPER,
    TC_OPT_UTF16,
    TC_OPT_UTF16BE,
    TC_OPT_UTF16LE,
    TC_OPT_UTF8,
    TC_OPT_VERSION,
    TC_OPT_WIN1252,
    TC_OPT_WRAP,
    TC_OPT_XML,
    TC_OPT_XMLCFG,
    TC_OPT_XMLSTRG,
    TC_OPT_XMLERRS,
    TC_OPT_XMLOPTS,
    TC_OPT_XMLHELP,
    TC_STRING_CONF_HEADER,
    TC_STRING_CONF_NAME,
    TC_STRING_CONF_TYPE,
    TC_STRING_CONF_VALUE,
    TC_STRING_CONF_NOTE,
    TC_STRING_OPT_NOT_DOCUMENTED,
    TC_STRING_OUT_OF_MEMORY,
    TC_STRING_FATAL_ERROR,
    TC_STRING_FILE_MANIP,
    TC_STRING_LANG_MUST_SPECIFY,
    TC_STRING_LANG_NOT_FOUND,
    TC_STRING_MUST_SPECIFY,
    TC_STRING_PROCESS_DIRECTIVES,
    TC_STRING_CHAR_ENCODING,
    TC_STRING_MISC,
    TC_STRING_XML,
    TC_STRING_UNKNOWN_OPTION,
    TC_STRING_UNKNOWN_OPTION_B,
    TC_STRING_VERS_A,
    TC_STRING_VERS_B,
    TC_TXT_HELP_1,
    TC_TXT_HELP_2A,
    TC_TXT_HELP_2B,
    TC_TXT_HELP_3,
    TC_TXT_HELP_CONFIG,
    TC_TXT_HELP_CONFIG_NAME,
    TC_TXT_HELP_CONFIG_TYPE,
    TC_TXT_HELP_CONFIG_ALLW,
    TC_TXT_HELP_LANG_1,
    TC_TXT_HELP_LANG_2,
    TC_TXT_HELP_LANG_3,
    
    /* This MUST be present and last. */
    tidyConsoleMessages_last
} tidyConsoleMessages;

#endif /* SUPPORT_CONSOLE_APP */


/** @} */


    
#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif /* __TIDYENUM_H__ */

