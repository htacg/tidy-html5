/* message.c
   Routines to handle messages and other output, as well as
   various utility routines used to generate data for output.

  (c) 1998-2008 (W3C) MIT, ERCIM, Keio University
  Portions Copyright University of Toronto
  See tidy.h and access.h for the copyright notice.

*/

#include "tidy-int.h"
#include "lexer.h"
#include "streamio.h"
#include "message.h"
#include "tmbstr.h"
#include "utf8.h"
#if !defined(NDEBUG) && defined(_MSC_VER)
#include "sprtf.h"
#endif
#include "version.h"

/**
 * Release information
 */

ctmbstr TY_(ReleaseDate)(void)
{
  return TY_(release_date);
}

ctmbstr TIDY_CALL tidyLibraryVersion(void)
{
  return TY_(library_version);
}


/**
 * Documentation of configuration options:
 *
 * Although most of the strings now come from the language module, the
 * documentation incorporates a series of cross-references that are generated
 * in this messaging module.
 */

/* Cross-references definitions.
 * Note that each list must be terminated with `TidyUnknownOption`.
 */
static const TidyOptionId TidyAsciiCharsLinks[] =      { TidyMakeClean, TidyUnknownOption };
static const TidyOptionId TidyBlockTagsLinks[] =       { TidyEmptyTags, TidyInlineTags, TidyPreTags, TidyUnknownOption };
static const TidyOptionId TidyCharEncodingLinks[] =    { TidyInCharEncoding, TidyOutCharEncoding, TidyUnknownOption };
static const TidyOptionId TidyDuplicateAttrsLinks[] =  { TidyJoinClasses, TidyJoinStyles, TidyUnknownOption };
static const TidyOptionId TidyEmptyTagsLinks[] =       { TidyBlockTags, TidyInlineTags, TidyPreTags, TidyUnknownOption };
static const TidyOptionId TidyErrFileLinks[] =         { TidyOutFile, TidyUnknownOption };
static const TidyOptionId TidyInCharEncodingLinks[] =  { TidyCharEncoding, TidyUnknownOption };
static const TidyOptionId TidyIndentContentLinks[] =   { TidyIndentSpaces, TidyUnknownOption };
static const TidyOptionId TidyIndentSpacesLinks[] =    { TidyIndentContent, TidyUnknownOption };
static const TidyOptionId TidyInlineTagsLinks[] =      { TidyBlockTags, TidyEmptyTags, TidyPreTags, TidyUnknownOption };
static const TidyOptionId TidyMergeDivsLinks[] =       { TidyMakeClean, TidyMergeSpans, TidyUnknownOption };
static const TidyOptionId TidyMergeSpansLinks[] =      { TidyMakeClean, TidyMergeDivs, TidyUnknownOption };
static const TidyOptionId TidyNumEntitiesLinks[] =     { TidyDoctype, TidyPreserveEntities, TidyUnknownOption };
static const TidyOptionId TidyOutCharEncodingLinks[] = { TidyCharEncoding, TidyUnknownOption };
static const TidyOptionId TidyOutFileLinks[] =         { TidyErrFile, TidyUnknownOption };
static const TidyOptionId TidyPreTagsLinks[] =         { TidyBlockTags, TidyEmptyTags, TidyInlineTags, TidyUnknownOption };
static const TidyOptionId TidyWrapAttValsLinks[] =     { TidyWrapScriptlets, TidyLiteralAttribs, TidyUnknownOption };
static const TidyOptionId TidyWrapScriptletsLinks[] =  { TidyWrapAttVals, TidyUnknownOption };
static const TidyOptionId TidyXmlDeclLinks[] =         { TidyCharEncoding, TidyOutCharEncoding, TidyUnknownOption };

/* Cross-reference assignments. 
 * We can't build a complex array at compile time and we're not counting on
 * any type of initialization, so this two-stage building process is required.
 */
static const TidyOptionDoc docs_xrefs[] =
{
    { TidyAsciiChars,      TidyAsciiCharsLinks      },
    { TidyBlockTags,       TidyBlockTagsLinks       },
    { TidyCharEncoding,    TidyCharEncodingLinks    },
    { TidyDuplicateAttrs,  TidyDuplicateAttrsLinks  },
    { TidyEmptyTags,       TidyEmptyTagsLinks       },
    { TidyErrFile,         TidyErrFileLinks         },
    { TidyInCharEncoding,  TidyInCharEncodingLinks  },
    { TidyIndentContent,   TidyIndentContentLinks   },
    { TidyIndentSpaces,    TidyIndentSpacesLinks    },
    { TidyInlineTags,      TidyInlineTagsLinks      },
    { TidyMergeDivs,       TidyMergeDivsLinks       },
    { TidyMergeSpans,      TidyMergeSpansLinks      },
    { TidyNumEntities,     TidyNumEntitiesLinks     },
    { TidyOutCharEncoding, TidyOutCharEncodingLinks },
    { TidyOutFile,         TidyOutFileLinks         },
    { TidyPreTags,         TidyPreTagsLinks         },
    { TidyWrapAttVals,     TidyWrapAttValsLinks     },
    { TidyWrapScriptlets,  TidyWrapScriptletsLinks  },
    { TidyXmlDecl,         TidyXmlDeclLinks         },
    { N_TIDY_OPTIONS                                }
};


