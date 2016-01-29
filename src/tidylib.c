/* tidylib.c -- internal library definitions

  (c) 1998-2008 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

  Defines HTML Tidy API implemented by tidy library.

  Very rough initial cut for discussion purposes.

  Public interface is const-correct and doesn't explicitly depend
  on any globals.  Thus, thread-safety may be introduced w/out
  changing the interface.

  Looking ahead to a C++ wrapper, C functions always pass
  this-equivalent as 1st arg.

  Created 2001-05-20 by Charles Reitzel

*/

#include <errno.h>

#include "tidy-int.h"
#include "parser.h"
#include "clean.h"
#include "gdoc.h"
#include "config.h"
#include "message.h"
#include "pprint.h"
#include "entities.h"
#include "tmbstr.h"
#include "utf8.h"
#include "mappedio.h"

#ifdef TIDY_WIN32_MLANG_SUPPORT
#include "win32tc.h"
#endif
#if !defined(NDEBUG) && defined(_MSC_VER)
#include "sprtf.h"
#endif

/* Create/Destroy a Tidy "document" object */
static TidyDocImpl* tidyDocCreate( TidyAllocator *allocator );
static void         tidyDocRelease( TidyDocImpl* impl );

static int          tidyDocStatus( TidyDocImpl* impl );

/* Parse Markup */
static int          tidyDocParseFile( TidyDocImpl* impl, ctmbstr htmlfil );
static int          tidyDocParseStdin( TidyDocImpl* impl );
static int          tidyDocParseString( TidyDocImpl* impl, ctmbstr content );
static int          tidyDocParseBuffer( TidyDocImpl* impl, TidyBuffer* inbuf );
static int          tidyDocParseSource( TidyDocImpl* impl, TidyInputSource* docIn );


/* Execute post-parse diagnostics and cleanup.
** Note, the order is important.  You will get different
** results from the diagnostics depending on if they are run
** pre-or-post repair.
*/
static int          tidyDocRunDiagnostics( TidyDocImpl* doc );
static void         tidyDocReportDoctype( TidyDocImpl* doc );
static int          tidyDocCleanAndRepair( TidyDocImpl* doc );


/* Save cleaned up file to file/buffer/sink */
static int          tidyDocSaveFile( TidyDocImpl* impl, ctmbstr htmlfil );
static int          tidyDocSaveStdout( TidyDocImpl* impl );
static int          tidyDocSaveString( TidyDocImpl* impl, tmbstr buffer, uint* buflen );
static int          tidyDocSaveBuffer( TidyDocImpl* impl, TidyBuffer* outbuf );
static int          tidyDocSaveSink( TidyDocImpl* impl, TidyOutputSink* docOut );
static int          tidyDocSaveStream( TidyDocImpl* impl, StreamOut* out );

#ifdef NEVER
TidyDocImpl* tidyDocToImpl( TidyDoc tdoc )
{
  return (TidyDocImpl*) tdoc;
}
TidyDoc      tidyImplToDoc( TidyDocImpl* impl )
{
  return (TidyDoc) impl;
}

Node*        tidyNodeToImpl( TidyNode tnod )
{
  return (Node*) tnod;
}
TidyNode     tidyImplToNode( Node* node )
{
  return (TidyNode) node;
}

AttVal*      tidyAttrToImpl( TidyAttr tattr )
{
  return (AttVal*) tattr;
}
TidyAttr     tidyImplToAttr( AttVal* attval )
{
  return (TidyAttr) attval;
}

const TidyOptionImpl* tidyOptionToImpl( TidyOption topt )
{
  return (const TidyOptionImpl*) topt;
}
TidyOption   tidyImplToOption( const TidyOptionImpl* option )
{
  return (TidyOption) option;
}
#endif

/* Tidy public interface
**
** Most functions return an integer:
**
** 0    -> SUCCESS
** >0   -> WARNING
** <0   -> ERROR
**
*/

TidyDoc TIDY_CALL       tidyCreate(void)
{
  TidyDocImpl* impl = tidyDocCreate( &TY_(g_default_allocator) );
  return tidyImplToDoc( impl );
}

TidyDoc TIDY_CALL tidyCreateWithAllocator( TidyAllocator *allocator )
{
  TidyDocImpl* impl = tidyDocCreate( allocator );
  return tidyImplToDoc( impl );
}

void TIDY_CALL          tidyRelease( TidyDoc tdoc )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  tidyDocRelease( impl );
}

TidyDocImpl* tidyDocCreate( TidyAllocator *allocator )
{
    TidyDocImpl* doc = (TidyDocImpl*)TidyAlloc( allocator, sizeof(TidyDocImpl) );
    TidyClearMemory( doc, sizeof(*doc) );
    doc->allocator = allocator;

    TY_(InitMap)();
    TY_(InitTags)( doc );
    TY_(InitAttrs)( doc );
    TY_(InitConfig)( doc );
    TY_(InitPrintBuf)( doc );

    /* By default, wire tidy messages to standard error.
    ** Document input will be set by parsing routines.
    ** Document output will be set by pretty print routines.
    ** Config input will be set by config parsing routines.
    ** But we need to start off with a way to report errors.
    */
    doc->errout = TY_(StdErrOutput)();
    return doc;
}

void          tidyDocRelease( TidyDocImpl* doc )
{
    /* doc in/out opened and closed by parse/print routines */
    if ( doc )
    {
        assert( doc->docIn == NULL );
        assert( doc->docOut == NULL );

        TY_(ReleaseStreamOut)( doc, doc->errout );
        doc->errout = NULL;

        TY_(FreePrintBuf)( doc );
        TY_(FreeNode)(doc, &doc->root);
        TidyClearMemory(&doc->root, sizeof(Node));

        if (doc->givenDoctype)
            TidyDocFree(doc, doc->givenDoctype);

        TY_(FreeConfig)( doc );
        TY_(FreeAttrTable)( doc );
        TY_(FreeTags)( doc );
        /*\ 
         *  Issue #186 - Now FreeNode depend on the doctype, so the lexer is needed
         *  to determine which hash is to be used, so free it last.
        \*/
        TY_(FreeLexer)( doc );
        TidyDocFree( doc, doc );
    }
}

/* Let application store a chunk of data w/ each Tidy tdocance.
** Useful for callbacks.
*/
void TIDY_CALL        tidySetAppData( TidyDoc tdoc, void* appData )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  if ( impl )
    impl->appData = appData;
}
void* TIDY_CALL       tidyGetAppData( TidyDoc tdoc )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  if ( impl )
    return impl->appData;
  return NULL;
}

ctmbstr TIDY_CALL     tidyReleaseDate(void)
{
    return TY_(ReleaseDate)();
}


/* Get/set configuration options
*/
Bool TIDY_CALL        tidySetOptionCallback( TidyDoc tdoc, TidyOptCallback pOptCallback )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  if ( impl )
  {
    impl->pOptCallback = pOptCallback;
    return yes;
  }
  return no;
}


int TIDY_CALL     tidyLoadConfig( TidyDoc tdoc, ctmbstr cfgfil )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
        return TY_(ParseConfigFile)( impl, cfgfil );
    return -EINVAL;
}

int TIDY_CALL     tidyLoadConfigEnc( TidyDoc tdoc, ctmbstr cfgfil, ctmbstr charenc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
        return TY_(ParseConfigFileEnc)( impl, cfgfil, charenc );
    return -EINVAL;
}

int TIDY_CALL         tidySetCharEncoding( TidyDoc tdoc, ctmbstr encnam )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
    {
        int enc = TY_(CharEncodingId)( impl, encnam );
        if ( enc >= 0 && TY_(AdjustCharEncoding)(impl, enc) )
            return 0;

        TY_(ReportBadArgument)( impl, "char-encoding" );
    }
    return -EINVAL;
}

int TIDY_CALL           tidySetInCharEncoding( TidyDoc tdoc, ctmbstr encnam )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
    {
        int enc = TY_(CharEncodingId)( impl, encnam );
        if ( enc >= 0 && TY_(SetOptionInt)( impl, TidyInCharEncoding, enc ) )
            return 0;

        TY_(ReportBadArgument)( impl, "in-char-encoding" );
    }
    return -EINVAL;
}

int TIDY_CALL           tidySetOutCharEncoding( TidyDoc tdoc, ctmbstr encnam )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
    {
        int enc = TY_(CharEncodingId)( impl, encnam );
        if ( enc >= 0 && TY_(SetOptionInt)( impl, TidyOutCharEncoding, enc ) )
            return 0;

        TY_(ReportBadArgument)( impl, "out-char-encoding" );
    }
    return -EINVAL;
}

TidyOptionId TIDY_CALL tidyOptGetIdForName( ctmbstr optnam )
{
    const TidyOptionImpl* option = TY_(lookupOption)( optnam );
    if ( option )
        return option->id;
    return N_TIDY_OPTIONS;  /* Error */
}

