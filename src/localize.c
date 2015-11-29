/* localize.c -- text strings and routines to handle errors and general messages

  (c) 1998-2008 (W3C) MIT, ERCIM, Keio University
  Portions Copyright University of Toronto
  See tidy.h and access.h for the copyright notice.

  You should only need to edit this file and tidy.c
  to localize HTML tidy. *** This needs checking ***

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


static char* LevelPrefix( TidyReportLevel level, char* buf, size_t count )
{
  *buf = 0;
  switch ( level )
  {
  case TidyInfo:
    TY_(tmbstrncpy)( buf, "Info: ", count );
    break;
  case TidyWarning:
    TY_(tmbstrncpy)( buf, "Warning: ", count );
    break;
  case TidyConfig:
    TY_(tmbstrncpy)( buf, "Config: ", count );
    break;
  case TidyAccess:
    TY_(tmbstrncpy)( buf, "Access: ", count );
    break;
  case TidyError:
    TY_(tmbstrncpy)( buf, "Error: ", count );
    break;
  case TidyBadDocument:
    TY_(tmbstrncpy)( buf, "Document: ", count );
    break;
  case TidyFatal:
    TY_(tmbstrncpy)( buf, "panic: ", count );
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

static char* ReportPosition(TidyDocImpl* doc, int line, int col, char* buf, size_t count)
{
    *buf = 0;

    /* Change formatting to be parsable by GNU Emacs */
    if ( cfgBool(doc, TidyEmacs) && cfgStr(doc, TidyEmacsFile) )
        TY_(tmbsnprintf)(buf, count, "%s:%d:%d: ", 
                         cfgStr(doc, TidyEmacsFile), line, col);
    else /* traditional format */
        TY_(tmbsnprintf)(buf, count, "line %d column %d - ", line, col);
    return buf + TY_(tmbstrlen)( buf );
}

/* General message writing routine.
** Each message is a single warning, error, etc.
** 
** This routine will keep track of counts and,
** if the caller has set a filter, it will be 
** called.  The new preferred way of handling
** Tidy diagnostics output is either a) define
** a new output sink or b) install a message
** filter routine.
*/

static void messagePos( TidyDocImpl* doc, TidyReportLevel level,
                        int line, int col, ctmbstr msg, va_list args )
#ifdef __GNUC__
__attribute__((format(printf, 5, 0)))
#endif
;
static void messagePos( TidyDocImpl* doc, TidyReportLevel level,
                        int line, int col, ctmbstr msg, va_list args )
{
    enum { sizeMessageBuf=2048 };
    char *messageBuf = TidyDocAlloc(doc,sizeMessageBuf);
    Bool go = UpdateCount( doc, level );

    if ( go )
    {
        va_list args_copy;
        va_copy(args_copy, args);
        TY_(tmbvsnprintf)(messageBuf, sizeMessageBuf, msg, args);
        if ( doc->mssgFilt )
        {
            TidyDoc tdoc = tidyImplToDoc( doc );
            go = doc->mssgFilt( tdoc, level, line, col, messageBuf );
        }
        if ( doc->mssgFilt2 )
        {
            TidyDoc tdoc = tidyImplToDoc( doc );
            go = go | doc->mssgFilt2( tdoc, level, line, col, msg, args_copy );
        }
    }

    if ( go )
    {
        enum { sizeBuf=1024 };
        char *buf = TidyDocAlloc(doc,sizeBuf);
        const char *cp;
        if ( line > 0 && col > 0 )
        {
            ReportPosition(doc, line, col, buf, sizeBuf);
#if !defined(NDEBUG) && defined(_MSC_VER)
            SPRTF("%s",buf);
#endif
            for ( cp = buf; *cp; ++cp )
                TY_(WriteChar)( *cp, doc->errout );
        }

        LevelPrefix( level, buf, sizeBuf );
#if !defined(NDEBUG) && defined(_MSC_VER)
            SPRTF("%s",buf);
            SPRTF("%s\n",messageBuf);
#else
        for ( cp = buf; *cp; ++cp )
            TY_(WriteChar)( *cp, doc->errout );

        for ( cp = messageBuf; *cp; ++cp )
            TY_(WriteChar)( *cp, doc->errout );
        TY_(WriteChar)( '\n', doc->errout );
#endif
        TidyDocFree(doc, buf);
    }
    TidyDocFree(doc, messageBuf);
}