/* Cross-reference retrieval. */
const TidyOptionDoc* TY_(OptGetDocDesc)( TidyOptionId optId )
{
    uint i = 0;

    while( docs_xrefs[i].opt != N_TIDY_OPTIONS )
    {
        if ( docs_xrefs[i].opt == optId )
            return &docs_xrefs[i];
        ++i;
    }
    return NULL;
}


/**
 *  General message utility functions.
 */

/* Generates the prefix string for message reports based on each
** message's TidyReportLevel.
*/
static char* LevelPrefix( TidyReportLevel level, char* buf, size_t count )
{
  *buf = 0;
  switch ( level )
  {
  case TidyInfo:
    TY_(tmbstrncpy)( buf, tidyLocalizedString(TidyInfoString), count );
    break;
  case TidyWarning:
    TY_(tmbstrncpy)( buf, tidyLocalizedString(TidyWarningString), count );
    break;
  case TidyConfig:
    TY_(tmbstrncpy)( buf, tidyLocalizedString(TidyConfigString), count );
    break;
  case TidyAccess:
    TY_(tmbstrncpy)( buf, tidyLocalizedString(TidyAccessString), count );
    break;
  case TidyError:
    TY_(tmbstrncpy)( buf, tidyLocalizedString(TidyErrorString), count );
    break;
  case TidyBadDocument:
    TY_(tmbstrncpy)( buf, tidyLocalizedString(TidyBadDocumentString), count );
    break;
  case TidyFatal:
    TY_(tmbstrncpy)( buf, tidyLocalizedString(TidyFatalString), count );
    break;
  }
  return buf + TY_(tmbstrlen)( buf );
}


/* Updates document message counts and
** compares counts to options to see if message
** display should go forward.
*/
static Bool UpdateCount( TidyDocImpl* doc, TidyReportLevel level )
{
  /* keep quiet after <ShowErrors> errors */
  Bool go = ( doc->errors < cfg(doc, TidyShowErrors) );

  switch ( level )
  {
  case TidyInfo:
    doc->infoMessages++;
    break;
  case TidyWarning:
    doc->warnings++;
    go = go && cfgBool( doc, TidyShowWarnings );
    break;
  case TidyConfig:
    doc->optionErrors++;
    break;
  case TidyAccess:
    doc->accessErrors++;
    break;
  case TidyError:
    doc->errors++;
    break;
  case TidyBadDocument:
    doc->docErrors++;
    break;
  case TidyFatal:
    /* Ack! */;
    break;
  }

  return go;
}


/* Generates the string indicating the source document position for which
** Tidy has generated a message.
*/
static char* ReportPosition(TidyDocImpl* doc, int line, int col, char* buf, size_t count)
{
    *buf = 0;

    /* Change formatting to be parsable by GNU Emacs */
    if ( cfgBool(doc, TidyEmacs) && cfgStr(doc, TidyEmacsFile) )
        TY_(tmbsnprintf)(buf, count, "%s:%d:%d: ", 
                         cfgStr(doc, TidyEmacsFile), line, col);
    else /* traditional format */
        TY_(tmbsnprintf)(buf, count, tidyLocalizedString(LINE_COLUMN_STRING), line, col);
    return buf + TY_(tmbstrlen)( buf );
}


/* General message writing routines.
** Each message is a single warning, error, etc.
** 
** These routines keep track of counts and,
** if the caller has set a filter, it will be 
** called. The new preferred way of handling
** Tidy diagnostics output is either a) define
** a new output sink or b) install a message
** filter routine.
*/

static void messagePos( TidyDocImpl* doc, TidyReportLevel level, uint code,
                        int line, int col, ctmbstr msg, va_list args )
#ifdef __GNUC__
__attribute__((format(printf, 6, 0)))
#endif
;
static void messagePos( TidyDocImpl* doc, TidyReportLevel level, uint code,
                        int line, int col, ctmbstr msg, va_list args )
{
    enum { sizeMessageBuf=2048 };
    char *messageBuf = TidyDocAlloc(doc,sizeMessageBuf);
    Bool go = UpdateCount( doc, level );

    if ( go )
    {
        va_list args_copy;
        va_copy(args_copy, args);
        TY_(tmbvsnprintf)(messageBuf, sizeMessageBuf, msg, args_copy);
        if ( doc->mssgFilt )
        {
            TidyDoc tdoc = tidyImplToDoc( doc );
            go = doc->mssgFilt( tdoc, level, line, col, messageBuf );
        }
        if ( doc->mssgFilt2 )
        {
            /* mssgFilt2 is intended to allow LibTidy users to localize
               messages via their own means by providing a key string and
               the parameters to fill it. For the key string to remain
               consistent, we have to ensure that we only ever return the
               built-in English version of this string. */
            TidyDoc tdoc = tidyImplToDoc( doc );
            va_end(args_copy);
            va_copy(args_copy, args);
            go = go | doc->mssgFilt2( tdoc, level, line, col, tidyDefaultString(code), args_copy );
        }
        if ( doc->mssgFilt3 )
        {
            /* mssgFilt3 is intended to allow LibTidy users to localize
               messages via their own means by providing a key string and
               the parameters to fill it. */
            TidyDoc tdoc = tidyImplToDoc( doc );
            va_end(args_copy);
            va_copy(args_copy, args);
            go = go | doc->mssgFilt3( tdoc, level, line, col, tidyErrorCodeAsString(code), args_copy );
        }
        va_end(args_copy);
    }

    if ( go )
    {
        enum { sizeBuf=1024 };
        TidyOutputSink *outp = &doc->errout->sink;
        char *buf = (char *)TidyDocAlloc(doc,sizeBuf);
        const char *cp;
        byte b;
        if ( line > 0 && col > 0 )
        {
            ReportPosition(doc, line, col, buf, sizeBuf);
            for ( cp = buf; *cp; ++cp )
            {
                b = (*cp & 0xff);
                outp->putByte( outp->sinkData, b );
            }
        }

        LevelPrefix( level, buf, sizeBuf );
        for ( cp = buf; *cp; ++cp )
        {
            b = (*cp & 0xff);
            outp->putByte( outp->sinkData, b );
        }
        for ( cp = messageBuf; *cp; ++cp )
        {
            b = (*cp & 0xff);
            outp->putByte( outp->sinkData, b );
        }
        TY_(WriteChar)( '\n', doc->errout );
        TidyDocFree(doc, buf);
    }
    TidyDocFree(doc, messageBuf);
}