TidyIterator TIDY_CALL  tidyGetOptionList( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
        return TY_(getOptionList)( impl );
    return (TidyIterator) -1;
}

TidyOption TIDY_CALL    tidyGetNextOption( TidyDoc tdoc, TidyIterator* pos )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    const TidyOptionImpl* option = NULL;
    if ( impl )
        option = TY_(getNextOption)( impl, pos );
    else if ( pos )
        *pos = 0;
    return tidyImplToOption( option );
}


TidyOption TIDY_CALL    tidyGetOption( TidyDoc ARG_UNUSED(tdoc), TidyOptionId optId )
{
    const TidyOptionImpl* option = TY_(getOption)( optId );
    return tidyImplToOption( option );
}
TidyOption TIDY_CALL    tidyGetOptionByName( TidyDoc ARG_UNUSED(doc), ctmbstr optnam )
{
    const TidyOptionImpl* option = TY_(lookupOption)( optnam );
    return tidyImplToOption( option );
}

TidyOptionId TIDY_CALL  tidyOptGetId( TidyOption topt )
{
    const TidyOptionImpl* option = tidyOptionToImpl( topt );
    if ( option )
        return option->id;
    return N_TIDY_OPTIONS;
}
ctmbstr TIDY_CALL       tidyOptGetName( TidyOption topt )
{
    const TidyOptionImpl* option = tidyOptionToImpl( topt );
    if ( option )
        return option->name;
    return NULL;
}
TidyOptionType TIDY_CALL tidyOptGetType( TidyOption topt )
{
    const TidyOptionImpl* option = tidyOptionToImpl( topt );
    if ( option )
        return option->type;
    return (TidyOptionType) -1;
}
TidyConfigCategory TIDY_CALL tidyOptGetCategory( TidyOption topt )
{
    const TidyOptionImpl* option = tidyOptionToImpl( topt );
    if ( option )
        return option->category;
    return (TidyConfigCategory) -1;
}
ctmbstr TIDY_CALL       tidyOptGetDefault( TidyOption topt )
{
    const TidyOptionImpl* option = tidyOptionToImpl( topt );
    if ( option && option->type == TidyString )
        return option->pdflt; /* Issue #306 - fix an old typo hidden by a cast! */
    return NULL;
}
ulong TIDY_CALL          tidyOptGetDefaultInt( TidyOption topt )
{
    const TidyOptionImpl* option = tidyOptionToImpl( topt );
    if ( option && option->type != TidyString )
        return option->dflt;
    return ~0U;
}
Bool TIDY_CALL          tidyOptGetDefaultBool( TidyOption topt )
{
    const TidyOptionImpl* option = tidyOptionToImpl( topt );
    if ( option && option->type != TidyString )
        return ( option->dflt ? yes : no );
    return no;
}
Bool TIDY_CALL          tidyOptIsReadOnly( TidyOption topt )
{
    const TidyOptionImpl* option = tidyOptionToImpl( topt );
    if ( option  )
        return ( option->parser == NULL );
    return yes;
}


TidyIterator TIDY_CALL  tidyOptGetPickList( TidyOption topt )
{
    const TidyOptionImpl* option = tidyOptionToImpl( topt );
    if ( option )
      return TY_(getOptionPickList)( option );
    return (TidyIterator) -1;
}
ctmbstr TIDY_CALL       tidyOptGetNextPick( TidyOption topt, TidyIterator* pos )
{
    const TidyOptionImpl* option = tidyOptionToImpl( topt );
    if ( option )
        return TY_(getNextOptionPick)( option, pos );
    return NULL;
}


ctmbstr TIDY_CALL       tidyOptGetValue( TidyDoc tdoc, TidyOptionId optId )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  ctmbstr optval = NULL;
  if ( impl )
    optval = cfgStr( impl, optId );
  return optval;
}
Bool TIDY_CALL        tidyOptSetValue( TidyDoc tdoc, TidyOptionId optId, ctmbstr val )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  if ( impl )
    return TY_(ParseConfigValue)( impl, optId, val );
  return no;
}
Bool TIDY_CALL        tidyOptParseValue( TidyDoc tdoc, ctmbstr optnam, ctmbstr val )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  if ( impl )
    return TY_(ParseConfigOption)( impl, optnam, val );
  return no;
}

ulong TIDY_CALL        tidyOptGetInt( TidyDoc tdoc, TidyOptionId optId )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    ulong opti = 0;
    if ( impl )
        opti = cfg( impl, optId );
    return opti;
}

Bool TIDY_CALL        tidyOptSetInt( TidyDoc tdoc, TidyOptionId optId, ulong val )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
        return TY_(SetOptionInt)( impl, optId, val );
    return no;
}

Bool TIDY_CALL         tidyOptGetBool( TidyDoc tdoc, TidyOptionId optId )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    Bool optb = no;
    if ( impl )
    {
        const TidyOptionImpl* option = TY_(getOption)( optId );
        if ( option )
        {
            optb = cfgBool( impl, optId );
        }
    }
    return optb;
}

Bool TIDY_CALL        tidyOptSetBool( TidyDoc tdoc, TidyOptionId optId, Bool val )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
        return TY_(SetOptionBool)( impl, optId, val );
    return no;
}

ctmbstr TIDY_CALL       tidyOptGetEncName( TidyDoc tdoc, TidyOptionId optId )
{
  uint enc = tidyOptGetInt( tdoc, optId );
  return TY_(CharEncodingOptName)( enc );
}

ctmbstr TIDY_CALL       tidyOptGetCurrPick( TidyDoc tdoc, TidyOptionId optId )
{
    const TidyOptionImpl* option = TY_(getOption)( optId );
    if ( option && option->pickList )
    {
        uint ix, pick = tidyOptGetInt( tdoc, optId );
        const ctmbstr* pL = option->pickList;
        for ( ix=0; *pL && ix < pick; ++ix )
            ++pL;
        if ( *pL )
            return *pL;
    }
    return NULL;
}


TidyIterator TIDY_CALL tidyOptGetDeclTagList( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    TidyIterator declIter = 0;
    if ( impl )
        declIter = TY_(GetDeclaredTagList)( impl );
    return declIter;
}

ctmbstr TIDY_CALL       tidyOptGetNextDeclTag( TidyDoc tdoc, TidyOptionId optId,
                                     TidyIterator* iter )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    ctmbstr tagnam = NULL;
    if ( impl )
    {
        UserTagType tagtyp = tagtype_null;
        if ( optId == TidyInlineTags )
            tagtyp = tagtype_inline;
        else if ( optId == TidyBlockTags )
            tagtyp = tagtype_block;
        else if ( optId == TidyEmptyTags )
            tagtyp = tagtype_empty;
        else if ( optId == TidyPreTags )
            tagtyp = tagtype_pre;
        if ( tagtyp != tagtype_null )
            tagnam = TY_(GetNextDeclaredTag)( impl, tagtyp, iter );
    }
    return tagnam;
}

ctmbstr TIDY_CALL tidyOptGetDoc( TidyDoc ARG_UNUSED(tdoc), TidyOption opt )
{
    const TidyOptionId optId = tidyOptGetId( opt );
    return tidyLocalizedString(optId);
}

TidyIterator TIDY_CALL tidyOptGetDocLinksList( TidyDoc ARG_UNUSED(tdoc), TidyOption opt )
{
    const TidyOptionId optId = tidyOptGetId( opt );
    const TidyOptionDoc* docDesc = TY_(OptGetDocDesc)( optId );
    if (docDesc && docDesc->links)
        return (TidyIterator)docDesc->links;
    return (TidyIterator)NULL;
}

TidyOption TIDY_CALL tidyOptGetNextDocLinks( TidyDoc tdoc, TidyIterator* pos )
{
    const TidyOptionId* curr = (const TidyOptionId *)*pos;
    TidyOption opt;

    if (*curr == TidyUnknownOption)
    {
        *pos = (TidyIterator)NULL;
        return (TidyOption)0;
    }
    opt = tidyGetOption(tdoc, *curr);
    curr++;
    *pos = (*curr == TidyUnknownOption ) ?
        (TidyIterator)NULL:(TidyIterator)curr;
    return opt;
}

int TIDY_CALL tidyOptSaveFile( TidyDoc tdoc, ctmbstr cfgfil )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
        return TY_(SaveConfigFile)( impl, cfgfil );
    return -EINVAL;
}

int TIDY_CALL tidyOptSaveSink( TidyDoc tdoc, TidyOutputSink* sink )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
        return TY_(SaveConfigSink)( impl, sink );
    return -EINVAL;
}