/* Reports error at current Lexer line/column. */ 
static
void message( TidyDocImpl* doc, TidyReportLevel level, ctmbstr msg, ... )
#ifdef __GNUC__
__attribute__((format(printf, 3, 4)))
#endif
;

/* Reports error at node line/column. */ 
static
void messageNode( TidyDocImpl* doc, TidyReportLevel level,
                  Node* node, ctmbstr msg, ... )
#ifdef __GNUC__
__attribute__((format(printf, 4, 5)))
#endif
;

/* Reports error at given line/column. */ 
static
void messageLexer( TidyDocImpl* doc, TidyReportLevel level, 
                   ctmbstr msg, ... )
#ifdef __GNUC__
__attribute__((format(printf, 3, 4)))
#endif
;

/* For general reporting.  Emits nothing if --quiet yes */
static
void tidy_out( TidyDocImpl* doc, ctmbstr msg, ... )
#ifdef __GNUC__
__attribute__((format(printf, 2, 3)))
#endif
;


void message( TidyDocImpl* doc, TidyReportLevel level, ctmbstr msg, ... )
{
    va_list args;
    if (level == TidyInfo && !cfgBool(doc, TidyShowInfo)) return;
    va_start( args, msg );
    messagePos( doc, level, 0, 0, msg, args );
    va_end( args );
}


void messageLexer( TidyDocImpl* doc, TidyReportLevel level, ctmbstr msg, ... )
{
    int line = ( doc->lexer ? doc->lexer->lines : 0 );
    int col  = ( doc->lexer ? doc->lexer->columns : 0 );

    va_list args;
    va_start( args, msg );
    messagePos( doc, level, line, col, msg, args );
    va_end( args );
}

void messageNode( TidyDocImpl* doc, TidyReportLevel level, Node* node,
                  ctmbstr msg, ... )
{
    int line = ( node ? node->line :
                 ( doc->lexer ? doc->lexer->lines : 0 ) );
    int col  = ( node ? node->column :
                 ( doc->lexer ? doc->lexer->columns : 0 ) );

    va_list args;
    va_start( args, msg );
    messagePos( doc, level, line, col, msg, args );
    va_end( args );
}

void tidy_out( TidyDocImpl* doc, ctmbstr msg, ... )
{
    if ( !cfgBool(doc, TidyQuiet) )
    {
        ctmbstr cp;
        enum { sizeBuf=2048 };
        char *buf = (char *)TidyDocAlloc(doc,sizeBuf);

        va_list args;
        va_start( args, msg );
        TY_(tmbvsnprintf)(buf, sizeBuf, msg, args);
        va_end( args );

#if !defined(NDEBUG) && defined(_MSC_VER)
        add_std_out(0);
#endif
        for ( cp=buf; *cp; ++cp )
          TY_(WriteChar)( *cp, doc->errout );
#if !defined(NDEBUG) && defined(_MSC_VER)
        add_std_out(1);
#endif
        TidyDocFree(doc, buf);
    }
}

void TY_(FileError)( TidyDocImpl* doc, ctmbstr file, TidyReportLevel level )
{
    message( doc, level, "Can't open \"%s\"\n", file );
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
            TY_(tmbsnprintf)(buf, count, "plain text");
        else if (tag->type == XmlDecl)
            TY_(tmbsnprintf)(buf, count, "XML declaration");
        else if (tag->element)
            TY_(tmbsnprintf)(buf, count, "%s", tag->element);
    }
    return buf + TY_(tmbstrlen)(buf);
}

/* lexer is not defined when this is called */
void TY_(ReportUnknownOption)( TidyDocImpl* doc, ctmbstr option )
{
    assert( option != NULL );
    message( doc, TidyConfig, "unknown option: %s", option );
}

