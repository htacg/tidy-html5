#ifndef __TIDY_H__
#define __TIDY_H__

/***************************************************************************//**
 * @file
 * Defines HTML Tidy public API implemented by LibTidy.
 *
 * This public interface provides the entire public API for LibTidy, and
 * is the sole interface that you should use when implementing LibTidy in
 * your own applications.
 *
 * See tidy.c as an example application implementing the public API.
 *
 * This API is const-correct and doesn't explicitly depend on any globals.
 * Thus, thread-safety may be introduced without changing the interface.
 *
 * The API limits all exposure to internal structures and provides only
 * accessors that return simple types such as C strings and integers, which
 * makes it quite suitable for integration with any number of other languages.
 *
 * @author  Dave Raggett [dsr@w3.org]
 * @author  HTACG, et al (consult git log)
 * 
 * @remarks The contributing author(s) would like to thank all those who 
 *          helped with testing, bug fixes and suggestions for improvements.
 *          This wouldn't have been possible without your help.
 *
 * @copyright
 *     Copyright (c) 1998-2017 World Wide Web Consortium (Massachusetts
 *     Institute of Technology, European Research Consortium for Informatics
 *     and Mathematics, Keio University).
 * @par
 *     All Rights Reserved.
 * @par
 *     This software and documentation is provided "as is," and the copyright 
 *     holders and contributing author(s) make no representations or warranties,
 *     express or implied, including but not limited to, warranties of 
 *     merchantability or fitness for any particular purpose or that the use of
 *     the software or documentation will not infringe any third party patents,
 *     copyrights, trademarks or other rights.
 *     @par
 *     The copyright holders and contributing author(s) will not be held liable
 *     for any direct, indirect, special or consequential damages arising out of
 *     any use of the software or documentation, even if advised of the
 *     possibility of such damage.
 * @par
 *     Permission is hereby granted to use, copy, modify, and distribute this
 *     source code, or portions hereof, documentation and executables, for any
 *     purpose, without fee, subject to the following restrictions:
 * @par
 *        1. The origin of this source code must not be misrepresented.
 *        2. Altered versions must be plainly marked as such and must not be
 *           misrepresented as being the original source.
 *        3. This Copyright notice may not be removed or altered from any source
 *           or altered source distribution.
 * @par
 *     The copyright holders and contributing author(s) specifically permit,
 *     without fee, and encourage the use of this source code as a component for
 *     supporting the Hypertext Markup Language in commercial products. If you
 *     use this source code in a product, acknowledgment is not required but
 *     would be appreciated.
 *
 * @date Created 2001-05-20 by Charles Reitzel
 * @date Updated 2002-07-01 by Charles Reitzel - 1st Implementation
 * @date Updated 2015-06-09 by Geoff R. McLane - Add more doxygen syntax
 * @date Additional updates: consult git log
 ******************************************************************************/

#include "tidyplatform.h"
#include "tidyenum.h"