Bool TIDY_CALL tidyOptSnapshot( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
    {
        TY_(TakeConfigSnapshot)( impl );
        return yes;
    }
    return no;
}
Bool TIDY_CALL tidyOptResetToSnapshot( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
    {
        TY_(ResetConfigToSnapshot)( impl );
        return yes;
    }
    return no;
}
Bool TIDY_CALL tidyOptResetAllToDefault( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
    {
        TY_(ResetConfigToDefault)( impl );
        return yes;
    }
    return no;
}

Bool TIDY_CALL tidyOptResetToDefault( TidyDoc tdoc, TidyOptionId optId )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
        return TY_(ResetOptionToDefault)( impl, optId );
    return no;
}

Bool TIDY_CALL tidyOptDiffThanDefault( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
        return TY_(ConfigDiffThanDefault)( impl );
    return no;
}
Bool TIDY_CALL          tidyOptDiffThanSnapshot( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
        return TY_(ConfigDiffThanSnapshot)( impl );
    return no;
}

Bool TIDY_CALL tidyOptCopyConfig( TidyDoc to, TidyDoc from )
{
    TidyDocImpl* docTo = tidyDocToImpl( to );
    TidyDocImpl* docFrom = tidyDocToImpl( from );
    if ( docTo && docFrom )
    {
        TY_(CopyConfig)( docTo, docFrom );
        return yes;
    }
    return no;
}


/* I/O and Message handling interface
**
** By default, Tidy will define, create and use
** tdocances of input and output handlers for
** standard C buffered I/O (i.e. FILE* stdin,
** FILE* stdout and FILE* stderr for content
** input, content output and diagnostic output,
** respectively.  A FILE* cfgFile input handler
** will be used for config files.  Command line
** options will just be set directly.
*/

/* Use TidyReportFilter to filter messages by diagnostic level:
** info, warning, etc.  Just set diagnostic output
** handler to redirect all diagnostics output.  Return true
** to proceed with output, false to cancel.
*/
Bool TIDY_CALL        tidySetReportFilter( TidyDoc tdoc, TidyReportFilter filt )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  if ( impl )
  {
    impl->mssgFilt = filt;
    return yes;
  }
  return no;
}

/* TidyReportFilter2 functions similar to TidyReportFilter, but provides the
** built-in English format string and va_list so that LibTidy users can use
** the format string as a lookup key for providing their own error 
** localizations.
*/
Bool TIDY_CALL        tidySetReportFilter2( TidyDoc tdoc, TidyReportFilter2 filt )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  if ( impl )
  {
    impl->mssgFilt2 = filt;
    return yes;
  }
  return no;
}

/* TidyReportFilter3 functions similar to TidyReportFilter, but provides the
 * string version of the internal enum name so that LibTidy users can use
** the string as a lookup key for providing their own error localizations.
** See the string definitions in language.h
*/
Bool TIDY_CALL        tidySetReportFilter3( TidyDoc tdoc, TidyReportFilter3 filt )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  if ( impl )
  {
    impl->mssgFilt3 = filt;
    return yes;
  }
  return no;
}

#if 0   /* Not yet */
int         tidySetContentOutputSink( TidyDoc tdoc, TidyOutputSink* outp )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  if ( impl )
  {
    impl->docOut = outp;
    return 0;
  }
  return -EINVAL;
}
int         tidySetDiagnosticOutputSink( TidyDoc tdoc, TidyOutputSink* outp )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  if ( impl )
  {
    impl->msgOut = outp;
    return 0;
  }
  return -EINVAL;
}


/* Library helpers
*/
cmbstr       tidyLookupMessage( TidyDoc tdoc, int errorNo )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  cmbstr mssg = NULL;
  if ( impl )
    mssg = tidyMessage_Lookup( impl->messages, errorNo );
  return mssg;
}
#endif


FILE* TIDY_CALL   tidySetErrorFile( TidyDoc tdoc, ctmbstr errfilnam )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
    {
        FILE* errout = fopen( errfilnam, "wb" );
        if ( errout )
        {
            uint outenc = cfg( impl, TidyOutCharEncoding );
            uint nl = cfg( impl, TidyNewline );
            TY_(ReleaseStreamOut)( impl, impl->errout );
            impl->errout = TY_(FileOutput)( impl, errout, outenc, nl );
            return errout;
        }
        else /* Emit message to current error sink */
            TY_(FileError)( impl, errfilnam, TidyError );
    }
    return NULL;
}

int TIDY_CALL    tidySetErrorBuffer( TidyDoc tdoc, TidyBuffer* errbuf )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
    {
        uint outenc = cfg( impl, TidyOutCharEncoding );
        uint nl = cfg( impl, TidyNewline );
        TY_(ReleaseStreamOut)( impl, impl->errout );
        impl->errout = TY_(BufferOutput)( impl, errbuf, outenc, nl );
        return ( impl->errout ? 0 : -ENOMEM );
    }
    return -EINVAL;
}

int TIDY_CALL    tidySetErrorSink( TidyDoc tdoc, TidyOutputSink* sink )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
    {
        uint outenc = cfg( impl, TidyOutCharEncoding );
        uint nl = cfg( impl, TidyNewline );
        TY_(ReleaseStreamOut)( impl, impl->errout );
        impl->errout = TY_(UserOutput)( impl, sink, outenc, nl );
        return ( impl->errout ? 0 : -ENOMEM );
    }
    return -EINVAL;
}

/* Use TidyPPProgress to monitor the progress of the pretty printer.
 */
Bool TIDY_CALL        tidySetPrettyPrinterCallback(TidyDoc tdoc, TidyPPProgress callback)
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
    {
        impl->progressCallback = callback;
        return yes;
    }
    return no;
}


/* Document info */
int TIDY_CALL        tidyStatus( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    int tidyStat = -EINVAL;
    if ( impl )
        tidyStat = tidyDocStatus( impl );
    return tidyStat;
}
int TIDY_CALL        tidyDetectedHtmlVersion( TidyDoc ARG_UNUSED(tdoc) )
{
/*    TidyDocImpl* impl = tidyDocToImpl( tdoc ); */
    return 0;
}
Bool TIDY_CALL        tidyDetectedXhtml( TidyDoc ARG_UNUSED(tdoc) )
{
/*    TidyDocImpl* impl = tidyDocToImpl( tdoc ); */
    return no;
}
Bool TIDY_CALL        tidyDetectedGenericXml( TidyDoc ARG_UNUSED(tdoc) )
{
/*    TidyDocImpl* impl = tidyDocToImpl( tdoc ); */
    return no;
}

uint TIDY_CALL       tidyErrorCount( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    uint count = 0xFFFFFFFF;
    if ( impl )
        count = impl->errors;
    return count;
}
uint TIDY_CALL       tidyWarningCount( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    uint count = 0xFFFFFFFF;
    if ( impl )
        count = impl->warnings;
    return count;
}
uint TIDY_CALL       tidyAccessWarningCount( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    uint count = 0xFFFFFFFF;
    if ( impl )
        count = impl->accessErrors;
    return count;
}
uint TIDY_CALL       tidyConfigErrorCount( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    uint count = 0xFFFFFFFF;
    if ( impl )
        count = impl->optionErrors;
    return count;
}


/* Error reporting functions
*/
void TIDY_CALL         tidyErrorSummary( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
        TY_(ErrorSummary)( impl );
}
void TIDY_CALL         tidyGeneralInfo( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
        TY_(GeneralInfo)( impl );
}


/* I/O Functions
**
** Initial version supports only whole-file operations.
** Do not expose Tidy StreamIn or Out data structures - yet.
*/

/* Parse/load Functions
**
** HTML/XHTML version determined from input.
*/
int TIDY_CALL  tidyParseFile( TidyDoc tdoc, ctmbstr filnam )
{
    TidyDocImpl* doc = tidyDocToImpl( tdoc );
    return tidyDocParseFile( doc, filnam );
}
int TIDY_CALL  tidyParseStdin( TidyDoc tdoc )
{
    TidyDocImpl* doc = tidyDocToImpl( tdoc );
    return tidyDocParseStdin( doc );
}
int TIDY_CALL  tidyParseString( TidyDoc tdoc, ctmbstr content )
{
    TidyDocImpl* doc = tidyDocToImpl( tdoc );
    return tidyDocParseString( doc, content );
}
int TIDY_CALL  tidyParseBuffer( TidyDoc tdoc, TidyBuffer* inbuf )
{
    TidyDocImpl* doc = tidyDocToImpl( tdoc );
    return tidyDocParseBuffer( doc, inbuf );
}
int TIDY_CALL  tidyParseSource( TidyDoc tdoc, TidyInputSource* source )
{
    TidyDocImpl* doc = tidyDocToImpl( tdoc );
    return tidyDocParseSource( doc, source );
}