/* lexer is not defined when this is called */
void TY_(ReportBadArgument)( TidyDocImpl* doc, ctmbstr option )
{
    assert( option != NULL );
    message( doc, TidyConfig,
             "missing or malformed argument for option: %s", option );
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
        messageLexer(doc, TidyWarning, tidyLocalizedString(code),
                     TY_(CharEncodingName)(doc->docIn->encoding),
                     TY_(CharEncodingName)(encoding));
        doc->badChars |= BC_ENCODING_MISMATCH;
        break;
    }
}

void TY_(ReportEncodingError)(TidyDocImpl* doc, uint code, uint c, Bool discarded)
{
    char buf[ 32 ] = {'\0'};

    ctmbstr action = discarded ? "discarding" : "replacing";
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
        messageLexer( doc, TidyWarning, fmt, action, buf );
}

void TY_(ReportEntityError)( TidyDocImpl* doc, uint code, ctmbstr entity,
                             int ARG_UNUSED(c) )
{
    ctmbstr fmt;
    ctmbstr entityname = ( entity ? entity : "NULL" );

    fmt = tidyLocalizedString(code);

    if (fmt)
        messageLexer( doc, TidyWarning, fmt, entityname );
}

void TY_(ReportAttrError)(TidyDocImpl* doc, Node *node, AttVal *av, uint code)
{
    char const *name = "NULL", *value = "NULL";
    char tagdesc[64];
    ctmbstr fmt = tidyLocalizedString(code);

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
        messageNode(doc, TidyWarning, node, fmt, tagdesc, name);
        break;

    case BAD_ATTRIBUTE_VALUE:
    case BAD_ATTRIBUTE_VALUE_REPLACED:
    case INVALID_ATTRIBUTE:
    case INSERTING_AUTO_ATTRIBUTE:
        messageNode(doc, TidyWarning, node, fmt, tagdesc, name, value);
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
        messageNode(doc, TidyWarning, node, fmt, tagdesc);
        break;

    case XML_ID_SYNTAX:
    case PROPRIETARY_ATTR_VALUE:
    case ANCHOR_NOT_UNIQUE:
    case ATTR_VALUE_NOT_LCASE:
        messageNode(doc, TidyWarning, node, fmt, tagdesc, value);
        break;


    case MISSING_IMAGEMAP:
        messageNode(doc, TidyWarning, node, fmt, tagdesc);
        doc->badAccess |= BA_MISSING_IMAGE_MAP;
        break;

    case REPEATED_ATTRIBUTE:
        messageNode(doc, TidyWarning, node, fmt, tagdesc, value, name);
        break;

    case UNEXPECTED_END_OF_FILE_ATTR:
        /* on end of file adjust reported position to end of input */
        doc->lexer->lines   = doc->docIn->curline;
        doc->lexer->columns = doc->docIn->curcol;
        messageLexer(doc, TidyWarning, fmt, tagdesc);
        break;
    }
}

void TY_(ReportMissingAttr)( TidyDocImpl* doc, Node* node, ctmbstr name )
{
    char tagdesc[ 64 ];
    ctmbstr fmt = tidyLocalizedString(MISSING_ATTRIBUTE);

    assert( fmt != NULL );
    TagToString(node, tagdesc, sizeof(tagdesc));
    messageNode( doc, TidyWarning, node, fmt, tagdesc, name );
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
    tidy_out(doc, " \n");
    tidy_out(doc, "      - First, search left from the cell's position to find row header cells.\n");
    tidy_out(doc, "      - Then search upwards to find column header cells.\n");
    tidy_out(doc, "      - The search in a given direction stops when the edge of the table is\n");
    tidy_out(doc, "        reached or when a data cell is found after a header cell.\n"); 
    tidy_out(doc, "      - Row headers are inserted into the list in the order they appear in\n");
    tidy_out(doc, "        the table. \n");
    tidy_out(doc, "      - For left-to-right tables, headers are inserted from left to right.\n");
    tidy_out(doc, "      - Column headers are inserted after row headers, in \n");
    tidy_out(doc, "        the order they appear in the table, from top to bottom. \n");
    tidy_out(doc, "      - If a header cell has the headers attribute set, then the headers \n");
    tidy_out(doc, "        referenced by this attribute are inserted into the list and the \n");
    tidy_out(doc, "        search stops for the current direction.\n");
    tidy_out(doc, "        TD cells that set the axis attribute are also treated as header cells.\n");
    tidy_out(doc, " \n");
}

