#ifndef __FILEIO_H__
#define __FILEIO_H__

/** @file fileio.h - does standard C I/O

  Implementation of a FILE* based TidyInputSource and 
  TidyOutputSink.

  (c) 1998-2007 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

*/

#include "tidybuffio.h"
#ifdef __cplusplus
extern "C" {
#endif

/** Allocate and initialize file input source */
TY_PRIVATE int TY_(initFileSource)( TidyAllocator *allocator, TidyInputSource* source, FILE* fp );

/** Free file input source */
TY_PRIVATE void TY_(freeFileSource)( TidyInputSource* source, Bool closeIt );

#if SUPPORT_POSIX_MAPPED_FILES
/** Allocate and initialize file input source using Standard C I/O */
TY_PRIVATE int TY_(initStdIOFileSource)( TidyAllocator *allocator, TidyInputSource* source, FILE* fp );

/** Free file input source using Standard C I/O */
TY_PRIVATE void TY_(freeStdIOFileSource)( TidyInputSource* source, Bool closeIt );
#endif

/** Initialize file output sink */
TY_PRIVATE void TY_(initFileSink)( TidyOutputSink* sink, FILE* fp );

/* Needed for internal declarations */
TY_PRIVATE void TIDY_CALL TY_(filesink_putByte)( void* sinkData, byte bv );

#ifdef __cplusplus
}
#endif
#endif /* __FILEIO_H__ */