int   tidyDocParseFile( TidyDocImpl* doc, ctmbstr filnam )
{
#ifdef _WIN32
    return TY_(DocParseFileWithMappedFile)( doc, filnam );
#else
    int status = -ENOENT;
    FILE* fin = fopen( filnam, "rb" );

#if PRESERVE_FILE_TIMES
    struct stat sbuf = {0};
    /* get last modified time */
    TidyClearMemory( &doc->filetimes, sizeof(doc->filetimes) );
    if ( fin && cfgBool(doc,TidyKeepFileTimes) &&
         fstat(fileno(fin), &sbuf) != -1 )
    {
          doc->filetimes.actime  = sbuf.st_atime;
          doc->filetimes.modtime = sbuf.st_mtime;
    }
#endif

    if ( fin )
    {
        StreamIn* in = TY_(FileInput)( doc, fin, cfg( doc, TidyInCharEncoding ));
        if ( !in )
        {
            fclose( fin );
            return status;
        }
        status = TY_(DocParseStream)( doc, in );
        TY_(freeFileSource)(&in->source, yes);
        TY_(freeStreamIn)(in);
    }
    else /* Error message! */
        TY_(FileError)( doc, filnam, TidyError );
    return status;
#endif
}

int   tidyDocParseStdin( TidyDocImpl* doc )
{
    StreamIn* in = TY_(FileInput)( doc, stdin, cfg( doc, TidyInCharEncoding ));
    int status = TY_(DocParseStream)( doc, in );
    TY_(freeStreamIn)(in);
    return status;
}

int   tidyDocParseBuffer( TidyDocImpl* doc, TidyBuffer* inbuf )
{
    int status = -EINVAL;
    if ( inbuf )
    {
        StreamIn* in = TY_(BufferInput)( doc, inbuf, cfg( doc, TidyInCharEncoding ));
        status = TY_(DocParseStream)( doc, in );
        TY_(freeStreamIn)(in);
    }
    return status;
}

int   tidyDocParseString( TidyDocImpl* doc, ctmbstr content )
{
    int status = -EINVAL;
    TidyBuffer inbuf;
    StreamIn* in = NULL;

    if ( content )
    {
        tidyBufInitWithAllocator( &inbuf, doc->allocator );
        tidyBufAttach( &inbuf, (byte*)content, TY_(tmbstrlen)(content)+1 );
        in = TY_(BufferInput)( doc, &inbuf, cfg( doc, TidyInCharEncoding ));
        status = TY_(DocParseStream)( doc, in );
        tidyBufDetach( &inbuf );
        TY_(freeStreamIn)(in);
    }
    return status;
}

int   tidyDocParseSource( TidyDocImpl* doc, TidyInputSource* source )
{
    StreamIn* in = TY_(UserInput)( doc, source, cfg( doc, TidyInCharEncoding ));
    int status = TY_(DocParseStream)( doc, in );
    TY_(freeStreamIn)(in);
    return status;
}


/* Print/save Functions
**
*/
int TIDY_CALL        tidySaveFile( TidyDoc tdoc, ctmbstr filnam )
{
    TidyDocImpl* doc = tidyDocToImpl( tdoc );
    return tidyDocSaveFile( doc, filnam );
}
int TIDY_CALL        tidySaveStdout( TidyDoc tdoc )
{
    TidyDocImpl* doc = tidyDocToImpl( tdoc );
    return tidyDocSaveStdout( doc );
}
int TIDY_CALL        tidySaveString( TidyDoc tdoc, tmbstr buffer, uint* buflen )
{
    TidyDocImpl* doc = tidyDocToImpl( tdoc );
    return tidyDocSaveString( doc, buffer, buflen );
}
int TIDY_CALL        tidySaveBuffer( TidyDoc tdoc, TidyBuffer* outbuf )
{
    TidyDocImpl* doc = tidyDocToImpl( tdoc );
    return tidyDocSaveBuffer( doc, outbuf );
}
int TIDY_CALL        tidySaveSink( TidyDoc tdoc, TidyOutputSink* sink )
{
    TidyDocImpl* doc = tidyDocToImpl( tdoc );
    return tidyDocSaveSink( doc, sink );
}

int         tidyDocSaveFile( TidyDocImpl* doc, ctmbstr filnam )
{
    int status = -ENOENT;
    FILE* fout = NULL;

    /* Don't zap input file if no output */
    if ( doc->errors > 0 &&
         cfgBool(doc, TidyWriteBack) && !cfgBool(doc, TidyForceOutput) )
        status = tidyDocStatus( doc );
    else
        fout = fopen( filnam, "wb" );

    if ( fout )
    {
        uint outenc = cfg( doc, TidyOutCharEncoding );
        uint nl = cfg( doc, TidyNewline );
        StreamOut* out = TY_(FileOutput)( doc, fout, outenc, nl );

        status = tidyDocSaveStream( doc, out );

        fclose( fout );
        TidyDocFree( doc, out );

#if PRESERVE_FILE_TIMES
        if ( doc->filetimes.actime )
        {
            /* set file last accessed/modified times to original values */
            utime( filnam, &doc->filetimes );
            TidyClearMemory( &doc->filetimes, sizeof(doc->filetimes) );
        }
#endif /* PRESERVFILETIMES */
    }
    if ( status < 0 ) /* Error message! */
        TY_(FileError)( doc, filnam, TidyError );
    return status;
}



/* Note, _setmode() does NOT work on Win2K Pro w/ VC++ 6.0 SP3.
** The code has been left in in case it works w/ other compilers
** or operating systems.  If stdout is in Text mode, be aware that
** it will garble UTF16 documents.  In text mode, when it encounters
** a single byte of value 10 (0xA), it will insert a single byte
** value 13 (0xD) just before it.  This has the effect of garbling
** the entire document.
*/

#if !defined(NO_SETMODE_SUPPORT)

#if defined(_WIN32) || defined(OS2_OS)
#include <fcntl.h>
#include <io.h>
#endif

#endif

int         tidyDocSaveStdout( TidyDocImpl* doc )
{
#if !defined(NO_SETMODE_SUPPORT)

#if defined(_WIN32) || defined(OS2_OS)
    int oldstdoutmode = -1, oldstderrmode = -1;
#endif

#endif
    int status = 0;
    uint outenc = cfg( doc, TidyOutCharEncoding );
    uint nl = cfg( doc, TidyNewline );
    StreamOut* out = TY_(FileOutput)( doc, stdout, outenc, nl );

#if !defined(NO_SETMODE_SUPPORT)

#if defined(_WIN32) || defined(OS2_OS)
    oldstdoutmode = setmode( fileno(stdout), _O_BINARY );
    oldstderrmode = setmode( fileno(stderr), _O_BINARY );
#endif

#endif

    if ( 0 == status )
      status = tidyDocSaveStream( doc, out );

    fflush(stdout);
    fflush(stderr);

#if !defined(NO_SETMODE_SUPPORT)

#if defined(_WIN32) || defined(OS2_OS)
    if ( oldstdoutmode != -1 )
        oldstdoutmode = setmode( fileno(stdout), oldstdoutmode );
    if ( oldstderrmode != -1 )
        oldstderrmode = setmode( fileno(stderr), oldstderrmode );
#endif

#endif

    TidyDocFree( doc, out );
    return status;
}

int         tidyDocSaveString( TidyDocImpl* doc, tmbstr buffer, uint* buflen )
{
    uint outenc = cfg( doc, TidyOutCharEncoding );
    uint nl = cfg( doc, TidyNewline );
    TidyBuffer outbuf;
    StreamOut* out;
    int status;

    tidyBufInitWithAllocator( &outbuf, doc->allocator );
    out = TY_(BufferOutput)( doc, &outbuf, outenc, nl );
    status = tidyDocSaveStream( doc, out );

    if ( outbuf.size > *buflen )
        status = -ENOMEM;
    else
        memcpy( buffer, outbuf.bp, outbuf.size );

    *buflen = outbuf.size;
    tidyBufFree( &outbuf );
    TidyDocFree( doc, out );
    return status;
}

int         tidyDocSaveBuffer( TidyDocImpl* doc, TidyBuffer* outbuf )
{
    int status = -EINVAL;
    if ( outbuf )
    {
        uint outenc = cfg( doc, TidyOutCharEncoding );
        uint nl = cfg( doc, TidyNewline );
        StreamOut* out = TY_(BufferOutput)( doc, outbuf, outenc, nl );

        status = tidyDocSaveStream( doc, out );
        TidyDocFree( doc, out );
    }
    return status;
}

int         tidyDocSaveSink( TidyDocImpl* doc, TidyOutputSink* sink )
{
    uint outenc = cfg( doc, TidyOutCharEncoding );
    uint nl = cfg( doc, TidyNewline );
    StreamOut* out = TY_(UserOutput)( doc, sink, outenc, nl );
    int status = tidyDocSaveStream( doc, out );
    TidyDocFree( doc, out );
    return status;
}

