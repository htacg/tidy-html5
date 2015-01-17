#ifndef __TIDYENUM_H__
#define __TIDYENUM_H__

/* @file tidyenum.h -- Split public enums into separate header

  Simplifies enum re-use in various wrappers.  e.g. SWIG
  generated wrappers and COM IDL files.

  Copyright (c) 1998-2008 World Wide Web Consortium
  (Massachusetts Institute of Technology, European Research 
  Consortium for Informatics and Mathematics, Keio University).
  All Rights Reserved.

  Contributing Author(s):

     Dave Raggett <dsr@w3.org>

  The contributing author(s) would like to thank all those who
  helped with testing, bug fixes and suggestions for improvements. 
  This wouldn't have been possible without your help.

  COPYRIGHT NOTICE:
 
  This software and documentation is provided "as is," and
  the copyright holders and contributing author(s) make no
  representations or warranties, express or implied, including
  but not limited to, warranties of merchantability or fitness
  for any particular purpose or that the use of the software or
  documentation will not infringe any third party patents,
  copyrights, trademarks or other rights. 

  The copyright holders and contributing author(s) will not be held
  liable for any direct, indirect, special or consequential damages
  arising out of any use of the software or documentation, even if
  advised of the possibility of such damage.

  Permission is hereby granted to use, copy, modify, and distribute
  this source code, or portions hereof, documentation and executables,
  for any purpose, without fee, subject to the following restrictions:

  1. The origin of this source code must not be misrepresented.
  2. Altered versions must be plainly marked as such and must
     not be misrepresented as being the original source.
  3. This Copyright notice may not be removed or altered from any
     source or altered source distribution.
 
  The copyright holders and contributing author(s) specifically
  permit, without fee, and encourage the use of this source code
  as a component for supporting the Hypertext Markup Language in
  commercial products. If you use this source code in a product,
  acknowledgment is not required but would be appreciated.


  Created 2001-05-20 by Charles Reitzel
  Updated 2002-07-01 by Charles Reitzel - 1st Implementation

*/