void TY_(ReportAccessWarning)( TidyDocImpl* doc, Node* node, uint code )
{
    ctmbstr fmt = tidyLocalizedString(code);
    doc->badAccess |= BA_WAI;
    messageNode( doc, TidyAccess, node, "%s", fmt );
}

void TY_(ReportAccessError)( TidyDocImpl* doc, Node* node, uint code )
{
    ctmbstr fmt = tidyLocalizedString(code);
    doc->badAccess |= BA_WAI;
    messageNode( doc, TidyAccess, node, "%s", fmt );
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
        messageNode(doc, TidyWarning, rpt, "%s", fmt);
        break;

    case OBSOLETE_ELEMENT:
        TagToString(element, elemdesc, sizeof(elemdesc));
        messageNode(doc, TidyWarning, rpt, fmt, elemdesc, nodedesc);
        break;

    case NESTED_EMPHASIS:
    case REMOVED_HTML5:
    case BAD_BODY_HTML5:
    case BAD_ALIGN_HTML5:
    case BAD_SUMMARY_HTML5:
        messageNode(doc, TidyWarning, rpt, fmt, nodedesc);
        break;
    case COERCE_TO_ENDTAG_WARN:
        messageNode(doc, TidyWarning, rpt, fmt, node->element, node->element);
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
        messageNode(doc, TidyWarning, element, fmt, elemdesc);
        break;

    case REPLACING_ELEMENT:
        TagToString(element, elemdesc, sizeof(elemdesc));
        messageNode(doc, TidyWarning, rpt, fmt, elemdesc, nodedesc);
        break;
    }
}