/* Reports error at current Lexer line/column. */ 
static
void message( TidyDocImpl* doc, TidyReportLevel level, uint code,
              ctmbstr msg, ... )
#ifdef __GNUC__
__attribute__((format(printf, 4, 5)))
#endif
;

/* Reports error at node line/column. */ 
static
void messageNode( TidyDocImpl* doc, TidyReportLevel level, uint code,
                  Node* node, ctmbstr msg, ... )
#ifdef __GNUC__
__attribute__((format(printf, 5, 6)))
#endif
;

/* Reports error at given line/column. */ 
static
void messageLexer( TidyDocImpl* doc, TidyReportLevel level, uint code,
                   ctmbstr msg, ... )
#ifdef __GNUC__
__attribute__((format(printf, 4, 5)))
#endif
;

/* For general reporting.  Emits nothing if --quiet yes */
static
void tidy_out( TidyDocImpl* doc, ctmbstr msg, ... )
#ifdef __GNUC__
__attribute__((format(printf, 2, 3)))
#endif
;


void message( TidyDocImpl* doc, TidyReportLevel level, uint code,
              ctmbstr msg, ... )
{
    va_list args;
    if (level == TidyInfo && !cfgBool(doc, TidyShowInfo)) return;
    va_start( args, msg );
    messagePos( doc, level, code, 0, 0, msg, args );
    va_end( args );
}


void messageLexer( TidyDocImpl* doc, TidyReportLevel level, uint code,
                   ctmbstr msg, ... )
{
    int line = ( doc->lexer ? doc->lexer->lines : 0 );
    int col  = ( doc->lexer ? doc->lexer->columns : 0 );

    va_list args;
    va_start( args, msg );
    messagePos( doc, level, code, line, col, msg, args );
    va_end( args );
}

void messageNode( TidyDocImpl* doc, TidyReportLevel level, uint code,
                  Node* node, ctmbstr msg, ... )
{
    int line = ( node ? node->line :
                 ( doc->lexer ? doc->lexer->lines : 0 ) );
    int col  = ( node ? node->column :
                 ( doc->lexer ? doc->lexer->columns : 0 ) );

    va_list args;
    va_start( args, msg );
    messagePos( doc, level, code, line, col, msg, args );
    va_end( args );
}

void tidy_out( TidyDocImpl* doc, ctmbstr msg, ... )
{
    if ( !cfgBool(doc, TidyQuiet) )
    {
        TidyOutputSink *outp = &doc->errout->sink;
        ctmbstr cp;
        enum { sizeBuf=2048 };
        char *buf = (char *)TidyDocAlloc(doc,sizeBuf);
        byte b;

        va_list args;
        va_start( args, msg );
        TY_(tmbvsnprintf)(buf, sizeBuf, msg, args);
        va_end( args );

        for ( cp=buf; *cp; ++cp )
        {
            b = (*cp & 0xff);
            if (b == (byte)'\n')
                TY_(WriteChar)( b, doc->errout ); /* for EOL translation */
            else
                outp->putByte( outp->sinkData, b ); /* #383 - no encoding */
        }

        TidyDocFree(doc, buf);
    }
}

void TY_(FileError)( TidyDocImpl* doc, ctmbstr file, TidyReportLevel level )
{
    message( doc, level, FILE_CANT_OPEN, tidyLocalizedString(FILE_CANT_OPEN), file );
}

static char* TagToString(Node* tag, char* buf, size_t count)
{
    *buf = 0;
    if (tag)
    {
        if (TY_(nodeIsElement)(tag))
            TY_(tmbsnprintf)(buf, count, "<%s>", tag->element);
        else if (tag->type == EndTag)
            TY_(tmbsnprintf)(buf, count, "</%s>", tag->element);
        else if (tag->type == DocTypeTag)
            TY_(tmbsnprintf)(buf, count, "<!DOCTYPE>");
        else if (tag->type == TextNode)
            TY_(tmbsnprintf)(buf, count, "%s", tidyLocalizedString(STRING_PLAIN_TEXT));
        else if (tag->type == XmlDecl)
            TY_(tmbsnprintf)(buf, count, "%s", tidyLocalizedString(STRING_XML_DECLARATION));
        else if (tag->element)
            TY_(tmbsnprintf)(buf, count, "%s", tag->element);
    }
    return buf + TY_(tmbstrlen)(buf);
}

