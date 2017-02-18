#ifndef __TIDY_H__
#define __TIDY_H__

/** @file tidy.h - Defines HTML Tidy API implemented by LibTidy.

  Public interface is const-correct and doesn't explicitly depend on any
  globals.  Thus, thread-safety may be introduced without changing the
  interface.

  Copyright (c) 1998-2016 World Wide Web Consortium
  (Massachusetts Institute of Technology, European Research 
  Consortium for Informatics and Mathematics, Keio University).
  All Rights Reserved.

  Contributing Author(s):

     Dave Raggett <dsr@w3.org>

  The contributing author(s) would like to thank all those who helped with 
  testing, bug fixes and suggestions for improvements. This wouldn't have been
  possible without your help.

  COPYRIGHT NOTICE:
 
  This software and documentation is provided "as is," and the copyright holders
  and contributing author(s) make no representations or warranties, express or
  implied, including but not limited to, warranties of merchantability or 
  fitness for any particular purpose or that the use of the software or
  documentation will not infringe any third party patents, copyrights, 
  trademarks or other rights.

  The copyright holders and contributing author(s) will not be held liable for 
  any direct, indirect, special or consequential damages arising out of any use
  of the software or documentation, even if advised of the possibility of such 
  damage.

  Permission is hereby granted to use, copy, modify, and distribute this source
  code, or portions hereof, documentation and executables, for any purpose,
  without fee, subject to the following restrictions:

  1. The origin of this source code must not be misrepresented.
  2. Altered versions must be plainly marked as such and must not be
     misrepresented as being the original source.
  3. This Copyright notice may not be removed or altered from any source or 
     altered source distribution.
 
  The copyright holders and contributing author(s) specifically permit, without
  fee, and encourage the use of this source code as a component for supporting
  the Hypertext Markup Language in commercial products. If you use this source
  code in a product, acknowledgment is not required but would be appreciated.

  Created 2001-05-20 by Charles Reitzel
  Updated 2002-07-01 by Charles Reitzel - 1st Implementation
  Updated 2015-06-09 by Geoff R. McLane - Add more doxygen syntax
  Additional updates: consult git log

*/

