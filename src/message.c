/* message.c -- General Message Writing Routines

  (c) 1998-2017 (W3C) MIT, ERCIM, Keio University, University of
  Toronto, HTACG
  See tidy.h for the copyright notice.

*/

#include "message.h"
#include "messageobj.h"
#include "limits.h"
#include "tidy-int.h"
#include "lexer.h"
#include "streamio.h"
#include "tmbstr.h"
#include "utf8.h"
#if !defined(NDEBUG) && defined(_MSC_VER)
#include "sprtf.h"
#endif
#include "version.h"


/*********************************************************************
 * Release Information
 *********************************************************************/

ctmbstr TY_(ReleaseDate)(void)
{
  return TY_(release_date);
}


ctmbstr TY_(tidyLibraryVersion)(void)
{
  return TY_(library_version);
}


/*********************************************************************
 * General Message Utility Functions
 *********************************************************************/

/* Updates document message counts and compares counts to options to
** see if message display should go forward.
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
          /* Ack! */
          break;
      default:
          break;
  }

  return go;
}


/* Returns the given node's tag as a string. */
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


/* Convert an integer to a string. */
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


/*********************************************************************
 * Message Writing Functions
 * These funtions provide final, formatted output to the output sink.
 *********************************************************************/


/* Writes messages to the output sink unless they are suppressed by one of the
** message callback filters, or suppressed by the configuration settings.
** Report messages are messages that are included in the "error table," and
** dialogue messages are any other output that Tidy traditionally emits.
*/
static void messageOut( TidyMessageImpl *message )
{
    TidyDocImpl *doc;
    Bool go;
    static Bool prevDialog = no;

    if ( !message )
        return;

    doc = message->tidyDoc;

    /* The filter has had a chance to suppress *any* message from output. */
    go = message->allowMessage;

    /* Allow UpdateCount a chance to suppress further report messages. */
    if ( message->level <= TidyFatal )
    {
        go = go & UpdateCount( doc, message->level );
    }
    
    /* If suppressing TidyInfo/TidyDialogueInfo on Reports, suppress them. */
    if ( message->level == TidyInfo || message->level == TidyDialogueInfo )
    {
        go = go & (cfgBool(doc, TidyShowInfo) == yes);
    }

    /* If we're TidyQuiet and handling TidyDialogue, then suppress. */
    if ( cfgBool(doc, TidyQuiet) )
    {
        go = go & !(message->level > TidyFatal);
    }

    /* Output the message if applicable. */
    if ( go )
    {
        TidyOutputSink *outp = &doc->errout->sink;
        Bool isDialog = message->level > TidyFatal;
        uint columns = isDialog ? cfg( doc, TidyConsoleWidth ) : 0;
        tmbstr wrapped = TY_(tidyWrappedText)( doc, message->messageOutput, columns );
        ctmbstr cp;
        byte b = '\0';
        
        /* Always ensure there's an empty line before a dialogue message,
           unless one is already there. This avoids adding formatting to the
           strings, and keeps them here, consistently. */
        if ( isDialog && !prevDialog )
        {
            TY_(WriteChar)( '\n', doc->errout );
        }
        
        for ( cp = wrapped; *cp; ++cp )
        {
            b = (*cp & 0xff);
            if (b == (byte)'\n')
                TY_(WriteChar)( b, doc->errout );   /* for EOL translation */
            else
                outp->putByte( outp->sinkData, b ); /* #383 - no encoding */
        }
        TidyDocFree( doc, wrapped );
        
        /* Always add a trailing newline after dialogue messages. */
        if ( isDialog )
        {
            TY_(WriteChar)( '\n', doc->errout );
            prevDialog = yes;
        }
        else
        {
            prevDialog = no;
        }
        
    }

    TY_(tidyMessageRelease)(message);
}


/*********************************************************************
 * High Level Message Writing Functions - General
 * When adding new reports to LibTidy, preference should be given
 * to one of these existing, general purpose message writing
 * functions, if at all possible.
 *********************************************************************/