/* lexer is not defined when this is called */
void TY_(ReportUnknownOption)( TidyDocImpl* doc, ctmbstr option )
{
    assert( option != NULL );
    message( doc, TidyConfig, STRING_UNKNOWN_OPTION, tidyLocalizedString(STRING_UNKNOWN_OPTION), option );
}

/* lexer is not defined when this is called */
void TY_(ReportBadArgument)( TidyDocImpl* doc, ctmbstr option )
{
    assert( option != NULL );
    message( doc, TidyConfig, STRING_MISSING_MALFORMED, tidyLocalizedString(STRING_MISSING_MALFORMED), option );
}

static void NtoS(int n, tmbstr str)
{
    tmbchar buf[40];
    int i;

    for (i = 0;; ++i)
    {
        buf[i] = (tmbchar)( (n % 10) + '0' );

        n = n / 10;

        if (n == 0)
            break;
    }

    n = i;

    while (i >= 0)
    {
        str[n-i] = buf[i];
        --i;
    }

    str[n+1] = '\0';
}

void TY_(ReportEncodingWarning)(TidyDocImpl* doc, uint code, uint encoding)
{
    switch(code)
    {
    case ENCODING_MISMATCH:
        messageLexer(doc, TidyWarning, code, tidyLocalizedString(code),
                     TY_(CharEncodingName)(doc->docIn->encoding),
                     TY_(CharEncodingName)(encoding));
        doc->badChars |= BC_ENCODING_MISMATCH;
        break;
    }
}

void TY_(ReportEncodingError)(TidyDocImpl* doc, uint code, uint c, Bool discarded)
{
    char buf[ 32 ] = {'\0'};

    ctmbstr action = tidyLocalizedString(discarded ? STRING_DISCARDING : STRING_REPLACING);
    ctmbstr fmt = tidyLocalizedString(code);

    /* An encoding mismatch is currently treated as a non-fatal error */
    switch (code)
    {
    case VENDOR_SPECIFIC_CHARS:
        NtoS(c, buf);
        doc->badChars |= BC_VENDOR_SPECIFIC_CHARS;
        break;

    case INVALID_SGML_CHARS:
        NtoS(c, buf);
        doc->badChars |= BC_INVALID_SGML_CHARS;
        break;

    case INVALID_UTF8:
        TY_(tmbsnprintf)(buf, sizeof(buf), "U+%04X", c);
        doc->badChars |= BC_INVALID_UTF8;
        break;

#if SUPPORT_UTF16_ENCODINGS
    case INVALID_UTF16:
        TY_(tmbsnprintf)(buf, sizeof(buf), "U+%04X", c);
        doc->badChars |= BC_INVALID_UTF16;
        break;
#endif

    case INVALID_NCR:
        NtoS(c, buf);
        doc->badChars |= BC_INVALID_NCR;
        break;
    }

    if (fmt)
        messageLexer( doc, TidyWarning, code, fmt, action, buf );
}

void TY_(ReportEntityError)( TidyDocImpl* doc, uint code, ctmbstr entity,
                             int ARG_UNUSED(c) )
{
    ctmbstr fmt;
    ctmbstr entityname = ( entity ? entity : "NULL" );

    fmt = tidyLocalizedString(code);

    if (fmt)
        messageLexer( doc, TidyWarning, code, fmt, entityname );
}

void TY_(ReportSurrogateError)(TidyDocImpl* doc, uint code, uint c1, uint c2)
{
    ctmbstr fmt = tidyLocalizedString(code);
    if (fmt)
        messageLexer(doc, TidyWarning, code, fmt, c1, c2);
}