#ifdef __cplusplus
extern "C" {
#endif
    
/***************************************************************************//**
 ** @defgroup internal_api Internal API
 ** The Internal API is used exclusively within LibTidy. If you are an
 ** HTML Tidy developer, then the internals API will be of especial
 ** importance to you.
 **
 ** @note Always check first to determine whether or not an internal API
 **       representation exists for a public API function before invoking a
 **       public API function internally. In most cases, the public API
 **       functions simply call an internal function.
 ** - - -
 ** @note This documentation _is not_ a substitute for browsing the source
 **       code. Although the public API is fairly well documented, the
 **       internal API is a very long, very slow, work-in-progress.
 ******************************************************************************/

/***************************************************************************//**
 ** @defgroup public_api External Public API
 ** The Public API is the API that LibTidy programmers must access in order 
 ** to harness HTML Tidy as a library. The API limits all exposure to internal
 ** structures and provides only accessors that return simple types such as
 ** C strings and integers, which makes it quite suitable for integration with
 ** any number of other languages.
 ** @{
 ******************************************************************************/


/* MARK: - Opaque Types */
/***************************************************************************//**
 ** @defgroup Opaque Opaque Types
 **
 ** Instances of these types are returned by LibTidy API functions, however
 ** they are opaque; you cannot see into them, and must use accessor functions
 ** to access the contents. This ensures that interfacing to LibTidy remains
 ** as universal as possible.
 **
 ** @note Internally LibTidy developers will cast these to internal
 **       implementation types with access to all member fields.
 ** @{
 ******************************************************************************/

/** @struct TidyDoc
 ** Instances of this represent a Tidy document, which encapsulates everything
 ** there is to know about a single Tidy session. Many of the API functions
 ** return instance of TidyDoc, or expect instances as parameters.
 */

/** @struct TidyOption
 ** Instances of this represent a Tidy configuration option, which contains
 ** useful data about these options. Functions related to configuration options
 ** return or accept instances of this type.
 */

/** @struct TidyNode
 ** Single nodes of a TidyDocument are represented by this datatype. It can be
 ** returned by various API functions, or accepted as a function argument.
 */

/** @struct TidyAttr
 ** Attributes of a TidyNode are represented by this data type. The public API
 ** functions related to attributes work with this type.
 */

/** @struct TidyMessage
 ** Instances of this type represent messages generated by Tidy in reference
 ** to your document. This API is available in some of Tidy's message callback
 ** functions.
*/

/** @struct TidyMessageArgument
 ** Instances of this type represent the arguments that compose part of the
 ** message represented by TidyMessage. These arguments have an API to query
 ** information about them.
*/

/* Prevent Doxygen from listing these as functions. */
#ifndef DOXYGEN_SHOULD_SKIP_THIS

opaque_type( TidyDoc );
opaque_type( TidyOption );
opaque_type( TidyNode );
opaque_type( TidyAttr );
opaque_type( TidyMessage );
opaque_type( TidyMessageArgument );

#endif


/** @} end Opaque group */
/* MARK: - Memory Allocation */
/***************************************************************************//**
 ** @defgroup Memory Memory Allocation
 **
 ** Tidy can use a user-provided allocator for all memory allocations.  If this
 ** allocator is not provided, then a default allocator is used which simply
 ** wraps standard C malloc()/free() calls. These wrappers call the panic()
 ** function upon any failure. The default panic function prints an out of
 ** memory message to **stderr**, and calls `exit(2)`.
 **
 ** For applications in which it is unacceptable to abort in the case of memory
 ** allocation, then the panic function can be replaced with one which
 ** `longjmps()` out of the LibTidy code. For this to clean up completely, you
 ** should be careful not to use any Tidy methods that open files as these will
 ** not be closed before `panic()` is called.
 **
 ** Calling the `xxxWithAllocator()` family (`tidyCreateWithAllocator`,
 ** `tidyBufInitWithAllocator`, `tidyBufAllocWithAllocator`) allow setting
 ** custom allocators.
 **
 ** All parts of the document use the same allocator. Calls that require a
 ** user-provided buffer can optionally use a different allocator.
 **
 ** For reference in designing a plug-in allocator, most allocations made by
 ** LibTidy are less than 100 bytes, corresponding to attribute names and
 ** values, etc.
 **
 ** There is also an additional class of much larger allocations which are where
 ** most of the data from the lexer is stored. It is not currently possible to
 ** use a separate allocator for the lexer; this would be a useful extension.
 **
 ** In general, approximately 1/3rd of the memory used by LibTidy is freed
 ** during the parse, so if memory usage is an issue then an allocator that can
 ** reuse this memory is a good idea.
 **
 ** **To create your own allocator, do something like the following:**
 ** @code{.c}
 ** typedef struct _MyAllocator {
 **    TidyAllocator base;
 **    // ...other custom allocator state...
 ** } MyAllocator;
 **
 ** void* MyAllocator_alloc(TidyAllocator *base, void *block, size_t nBytes) {
 **     MyAllocator *self = (MyAllocator*)base;
 **     // ...
 ** }
 ** // etc.
 **
 ** static const TidyAllocatorVtbl MyAllocatorVtbl = {
 **     MyAllocator_alloc,
 **     MyAllocator_realloc,
 **     MyAllocator_free,
 **     MyAllocator_panic
 ** };
 **
 ** myAllocator allocator;
 ** TidyDoc doc;
 **
 ** allocator.base.vtbl = &MyAllocatorVtbl;
 ** //...initialise allocator specific state...
 ** doc = tidyCreateWithAllocator(&allocator);
 ** @endcode
 **
 ** Although this looks slightly long-winded, the advantage is that to create a
 ** custom allocator you simply need to set the vtbl pointer correctly. The vtbl
 ** itself can reside in static/global data, and hence does not need to be
 ** initialised each time an allocator is created, and furthermore the memory
 ** is shared amongst all created allocators.
 **
 ** @{
 ******************************************************************************/

/* Forward declarations and typedefs. */
struct _TidyAllocatorVtbl;
struct _TidyAllocator;

typedef struct _TidyAllocatorVtbl TidyAllocatorVtbl;
typedef struct _TidyAllocator TidyAllocator;

    
/** Tidy's built-in default allocator. */
struct _TidyAllocator {
    const TidyAllocatorVtbl *vtbl; /**< The allocator's function table. */
};


/** This structure is the function table for an allocator. Note that all
    functions in this table must be provided. */
struct _TidyAllocatorVtbl
{
/* Doxygen has no idea how to parse these. */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    void* (TIDY_CALL *alloc)( TidyAllocator *self, size_t nBytes );
    void* (TIDY_CALL *realloc)(TidyAllocator *self, void *block, size_t nBytes );
    void (TIDY_CALL *free)(TidyAllocator *self, void *block);
    void (TIDY_CALL *panic)(TidyAllocator *self, ctmbstr msg);
#else
    /** Called to allocate a block of nBytes of memory */
    void* *alloc(TidyAllocator *self, /**< The TidyAllocator to use to alloc memory. */
                 size_t nBytes        /**< The number of bytes to allocate. */
                 );

    /** Called to resize (grow, in general) a block of memory.
        Must support being called with `NULL`. */
    void* *realloc(TidyAllocator *self, /**< The TidyAllocator to use to realloc memory. */
                   void *block,         /**< The pointer to the existing block. */
                   size_t nBytes        /**< The number of bytes to allocate. */
                   );
    
    /** Called to free a previously allocated block of memory.
     */
    void *free(TidyAllocator *self,  /**< The TidyAllocator to use to free memory. */
               void *block           /**< The block to free. */
               );

    /** Called when a panic condition is detected. Must support `block == NULL`.
        This function is not called if either alloc() or realloc() fails; it is
        up to the allocator to do this. Currently this function can only be
        called if an error is detected in the tree integrity via the internal
        function CheckNodeIntegrity(). This is a situation that can only arise
        in the case of a programming error in LibTidy. You can turn off node
        integrity checking by defining the constant `NO_NODE_INTEGRITY_CHECK` 
        during the build.
    **/
    void *panic(TidyAllocator *self,  /**< The TidyAllocator to use to panic. */
                ctmbstr msg           /**< The panic message. */
                );
#endif /* Doxygen Fix */
};


/** Callback for `malloc` replacement */
typedef void* (TIDY_CALL *TidyMalloc)( size_t len );

/** Callback for `realloc` replacement */
typedef void* (TIDY_CALL *TidyRealloc)( void* buf, size_t len );

/** Callback for `free` replacement */
typedef void  (TIDY_CALL *TidyFree)( void* buf );

/** Callback for out of memory panic state */
typedef void  (TIDY_CALL *TidyPanic)( ctmbstr mssg );


/** Give Tidy a `malloc()` replacement */
TIDY_EXPORT Bool TIDY_CALL tidySetMallocCall( TidyMalloc fmalloc );

/** Give Tidy a `realloc()` replacement */
TIDY_EXPORT Bool TIDY_CALL tidySetReallocCall( TidyRealloc frealloc );

/** Give Tidy a `free()` replacement */
TIDY_EXPORT Bool TIDY_CALL tidySetFreeCall( TidyFree ffree );

/** Give Tidy an "out of memory" handler */
TIDY_EXPORT Bool TIDY_CALL tidySetPanicCall( TidyPanic fpanic );


/** @} end Memory group */
/* MARK: - Basic Operations */
/***************************************************************************//**
 ** @defgroup Basic Basic Operations
 **
 ** For an excellent example of how to invoke LibTidy, please consult
 ** `console/tidy.c:main()` for in-depth implementation details. A simplified
 ** example can be seen on our site: http://www.html-tidy.org/developer/
 **
 ** @{
 ******************************************************************************/

/** @name Instantiation and Destruction
 ** @{
 */
    
/** The primary creation of a document instance. Instances of a TidyDoc are used
 ** throughout the API as a token to represent a particular document. You must
 ** create at least one TidyDoc instance to initialize the library and begin
 ** interaction with the API. When done using a TidyDoc instance, be sure to
 ** `tidyRelease(myTidyDoc);` in order to free related memory.
 ** @result Returns a TidyDoc instance.
 */
TIDY_EXPORT TidyDoc TIDY_CALL     tidyCreate(void);

/** Create a document supplying your own, custom TidyAllocator instead of using
 ** the built-in default. See the @ref Memory module if you want to create and
 ** use your own allocator.
 ** @param allocator The allocator to use for creating the document.
 ** @result Returns a TidyDoc instance.
 */
TIDY_EXPORT TidyDoc TIDY_CALL     tidyCreateWithAllocator(TidyAllocator *allocator);

/** Free all memory and release the TidyDoc. The TidyDoc can not be used after 
 ** this call.
 ** @param tdoc The TidyDoc to free.
 */
TIDY_EXPORT void TIDY_CALL        tidyRelease(TidyDoc tdoc);

    
/** @}
 ** @name Host Application Data
 ** @{
 */
   
 
/** Allows the host application to store a chunk of data with each TidyDoc
 ** instance. This can be useful for callbacks, such as saving a reference to
 ** `self` within the document.
 */
TIDY_EXPORT void TIDY_CALL        tidySetAppData(TidyDoc tdoc,  /**< The document in which to store the data. */
                                                 void* appData  /**< The pointer to a block of data to store. */
                                                 );

/** Returns the data previously stored with `tidySetAppData()`.
 ** @param tdoc  document where data has been stored.
 ** @result The pointer to the data block previously stored. 
 */
TIDY_EXPORT void* TIDY_CALL       tidyGetAppData(TidyDoc tdoc);

    
/** @}
 ** @name LibTidy Version Information
 ** @{
 */

    
/** Get the release date for the current library.
 ** @result The string representing the release date.
 */
TIDY_EXPORT ctmbstr TIDY_CALL     tidyReleaseDate(void);

/** Get the version number for the current library.
 ** @result The string representing the version number.
 */
TIDY_EXPORT ctmbstr TIDY_CALL     tidyLibraryVersion(void);

/** Get the platform for which Tidy was built.
 ** @result The string representing the version number.
 */
TIDY_EXPORT ctmbstr TIDY_CALL     tidyPlatform(void);

    
/** @}
 ** @name Diagnostics and Repair
 ** @{
 */

    
/** Get status of current document.
 ** @param tdoc An instance of a TidyDoc to query.
 ** @result Returns the highest of `2` indicating that errors were present in
 **         the document, `1` indicating warnings, and `0` in the case of
 **         everything being okay.
 */
TIDY_EXPORT int TIDY_CALL         tidyStatus( TidyDoc tdoc );

/** Gets the version of HTML that was output, as an integer, times 100. For
 ** example, HTML5 will return 500; HTML4.0.1 will return 401.
 ** @param tdoc An instance of a TidyDoc to query.
 ** @result Returns the HTML version number (x100).
 */
TIDY_EXPORT int TIDY_CALL         tidyDetectedHtmlVersion( TidyDoc tdoc );

/** Indicates whether the output document is or isn't XHTML.
 ** @param tdoc An instance of a TidyDoc to query.
 ** @result Returns `yes` if the document is an XHTML type.
 */
TIDY_EXPORT Bool TIDY_CALL        tidyDetectedXhtml( TidyDoc tdoc );

/** Indicates whether or not the input document was XML. If TidyXml tags is
 ** true, or there was an XML declaration in the input document, then this
 ** function will return yes.
 ** @param tdoc An instance of a TidyDoc to query.
 ** @result Returns `yes` if the input document was XML.
 */
TIDY_EXPORT Bool TIDY_CALL        tidyDetectedGenericXml( TidyDoc tdoc );

/** Indicates the number of TidyError messages that were generated. For any
 ** value greater than `0`, output is suppressed unless TidyForceOutput is set.
 ** @param tdoc An instance of a TidyDoc to query.
 ** @result Returns the number of TidyError messages that were generated.
 */
TIDY_EXPORT uint TIDY_CALL        tidyErrorCount( TidyDoc tdoc );

/** Indicates the number of TidyWarning messages that were generated.
 ** @param tdoc An instance of a TidyDoc to query.
 ** @result Returns the number of TidyWarning messages that were generated.
 */
TIDY_EXPORT uint TIDY_CALL        tidyWarningCount( TidyDoc tdoc );

/** Indicates the number of TidyAccess messages that were generated.
 ** @param tdoc An instance of a TidyDoc to query.
 ** @result Returns the number of TidyAccess messages that were generated.
 */
TIDY_EXPORT uint TIDY_CALL        tidyAccessWarningCount( TidyDoc tdoc );

/** Indicates the number of configuration error messages that were generated.
 ** @param tdoc An instance of a TidyDoc to query.
 ** @result Returns the number of configuration error messages that were
 **         generated.
 */
TIDY_EXPORT uint TIDY_CALL        tidyConfigErrorCount( TidyDoc tdoc );

/** Write more complete information about errors to current error sink.
 ** @param tdoc An instance of a TidyDoc to query.
 */
TIDY_EXPORT void TIDY_CALL        tidyErrorSummary( TidyDoc tdoc );

/** Write more general information about markup to current error sink.
 ** @param tdoc An instance of a TidyDoc to query.
 */
TIDY_EXPORT void TIDY_CALL        tidyGeneralInfo( TidyDoc tdoc );


/** @}
 ** @name Configuration, File, and Encoding Operations
 ** @{
 */
    
    
/** Load an ASCII Tidy configuration file and set the configuration per its
 ** contents. Reports config option errors, which can be filtered.
 ** @result Returns 0 upon success, or any other value if there was an option error.
 */
TIDY_EXPORT int TIDY_CALL         tidyLoadConfig(TidyDoc tdoc,      /**< The TidyDoc to which to apply the configuration. */
                                                 ctmbstr configFile /**< The complete path to the file to load. */
                                                 );

/** Load a Tidy configuration file with the specified character encoding, and
 ** set the configuration per its contents.  Reports config option errors, which can be filtered.
 ** @result Returns 0 upon success, or any other value if there was an option error.
 */
TIDY_EXPORT int TIDY_CALL         tidyLoadConfigEnc(TidyDoc tdoc,       /**< The TidyDoc to which to apply the configuration. */
                                                    ctmbstr configFile, /**< The complete path to the file to load. */
                                                    ctmbstr charenc     /**< The encoding to use. See the _enc2iana struct for valid values. */
                                                    );

/** Determine whether or not a particular file exists. On Unix systems, the use
 ** of the tilde to represent the user's home directory is supported.
 ** @result Returns `yes` or `no`, indicating whether or not the file exists.
 */
TIDY_EXPORT Bool TIDY_CALL        tidyFileExists(TidyDoc tdoc,     /**< The TidyDoc on whose behalf you are checking. */
                                                 ctmbstr filename  /**< The path to the file whose existence you wish to check. */
                                                 );


/** Set the input/output character encoding for parsing markup. Valid values
 ** include `ascii`, `latin1`, `raw`, `utf8`, `iso2022`, `mac`, `win1252`,
 ** `utf16le`, `utf16be`, `utf16`, `big5`, and `shiftjis`. These values are not
 ** case sensitive.
 ** @note This is the same as using TidySetInCharEncoding() and 
 **       TidySetOutCharEncoding() to set the same value.
 ** @result Returns 0 upon success, or a system standard error number `EINVAL`.
 */
TIDY_EXPORT int TIDY_CALL         tidySetCharEncoding(TidyDoc tdoc,  /**< The TidyDoc for which you are setting the encoding. */
                                                      ctmbstr encnam /**< The encoding name as described above. */
                                                      );

/** Set the input encoding for parsing markup.  Valid values include `ascii`, 
 ** `latin1`, `raw`, `utf8`, `iso2022`, `mac`, `win1252`, `utf16le`, `utf16be`,
 ** `utf16`, `big5`, and `shiftjis`. These values are not case sensitive.
 ** @result Returns 0 upon success, or a system standard error number `EINVAL`.
 */
TIDY_EXPORT int TIDY_CALL         tidySetInCharEncoding(TidyDoc tdoc,  /**< The TidyDoc for which you are setting the encoding. */
                                                        ctmbstr encnam /**< The encoding name as described above. */
                                                        );

/** Set the input encoding for writing markup.  Valid values include `ascii`,
 ** `latin1`, `raw`, `utf8`, `iso2022`, `mac`, `win1252`, `utf16le`, `utf16be`,
 ** `utf16`, `big5`, and `shiftjis`. These values are not case sensitive.
 ** @result Returns 0 upon success, or a system standard error number `EINVAL`.
 */
TIDY_EXPORT int TIDY_CALL         tidySetOutCharEncoding(TidyDoc tdoc,  /**< The TidyDoc for which you are setting the encoding. */
                                                         ctmbstr encnam /**< The encoding name as described above. */
                                                         );


/** @} */
/** @} end Basic group */
/* MARK: - Configuration Options */
/***************************************************************************//**
 ** @defgroup Configuration Configuration Options
 **
 ** Functions for getting and setting Tidy configuration options.
 **
 ** @note In general, you should expect that options you set should stay set.
 **       This isn't always the case, though, because Tidy will adjust options
 **       for internal use during the lexing, parsing, cleaning, and printing
 **       phases. If you require access to user configuration values at any
 **       time after the tidyParseXXX() process, make sure to keep your own
 **       copy, or use tidyOptResetToSnapshot() when you no longer need to
 **       use any other tidy functions.
 ** @{
 ******************************************************************************/

/** @name Option Callback Functions
 ** @{
 */

/** This typedef represents the required signature for your provided callback
 ** function should you wish to register one with tidySetOptionCallback().
 ** Your callback function will be provided with the following parameters.
 ** Note that this is deprecated and you should instead migrate to
 ** tidySetConfigCallback().
 ** @param option The option name that was provided.
 ** @param value The option value that was provided
 ** @return Your callback function will return `yes` if it handles the provided
 **         option, or `no` if it does not. In the latter case, Tidy will issue
 **         an unknown configuration option error.
 */
typedef Bool (TIDY_CALL *TidyOptCallback)(ctmbstr option, ctmbstr value);

/** Applications using TidyLib may want to augment command-line and
 ** configuration file options. Setting this callback allows a LibTidy
 ** application developer to examine command-line and configuration file options
 ** after LibTidy has examined them and failed to recognize them.
 ** Note that this is deprecated and you should instead migrate to
 ** tidySetConfigCallback().
 ** @result Returns `yes` upon success.
 */
TIDY_EXPORT Bool TIDY_CALL          tidySetOptionCallback(TidyDoc tdoc,                /**< The document to apply the callback to. */
                                                          TidyOptCallback pOptCallback /**< The name of a function of type TidyOptCallback() to serve as your callback. */
                                                          );

/** This typedef represents the required signature for your provided callback
 ** function should you wish to register one with tidySetConfigCallback().
 ** Your callback function will be provided with the following parameters.
 ** @param tdoc The document instance for which the callback was invoked.
 ** @param option The option name that was provided.
 ** @param value The option value that was provided
 ** @return Your callback function will return `yes` if it handles the provided
 **         option, or `no` if it does not. In the latter case, Tidy will issue
 **         an unknown configuration option error.
 */
typedef Bool (TIDY_CALL *TidyConfigCallback)(TidyDoc tdoc, ctmbstr option, ctmbstr value);

/** Applications using TidyLib may want to augment command-line and
 ** configuration file options. Setting this callback allows a LibTidy
 ** application developer to examine command-line and configuration file options
 ** after LibTidy has examined them and failed to recognize them.
 ** @result Returns `yes` upon success.
 */
TIDY_EXPORT Bool TIDY_CALL          tidySetConfigCallback(TidyDoc tdoc,                      /**< The document to apply the callback to. */
                                                          TidyConfigCallback pConfigCallback /**< The name of a function of type TidyConfigCallback() to serve as your callback. */
                                                          );

    
/** This typedef represents the required signature for your provided callback
 ** function should you wish to register one with tidySetConfigChangeCallback().
 ** Your callback function will be provided with the following parameters.
 ** @param tdoc The document instance for which the callback was invoked.
 ** @param option The option that will be changed.
 */
typedef void (TIDY_CALL *TidyConfigChangeCallback)(TidyDoc tdoc, TidyOption option);

/** Applications using TidyLib may want to be informed when changes to options
 ** are made. Temporary changes made internally by Tidy are not reported, but
 ** permanent changes made by Tidy (such as indent-spaces or output-encoding)
 ** will be reported.
 ** @note This callback is not currently implemented.
 ** @result Returns `yes` upon success.
 */
TIDY_EXPORT Bool TIDY_CALL          tidySetConfigChangeCallback(TidyDoc tdoc,                      /**< The document to apply the callback to. */
                                                                TidyConfigChangeCallback pCallback /**< The name of a function of type TidyConfigChangeCallback() to serve as your callback. */
                                                                );


/** @}
 ** @name Option ID Discovery
 ** @{
 */

/** Get ID of given Option
 ** @param opt An instance of a TidyOption to query.
 ** @result The TidyOptionId of the given option.
 */
TIDY_EXPORT TidyOptionId TIDY_CALL  tidyOptGetId( TidyOption opt );

/** Returns the TidyOptionId (enum value) by providing the name of a Tidy
 ** configuration option.
 ** @param optnam The name of the option ID to retrieve.
 ** @result The TidyOptionId of the given `optname`.
 */
TIDY_EXPORT TidyOptionId TIDY_CALL  tidyOptGetIdForName(ctmbstr optnam);

/** @}
 ** @name Getting Instances of Tidy Options
 ** @{
 */

/** Initiates an iterator for a list of TidyOption instances, which allows you
 ** to iterate through all of the available options. In order to iterate through
 ** the available options, initiate the iterator with this function, and then
 ** use tidyGetNextOption() to retrieve the first and subsequent options. For
 ** example:
 ** @code{.c}
 **   TidyIterator itOpt = tidyGetOptionList( tdoc );
 **   while ( itOpt ) {
 **     TidyOption opt = tidyGetNextOption( tdoc, &itOpt );
 **     // Use other API to query or set set option values
 **   }
 ** @endcode
 ** @param tdoc An instance of a TidyDoc to query.
 ** @result Returns a TidyIterator, which is a token used to represent the
 **         current position in a list within LibTidy.
 */
TIDY_EXPORT TidyIterator TIDY_CALL  tidyGetOptionList( TidyDoc tdoc );

/** Given a valid TidyIterator initiated with tidyGetOptionList(), returns
 ** the instance of the next TidyOption.
 ** @note This function will return internal-only option types including
 **       `TidyInternalCategory`; you should *never* use these. Always ensure
 **       that you use `tidyOptGetCategory()` before assuming that an option
 **       is okay to use in your application.
 ** @result An instance of TidyOption.
 */
TIDY_EXPORT TidyOption TIDY_CALL    tidyGetNextOption(TidyDoc tdoc,     /**< The document for which you are retrieving options. */
                                                      TidyIterator* pos /**< The TidyIterator (initiated with tidyGetOptionList()) token. */
                                                      );

/** Retrieves an instance of TidyOption given a valid TidyOptionId.
 ** @result An instance of TidyOption matching the provided TidyOptionId.
 */
TIDY_EXPORT TidyOption TIDY_CALL    tidyGetOption(TidyDoc tdoc,      /**< The document for which you are retrieving the option. */
                                                  TidyOptionId optId /**< The TidyOptionId to retrieve. */
                                                  );

/** Returns an instance of TidyOption by providing the name of a Tidy
 ** configuration option.
 ** @result The TidyOption of the given `optname`.
 */
TIDY_EXPORT TidyOption TIDY_CALL    tidyGetOptionByName(TidyDoc tdoc,  /**< The document for which you are retrieving the option. */
                                                        ctmbstr optnam /**< The name of the Tidy configuration option. */
                                                        );

/** @}
 ** @name Information About Options
 ** @{
 */

/** Get name of given Option
 ** @param opt An instance of a TidyOption to query.
 ** @result The name of the given option.
 */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetName( TidyOption opt );

/** Get datatype of given Option
 ** @param opt An instance of a TidyOption to query.
 ** @result The TidyOptionType of the given option.
 */
TIDY_EXPORT TidyOptionType TIDY_CALL tidyOptGetType( TidyOption opt );

/** Indicates that an option takes a list of items.
 ** @param opt An instance of a TidyOption to query.
 ** @result A bool indicating whether or not the option accepts a list.
 */
TIDY_EXPORT Bool TIDY_CALL tidyOptionIsList( TidyOption opt );

/** Is Option read-only? Some options (mainly internal use only options) are
 ** read-only.
 ** @deprecated This is no longer a valid test for the public API; instead
 **   you should test an option's availability using `tidyOptGetCategory()`
 **   against `TidyInternalCategory`. This API will be removed!
 ** @param opt An instance of a TidyOption to query.
 ** @result Returns `yes` or `no` depending on whether or not the specified
 **         option is read-only.
 */
TIDY_EXPORT Bool TIDY_CALL          tidyOptIsReadOnly( TidyOption opt );

/** Get category of given Option
 ** @param opt An instance of a TidyOption to query.
 ** @result The TidyConfigCategory of the specified option.
 */
TIDY_EXPORT TidyConfigCategory TIDY_CALL tidyOptGetCategory( TidyOption opt );

/** Get default value of given Option as a string 
 ** @param opt An instance of a TidyOption to query.
 ** @result A string indicating the default value of the specified option.
 */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetDefault( TidyOption opt );

/** Get default value of given Option as an unsigned integer 
 ** @param opt An instance of a TidyOption to query.
 ** @result An unsigned integer indicating the default value of the specified
 **         option.
 */
TIDY_EXPORT ulong TIDY_CALL         tidyOptGetDefaultInt( TidyOption opt );

/** Get default value of given Option as a Boolean value 
 ** @param opt An instance of a TidyOption to query.
 ** @result A boolean indicating the default value of the specified option.
 */
TIDY_EXPORT Bool TIDY_CALL          tidyOptGetDefaultBool( TidyOption opt );

/** Initiates an iterator for a list of TidyOption pick-list values, which
 ** allows you iterate through all of the available option values. In order to
 ** iterate through the available values, initiate the iterator with this
 ** function, and then use tidyOptGetNextPick() to retrieve the first and 
 ** subsequent option values. For example:
 ** @code{.c}
 **   TidyIterator itOpt = tidyOptGetPickList( opt );
 **   while ( itOpt ) {
 **     printf("%s", tidyOptGetNextPick( opt, &itOpt ));
 **   }
 ** @endcode
 ** @param opt An instance of a TidyOption to query.
 ** @result Returns a TidyIterator, which is a token used to represent the
 **         current position in a list within LibTidy.
 */
TIDY_EXPORT TidyIterator TIDY_CALL  tidyOptGetPickList( TidyOption opt );

/** Given a valid TidyIterator initiated with tidyOptGetPickList(), returns a
 ** string representing a possible option value.
 ** @result A string containing the next pick-list option value.
 */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetNextPick(TidyOption opt,   /**< An instance of a TidyOption to query. */
                                                       TidyIterator* pos /**< The TidyIterator (initiated with tidyOptGetPickList()) token. */
                                                       );

/** @}
 ** @name Option Value Functions
 ** @{
 */

/** Get the current value of the option ID for the given document.
 ** @remark The optId *must* have a @ref TidyOptionType of @ref TidyString!
 */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetValue(TidyDoc tdoc,      /**< The tidy document whose option value you wish to check. */
                                                    TidyOptionId optId /**< The option ID whose value you wish to check. */
                                                    );

/** Set the option value as a string.
 ** @remark The optId *must* have a @ref TidyOptionType of @ref TidyString!
 ** @result Returns a bool indicating success or failure.
 */
TIDY_EXPORT Bool TIDY_CALL          tidyOptSetValue(TidyDoc tdoc,       /**< The tidy document for which to set the value. */
                                                    TidyOptionId optId, /**< The option ID of the value to set. */
                                                    ctmbstr val         /**< The string value to set. */
                                                    );

/** Set named option value as a string, regardless of the @ref TidyOptionType.
 ** @remark This is good setter if you are unsure of the type.
 ** @result Returns a bool indicating success or failure.
 */
TIDY_EXPORT Bool TIDY_CALL          tidyOptParseValue(TidyDoc tdoc,   /**< The tidy document for which to set the value. */
                                                      ctmbstr optnam, /**< The name of the option to set; this is the string value from the UI, e.g., `error-file`. */
                                                      ctmbstr val     /**< The value to set, as a string. */
                                                      );

/** Get current option value as an integer.
 ** @result Returns the integer value of the specified option.
 */
TIDY_EXPORT ulong TIDY_CALL         tidyOptGetInt(TidyDoc tdoc,      /**< The tidy document for which to get the value. */
                                                  TidyOptionId optId /**< The option ID to get. */
                                                  );

/** Set option value as an integer.
 ** @result Returns a bool indicating success or failure.
 */
TIDY_EXPORT Bool TIDY_CALL          tidyOptSetInt(TidyDoc tdoc,       /**< The tidy document for which to set the value. */
                                                  TidyOptionId optId, /**< The option ID to set. */
                                                  ulong val           /**< The value to set. */
                                                  );

/** Get current option value as a Boolean flag.
 ** @result Returns a bool indicating the value.
 */
TIDY_EXPORT Bool TIDY_CALL          tidyOptGetBool(TidyDoc tdoc,      /**< The tidy document for which to get the value. */
                                                   TidyOptionId optId /**< The option ID to get. */
                                                   );

/** Set option value as a Boolean flag.
 ** @result Returns a bool indicating success or failure.
 */
TIDY_EXPORT Bool TIDY_CALL          tidyOptSetBool(TidyDoc tdoc,       /**< The tidy document for which to set the value. */
                                                   TidyOptionId optId, /**< The option ID to set. */
                                                   Bool val            /**< The value to set. */
                                                   );

/** Reset option to default value by ID.
 ** @result Returns a bool indicating success or failure.
 */
TIDY_EXPORT Bool TIDY_CALL          tidyOptResetToDefault(TidyDoc tdoc,    /**< The tidy document for which to reset the value. */
                                                          TidyOptionId opt /**< The option ID to reset. */
                                                          );

/** Reset all options to their default values.
 ** @param tdoc The tidy document for which to reset all values.
 ** @result Returns a bool indicating success or failure.
 */
TIDY_EXPORT Bool TIDY_CALL          tidyOptResetAllToDefault( TidyDoc tdoc );

/** Take a snapshot of current config settings. These settings are stored
 ** within the tidy document. Note, however, that snapshots do not reliably
 ** survive the tidyParseXXX() process, as Tidy uses the snapshot mechanism
 ** in order to store the current configuration right at the beginning of the
 ** parsing process.
 ** @param tdoc The tidy document for which to take a snapshot.
 ** @result Returns a bool indicating success or failure.
 */
TIDY_EXPORT Bool TIDY_CALL          tidyOptSnapshot( TidyDoc tdoc );

/** Apply a snapshot of config settings to a document.
 ** @param tdoc The tidy document for which to apply a snapshot.
 ** @result Returns a bool indicating success or failure.
 */
TIDY_EXPORT Bool TIDY_CALL          tidyOptResetToSnapshot( TidyDoc tdoc );

/** Any settings different than default? 
 ** @param tdoc The tidy document to check.
 ** @result Returns a bool indicating whether or not a difference exists.
 */
TIDY_EXPORT Bool TIDY_CALL          tidyOptDiffThanDefault( TidyDoc tdoc );

/** Any settings different than snapshot?
 ** @param tdoc The tidy document to check.
 ** @result Returns a bool indicating whether or not a difference exists.
 */
TIDY_EXPORT Bool TIDY_CALL          tidyOptDiffThanSnapshot( TidyDoc tdoc );

/** Copy current configuration settings from one document to another. Note
 ** that the destination document's existing settings will be stored as that
 ** document's snapshot prior to having its option values overwritten by the
 ** source document's settings.
 ** @result Returns a bool indicating success or failure.
 */
TIDY_EXPORT Bool TIDY_CALL          tidyOptCopyConfig(TidyDoc tdocTo,  /**< The destination tidy document. */
                                                      TidyDoc tdocFrom /**< The source tidy document. */
                                                      );

/** Get character encoding name. Used with @ref TidyCharEncoding,
 ** @ref TidyOutCharEncoding, and @ref TidyInCharEncoding.
 ** @result The encoding name as a string for the specified option.
 */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetEncName(TidyDoc tdoc,      /**< The tidy document to query. */
                                                      TidyOptionId optId /**< The option ID whose value to check. */
                                                      );

/** Get the current pick list value for the option ID, which can be useful for
 ** enum types.
 ** @result Returns a string indicating the current value of the specified
 **         option.
 */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetCurrPick(TidyDoc tdoc,      /**< The tidy document to query. */
                                                       TidyOptionId optId /**< The option ID whose value to check. */
                                                       );

/** Initiates an iterator for a list of user-declared tags, including autonomous
 ** custom tags detected in the document if @ref TidyUseCustomTags is not set to
 ** **no**. This iterator allows you to iterate through all of the custom tags. 
 ** In order to iterate through the tags, initiate the iterator with this
 ** function, and then use tidyOptGetNextDeclTag() to retrieve the first and
 ** subsequent tags. For example:
 ** @code{.c}
 **   TidyIterator itTag = tidyOptGetDeclTagList( tdoc );
 **   while ( itTag ) {
 **     printf("%s", tidyOptGetNextDeclTag( tdoc, TidyBlockTags, &itTag ));
 **   }
 ** @endcode
 ** @param tdoc An instance of a TidyDoc to query.
 ** @result Returns a TidyIterator, which is a token used to represent the
 **         current position in a list within LibTidy.
 */
TIDY_EXPORT TidyIterator TIDY_CALL  tidyOptGetDeclTagList( TidyDoc tdoc );

/** Given a valid TidyIterator initiated with tidyOptGetDeclTagList(), returns a
 ** string representing a user-declared or autonomous custom tag.
 ** @remark Specifying optId limits the scope of the tags to one of 
 **         @ref TidyInlineTags, @ref TidyBlockTags, @ref TidyEmptyTags, or 
 **         @ref TidyPreTags. Note that autonomous custom tags (if used) are
 **         added to one of these option types, depending on the value of
 **         @ref TidyUseCustomTags.
 ** @result A string containing the next tag.
 */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetNextDeclTag(TidyDoc tdoc,       /**< The tidy document to query. */
                                                          TidyOptionId optId, /**< The option ID matching the type of tag to retrieve. */
                                                          TidyIterator* iter  /**< The TidyIterator (initiated with tidyOptGetDeclTagList()) token.  */
                                                          );

/** Initiates an iterator for a list of priority attributes. This iterator
 ** allows you to iterate through all of the priority attributes defined with
 ** the `priority-attributes` configuration option. In order to iterate through
 ** the attributes, initiate the iterator with this function, and then use
 ** tidyOptGetNextPriorityAttr() to retrieve the first and subsequent attributes.
 ** For example:
 ** @code{.c}
 **   TidyIterator itAttr = tidyOptGetPriorityAttrList( tdoc );
 **   while ( itAttr ) {
 **     printf("%s", tidyOptGetNextPriorityAttr( tdoc, &itAttr ));
 **   }
 ** @endcode
 ** @param tdoc An instance of a TidyDoc to query.
 ** @result Returns a TidyIterator, which is a token used to represent the
 **         current position in a list within LibTidy.
 */
TIDY_EXPORT TidyIterator TIDY_CALL  tidyOptGetPriorityAttrList( TidyDoc tdoc );

/** Given a valid TidyIterator initiated with tidyOptGetPriorityAttrList(),
 ** returns a string representing a priority attribute.
 ** @result A string containing the next tag.
 */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetNextPriorityAttr(TidyDoc tdoc,       /**< The tidy document to query. */
                                                               TidyIterator* iter  /**< The TidyIterator (initiated with tidyOptGetPriorityAttrList()) token.  */
                                                               );

/** Initiates an iterator for a list of muted messages. This iterator allows
 ** you to iterate through all of the priority attributes defined with the
 ** `mute` configuration option. In order to iterate through the list, initiate
 ** with this function, and then use tidyOptGetNextMutedMessage() to retrieve
 ** the first and subsequent attributes.
 ** For example:
 ** @code{.c}
 **   TidyIterator itAttr = tidyOptGetMutedMessageList( tdoc );
 **   while ( itAttr ) {
 **     printf("%s", tidyOptGetNextMutedMessage( tdoc, &itAttr ));
 **   }
 ** @endcode
 ** @param tdoc An instance of a TidyDoc to query.
 ** @result Returns a TidyIterator, which is a token used to represent the
 **         current position in a list within LibTidy.
 */
TIDY_EXPORT TidyIterator TIDY_CALL  tidyOptGetMutedMessageList( TidyDoc tdoc );

/** Given a valid TidyIterator initiated with tidyOptGetMutedMessageList(),
 ** returns a string representing a muted message.
 ** @result A string containing the next tag.
 */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetNextMutedMessage(TidyDoc tdoc,       /**< The tidy document to query. */
                                                               TidyIterator* iter  /**< The TidyIterator (initiated with tidyOptGetMutedMessageList()) token.  */
                                                               );

/** @}
 ** @name Option Documentation
 ** @{
 */

/** Get the description of the specified option.
 ** @result Returns a string containing a description of the given option.
 */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetDoc(TidyDoc tdoc,  /**< The tidy document to query. */
                                                  TidyOption opt /**< The option ID of the option. */
                                                  );

/** Initiates an iterator for a list of options related to a given option. This
 ** iterator allows you to iterate through all of the related options, if any.
 ** In order to iterate through the options, initiate the iterator with this
 ** function, and then use tidyOptGetNextDocLinks() to retrieve the first and
 ** subsequent options. For example:
 ** @code{.c}
 **   TidyIterator itOpt = tidyOptGetDocLinksList( tdoc, TidyJoinStyles );
 **   while ( itOpt ) {
 **     TidyOption my_option = tidyOptGetNextDocLinks( tdoc, &itOpt );
 **     // do something with my_option
 **   }
 ** @endcode
 ** @result Returns a TidyIterator, which is a token used to represent the
 **         current position in a list within LibTidy.
 */
TIDY_EXPORT TidyIterator TIDY_CALL  tidyOptGetDocLinksList(TidyDoc tdoc,  /**< The tidy document to query. */
                                                           TidyOption opt /**< The option whose related options you wish to find. */
                                                           );

/** Given a valid TidyIterator initiated with tidyOptGetDocLinksList(), returns
 ** a TidyOption instance.
 ** @result Returns in instance of TidyOption.
 */
TIDY_EXPORT TidyOption TIDY_CALL    tidyOptGetNextDocLinks(TidyDoc tdoc,     /**< The tidy document to query. */
                                                           TidyIterator* pos /**< The TidyIterator (initiated with tidyOptGetDocLinksList()) token. */
                                                           );

/** @} */
/** @} end Configuration group */
/* MARK: - I/O and Messages */
/***************************************************************************//**
 ** @defgroup IO I/O and Messages
 **
 ** Tidy provides flexible I/O. By default, Tidy will define, create and use 
 ** instances of input and output handlers for standard C buffered I/O (i.e.,
 ** `FILE* stdin`, `FILE* stdout`, and `FILE* stderr` for content input,
 ** content output and diagnostic output, respectively. A `FILE* cfgFile` 
 ** input handler will be used for config files. Command line options will
 ** just be set directly.
 **
 ** @{
 ******************************************************************************/

/** @name Forward declarations and typedefs.
 ** @{ 
 */

TIDY_STRUCT struct _TidyBuffer;
typedef struct _TidyBuffer TidyBuffer;

/** @}
 ** @name Input Source
 ** If you wish to write to your own input sources, then these types, structs,
 ** and functions will allow them to work seamlessly with Tidy.
 ** @{
 */

/** End of input "character" */
#define EndOfStream (~0u)

/** Input Callback: get next byte of input */
typedef int  (TIDY_CALL *TidyGetByteFunc)( void* sourceData );

/** Input Callback: unget a byte of input */
typedef void (TIDY_CALL *TidyUngetByteFunc)( void* sourceData, byte bt );

/** Input Callback: is end of input? */
typedef Bool (TIDY_CALL *TidyEOFFunc)( void* sourceData );

/** This type defines an input source capable of delivering raw bytes of input.
 */
TIDY_STRUCT
typedef struct _TidyInputSource
{
  void*               sourceData;  /**< Input context. Passed to callbacks. */

  TidyGetByteFunc     getByte;     /**< Pointer to "get byte" callback. */
  TidyUngetByteFunc   ungetByte;   /**< Pointer to "unget" callback. */
  TidyEOFFunc         eof;         /**< Pointer to "eof" callback. */
} TidyInputSource;

/** Facilitates user defined source by providing an entry point to marshal
 ** pointers-to-functions. This is needed by .NET, and possibly other language
 ** bindings.
 ** @result Returns a bool indicating success or failure.
 */
TIDY_EXPORT Bool TIDY_CALL tidyInitSource(TidyInputSource*  source,  /**< The source to populate with data. */
                                          void*             srcData, /**< The input context. */
                                          TidyGetByteFunc   gbFunc,  /**< Pointer to the "get byte" callback. */
                                          TidyUngetByteFunc ugbFunc, /**< Pointer to the "unget" callback. */
                                          TidyEOFFunc       endFunc  /**< Pointer to the "eof" callback. */
                                          );

/** Helper: get next byte from input source.
 ** @param source A pointer to your input source.
 ** @result Returns a byte as an unsigned integer.
 */
TIDY_EXPORT uint TIDY_CALL tidyGetByte( TidyInputSource* source );

/** Helper: unget byte back to input source. */
TIDY_EXPORT void TIDY_CALL tidyUngetByte(TidyInputSource* source, /**< The input source. */
                                         uint byteValue           /**< The byte to push back. */
                                         );

/** Helper: check if input source at end.
 ** @param source The input source.
 ** @result Returns a bool indicating whether or not the source is at EOF.
 */
TIDY_EXPORT Bool TIDY_CALL tidyIsEOF( TidyInputSource* source );

/** @}
 ** @name Output Sink
 ** @{
 */

/** Output callback: send a byte to output */
typedef void (TIDY_CALL *TidyPutByteFunc)( void* sinkData, byte bt );

/** This type defines an output destination capable of accepting raw bytes
 ** of output
 */
TIDY_STRUCT
typedef struct _TidyOutputSink
{
  void*               sinkData;  /**< Output context. Passed to callbacks. */

  TidyPutByteFunc     putByte;   /**< Pointer to "put byte" callback */
} TidyOutputSink;

/** Facilitates user defined sinks by providing an entry point to marshal 
 ** pointers-to-functions. This is needed by .NET, and possibly other language
 ** bindings.
 ** @result Returns a bool indicating success or failure.
 */
TIDY_EXPORT Bool TIDY_CALL tidyInitSink(TidyOutputSink* sink,     /**< The sink to populate with data. */
                                        void*           snkData,  /**< The output context. */
                                        TidyPutByteFunc pbFunc    /**< Pointer to the "put byte" callback function. */
                                        );

/** Helper: send a byte to output. */
TIDY_EXPORT void TIDY_CALL tidyPutByte(TidyOutputSink* sink, /**< The output sink to send a byte. */
                                       uint byteValue        /**< The byte to be sent. */
                                       );

/** @}
 ** @name Emacs-compatible reporting support.
 ** If you work with Emacs and prefer Tidy's report output to be in a form
 ** that is easy for Emacs to parse, then these functions may be valuable.
 ** @{
 */

/** Set the file path to use for reports when `TidyEmacs` is being used. This
 ** function provides a proper interface for using the hidden, internal-only
 ** `TidyEmacsFile` configuration option.
 */
TIDY_EXPORT void TIDY_CALL tidySetEmacsFile(TidyDoc tdoc,    /**< The tidy document for which you are setting the filePath. */
                                            ctmbstr filePath /**< The path of the document that should be reported. */
                                            );

/** Get the file path to use for reports when `TidyEmacs` is being used. This
 ** function provides a proper interface for using the hidden, internal-only
 ** `TidyEmacsFile` configuration option.
 ** @param tdoc The tidy document for which you want to fetch the file path.
 ** @result Returns a string indicating the file path.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetEmacsFile( TidyDoc tdoc );
    
/** @}
 ** @name Error Sink
 ** Send Tidy's output to any of several destinations with these functions.
 ** @{
 */

/** Set error sink to named file. 
 ** @result Returns a file handle.
 */
TIDY_EXPORT FILE* TIDY_CALL tidySetErrorFile(TidyDoc tdoc,     /**< The document to set. */
                                             ctmbstr errfilnam /**< The file path to send output. */
                                             );

/** Set error sink to given buffer. 
 ** @result Returns 0 upon success or a standard error number.
 */
TIDY_EXPORT int TIDY_CALL tidySetErrorBuffer(TidyDoc tdoc,      /**< The document to set. */
                                             TidyBuffer* errbuf /**< The TidyBuffer to collect output. */
                                             );

/** Set error sink to given generic sink.
 ** @result Returns 0 upon success or a standard error number.
 */
TIDY_EXPORT int TIDY_CALL tidySetErrorSink(TidyDoc tdoc,        /**< The document to set. */
                                           TidyOutputSink* sink /**< The TidyOutputSink to collect output. */
                                           );

/** @}
 ** @name Error and Message Callbacks - TidyReportFilter
 ** A simple callback to filter or collect messages by diagnostic level,
 ** for example, TidyInfo, TidyWarning, etc. Its name reflects its original
 ** purpose as a filter, by which your application can inform LibTidy whether
 ** or not to output a particular report.
 **
 ** @{
 */

/** This typedef represents the required signature for your provided callback
 ** function should you wish to register one with tidySetReportFilter().
 ** Your callback function will be provided with the following parameters.
 ** @param tdoc Indicates the tidy document the message comes from.
 ** @param lvl Specifies the TidyReportLevel of the message.
 ** @param line Indicates the line number in the source document the message applies to.
 ** @param col Indicates the column in the source document the message applies to.
 ** @param mssg Specifies the complete message as Tidy would emit it.
 ** @return Your callback function will return `yes` if Tidy should include the
 **         report in its own output sink, or `no` if Tidy should suppress it.
 */
typedef Bool (TIDY_CALL *TidyReportFilter)( TidyDoc tdoc, TidyReportLevel lvl, uint line, uint col, ctmbstr mssg );

/** This function informs Tidy to use the specified callback to send reports. */
TIDY_EXPORT Bool TIDY_CALL tidySetReportFilter(TidyDoc tdoc,                 /**< The tidy document for which the callback applies. */
                                               TidyReportFilter filtCallback /**< A pointer to your callback function of type TidyReportFilter. */
                                               );

/** @}
 ** @name Error and Message Callbacks - TidyReportCallback
 ** A simple callback to filter or collect messages reported by Tidy.
 ** Unlike TidyReportFilter, more data are provided (including a `va_list`),
 ** making this callback suitable for applications that provide more
 ** sophisticated handling of reports.
 ** @remark The use of a `va_list` may preclude using this callback from
 **         non-C-like languages, which is uncharacteristic of Tidy. For more
 **         flexibility, consider using TidyMessageCallback instead.
 ** @note This callback was previously `TidyMessageFilter3` in older versions
 **       of LibTidy.
 ** @{
 */

/** This typedef represents the required signature for your provided callback
 ** function should you wish to register one with tidySetReportCallback().
 ** Your callback function will be provided with the following parameters.
 ** @param tdoc Indicates the tidy document the message comes from.
 ** @param lvl Specifies the TidyReportLevel of the message.
 ** @param line Indicates the line number in the source document the message applies to.
 ** @param col Indicates the column in the source document the message applies to.
 ** @param code Specifies the message code representing the message. Note that
 **        this code is a string value that the API promises to hold constant,
 **        as opposed to an enum value that can change at any time. Although
 **        this is intended so that you can look up your own application's
 **        strings, you can retrieve Tidy's format string with this code by
 **        using tidyErrorCodeFromKey() and then the tidyLocalizedString()
 **        family of functions.
 ** @param args Is a `va_list` of arguments used to fill Tidy's message format string.
 ** @return Your callback function will return `yes` if Tidy should include the
 **         report in its own output sink, or `no` if Tidy should suppress it.
 */
typedef Bool (TIDY_CALL *TidyReportCallback)( TidyDoc tdoc, TidyReportLevel lvl,
                                              uint line, uint col, ctmbstr code, va_list args );

/** This function informs Tidy to use the specified callback to send reports. */
TIDY_EXPORT Bool TIDY_CALL tidySetReportCallback(TidyDoc tdoc,                   /**< The tidy document for which the callback applies. */
                                                 TidyReportCallback filtCallback /**< A pointer to your callback function of type TidyReportCallback. */
                                                 );

/** @}
 ** @name Error and Message Callbacks - TidyMessageCallback
 ** A sophisticated and extensible callback to filter or collect messages
 ** reported by Tidy. It returns only an opaque type `TidyMessage` for every
 ** report and dialogue message, and this message can be queried with the
**  TidyMessageCallback API, below. Note that unlike the older filters, this
**  callback exposes *all* output that LibTidy emits (excluding the console
**  application, which is a client of LibTidy).
*/

/** This typedef represents the required signature for your provided callback
 ** function should you wish to register one with tidySetMessageCallback().
 ** Your callback function will be provided with the following parameters.
 ** @param tmessage An opaque type used as a token against which other API
 **        calls can be made.
 ** @return Your callback function will return `yes` if Tidy should include the
 **         report in its own output sink, or `no` if Tidy should suppress it.
 */
typedef Bool (TIDY_CALL *TidyMessageCallback)( TidyMessage tmessage );

/** This function informs Tidy to use the specified callback to send reports. */
TIDY_EXPORT Bool TIDY_CALL tidySetMessageCallback(TidyDoc tdoc,                    /**< The tidy document for which the callback applies. */
                                                  TidyMessageCallback filtCallback /**< A pointer to your callback function of type TidyMessageCallback. */
                                                  );

/** @name TidyMessageCallback API
 ** When using `TidyMessageCallback` you will be supplied with a TidyMessage 
 ** object, which is used as a token to be interrogated with the following
 ** API before the callback returns.
 ** @remark Upon returning from the callback, this object is destroyed so do
 ** not attempt to copy it, or keep it around, or use it in any way.
 **
 ** @{
 */

/** Get the tidy document this message comes from. 
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns the TidyDoc that generated the message.
 */
TIDY_EXPORT TidyDoc TIDY_CALL tidyGetMessageDoc( TidyMessage tmessage );

/** Get the message code.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns a code representing the message. This code can be used
 **         directly with the localized strings API; however we never make
 **         any guarantees about the value of these codes. For code stability
 **         don't store this value in your own application. Instead use the
 **         enum field or use the message key string value.
 */
TIDY_EXPORT uint TIDY_CALL tidyGetMessageCode( TidyMessage tmessage );

/** Get the message key string.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns a string representing the message. This string is intended
 **         to be stable by the LibTidy API, and is suitable for use as a key
 **         in your own applications.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetMessageKey( TidyMessage tmessage );

/** Get the line number the message applies to.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns the line number, if any, that generated the message.
 */
TIDY_EXPORT int TIDY_CALL tidyGetMessageLine( TidyMessage tmessage );

/** Get the column the message applies to.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns the column number, if any, that generated the message.
 */
TIDY_EXPORT int TIDY_CALL tidyGetMessageColumn( TidyMessage tmessage );

/** Get the TidyReportLevel of the message.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns a TidyReportLevel indicating the severity or status of the
 **         message.
 */
TIDY_EXPORT TidyReportLevel TIDY_CALL tidyGetMessageLevel( TidyMessage tmessage );


/** Get the muted status of the message, that is, whether or not the
 ** current configuration indicated that this message should be muted.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns a Bool indicating that the config indicates muting this
 **         message.
 */
TIDY_EXPORT Bool TIDY_CALL tidyGetMessageIsMuted( TidyMessage tmessage );

/** Get the default format string, which is the format string for the message
 ** in Tidy's default localization (en_us).
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns the default localization format string of the message.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetMessageFormatDefault( TidyMessage tmessage );

/** Get the localized format string. If a localized version of the format string
 ** doesn't exist, then the default version will be returned.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns the localized format string of the message.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetMessageFormat( TidyMessage tmessage );

/** Get the message with the format string already completed, in Tidy's
 ** default localization.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns the message in the default localization.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetMessageDefault( TidyMessage tmessage );

/** Get the message with the format string already completed, in Tidy's
 ** current localization.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns the message in the current localization.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetMessage( TidyMessage tmessage );

/** Get the position part part of the message in the default language.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns the positional part of a string as Tidy would display it
 **         in the console application.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetMessagePosDefault( TidyMessage tmessage );

/** Get the position part part of the message in the current language.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns the positional part of a string as Tidy would display it
 **         in the console application.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetMessagePos( TidyMessage tmessage );

/** Get the prefix part of a message in the default language.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns the message prefix part of a string as Tidy would display
 **         it in the console application.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetMessagePrefixDefault( TidyMessage tmessage );

/** Get the prefix part of a message in the current language.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns the message prefix part of a string as Tidy would display
 **         it in the console application.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetMessagePrefix( TidyMessage tmessage );

/** Get the complete message as Tidy would emit it in the default localization.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns the complete message just as Tidy would display it on the
 **         console.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetMessageOutputDefault( TidyMessage tmessage );

/** Get the complete message as Tidy would emit it in the current localization.
 ** @param tmessage Specify the message that you are querying.
 ** @result Returns the complete message just as Tidy would display it on the
 **         console.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetMessageOutput( TidyMessage tmessage );

/** @} end subgroup TidyMessageCallback API */

/** @name TidyMessageCallback Arguments API
 ** When using `TidyMessageCallback` you will be supplied with a TidyMessage
 ** object which can be used as a token against which to query using this API.
 ** This API deals strictly with _arguments_ that a message may or may not have;
 ** these are the same arguments that Tidy would apply to a format string in
 ** order to fill in the placeholder fields and deliver a complete report or
 ** dialogue string to you.
 **
 ** @{
 */

/** Initiates an iterator for a list of arguments related to a given message.
 ** This iterator allows you to iterate through all of the arguments, if any.
 ** In order to iterate through the arguments, initiate the iterator with this
 ** function, and then use tidyGetNextMessageArgument() to retrieve the first
 ** and subsequent arguments. For example:
 ** @code{.c}
 **   TidyIterator itArg = tidyGetMessageArguments( tmessage );
 **   while ( itArg ) {
 **     TidyMessageArgument my_arg = tidyGetNextMessageArgument( tmessage, &itArg );
 **     // do something with my_arg, such as inspect its value or format
 **   }
 ** @endcode
 ** @param tmessage The message about whose arguments you wish to query.
 ** @result Returns a TidyIterator, which is a token used to represent the
 **         current position in a list within LibTidy.
 */
TIDY_EXPORT TidyIterator TIDY_CALL tidyGetMessageArguments( TidyMessage tmessage );

/** Given a valid TidyIterator initiated with tidyGetMessageArguments(), returns
 ** an instance of the opaque type TidyMessageArgument, which serves as a token
 ** against which the remaining argument API functions may be used to query
 ** information.
 ** @result Returns an instance of TidyMessageArgument.
 */
TIDY_EXPORT TidyMessageArgument TIDY_CALL tidyGetNextMessageArgument(TidyMessage tmessage, /**< The message whose arguments you want to access. */
                                                                     TidyIterator* iter    /**< The TidyIterator (initiated with tidyOptGetDocLinksList()) token. */
                                                                     );

/** Returns the `TidyFormatParameterType` of the given message argument.
 ** @result Returns the type of parameter of type TidyFormatParameterType.
 */
TIDY_EXPORT TidyFormatParameterType TIDY_CALL tidyGetArgType(TidyMessage tmessage,    /**< The message whose arguments you want to access. */
                                                             TidyMessageArgument* arg /**< The argument that you are querying. */
                                                             );

/** Returns the format specifier of the given message argument. The memory for
 ** this string is cleared upon termination of the callback, so do be sure to
 ** make your own copy.
 ** @result Returns the format specifier string of the given argument.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetArgFormat(TidyMessage tmessage,    /**< The message whose arguments you want to access. */
                                               TidyMessageArgument* arg /**< The argument that you are querying. */
                                               );