void TY_(ReportNotice)(TidyDocImpl* doc, Node *element, Node *node, uint code)
{
    TidyMessageImpl *message = NULL;
    Node* rpt = ( element ? element : node );
    char nodedesc[256] = { 0 };
    char elemdesc[256] = { 0 };
    ctmbstr tagtype;
    
    TagToString(node, nodedesc, sizeof(nodedesc));

    switch (code)
    {
        case TRIM_EMPTY_ELEMENT:
            TagToString(element, elemdesc, sizeof(nodedesc));
            message = TY_(tidyMessageCreateWithNode)(doc, element, code, TidyWarning, elemdesc );
            break;

        case REPLACING_ELEMENT:
            TagToString(element, elemdesc, sizeof(elemdesc));
            message = TY_(tidyMessageCreateWithNode)(doc, rpt, code, TidyWarning, elemdesc, nodedesc );
            break;

        case CUSTOM_TAG_DETECTED:
            TagToString(element, elemdesc, sizeof(elemdesc));
            
            switch ( cfg( doc, TidyUseCustomTags ) )
            {
                case TidyCustomBlocklevel:
                    tagtype = tidyLocalizedString( TIDYCUSTOMBLOCKLEVEL_STRING );
                    break;
                case TidyCustomEmpty:
                    tagtype = tidyLocalizedString( TIDYCUSTOMEMPTY_STRING );
                    break;
                case TidyCustomInline:
                    tagtype = tidyLocalizedString( TIDYCUSTOMINLINE_STRING );
                    break;
                case TidyCustomPre:
                    tagtype = tidyLocalizedString( TIDYCUSTOMPRE_STRING );
                    break;
            }
            message = TY_(tidyMessageCreateWithNode)(doc, element, code, TidyInfo, elemdesc, tagtype );
            break;
    }

    messageOut( message );
}


void TY_(ReportWarning)(TidyDocImpl* doc, Node *element, Node *node, uint code)
{
    TidyMessageImpl *message = NULL;
    Node* rpt = (element ? element : node);
    char nodedesc[256] = { 0 };
    char elemdesc[256] = { 0 };

    TagToString(node, nodedesc, sizeof(nodedesc));

    switch (code)
    {
        case NESTED_QUOTATION:
            message = TY_(tidyMessageCreateWithNode)(doc, rpt, code, TidyWarning );
            break;

        case OBSOLETE_ELEMENT:
            TagToString(element, elemdesc, sizeof(elemdesc));
            message = TY_(tidyMessageCreateWithNode)(doc, rpt, code, TidyWarning, elemdesc, nodedesc );
            break;

        case NESTED_EMPHASIS:
        case REMOVED_HTML5:
        case BAD_SUMMARY_HTML5:
            message = TY_(tidyMessageCreateWithNode)(doc, rpt, code, TidyWarning, nodedesc );
            break;
        case COERCE_TO_ENDTAG_WARN:
            message = TY_(tidyMessageCreateWithNode)(doc, rpt, code, TidyWarning, node->element, node->element );
            break;
        case XML_DECLARATION_DETECTED:
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning );
            break;
    }

    messageOut( message );
}


void TY_(ReportError)(TidyDocImpl* doc, Node *element, Node *node, uint code)
{
    TidyMessageImpl *message = NULL;
    TidyMessageImpl *message2 = NULL; /* extra, when TidyShowWarnings */
    char nodedesc[ 256 ] = {0};
    char elemdesc[ 256 ] = {0};
    Node* rpt = ( element ? element : node );
    uint versionEmitted, declared, version;
    ctmbstr extra_string = NULL;

    TagToString(node, nodedesc, sizeof(nodedesc));

    switch ( code )
    {
        case MISSING_STARTTAG:
        case UNEXPECTED_ENDTAG:
        case TOO_MANY_ELEMENTS:
        case INSERTING_TAG:
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning, node->element );
            break;

        case USING_BR_INPLACE_OF:
        case CANT_BE_NESTED:
        case PROPRIETARY_ELEMENT:
        case UNESCAPED_ELEMENT:
        case NOFRAMES_CONTENT:
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning, nodedesc );
            break;

        case ELEMENT_VERS_MISMATCH_WARN:
            versionEmitted = doc->lexer->versionEmitted;
            declared = doc->lexer->doctype;
            version = versionEmitted == 0 ? declared : versionEmitted;
            extra_string = TY_(HTMLVersionNameFromCode)(version, 0);
            if (!extra_string)
                extra_string = tidyLocalizedString(STRING_HTML_PROPRIETARY);
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning, nodedesc, extra_string );
            break;

        case ELEMENT_VERS_MISMATCH_ERROR:
            versionEmitted = doc->lexer->versionEmitted;
            declared = doc->lexer->doctype;
            version = versionEmitted == 0 ? declared : versionEmitted;
            extra_string = TY_(HTMLVersionNameFromCode)(version, 0);
            if (!extra_string)
                extra_string = tidyLocalizedString(STRING_HTML_PROPRIETARY);
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyError, nodedesc, extra_string );
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
            message = TY_(tidyMessageCreateWithNode)(doc, rpt, code, TidyWarning );
            break;

        case COERCE_TO_ENDTAG:
        case NON_MATCHING_ENDTAG:
            message = TY_(tidyMessageCreateWithNode)(doc, rpt, code, TidyWarning, node->element, node->element );
            break;

        case UNEXPECTED_ENDTAG_IN:
        case TOO_MANY_ELEMENTS_IN:
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning, node->element, node->element );
            message2 = TY_(tidyMessageCreateWithNode)(doc, node, PREVIOUS_LOCATION, TidyInfo, element->element );
            break;

        case ENCODING_IO_CONFLICT:
        case MISSING_DOCTYPE:
        case SPACE_PRECEDING_XMLDECL:
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning );
            break;

        case TRIM_EMPTY_ELEMENT:
        case ILLEGAL_NESTING:
        case UNEXPECTED_END_OF_FILE:
        case ELEMENT_NOT_EMPTY:
            TagToString(element, elemdesc, sizeof(elemdesc));
            message = TY_(tidyMessageCreateWithNode)(doc, element, code, TidyWarning, elemdesc );
            break;


        case MISSING_ENDTAG_FOR:
            message = TY_(tidyMessageCreateWithNode)(doc, rpt, code, TidyWarning, element->element );
            break;

        case MISSING_ENDTAG_BEFORE:
            message = TY_(tidyMessageCreateWithNode)(doc, rpt, code, TidyWarning, element->element, nodedesc );
            break;

        case DISCARDING_UNEXPECTED:
            /* Force error if in a bad form, or
             Issue #166 - repeated <main> element
             */
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, doc->badForm ? TidyError : TidyWarning, nodedesc );
            break;

        case TAG_NOT_ALLOWED_IN:
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning, nodedesc, element->element );
            message2 = TY_(tidyMessageCreateWithNode)(doc, element, PREVIOUS_LOCATION, TidyInfo, element->element );
            break;
            
        case REPLACING_UNEX_ELEMENT:
            TagToString(element, elemdesc, sizeof(elemdesc));
            message = TY_(tidyMessageCreateWithNode)(doc, rpt, code, TidyWarning, elemdesc, nodedesc );
            break;
        case REMOVED_HTML5:
            message = TY_(tidyMessageCreateWithNode)(doc, rpt, code, TidyError, nodedesc );
            break;
    }

    messageOut( message );

    /* Although the callback is always executed for message2, it's only
       added to the output sink TidyShowWarnings is enabled. */
    if (cfgBool( doc, TidyShowWarnings ))
        messageOut( message2 );
}


