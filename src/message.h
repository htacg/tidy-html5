#ifndef __MESSAGE_H__
#define __MESSAGE_H__

/* message.h -- general message writing routines

  (c) 1998-2007 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

*/

#include "forward.h"
#include "tidy.h"  /* For TidyReportLevel */
#include "language.h"

/* General message writing routines.
** Each message is a single warning, error, etc.
**
** This routine will keep track of counts and,
** if the caller has set a filter, it will be
** called.  The new preferred way of handling
** Tidy diagnostics output is either a) define
** a new output sink or b) install a message
** filter routine.
**
** Keeps track of ShowWarnings, ShowErrors, etc.
*/

ctmbstr TY_(ReleaseDate)(void);

/* void TY_(ShowVersion)( TidyDocImpl* doc ); */
void TY_(ReportUnknownOption)( TidyDocImpl* doc, ctmbstr option );
void TY_(ReportBadArgument)( TidyDocImpl* doc, ctmbstr option );
void TY_(NeedsAuthorIntervention)( TidyDocImpl* doc );

/* void TY_(HelloMessage)( TidyDocImpl* doc, ctmbstr date, ctmbstr filename ); */
void TY_(ReportMarkupVersion)( TidyDocImpl* doc );
void TY_(ReportNumWarnings)( TidyDocImpl* doc );

void TY_(GeneralInfo)( TidyDocImpl* doc );
/* void TY_(UnknownOption)( TidyDocImpl* doc, char c ); */
/* void TY_(UnknownFile)( TidyDocImpl* doc, ctmbstr program, ctmbstr file ); */
void TY_(FileError)( TidyDocImpl* doc, ctmbstr file, TidyReportLevel level );

void TY_(ErrorSummary)( TidyDocImpl* doc );

void TY_(ReportEncodingWarning)(TidyDocImpl* doc, uint code, uint encoding);
void TY_(ReportEncodingError)(TidyDocImpl* doc, uint code, uint c, Bool discarded);
void TY_(ReportEntityError)( TidyDocImpl* doc, uint code, ctmbstr entity, int c );
void TY_(ReportAttrError)( TidyDocImpl* doc, Node* node, AttVal* av, uint code );
void TY_(ReportMissingAttr)( TidyDocImpl* doc, Node* node, ctmbstr name );

#if SUPPORT_ACCESSIBILITY_CHECKS

void TY_(ReportAccessWarning)( TidyDocImpl* doc, Node* node, uint code );
void TY_(ReportAccessError)( TidyDocImpl* doc, Node* node, uint code );

#endif

void TY_(ReportNotice)(TidyDocImpl* doc, Node *element, Node *node, uint code);
void TY_(ReportWarning)(TidyDocImpl* doc, Node *element, Node *node, uint code);
void TY_(ReportError)(TidyDocImpl* doc, Node* element, Node* node, uint code);
void TY_(ReportFatal)(TidyDocImpl* doc, Node* element, Node* node, uint code);


/**
 *  These tidyErrorCodes are used throughout libtidy, and also
 *  have associated localized strings to describe them.
 */
enum tidyErrorCodes {
    /* This MUST be present and first. */
    CODES_TIDY_ERROR_FIRST = 1,

    /* error codes for entities/numeric character references */

    MISSING_SEMICOLON,
    MISSING_SEMICOLON_NCR,
    UNKNOWN_ENTITY,
    UNESCAPED_AMPERSAND,
    APOS_UNDEFINED,

    /* error codes for element messages */

