#ifndef __MESSAGE_H__
#define __MESSAGE_H__

/******************************************************************************
 * General Message Writing Routines
 *
 * This module handles LibTidy's high level output routines, as well as
 * provides lookup functions and management for keys used for retrieval
 * of these messages.
 *
 * LibTidy emits two general types of output:
 *
 *  - Reports, which contain data relating to what Tidy discovered in your
 *    source file, and/or what Tidy did to your source file. In some cases
 *    general information about your source file is emitted as well. Reports
 *    are emitted in the current output buffer, but LibTidy users will probably
 *    prefer to hook into a callback in order to take advantage of the data
 *    that are available in a more flexible way.
 *
 *  - Dialogue, consisting of general information that's not related to your
 *    source file in particular, is also written to the current output buffer
 *    when appropriate.
 *
 * Report information typically takes the form of a warning, an error, info,
 * etc., and the output routines keep track of the count of these.
 *
 * The preferred way of handling Tidy diagnostics output is either
 *   - define a new output sink, or
 *   - use a message filter callback routine.
 * *
 * (c) 1998-2017 (W3C) MIT, ERCIM, Keio University, University of
 * Toronto, HTACG
 * See tidy.h for the copyright notice.
 ******************************************************************************/

#include "forward.h"

/** @name Release Information */
/** @{ */


ctmbstr TY_(ReleaseDate)(void);
ctmbstr TY_(tidyLibraryVersion)(void);


/** @} */
/** @name High Level Message Writing Functions - General */
/** @{ */


void TY_(ReportNotice)(TidyDocImpl* doc, Node *element, Node *node, uint code);
void TY_(ReportWarning)(TidyDocImpl* doc, Node *element, Node *node, uint code);
void TY_(ReportError)(TidyDocImpl* doc, Node* element, Node* node, uint code);
void TY_(ReportFatal)(TidyDocImpl* doc, Node* element, Node* node, uint code);


/** @} */
/** @name High Level Message Writing Functions - Specific */
/** @{ */


void TY_(FileError)( TidyDocImpl* doc, ctmbstr file, TidyReportLevel level );
void TY_(ReportAttrError)( TidyDocImpl* doc, Node* node, AttVal* av, uint code );
void TY_(ReportBadArgument)( TidyDocImpl* doc, ctmbstr option );
void TY_(ReportEncodingError)(TidyDocImpl* doc, uint code, uint c, Bool discarded);
void TY_(ReportEncodingWarning)(TidyDocImpl* doc, uint code, uint encoding);
void TY_(ReportEntityError)( TidyDocImpl* doc, uint code, ctmbstr entity, int c );
void TY_(ReportMarkupVersion)( TidyDocImpl* doc );
void TY_(ReportMissingAttr)( TidyDocImpl* doc, Node* node, ctmbstr name );
void TY_(ReportSurrogateError)(TidyDocImpl* doc, uint code, uint c1, uint c2);
void TY_(ReportUnknownOption)( TidyDocImpl* doc, ctmbstr option );


#if SUPPORT_ACCESSIBILITY_CHECKS

void TY_(ReportAccessError)( TidyDocImpl* doc, Node* node, uint code );
void TY_(ReportAccessWarning)( TidyDocImpl* doc, Node* node, uint code );

#endif


/** @} */
/** @name Output Dialogue Information */
/** @{ */


void TY_(DialogueMessage)( TidyDocImpl* doc, uint code, TidyReportLevel level );
void TY_(ErrorSummary)( TidyDocImpl* doc );
void TY_(ReportNumWarnings)( TidyDocImpl* doc );


/** @} */
/** @name Key Discovery */
/** @{ */

/**
 *  LibTidy users may want to use `TidyReportCallback` to enable their own
 *  localization lookup features. Because Tidy's report codes are enums the
 *  specific values can change over time. This function returns a string
 *  representing the enum value name that can be used as a lookup key
 *  independent of changing string values. `TidyReportCallback` will return
 *  this general string as the report message key.
 */
ctmbstr TY_(tidyErrorCodeAsKey)(uint code);

/**
 *  Given an error code string, return the integer value of it, or UINT_MAX
 *  as an error flag.
 */
uint TY_(tidyErrorCodeFromKey)(ctmbstr code);


/**
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's list of error codes that can be return with
 *  `TidyReportFilter3`.
 *  Items can be retrieved with getNextErrorCode();
 */
TidyIterator TY_(getErrorCodeList)();

/**
 *  Returns the next error code having initialized the iterator
 *  with `getErrorCodeList()`. You can use tidyErrorCodeAsKey
 *  to determine the key for this value.
 */
uint TY_(getNextErrorCode)( TidyIterator* iter );


/** @} */
/** @name Output Utility Functions */
/** @{ */

/** Performs word wrapping on `string` limiting output to `column`, returning
 ** an allocated string.
 ** @param doc A TidyDocImpl instance.
 ** @param string The text to wrap.
 ** @param columns The maximum column count to output.
 ** @result An allocated, word-wrapped string.
 */
tmbstr TY_(tidyWrappedText)(TidyDocImpl* doc, ctmbstr string, uint columns);

/** @} */


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