int         tidyDocStatus( TidyDocImpl* doc )
{
    if ( doc->errors > 0 )
        return 2;
    if ( doc->warnings > 0 || doc->accessErrors > 0 )
        return 1;
    return 0;
}



int TIDY_CALL        tidyCleanAndRepair( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
      return tidyDocCleanAndRepair( impl );
    return -EINVAL;
}

int TIDY_CALL        tidyRunDiagnostics( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl )
      return tidyDocRunDiagnostics( impl );
    return -EINVAL;
}

int TIDY_CALL        tidyReportDoctype( TidyDoc tdoc )
{
    int iret = -EINVAL;
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    if ( impl ) {
      tidyDocReportDoctype( impl );
      iret = 0;
    }
    return iret;
}

/* Workhorse functions.
**
** Parse requires input source, all input config items
** and diagnostic sink to have all been set before calling.
**
** Emit likewise requires that document sink and all
** pretty printing options have been set.
*/
static ctmbstr integrity = "\nPanic - tree has lost its integrity\n";

int         TY_(DocParseStream)( TidyDocImpl* doc, StreamIn* in )
{
    Bool xmlIn = cfgBool( doc, TidyXmlTags );
    int bomEnc;

    assert( doc != NULL && in != NULL );
    assert( doc->docIn == NULL );
    doc->docIn = in;

    TY_(ResetTags)(doc);    /* reset table to html5 mode */
    TY_(TakeConfigSnapshot)( doc );    /* Save config state */
    TY_(FreeAnchors)( doc );

    TY_(FreeNode)(doc, &doc->root);
    TidyClearMemory(&doc->root, sizeof(Node));

    if (doc->givenDoctype)
        TidyDocFree(doc, doc->givenDoctype);
    /*\ 
     *  Issue #186 - Now FreeNode depend on the doctype, so the lexer is needed
     *  to determine which hash is to be used, so free it last.
    \*/
    TY_(FreeLexer)( doc );
    doc->givenDoctype = NULL;

    doc->lexer = TY_(NewLexer)( doc );
    /* doc->lexer->root = &doc->root; */
    doc->root.line = doc->lexer->lines;
    doc->root.column = doc->lexer->columns;
    doc->inputHadBOM = no;

    bomEnc = TY_(ReadBOMEncoding)(in);

    if (bomEnc != -1)
    {
        in->encoding = bomEnc;
        TY_(SetOptionInt)(doc, TidyInCharEncoding, bomEnc);
    }

#ifdef TIDY_WIN32_MLANG_SUPPORT
    if (in->encoding > WIN32MLANG)
        TY_(Win32MLangInitInputTranscoder)(in, in->encoding);
#endif /* TIDY_WIN32_MLANG_SUPPORT */

    /* Tidy doesn't alter the doctype for generic XML docs */
    if ( xmlIn )
    {
        TY_(ParseXMLDocument)( doc );
        if ( !TY_(CheckNodeIntegrity)( &doc->root ) )
            TidyPanic( doc->allocator, integrity );
    }
    else
    {
        doc->warnings = 0;
        TY_(ParseDocument)( doc );
        if ( !TY_(CheckNodeIntegrity)( &doc->root ) )
            TidyPanic( doc->allocator, integrity );
    }

#ifdef TIDY_WIN32_MLANG_SUPPORT
    TY_(Win32MLangUninitInputTranscoder)(in);
#endif /* TIDY_WIN32_MLANG_SUPPORT */

    doc->docIn = NULL;
    return tidyDocStatus( doc );
}

int         tidyDocRunDiagnostics( TidyDocImpl* doc )
{
    Bool quiet = cfgBool( doc, TidyQuiet );
    Bool force = cfgBool( doc, TidyForceOutput );

    if ( !quiet )
    {

        TY_(ReportMarkupVersion)( doc );
        TY_(ReportNumWarnings)( doc );
    }

    if ( doc->errors > 0 && !force )
        TY_(NeedsAuthorIntervention)( doc );

     return tidyDocStatus( doc );
}

void         tidyDocReportDoctype( TidyDocImpl* doc )
{
        TY_(ReportMarkupVersion)( doc );
}


/* ######################################################################################
   HTML5 STUFF
 */
#if !defined(NDEBUG) && defined(_MSC_VER)
extern void show_not_html5(void);
/* -----------------------------
List tags that do not have version HTML5 (HT50|XH50)

acronym applet basefont big center dir font frame frameset isindex
listing noframes plaintext rb rbc rtc strike tt xmp nextid
align bgsound blink comment ilayer layer marquee multicol nobr noembed
nolayer nosave server servlet spacer

Listed total 35 tags that do not have version 393216
   ------------------------------ */

static void list_not_html5(void)
{
    static Bool done_list = no;
    if (done_list == no) {
        done_list = yes;
        show_not_html5();
    }
}
#endif

/* What about <blink>, <s> stike-through, <u> underline */
static struct _html5Info
{
    const char *tag;
    uint id;
} const html5Info[] = {
    {"acronym", TidyTag_ACRONYM},
    {"applet", TidyTag_APPLET  },
    {"basefont",TidyTag_BASEFONT },
    { "big", TidyTag_BIG },
    { "center", TidyTag_CENTER },
    { "dir", TidyTag_DIR },
    { "font", TidyTag_FONT },
    { "frame", TidyTag_FRAME},
    { "frameset", TidyTag_FRAMESET},
    { "noframes", TidyTag_NOFRAMES },
    { "strike", TidyTag_STRIKE },
    { "tt", TidyTag_TT },
    { 0, 0 }
};
Bool inRemovedInfo( uint tid )
{
    int i;
    for (i = 0; ; i++) {
        if (html5Info[i].tag == 0)
            break;
        if (html5Info[i].id == tid)
            return yes;
    }
    return no;
}

static Bool BadBody5( Node* node )
{
    if (TY_(AttrGetById)(node, TidyAttr_BACKGROUND) ||
        TY_(AttrGetById)(node, TidyAttr_BGCOLOR)    ||
        TY_(AttrGetById)(node, TidyAttr_TEXT)       ||
        TY_(AttrGetById)(node, TidyAttr_LINK)       ||
        TY_(AttrGetById)(node, TidyAttr_VLINK)      ||
        TY_(AttrGetById)(node, TidyAttr_ALINK))
    {
        return yes;
    }
    return no;
}

static Bool nodeHasAlignAttr( Node *node )
{
    /* #define attrIsALIGN(av) AttrIsId( av, TidyAttr_ALIGN  ) */
    AttVal* av;
    for ( av = node->attributes; av != NULL; av = av->next ) {
        if (attrIsALIGN(av))
            return yes;
    }
    return no;
}

/* see http://www.whatwg.org/specs/web-apps/current-work/multipage/obsolete.html#obsolete */