#include "tidyplatform.h"
#include "tidyenum.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup Opaque Opaque Types
**
** These instances of these types are available for use in your programs,
** however their internal details are opaque. These items should be accessed
** with LibTidy's accessor functions.
**
** Internally LibTidy will cast these to internal implementation types.
** Cast to implementation types within lib.
**
** This reduces inter-dependencies and conflicts with application code.
** @{
*/

/** @struct TidyDoc
**  Opaque document datatype
*/
opaque_type( TidyDoc );

/** @struct TidyOption
**  Opaque option datatype
*/
opaque_type( TidyOption );

/** @struct TidyNode
**  Opaque node datatype
*/
opaque_type( TidyNode );

/** @struct TidyAttr
**  Opaque attribute datatype
*/
opaque_type( TidyAttr );

/** @} end Opaque group */


TIDY_STRUCT struct _TidyBuffer;
typedef struct _TidyBuffer TidyBuffer;


/** @defgroup Memory  Memory Allocation
**
** Tidy uses a user provided allocator for all memory allocations.  If this 
** allocator is not provided, then a default allocator is used which simply
** wraps standard C malloc/free calls.  These wrappers call the panic function
** upon any failure.  The default panic function prints an out of memory message
** to stderr, and calls exit(2).
**
** For applications in which it is unacceptable to abort in the case of memory 
** allocation, then the panic function can be replaced with one which longjmps()
** out of the LibTidy code.  For this to clean up completely, you should be
** careful not to use any tidy methods that open files as these will not be 
** closed before panic() is called.
**
** TODO: associate file handles with tidyDoc and ensure that tidyDocRelease()
** can close them all.
**
** Calling the xWithAllocator() family (tidyCreateWithAllocator,
** tidyBufInitWithAllocator, tidyBufAllocWithAllocator) allow setting custom
** allocators.
**
** All parts of the document use the same allocator. Calls that require a user
** provided buffer can optionally use a different allocator.
**
** For reference in designing a plug-in allocator, most allocations made by 
** LibTidy are less than 100 bytes, corresponding to attribute names and 
** values, etc.
**
** There is also an additional class of much larger allocations which are where
** most of the data from the lexer is stored. It is not currently possible to
** use a separate allocator for the lexer; this would be a useful extension.
**
** In general, approximately 1/3rd of the memory used by LibTidy is freed during
** the parse, so if memory usage is an issue then an allocator that can reuse
** this memory is a good idea.
**
** @{
*/

/** Prototype for the allocator's function table */
struct _TidyAllocatorVtbl;
/** The allocators function table */
typedef struct _TidyAllocatorVtbl TidyAllocatorVtbl;

/** Prototype for the allocator */
struct _TidyAllocator;
/** The allocator **/
typedef struct _TidyAllocator TidyAllocator;

/**  An allocator's function table.  All functions here must be provided.
 */
struct _TidyAllocatorVtbl {
    /** Called to allocate a block of nBytes of memory */
    void* (TIDY_CALL *alloc)( TidyAllocator *self, size_t nBytes );
    /** Called to resize (grow, in general) a block of memory.
        Must support being called with NULL.
    */
    void* (TIDY_CALL *realloc)( TidyAllocator *self, void *block, size_t nBytes );
    /** Called to free a previously allocated block of memory */
    void (TIDY_CALL *free)( TidyAllocator *self, void *block);
    /** Called when a panic condition is detected.  Must support block == NULL.
        This function is not called if either alloc or realloc fails; it is up 
        to the allocator to do this. Currently this function can only be called
        if an error is detected in the tree integrity via the internal function
        CheckNodeIntegrity().  This is a situation that can only arise in the 
        case of a programming error in LibTidy. You can turn off node integrity
        checking by defining the constant NO_NODE_INTEGRITY_CHECK during the
        build.
    **/
    void (TIDY_CALL *panic)( TidyAllocator *self, ctmbstr msg );
};

/** An allocator.  To create your own allocator, do something like
    the following:
    \code
    typedef struct _MyAllocator {
       TidyAllocator base;
       ...other custom allocator state...
    } MyAllocator;
    
    void* MyAllocator_alloc(TidyAllocator *base, void *block, size_t nBytes)
    {
        MyAllocator *self = (MyAllocator*)base;
        ...
    }
    (etc)

    static const TidyAllocatorVtbl MyAllocatorVtbl = {
        MyAllocator_alloc,
        MyAllocator_realloc,
        MyAllocator_free,
        MyAllocator_panic
    };

    myAllocator allocator;
    TidyDoc doc;

    allocator.base.vtbl = &amp;MyAllocatorVtbl;
    ...initialise allocator specific state...
    doc = tidyCreateWithAllocator(&allocator);
    \endcode

    Although this looks slightly long winded, the advantage is that to create
    a custom allocator you simply need to set the vtbl pointer correctly.
    The vtbl itself can reside in static/global data, and hence does not
    need to be initialised each time an allocator is created, and furthermore
    the memory is shared amongst all created allocators.
*/
struct _TidyAllocator {
    const TidyAllocatorVtbl *vtbl;
};

/** Callback for "malloc" replacement */
typedef void* (TIDY_CALL *TidyMalloc)( size_t len );
/** Callback for "realloc" replacement */
typedef void* (TIDY_CALL *TidyRealloc)( void* buf, size_t len );
/** Callback for "free" replacement */
typedef void  (TIDY_CALL *TidyFree)( void* buf );
/** Callback for "out of memory" panic state */
typedef void  (TIDY_CALL *TidyPanic)( ctmbstr mssg );


/** Give Tidy a malloc() replacement */
TIDY_EXPORT Bool TIDY_CALL tidySetMallocCall( TidyMalloc fmalloc );
/** Give Tidy a realloc() replacement */
TIDY_EXPORT Bool TIDY_CALL tidySetReallocCall( TidyRealloc frealloc );
/** Give Tidy a free() replacement */
TIDY_EXPORT Bool TIDY_CALL tidySetFreeCall( TidyFree ffree );
/** Give Tidy an "out of memory" handler */
TIDY_EXPORT Bool TIDY_CALL tidySetPanicCall( TidyPanic fpanic );

/** @} end Memory group */

/** @defgroup Basic Basic Operations
**
** For an excellent example of how to invoke LibTidy, please consult
** `console/tidy.c:main()` for in-depth implementation details. A simplified
** example can be seen on our site: http://www.html-tidy.org/developer/
**
** There used to be an example built into the documentation right here, but
** as it was formatted for Doxygen rather than a developer, it was unreadable
** and so has been removed.
**
** @{
*/

/** The primary creation of a TidyDoc. This must be the first call before most
 ** of the Tidy API which require the TidyDoc parameter. When completed,
 **  tidyRelease( TidyDoc tdoc ); should be called to release all memory
 */
TIDY_EXPORT TidyDoc TIDY_CALL     tidyCreate(void);

/** Create a Tidoc supplying the TidyAllocator.
 ** See the TidyAllocator structure for creating an allocator
 */
TIDY_EXPORT TidyDoc TIDY_CALL     tidyCreateWithAllocator( TidyAllocator *allocator );

/** Free all memory and release the TidyDoc.
 ** TidyDoc can not be used after this call.
 */
TIDY_EXPORT void TIDY_CALL        tidyRelease( TidyDoc tdoc );

/** Let application store a chunk of data w/ each Tidy instance.
**  Useful for callbacks.
*/
TIDY_EXPORT void TIDY_CALL        tidySetAppData( TidyDoc tdoc, void* appData );

/** Get application data set previously */
TIDY_EXPORT void* TIDY_CALL       tidyGetAppData( TidyDoc tdoc );

/** Get release date (version) for current library 
 */
TIDY_EXPORT ctmbstr TIDY_CALL     tidyReleaseDate(void);

/** Get version number for the current library */
TIDY_EXPORT ctmbstr TIDY_CALL     tidyLibraryVersion(void);

/* Diagnostics and Repair
*/

/** Get status of current document. */
TIDY_EXPORT int TIDY_CALL         tidyStatus( TidyDoc tdoc );

/** Detected HTML version: 0, 2, 3 or 4 */
TIDY_EXPORT int TIDY_CALL         tidyDetectedHtmlVersion( TidyDoc tdoc );

/** Input is XHTML? */
TIDY_EXPORT Bool TIDY_CALL        tidyDetectedXhtml( TidyDoc tdoc );

/** Input is generic XML (not HTML or XHTML)? */
TIDY_EXPORT Bool TIDY_CALL        tidyDetectedGenericXml( TidyDoc tdoc );

/** Number of Tidy errors encountered.  If > 0, output is suppressed
**  unless TidyForceOutput is set.
*/
TIDY_EXPORT uint TIDY_CALL        tidyErrorCount( TidyDoc tdoc );

/** Number of Tidy warnings encountered. */
TIDY_EXPORT uint TIDY_CALL        tidyWarningCount( TidyDoc tdoc );

/** Number of Tidy accessibility warnings encountered. */
TIDY_EXPORT uint TIDY_CALL        tidyAccessWarningCount( TidyDoc tdoc );

/** Number of Tidy configuration errors encountered. */
TIDY_EXPORT uint TIDY_CALL        tidyConfigErrorCount( TidyDoc tdoc );

/* Get/Set configuration options
*/
/** Load an ASCII Tidy configuration file */
TIDY_EXPORT int TIDY_CALL         tidyLoadConfig( TidyDoc tdoc, ctmbstr configFile );

/** Load a Tidy configuration file with the specified character encoding */
TIDY_EXPORT int TIDY_CALL         tidyLoadConfigEnc( TidyDoc tdoc, ctmbstr configFile,
                                                     ctmbstr charenc );

TIDY_EXPORT Bool TIDY_CALL        tidyFileExists( TidyDoc tdoc, ctmbstr filename );


/** Set the input/output character encoding for parsing markup.
**  Values include: ascii, latin1, raw, utf8, iso2022, mac,
**  win1252, utf16le, utf16be, utf16, big5 and shiftjis.  Case in-sensitive.
*/
TIDY_EXPORT int TIDY_CALL         tidySetCharEncoding( TidyDoc tdoc, ctmbstr encnam );

/** Set the input encoding for parsing markup.
** As for tidySetCharEncoding but only affects the input encoding
**/
TIDY_EXPORT int TIDY_CALL         tidySetInCharEncoding( TidyDoc tdoc, ctmbstr encnam );

/** Set the output encoding.
**/
TIDY_EXPORT int TIDY_CALL         tidySetOutCharEncoding( TidyDoc tdoc, ctmbstr encnam );

/** @} end Basic group */


/** @defgroup Configuration Configuration Options
**
** Functions for getting and setting Tidy configuration options.
** @{
*/

/** Applications using TidyLib may want to augment command-line and
**  configuration file options.  Setting this callback allows an application 
**  developer to examine command-line and configuration file options after
**  TidyLib has examined them and failed to recognize them.
**/

typedef Bool (TIDY_CALL *TidyOptCallback)( ctmbstr option, ctmbstr value );

TIDY_EXPORT Bool TIDY_CALL          tidySetOptionCallback( TidyDoc tdoc, TidyOptCallback pOptCallback );

/** Get option ID by name */
TIDY_EXPORT TidyOptionId TIDY_CALL  tidyOptGetIdForName( ctmbstr optnam );

/** Get iterator for list of option */
/** 
Example:
<pre>
TidyIterator itOpt = tidyGetOptionList( tdoc );
while ( itOpt )
{
  TidyOption opt = tidyGetNextOption( tdoc, &itOpt );
  .. get/set option values ..
}
</pre>
*/

TIDY_EXPORT TidyIterator TIDY_CALL  tidyGetOptionList( TidyDoc tdoc );
/** Get next Option */
TIDY_EXPORT TidyOption TIDY_CALL    tidyGetNextOption( TidyDoc tdoc, TidyIterator* pos );

/** Lookup option by ID */
TIDY_EXPORT TidyOption TIDY_CALL    tidyGetOption( TidyDoc tdoc, TidyOptionId optId );
/** Lookup option by name */
TIDY_EXPORT TidyOption TIDY_CALL    tidyGetOptionByName( TidyDoc tdoc, ctmbstr optnam );

/** Get ID of given Option */
TIDY_EXPORT TidyOptionId TIDY_CALL  tidyOptGetId( TidyOption opt );

/** Get name of given Option */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetName( TidyOption opt );

/** Get datatype of given Option */
TIDY_EXPORT TidyOptionType TIDY_CALL tidyOptGetType( TidyOption opt );

/** Is Option read-only? */
TIDY_EXPORT Bool TIDY_CALL          tidyOptIsReadOnly( TidyOption opt );

/** Get category of given Option */
TIDY_EXPORT TidyConfigCategory TIDY_CALL tidyOptGetCategory( TidyOption opt );

/** Get default value of given Option as a string */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetDefault( TidyOption opt );

/** Get default value of given Option as an unsigned integer */
TIDY_EXPORT ulong TIDY_CALL         tidyOptGetDefaultInt( TidyOption opt );

/** Get default value of given Option as a Boolean value */
TIDY_EXPORT Bool TIDY_CALL          tidyOptGetDefaultBool( TidyOption opt );

/** Iterate over Option "pick list" */
TIDY_EXPORT TidyIterator TIDY_CALL  tidyOptGetPickList( TidyOption opt );
/** Get next string value of Option "pick list" */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetNextPick( TidyOption opt, TidyIterator* pos );

/** Get string Option current value. Note, the optID "must" be a type 'TidyString'! */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetValue( TidyDoc tdoc, TidyOptionId optId );
/** Set Option value as a string */
TIDY_EXPORT Bool TIDY_CALL          tidyOptSetValue( TidyDoc tdoc, TidyOptionId optId, ctmbstr val );
/** Set named Option value as a string.  Good if not sure of type. */
TIDY_EXPORT Bool TIDY_CALL          tidyOptParseValue( TidyDoc tdoc, ctmbstr optnam, ctmbstr val );

/** Get current Option value as an integer */
TIDY_EXPORT ulong TIDY_CALL         tidyOptGetInt( TidyDoc tdoc, TidyOptionId optId );
/** Set Option value as an integer */
TIDY_EXPORT Bool TIDY_CALL          tidyOptSetInt( TidyDoc tdoc, TidyOptionId optId, ulong val );

/** Get current Option value as a Boolean flag */
TIDY_EXPORT Bool TIDY_CALL          tidyOptGetBool( TidyDoc tdoc, TidyOptionId optId );
/** Set Option value as a Boolean flag */
TIDY_EXPORT Bool TIDY_CALL          tidyOptSetBool( TidyDoc tdoc, TidyOptionId optId, Bool val );

/** Reset option to default value by ID */
TIDY_EXPORT Bool TIDY_CALL          tidyOptResetToDefault( TidyDoc tdoc, TidyOptionId opt );
/** Reset all options to their default values */
TIDY_EXPORT Bool TIDY_CALL          tidyOptResetAllToDefault( TidyDoc tdoc );

/** Take a snapshot of current config settings */
TIDY_EXPORT Bool TIDY_CALL          tidyOptSnapshot( TidyDoc tdoc );
/** Reset config settings to snapshot (after document processing) */
TIDY_EXPORT Bool TIDY_CALL          tidyOptResetToSnapshot( TidyDoc tdoc );

/** Any settings different than default? */
TIDY_EXPORT Bool TIDY_CALL          tidyOptDiffThanDefault( TidyDoc tdoc );
/** Any settings different than snapshot? */
TIDY_EXPORT Bool TIDY_CALL          tidyOptDiffThanSnapshot( TidyDoc tdoc );

/** Copy current configuration settings from one document to another */
TIDY_EXPORT Bool TIDY_CALL          tidyOptCopyConfig( TidyDoc tdocTo, TidyDoc tdocFrom );

/** Get character encoding name.  Used with TidyCharEncoding,
**  TidyOutCharEncoding, TidyInCharEncoding */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetEncName( TidyDoc tdoc, TidyOptionId optId );

/** Get current pick list value for option by ID.  Useful for enum types. */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetCurrPick( TidyDoc tdoc, TidyOptionId optId);

/** Iterate over user declared tags */
TIDY_EXPORT TidyIterator TIDY_CALL  tidyOptGetDeclTagList( TidyDoc tdoc );
/** Get next declared tag of specified type: TidyInlineTags, TidyBlockTags,
**  TidyEmptyTags, TidyPreTags */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetNextDeclTag( TidyDoc tdoc, 
                                                          TidyOptionId optId,
                                                          TidyIterator* iter );
/** Get option description */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetDoc( TidyDoc tdoc, TidyOption opt );

/** Iterate over a list of related options */
TIDY_EXPORT TidyIterator TIDY_CALL  tidyOptGetDocLinksList( TidyDoc tdoc,
                                                  TidyOption opt );
/** Get next related option */
TIDY_EXPORT TidyOption TIDY_CALL    tidyOptGetNextDocLinks( TidyDoc tdoc,
                                                  TidyIterator* pos );

/** @} end Configuration group */

/** @defgroup IO  I/O and Messages
**
** By default, Tidy will define, create and use 
** instances of input and output handlers for 
** standard C buffered I/O (i.e. FILE* stdin,
** FILE* stdout and FILE* stderr for content
** input, content output and diagnostic output,
** respectively.  A FILE* cfgFile input handler
** will be used for config files.  Command line
** options will just be set directly.
**
** @{
*/

/*****************
   Input Source
*****************/
/** Input Callback: get next byte of input */
typedef int  (TIDY_CALL *TidyGetByteFunc)( void* sourceData );

/** Input Callback: unget a byte of input */
typedef void (TIDY_CALL *TidyUngetByteFunc)( void* sourceData, byte bt );

/** Input Callback: is end of input? */
typedef Bool (TIDY_CALL *TidyEOFFunc)( void* sourceData );

/** End of input "character" */
#define EndOfStream (~0u)

/** TidyInputSource - Delivers raw bytes of input
*/
TIDY_STRUCT
typedef struct _TidyInputSource
{
  /* Instance data */
  void*               sourceData;  /**< Input context.  Passed to callbacks */

  /* Methods */
  TidyGetByteFunc     getByte;     /**< Pointer to "get byte" callback */
  TidyUngetByteFunc   ungetByte;   /**< Pointer to "unget" callback */
  TidyEOFFunc         eof;         /**< Pointer to "eof" callback */
} TidyInputSource;

/** Facilitates user defined source by providing
**  an entry point to marshal pointers-to-functions.
**  Needed by .NET and possibly other language bindings.
*/
TIDY_EXPORT Bool TIDY_CALL tidyInitSource( TidyInputSource*  source,
                                          void*             srcData,
                                          TidyGetByteFunc   gbFunc,
                                          TidyUngetByteFunc ugbFunc,
                                          TidyEOFFunc       endFunc );

/** Helper: get next byte from input source */
TIDY_EXPORT uint TIDY_CALL tidyGetByte( TidyInputSource* source );

/** Helper: unget byte back to input source */
TIDY_EXPORT void TIDY_CALL tidyUngetByte( TidyInputSource* source, uint byteValue );

/** Helper: check if input source at end */
TIDY_EXPORT Bool TIDY_CALL tidyIsEOF( TidyInputSource* source );


/****************
   Output Sink
****************/
/** Output callback: send a byte to output */
typedef void (TIDY_CALL *TidyPutByteFunc)( void* sinkData, byte bt );


/** TidyOutputSink - accepts raw bytes of output
*/
TIDY_STRUCT
typedef struct _TidyOutputSink
{
  /* Instance data */
  void*               sinkData;  /**< Output context.  Passed to callbacks */

  /* Methods */
  TidyPutByteFunc     putByte;   /**< Pointer to "put byte" callback */
} TidyOutputSink;

/** Facilitates user defined sinks by providing
**  an entry point to marshal pointers-to-functions.
**  Needed by .NET and possibly other language bindings.
*/
TIDY_EXPORT Bool TIDY_CALL tidyInitSink( TidyOutputSink* sink, 
                                        void*           snkData,
                                        TidyPutByteFunc pbFunc );

/** Helper: send a byte to output */
TIDY_EXPORT void TIDY_CALL tidyPutByte( TidyOutputSink* sink, uint byteValue );


/****************
   Errors
****************/
/** Callback to filter messages by diagnostic level:
**  info, warning, etc.  Just set diagnostic output 
**  handler to redirect all diagnostics output.  Return true
**  to proceed with output, false to cancel.
*/
typedef Bool (TIDY_CALL *TidyReportFilter)( TidyDoc tdoc, TidyReportLevel lvl,
                                           uint line, uint col, ctmbstr mssg );

typedef Bool (TIDY_CALL *TidyReportFilter2)( TidyDoc tdoc, TidyReportLevel lvl,
                                           uint line, uint col, ctmbstr mssg, va_list args );

typedef Bool (TIDY_CALL *TidyReportFilter3)( TidyDoc tdoc, TidyReportLevel lvl,
                                                uint line, uint col, ctmbstr code, va_list args );

/** Give Tidy a filter callback to use */
TIDY_EXPORT Bool TIDY_CALL    tidySetReportFilter( TidyDoc tdoc,
                                                  TidyReportFilter filtCallback );

TIDY_EXPORT Bool TIDY_CALL    tidySetReportFilter2( TidyDoc tdoc,
                                                  TidyReportFilter2 filtCallback );

TIDY_EXPORT Bool TIDY_CALL    tidySetReportFilter3( TidyDoc tdoc,
                                                       TidyReportFilter3 filtCallback );

/** Set error sink to named file */
TIDY_EXPORT FILE* TIDY_CALL   tidySetErrorFile( TidyDoc tdoc, ctmbstr errfilnam );
/** Set error sink to given buffer */
TIDY_EXPORT int TIDY_CALL     tidySetErrorBuffer( TidyDoc tdoc, TidyBuffer* errbuf );
/** Set error sink to given generic sink */
TIDY_EXPORT int TIDY_CALL     tidySetErrorSink( TidyDoc tdoc, TidyOutputSink* sink );


/****************
   Printing
****************/
/** Callback to track the progress of the pretting printing process.
**
*/
typedef void (TIDY_CALL *TidyPPProgress)( TidyDoc tdoc, uint line, uint col, uint destLine );

TIDY_EXPORT Bool TIDY_CALL   tidySetPrettyPrinterCallback( TidyDoc tdoc,
                                                  TidyPPProgress callback );

/** @} end IO group */

/* TODO: Catalog all messages for easy translation
TIDY_EXPORT ctmbstr     tidyLookupMessage( int errorNo );
*/



/** @defgroup Parse Document Parse
**
** Parse markup from a given input source.  String and filename 
** functions added for convenience.  HTML/XHTML version determined
** from input.
** @{
*/

/** Parse markup in named file */
TIDY_EXPORT int TIDY_CALL         tidyParseFile( TidyDoc tdoc, ctmbstr filename );

/** Parse markup from the standard input */
TIDY_EXPORT int TIDY_CALL         tidyParseStdin( TidyDoc tdoc );

/** Parse markup in given string */
TIDY_EXPORT int TIDY_CALL         tidyParseString( TidyDoc tdoc, ctmbstr content );

/** Parse markup in given buffer */
TIDY_EXPORT int TIDY_CALL         tidyParseBuffer( TidyDoc tdoc, TidyBuffer* buf );

/** Parse markup in given generic input source */
TIDY_EXPORT int TIDY_CALL         tidyParseSource( TidyDoc tdoc, TidyInputSource* source);

/** @} End Parse group */


/** @defgroup Clean Diagnostics and Repair
**
** @{
*/
/** Execute configured cleanup and repair operations on parsed markup */
TIDY_EXPORT int TIDY_CALL         tidyCleanAndRepair( TidyDoc tdoc );

/** Run configured diagnostics on parsed and repaired markup. 
**  Must call tidyCleanAndRepair() first.
*/
TIDY_EXPORT int TIDY_CALL         tidyRunDiagnostics( TidyDoc tdoc );

TIDY_EXPORT int TIDY_CALL         tidyReportDoctype( TidyDoc tdoc );

/** @} end Clean group */


/** @defgroup Save Document Save Functions
**
** Save currently parsed document to the given output sink.  File name
** and string/buffer functions provided for convenience.
** @{
*/

/** Save to named file */
TIDY_EXPORT int TIDY_CALL         tidySaveFile( TidyDoc tdoc, ctmbstr filename );

/** Save to standard output (FILE*) */
TIDY_EXPORT int TIDY_CALL         tidySaveStdout( TidyDoc tdoc );

/** Save to given TidyBuffer object */
TIDY_EXPORT int TIDY_CALL         tidySaveBuffer( TidyDoc tdoc, TidyBuffer* buf );

/** Save document to application buffer.  If TidyShowMarkup and
**  the document has no errors, or TidyForceOutput, the current 
**  document, per the current configuration, will be Pretty Printed
**  to the application buffer.  The document byte length,
**  not character length, will be placed in *buflen. The document 
**  will not be null terminated. If the buffer is not big enough,
**  ENOMEM will be returned, else the actual document status.
*/
TIDY_EXPORT int TIDY_CALL         tidySaveString( TidyDoc tdoc,
                                                 tmbstr buffer, uint* buflen );

/** Save to given generic output sink */
TIDY_EXPORT int TIDY_CALL         tidySaveSink( TidyDoc tdoc, TidyOutputSink* sink );

/** @} end Save group */


/** @addtogroup Basic
** @{
*/
/** Save current settings to named file.
    Only non-default values are written. */
TIDY_EXPORT int TIDY_CALL         tidyOptSaveFile( TidyDoc tdoc, ctmbstr cfgfil );

/** Save current settings to given output sink.
    Only non-default values are written. */
TIDY_EXPORT int TIDY_CALL         tidyOptSaveSink( TidyDoc tdoc, TidyOutputSink* sink );


/* Error reporting functions 
*/

/** Write more complete information about errors to current error sink. */
TIDY_EXPORT void TIDY_CALL        tidyErrorSummary( TidyDoc tdoc );

/** Write more general information about markup to current error sink. */
TIDY_EXPORT void TIDY_CALL        tidyGeneralInfo( TidyDoc tdoc );

/** @} end Basic group (again) */


/** @defgroup Tree Document Tree
**
** A parsed and, optionally, repaired document is
** represented by Tidy as a Tree, much like a W3C DOM.
** This tree may be traversed using these functions.
** The following snippet gives a basic idea how these
** functions can be used.
**
<pre>
void dumpNode( TidyNode tnod, int indent )
{
  TidyNode child;

  for ( child = tidyGetChild(tnod); child; child = tidyGetNext(child) )
  {
    ctmbstr name;
    switch ( tidyNodeGetType(child) )
    {
    case TidyNode_Root:       name = "Root";                    break;
    case TidyNode_DocType:    name = "DOCTYPE";                 break;
    case TidyNode_Comment:    name = "Comment";                 break;
    case TidyNode_ProcIns:    name = "Processing Instruction";  break;
    case TidyNode_Text:       name = "Text";                    break;
    case TidyNode_CDATA:      name = "CDATA";                   break;
    case TidyNode_Section:    name = "XML Section";             break;
    case TidyNode_Asp:        name = "ASP";                     break;
    case TidyNode_Jste:       name = "JSTE";                    break;
    case TidyNode_Php:        name = "PHP";                     break;
    case TidyNode_XmlDecl:    name = "XML Declaration";         break;

    case TidyNode_Start:
    case TidyNode_End:
    case TidyNode_StartEnd:
    default:
      name = tidyNodeGetName( child );
      break;
    }
    assert( name != NULL );
    printf( "\%*.*sNode: \%s\\n", indent, indent, " ", name );
    dumpNode( child, indent + 4 );
  }
}

void dumpDoc( TidyDoc tdoc )
{
  dumpNode( tidyGetRoot(tdoc), 0 );
}

void dumpBody( TidyDoc tdoc )
{
  dumpNode( tidyGetBody(tdoc), 0 );
}
</pre>

@{

*/

TIDY_EXPORT TidyNode TIDY_CALL    tidyGetRoot( TidyDoc tdoc );
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetHtml( TidyDoc tdoc );
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetHead( TidyDoc tdoc );
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetBody( TidyDoc tdoc );

/* remove a node */
TIDY_EXPORT TidyNode TIDY_CALL    tidyDiscardElement( TidyDoc tdoc, TidyNode tnod );

/* parent / child */
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetParent( TidyNode tnod );
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetChild( TidyNode tnod );

/* siblings */
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetNext( TidyNode tnod );
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetPrev( TidyNode tnod );

/* Iterate over attribute values */
TIDY_EXPORT TidyAttr TIDY_CALL    tidyAttrFirst( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL    tidyAttrNext( TidyAttr tattr );

TIDY_EXPORT ctmbstr TIDY_CALL     tidyAttrName( TidyAttr tattr );
TIDY_EXPORT ctmbstr TIDY_CALL     tidyAttrValue( TidyAttr tattr );

TIDY_EXPORT void TIDY_CALL        tidyAttrDiscard( TidyDoc itdoc, TidyNode tnod, TidyAttr tattr );

/** @} end Tree group */


/** @defgroup NodeAsk Node Interrogation
**
** Get information about any givent node.
** @{
*/

/* Node info */
TIDY_EXPORT TidyNodeType TIDY_CALL tidyNodeGetType( TidyNode tnod );
TIDY_EXPORT ctmbstr TIDY_CALL tidyNodeGetName( TidyNode tnod );

TIDY_EXPORT Bool TIDY_CALL tidyNodeIsText( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsProp( TidyDoc tdoc, TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsHeader( TidyNode tnod ); /* h1, h2, ... */

TIDY_EXPORT Bool TIDY_CALL tidyNodeHasText( TidyDoc tdoc, TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeGetText( TidyDoc tdoc, TidyNode tnod, TidyBuffer* buf );

/* Copy the unescaped value of this node into the given TidyBuffer as UTF-8 */
TIDY_EXPORT Bool TIDY_CALL tidyNodeGetValue( TidyDoc tdoc, TidyNode tnod, TidyBuffer* buf );

TIDY_EXPORT TidyTagId TIDY_CALL tidyNodeGetId( TidyNode tnod );

TIDY_EXPORT uint TIDY_CALL tidyNodeLine( TidyNode tnod );
TIDY_EXPORT uint TIDY_CALL tidyNodeColumn( TidyNode tnod );

/** @} End NodeAsk group */


/** @defgroup Attribute Attribute Interrogation and Retrieval
**
** Get information about attributes, and retrieve them from nodes.
** @{
*/

TIDY_EXPORT TidyAttrId TIDY_CALL tidyAttrGetId( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsEvent( TidyAttr tattr );

TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetById( TidyNode tnod, TidyAttrId attId );

/** @} end Attribute group */

    
/** @defgroup MessagesKeys Message Key Management
**
** These functions serve to manage message codes. To-do is to rename them
** so they reflect messages and not errors.
** @{
*/

TIDY_EXPORT ctmbstr TIDY_CALL tidyErrorCodeAsKey(uint code);
TIDY_EXPORT TidyIterator TIDY_CALL getErrorCodeList();
TIDY_EXPORT uint TIDY_CALL getNextErrorCode( TidyIterator* iter );

/** @} end MessagesKeys group */
    
    
/** @defgroup Localization Localization Support
**
** These functions help manage localization in Tidy.
 ** @{
*/

    
/**
 **  Determines the current locale without affecting the C locale.
 **  Tidy has always used the default C locale, and at this point
 **  in its development we're not going to tamper with that.
 **  @param  result The buffer to use to return the string.
 **          Returns NULL on failure.
 **  @return The same buffer for convenience.
 */
TIDY_EXPORT tmbstr TIDY_CALL tidySystemLocale(tmbstr result);

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
TIDY_EXPORT Bool TIDY_CALL tidySetLanguage( ctmbstr languageCode );

/**
 *  Gets the current language used by Tidy.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetLanguage();

/**
 *  Provides a string given `messageType` in the current
 *  localization for `quantity`.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyLocalizedStringN( uint messageType, uint quantity );

/**
 *  Provides a string given `messageType` in the current
 *  localization for the single case.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyLocalizedString( uint messageType );

/**
 *  Provides a string given `messageType` in the default
 *  localization (which is `en`).
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyDefaultString( uint messageType );

/*
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's list of localization string keys. Note that
 *  these are provided for documentation generation purposes
 *  and probably aren't useful for LibTidy implementors.
 */
TIDY_EXPORT TidyIterator TIDY_CALL getStringKeyList();

/*
 *  Provides the next key value in Tidy's list of localized
 *  strings. Note that these are provided for documentation
 *  generation purposes and probably aren't useful to
 *  libtidy implementors.
 */
TIDY_EXPORT uint TIDY_CALL getNextStringKey( TidyIterator* iter );

/**
 *  Define an opaque type we can use for tidyLocaleMapItem, which
 *  is used to iterate through the language list, and used to access
 *  the windowsName() and the posixName().
 */
opaque_type(tidyLocaleMapItem);
    
/**
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's structure of Windows<->POSIX local mapping.
 *  Items can be retrieved with getNextWindowsLanguage();
 */
TIDY_EXPORT TidyIterator TIDY_CALL getWindowsLanguageList();

/**
 *  Returns the next record of type `localeMapItem` in
 *  Tidy's structure of Windows<->POSIX local mapping.
 */
TIDY_EXPORT const tidyLocaleMapItem TIDY_CALL *getNextWindowsLanguage( TidyIterator* iter );

/**
 *  Given a `tidyLocalMapItem`, return the Windows name.
 */
TIDY_EXPORT const ctmbstr TIDY_CALL TidyLangWindowsName( const tidyLocaleMapItem *item );

/**
 *  Given a `tidyLocalMapItem`, return the POSIX name.
 */
TIDY_EXPORT const ctmbstr TIDY_CALL TidyLangPosixName( const tidyLocaleMapItem *item );

/**
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's list of installed language codes.
 *  Items can be retrieved with getNextInstalledLanguage();
 */
TIDY_EXPORT TidyIterator TIDY_CALL getInstalledLanguageList();

/**
 *  Returns the next installed language.
 */
TIDY_EXPORT ctmbstr TIDY_CALL getNextInstalledLanguage( TidyIterator* iter );



/** @} end MessagesKeys group */
    

#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif /* __TIDY_H__ */

/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