void TY_(ReportError)(TidyDocImpl* doc, Node *element, Node *node, uint code)
{
    char nodedesc[ 256 ] = {0};
    char elemdesc[ 256 ] = {0};
    Node* rpt = ( element ? element : node );
    ctmbstr fmt = tidyLocalizedString(code);

    assert( fmt != NULL );

    TagToString(node, nodedesc, sizeof(nodedesc));

    switch ( code )
    {
    case MISSING_STARTTAG:
    case UNEXPECTED_ENDTAG:
    case TOO_MANY_ELEMENTS:
    case INSERTING_TAG:
        messageNode(doc, TidyWarning, node, fmt, node->element);
        break;

    case USING_BR_INPLACE_OF:
    case CANT_BE_NESTED:
    case PROPRIETARY_ELEMENT:
    case UNESCAPED_ELEMENT:
    case NOFRAMES_CONTENT:
        messageNode(doc, TidyWarning, node, fmt, nodedesc);
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
        messageNode(doc, TidyWarning, rpt, "%s", fmt);
        break;

    case COERCE_TO_ENDTAG:
    case NON_MATCHING_ENDTAG:
        messageNode(doc, TidyWarning, rpt, fmt, node->element, node->element);
        break;

    case UNEXPECTED_ENDTAG_IN:
    case TOO_MANY_ELEMENTS_IN:
        messageNode(doc, TidyWarning, node, fmt, node->element, element->element);
        if (cfgBool( doc, TidyShowWarnings ))
            messageNode(doc, TidyInfo, node, tidyLocalizedString(PREVIOUS_LOCATION),
                        element->element);
        break;

    case ENCODING_IO_CONFLICT:
    case MISSING_DOCTYPE:
    case SPACE_PRECEDING_XMLDECL:
        messageNode(doc, TidyWarning, node, "%s", fmt);
        break;

    case TRIM_EMPTY_ELEMENT:
    case ILLEGAL_NESTING:
    case UNEXPECTED_END_OF_FILE:
    case ELEMENT_NOT_EMPTY:
        TagToString(element, elemdesc, sizeof(elemdesc));
        messageNode(doc, TidyWarning, element, fmt, elemdesc);
        break;


    case MISSING_ENDTAG_FOR:
        messageNode(doc, TidyWarning, rpt, fmt, element->element);
        break;

    case MISSING_ENDTAG_BEFORE:
        messageNode(doc, TidyWarning, rpt, fmt, element->element, nodedesc);
        break;

    case DISCARDING_UNEXPECTED:
        /* Force error if in a bad form, or 
           Issue #166 - repeated <main> element
        */
        messageNode(doc, doc->badForm ? TidyError : TidyWarning, node, fmt, nodedesc);
        break;

    case TAG_NOT_ALLOWED_IN:
        messageNode(doc, TidyWarning, node, fmt, nodedesc, element->element);
        if (cfgBool( doc, TidyShowWarnings ))
            messageNode(doc, TidyInfo, element,
                        tidyLocalizedString(PREVIOUS_LOCATION), element->element);
        break;

    case REPLACING_UNEX_ELEMENT:
        TagToString(element, elemdesc, sizeof(elemdesc));
        messageNode(doc, TidyWarning, rpt, fmt, elemdesc, nodedesc);
        break;
    case REMOVED_HTML5:
        messageNode(doc, TidyError, rpt, fmt, nodedesc);
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
        messageNode(doc, TidyError, rpt, "%s", fmt);
        break;

    case UNKNOWN_ELEMENT:
        TagToString(node, nodedesc, sizeof(nodedesc));
        messageNode( doc, TidyError, node, fmt, nodedesc );
        break;

    case UNEXPECTED_ENDTAG_IN:
        messageNode(doc, TidyError, node, fmt, node->element, element->element);
        break;

    case UNEXPECTED_ENDTAG:  /* generated by XML docs */
        messageNode(doc, TidyError, node, fmt, node->element);
        break;
    }
}

void TY_(ErrorSummary)( TidyDocImpl* doc )
{
    ctmbstr encnam = "specified";
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
            tidy_out(doc, "Characters codes for the Microsoft Windows fonts in the range\n");
            tidy_out(doc, "128 - 159 may not be recognized on other platforms. You are\n");
            tidy_out(doc, "instead recommended to use named entities, e.g. &trade; rather\n");
            tidy_out(doc, "than Windows character code 153 (0x2122 in Unicode). Note that\n");
            tidy_out(doc, "as of February 1998 few browsers support the new entities.\n\n");
        }
#endif
        if (doc->badChars & BC_VENDOR_SPECIFIC_CHARS)
        {

            tidy_out(doc, "It is unlikely that vendor-specific, system-dependent encodings\n");
            tidy_out(doc, "work widely enough on the World Wide Web; you should avoid using the \n");
            tidy_out(doc, "%s", encnam );
            tidy_out(doc, " character encoding, instead you are recommended to\n" );
            tidy_out(doc, "use named entities, e.g. &trade;.\n\n");
        }
        if ((doc->badChars & BC_INVALID_SGML_CHARS) || (doc->badChars & BC_INVALID_NCR))
        {
            tidy_out(doc, "Character codes 128 to 159 (U+0080 to U+009F) are not allowed in HTML;\n");
            tidy_out(doc, "even if they were, they would likely be unprintable control characters.\n");
            tidy_out(doc, "Tidy assumed you wanted to refer to a character with the same byte value in the \n");
            tidy_out(doc, "%s", encnam );
            tidy_out(doc, " encoding and replaced that reference with the Unicode equivalent.\n\n" );
        }
        if (doc->badChars & BC_INVALID_UTF8)
        {
            tidy_out(doc, "Character codes for UTF-8 must be in the range: U+0000 to U+10FFFF.\n");
            tidy_out(doc, "The definition of UTF-8 in Annex D of ISO/IEC 10646-1:2000 also\n");
            tidy_out(doc, "allows for the use of five- and six-byte sequences to encode\n");
            tidy_out(doc, "characters that are outside the range of the Unicode character set;\n");
            tidy_out(doc, "those five- and six-byte sequences are illegal for the use of\n");
            tidy_out(doc, "UTF-8 as a transformation of Unicode characters. ISO/IEC 10646\n");
            tidy_out(doc, "does not allow mapping of unpaired surrogates, nor U+FFFE and U+FFFF\n");
            tidy_out(doc, "(but it does allow other noncharacters). For more information please refer to\n");
            tidy_out(doc, "http://www.unicode.org/ and http://www.cl.cam.ac.uk/~mgk25/unicode.html\n\n");
        }

