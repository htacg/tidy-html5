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
static TidyDoc tidyDocCreate( TidyAllocator *allocator );
static void         tidyDocRelease( TidyDoc impl );

static int          tidyDocStatus( TidyDoc impl );

/* Parse Markup */
static int          tidyDocParseFile( TidyDoc impl, ctmbstr htmlfil );
static int          tidyDocParseStdin( TidyDoc impl );
static int          tidyDocParseString( TidyDoc impl, ctmbstr content );
static int          tidyDocParseBuffer( TidyDoc impl, TidyBuffer* inbuf );
static int          tidyDocParseSource( TidyDoc impl, TidyInputSource* docIn );


/* Execute post-parse diagnostics and cleanup.
** Note, the order is important.  You will get different
** results from the diagnostics depending on if they are run
** pre-or-post repair.
*/
static int          tidyDocRunDiagnostics( TidyDoc doc );
static void         tidyDocReportDoctype( TidyDoc doc );
static int          tidyDocCleanAndRepair( TidyDoc doc );


/* Save cleaned up file to file/buffer/sink */
static int          tidyDocSaveFile( TidyDoc impl, ctmbstr htmlfil );
static int          tidyDocSaveStdout( TidyDoc impl );
static int          tidyDocSaveString( TidyDoc impl, tmbstr buffer, uint* buflen );
static int          tidyDocSaveBuffer( TidyDoc impl, TidyBuffer* outbuf );
static int          tidyDocSaveSink( TidyDoc impl, TidyOutputSink* docOut );
static int          tidyDocSaveStream( TidyDoc impl, StreamOut* out );

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
  return tidyDocCreate( &TY_(g_default_allocator) );
}

TidyDoc TIDY_CALL tidyCreateWithAllocator( TidyAllocator *allocator )
{
  return tidyDocCreate( allocator );
}

void TIDY_CALL          tidyRelease( TidyDoc tdoc )
{
  tidyDocRelease( tdoc );
}

TidyDoc tidyDocCreate( TidyAllocator *allocator )
{
    TidyDoc doc = (TidyDoc)TidyAlloc( allocator, sizeof(struct _TidyDoc) );
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

void          tidyDocRelease( TidyDoc doc )
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
        TidyClearMemory(&doc->root, sizeof(struct _TidyNode));

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
  if ( tdoc )
    tdoc->appData = appData;
}
void* TIDY_CALL       tidyGetAppData( TidyDoc tdoc )
{
  if ( tdoc )
    return tdoc->appData;
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
  if ( tdoc )
  {
    tdoc->pOptCallback = pOptCallback;
    return yes;
  }
  return no;
}


int TIDY_CALL     tidyLoadConfig( TidyDoc tdoc, ctmbstr cfgfil )
{
    if ( tdoc )
        return TY_(ParseConfigFile)( tdoc, cfgfil );
    return -EINVAL;
}

int TIDY_CALL     tidyLoadConfigEnc( TidyDoc tdoc, ctmbstr cfgfil, ctmbstr charenc )
{
    if ( tdoc )
        return TY_(ParseConfigFileEnc)( tdoc, cfgfil, charenc );
    return -EINVAL;
}

int TIDY_CALL         tidySetCharEncoding( TidyDoc tdoc, ctmbstr encnam )
{
    if ( tdoc )
    {
        int enc = TY_(CharEncodingId)( tdoc, encnam );
        if ( enc >= 0 && TY_(AdjustCharEncoding)(tdoc, enc) )
            return 0;

        TY_(ReportBadArgument)( tdoc, "char-encoding" );
    }
    return -EINVAL;
}

int TIDY_CALL           tidySetInCharEncoding( TidyDoc tdoc, ctmbstr encnam )
{
    if ( tdoc )
    {
        int enc = TY_(CharEncodingId)( tdoc, encnam );
        if ( enc >= 0 && TY_(SetOptionInt)( tdoc, TidyInCharEncoding, enc ) )
            return 0;

        TY_(ReportBadArgument)( tdoc, "in-char-encoding" );
    }
    return -EINVAL;
}

int TIDY_CALL           tidySetOutCharEncoding( TidyDoc tdoc, ctmbstr encnam )
{
    if ( tdoc )
    {
        int enc = TY_(CharEncodingId)( tdoc, encnam );
        if ( enc >= 0 && TY_(SetOptionInt)( tdoc, TidyOutCharEncoding, enc ) )
            return 0;

        TY_(ReportBadArgument)( tdoc, "out-char-encoding" );
    }
    return -EINVAL;
}

TidyOptionId TIDY_CALL tidyOptGetIdForName( ctmbstr optnam )
{
    TidyOption option = TY_(lookupOption)( optnam );
    if ( option )
        return option->id;
    return N_TIDY_OPTIONS;  /* Error */
}

TidyIterator TIDY_CALL  tidyGetOptionList( TidyDoc tdoc )
{
    if ( tdoc )
        return TY_(getOptionList)( tdoc );
    return (TidyIterator) -1;
}