/** Returns the string value of the given message argument. An assertion
 ** will be generated if the argument type is not a string.
 ** @result Returns the string value of the given argument.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetArgValueString(TidyMessage tmessage,    /**< The message whose arguments you want to access. */
                                                    TidyMessageArgument* arg /**< The argument that you are querying. */
                                                    );

/** Returns the unsigned integer value of the given message argument. An
 ** assertion will be generated if the argument type is not an unsigned int.
 ** @result Returns the unsigned integer value of the given argument.
 */
TIDY_EXPORT uint TIDY_CALL tidyGetArgValueUInt(TidyMessage tmessage,    /**< The message whose arguments you want to access. */
                                               TidyMessageArgument* arg /**< The argument that you are querying. */
                                               );

/** Returns the integer value of the given message argument. An assertion
 ** will be generated if the argument type is not an integer.
 ** @result Returns the integer value of the given argument.
 */
TIDY_EXPORT int TIDY_CALL tidyGetArgValueInt(TidyMessage tmessage,    /**< The message whose arguments you want to access. */
                                             TidyMessageArgument* arg /**< The argument that you are querying. */
                                             );

/**
 *  Returns the double value of the given message argument. An assertion
 *  will be generated if the argument type is not a double.
 ** @result Returns the double value of the given argument.
 */