#if SUPPORT_UTF16_ENCODINGS

      if (doc->badChars & BC_INVALID_UTF16)
      {
        tidy_out(doc, "Character codes for UTF-16 must be in the range: U+0000 to U+10FFFF.\n");
        tidy_out(doc, "The definition of UTF-16 in Annex C of ISO/IEC 10646-1:2000 does not allow the\n");
        tidy_out(doc, "mapping of unpaired surrogates. For more information please refer to\n");
        tidy_out(doc, "http://www.unicode.org/ and http://www.cl.cam.ac.uk/~mgk25/unicode.html\n\n");
      }

#endif

      if (doc->badChars & BC_INVALID_URI)
      {
        tidy_out(doc, "URIs must be properly escaped, they must not contain unescaped\n");
        tidy_out(doc, "characters below U+0021 including the space character and not\n");
        tidy_out(doc, "above U+007E. Tidy escapes the URI for you as recommended by\n");
        tidy_out(doc, "HTML 4.01 section B.2.1 and XML 1.0 section 4.2.2. Some user agents\n");
        tidy_out(doc, "use another algorithm to escape such URIs and some server-sided\n");
        tidy_out(doc, "scripts depend on that. If you want to depend on that, you must\n");
        tidy_out(doc, "escape the URI by your own. For more information please refer to\n");
        tidy_out(doc, "http://www.w3.org/International/O-URL-and-ident.html\n\n");
      }
    }

    if (doc->badForm & flg_BadForm) /* Issue #166 - changed to BIT flag to support other errors */
    {
        tidy_out(doc, "You may need to move one or both of the <form> and </form>\n");
        tidy_out(doc, "tags. HTML elements should be properly nested and form elements\n");
        tidy_out(doc, "are no exception. For instance you should not place the <form>\n");
        tidy_out(doc, "in one table cell and the </form> in another. If the <form> is\n");
        tidy_out(doc, "placed before a table, the </form> cannot be placed inside the\n");
        tidy_out(doc, "table! Note that one form can't be nested inside another!\n\n");
    }

    if (doc->badForm & flg_BadMain) /* Issue #166 - repeated <main> element */
    {
        tidy_out(doc, "Only one <main> element is allowed in a document.\n");
        tidy_out(doc, "Subsequent <main> elements have been discarded, which may\n");
        tidy_out(doc, "render the document invalid.\n");
    }
    
    if (doc->badAccess)
    {
        /* Tidy "classic" accessibility tests */
        if ( cfg(doc, TidyAccessibilityCheckLevel) == 0 )
        {
            if (doc->badAccess & BA_MISSING_SUMMARY)
            {
                tidy_out(doc, "The table summary attribute should be used to describe\n");
                tidy_out(doc, "the table structure. It is very helpful for people using\n");
                tidy_out(doc, "non-visual browsers. The scope and headers attributes for\n");
                tidy_out(doc, "table cells are useful for specifying which headers apply\n");
                tidy_out(doc, "to each table cell, enabling non-visual browsers to provide\n");
                tidy_out(doc, "a meaningful context for each cell.\n\n");
            }

            if (doc->badAccess & BA_MISSING_IMAGE_ALT)
            {
                tidy_out(doc, "The alt attribute should be used to give a short description\n");
                tidy_out(doc, "of an image; longer descriptions should be given with the\n");
                tidy_out(doc, "longdesc attribute which takes a URL linked to the description.\n");
                tidy_out(doc, "These measures are needed for people using non-graphical browsers.\n\n");
            }

            if (doc->badAccess & BA_MISSING_IMAGE_MAP)
            {
                tidy_out(doc, "Use client-side image maps in preference to server-side image\n");
                tidy_out(doc, "maps as the latter are inaccessible to people using non-\n");
                tidy_out(doc, "graphical browsers. In addition, client-side maps are easier\n");
                tidy_out(doc, "to set up and provide immediate feedback to users.\n\n");
            }

            if (doc->badAccess & BA_MISSING_LINK_ALT)
            {
                tidy_out(doc, "For hypertext links defined using a client-side image map, you\n");
                tidy_out(doc, "need to use the alt attribute to provide a textual description\n");
                tidy_out(doc, "of the link for people using non-graphical browsers.\n\n");
            }

            if ((doc->badAccess & BA_USING_FRAMES) && !(doc->badAccess & BA_USING_NOFRAMES))
            {
                tidy_out(doc, "Pages designed using frames presents problems for\n");
                tidy_out(doc, "people who are either blind or using a browser that\n");
                tidy_out(doc, "doesn't support frames. A frames-based page should always\n");
                tidy_out(doc, "include an alternative layout inside a NOFRAMES element.\n\n");
            }

        }

        tidy_out(doc, "For further advice on how to make your pages accessible\n");
        tidy_out(doc, "see %s", tidyLocalizedString( ACCESS_URL ) );
        if ( cfg(doc, TidyAccessibilityCheckLevel) > 0 )
            tidy_out(doc, " and %s", tidyLocalizedString( ATRC_ACCESS_URL ) );
        tidy_out(doc, ".\n" );
    }

    if (doc->badLayout)
    {
        if (doc->badLayout & USING_LAYER)
        {
            tidy_out(doc, "The Cascading Style Sheets (CSS) Positioning mechanism\n");
            tidy_out(doc, "is recommended in preference to the proprietary <LAYER>\n");
            tidy_out(doc, "element due to limited vendor support for LAYER.\n\n");
        }

        if (doc->badLayout & USING_SPACER)
        {
            tidy_out(doc, "You are recommended to use CSS for controlling white\n");
            tidy_out(doc, "space (e.g. for indentation, margins and line spacing).\n");
            tidy_out(doc, "The proprietary <SPACER> element has limited vendor support.\n\n");
        }

        if (doc->badLayout & USING_FONT)
        {
            tidy_out(doc, "You are recommended to use CSS to specify the font and\n");
            tidy_out(doc, "properties such as its size and color. This will reduce\n");
            tidy_out(doc, "the size of HTML files and make them easier to maintain\n");
            tidy_out(doc, "compared with using <FONT> elements.\n\n");
        }

        if (doc->badLayout & USING_NOBR)
        {
            tidy_out(doc, "You are recommended to use CSS to control line wrapping.\n");
            tidy_out(doc, "Use \"white-space: nowrap\" to inhibit wrapping in place\n");
            tidy_out(doc, "of inserting <NOBR>...</NOBR> into the markup.\n\n");
        }

        if (doc->badLayout & USING_BODY)
        {
            tidy_out(doc, "You are recommended to use CSS to specify page and link colors\n");
        }
    }
}