void TY_(ReportAttrError)(TidyDocImpl* doc, Node *node, AttVal *av, uint code)
{
    char const *name = "NULL", *value = "NULL";
    char tagdesc[64];
    ctmbstr fmt = tidyLocalizedString(code);
    uint version;
    ctmbstr extra_string;

    assert( fmt != NULL );

    TagToString(node, tagdesc, sizeof(tagdesc));

    if (av)
    {
        if (av->attribute)
            name = av->attribute;
        if (av->value)
            value = av->value;
    }

    switch (code)
    {
    case UNKNOWN_ATTRIBUTE:
    case INSERTING_ATTRIBUTE:
    case MISSING_ATTR_VALUE:
    case XML_ATTRIBUTE_VALUE:
    case PROPRIETARY_ATTRIBUTE:
    case JOINING_ATTRIBUTE:
        messageNode(doc, TidyWarning, code, node, fmt, tagdesc, name);
        break;

    case MISMATCHED_ATTRIBUTE_WARN:
        version = doc->lexer->versionEmitted == 0 ? doc->lexer->doctype : doc->lexer->versionEmitted;
        extra_string = TY_(HTMLVersionNameFromCode)(version, 0);
        if (!extra_string)
            extra_string = tidyLocalizedString(STRING_HTML_PROPRIETARY);
        messageNode(doc, TidyWarning, code, node, fmt, tagdesc, name, extra_string);
        break;

    case MISMATCHED_ATTRIBUTE_ERROR:
        version = doc->lexer->versionEmitted == 0 ? doc->lexer->doctype : doc->lexer->versionEmitted;
        extra_string = TY_(HTMLVersionNameFromCode)(version, 0);
        if (!extra_string)
            extra_string = tidyLocalizedString(STRING_HTML_PROPRIETARY);
        messageNode(doc, TidyError, code, node, fmt, tagdesc, name, extra_string);
        break;

    case BAD_ATTRIBUTE_VALUE:
    case BAD_ATTRIBUTE_VALUE_REPLACED:
    case INVALID_ATTRIBUTE:
    case INSERTING_AUTO_ATTRIBUTE:
        messageNode(doc, TidyWarning, code, node, fmt, tagdesc, name, value);
        break;

    case UNEXPECTED_QUOTEMARK:
    case MISSING_QUOTEMARK:
    case ID_NAME_MISMATCH:
    case BACKSLASH_IN_URI:
    case FIXED_BACKSLASH:
    case ILLEGAL_URI_REFERENCE:
    case ESCAPED_ILLEGAL_URI:
    case NEWLINE_IN_URI:
    case WHITE_IN_URI:
    case UNEXPECTED_GT:
    case INVALID_XML_ID:
    case UNEXPECTED_EQUALSIGN:
        messageNode(doc, TidyWarning, code, node, fmt, tagdesc);
        break;

    case XML_ID_SYNTAX:
    case PROPRIETARY_ATTR_VALUE:
    case ANCHOR_NOT_UNIQUE:
    case ATTR_VALUE_NOT_LCASE:
        messageNode(doc, TidyWarning, code, node, fmt, tagdesc, value);
        break;


    case MISSING_IMAGEMAP:
        messageNode(doc, TidyWarning, code, node, fmt, tagdesc);
        doc->badAccess |= BA_MISSING_IMAGE_MAP;
        break;

    case REPEATED_ATTRIBUTE:
        messageNode(doc, TidyWarning, code, node, fmt, tagdesc, value, name);
        break;

    case UNEXPECTED_END_OF_FILE_ATTR:
        /* on end of file adjust reported position to end of input */
        doc->lexer->lines   = doc->docIn->curline;
        doc->lexer->columns = doc->docIn->curcol;
        messageLexer(doc, TidyWarning, code, fmt, tagdesc);
        break;
    }
}

void TY_(ReportMissingAttr)( TidyDocImpl* doc, Node* node, ctmbstr name )
{
    char tagdesc[ 64 ];
    ctmbstr fmt = tidyLocalizedString(MISSING_ATTRIBUTE);

    assert( fmt != NULL );
    TagToString(node, tagdesc, sizeof(tagdesc));
    messageNode( doc, TidyWarning, MISSING_ATTRIBUTE, node, fmt, tagdesc, name );
}

#if SUPPORT_ACCESSIBILITY_CHECKS

/*********************************************************
* Accessibility
*
* DisplayHTMLTableAlgorithm()
*
* If the table does contain 2 or more logical levels of 
* row or column headers, the HTML 4 table algorithm 
* to show the author how the headers are currently associated 
* with the cells.
*********************************************************/
 
void TY_(DisplayHTMLTableAlgorithm)( TidyDocImpl* doc )
{
    tidy_out(doc, "%s", tidyLocalizedString(TEXT_HTML_T_ALGORITHM));
}

void TY_(ReportAccessWarning)( TidyDocImpl* doc, Node* node, uint code )
{
    ctmbstr fmt = tidyLocalizedString(code);
    doc->badAccess |= BA_WAI;
    messageNode( doc, TidyAccess, code, node, "%s", fmt );
}

void TY_(ReportAccessError)( TidyDocImpl* doc, Node* node, uint code )
{
    ctmbstr fmt = tidyLocalizedString(code);
    doc->badAccess |= BA_WAI;
    messageNode( doc, TidyAccess, code, node, "%s", fmt );
}

#endif /* SUPPORT_ACCESSIBILITY_CHECKS */

void TY_(ReportWarning)(TidyDocImpl* doc, Node *element, Node *node, uint code)
{
    Node* rpt = (element ? element : node);
    ctmbstr fmt = tidyLocalizedString(code);
    char nodedesc[256] = { 0 };
    char elemdesc[256] = { 0 };

    assert( fmt != NULL );

    TagToString(node, nodedesc, sizeof(nodedesc));

    switch (code)
    {
    case NESTED_QUOTATION:
        messageNode(doc, TidyWarning, code, rpt, "%s", fmt);
        break;

    case OBSOLETE_ELEMENT:
        TagToString(element, elemdesc, sizeof(elemdesc));
        messageNode(doc, TidyWarning, code, rpt, fmt, elemdesc, nodedesc);
        break;

    case NESTED_EMPHASIS:
    case REMOVED_HTML5:
    case BAD_SUMMARY_HTML5:
        messageNode(doc, TidyWarning, code, rpt, fmt, nodedesc);
        break;
    case COERCE_TO_ENDTAG_WARN:
        messageNode(doc, TidyWarning, code, rpt, fmt, node->element, node->element);
        break;
    }
}