void TY_(ReportFatal)( TidyDocImpl* doc, Node *element, Node *node, uint code)
{
    TidyMessageImpl *message = NULL;
    char nodedesc[ 256 ] = {0};
    Node* rpt = ( element ? element : node );

    switch ( code )
    {
        case SUSPECTED_MISSING_QUOTE:
        case DUPLICATE_FRAMESET:
            message = TY_(tidyMessageCreateWithNode)(doc, rpt, code, TidyError );
            break;

        case UNKNOWN_ELEMENT:
        case UNKNOWN_ELEMENT_LOOKS_CUSTOM:
            TagToString(node, nodedesc, sizeof(nodedesc));
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyError, nodedesc );
            break;

        case UNEXPECTED_ENDTAG_IN:
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyError, node->element, element->element );
            break;

        case UNEXPECTED_ENDTAG:  /* generated by XML docs */
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyError, node->element );
            break;
    }

    messageOut( message );
}


/*********************************************************************
 * High Level Message Writing Functions - Specific
 * When adding new reports to LibTidy, preference should be given
 * to one of the existing, general pupose message writing functions
 * above, if possible, otherwise try to use one of these, or as a
 * last resort add a new one in this section.
 *********************************************************************/


void TY_(FileError)( TidyDocImpl* doc, ctmbstr file, TidyReportLevel level )
{
    TidyMessageImpl *message = TY_(tidyMessageCreate)( doc, FILE_CANT_OPEN, level, file);
    messageOut( message );
}