void TY_(CheckHTML5)( TidyDocImpl* doc, Node* node )
{
    /* Lexer* lexer = doc->lexer; */
    Bool clean = cfgBool( doc, TidyMakeClean );
    Node* body = TY_(FindBody)( doc );
    Bool warn = yes;    /* should this be a warning, error, or report??? */
#if !defined(NDEBUG) && defined(_MSC_VER)
//    list_not_html5();
#endif
    while (node)
    {
        if ( nodeHasAlignAttr( node ) ) {
            /*\
             * Is this for ALL elements that accept an 'align' attribute, or should
             * this be a sub-set test
            \*/
            TY_(ReportWarning)(doc, node, node, BAD_ALIGN_HTML5);
        }
        if ( node == body ) {
            if ( BadBody5(body) ) {
                /* perhaps need a new/different warning for this, like
                 * The background 'attribute" on the body element is obsolete. Use CSS instead.
                 * but how to pass an attribute name to be embedded in the message.
                \*/
                TY_(ReportWarning)(doc, node, body, BAD_BODY_HTML5);
            }
        } else
        if ( nodeIsACRONYM(node) ) {
            if (clean) {
                /* replace with 'abbr' with warning to that effect 
                 * maybe should use static void RenameElem( TidyDocImpl* doc, Node* node, TidyTagId tid )
                 */
                TY_(CoerceNode)(doc, node, TidyTag_ABBR, warn, no);
            } else {
                /* sadly, this stops writing of the tidied document, unless 'forced'
                   TY_(ReportError)(doc, node, node, REMOVED_HTML5); 
                   so go back to a 'warning' for now...
                */
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
            }
        } else 
        if ( nodeIsAPPLET(node) ) {
            if (clean) {
                /* replace with 'object' with warning to that effect 
                 * maybe should use static void RenameElem( TidyDocImpl* doc, Node* node, TidyTagId tid )
                 */
                TY_(CoerceNode)(doc, node, TidyTag_OBJECT, warn, no);
            } else {
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
            }
        } else
        if ( nodeIsBASEFONT(node) ) {
            /*\ 
             * basefont: CSS equivalen 'font-size', 'font-family' and 'color' on body or class on each subsequent element
             * Difficult - If it is the first body element, then could consider adding that
             *  to the <body> as a whole, else could perhaps apply it to all subsequent element.
             *  But also in consideration is the fact that it was NOT supported in many browsers
             *  For now just report a warning
            \*/
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
        } else
        if ( nodeIsBIG(node) ) {
            /*\
             * big: CSS equivalent 'font-size:larger'
             * so could replace the <big> ... </big> with 
             * <span style="font-size: larger"> ... </span>
             * then replace <big> with <span>
             * Need to think about that...
             * Could use -
             *   TY_(AddStyleProperty)( doc, node, "font-size: larger" );
             *   TY_(CoerceNode)(doc, node, TidyTag_SPAN, no, no);
             * Alternatively generated a <style> but how to get the style name
             * TY_(AddAttribute)( doc, node, "class", "????" );
             * Also maybe need a specific message like
             * Element '%s' replaced with 'span' with a 'font-size: larger style attribute
             * maybe should use static void RenameElem( TidyDocImpl* doc, Node* node, TidyTagId tid )
             *
            \*/
            if (clean) {
                TY_(AddStyleProperty)( doc, node, "font-size: larger" );
                TY_(CoerceNode)(doc, node, TidyTag_SPAN, warn, no);
            } else {
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
            }
        } else
        if ( nodeIsCENTER(node) ) {
            /*\
             * center: CSS equivalent 'text-align:center'
             *  and 'margin-left:auto; margin-right:auto' on descendant blocks
             * Tidy already handles this if 'clean' by SILENTLY generating the <style>
             * and adding a <div class="c1"> around the elements.
             * see: static Bool Center2Div( TidyDocImpl* doc, Node *node, Node **pnode)
            \*/
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
        } else 
        if ( nodeIsDIR(node) ) {
            /*\
             *  dir: replace by <ul>
             *  Tidy already actions this and issues a warning
             *  Should this be CHANGED???
            \*/
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
        } else
        if ( nodeIsFONT(node) ) {
            /*\
             * Tidy already handles this -
             * If 'clean' replaced by CSS, else 
             * if is NOT clean, and doctype html5 then warnings issued
             * done in Bool Font2Span( TidyDocImpl* doc, Node *node, Node **pnode ) (I think?)
             *
            \*/
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
        } else
        if (( nodesIsFRAME(node) ) || ( nodeIsFRAMESET(node) ) || ( nodeIsNOFRAMES(node) )) {
            /*\
             * YOW: What to do here?????? Maybe <iframe>????
            \*/
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
        } else
        if ( nodeIsSTRIKE(node) ) {
            /*\
             * strike: CSS equivalent 'text-decoration:line-through'
             * maybe should use static void RenameElem( TidyDocImpl* doc, Node* node, TidyTagId tid )
            \*/
            if (clean) {
                TY_(AddStyleProperty)( doc, node, "text-decoration: line-through" );
                TY_(CoerceNode)(doc, node, TidyTag_SPAN, warn, no);
            } else {
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
            }
        } else
        if ( nodeIsTT(node) ) {
            /*\
             * tt: CSS equivalent 'font-family:monospace'
             * Tidy presently does nothing. Tidy5 issues a warning
             * But like the 'clean' <font> replacement this could also be replaced with CSS
             * maybe should use static void RenameElem( TidyDocImpl* doc, Node* node, TidyTagId tid )
             *
            \*/
            if (clean) {
                TY_(AddStyleProperty)( doc, node, "font-family: monospace" );
                TY_(CoerceNode)(doc, node, TidyTag_SPAN, warn, no);
            } else {
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
            }
        } else
        if (TY_(nodeIsElement)(node)) {
            if (node->tag) {
                if ((!(node->tag->versions & VERS_HTML5))||(inRemovedInfo(node->tag->id))) {
                    /* issue warning for elements like 'markquee' */
                    TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
                }
            }
        }

        if (node->content)
            TY_(CheckHTML5)( doc, node->content );

        node = node->next;
    }
}
/* END HTML5 STUFF
   ######################################################################################
 */

#if !defined(NDEBUG) && defined(_MSC_VER)
/* *** FOR DEBUG ONLY *** */
const char *dbg_get_lexer_type( void *vp )
{
    Node *node = (Node *)vp;
    switch ( node->type )
    {
    case RootNode:      return "Root";
    case DocTypeTag:    return "DocType";
    case CommentTag:    return "Comment";
    case ProcInsTag:    return "ProcIns";
    case TextNode:      return "Text";
    case StartTag:      return "StartTag";
    case EndTag:        return "EndTag";
    case StartEndTag:   return "StartEnd";
    case CDATATag:      return "CDATA";
    case SectionTag:    return "Section";
    case AspTag:        return "Asp";
    case JsteTag:       return "Jste";
    case PhpTag:        return "Php";
    case XmlDecl:       return "XmlDecl";
    }
    return "Uncased";
}

/* NOTE: THis matches the above lexer type, except when element has a name */
const char *dbg_get_element_name( void *vp )
{
    Node *node = (Node *)vp;
    switch ( node->type )
    {
    case TidyNode_Root:       return "Root";
    case TidyNode_DocType:    return "DocType";
    case TidyNode_Comment:    return "Comment";
    case TidyNode_ProcIns:    return "ProcIns";
    case TidyNode_Text:       return "Text";
    case TidyNode_CDATA:      return "CDATA";
    case TidyNode_Section:    return "Section";
    case TidyNode_Asp:        return "Asp";
    case TidyNode_Jste:       return "Jste";
    case TidyNode_Php:        return "Php";
    case TidyNode_XmlDecl:    return "XmlDecl";

    case TidyNode_Start:
    case TidyNode_End:
    case TidyNode_StartEnd:
    default:
        if (node->element)
            return node->element;
    }
    return "Unknown";
}

void dbg_show_node( TidyDocImpl* doc, Node *node, int caller, int indent )
{
    AttVal* av;
    Lexer* lexer = doc->lexer;
    ctmbstr call = "";
    ctmbstr name = dbg_get_element_name(node);
    ctmbstr type = dbg_get_lexer_type(node);
    ctmbstr impl = node->implicit ? "implicit" : "";
    switch ( caller )
    {
    case 1: call = "discard";   break;
    case 2: call = "trim";      break;
    case 3: call = "test";      break;
    }
    while (indent--)
        SPRTF(" ");
    if (strcmp(type,name))
        SPRTF("%s %s %s %s", type, name, impl, call );
    else
        SPRTF("%s %s %s", name, impl, call );
    if (lexer && (strcmp("Text",name) == 0)) {
        uint len = node->end - node->start;
        uint i;
        SPRTF(" (%d) '", len);
        if (len < 40) {
            /* show it all */
            for (i = node->start; i < node->end; i++) {
                SPRTF("%c", lexer->lexbuf[i]);
            }
        } else {
            /* partial display */
            uint max = 19;
            for (i = node->start; i < max; i++) {
                SPRTF("%c", lexer->lexbuf[i]);
            }
            SPRTF("...");
            i = node->end - 19;
            for (; i < node->end; i++) {
                SPRTF("%c", lexer->lexbuf[i]);
            }
        }
        SPRTF("'");
    }
    for (av = node->attributes; av; av = av->next) {
        name = av->attribute;
        if (name) {
            SPRTF(" %s",name);
            if (av->value) {
                SPRTF("=\"%s\"", av->value);
            }
        }
    }

    SPRTF("\n");
}

void dbg_show_all_nodes( TidyDocImpl* doc, Node *node, int indent )
{
    while (node)
    {
        dbg_show_node( doc, node, 0, indent );
        dbg_show_all_nodes( doc, node->content, indent + 1 );
        node = node->next;
    }
}

#endif