#if 0
void TY_(UnknownOption)( TidyDocImpl* doc, char c )
{
    message( doc, TidyConfig,
             "unrecognized option -%c use -help to list options\n", c );
}

void TY_(UnknownFile)( TidyDocImpl* doc, ctmbstr program, ctmbstr file )
{
    message( doc, TidyConfig, 
             "%s: can't open file \"%s\"\n", program, file );
}
#endif

void TY_(NeedsAuthorIntervention)( TidyDocImpl* doc )
{
    tidy_out(doc, "This document has errors that must be fixed before\n");
    tidy_out(doc, "using HTML Tidy to generate a tidied up version.\n\n");
}

void TY_(GeneralInfo)( TidyDocImpl* doc )
{
    if (!cfgBool(doc, TidyShowInfo)) return;
    tidy_out(doc, "About HTML Tidy: https://github.com/htacg/tidy-html5\n");
    tidy_out(doc, "Bug reports and comments: https://github.com/htacg/tidy-html5/issues\n");
    tidy_out(doc, "Or send questions and comments to: https://lists.w3.org/Archives/Public/public-htacg/\n");
    tidy_out(doc, "Latest HTML specification: http://dev.w3.org/html5/spec-author-view/\n");
    tidy_out(doc, "Validate your HTML documents: http://validator.w3.org/nu/\n");
    tidy_out(doc, "Lobby your company to join the W3C: http://www.w3.org/Consortium\n");
}