void TY_(ReportAttrError)(TidyDocImpl* doc, Node *node, AttVal *av, uint code)
{
    TidyMessageImpl *message = NULL;
    char const *name = "NULL", *value = "NULL";
    char tagdesc[64];
    uint version;
    ctmbstr extra_string;

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
        case MISSING_ATTR_VALUE:
        case XML_ATTRIBUTE_VALUE:
        case PROPRIETARY_ATTRIBUTE:
        case JOINING_ATTRIBUTE:
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning, tagdesc, name );
            break;

        case ATTRIBUTE_IS_NOT_ALLOWED:
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning, tagdesc, name );
            break;

        case MISMATCHED_ATTRIBUTE_WARN:
            version = doc->lexer->versionEmitted == 0 ? doc->lexer->doctype : doc->lexer->versionEmitted;
            extra_string = TY_(HTMLVersionNameFromCode)(version, 0);
            if (!extra_string)
                extra_string = tidyLocalizedString(STRING_HTML_PROPRIETARY);
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning, tagdesc, name, extra_string );
            break;

        case MISMATCHED_ATTRIBUTE_ERROR:
            version = doc->lexer->versionEmitted == 0 ? doc->lexer->doctype : doc->lexer->versionEmitted;
            extra_string = TY_(HTMLVersionNameFromCode)(version, 0);
            if (!extra_string)
                extra_string = tidyLocalizedString(STRING_HTML_PROPRIETARY);
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyError, tagdesc, name, extra_string );
            break;

        case BAD_ATTRIBUTE_VALUE:
        case BAD_ATTRIBUTE_VALUE_REPLACED:
        case INVALID_ATTRIBUTE:
        case INSERTING_AUTO_ATTRIBUTE:
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning, tagdesc, name, value );
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
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning, tagdesc );
            break;

        case XML_ID_SYNTAX:
        case PROPRIETARY_ATTR_VALUE:
        case ANCHOR_NOT_UNIQUE:
        case ATTR_VALUE_NOT_LCASE:
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning, tagdesc, value );
            break;


        case MISSING_IMAGEMAP:
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning, tagdesc );
            doc->badAccess |= BA_MISSING_IMAGE_MAP; /* @todo: why is this here instead of calling function? */
            break;

        case REPEATED_ATTRIBUTE:
            message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyWarning, tagdesc, value, name );
            break;
            
        case UNEXPECTED_END_OF_FILE_ATTR:
            /* on end of file adjust reported position to end of input */
            doc->lexer->lines   = doc->docIn->curline;
            doc->lexer->columns = doc->docIn->curcol;
            message = TY_(tidyMessageCreateWithLexer)(doc, code, TidyWarning, tagdesc );
            break;
    }

    messageOut( message );
}


/* lexer is not defined when this is called */
void TY_(ReportBadArgument)( TidyDocImpl* doc, ctmbstr option )
{
    assert( option != NULL );

    TidyMessageImpl *message = TY_(tidyMessageCreate)( doc, STRING_MISSING_MALFORMED, TidyConfig, option );
    messageOut( message );
}


void TY_(ReportEncodingError)(TidyDocImpl* doc, uint code, uint c, Bool discarded)
{
    TidyMessageImpl *message = NULL;
    char buf[ 32 ] = {'\0'};
    ctmbstr action = tidyLocalizedString(discarded ? STRING_DISCARDING : STRING_REPLACING);

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

    message = TY_(tidyMessageCreateWithLexer)(doc, code, TidyWarning, action, buf );
    messageOut( message );
}


void TY_(ReportEncodingWarning)(TidyDocImpl* doc, uint code, uint encoding)
{
    TidyMessageImpl *message = NULL;
    switch(code)
    {
        case ENCODING_MISMATCH:
            message = TY_(tidyMessageCreateWithLexer)(doc,
                                                      code,
                                                      TidyWarning,
                                                      TY_(CharEncodingName)(doc->docIn->encoding),
                                                      TY_(CharEncodingName)(encoding));
            doc->badChars |= BC_ENCODING_MISMATCH; /* @todo: why not in calling function? */
            break;
    }

    messageOut( message );
}


void TY_(ReportEntityError)( TidyDocImpl* doc, uint code, ctmbstr entity,
                             int ARG_UNUSED(c) )
{
    TidyMessageImpl *message = NULL;
    ctmbstr entityname = ( entity ? entity : "NULL" );

    message = TY_(tidyMessageCreateWithLexer)(doc, code, TidyWarning, entityname);
    messageOut( message );
}


void TY_(ReportMarkupVersion)( TidyDocImpl* doc )
{
    TidyMessageImpl *message = NULL;
    
    if ( doc->givenDoctype )
    {
        /* @todo: deal with non-ASCII characters in FPI */
        message = TY_(tidyMessageCreate)( doc, STRING_DOCTYPE_GIVEN, TidyInfo, doc->givenDoctype );
        messageOut(message);
    }
    
    if ( ! cfgBool(doc, TidyXmlTags) )
    {
        Bool isXhtml = doc->lexer->isvoyager;
        uint apparentVers;
        ctmbstr vers;
        
        apparentVers = TY_(ApparentVersion)( doc );
        
        vers = TY_(HTMLVersionNameFromCode)( apparentVers, isXhtml );
        
        if ( !vers )
        {
            vers = tidyLocalizedString(STRING_HTML_PROPRIETARY);
        }
        
        message = TY_(tidyMessageCreate)( doc, STRING_CONTENT_LOOKS, TidyInfo, vers );
        messageOut(message);
        
        /* Warn about missing sytem identifier (SI) in emitted doctype */
        if ( TY_(WarnMissingSIInEmittedDocType)( doc ) )
        {
            message = TY_(tidyMessageCreate)( doc, STRING_NO_SYSID, TidyInfo);
            messageOut(message);
        }
    }
}