void TY_(ReportNotice)(TidyDocImpl* doc, Node *element, Node *node, uint code)
{
    Node* rpt = ( element ? element : node );
    ctmbstr fmt = tidyLocalizedString(code);
    char nodedesc[256] = { 0 };
    char elemdesc[256] = { 0 };

    assert( fmt != NULL );

    TagToString(node, nodedesc, sizeof(nodedesc));

    switch (code)
    {
    case TRIM_EMPTY_ELEMENT:
        TagToString(element, elemdesc, sizeof(nodedesc));
        messageNode(doc, TidyWarning, code, element, fmt, elemdesc);
        break;

    case REPLACING_ELEMENT:
        TagToString(element, elemdesc, sizeof(elemdesc));
        messageNode(doc, TidyWarning, code, rpt, fmt, elemdesc, nodedesc);
        break;
    }
}

void TY_(ReportError)(TidyDocImpl* doc, Node *element, Node *node, uint code)
{
    char nodedesc[ 256 ] = {0};
    char elemdesc[ 256 ] = {0};
    Node* rpt = ( element ? element : node );
    ctmbstr fmt = tidyLocalizedString(code);
    uint versionEmitted, declared, version;
    ctmbstr extra_string = NULL;

    assert( fmt != NULL );

    TagToString(node, nodedesc, sizeof(nodedesc));

    switch ( code )
    {
    case MISSING_STARTTAG:
    case UNEXPECTED_ENDTAG:
    case TOO_MANY_ELEMENTS:
    case INSERTING_TAG:
        messageNode(doc, TidyWarning, code, node, fmt, node->element);
        break;

    case USING_BR_INPLACE_OF:
    case CANT_BE_NESTED:
    case PROPRIETARY_ELEMENT:
    case UNESCAPED_ELEMENT:
    case NOFRAMES_CONTENT:
        messageNode(doc, TidyWarning, code, node, fmt, nodedesc);
        break;

    case ELEMENT_VERS_MISMATCH_WARN:
        versionEmitted = doc->lexer->versionEmitted;
        declared = doc->lexer->doctype;
        version = versionEmitted == 0 ? declared : versionEmitted;
        extra_string = TY_(HTMLVersionNameFromCode)(version, 0);
        if (!extra_string)
            extra_string = tidyLocalizedString(STRING_HTML_PROPRIETARY);
        messageNode(doc, TidyWarning, code, node, fmt, nodedesc, extra_string);
        break;

    case ELEMENT_VERS_MISMATCH_ERROR:
        versionEmitted = doc->lexer->versionEmitted;
        declared = doc->lexer->doctype;
        version = versionEmitted == 0 ? declared : versionEmitted;
        extra_string = TY_(HTMLVersionNameFromCode)(version, 0);
        if (!extra_string)
            extra_string = tidyLocalizedString(STRING_HTML_PROPRIETARY);
        messageNode(doc, TidyError, code, node, fmt, nodedesc, extra_string);
        break;

    case MISSING_TITLE_ELEMENT:
    case INCONSISTENT_VERSION:
    case MALFORMED_DOCTYPE:
    case CONTENT_AFTER_BODY:
    case MALFORMED_COMMENT:
    case BAD_COMMENT_CHARS:
    case BAD_XML_COMMENT:
    case BAD_CDATA_CONTENT:
    case INCONSISTENT_NAMESPACE:
    case DOCTYPE_AFTER_TAGS:
    case DTYPE_NOT_UPPER_CASE:
        messageNode(doc, TidyWarning, code, rpt, "%s", fmt);
        break;

    case COERCE_TO_ENDTAG:
    case NON_MATCHING_ENDTAG:
        messageNode(doc, TidyWarning, code, rpt, fmt, node->element, node->element);
        break;

    case UNEXPECTED_ENDTAG_IN:
    case TOO_MANY_ELEMENTS_IN:
        messageNode(doc, TidyWarning, code, node, fmt, node->element, element->element);
        if (cfgBool( doc, TidyShowWarnings ))
            messageNode(doc, TidyInfo, PREVIOUS_LOCATION, node, tidyLocalizedString(PREVIOUS_LOCATION),
                        element->element);
        break;

    case ENCODING_IO_CONFLICT:
    case MISSING_DOCTYPE:
    case SPACE_PRECEDING_XMLDECL:
        messageNode(doc, TidyWarning, code, node, "%s", fmt);
        break;

    case TRIM_EMPTY_ELEMENT:
    case ILLEGAL_NESTING:
    case UNEXPECTED_END_OF_FILE:
    case ELEMENT_NOT_EMPTY:
        TagToString(element, elemdesc, sizeof(elemdesc));
        messageNode(doc, TidyWarning, code, element, fmt, elemdesc);
        break;


    case MISSING_ENDTAG_FOR:
        messageNode(doc, TidyWarning, code, rpt, fmt, element->element);
        break;

    case MISSING_ENDTAG_BEFORE:
        messageNode(doc, TidyWarning, code, rpt, fmt, element->element, nodedesc);
        break;

    case DISCARDING_UNEXPECTED:
        /* Force error if in a bad form, or 
           Issue #166 - repeated <main> element
        */
        messageNode(doc, doc->badForm ? TidyError : TidyWarning, code, node, fmt, nodedesc);
        break;

    case TAG_NOT_ALLOWED_IN:
        messageNode(doc, TidyWarning, code, node, fmt, nodedesc, element->element);
        if (cfgBool( doc, TidyShowWarnings ))
            messageNode(doc, TidyInfo, PREVIOUS_LOCATION, element,
                        tidyLocalizedString(PREVIOUS_LOCATION), element->element);
        break;

    case REPLACING_UNEX_ELEMENT:
        TagToString(element, elemdesc, sizeof(elemdesc));
        messageNode(doc, TidyWarning, code, rpt, fmt, elemdesc, nodedesc);
        break;
    case REMOVED_HTML5:
        messageNode(doc, TidyError, code, rpt, fmt, nodedesc);
        break;
    }
}