TIDY_EXPORT double TIDY_CALL tidyGetArgValueDouble(TidyMessage tmessage,    /**< The message whose arguments you want to access. */
                                                   TidyMessageArgument* arg /**< The argument that you are querying. */
                                                   );

/** @} end subgroup TidyMessageCallback Arguments API */

/** @name Printing
 ** LibTidy applications can somewhat track the progress of the tidying process
 ** by using this provided callback. It relates where something in the source
 ** document ended up in the output.
 ** @{
 */
    
/** This typedef represents the required signature for your provided callback
 ** function should you wish to register one with tidySetMessageCallback().
 ** Your callback function will be provided with the following parameters.
 ** @param tdoc Indicates the source tidy document.
 ** @param line Indicates the line in the source document at this point in the process.
 ** @param col Indicates the column in the source document at this point in the process.
 ** @param destLine Indicates the line number in the output document at this point in the process.
 */
typedef void (TIDY_CALL *TidyPPProgress)( TidyDoc tdoc, uint line, uint col, uint destLine );

/** This function informs Tidy to use the specified callback for tracking the
 ** pretty-printing process progress.
 */
TIDY_EXPORT Bool TIDY_CALL   tidySetPrettyPrinterCallback(TidyDoc tdoc,
                                                          TidyPPProgress callback
                                                          );