int         tidyDocCleanAndRepair( TidyDocImpl* doc )
{
    Bool word2K   = cfgBool( doc, TidyWord2000 );
    Bool logical  = cfgBool( doc, TidyLogicalEmphasis );
    Bool clean    = cfgBool( doc, TidyMakeClean );
    Bool gdoc     = cfgBool( doc, TidyGDocClean );
    Bool dropFont = cfgBool( doc, TidyDropFontTags );
    Bool htmlOut  = cfgBool( doc, TidyHtmlOut );
    Bool xmlOut   = cfgBool( doc, TidyXmlOut );
    Bool xhtmlOut = cfgBool( doc, TidyXhtmlOut );
    Bool xmlDecl  = cfgBool( doc, TidyXmlDecl );
    Bool tidyMark = cfgBool( doc, TidyMark );
    Bool tidyXmlTags = cfgBool( doc, TidyXmlTags );
    Bool wantNameAttr = cfgBool( doc, TidyAnchorAsName );
    Bool mergeEmphasis = cfgBool( doc, TidyMergeEmphasis );
    ctmbstr sdef = NULL;
    Node* node;

#if !defined(NDEBUG) && defined(_MSC_VER)
    SPRTF("All nodes BEFORE clean and repair\n");
    dbg_show_all_nodes( doc, &doc->root, 0  );
#endif
    if (tidyXmlTags)
       return tidyDocStatus( doc );

    /* simplifies <b><b> ... </b> ...</b> etc. */
    if ( mergeEmphasis )
        TY_(NestedEmphasis)( doc, &doc->root );

    /* cleans up <dir>indented text</dir> etc. */
    TY_(List2BQ)( doc, &doc->root );
    TY_(BQ2Div)( doc, &doc->root );

    /* replaces i by em and b by strong */
    if ( logical )
        TY_(EmFromI)( doc, &doc->root );

    if ( word2K && TY_(IsWord2000)(doc) )
    {
        /* prune Word2000's <![if ...]> ... <![endif]> */
        TY_(DropSections)( doc, &doc->root );

        /* drop style & class attributes and empty p, span elements */
        TY_(CleanWord2000)( doc, &doc->root );
        TY_(DropEmptyElements)(doc, &doc->root);
    }

    /* replaces presentational markup by style rules */
    if ( clean || dropFont )
        TY_(CleanDocument)( doc );

    /* clean up html exported by Google Docs */
    if ( gdoc )
        TY_(CleanGoogleDocument)( doc );

    /*  Move terminating <br /> tags from out of paragraphs  */
    /*!  Do we want to do this for all block-level elements?  */

    /* This is disabled due to http://tidy.sf.net/bug/681116 */
#if 0
    FixBrakes( doc, TY_(FindBody)( doc ));
#endif

    /*  Reconcile http-equiv meta element with output encoding  */
    if (cfg( doc, TidyOutCharEncoding) != RAW
#ifndef NO_NATIVE_ISO2022_SUPPORT
        && cfg( doc, TidyOutCharEncoding) != ISO2022
#endif
        )
        TY_(VerifyHTTPEquiv)( doc, TY_(FindHEAD)( doc ));

    if ( !TY_(CheckNodeIntegrity)( &doc->root ) )
        TidyPanic( doc->allocator, integrity );

    /* remember given doctype for reporting */
    node = TY_(FindDocType)(doc);
    sdef = tidyOptGetValue((TidyDoc)doc, TidyDoctype );
    if (!sdef)
        sdef = tidyOptGetCurrPick((TidyDoc) doc, TidyDoctypeMode );
    if (sdef && (strcmp(sdef,"html5") == 0)) {
        TY_(CheckHTML5)( doc, &doc->root );
    }
    if (node)
    {
        AttVal* fpi = TY_(GetAttrByName)(node, "PUBLIC");
        if (AttrHasValue(fpi))
        {
            if (doc->givenDoctype)
                TidyDocFree(doc, doc->givenDoctype);
            doc->givenDoctype = TY_(tmbstrdup)(doc->allocator,fpi->value);
        }
    }

    if ( doc->root.content )
    {
        /* If we had XHTML input but want HTML output */
        if ( htmlOut && doc->lexer->isvoyager )
        {
            Node* node = TY_(FindDocType)(doc);
            /* Remove reference, but do not free */
            if (node)
              TY_(RemoveNode)(node);
        }

        if (xhtmlOut && !htmlOut)
        {
            TY_(SetXHTMLDocType)(doc);
            TY_(FixAnchors)(doc, &doc->root, wantNameAttr, yes);
            TY_(FixXhtmlNamespace)(doc, yes);
            TY_(FixLanguageInformation)(doc, &doc->root, yes, yes);
        }
        else
        {
            TY_(FixDocType)(doc);
            TY_(FixAnchors)(doc, &doc->root, wantNameAttr, yes);
            TY_(FixXhtmlNamespace)(doc, no);
            TY_(FixLanguageInformation)(doc, &doc->root, no, yes);
        }

        if (tidyMark )
            TY_(AddGenerator)(doc);
    }

    /* ensure presence of initial <?xml version="1.0"?> */
    if ( xmlOut && xmlDecl )
        TY_(FixXmlDecl)( doc );

#if !defined(NDEBUG) && defined(_MSC_VER)
    SPRTF("All nodes AFTER clean and repair\n");
    dbg_show_all_nodes( doc, &doc->root, 0  );
#endif
    return tidyDocStatus( doc );
}

static
Bool showBodyOnly( TidyDocImpl* doc, TidyTriState bodyOnly )
{
    Node* node;

    switch( bodyOnly )
    {
    case TidyNoState:
        return no;
    case TidyYesState:
        return yes;
    default:
        node = TY_(FindBody)( doc );
        if (node && node->implicit )
            return yes;
    }
    return no;
}


int         tidyDocSaveStream( TidyDocImpl* doc, StreamOut* out )
{
    Bool showMarkup  = cfgBool( doc, TidyShowMarkup );
    Bool forceOutput = cfgBool( doc, TidyForceOutput );
#if SUPPORT_UTF16_ENCODINGS
    Bool outputBOM   = ( cfgAutoBool(doc, TidyOutputBOM) == TidyYesState );
    Bool smartBOM    = ( cfgAutoBool(doc, TidyOutputBOM) == TidyAutoState );
#endif
    Bool xmlOut      = cfgBool( doc, TidyXmlOut );
    Bool xhtmlOut    = cfgBool( doc, TidyXhtmlOut );
    TidyTriState bodyOnly    = cfgAutoBool( doc, TidyBodyOnly );

    Bool dropComments = cfgBool(doc, TidyHideComments);
    Bool makeClean    = cfgBool(doc, TidyMakeClean);
    Bool asciiChars   = cfgBool(doc, TidyAsciiChars);
    Bool makeBare     = cfgBool(doc, TidyMakeBare);
    Bool escapeCDATA  = cfgBool(doc, TidyEscapeCdata);
    Bool ppWithTabs   = cfgBool(doc, TidyPPrintTabs);
    TidyAttrSortStrategy sortAttrStrat = cfg(doc, TidySortAttributes);

    if (ppWithTabs)
        TY_(PPrintTabs)();
    else
        TY_(PPrintSpaces)();

    if (escapeCDATA)
        TY_(ConvertCDATANodes)(doc, &doc->root);

    if (dropComments)
        TY_(DropComments)(doc, &doc->root);

    if (makeClean)
    {
        /* noop */
        TY_(DropFontElements)(doc, &doc->root, NULL);
    }

    if ((makeClean && asciiChars) || makeBare)
        TY_(DowngradeTypography)(doc, &doc->root);

    if (makeBare)
        /* Note: no longer replaces &nbsp; in */
        /* attribute values / non-text tokens */
        TY_(NormalizeSpaces)(doc->lexer, &doc->root);
    else
        TY_(ReplacePreformattedSpaces)(doc, &doc->root);

    if ( sortAttrStrat != TidySortAttrNone )
        TY_(SortAttributes)(&doc->root, sortAttrStrat);

    if ( showMarkup && (doc->errors == 0 || forceOutput) )
    {
#if SUPPORT_UTF16_ENCODINGS
        /* Output a Byte Order Mark if required */
        if ( outputBOM || (doc->inputHadBOM && smartBOM) )
            TY_(outBOM)( out );
#endif

        /* No longer necessary. No DOCTYPE == HTML 3.2,
        ** which gives you only the basic character entities,
        ** which are safe in any browser.
        ** if ( !TY_(FindDocType)(doc) )
        **    TY_(SetOptionBool)( doc, TidyNumEntities, yes );
        */

        doc->docOut = out;
        if ( xmlOut && !xhtmlOut )
            TY_(PPrintXMLTree)( doc, NORMAL, 0, &doc->root );
        else if ( showBodyOnly( doc, bodyOnly ) )
            TY_(PrintBody)( doc );
        else
            TY_(PPrintTree)( doc, NORMAL, 0, &doc->root );

        TY_(PFlushLine)( doc, 0 );
        doc->docOut = NULL;
    }

    TY_(ResetConfigToSnapshot)( doc );
    return tidyDocStatus( doc );
}

/* Tree traversal functions
**
** The big issue here is the degree to which we should mimic
** a DOM and/or SAX nodes.
**
** Is it 100% possible (and, if so, how difficult is it) to
** emit SAX events from this API?  If SAX events are possible,
** is that 100% of data needed to build a DOM?
*/

TidyNode TIDY_CALL   tidyGetRoot( TidyDoc tdoc )
{
    TidyDocImpl* impl = tidyDocToImpl( tdoc );
    Node* node = NULL;
    if ( impl )
        node = &impl->root;
    return tidyImplToNode( node );
}

TidyNode TIDY_CALL   tidyGetHtml( TidyDoc tdoc )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  Node* node = NULL;
  if ( impl )
      node = TY_(FindHTML)( impl );
  return tidyImplToNode( node );
}