void TY_(ReportFatal)( TidyDocImpl* doc, Node *element, Node *node, uint code)
{
    char nodedesc[ 256 ] = {0};
    Node* rpt = ( element ? element : node );
    ctmbstr fmt = tidyLocalizedString(code);

    switch ( code )
    {
    case SUSPECTED_MISSING_QUOTE:
    case DUPLICATE_FRAMESET:
        messageNode(doc, TidyError, code, rpt, "%s", fmt);
        break;

    case UNKNOWN_ELEMENT:
        TagToString(node, nodedesc, sizeof(nodedesc));
        messageNode( doc, TidyError, code, node, fmt, nodedesc );
        break;

    case UNEXPECTED_ENDTAG_IN:
        messageNode(doc, TidyError, code, node, fmt, node->element, element->element);
        break;

    case UNEXPECTED_ENDTAG:  /* generated by XML docs */
        messageNode(doc, TidyError, code, node, fmt, node->element);
        break;
    }
}

void TY_(ErrorSummary)( TidyDocImpl* doc )
{
    ctmbstr encnam = tidyLocalizedString(STRING_SPECIFIED);
    int charenc = cfg( doc, TidyCharEncoding ); 
    if ( charenc == WIN1252 ) 
        encnam = "Windows-1252";
    else if ( charenc == MACROMAN )
        encnam = "MacRoman";
    else if ( charenc == IBM858 )
        encnam = "ibm858";
    else if ( charenc == LATIN0 )
        encnam = "latin0";

    /* adjust badAccess to that it is 0 if frames are ok */
    if ( doc->badAccess & (BA_USING_FRAMES | BA_USING_NOFRAMES) )
    {
        if (!((doc->badAccess & BA_USING_FRAMES) && !(doc->badAccess & BA_USING_NOFRAMES)))
            doc->badAccess &= ~(BA_USING_FRAMES | BA_USING_NOFRAMES);
    }

    if (doc->badChars)
    {
#if 0
        if ( doc->badChars & WINDOWS_CHARS )
        {
            tidy_out(doc, "%s", tidyLocalizedString(TEXT_WINDOWS_CHARS));
        }
#endif
        if (doc->badChars & BC_VENDOR_SPECIFIC_CHARS)
        {
            tidy_out(doc, tidyLocalizedString(TEXT_VENDOR_CHARS), encnam);
        }
        if ((doc->badChars & BC_INVALID_SGML_CHARS) || (doc->badChars & BC_INVALID_NCR))
        {
            tidy_out(doc, tidyLocalizedString(TEXT_SGML_CHARS), encnam);
        }
        if (doc->badChars & BC_INVALID_UTF8)
        {
            tidy_out(doc, "%s", tidyLocalizedString(TEXT_INVALID_UTF8));
        }

#if SUPPORT_UTF16_ENCODINGS

      if (doc->badChars & BC_INVALID_UTF16)
      {
          tidy_out(doc, "%s", tidyLocalizedString(TEXT_INVALID_UTF16));
      }

#endif

      if (doc->badChars & BC_INVALID_URI)
      {
          tidy_out(doc, "%s", tidyLocalizedString(TEXT_INVALID_URI));
      }
    }

    if (doc->badForm & flg_BadForm) /* Issue #166 - changed to BIT flag to support other errors */
    {
        tidy_out(doc, "%s", tidyLocalizedString(TEXT_BAD_FORM));
    }

    if (doc->badForm & flg_BadMain) /* Issue #166 - repeated <main> element */
    {
        tidy_out(doc, "%s", tidyLocalizedString(TEXT_BAD_MAIN));
    }
    
    if (doc->badAccess)
    {
        /* Tidy "classic" accessibility tests */
        if ( cfg(doc, TidyAccessibilityCheckLevel) == 0 )
        {
            if (doc->badAccess & BA_MISSING_SUMMARY)
            {
                tidy_out(doc, "%s", tidyLocalizedString(TEXT_M_SUMMARY));
            }

            if (doc->badAccess & BA_MISSING_IMAGE_ALT)
            {
                tidy_out(doc, "%s", tidyLocalizedString(TEXT_M_IMAGE_ALT));
            }

            if (doc->badAccess & BA_MISSING_IMAGE_MAP)
            {
                tidy_out(doc, "%s", tidyLocalizedString(TEXT_M_IMAGE_MAP));
            }

            if (doc->badAccess & BA_MISSING_LINK_ALT)
            {
                tidy_out(doc, "%s", tidyLocalizedString(TEXT_M_LINK_ALT));
            }

            if ((doc->badAccess & BA_USING_FRAMES) && !(doc->badAccess & BA_USING_NOFRAMES))
            {
                tidy_out(doc, "%s", tidyLocalizedString(TEXT_USING_FRAMES));
            }
        }

        tidy_out(doc, "%s", tidyLocalizedString(TEXT_ACCESS_ADVICE1));
        if ( cfg(doc, TidyAccessibilityCheckLevel) > 0 )
            tidy_out(doc, "%s", tidyLocalizedString(TEXT_ACCESS_ADVICE2));
        tidy_out(doc, ".\n" );
    }

    if (doc->badLayout)
    {
        if (doc->badLayout & USING_LAYER)
        {
            tidy_out(doc, "%s", tidyLocalizedString(TEXT_USING_LAYER));
        }

        if (doc->badLayout & USING_SPACER)
        {
            tidy_out(doc, "%s", tidyLocalizedString(TEXT_USING_SPACER));
        }

        if (doc->badLayout & USING_FONT)
        {
            tidy_out(doc, "%s", tidyLocalizedString(TEXT_USING_FONT));
        }

        if (doc->badLayout & USING_NOBR)
        {
            tidy_out(doc, "%s", tidyLocalizedString(TEXT_USING_NOBR));
        }

        if (doc->badLayout & USING_BODY)
        {
            tidy_out(doc, "%s", tidyLocalizedString(TEXT_USING_BODY));
        }
    }
}

