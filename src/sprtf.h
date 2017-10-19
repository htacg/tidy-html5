#ifndef _SPRTF_HXX_
#define _SPRTF_HXX_

/**************************************************************************//**
 * @file
 * Log output utility - part of the HTML Tidy project
 *
 * @author  Geoff R. McLane [reports _at_ geoffair _dot_ info]
 *
 * @copyright
 *     Copyright (c) 1998-2017 Geoff R. McLane and HTACG.
 * @par
 *     All Rights Reserved.
 * @par
 *     See `tidy.h` for the complete license.
 *
 * @date 2017/02/12 17:06:02 Revision 1.0.2  geoff - correct license and coding style
 * @date 2012/11/06 13:01:25 Revision 1.0.1  geoff
 * @date 2012/10/17 00:00:00 Revision 1.0.0  geoff
 * @date Additional updates: consult git log
 *
 ******************************************************************************/

#include "tidyplatform.h"

#ifdef   __cplusplus
extern "C" {
#endif
#ifdef ENABLE_DEBUG_LOG
    /*=============================================================================
    * EXTRA Debugging, and information aid.
    *
    *  When building and defining the ENABLE_DEBUG_LOG macro, Tidy will output
    *  extensive debug information. In addition to this macro, you can supply
    *  cmake build flags for additional diagnostic information:
    *    - -DENABLE_ALLOC_DEBUG:BOOL=ON   - DEBUG_ALLOCATION
    *    - -DENABLE_MEMORY_DEBUG:BOOL=ON  - DEBUG_MEMORY
    *    - -DENABLE_CRTDBG_MEMORY:BOOL=ON - _CRTDBG_MAP_ALLOC (WIN32 only)
    *
    *  _MSC_VER Only - ENABLE_DEBUG_LOG is automatically enabled in the Debug
    *  build, unless DISABLE_DEBUG_LOG is defined. See 'tidyplatform.h'
    *
    *  You can use DEBUG_LOG( SPRTF() ) to avoid #ifdef ENABLE_DEBUG_LOG for
    *  one-liners.
    *
    *  This EXTRA Debug information is also written to a 'temptidy.txt' log
    *  file, for review, and analysis.
    *
    *===========================================================================*/

#ifndef SPRTF
#  define SPRTF sprtf
#endif

#ifdef _MSC_VER
#  define MCDECL _cdecl
#else
#  define MCDECL
#endif

TIDY_EXPORT int add_std_out( int val );
TIDY_EXPORT int add_sys_time( int val );
TIDY_EXPORT int add_sys_date( int val );

TIDY_EXPORT int add_screen_out( int val );
TIDY_EXPORT int add_list_out( int val );
TIDY_EXPORT int add_append_log( int val );

TIDY_EXPORT int open_log_file( void );
TIDY_EXPORT void close_log_file( void );
TIDY_EXPORT void set_log_file( char * nf, int open );
TIDY_EXPORT char * get_log_file( void );

TIDY_EXPORT int MCDECL sprtf( const char *pf, ... );
#define M_MAX_SPRTF 2048
TIDY_EXPORT int direct_out_it( char *cp );

TIDY_EXPORT char *GetNxtBuf(void);

#define EndBuf(a)   ( a + strlen(a) )

TIDY_EXPORT char *get_date_stg(void);
TIDY_EXPORT char *get_time_stg(void);
TIDY_EXPORT char *get_date_time_stg(void);

#ifdef _MSC_VER
TIDY_EXPORT int gettimeofday(struct timeval *tp, void *tzp);
#endif

#  define DEBUG_LOG(ARG) do { ARG; } while(0)

#else
#  define DEBUG_LOG(ARG)
#endif

#ifdef   __cplusplus
}
#endif
#endif /* #ifndef _SPRTF_HXX_*/
/* eof - sprtf.h */