TidyOption TIDY_CALL    tidyGetNextOption( TidyDoc tdoc, TidyIterator* pos )
{
    TidyOption option = NULL;
    if ( tdoc )
        option = TY_(getNextOption)( tdoc, pos );
    else if ( pos )
        *pos = 0;
    return option;
}


TidyOption TIDY_CALL    tidyGetOption( TidyDoc ARG_UNUSED(tdoc), TidyOptionId optId )
{
    return TY_(getOption)( optId );
}
TidyOption TIDY_CALL    tidyGetOptionByName( TidyDoc ARG_UNUSED(doc), ctmbstr optnam )
{
    return TY_(lookupOption)( optnam );
}

TidyOptionId TIDY_CALL  tidyOptGetId( TidyOption topt )
{
    if ( topt )
        return topt->id;
    return N_TIDY_OPTIONS;
}
ctmbstr TIDY_CALL       tidyOptGetName( TidyOption topt )
{
    if ( topt )
        return topt->name;
    return NULL;
}
TidyOptionType TIDY_CALL tidyOptGetType( TidyOption topt )
{
    if ( topt )
        return topt->type;
    return (TidyOptionType) -1;
}
TidyConfigCategory TIDY_CALL tidyOptGetCategory( TidyOption topt )
{
    if ( topt )
        return topt->category;
    return (TidyConfigCategory) -1;
}
ctmbstr TIDY_CALL       tidyOptGetDefault( TidyOption topt )
{
    if ( topt && topt->type == TidyString )
        return topt->pdflt; /* Issue #306 - fix an old typo hidden by a cast! */
    return NULL;
}
ulong TIDY_CALL          tidyOptGetDefaultInt( TidyOption topt )
{
    if ( topt && topt->type != TidyString )
        return topt->dflt;
    return ~0U;
}
Bool TIDY_CALL          tidyOptGetDefaultBool( TidyOption topt )
{
    if ( topt && topt->type != TidyString )
        return ( topt->dflt ? yes : no );
    return no;
}
Bool TIDY_CALL          tidyOptIsReadOnly( TidyOption topt )
{
    if ( topt  )
        return ( topt->parser == NULL );
    return yes;
}


TidyIterator TIDY_CALL  tidyOptGetPickList( TidyOption topt )
{
    if ( topt )
      return TY_(getOptionPickList)( topt );
    return (TidyIterator) -1;
}
ctmbstr TIDY_CALL       tidyOptGetNextPick( TidyOption topt, TidyIterator* pos )
{
    if ( topt )
        return TY_(getNextOptionPick)( topt, pos );
    return NULL;
}


ctmbstr TIDY_CALL       tidyOptGetValue( TidyDoc tdoc, TidyOptionId optId )
{
  ctmbstr optval = NULL;
  if ( tdoc )
    optval = cfgStr( tdoc, optId );
  return optval;
}
Bool TIDY_CALL        tidyOptSetValue( TidyDoc tdoc, TidyOptionId optId, ctmbstr val )
{
  if ( tdoc )
    return TY_(ParseConfigValue)( tdoc, optId, val );
  return no;
}
Bool TIDY_CALL        tidyOptParseValue( TidyDoc tdoc, ctmbstr optnam, ctmbstr val )
{
  if ( tdoc )
    return TY_(ParseConfigOption)( tdoc, optnam, val );
  return no;
}

ulong TIDY_CALL        tidyOptGetInt( TidyDoc tdoc, TidyOptionId optId )
{
    ulong opti = 0;
    if ( tdoc )
        opti = cfg( tdoc, optId );
    return opti;
}

Bool TIDY_CALL        tidyOptSetInt( TidyDoc tdoc, TidyOptionId optId, ulong val )
{
    if ( tdoc )
        return TY_(SetOptionInt)( tdoc, optId, val );
    return no;
}

Bool TIDY_CALL         tidyOptGetBool( TidyDoc tdoc, TidyOptionId optId )
{
    Bool optb = no;
    if ( tdoc )
    {
        TidyOption option = TY_(getOption)( optId );
        if ( option )
        {
            optb = cfgBool( tdoc, optId );
        }
    }
    return optb;
}

Bool TIDY_CALL        tidyOptSetBool( TidyDoc tdoc, TidyOptionId optId, Bool val )
{
    if ( tdoc )
        return TY_(SetOptionBool)( tdoc, optId, val );
    return no;
}

ctmbstr TIDY_CALL       tidyOptGetEncName( TidyDoc tdoc, TidyOptionId optId )
{
  uint enc = tidyOptGetInt( tdoc, optId );
  return TY_(CharEncodingOptName)( enc );
}

ctmbstr TIDY_CALL       tidyOptGetCurrPick( TidyDoc tdoc, TidyOptionId optId )
{
    TidyOption option = TY_(getOption)( optId );
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
    TidyIterator declIter = 0;
    if ( tdoc )
        declIter = TY_(GetDeclaredTagList)( tdoc );
    return declIter;
}