#if 0
void TY_(UnknownOption)( TidyDocImpl* doc, char c )
{
    message( doc, TidyConfig, tidyLocalizedString(STRING_UNRECZD_OPTION), c );
}

void TY_(UnknownFile)( TidyDocImpl* doc, ctmbstr program, ctmbstr file )
{
    message( doc, TidyConfig, tidyLocalizedString(STRING_UNKNOWN_FILE), program, file );
}
#endif

void TY_(NeedsAuthorIntervention)( TidyDocImpl* doc )
{
    tidy_out(doc, "%s", tidyLocalizedString(TEXT_NEEDS_INTERVENTION));
}

void TY_(GeneralInfo)( TidyDocImpl* doc )
{
    if (!cfgBool(doc, TidyShowInfo)) return;
    tidy_out(doc, "%s", tidyLocalizedString(TEXT_GENERAL_INFO));
    tidy_out(doc, "%s", tidyLocalizedString(TEXT_GENERAL_INFO_PLEA));
}

#if SUPPORT_ACCESSIBILITY_CHECKS

void TY_(AccessibilityHelloMessage)( TidyDocImpl* doc )
{
    tidy_out(doc, "\n%s\n\n", tidyLocalizedString(STRING_HELLO_ACCESS));
}

#endif /* SUPPORT_ACCESSIBILITY_CHECKS */


void TY_(ReportMarkupVersion)( TidyDocImpl* doc )
{
    if (doc->givenDoctype)
    {
        /* todo: deal with non-ASCII characters in FPI */
        message(doc, TidyInfo, STRING_DOCTYPE_GIVEN, tidyLocalizedString(STRING_DOCTYPE_GIVEN), doc->givenDoctype);
    }

    if ( ! cfgBool(doc, TidyXmlTags) )
    {
        Bool isXhtml = doc->lexer->isvoyager;
        uint apparentVers;
        ctmbstr vers;

        apparentVers = TY_(ApparentVersion)( doc );

        vers = TY_(HTMLVersionNameFromCode)( apparentVers, isXhtml );

        if (!vers)
            vers = tidyLocalizedString(STRING_HTML_PROPRIETARY);

        message( doc, TidyInfo, STRING_CONTENT_LOOKS, tidyLocalizedString(STRING_CONTENT_LOOKS), vers );

        /* Warn about missing sytem identifier (SI) in emitted doctype */
        if ( TY_(WarnMissingSIInEmittedDocType)( doc ) )
            message( doc, TidyInfo, STRING_NO_SYSID, "%s", tidyLocalizedString(STRING_NO_SYSID) );
    }
}

void TY_(ReportNumWarnings)( TidyDocImpl* doc )
{
    if ( doc->warnings > 0 || doc->errors > 0 )
    {
        tidy_out( doc, tidyLocalizedString(STRING_ERROR_COUNT),
                  doc->warnings, tidyLocalizedStringN( STRING_ERROR_COUNT_WARNING, doc->warnings ),
                  doc->errors, tidyLocalizedStringN( STRING_ERROR_COUNT_ERROR, doc->errors ) );

        if ( doc->errors > cfg(doc, TidyShowErrors) ||
             !cfgBool(doc, TidyShowWarnings) )
            tidy_out( doc, " %s\n\n", tidyLocalizedString(STRING_NOT_ALL_SHOWN) );
        else
            tidy_out( doc, "\n\n" );
    }
    else
        tidy_out( doc, "%s\n\n", tidyLocalizedString(STRING_NO_ERRORS) );
}

/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