TidyNode TIDY_CALL    tidyGetHead( TidyDoc tdoc )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  Node* node = NULL;
  if ( impl )
      node = TY_(FindHEAD)( impl );
  return tidyImplToNode( node );
}

TidyNode TIDY_CALL    tidyGetBody( TidyDoc tdoc )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  Node* node = NULL;
  if ( impl )
      node = TY_(FindBody)( impl );
  return tidyImplToNode( node );
}

/* parent / child */
TidyNode TIDY_CALL    tidyGetParent( TidyNode tnod )
{
  Node* nimp = tidyNodeToImpl( tnod );
  return tidyImplToNode( nimp->parent );
}
TidyNode TIDY_CALL    tidyGetChild( TidyNode tnod )
{
  Node* nimp = tidyNodeToImpl( tnod );
  return tidyImplToNode( nimp->content );
}

/* remove a node */
TidyNode TIDY_CALL    tidyDiscardElement( TidyDoc tdoc, TidyNode tnod )
{
  TidyDocImpl* doc = tidyDocToImpl( tdoc );
  Node* nimp = tidyNodeToImpl( tnod );
  Node* next = TY_(DiscardElement)( doc, nimp );
  return tidyImplToNode( next );
}

/* siblings */
TidyNode TIDY_CALL    tidyGetNext( TidyNode tnod )
{
  Node* nimp = tidyNodeToImpl( tnod );
  return tidyImplToNode( nimp->next );
}
TidyNode TIDY_CALL    tidyGetPrev( TidyNode tnod )
{
  Node* nimp = tidyNodeToImpl( tnod );
  return tidyImplToNode( nimp->prev );
}

/* Node info */
TidyNodeType TIDY_CALL tidyNodeGetType( TidyNode tnod )
{
  Node* nimp = tidyNodeToImpl( tnod );
  TidyNodeType ntyp = TidyNode_Root;
  if ( nimp )
    ntyp = (TidyNodeType) nimp->type;
  return ntyp;
}

uint TIDY_CALL tidyNodeLine( TidyNode tnod )
{
  Node* nimp = tidyNodeToImpl( tnod );
  uint line = 0;
  if ( nimp )
    line = nimp->line;
  return line;
}
uint TIDY_CALL tidyNodeColumn( TidyNode tnod )
{
  Node* nimp = tidyNodeToImpl( tnod );
  uint col = 0;
  if ( nimp )
    col = nimp->column;
  return col;
}

ctmbstr TIDY_CALL        tidyNodeGetName( TidyNode tnod )
{
  Node* nimp = tidyNodeToImpl( tnod );
  ctmbstr nnam = NULL;
  if ( nimp )
    nnam = nimp->element;
  return nnam;
}


Bool TIDY_CALL  tidyNodeHasText( TidyDoc tdoc, TidyNode tnod )
{
  TidyDocImpl* doc = tidyDocToImpl( tdoc );
  if ( doc )
      return TY_(nodeHasText)( doc, tidyNodeToImpl(tnod) );
  return no;
}


Bool TIDY_CALL  tidyNodeGetText( TidyDoc tdoc, TidyNode tnod, TidyBuffer* outbuf )
{
  TidyDocImpl* doc = tidyDocToImpl( tdoc );
  Node* nimp = tidyNodeToImpl( tnod );
  if ( doc && nimp && outbuf )
  {
      uint outenc     = cfg( doc, TidyOutCharEncoding );
      uint nl         = cfg( doc, TidyNewline );
      StreamOut* out  = TY_(BufferOutput)( doc, outbuf, outenc, nl );
      Bool xmlOut     = cfgBool( doc, TidyXmlOut );
      Bool xhtmlOut   = cfgBool( doc, TidyXhtmlOut );

      doc->docOut = out;
      if ( xmlOut && !xhtmlOut )
          TY_(PPrintXMLTree)( doc, NORMAL, 0, nimp );
      else
          TY_(PPrintTree)( doc, NORMAL, 0, nimp );

      TY_(PFlushLine)( doc, 0 );
      doc->docOut = NULL;

      TidyDocFree( doc, out );
      return yes;
  }
  return no;
}

Bool TIDY_CALL tidyNodeGetValue( TidyDoc tdoc, TidyNode tnod, TidyBuffer* buf )
{
    TidyDocImpl *doc = tidyDocToImpl( tdoc );
    Node *node = tidyNodeToImpl( tnod );
    if ( doc == NULL || node == NULL || buf == NULL )
        return no;

    switch( node->type ) {
    case TextNode:
    case CDATATag:
    case CommentTag:
    case ProcInsTag:
    case SectionTag:
    case AspTag:
    case JsteTag:
    case PhpTag:
    {
        tidyBufClear( buf );
        tidyBufAppend( buf, doc->lexer->lexbuf + node->start,
                       node->end - node->start );
        break;
    }
    default:
        /* The node doesn't have a value */
        return no;
    }

    return yes;
}

Bool TIDY_CALL tidyNodeIsProp( TidyDoc ARG_UNUSED(tdoc), TidyNode tnod )
{
  Node* nimp = tidyNodeToImpl( tnod );
  Bool isProprietary = yes;
  if ( nimp )
  {
    switch ( nimp->type )
    {
    case RootNode:
    case DocTypeTag:
    case CommentTag:
    case XmlDecl:
    case ProcInsTag:
    case TextNode:
    case CDATATag:
        isProprietary = no;
        break;

    case SectionTag:
    case AspTag:
    case JsteTag:
    case PhpTag:
        isProprietary = yes;
        break;

    case StartTag:
    case EndTag:
    case StartEndTag:
        isProprietary = ( nimp->tag
                          ? (nimp->tag->versions&VERS_PROPRIETARY)!=0
                          : yes );
        break;
    }
  }
  return isProprietary;
}

TidyTagId TIDY_CALL tidyNodeGetId(TidyNode tnod)
{
    Node* nimp = tidyNodeToImpl(tnod);

    TidyTagId tagId = TidyTag_UNKNOWN;
    if (nimp && nimp->tag)
        tagId = nimp->tag->id;

    return tagId;
}


/* Null for non-element nodes and all pure HTML
cmbstr       tidyNodeNsLocal( TidyNode tnod )
{
}
cmbstr       tidyNodeNsPrefix( TidyNode tnod )
{
}
cmbstr       tidyNodeNsUri( TidyNode tnod )
{
}
*/

/* Iterate over attribute values */
TidyAttr TIDY_CALL   tidyAttrFirst( TidyNode tnod )
{
  Node* nimp = tidyNodeToImpl( tnod );
  AttVal* attval = NULL;
  if ( nimp )
    attval = nimp->attributes;
  return tidyImplToAttr( attval );
}
TidyAttr TIDY_CALL    tidyAttrNext( TidyAttr tattr )
{
  AttVal* attval = tidyAttrToImpl( tattr );
  AttVal* nxtval = NULL;
  if ( attval )
    nxtval = attval->next;
  return tidyImplToAttr( nxtval );
}

ctmbstr TIDY_CALL       tidyAttrName( TidyAttr tattr )
{
  AttVal* attval = tidyAttrToImpl( tattr );
  ctmbstr anam = NULL;
  if ( attval )
    anam = attval->attribute;
  return anam;
}
ctmbstr TIDY_CALL       tidyAttrValue( TidyAttr tattr )
{
  AttVal* attval = tidyAttrToImpl( tattr );
  ctmbstr aval = NULL;
  if ( attval )
    aval = attval->value;
  return aval;
}

void TIDY_CALL           tidyAttrDiscard( TidyDoc tdoc, TidyNode tnod, TidyAttr tattr )
{
  TidyDocImpl* impl = tidyDocToImpl( tdoc );
  Node* nimp = tidyNodeToImpl( tnod );
  AttVal* attval = tidyAttrToImpl( tattr );
  TY_(RemoveAttribute)( impl, nimp, attval );
}

/* Null for pure HTML
ctmbstr       tidyAttrNsLocal( TidyAttr tattr )
{
}
ctmbstr       tidyAttrNsPrefix( TidyAttr tattr )
{
}
ctmbstr       tidyAttrNsUri( TidyAttr tattr )
{
}
*/

TidyAttrId TIDY_CALL tidyAttrGetId( TidyAttr tattr )
{
  AttVal* attval = tidyAttrToImpl( tattr );
  TidyAttrId attrId = TidyAttr_UNKNOWN;
  if ( attval && attval->dict )
    attrId = attval->dict->id;
  return attrId;
}
Bool TIDY_CALL tidyAttrIsProp( TidyAttr tattr )
{
  /*
    You cannot tell whether an attribute is proprietary without
    knowing on which element it occurs in the general case, but
    this function cannot know the element. As a result, it does
    not work anymore. Do not use.
  */
  return no;
}

/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