#if SUPPORT_ACCESSIBILITY_CHECKS

void TY_(AccessibilityHelloMessage)( TidyDocImpl* doc )
{
    tidy_out( doc, "\n" );
    tidy_out( doc, "Accessibility Checks: Version 0.1\n" );
    tidy_out( doc, "\n" );
}

#endif /* SUPPORT_ACCESSIBILITY_CHECKS */

#if 0
void TY_(HelloMessage)( TidyDocImpl* doc, ctmbstr date, ctmbstr filename )
{
    tmbchar buf[ 2048 ];
    ctmbstr platform = "", helper = "";
    ctmbstr msgfmt = "\nHTML Tidy for %s (vers %s; built on %s, at %s)\n"
                  "Parsing \"%s\"\n";

#ifdef PLATFORM_NAME
    platform = PLATFORM_NAME;
    helper = " for ";
#endif
    
    if ( TY_(tmbstrcmp)(filename, "stdin") == 0 )
    {
        /* Filename will be ignored at end of varargs */
        msgfmt = "\nHTML Tidy for %s (vers %s; built on %s, at %s)\n"
                 "Parsing console input (stdin)\n";
    }
    
    TY_(tmbsnprintf)(buf, sizeof(buf), msgfmt, helper, platform, 
                     date, __DATE__, __TIME__, filename);
    tidy_out( doc, buf );
}
#endif

void TY_(ReportMarkupVersion)( TidyDocImpl* doc )
{
    if (doc->givenDoctype)
    {
        /* todo: deal with non-ASCII characters in FPI */
        message(doc, TidyInfo, "Doctype given is \"%s\"", doc->givenDoctype);
    }

    if ( ! cfgBool(doc, TidyXmlTags) )
    {
        Bool isXhtml = doc->lexer->isvoyager;
        uint apparentVers;
        ctmbstr vers;

        apparentVers = TY_(ApparentVersion)( doc );

        vers = TY_(HTMLVersionNameFromCode)( apparentVers, isXhtml );

        if (!vers)
            vers = "HTML Proprietary";

        message( doc, TidyInfo, "Document content looks like %s", vers );

        /* Warn about missing sytem identifier (SI) in emitted doctype */
        if ( TY_(WarnMissingSIInEmittedDocType)( doc ) )
            message( doc, TidyInfo, "No system identifier in emitted doctype" );
    }
}

void TY_(ReportNumWarnings)( TidyDocImpl* doc )
{
    if ( doc->warnings > 0 || doc->errors > 0 )
    {
        tidy_out( doc, "%u %s, %u %s were found!",
                  doc->warnings, doc->warnings == 1 ? "warning" : "warnings",
                  doc->errors, doc->errors == 1 ? "error" : "errors" );

        if ( doc->errors > cfg(doc, TidyShowErrors) ||
             !cfgBool(doc, TidyShowWarnings) )
            tidy_out( doc, " Not all warnings/errors were shown.\n\n" );
        else
            tidy_out( doc, "\n\n" );
    }
    else
        tidy_out( doc, "No warnings or errors were found.\n\n" );
}

/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