void TY_(ReportMissingAttr)( TidyDocImpl* doc, Node* node, ctmbstr name )
{
    TidyMessageImpl *message = NULL;
    char tagdesc[ 64 ];

    TagToString(node, tagdesc, sizeof(tagdesc));
    message = TY_(tidyMessageCreateWithNode)(doc, node, MISSING_ATTRIBUTE, TidyWarning, tagdesc, name );
    messageOut(message);
}


void TY_(ReportSurrogateError)(TidyDocImpl* doc, uint code, uint c1, uint c2)
{
    TidyMessageImpl *message = NULL;
    message = TY_(tidyMessageCreateWithLexer)(doc, code, TidyWarning, c1, c2);
    messageOut(message);
}


/* lexer is not defined when this is called */
void TY_(ReportUnknownOption)( TidyDocImpl* doc, ctmbstr option )
{
    TidyMessageImpl *message = NULL;
    assert( option != NULL );
    message = TY_(tidyMessageCreateWithLexer)(doc, STRING_UNKNOWN_OPTION, TidyConfig, option);
    messageOut(message);
}


/*********************************************************************
 * Output Dialogue Information
 * In addition to reports that are added to the table, Tidy emits
 * various dialogue type information. Most of these are specific to
 * exact circumstances, although `TY_(DialogueMessage)` should be
 * used instead of adding a new function, if possible.
 *********************************************************************/


void TY_(DialogueMessage)( TidyDocImpl* doc, uint code, TidyReportLevel level )
{
    TidyMessageImpl *message = NULL;

    message = TY_(tidyMessageCreate)( doc, code, level);
    messageOut(message);
}


void TY_(ErrorSummary)( TidyDocImpl* doc )
{
    TidyMessageImpl *message = NULL;
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
        {
            doc->badAccess &= ~(BA_USING_FRAMES | BA_USING_NOFRAMES);
        }
    }

    if (doc->badChars)
    {
#if 0
        if ( doc->badChars & WINDOWS_CHARS )
        {
            message = TY_(tidyMessageCreate)( doc, TEXT_WINDOWS_CHARS, TidyDialogueDoc);
            messagePos(message);
        }
#endif
        if (doc->badChars & BC_VENDOR_SPECIFIC_CHARS)
        {
            message = TY_(tidyMessageCreate)( doc, TEXT_VENDOR_CHARS, TidyDialogueDoc, encnam);
            messageOut(message);
        }
        if ((doc->badChars & BC_INVALID_SGML_CHARS) || (doc->badChars & BC_INVALID_NCR))
        {
            message = TY_(tidyMessageCreate)( doc, TEXT_SGML_CHARS, TidyDialogueDoc, encnam);
            messageOut(message);
        }
        if (doc->badChars & BC_INVALID_UTF8)
        {
            message = TY_(tidyMessageCreate)( doc, TEXT_INVALID_UTF8, TidyDialogueDoc);
            messageOut(message);
        }

#if SUPPORT_UTF16_ENCODINGS

        if (doc->badChars & BC_INVALID_UTF16)
        {
            message = TY_(tidyMessageCreate)( doc, TEXT_INVALID_UTF16, TidyDialogueDoc);
            messageOut(message);
        }

#endif

        if (doc->badChars & BC_INVALID_URI)
        {
            message = TY_(tidyMessageCreate)( doc, TEXT_INVALID_URI, TidyDialogueDoc);
            messageOut(message);
        }
    }

    if (doc->badForm & flg_BadForm) /* Issue #166 - changed to BIT flag to support other errors */
    {
        message = TY_(tidyMessageCreate)( doc, TEXT_BAD_FORM, TidyDialogueDoc);
        messageOut(message);
    }

    if (doc->badForm & flg_BadMain) /* Issue #166 - repeated <main> element */
    {
        message = TY_(tidyMessageCreate)( doc, TEXT_BAD_MAIN, TidyDialogueDoc);
        messageOut(message);
    }

    if (doc->badAccess)
    {
        /* Tidy "classic" accessibility tests */
        if ( cfg(doc, TidyAccessibilityCheckLevel) == 0 )
        {
            if (doc->badAccess & BA_MISSING_SUMMARY)
            {
                message = TY_(tidyMessageCreate)( doc, TEXT_M_SUMMARY, TidyDialogueDoc);
                messageOut(message);
            }

            if (doc->badAccess & BA_MISSING_IMAGE_ALT)
            {
                message = TY_(tidyMessageCreate)( doc, TEXT_M_IMAGE_ALT, TidyDialogueDoc);
                messageOut(message);
            }

            if (doc->badAccess & BA_MISSING_IMAGE_MAP)
            {
                message = TY_(tidyMessageCreate)( doc, TEXT_M_IMAGE_MAP, TidyDialogueDoc);
                messageOut(message);
            }

            if (doc->badAccess & BA_MISSING_LINK_ALT)
            {
                message = TY_(tidyMessageCreate)( doc, TEXT_M_LINK_ALT, TidyDialogueDoc);
                messageOut(message);
            }

            if ((doc->badAccess & BA_USING_FRAMES) && !(doc->badAccess & BA_USING_NOFRAMES))
            {
                message = TY_(tidyMessageCreate)( doc, TEXT_USING_FRAMES, TidyDialogueDoc);
                messageOut(message);
            }
        }

        if ( cfg(doc, TidyAccessibilityCheckLevel) > 0 )
        {
            message = TY_(tidyMessageCreate)( doc, TEXT_ACCESS_ADVICE2, TidyDialogueDoc);
            messageOut(message);
        }
        else
        {
            message = TY_(tidyMessageCreate)( doc, TEXT_ACCESS_ADVICE1, TidyDialogueDoc);
            messageOut(message);
        }
    }

    if (doc->badLayout)
    {
        if (doc->badLayout & USING_LAYER)
        {
            message = TY_(tidyMessageCreate)( doc, TEXT_USING_LAYER, TidyDialogueDoc);
            messageOut(message);
        }

        if (doc->badLayout & USING_SPACER)
        {
            message = TY_(tidyMessageCreate)( doc, TEXT_USING_SPACER, TidyDialogueDoc);
            messageOut(message);
        }

        if (doc->badLayout & USING_FONT)
        {
            message = TY_(tidyMessageCreate)( doc, TEXT_USING_FONT, TidyDialogueDoc);
            messageOut(message);
        }

        if (doc->badLayout & USING_NOBR)
        {
            message = TY_(tidyMessageCreate)( doc, TEXT_USING_NOBR, TidyDialogueDoc);
            messageOut(message);
        }
        
        if (doc->badLayout & USING_BODY)
        {
            message = TY_(tidyMessageCreate)( doc, TEXT_USING_BODY, TidyDialogueDoc);
            messageOut(message);
        }
    }
}