/** @} */
/** @} end IO group */
/* MARK: - Document Parse */
/***************************************************************************//**
 ** @defgroup Parse Document Parse
 **
 ** Functions for parsing markup from a given input source, as well as string
 ** and filename functions for added convenience. HTML/XHTML version determined
 ** from input.
 **
 ** @{
 ******************************************************************************/

/** Parse markup in named file.
 ** @result Returns the highest of `2` indicating that errors were present in
 **         the document, `1` indicating warnings, and `0` in the case of
 **         everything being okay.
 */
TIDY_EXPORT int TIDY_CALL         tidyParseFile(TidyDoc tdoc,    /**< The tidy document to use for parsing. */
                                                ctmbstr filename /**< The filename to parse. */
                                                );

/** Parse markup from the standard input.
 ** @param tdoc The tidy document to use for parsing.
 ** @result Returns the highest of `2` indicating that errors were present in
 **         the document, `1` indicating warnings, and `0` in the case of
 **         everything being okay.
 */
TIDY_EXPORT int TIDY_CALL         tidyParseStdin( TidyDoc tdoc );

/** Parse markup in given string. Note that the supplied string is of type
 ** `ctmbstr` based on `char` and therefore doesn't support the use of
 ** UTF-16 strings. Use `tidyParseBuffer()` if parsing multibyte strings.
 ** @result Returns the highest of `2` indicating that errors were present in
 **         the document, `1` indicating warnings, and `0` in the case of
 **         everything being okay.
 */