ctmbstr TIDY_CALL       tidyOptGetNextDeclTag( TidyDoc tdoc, TidyOptionId optId,
                                     TidyIterator* iter )
{
    ctmbstr tagnam = NULL;
    if ( tdoc )
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
            tagnam = TY_(GetNextDeclaredTag)( tdoc, tagtyp, iter );
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
    if ( tdoc )
        return TY_(SaveConfigFile)( tdoc, cfgfil );
    return -EINVAL;
}

int TIDY_CALL tidyOptSaveSink( TidyDoc tdoc, TidyOutputSink* sink )
{
    if ( tdoc )
        return TY_(SaveConfigSink)( tdoc, sink );
    return -EINVAL;
}

Bool TIDY_CALL tidyOptSnapshot( TidyDoc tdoc )
{
    if ( tdoc )
    {
        TY_(TakeConfigSnapshot)( tdoc );
        return yes;
    }
    return no;
}
Bool TIDY_CALL tidyOptResetToSnapshot( TidyDoc tdoc )
{
    if ( tdoc )
    {
        TY_(ResetConfigToSnapshot)( tdoc );
        return yes;
    }
    return no;
}
Bool TIDY_CALL tidyOptResetAllToDefault( TidyDoc tdoc )
{
    if ( tdoc )
    {
        TY_(ResetConfigToDefault)( tdoc );
        return yes;
    }
    return no;
}

Bool TIDY_CALL tidyOptResetToDefault( TidyDoc tdoc, TidyOptionId optId )
{
    if ( tdoc )
        return TY_(ResetOptionToDefault)( tdoc, optId );
    return no;
}

Bool TIDY_CALL tidyOptDiffThanDefault( TidyDoc tdoc )
{
    if ( tdoc )
        return TY_(ConfigDiffThanDefault)( tdoc );
    return no;
}
Bool TIDY_CALL          tidyOptDiffThanSnapshot( TidyDoc tdoc )
{
    if ( tdoc )
        return TY_(ConfigDiffThanSnapshot)( tdoc );
    return no;
}