void TY_(ReportNumWarnings)( TidyDocImpl* doc )
{
    TidyMessageImpl *message = NULL;

    if ( doc->warnings > 0 || doc->errors > 0 )
    {
        uint code;
        if ( doc->errors > cfg(doc, TidyShowErrors) || !cfgBool(doc, TidyShowWarnings) )
        {
            code = STRING_NOT_ALL_SHOWN;
        }
        else
        {
            code = STRING_ERROR_COUNT;
        }

        message = TY_(tidyMessageCreate)( doc, code, TidyDialogueSummary,
                                         doc->warnings, tidyLocalizedStringN( STRING_ERROR_COUNT_WARNING, doc->warnings ),
                                         doc->errors, tidyLocalizedStringN( STRING_ERROR_COUNT_ERROR, doc->errors ) );
    }
    else
    {
        message = TY_(tidyMessageCreate)( doc, STRING_NO_ERRORS, TidyDialogueSummary);
    }
    messageOut(message);
}


/*********************************************************************
 * Key Discovery
 *********************************************************************/


/*********************************************************************
 * LibTidy users may want to to enable their own localization lookup
 * lookup methods. Because Tidy's errors codes are enums, the actual
 * values can change over time. This table will the LibTidy users
 * always have a static value available for use.
 *
 * For macro documentation, refer to the comments in `tidyenum.h`.
 *********************************************************************/

typedef struct tidyStringsKeyItem {
    ctmbstr key;
    int value;
} tidyStringsKeyItem;

static const tidyStringsKeyItem tidyStringsKeys[] = {

    FOREACH_TIDYCONFIGCATEGORY(MAKE_STRUCT)
    FOREACH_MSG_MISC(MAKE_STRUCT)
    FOREACH_DIALOG_MSG(MAKE_STRUCT)
    FOREACH_REPORT_MSG(MAKE_STRUCT)
    
    { "TIDYSTRINGS_FIRST",                        TIDYSTRINGS_FIRST },
    
#if SUPPORT_ACCESSIBILITY_CHECKS
    FOREACH_ACCESS_MSG(MAKE_STRUCT)
#endif


#if SUPPORT_CONSOLE_APP
    FOREACH_MSG_CONSOLE(MAKE_STRUCT)
#endif

    { "TIDYSTRINGS_LAST",                         TIDYSTRINGS_LAST  },
    { NULL,                                       0                 },
};


/**
 *  Given an error code, return the string associated with it.
 */
ctmbstr TY_(tidyErrorCodeAsKey)(uint code)
{
    uint i = 0;
    while (tidyStringsKeys[i].key) {
        if ( tidyStringsKeys[i].value == code )
            return tidyStringsKeys[i].key;
        i++;
    }
    return "UNDEFINED";
}


/**
 *  Given an error code string, return its uint.
 */
uint TY_(tidyErrorCodeFromKey)(ctmbstr code)
{
    uint i = 0;
    while (tidyStringsKeys[i].key) {
        if ( strcmp(tidyStringsKeys[i].key, code) == 0 )
            return tidyStringsKeys[i].value;
        i++;
    }
    return UINT_MAX;
}


