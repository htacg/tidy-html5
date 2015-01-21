/*
 *  SPRTF - Log output utility
 *
 *   Author: Geoff R. McLane <reports _at_ geoffair _dot_ info>
 *   License: GPL v2 (or later at your choice)
 *
 *   Revision 1.0.1  2012/11/06 13:01:25  geoff
 *   Revision 1.0.0  2012/10/17 00:00:00  geoff
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation; either version 2 of the
 *   License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, US
 *
 */

// Module: sprtf.hxx
// Debug log file output
#ifndef _SPRTF_HXX_
#define _SPRTF_HXX_
#ifdef   __cplusplus
extern "C" {
#endif
#ifdef _MSC_VER
#define MCDECL _cdecl
#else
#define MCDECL
#endif

extern int add_std_out( int val );
extern int add_sys_time( int val );
extern int add_sys_date( int val );

extern int add_screen_out( int val );
extern int add_list_out( int val );
extern int add_append_log( int val );

extern int open_log_file( void );
extern void close_log_file( void );
extern void set_log_file( char * nf, int open );
extern char * get_log_file( void );

extern int MCDECL sprtf( const char *pf, ... );
#define M_MAX_SPRTF 2048
extern int direct_out_it( char *cp );

extern char *GetNxtBuf();

#define EndBuf(a)   ( a + strlen(a) )

extern char *get_date_stg();
extern char *get_time_stg();
extern char *get_date_time_stg();
#ifdef _MSC_VER
extern int gettimeofday(struct timeval *tp, void *tzp);
#endif

#ifndef SPRTF
#define SPRTF sprtf
#endif

#ifdef   __cplusplus
}
#endif
#endif // #ifndef _SPRTF_HXX_
// oef - sprtf.hxx