    MISSING_ENDTAG_FOR,
    MISSING_ENDTAG_BEFORE,
    DISCARDING_UNEXPECTED,
    NESTED_EMPHASIS,
    NON_MATCHING_ENDTAG,
    TAG_NOT_ALLOWED_IN,
    MISSING_STARTTAG,
    UNEXPECTED_ENDTAG,
    USING_BR_INPLACE_OF,
    INSERTING_TAG,
    SUSPECTED_MISSING_QUOTE,
    MISSING_TITLE_ELEMENT,
    DUPLICATE_FRAMESET,
    CANT_BE_NESTED,
    OBSOLETE_ELEMENT,
    PROPRIETARY_ELEMENT,
    UNKNOWN_ELEMENT,
    TRIM_EMPTY_ELEMENT,
    COERCE_TO_ENDTAG,
    ILLEGAL_NESTING,
    NOFRAMES_CONTENT,
    CONTENT_AFTER_BODY,
    INCONSISTENT_VERSION,
    MALFORMED_COMMENT,
    BAD_COMMENT_CHARS,
    BAD_XML_COMMENT,
    BAD_CDATA_CONTENT,
    INCONSISTENT_NAMESPACE,
    DOCTYPE_AFTER_TAGS,
    MALFORMED_DOCTYPE,
    UNEXPECTED_END_OF_FILE,
    DTYPE_NOT_UPPER_CASE,
    TOO_MANY_ELEMENTS,
    UNESCAPED_ELEMENT,
    NESTED_QUOTATION,
    ELEMENT_NOT_EMPTY,
    ENCODING_IO_CONFLICT,
    MIXED_CONTENT_IN_BLOCK,
    MISSING_DOCTYPE,
    SPACE_PRECEDING_XMLDECL,
    TOO_MANY_ELEMENTS_IN,
    UNEXPECTED_ENDTAG_IN,
    REPLACING_ELEMENT,
    REPLACING_UNEX_ELEMENT,
    COERCE_TO_ENDTAG_WARN,

    /* error codes used for attribute messages */

    UNKNOWN_ATTRIBUTE,
    INSERTING_ATTRIBUTE,
    INSERTING_AUTO_ATTRIBUTE,
    MISSING_ATTR_VALUE,
    BAD_ATTRIBUTE_VALUE,
    UNEXPECTED_GT,
    PROPRIETARY_ATTRIBUTE,
    PROPRIETARY_ATTR_VALUE,
    REPEATED_ATTRIBUTE,
    MISSING_IMAGEMAP,
    XML_ATTRIBUTE_VALUE,
    UNEXPECTED_QUOTEMARK,
    MISSING_QUOTEMARK,
    ID_NAME_MISMATCH,

    BACKSLASH_IN_URI,
    FIXED_BACKSLASH,
    ILLEGAL_URI_REFERENCE,
    ESCAPED_ILLEGAL_URI,

    NEWLINE_IN_URI,
    ANCHOR_NOT_UNIQUE,

    JOINING_ATTRIBUTE,
    UNEXPECTED_EQUALSIGN,
    ATTR_VALUE_NOT_LCASE,
    XML_ID_SYNTAX,

    INVALID_ATTRIBUTE,

    BAD_ATTRIBUTE_VALUE_REPLACED,

    INVALID_XML_ID,
    UNEXPECTED_END_OF_FILE_ATTR,
    MISSING_ATTRIBUTE,
    WHITE_IN_URI,

    REMOVED_HTML5,                 /* this element removed from HTML5 */
    BAD_BODY_HTML5,                /* attr on body removed from HTML5 */
    BAD_ALIGN_HTML5,               /* use of align attr removed from HTML5 */
    BAD_SUMMARY_HTML5,             /* use of summary attr removed from HTML5 */

    PREVIOUS_LOCATION,             /* last */

    /* character encoding errors */

    VENDOR_SPECIFIC_CHARS,
    INVALID_SGML_CHARS,
    INVALID_UTF8,
    INVALID_UTF16,
    ENCODING_MISMATCH,
    INVALID_URI,
    INVALID_NCR,

    /* This MUST be present and last. */
    CODES_TIDY_ERROR_LAST
};


/* accessibility flaws */

#define BA_MISSING_IMAGE_ALT       1
#define BA_MISSING_LINK_ALT        2
#define BA_MISSING_SUMMARY         4
#define BA_MISSING_IMAGE_MAP       8
#define BA_USING_FRAMES            16
#define BA_USING_NOFRAMES          32
#define BA_INVALID_LINK_NOFRAMES   64  /* WAI [6.5.1.4] */  
#define BA_WAI                     (1 << 31)

/* presentation flaws */

#define USING_SPACER            1
#define USING_LAYER             2
#define USING_NOBR              4
#define USING_FONT              8
#define USING_BODY              16

/* badchar bit field */

#define BC_VENDOR_SPECIFIC_CHARS   1
#define BC_INVALID_SGML_CHARS      2
#define BC_INVALID_UTF8            4
#define BC_INVALID_UTF16           8
#define BC_ENCODING_MISMATCH       16 /* fatal error */
#define BC_INVALID_URI             32
#define BC_INVALID_NCR             64

/* Lexer and I/O Macros */

#define REPLACED_CHAR           0
#define DISCARDED_CHAR          1


#endif /* __MESSAGE_H__ */