/**
 *  Determines the number of error codes used by Tidy.
 */
static const uint tidyErrorCodeListSize()
{
    static uint array_size = 0;
    
    if ( array_size == 0 )
    {
        while ( tidyStringsKeys[array_size].key ) {
            array_size++;
        }
    }
    
    return array_size;
}

/**
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's list of error codes. Individual items must be
 *  retrieved with getNextErrorCode();
 */
TidyIterator TY_(getErrorCodeList)()
{
    return (TidyIterator)(size_t)1;
}

/**
 *  Returns the next error code.
 */
uint TY_(getNextErrorCode)( TidyIterator* iter )
{
    const tidyStringsKeyItem *item = NULL;
    size_t itemIndex;
    assert( iter != NULL );
    
    itemIndex = (size_t)*iter;
    
    if ( itemIndex > 0 && itemIndex <= tidyErrorCodeListSize() )
    {
        item = &tidyStringsKeys[itemIndex - 1];
        itemIndex++;
    }
    
    *iter = (TidyIterator)( itemIndex <= tidyErrorCodeListSize() ? itemIndex : (size_t)0 );
    return item->value;
}


/*********************************************************************
 * Output Utility Functions
 *********************************************************************/


/** A simple structure to hold our list of words. */
typedef struct word {
    ctmbstr s;  /**< a pointer to the start of the word. */
    uint len;   /**< The length of the word in bytes. */
} *wordList;


/** Make a list of all of the words that we want to output. Keeping this
 ** separate allows us the possibility to write other word wrap functions in
 ** the future, such as typographically beautiful ones instead of greedy ones.
 ** @param s The string to word wrap.
 ** @param [out] n A pointer to an integer indicating the number of words in 
 **        the list. Note that the number of words includes the count of 
 **        newlines, which are considered words for our purpose.
 ** @return The list of words, as allocated memory.
 */
static wordList makeWordList( TidyDocImpl* doc, ctmbstr s, uint *n )
{
    uint max_n = 0;
    wordList words = 0;
    
    *n = 0;

    while (1)
    {
        while ( *s && isblank(*s) )
        {
            s++;
        }
        
        if ( !*s )
        {
            break;
        }
        
        if ( *n >= max_n )
        {
            if ( !(max_n *= 2) )
            {
                max_n = 2;
            }
            words = TidyDocRealloc(doc, words, max_n * sizeof(*words));
        }

        words[*n].s = s;

        if ( *s == '\n' )
        {
            s++;
            words[*n].len = 1;
        }
        else
        {
            while ( *s && (!isspace(*s)) )
            {
                s++;
                words[*n].len = (uint)(s - words[*n].s);
            }
        }

        (*n)++;
    }
    
    return words;
}


/** Builds a list of line breaks according to the number of specified columns.
 ** Note that newlines will be treated properly as breaks, but it's important
 ** that your writing routine identify and not output them, lest you end up
 ** with a double quantity of newlines.
 ** @param words A wordList of words, previously generated.
 ** @param count A count of the words in the wordlist, previously generated.
 ** @param cols The maximum number of columns to write.
 ** @result A list of line breaks, as allocated memory.
 **
 */
static uint* makeBreakList( TidyDocImpl* doc, wordList words, uint count, uint cols )
{
    uint line = 0;
    uint i = 0;
    uint j = 0;
    Bool isNewline = no;
    uint *breaks = TidyDocAlloc(doc, sizeof(uint) * (count + 1) );
    
    while (1)
    {
        if ( i == count )
        {
            breaks[j++] = i;
            break;
        }

        isNewline = words[i].s[0] == '\n';
        
        if ( !line && !isNewline )
        {
            line = words[i++].len;
            continue;
        }
        
        if ( line + words[i].len < cols && !isNewline )
        {
            line += words[i++].len + 1;
            continue;
        }
        
        if ( isNewline )
        {
            i++;
        }
        
        breaks[j++] = i;
        line = 0;
    }
    breaks[j++] = 0;
    return breaks;
}


/** Returns an allocated string of the wrapped text using using the 
 ** makeBreakList() wrapping algorithm.
 ** @param doc A Tidy document so that we can use its allocator.
 ** @param text The text to wrap.
 ** @param columns The maximum column count to output.
 ** @result An allocated, word-wrapped string.
 */