#ifdef __cplusplus
extern "C" {
#endif

/* Enumerate configuration options
*/

/** Categories of Tidy configuration options
*/
typedef enum
{
  TidyMarkup = 0,          /**< Markup options: (X)HTML version, etc */
  TidyDiagnostics = 1,     /**< Diagnostics */
  TidyPrettyPrint = 2,     /**< Output layout */
  TidyEncoding = 3,        /**< Character encodings */
  TidyMiscellaneous = 4    /**< File handling, message format, etc. */
} TidyConfigCategory;


/** Option IDs Used to get/set option values.
*/
typedef enum
{
  TidyUnknownOption = 0,   /**< Unknown option! */
  TidyIndentSpaces = 1,    /**< Indentation n spaces */
  TidyWrapLen = 2,         /**< Wrap margin */
  TidyTabSize = 3,         /**< Expand tabs to n spaces */

  TidyCharEncoding = 4,    /**< In/out character encoding */
  TidyInCharEncoding = 5,  /**< Input character encoding (if different) */
  TidyOutCharEncoding = 6, /**< Output character encoding (if different) */
  TidyNewline = 7,         /**< Output line ending (default to platform) */

  TidyDoctypeMode = 8,     /**< See doctype property */
  TidyDoctype = 9,         /**< User specified doctype */

  TidyDuplicateAttrs = 10, /**< Keep first or last duplicate attribute */
  TidyAltText = 11,        /**< Default text for alt attribute */
  
  /* obsolete */
  TidySlideStyle = 12,     /**< Style sheet for slides: not used for anything yet */

  TidyErrFile = 13,        /**< File name to write errors to */
  TidyOutFile = 14,        /**< File name to write markup to */
  TidyWriteBack = 15,      /**< If true then output tidied markup */
  TidyShowMarkup = 16,     /**< If false, normal output is suppressed */
  TidyShowInfo = 17,       /**< If true, info-level messages are shown */
  TidyShowWarnings = 18,   /**< However errors are always shown */
  TidyQuiet = 19,          /**< No 'Parsing X', guessed DTD or summary */
  TidyIndentContent = 20,  /**< Indent content of appropriate tags */
                           /**< "auto" does text/block level content indentation */
  TidyCoerceEndTags = 21,  /**< Coerce end tags from start tags where probably intended */
  TidyOmitOptionalTags = 22,/**< Suppress optional start tags and end tags */
  TidyHideEndTags = 23,    /**< Legacy name for TidyOmitOptionalTags */
  TidyXmlTags = 24,        /**< Treat input as XML */
  TidyXmlOut = 25,         /**< Create output as XML */
  TidyXhtmlOut = 26,       /**< Output extensible HTML */
  TidyHtmlOut = 27,        /**< Output plain HTML, even for XHTML input.
                                Yes means set explicitly. */
  TidyXmlDecl = 28,        /**< Add <?xml?> for XML docs */
  TidyUpperCaseTags = 29,  /**< Output tags in upper not lower case */
  TidyUpperCaseAttrs = 30, /**< Output attributes in upper not lower case */
  TidyMakeBare = 31,       /**< Make bare HTML: remove Microsoft cruft */
  TidyMakeClean = 32,      /**< Replace presentational clutter by style rules */
  TidyGDocClean = 33,      /**< Clean up HTML exported from Google Docs */
  TidyLogicalEmphasis = 34,/**< Replace i by em and b by strong */
  TidyDropPropAttrs = 35,  /**< Discard proprietary attributes */
  TidyDropFontTags = 36,   /**< Discard presentation tags */
  TidyDropEmptyElems = 37, /**< Discard empty elements */
  TidyDropEmptyParas = 38, /**< Discard empty p elements */
  TidyFixComments = 39,    /**< Fix comments with adjacent hyphens */
  TidyBreakBeforeBR = 40,  /**< Output newline before <br> or not? */

  /* obsolete */
  TidyBurstSlides = 41,    /**< Create slides on each h2 element */

  TidyNumEntities = 42,    /**< Use numeric entities */
  TidyQuoteMarks = 43,     /**< Output " marks as &quot; */
  TidyQuoteNbsp = 44,      /**< Output non-breaking space as entity */
  TidyQuoteAmpersand = 45, /**< Output naked ampersand as &amp; */
  TidyWrapAttVals = 46,    /**< Wrap within attribute values */
  TidyWrapScriptlets = 47, /**< Wrap within JavaScript string literals */
  TidyWrapSection = 48,    /**< Wrap within <![ ... ]> section tags */
  TidyWrapAsp = 49,        /**< Wrap within ASP pseudo elements */
  TidyWrapJste = 50,       /**< Wrap within JSTE pseudo elements */
  TidyWrapPhp = 51,        /**< Wrap within PHP pseudo elements */
  TidyFixBackslash = 52,   /**< Fix URLs by replacing \ with / */
  TidyIndentAttributes = 53,/**< Newline+indent before each attribute */
  TidyXmlPIs = 54,         /**< If set to yes PIs must end with ?> */
  TidyXmlSpace = 55,       /**< If set to yes adds xml:space attr as needed */
  TidyEncloseBodyText = 56,/**< If yes text at body is wrapped in P's */
  TidyEncloseBlockText = 57,/**< If yes text in blocks is wrapped in P's */
  TidyKeepFileTimes = 58,  /**< If yes last modied time is preserved */
  TidyWord2000 = 59,       /**< Draconian cleaning for Word2000 */
  TidyMark = 60,           /**< Add meta element indicating tidied doc */
  TidyEmacs = 61,          /**< If true format error output for GNU Emacs */
  TidyEmacsFile = 62,      /**< Name of current Emacs file */
  TidyLiteralAttribs = 63, /**< If true attributes may use newlines */
  TidyBodyOnly = 64,       /**< Output BODY content only */
  TidyFixUri = 65,         /**< Applies URI encoding if necessary */
  TidyLowerLiterals = 66,  /**< Folds known attribute values to lower case */
  TidyHideComments = 67,   /**< Hides all (real) comments in output */
  TidyIndentCdata = 68,    /**< Indent <!CDATA[ ... ]]> section */
  TidyForceOutput = 69,    /**< Output document even if errors were found */
  TidyShowErrors = 70,     /**< Number of errors to put out */
  TidyAsciiChars = 71,     /**< Convert quotes and dashes to nearest ASCII char */
  TidyJoinClasses = 72,    /**< Join multiple class attributes */
  TidyJoinStyles = 73,     /**< Join multiple style attributes */
  TidyEscapeCdata = 74,    /**< Replace <![CDATA[]]> sections with escaped text */

#if SUPPORT_ASIAN_ENCODINGS
  TidyLanguage = 75,       /**< Language property: not used for anything yet */
  TidyNCR = 76,            /**< Allow numeric character references */
#else
  TidyLanguageNotUsed = 75,
  TidyNCRNotUsed = 76,
#endif
#if SUPPORT_UTF16_ENCODINGS
  TidyOutputBOM = 77,     /**< Output a Byte Order Mark (BOM) for UTF-16 encodings */
                          /**< auto: if input stream has BOM, we output a BOM */
#else
  TidyOutputBOMNotUsed = 77,
#endif

  TidyReplaceColor = 78,   /**< Replace hex color attribute values with names */
  TidyCSSPrefix = 79,      /**< CSS class naming for -clean option */

  TidyInlineTags = 80,     /**< Declared inline tags */
  TidyBlockTags = 81,      /**< Declared block tags */
  TidyEmptyTags = 82,      /**< Declared empty tags */
  TidyPreTags = 83,         /**< Declared pre tags */

  TidyAccessibilityCheckLevel = 84,/**< Accessibility check level 
                                        0 (old style), or 1, 2, 3 */

  TidyVertSpace = 85,      /**< degree to which markup is spread out vertically */
#if SUPPORT_ASIAN_ENCODINGS
  TidyPunctWrap = 86,      /**< consider punctuation and breaking spaces for wrapping */
#else
  TidyPunctWrapNotUsed = 86,
#endif
  TidyMergeEmphasis = 87,  /**< Merge nested B and I elements */
  TidyMergeDivs = 88,      /**< Merge multiple DIVs */
  TidyDecorateInferredUL = 89, /**< Mark inferred UL elements with no indent CSS */
  TidyPreserveEntities = 90,   /**< Preserve entities */
  TidySortAttributes = 91,     /**< Sort attributes */
  TidyMergeSpans = 92,     /**< Merge multiple SPANs */
  TidyAnchorAsName = 93,   /**< Define anchors as name attributes */
  N_TIDY_OPTIONS       /**< Must be last */
} TidyOptionId;

/** Option data types
*/
typedef enum
{
  TidyString = 0,          /**< String */
  TidyInteger = 1,         /**< Integer or enumeration */
  TidyBoolean = 2          /**< Boolean flag */
} TidyOptionType;


/** AutoBool values used by ParseBool, ParseTriState, ParseIndent, ParseBOM
*/
typedef enum
{
   TidyNoState = 0,     /**< maps to 'no' */
   TidyYesState = 1,    /**< maps to 'yes' */
   TidyAutoState = 2    /**< Automatic */
} TidyTriState;

/** TidyNewline option values to control output line endings.
*/
typedef enum
{
    TidyLF = 0,         /**< Use Unix style: LF */
    TidyCRLF = 1,       /**< Use DOS/Windows style: CR+LF */
    TidyCR = 2          /**< Use Macintosh style: CR */
} TidyLineEnding;


/** Mode controlling treatment of doctype
*/
typedef enum
{
    TidyDoctypeHtml5 = 0,   /**< <!DOCTYPE html> */
    TidyDoctypeOmit = 1,    /**< Omit DOCTYPE altogether */
    TidyDoctypeAuto = 2,    /**< Keep DOCTYPE in input.  Set version to content */
    TidyDoctypeStrict = 3,  /**< Convert document to HTML 4 strict content model */
    TidyDoctypeLoose = 4,   /**< Convert document to HTML 4 transitional
                                 content model */
    TidyDoctypeUser = 5    /**< Set DOCTYPE FPI explicitly */
} TidyDoctypeModes;

/** Mode controlling treatment of duplicate Attributes
*/
typedef enum
{
    TidyKeepFirst = 0,
    TidyKeepLast = 1
} TidyDupAttrModes;

/** Mode controlling treatment of sorting attributes
*/
typedef enum
{
    TidySortAttrNone = 0,
    TidySortAttrAlpha = 1
} TidyAttrSortStrategy;

/* I/O and Message handling interface
**
** By default, Tidy will define, create and use 
** instances of input and output handlers for 
** standard C buffered I/O (i.e. FILE* stdin,
** FILE* stdout and FILE* stderr for content
** input, content output and diagnostic output,
** respectively.  A FILE* cfgFile input handler
** will be used for config files.  Command line
** options will just be set directly.
*/

/** Message severity level
*/
typedef enum 
{
  TidyInfo = 0,             /**< Information about markup usage */
  TidyWarning = 1,          /**< Warning message */
  TidyConfig = 2,           /**< Configuration error */
  TidyAccess = 3,           /**< Accessibility message */
  TidyError = 4,            /**< Error message - output suppressed */
  TidyBadDocument = 5,      /**< I/O or file system error */
  TidyFatal = 6             /**< Crash! */
} TidyReportLevel;


/* Document tree traversal functions
*/

/** Node types
*/
typedef enum 
{
  TidyNode_Root = 0,        /**< Root */
  TidyNode_DocType = 1,     /**< DOCTYPE */
  TidyNode_Comment = 2,     /**< Comment */
  TidyNode_ProcIns = 3,     /**< Processing Instruction */
  TidyNode_Text = 4,        /**< Text */
  TidyNode_Start = 5,       /**< Start Tag */
  TidyNode_End = 6,         /**< End Tag */
  TidyNode_StartEnd = 7,    /**< Start/End (empty) Tag */
  TidyNode_CDATA = 8,       /**< Unparsed Text */
  TidyNode_Section = 9,     /**< XML Section */
  TidyNode_Asp = 10,        /**< ASP Source */
  TidyNode_Jste = 11,       /**< JSTE Source */
  TidyNode_Php = 12,        /**< PHP Source */
  TidyNode_XmlDecl = 13     /**< XML Declaration */
} TidyNodeType;


/** Known HTML element types
*/
typedef enum
{
  TidyTag_UNKNOWN,   /**< Unknown tag! */
  TidyTag_A,         /**< A */
  TidyTag_ABBR,      /**< ABBR */
  TidyTag_ACRONYM,   /**< ACRONYM */
  TidyTag_ADDRESS,   /**< ADDRESS */
  TidyTag_ALIGN,     /**< ALIGN */
  TidyTag_APPLET,    /**< APPLET */
  TidyTag_AREA,      /**< AREA */
  TidyTag_B,         /**< B */
  TidyTag_BASE,      /**< BASE */
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
  TidyTag_CANVAS,
  TidyTag_COMMAND,
  TidyTag_DATALIST,
  TidyTag_DETAILS,
  TidyTag_FIGCAPTION,
  TidyTag_FIGURE,
  TidyTag_FOOTER,
  TidyTag_HEADER,
  TidyTag_HGROUP,
  TidyTag_MARK,
  TidyTag_METER,
  TidyTag_NAV,
  TidyTag_OUTPUT,
  TidyTag_PROGRESS,
  TidyTag_SECTION,
  TidyTag_SOURCE,
  TidyTag_SUMMARY,
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
  TidyAttr_ITEMPROP,          /**< ITEMPROP= */
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
  TidyAttr_STANDBY,           /**< STANDBY= */
  TidyAttr_START,             /**< START= */
  TidyAttr_STYLE,             /**< STYLE= */
  TidyAttr_SUMMARY,           /**< SUMMARY= */
  TidyAttr_TABINDEX,          /**< TABINDEX= */
  TidyAttr_TARGET,            /**< TARGET= */
  TidyAttr_TEXT,              /**< TEXT= */
  TidyAttr_TITLE,             /**< TITLE= */
  TidyAttr_TOPMARGIN,         /**< TOPMARGIN= */
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


  N_TIDY_ATTRIBS              /**< Must be last */
} TidyAttrId;

#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif /* __TIDYENUM_H__ */