TIDY_EXPORT int TIDY_CALL         tidyParseString(TidyDoc tdoc,   /**< The tidy document to use for parsing. */
                                                  ctmbstr content /**< The string to parse. */
                                                  );

/** Parse markup in given buffer.
 ** @result Returns the highest of `2` indicating that errors were present in
 **         the document, `1` indicating warnings, and `0` in the case of
 **         everything being okay.
 */
TIDY_EXPORT int TIDY_CALL         tidyParseBuffer(TidyDoc tdoc,   /**< The tidy document to use for parsing. */
                                                  TidyBuffer* buf /**< The TidyBuffer containing data to parse. */
                                                  );

/** Parse markup in given generic input source.
 ** @result Returns the highest of `2` indicating that errors were present in
 **         the document, `1` indicating warnings, and `0` in the case of
 **         everything being okay.
 */
TIDY_EXPORT int TIDY_CALL         tidyParseSource(TidyDoc tdoc,           /**< The tidy document to use for parsing. */
                                                  TidyInputSource* source /**< A TidyInputSource containing data to parse. */
                                                  );


/** @} End Parse group */
/* MARK: - Diagnostics and Repair */
/***************************************************************************//**
 ** @defgroup Clean Diagnostics and Repair
 **
 ** After parsing the document, you can use these functions to attempt cleanup,
 ** repair, get additional diagnostics, and determine the document type.
 ** @{
 ******************************************************************************/