tmbstr TY_(tidyWrappedText)( TidyDocImpl* doc, ctmbstr string, uint columns )
{
    uint i = 0;
    uint j = 0;
    uint nl = 0;
    uint nnl = 0;

    uint len;
    wordList list;
    uint *breaks;
    uint sizeBuf;

    columns = columns > 0 ? columns : UINT_MAX;
    list = makeWordList( doc,string, &len );
    breaks = makeBreakList( doc, list, len, columns );
    sizeBuf = (uint)strlen(list[0].s) + sizeof(breaks) * len + 1;

    char *output = TidyDocAlloc( doc, sizeBuf );
    output[0] = '\0';

    for ( i = 0; i < len && breaks[i]; i++ )
    {
        while ( j < breaks[i] )
        {
            nl = list[j].s[0] == '\n';
            nnl = j + 1 < len && list[j+1].s[0] == '\n';
            
            if ( !nl )
            {
                uint size = strlen(output);
                snprintf( output + size, sizeBuf - size + 1, "%.*s", list[j].len, list[j].s );
            }
            if ( j < breaks[i] - 1 && !nnl )
            {
                snprintf( output + strlen(output), 2, " " );
            }
            j++;
        }
        if ( breaks[i] )
        {
            snprintf( output + strlen(output), 2, "\n" );
        }
    }

    TidyDocFree(doc, breaks);
    return output;
}


/*********************************************************************
 * Accessibility Module
 * These methods are part of the accessibility module access.h/c.
 *********************************************************************/


#if SUPPORT_ACCESSIBILITY_CHECKS

void TY_(ReportAccessError)( TidyDocImpl* doc, Node* node, uint code )
{
    TidyMessageImpl *message = NULL;

    doc->badAccess |= BA_WAI;
    message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyAccess );
    messageOut(message);
}


void TY_(ReportAccessWarning)( TidyDocImpl* doc, Node* node, uint code )
{
    TidyMessageImpl *message = NULL;

    doc->badAccess |= BA_WAI;
    message = TY_(tidyMessageCreateWithNode)(doc, node, code, TidyAccess );
    messageOut(message);
}

#endif /* SUPPORT_ACCESSIBILITY_CHECKS */


/*********************************************************************
 * Documentation of configuration options
 *
 * Although most of the strings now come from the language module,
 * generating the documentation by the console application requires a
 * series of cross-references that are generated in this messaging
 * module.
 *********************************************************************/


#if SUPPORT_CONSOLE_APP
/* Cross-references definitions.
 * Note that each list must be terminated with `TidyUnknownOption`.
 */
static const TidyOptionId TidyAsciiCharsLinks[] =      { TidyMakeClean, TidyUnknownOption };
static const TidyOptionId TidyBlockTagsLinks[] =       { TidyEmptyTags, TidyInlineTags, TidyPreTags, TidyUseCustomTags, TidyUnknownOption };
static const TidyOptionId TidyCharEncodingLinks[] =    { TidyInCharEncoding, TidyOutCharEncoding, TidyUnknownOption };
static const TidyOptionId TidyDuplicateAttrsLinks[] =  { TidyJoinClasses, TidyJoinStyles, TidyUnknownOption };
static const TidyOptionId TidyEmptyTagsLinks[] =       { TidyBlockTags, TidyInlineTags, TidyPreTags, TidyUseCustomTags, TidyUnknownOption };
static const TidyOptionId TidyErrFileLinks[] =         { TidyOutFile, TidyUnknownOption };
static const TidyOptionId TidyInCharEncodingLinks[] =  { TidyCharEncoding, TidyUnknownOption };
static const TidyOptionId TidyIndentContentLinks[] =   { TidyIndentSpaces, TidyUnknownOption };
static const TidyOptionId TidyIndentSpacesLinks[] =    { TidyIndentContent, TidyUnknownOption };
static const TidyOptionId TidyInlineTagsLinks[] =      { TidyBlockTags, TidyEmptyTags, TidyPreTags, TidyUseCustomTags, TidyUnknownOption };
static const TidyOptionId TidyMergeDivsLinks[] =       { TidyMakeClean, TidyMergeSpans, TidyUnknownOption };
static const TidyOptionId TidyMergeSpansLinks[] =      { TidyMakeClean, TidyMergeDivs, TidyUnknownOption };
static const TidyOptionId TidyNumEntitiesLinks[] =     { TidyDoctype, TidyPreserveEntities, TidyUnknownOption };
static const TidyOptionId TidyOutCharEncodingLinks[] = { TidyCharEncoding, TidyUnknownOption };
static const TidyOptionId TidyOutFileLinks[] =         { TidyErrFile, TidyUnknownOption };
static const TidyOptionId TidyPreTagsLinks[] =         { TidyBlockTags, TidyEmptyTags, TidyInlineTags, TidyUseCustomTags, TidyUnknownOption };
static const TidyOptionId TidyUseCustomTagsLinks[] =   { TidyBlockTags, TidyEmptyTags, TidyInlineTags, TidyPreTags, TidyUnknownOption };
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
    { TidyUseCustomTags,   TidyUseCustomTagsLinks   },
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

#endif /* SUPPORT_CONSOLE_APP */


/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