Bool TIDY_CALL tidyOptCopyConfig( TidyDoc to, TidyDoc from )
{
    if ( to && from )
    {
        TY_(CopyConfig)( to, from );
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
  if ( tdoc )
  {
    tdoc->mssgFilt = filt;
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
  if ( tdoc )
  {
    tdoc->mssgFilt2 = filt;
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
  if ( tdoc )
  {
    tdoc->mssgFilt3 = filt;
    return yes;
  }
  return no;
}

#if 0   /* Not yet */
int         tidySetContentOutputSink( TidyDoc tdoc, TidyOutputSink* outp )
{
  if ( tdoc )
  {
    tdoc->docOut = outp;
    return 0;
  }
  return -EINVAL;
}
int         tidySetDiagnosticOutputSink( TidyDoc tdoc, TidyOutputSink* outp )
{
  if ( tdoc )
  {
    tdoc->msgOut = outp;
    return 0;
  }
  return -EINVAL;
}


/* Library helpers
*/
cmbstr       tidyLookupMessage( TidyDoc tdoc, int errorNo )
{
  cmbstr mssg = NULL;
  if ( tdoc )
    mssg = tidyMessage_Lookup( tdoc->messages, errorNo );
  return mssg;
}
#endif


FILE* TIDY_CALL   tidySetErrorFile( TidyDoc tdoc, ctmbstr errfilnam )
{
    if ( tdoc )
    {
        FILE* errout = fopen( errfilnam, "wb" );
        if ( errout )
        {
            uint outenc = cfg( tdoc, TidyOutCharEncoding );
            uint nl = cfg( tdoc, TidyNewline );
            TY_(ReleaseStreamOut)( tdoc, tdoc->errout );
            tdoc->errout = TY_(FileOutput)( tdoc, errout, outenc, nl );
            return errout;
        }
        else /* Emit message to current error sink */
            TY_(FileError)( tdoc, errfilnam, TidyError );
    }
    return NULL;
}

int TIDY_CALL    tidySetErrorBuffer( TidyDoc tdoc, TidyBuffer* errbuf )
{
    if ( tdoc )
    {
        uint outenc = cfg( tdoc, TidyOutCharEncoding );
        uint nl = cfg( tdoc, TidyNewline );
        TY_(ReleaseStreamOut)( tdoc, tdoc->errout );
        tdoc->errout = TY_(BufferOutput)( tdoc, errbuf, outenc, nl );
        return ( tdoc->errout ? 0 : -ENOMEM );
    }
    return -EINVAL;
}

int TIDY_CALL    tidySetErrorSink( TidyDoc tdoc, TidyOutputSink* sink )
{
    if ( tdoc )
    {
        uint outenc = cfg( tdoc, TidyOutCharEncoding );
        uint nl = cfg( tdoc, TidyNewline );
        TY_(ReleaseStreamOut)( tdoc, tdoc->errout );
        tdoc->errout = TY_(UserOutput)( tdoc, sink, outenc, nl );
        return ( tdoc->errout ? 0 : -ENOMEM );
    }
    return -EINVAL;
}

/* Use TidyPPProgress to monitor the progress of the pretty printer.
 */
Bool TIDY_CALL        tidySetPrettyPrinterCallback(TidyDoc tdoc, TidyPPProgress callback)
{
    if ( tdoc )
    {
        tdoc->progressCallback = callback;
        return yes;
    }
    return no;
}


/* Document info */
int TIDY_CALL        tidyStatus( TidyDoc tdoc )
{
    int tidyStat = -EINVAL;
    if ( tdoc )
        tidyStat = tidyDocStatus( tdoc );
    return tidyStat;
}
int TIDY_CALL        tidyDetectedHtmlVersion( TidyDoc ARG_UNUSED(tdoc) )
{
    return 0;
}
Bool TIDY_CALL        tidyDetectedXhtml( TidyDoc ARG_UNUSED(tdoc) )
{
    return no;
}
Bool TIDY_CALL        tidyDetectedGenericXml( TidyDoc ARG_UNUSED(tdoc) )
{
    return no;
}

uint TIDY_CALL       tidyErrorCount( TidyDoc tdoc )
{
    uint count = 0xFFFFFFFF;
    if ( tdoc )
        count = tdoc->errors;
    return count;
}
uint TIDY_CALL       tidyWarningCount( TidyDoc tdoc )
{
    uint count = 0xFFFFFFFF;
    if ( tdoc )
        count = tdoc->warnings;
    return count;
}
uint TIDY_CALL       tidyAccessWarningCount( TidyDoc tdoc )
{
    uint count = 0xFFFFFFFF;
    if ( tdoc )
        count = tdoc->accessErrors;
    return count;
}
uint TIDY_CALL       tidyConfigErrorCount( TidyDoc tdoc )
{
    uint count = 0xFFFFFFFF;
    if ( tdoc )
        count = tdoc->optionErrors;
    return count;
}


/* Error reporting functions
*/
void TIDY_CALL         tidyErrorSummary( TidyDoc tdoc )
{
    if ( tdoc )
        TY_(ErrorSummary)( tdoc );
}
void TIDY_CALL         tidyGeneralInfo( TidyDoc tdoc )
{
    if ( tdoc )
        TY_(GeneralInfo)( tdoc );
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
int TIDY_CALL  tidyParseFile( TidyDoc doc, ctmbstr filnam )
{
    return tidyDocParseFile( doc, filnam );
}
int TIDY_CALL  tidyParseStdin( TidyDoc doc )
{
    return tidyDocParseStdin( doc );
}
int TIDY_CALL  tidyParseString( TidyDoc doc, ctmbstr content )
{
    return tidyDocParseString( doc, content );
}
int TIDY_CALL  tidyParseBuffer( TidyDoc doc, TidyBuffer* inbuf )
{
    return tidyDocParseBuffer( doc, inbuf );
}
int TIDY_CALL  tidyParseSource( TidyDoc doc, TidyInputSource* source )
{
    return tidyDocParseSource( doc, source );
}


int   tidyDocParseFile( TidyDoc doc, ctmbstr filnam )
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

int   tidyDocParseStdin( TidyDoc doc )
{
    StreamIn* in = TY_(FileInput)( doc, stdin, cfg( doc, TidyInCharEncoding ));
    int status = TY_(DocParseStream)( doc, in );
    TY_(freeStreamIn)(in);
    return status;
}

int   tidyDocParseBuffer( TidyDoc doc, TidyBuffer* inbuf )
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

int   tidyDocParseString( TidyDoc doc, ctmbstr content )
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

int   tidyDocParseSource( TidyDoc doc, TidyInputSource* source )
{
    StreamIn* in = TY_(UserInput)( doc, source, cfg( doc, TidyInCharEncoding ));
    int status = TY_(DocParseStream)( doc, in );
    TY_(freeStreamIn)(in);
    return status;
}


/* Print/save Functions
**
*/
int TIDY_CALL        tidySaveFile( TidyDoc doc, ctmbstr filnam )
{
    return tidyDocSaveFile( doc, filnam );
}
int TIDY_CALL        tidySaveStdout( TidyDoc doc )
{
    return tidyDocSaveStdout( doc );
}
int TIDY_CALL        tidySaveString( TidyDoc doc, tmbstr buffer, uint* buflen )
{
    return tidyDocSaveString( doc, buffer, buflen );
}
int TIDY_CALL        tidySaveBuffer( TidyDoc doc, TidyBuffer* outbuf )
{
    return tidyDocSaveBuffer( doc, outbuf );
}
int TIDY_CALL        tidySaveSink( TidyDoc doc, TidyOutputSink* sink )
{
    return tidyDocSaveSink( doc, sink );
}

int         tidyDocSaveFile( TidyDoc doc, ctmbstr filnam )
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

int         tidyDocSaveStdout( TidyDoc doc )
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

int         tidyDocSaveString( TidyDoc doc, tmbstr buffer, uint* buflen )
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

int         tidyDocSaveBuffer( TidyDoc doc, TidyBuffer* outbuf )
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

int         tidyDocSaveSink( TidyDoc doc, TidyOutputSink* sink )
{
    uint outenc = cfg( doc, TidyOutCharEncoding );
    uint nl = cfg( doc, TidyNewline );
    StreamOut* out = TY_(UserOutput)( doc, sink, outenc, nl );
    int status = tidyDocSaveStream( doc, out );
    TidyDocFree( doc, out );
    return status;
}

int         tidyDocStatus( TidyDoc doc )
{
    if ( doc->errors > 0 )
        return 2;
    if ( doc->warnings > 0 || doc->accessErrors > 0 )
        return 1;
    return 0;
}



int TIDY_CALL        tidyCleanAndRepair( TidyDoc tdoc )
{
    if ( tdoc )
      return tidyDocCleanAndRepair( tdoc );
    return -EINVAL;
}

int TIDY_CALL        tidyRunDiagnostics( TidyDoc tdoc )
{
    if ( tdoc )
      return tidyDocRunDiagnostics( tdoc );
    return -EINVAL;
}

int TIDY_CALL        tidyReportDoctype( TidyDoc tdoc )
{
    int iret = -EINVAL;
    if ( tdoc ) {
      tidyDocReportDoctype( tdoc );
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

int         TY_(DocParseStream)( TidyDoc doc, StreamIn* in )
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
    TidyClearMemory(&doc->root, sizeof(struct _TidyNode));

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

int         tidyDocRunDiagnostics( TidyDoc doc )
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

void         tidyDocReportDoctype( TidyDoc doc )
{
        TY_(ReportMarkupVersion)( doc );
}


/*****************************************************************************
 *  HTML5 STUFF
 *****************************************************************************/
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

/* Things that should not be in an HTML5 body. This is special for CheckHTML5(),
 and we might just want to remove CheckHTML5()'s output altogether and count
 on the default --strict-tags-attributes.
 */
static int BadBody5Attribs[] = {
    TidyAttr_BACKGROUND,
    TidyAttr_BGCOLOR,
    TidyAttr_TEXT,
    TidyAttr_LINK,
    TidyAttr_VLINK,
    TidyAttr_ALINK,
    TidyAttr_UNKNOWN /* Must be last! */
};

static Bool nodeHasAlignAttr( TidyNode node )
{
    /* #define attrIsALIGN(av) AttrIsId( av, TidyAttr_ALIGN  ) */
    TidyAttr av;
    for ( av = node->attributes; av != NULL; av = av->next ) {
        if (attrIsALIGN(av))
            return yes;
    }
    return no;
}

/*
 *  Perform special checks for HTML, even when we're not using the default
 *  option `--strict-tags-attributes yes`. This will ensure that HTML5 warning
 *  and error output is given regardless of the new option, and ensure that
 *  cleanup takes place. This provides mostly consistent Tidy behavior even with
 *  the introduction of this new option. Note that strings have changed, though,
 *  in order to maintain consistency with the `--strict-tags-attributes` 
 *  messages.
 *
 *  See also: http://www.whatwg.org/specs/web-apps/current-work/multipage/obsolete.html#obsolete
 */
void TY_(CheckHTML5)( TidyDoc doc, TidyNode node )
{
    Bool clean = cfgBool( doc, TidyMakeClean );
    Bool already_strict = cfgBool( doc, TidyStrictTagsAttr );
    TidyNode body = TY_(FindBody)( doc );
    Bool warn = yes;    /* should this be a warning, error, or report??? */
    TidyAttr attr = NULL;
    int i = 0;
#if !defined(NDEBUG) && defined(_MSC_VER)
    //    list_not_html5();
#endif
    while (node)
    {
        if ( nodeHasAlignAttr( node ) ) {
            /* @todo: Is this for ALL elements that accept an 'align' attribute,
             * or should this be a sub-set test?
             */

            /* We will only emit this message if `--strict-tags-attributes==no`;
             * otherwise if yes this message will be output during later
             * checking.
             */
            if ( !already_strict )
                TY_(ReportAttrError)(doc, node, TY_(AttrGetById)(node, TidyAttr_ALIGN), MISMATCHED_ATTRIBUTE_WARN);
        }
        if ( node == body ) {
            i = 0;
            /* We will only emit these messages if `--strict-tags-attributes==no`;
             * otherwise if yes these messages will be output during later
             * checking.
             */
            if ( !already_strict ) {
                while ( BadBody5Attribs[i] != TidyAttr_UNKNOWN ) {
                    attr = TY_(AttrGetById)(node, BadBody5Attribs[i]);
                    if ( attr )
                        TY_(ReportAttrError)(doc, node, attr , MISMATCHED_ATTRIBUTE_WARN);
                    i++;
                }
            }
        } else
        if ( nodeIsACRONYM(node) ) {
            if (clean) {
                /* Replace with 'abbr' with warning to that effect.
                 * Maybe should use static void RenameElem( TidyDoc doc, TidyNode node, TidyTagId tid )
                 */
                TY_(CoerceNode)(doc, node, TidyTag_ABBR, warn, no);
            } else {
                if ( !already_strict )
                    TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
            }
        } else
        if ( nodeIsAPPLET(node) ) {
            if (clean) {
                /* replace with 'object' with warning to that effect
                 * maybe should use static void RenameElem( TidyDoc doc, TidyNode node, TidyTagId tid )
                 */
                TY_(CoerceNode)(doc, node, TidyTag_OBJECT, warn, no);
            } else {
                if ( !already_strict )
                    TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
            }
        } else
        if ( nodeIsBASEFONT(node) ) {
            /* basefont: CSS equivalent 'font-size', 'font-family' and 'color' 
             * on body or class on each subsequent element.
             * Difficult - If it is the first body element, then could consider
             * adding that to the <body> as a whole, else could perhaps apply it
             * to all subsequent elements. But also in consideration is the fact
             * that it was NOT supported in many browsers.
             * - For now just report a warning
             */
            if ( !already_strict )
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
        } else
        if ( nodeIsBIG(node) ) {
            /* big: CSS equivalent 'font-size:larger'
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
             * maybe should use static void RenameElem( TidyDoc doc, TidyNode node, TidyTagId tid )
             */
            if (clean) {
                TY_(AddStyleProperty)( doc, node, "font-size: larger" );
                TY_(CoerceNode)(doc, node, TidyTag_SPAN, warn, no);
            } else {
                if ( !already_strict )
                    TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
            }
        } else
        if ( nodeIsCENTER(node) ) {
            /* center: CSS equivalent 'text-align:center'
             * and 'margin-left:auto; margin-right:auto' on descendant blocks
             * Tidy already handles this if 'clean' by SILENTLY generating the
             * <style> and adding a <div class="c1"> around the elements.
             * see: static Bool Center2Div( TidyDoc doc, TidyNode node, TidyNode *pnode)
             */
            if ( !already_strict )
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
        } else
        if ( nodeIsDIR(node) ) {
            /* dir: replace by <ul>
             * Tidy already actions this and issues a warning
             * Should this be CHANGED???
             */
            if ( !already_strict )
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
        } else
        if ( nodeIsFONT(node) ) {
            /* Tidy already handles this -
             * If 'clean' replaced by CSS, else
             * if is NOT clean, and doctype html5 then warnings issued
             * done in Bool Font2Span( TidyDoc doc, TidyNode node, TidyNode *pnode ) (I think?)
             */
            if ( !already_strict )
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
        } else
        if (( nodesIsFRAME(node) ) || ( nodeIsFRAMESET(node) ) || ( nodeIsNOFRAMES(node) )) {
            /* YOW: What to do here?????? Maybe <iframe>????
             */
            if ( !already_strict )
                TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
        } else
        if ( nodeIsSTRIKE(node) ) {
            /* strike: CSS equivalent 'text-decoration:line-through'
             * maybe should use static void RenameElem( TidyDoc doc, TidyNode node, TidyTagId tid )
             */
            if (clean) {
                TY_(AddStyleProperty)( doc, node, "text-decoration: line-through" );
                TY_(CoerceNode)(doc, node, TidyTag_SPAN, warn, no);
            } else {
                if ( !already_strict )
                    TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
            }
        } else
        if ( nodeIsTT(node) ) {
            /* tt: CSS equivalent 'font-family:monospace'
             * Tidy presently does nothing. Tidy5 issues a warning
             * But like the 'clean' <font> replacement this could also be replaced with CSS
             * maybe should use static void RenameElem( TidyDoc doc, TidyNode node, TidyTagId tid )
             */
            if (clean) {
                TY_(AddStyleProperty)( doc, node, "font-family: monospace" );
                TY_(CoerceNode)(doc, node, TidyTag_SPAN, warn, no);
            } else {
                if ( !already_strict )
                    TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
            }
        } else
            if (TY_(nodeIsElement)(node)) {
                if (node->tag) {
                    if ( (!(node->tag->versions & VERS_HTML5) && !(node->tag->versions & VERS_PROPRIETARY)) || (inRemovedInfo(node->tag->id)) ) {
                        if ( !already_strict )
                            TY_(ReportWarning)(doc, node, node, REMOVED_HTML5);
                    }
                }
            }

        if (node->content)
            TY_(CheckHTML5)( doc, node->content );
        
        node = node->next;
    }
}
/*****************************************************************************
 *  END HTML5 STUFF
 *****************************************************************************/


/*
 * Check and report HTML tags and attributes that are:
 *  - Proprietary, and/or
 *  - Not supported in the current version of HTML, defined as the version
 *    of HTML that we are emitting.
 * Proprietary items are reported as WARNINGS, and version mismatches will
 * be reported as WARNING or ERROR in the following conditions:
 *  - ERROR if the emitted doctype is a strict doctype.
 *  - WARNING if the emitted doctype is a non-strict doctype.
 * The propriety checks are *always* run as they have always been an integral
 * part of Tidy. The version checks are controlled by `strict-tags-attributes`.
 */
void TY_(CheckHTMLTagsAttribsVersions)( TidyDoc doc, TidyNode node )
{
    uint versionEmitted = doc->lexer->versionEmitted;
    uint declared = doc->lexer->doctype;
    uint version = versionEmitted == 0 ? declared : versionEmitted;
    int tagReportType = VERS_STRICT & version ? ELEMENT_VERS_MISMATCH_ERROR : ELEMENT_VERS_MISMATCH_WARN;
    int attrReportType = VERS_STRICT & version ? MISMATCHED_ATTRIBUTE_ERROR : MISMATCHED_ATTRIBUTE_WARN;
    Bool check_versions = cfgBool( doc, TidyStrictTagsAttr );
    TidyAttr next_attr, attval;
    Bool attrIsProprietary = no;
    Bool attrIsMismatched = yes;

    while (node)
    {
        /* This bit here handles our HTML tags */
        if ( TY_(nodeIsElement)(node) && node->tag ) {

            /* Leave XML stuff alone. */
            if ( !cfgBool(doc, TidyXmlTags) )
            {
                /* Version mismatches take priority. */
                if ( check_versions && !(node->tag->versions & version) )
                {
                    TY_(ReportError)(doc, NULL, node, tagReportType );
                }
                /* If it's not mismatched, it could still be proprietary. */
                else if ( node->tag->versions & VERS_PROPRIETARY )
                {
                    if ( !cfgBool(doc, TidyMakeClean) ||
                        ( !nodeIsNOBR(node) && !nodeIsWBR(node) ) )
                    {
                        TY_(ReportError)(doc, NULL, node, PROPRIETARY_ELEMENT );

                        if ( nodeIsLAYER(node) )
                            doc->badLayout |= USING_LAYER;
                        else if ( nodeIsSPACER(node) )
                            doc->badLayout |= USING_SPACER;
                        else if ( nodeIsNOBR(node) )
                            doc->badLayout |= USING_NOBR;
                    }
                }
            }
        }

        /* And this bit here handles our attributes */
        if (TY_(nodeIsElement)(node))
        {
            attval = node->attributes;

            while (attval)
            {
                next_attr = attval->next;

                attrIsProprietary = TY_(AttributeIsProprietary)(node, attval);
                attrIsMismatched = check_versions ? TY_(AttributeIsMismatched)(node, attval, doc) : no;
                /* Let the PROPRIETARY_ATTRIBUTE warning have precedence. */
                if ( attrIsProprietary )
                    TY_(ReportAttrError)(doc, node, attval, PROPRIETARY_ATTRIBUTE);
                else if ( attrIsMismatched )
                {
                    TY_(ReportAttrError)(doc, node, attval, attrReportType);
                }

                /* @todo: do we need a new option to drop mismatches? Or should we
                 simply drop them? */
                if ( ( attrIsProprietary || attrIsMismatched ) && cfgBool(doc, TidyDropPropAttrs) )
                    TY_(RemoveAttribute)( doc, node, attval );

                attval = next_attr;
            }
        }

        if (node->content)
            TY_(CheckHTMLTagsAttribsVersions)( doc, node->content );
        
        node = node->next;
    }
}


#if !defined(NDEBUG) && defined(_MSC_VER)
/* *** FOR DEBUG ONLY *** */
const char *dbg_get_lexer_type( void *vp )
{
    TidyNode node = (TidyNode )vp;
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
    TidyNode node = (TidyNode )vp;
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

void dbg_show_node( TidyDoc doc, TidyNode node, int caller, int indent )
{
    TidyAttr av;
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

void dbg_show_all_nodes( TidyDoc doc, TidyNode node, int indent )
{
    while (node)
    {
        dbg_show_node( doc, node, 0, indent );
        dbg_show_all_nodes( doc, node->content, indent + 1 );
        node = node->next;
    }
}

#endif

int         tidyDocCleanAndRepair( TidyDoc doc )
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
    TidyNode node;

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

    if (node)
    {
        TidyAttr fpi = TY_(GetAttrByName)(node, "PUBLIC");
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
            TidyNode node = TY_(FindDocType)(doc);
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

    /* At this point the apparent doctype is going to be as stable as
       it can ever be, so we can start detecting things that shouldn't
       be in this version of HTML
     */
    if (doc->lexer->versionEmitted & VERS_HTML5)
         TY_(CheckHTML5)( doc, &doc->root );
    TY_(CheckHTMLTagsAttribsVersions)( doc, &doc->root );

#if !defined(NDEBUG) && defined(_MSC_VER)
    SPRTF("All nodes AFTER clean and repair\n");
    dbg_show_all_nodes( doc, &doc->root, 0  );
#endif
    return tidyDocStatus( doc );
}

static
Bool showBodyOnly( TidyDoc doc, TidyTriState bodyOnly )
{
    TidyNode node;

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


int         tidyDocSaveStream( TidyDoc doc, StreamOut* out )
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
    TidyNode node = NULL;
    if ( tdoc )
        node = &tdoc->root;
    return node;
}

TidyNode TIDY_CALL   tidyGetHtml( TidyDoc tdoc )
{
  TidyNode node = NULL;
  if ( tdoc )
      node = TY_(FindHTML)( tdoc );
  return node;
}

TidyNode TIDY_CALL    tidyGetHead( TidyDoc tdoc )
{
  TidyNode node = NULL;
  if ( tdoc )
      node = TY_(FindHEAD)( tdoc );
  return node;
}

TidyNode TIDY_CALL    tidyGetBody( TidyDoc tdoc )
{
  TidyNode node = NULL;
  if ( tdoc )
      node = TY_(FindBody)( tdoc );
  return node;
}

/* parent / child */
TidyNode TIDY_CALL    tidyGetParent( TidyNode tnod )
{
  return tnod->parent;
}
TidyNode TIDY_CALL    tidyGetChild( TidyNode tnod )
{
  return tnod->content;
}

/* remove a node */
TidyNode TIDY_CALL    tidyDiscardElement( TidyDoc tdoc, TidyNode tnod )
{
  return TY_(DiscardElement)( tdoc, tnod );
}

/* siblings */
TidyNode TIDY_CALL    tidyGetNext( TidyNode tnod )
{
  return tnod->next;
}
TidyNode TIDY_CALL    tidyGetPrev( TidyNode tnod )
{
  return tnod->prev;
}

/* Node info */
TidyNodeType TIDY_CALL tidyNodeGetType( TidyNode tnod )
{
  TidyNodeType ntyp = TidyNode_Root;
  if ( tnod )
    ntyp = (TidyNodeType) tnod->type;
  return ntyp;
}

uint TIDY_CALL tidyNodeLine( TidyNode tnod )
{
  uint line = 0;
  if ( tnod )
    line = tnod->line;
  return line;
}
uint TIDY_CALL tidyNodeColumn( TidyNode tnod )
{
  uint col = 0;
  if ( tnod )
    col = tnod->column;
  return col;
}

ctmbstr TIDY_CALL        tidyNodeGetName( TidyNode tnod )
{
  ctmbstr nnam = NULL;
  if ( tnod )
    nnam = tnod->element;
  return nnam;
}


Bool TIDY_CALL  tidyNodeHasText( TidyDoc tdoc, TidyNode tnod )
{
  if ( tdoc )
      return TY_(nodeHasText)( tdoc, tnod );
  return no;
}


Bool TIDY_CALL  tidyNodeGetText( TidyDoc tdoc, TidyNode tnod, TidyBuffer* outbuf )
{
  if ( tdoc && tnod && outbuf )
  {
      uint outenc     = cfg( tdoc, TidyOutCharEncoding );
      uint nl         = cfg( tdoc, TidyNewline );
      StreamOut* out  = TY_(BufferOutput)( tdoc, outbuf, outenc, nl );
      Bool xmlOut     = cfgBool( tdoc, TidyXmlOut );
      Bool xhtmlOut   = cfgBool( tdoc, TidyXhtmlOut );

      tdoc->docOut = out;
      if ( xmlOut && !xhtmlOut )
          TY_(PPrintXMLTree)( tdoc, NORMAL, 0, tnod );
      else
          TY_(PPrintTree)( tdoc, NORMAL, 0, tnod );

      TY_(PFlushLine)( tdoc, 0 );
      tdoc->docOut = NULL;

      TidyDocFree( tdoc, out );
      return yes;
  }
  return no;
}

Bool TIDY_CALL tidyNodeGetValue( TidyDoc doc, TidyNode node, TidyBuffer* buf )
{
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
  Bool isProprietary = yes;
  if ( tnod )
  {
    switch ( tnod->type )
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
        isProprietary = ( tnod->tag
                          ? (tnod->tag->versions&VERS_PROPRIETARY)!=0
                          : yes );
        break;
    }
  }
  return isProprietary;
}

TidyTagId TIDY_CALL tidyNodeGetId(TidyNode tnod)
{

    TidyTagId tagId = TidyTag_UNKNOWN;
    if (tnod && tnod->tag)
        tagId = tnod->tag->id;

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
  TidyAttr attval = NULL;
  if ( tnod )
    attval = tnod->attributes;
  return attval;
}
TidyAttr TIDY_CALL    tidyAttrNext( TidyAttr tattr )
{
  TidyAttr nxtval = NULL;
  if ( tattr )
    nxtval = tattr->next;
  return nxtval;
}

ctmbstr TIDY_CALL       tidyAttrName( TidyAttr tattr )
{
  ctmbstr anam = NULL;
  if ( tattr )
    anam = tattr->attribute;
  return anam;
}
ctmbstr TIDY_CALL       tidyAttrValue( TidyAttr tattr )
{
  ctmbstr aval = NULL;
  if ( tattr )
    aval = tattr->value;
  return aval;
}

void TIDY_CALL           tidyAttrDiscard( TidyDoc tdoc, TidyNode tnod, TidyAttr tattr )
{
  TY_(RemoveAttribute)( tdoc, tnod, tattr );
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
  TidyAttrId attrId = TidyAttr_UNKNOWN;
  if ( tattr && tattr->dict )
    attrId = tattr->dict->id;
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