/** Execute configured cleanup and repair operations on parsed markup.
 ** @param tdoc The tidy document to use.
 ** @result An integer representing the status.
 */
TIDY_EXPORT int TIDY_CALL         tidyCleanAndRepair( TidyDoc tdoc );

/** Reports the document type and diagnostic statistics on parsed and repaired 
 ** markup. You must call tidyCleanAndRepair() before using this function.
 ** @param tdoc The tidy document to use.
 ** @result An integer representing the status.
 */
TIDY_EXPORT int TIDY_CALL         tidyRunDiagnostics( TidyDoc tdoc );

/** Reports the document type into the output sink.
 ** @param tdoc The tidy document to use.
 ** @result An integer representing the status.
 */
TIDY_EXPORT int TIDY_CALL         tidyReportDoctype( TidyDoc tdoc );


/** @} end Clean group */
/* MARK: - Document Save Functions */
/***************************************************************************//**
 ** @defgroup Save Document Save Functions
 **
 ** Save currently parsed document to the given output sink. File name
 ** and string/buffer functions provided for convenience.
 **
 ** @{
 ******************************************************************************/

/** Save the tidy document to the named file.
 ** @result An integer representing the status.
 */
TIDY_EXPORT int TIDY_CALL         tidySaveFile(TidyDoc tdoc,    /**< The tidy document to save. */
                                               ctmbstr filename /**< The destination file name. */
                                               );

/** Save the tidy document to standard output (FILE*).
 ** @param tdoc The tidy document to save.
 ** @result An integer representing the status.
 */
TIDY_EXPORT int TIDY_CALL         tidySaveStdout( TidyDoc tdoc );

/** Save the tidy document to given TidyBuffer object.
 ** @result An integer representing the status.
 */
TIDY_EXPORT int TIDY_CALL         tidySaveBuffer(TidyDoc tdoc,   /**< The tidy document to save. */
                                                 TidyBuffer* buf /**< The buffer to place the output. */
                                                 );

/** Save the tidy document to an application buffer. If TidyShowMarkup and the
 ** document has no errors, or TidyForceOutput, then the current document (per
 ** the current configuration) will be pretty printed to this application
 ** buffer. The document byte length (not character length) will be placed into
 ** *buflen. The document will not be null terminated. If the buffer is not big
 ** enough, ENOMEM will be returned, else the actual document status.
 ** @result An integer representing the status.
 */
TIDY_EXPORT int TIDY_CALL         tidySaveString(TidyDoc tdoc,  /**< The tidy document to save. */
                                                 tmbstr buffer, /**< The buffer to save to. */
                                                 uint* buflen   /**< [out] The byte length written. */
                                                 );

/** Save to given generic output sink.
 ** @result An integer representing the status.
 */
TIDY_EXPORT int TIDY_CALL         tidySaveSink(TidyDoc tdoc,        /**< The tidy document to save. */
                                               TidyOutputSink* sink /**< The output sink to save to. */
                                               );

/** Save current settings to named file. Only writes non-default values.
 ** @result An integer representing the status.
 */
TIDY_EXPORT int TIDY_CALL         tidyOptSaveFile(TidyDoc tdoc,  /**< The tidy document to save. */
                                                  ctmbstr cfgfil /**< The filename to save the configuration to. */
                                                  );

/** Save current settings to given output sink. Only non-default values are
 ** written.
 ** @result An integer representing the status.
 */
TIDY_EXPORT int TIDY_CALL         tidyOptSaveSink(TidyDoc tdoc,        /**< The tidy document to save. */
                                                  TidyOutputSink* sink /**< The output sink to save the configuration to. */
                                                  );


/** @} end Save group */
/* MARK: - Document Tree */
/***************************************************************************//**
 ** @defgroup Tree Document Tree
 **
 ** A parsed (and optionally repaired) document is represented by Tidy as a
 ** tree, much like a W3C DOM. This tree may be traversed using these 
 ** functions. The following snippet gives a basic idea how these functions
 ** can be used.
 **
 ** @code{.c}
 ** void dumpNode( TidyNode tnod, int indent ) {
 **   TidyNode child;
 ** 
 **   for ( child = tidyGetChild(tnod); child; child = tidyGetNext(child) ) {
 **     ctmbstr name;
 **     switch ( tidyNodeGetType(child) ) {
 **     case TidyNode_Root:       name = "Root";                    break;
 **     case TidyNode_DocType:    name = "DOCTYPE";                 break;
 **     case TidyNode_Comment:    name = "Comment";                 break;
 **     case TidyNode_ProcIns:    name = "Processing Instruction";  break;
 **     case TidyNode_Text:       name = "Text";                    break;
 **     case TidyNode_CDATA:      name = "CDATA";                   break;
 **     case TidyNode_Section:    name = "XML Section";             break;
 **     case TidyNode_Asp:        name = "ASP";                     break;
 **     case TidyNode_Jste:       name = "JSTE";                    break;
 **     case TidyNode_Php:        name = "PHP";                     break;
 **     case TidyNode_XmlDecl:    name = "XML Declaration";         break;
 ** 
 **     case TidyNode_Start:
 **     case TidyNode_End:
 **     case TidyNode_StartEnd:
 **     default:
 **       name = tidyNodeGetName( child );
 **       break;
 **     }
 **     assert( name != NULL );
 **     printf( "\%*.*sNode: \%s\\n", indent, indent, " ", name );
 **     dumpNode( child, indent + 4 );
 **   }
 ** }
 ** 
 ** void dumpDoc( TidyDoc tdoc ) {
 **   dumpNode( tidyGetRoot(tdoc), 0 );
 ** }
 ** 
 ** void dumpBody( TidyDoc tdoc ) {
 **   dumpNode( tidyGetBody(tdoc), 0 );
 ** }
 ** @endcode
 **
 ** @{
 ******************************************************************************/

/** @name Nodes for Document Sections
 ** @{
 */

/** Get the root node.
 ** @param tdoc The document to query.
 ** @result Returns a tidy node.
 */
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetRoot( TidyDoc tdoc );

/** Get the HTML node.
 ** @param tdoc The document to query.
 ** @result Returns a tidy node.
 */
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetHtml( TidyDoc tdoc );

/** Get the HEAD node.
 ** @param tdoc The document to query.
 ** @result Returns a tidy node.
 */
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetHead( TidyDoc tdoc );

/** Get the BODY node.
 ** @param tdoc The document to query.
 ** @result Returns a tidy node.
 */
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetBody( TidyDoc tdoc );

/** @}
 ** @name Relative Nodes
 ** @{
 */

/** Get the parent of the indicated node.
 ** @param tnod The node to query.
 ** @result Returns a tidy node.
 */
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetParent( TidyNode tnod );

/** Get the child of the indicated node.
 ** @param tnod The node to query.
 ** @result Returns a tidy node.
 */
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetChild( TidyNode tnod );

/** Get the next sibling node.
 ** @param tnod The node to query.
 ** @result Returns a tidy node.
 */
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetNext( TidyNode tnod );

/** Get the previous sibling node.
 ** @param tnod The node to query.
 ** @result Returns a tidy node.
 */
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetPrev( TidyNode tnod );

/** @}
 ** @name Miscellaneous Node Functions
 ** @{
 */

/** Remove the indicated node.
 ** @result Returns the next tidy node.
 */
TIDY_EXPORT TidyNode TIDY_CALL    tidyDiscardElement(TidyDoc tdoc, /**< The tidy document from which to remove the node. */
                                                     TidyNode tnod /**< The node to remove */
                                                     );

/** @}
 ** @name Node Attribute Functions
 ** @{
 */

/** Get the first attribute.
 ** @param tnod The node for which to get attributes.
 ** @result Returns an instance of TidyAttr.
 */
TIDY_EXPORT TidyAttr TIDY_CALL    tidyAttrFirst( TidyNode tnod );

/** Get the next attribute.
 ** @param tattr The current attribute, so the next one can be returned.
 ** @result Returns and instance of TidyAttr.
 */
TIDY_EXPORT TidyAttr TIDY_CALL    tidyAttrNext( TidyAttr tattr );

/** Get the name of a TidyAttr instance.
 ** @param tattr The tidy attribute to query.
 ** @result Returns a string indicating the name of the attribute.
 */
TIDY_EXPORT ctmbstr TIDY_CALL     tidyAttrName( TidyAttr tattr );

/** Get the value of a TidyAttr instance.
 ** @param tattr The tidy attribute to query.
 ** @result Returns a string indicating the value of the attribute.
 */
TIDY_EXPORT ctmbstr TIDY_CALL     tidyAttrValue( TidyAttr tattr );

/** Discard an attribute. */
TIDY_EXPORT void TIDY_CALL        tidyAttrDiscard(TidyDoc itdoc, /**< The tidy document from which to discard the attribute. */
                                                  TidyNode tnod, /**< The node from which to discard the attribute. */
                                                  TidyAttr tattr /**< The attribute to discard. */
                                                  );

/** Get the attribute ID given a tidy attribute.
 ** @param tattr The attribute to query.
 ** @result Returns the TidyAttrId of the given attribute.
 **/
TIDY_EXPORT TidyAttrId TIDY_CALL  tidyAttrGetId( TidyAttr tattr );

/** Indicates whether or not a given attribute is an event attribute.
 ** @param tattr The attribute to query.
 ** @result Returns a bool indicating whether or not the attribute is an event.
 **/
TIDY_EXPORT Bool TIDY_CALL        tidyAttrIsEvent( TidyAttr tattr );

/** Get an instance of TidyAttr by specifying an attribute ID.
 ** @result Returns a TidyAttr instance.
 */
TIDY_EXPORT TidyAttr TIDY_CALL    tidyAttrGetById(TidyNode tnod,   /**< The node to query. */
                                                  TidyAttrId attId /**< The attribute ID to find. */
                                                  );

/** @}
 ** @name Additional Node Interrogation
 ** @{
 */

/** Get the type of node.
 ** @param tnod The node to query.
 ** @result Returns the type of node as TidyNodeType.
 */
TIDY_EXPORT TidyNodeType TIDY_CALL tidyNodeGetType( TidyNode tnod );

/** Get the name of the node.
 ** @param tnod The node to query.
 ** @result Returns a string indicating the name of the node.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyNodeGetName( TidyNode tnod );

/** Indicates whether or not a node is a text node.
 ** @param tnod The node to query.
 ** @result Returns a bool indicating whether or not the node is a text node.
 */
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsText( TidyNode tnod );

/** Indicates whether or not the node is a propriety type.
 ** @result Returns a bool indicating whether or not the node is a proprietary type.
 */
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsProp(TidyDoc tdoc, /**< The document to query. */
                                          TidyNode tnod /**< The node to query */
                                          );

/** Indicates whether or not a node represents and HTML header element, such
 ** as h1, h2, etc.
 ** @param tnod The node to query.
 ** @result Returns a bool indicating whether or not the node is an HTML header.
 */
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsHeader( TidyNode tnod );

