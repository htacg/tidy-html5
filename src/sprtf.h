/*
 *  SPRTF - Log output utility - part of the HTML Tidy project
 *
 *   Author: Geoff R. McLane <reports _at_ geoffair _dot_ info>
 *   License: MIT (see tidy.h for the copyright notice)
 *
 *   Revision 1.0.2  2017/02/12 17:06:02  geoff - correct license and coding style
 *   Revision 1.0.1  2012/11/06 13:01:25  geoff
 *   Revision 1.0.0  2012/10/17 00:00:00  geoff
 *
 */

/* Module: sprtf.h */
/* Debug log file output */
#ifndef _SPRTF_HXX_
#define _SPRTF_HXX_
#include "tidyplatform.h"

#ifdef   __cplusplus
extern "C" {
#endif
#ifdef _MSC_VER
#define MCDECL _cdecl
#else
#define MCDECL
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

TIDY_EXPORT char *GetNxtBuf();

#define EndBuf(a)   ( a + strlen(a) )

TIDY_EXPORT char *get_date_stg();
TIDY_EXPORT char *get_time_stg();
TIDY_EXPORT char *get_date_time_stg();
#ifdef _MSC_VER
TIDY_EXPORT int gettimeofday(struct timeval *tp, void *tzp);
#endif

#ifndef SPRTF
#define SPRTF sprtf
#endif

#ifdef   __cplusplus
}
#endif
#endif /* #ifndef _SPRTF_HXX_*/
/* eof - sprtf.h */
