#ifndef __win_vsnprintf_h__
#define __win_vsnprintf_h__

/* win_vsnprintf.h -- Provides standard vsnprintf.h and
 *   additional printf routines to Tidy on Windows.
 *
 * Created by Jim Derry on 1/8/16.
 * (c) 2016 HTACG
 * See tidy.h and access.h for the copyright notice.
 */

#if defined(_WIN32)

#include <stdio.h>
#include "tidyplatform.h"


/* Provides a proper `vsnprintf` for Windows including correct return
 * values and with support for positional arguments.
 */
int TY_(win_vsnprintf)(char *s, uint n, const char *fmt, va_list ap);


/* Provides a proper `snprintf` for Windows including correct return
 * values and with support for positional arguments.
 */
int TY_(win_snprintf)(char *s, uint n, const char *fmt, ...)


/* Provides a wrapper for `printf` using the improved `vsnprintf`. */
int	TY(win_printf)(char *s, ...);


/* Provides a wrapper for `fprintf` using the improved `vsnprintf`. */
int	TY(win_fprintf)(FILE *f, char *s, ...);


#endif /* defined(_WIN32) */
#endif /* __win_vsnprintf_h_ */