/** Indicates whether or not the node has text.
 ** @result Returns the type of node as TidyNodeType.
 */
TIDY_EXPORT Bool TIDY_CALL tidyNodeHasText(TidyDoc tdoc, /**< The document to query. */
                                           TidyNode tnod /**< The node to query. */
                                           );

/** Gets the text of a node and places it into the given TidyBuffer. The text will be terminated with a `TidyNewline`.
 ** If you want the raw utf-8 stream see `tidyNodeGetValue()`.
 ** @result Returns a bool indicating success or not.
 */
TIDY_EXPORT Bool TIDY_CALL tidyNodeGetText(TidyDoc tdoc,   /**< The document to query. */
                                           TidyNode tnod,  /**< The node to query. */
                                           TidyBuffer* buf /**< [out] A TidyBuffer used to receive the node's text. */
                                           );

/** Get the value of the node. This copies the unescaped value of this node into
 ** the given TidyBuffer at UTF-8.
 ** @result Returns a bool indicating success or not.
 */
TIDY_EXPORT Bool TIDY_CALL tidyNodeGetValue(TidyDoc tdoc,   /**< The document to query */
                                            TidyNode tnod,  /**< The node to query */
                                            TidyBuffer* buf /**< [out] A TidyBuffer used to receive the node's value. */
                                            );

/** Get the tag ID of the node.
 ** @param tnod The node to query.
 ** @result Returns the tag ID of the node as TidyTagId.
 */
TIDY_EXPORT TidyTagId TIDY_CALL tidyNodeGetId( TidyNode tnod );

/** Get the line number where the node occurs.
 ** @param tnod The node to query.
 ** @result Returns the line number.
 */
TIDY_EXPORT uint TIDY_CALL tidyNodeLine( TidyNode tnod );

/** Get the column location of the node.
 ** @param tnod The node to query.
 ** @result Returns the column location of the node.
 */
TIDY_EXPORT uint TIDY_CALL tidyNodeColumn( TidyNode tnod );


/** @} */
/** @} end Tree group */
/* MARK: - Message Key Management */
/***************************************************************************//**
 ** @defgroup MessagesKeys Message Key Management
 **
 ** These functions serve to manage message codes, i.e., codes that are used
 ** Tidy and communicated via its callback filters to represent reports and
 ** dialogue that Tidy emits.
 **
 ** @remark These codes only reflect complete messages, and are specifically
 **         distinct from the internal codes that are used to lookup individual
 **         strings for localization purposes.
 **
 ** @{
 ******************************************************************************/

/**
 ** Given a message code, return the text key that represents it.
 ** @param code The error code to lookup.
 ** @result The string representing the error code.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyErrorCodeAsKey(uint code);

/**
 ** Given a text key representing a message code, return the uint that
 ** represents it.
 **
 ** @remark We establish that for external purposes, the API will ensure that
 **         string keys remain consistent. *Never* count on the integer value
 **         of a message code. Always use this function to ensure that the
 **         integer is valid if you need one.
 ** @param code The string representing the error code.
 ** @result Returns an integer that represents the error code, which can be
 **         used to lookup Tidy's built-in strings. If the provided string does
 **         not have a matching message code, then UINT_MAX will be returned.
 */
TIDY_EXPORT uint TIDY_CALL tidyErrorCodeFromKey(ctmbstr code);

/** Initiates an iterator for a list of message codes available in Tidy.
 ** This iterator allows you to iterate through all of the code. In orde to
 ** iterate through the codes, initiate the iterator with this function, and
 ** then use getNextErrorCode() to retrieve the first and subsequent codes.
 ** For example:
 ** @code{.c}
 **   TidyIterator itMessage = getErrorCodeList();
 **   while ( itMessage ) {
 **     uint code = getNextErrorCode( &itMessage );
 **     // do something with the code, such as lookup a string.
 **   }
 ** @endcode
 ** @result Returns a TidyIterator, which is a token used to represent the
 **         current position in a list within LibTidy.
 */
TIDY_EXPORT TidyIterator TIDY_CALL getErrorCodeList(void);

/** Given a valid TidyIterator initiated with getErrorCodeList(), returns
 ** an instance of the opaque type TidyMessageArgument, which serves as a token
 ** against which the remaining argument API functions may be used to query
 ** information.
 ** @param iter The TidyIterator (initiated with getErrorCodeList()) token.
 ** @result Returns a message code.
 */
TIDY_EXPORT uint TIDY_CALL getNextErrorCode( TidyIterator* iter );


/** @} end MessagesKeys group */
/* MARK: - Localization Support */
/***************************************************************************//**
 ** @defgroup Localization Localization Support
 **
 ** These functions help manage localization in Tidy.
 **
 ** @{
 ******************************************************************************/


/** @name Tidy's Locale
 ** @{
 */

/** Tells Tidy to use a different language for output.
 ** @param  languageCode A Windows or POSIX language code, and must match
 **         a TIDY_LANGUAGE for an installed language.
 ** @result Indicates that a setting was applied, but not necessarily the
 **         specific request, i.e., true indicates a language and/or region
 **         was applied. If es_mx is requested but not installed, and es is
 **         installed, then es will be selected and this function will return
 **         true. However the opposite is not true; if es is requested but
 **         not present, Tidy will not try to select from the es_XX variants.
 */
TIDY_EXPORT Bool TIDY_CALL tidySetLanguage( ctmbstr languageCode );

/** Gets the current language used by Tidy.
 ** @result Returns a string indicating the currently set language.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyGetLanguage(void);

/** @}
 ** @name Locale Mappings
 ** @{
 */

/** @struct tidyLocaleMapItem
 ** Represents an opaque type we can use for tidyLocaleMapItem, which
 ** is used to iterate through the language list, and used to access
 ** the windowsName() and the posixName().
 */
/* Prevent Doxygen from listing this as a function. */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
opaque_type(tidyLocaleMapItem);
#endif
    
/** Initiates an iterator for a list of Tidy's Windows<->POSIX locale mappings.
 ** This iterator allows you to iterate through this list. In order to
 ** iterate through the list, initiate the iterator with this function, and then
 ** use getNextWindowsLanguage() to retrieve the first and subsequent codes.
 ** For example:
 ** @code{.c}
 **   TidyIterator itList = getWindowsLanguageList();
 **   while ( itList ) {
 **     tidyLocaleMapItem *item = getNextWindowsLanguage( &itList );
 **     // do something such as get the TidyLangWindowsName(item).
 **   }
 ** @endcode
 ** @result Returns a TidyIterator, which is a token used to represent the
 **         current position in a list within LibTidy.
 */
TIDY_EXPORT TidyIterator TIDY_CALL getWindowsLanguageList(void);

/** Given a valid TidyIterator initiated with getWindowsLanguageList(), returns
 ** a pointer to a tidyLocaleMapItem, which can be further interrogated with
 ** TidyLangWindowsName() or TidyLangPosixName().
 ** @param iter The TidyIterator (initiated with getWindowsLanguageList()) token.
 ** @result Returns a pointer to a tidyLocaleMapItem.
 */
TIDY_EXPORT const tidyLocaleMapItem* TIDY_CALL getNextWindowsLanguage( TidyIterator* iter );

/** Given a `tidyLocaleMapItem`, return the Windows name.
 ** @param item An instance of tidyLocaleMapItem to query.
 ** @result Returns a string with the Windows name of the mapping.
 */
TIDY_EXPORT ctmbstr TIDY_CALL TidyLangWindowsName( const tidyLocaleMapItem *item );

/** Given a `tidyLocaleMapItem`, return the POSIX name.
 ** @param item An instance of tidyLocaleMapItem to query.
 ** @result Returns a string with the POSIX name of the mapping.
 */
TIDY_EXPORT ctmbstr TIDY_CALL TidyLangPosixName( const tidyLocaleMapItem *item );

/** @}
 ** @name Getting Localized Strings
 ** @{
 */

/** Provides a string given `messageType` in the current localization for
 ** `quantity`. Some strings have one or more plural forms, and this function
 ** will ensure that the correct singular or plural form is returned for the
 ** specified quantity.
 ** @result Returns the desired string.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyLocalizedStringN(uint messageType, /**< The message type. */
                                                   uint quantity     /**< The quantity. */
                                                   );

/** Provides a string given `messageType` in the current localization for the
 ** single case.
 ** @param messageType The message type.
 ** @result Returns the desired string.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyLocalizedString( uint messageType );

/** Provides a string given `messageType` in the default localization (which
 ** is `en`).
 ** @param messageType The message type.
 ** @result Returns the desired string.
 */
TIDY_EXPORT ctmbstr TIDY_CALL tidyDefaultString( uint messageType );

/** Initiates an iterator for a list of string key codes available in Tidy.
 ** This iterator allows you to iterate through all of the codes. In order to
 ** iterate through the codes, initiate the iterator with this function, and
 ** then use getNextStringKey() to retrieve the first and subsequent codes.
 ** For example:
 ** @code{.c}
 **   TidyIterator itKey = getErrorCodeList();
 **   while ( itKey ) {
 **     uint code = getNextStringKey( &itKey );
 **     // do something with the code, such as lookup a string.
 **   }
 ** @endcode
 ** @remark These are provided for documentation generation purposes, and
 **         probably aren't of much use to the average LibTidy implementor.
 ** @result Returns a TidyIterator, which is a token used to represent the
 **         current position in a list within LibTidy.
 */
TIDY_EXPORT TidyIterator TIDY_CALL getStringKeyList(void);

/** Given a valid TidyIterator initiated with getStringKeyList(), returns
 ** an unsigned integer representing the next key value.
 ** @remark These are provided for documentation generation purposes, and
 **         probably aren't of much use to the average LibTidy implementor.
 ** @param iter The TidyIterator (initiated with getStringKeyList()) token.
 ** @result Returns a message code.
 */
TIDY_EXPORT uint TIDY_CALL getNextStringKey( TidyIterator* iter );

/** @}
 ** @name Available Languages
 ** @{
 */

/** Initiates an iterator for a list of Tidy's installed languages. This
 ** iterator allows you to iterate through this list. In order to iterate
 ** through the list, initiate the iterator with this function, and then use
 ** use getNextInstalledLanguage() to retrieve the first and subsequent strings.
 ** For example:
 ** @code{.c}
 **   TidyIterator itList = getInstalledLanguageList();
 **   while ( itList ) {
 **     printf("%s",  getNextInstalledLanguage( &itList ));
 **   }
 ** @endcode
 ** @result Returns a TidyIterator, which is a token used to represent the
 **         current position in a list within LibTidy.
 */
TIDY_EXPORT TidyIterator TIDY_CALL getInstalledLanguageList(void);

/** Given a valid TidyIterator initiated with getInstalledLanguageList(),
 ** returns a string representing a language name that is installed in Tidy.
 ** @param iter The TidyIterator (initiated with getInstalledLanguageList())
 **        token.
 ** @result Returns a string indicating the installed language.
 */
TIDY_EXPORT ctmbstr TIDY_CALL getNextInstalledLanguage( TidyIterator* iter );

/** @} */

/** @} end MessagesKeys group */
/** @} end public_api group */


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
