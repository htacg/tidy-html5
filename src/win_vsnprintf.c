//
//  win_vsnprintf.c
//  tidy
//
//  Created by Jim Derry on 1/8/16.
//  Copyright © 2016 balthisar.com. All rights reserved.
//

#include <stdarg.h>
#include "forward.h"
#include "win_vsnprintf.h"

#if defined(_WIN32)

static char* TY(new_string)( const ctmbstr fmt, va_list args );


/* Provides a proper `vsnprintf` for Windows including correct return
 * values and with support for positional arguments.
 * Adapted from FFmpeg -- LGPL 
 */
int TY_(win_vsnprintf)(char *s, uint n, const char *fmt, va_list ap)
{
	int ret;
	va_list ap_copy;
	
	if (n == 0)
		return _vscprintf(fmt, ap);
		
	/* we use n - 1 here because if the buffer is not big enough, the MS
	 * runtime libraries don't add a terminating zero at the end. MSDN
	 * recommends to provide _snprintf/_vsnprintf() a buffer size that
	 * is one less than the actual buffer, and zero it before calling
	 * _snprintf/_vsnprintf() to workaround this problem.
	 * See http://msdn.microsoft.com/en-us/library/1kt27hek(v=vs.80).aspx */
		memset(s, 0, n);
		va_copy(ap_copy, ap);
		ret = _vsprintf_p(s, n - 1, fmt, ap_copy);
		va_end(ap_copy);
		if (ret == -1)
			ret = _vscprintf(fmt, ap);
			
			return ret;
}


/* Provides a proper `snprintf` for Windows including correct return
 * values and with support for positional arguments.
 */
int TY_(win_snprintf)(char *s, uint n, const char *fmt, ...)
{
	int retval;
	va_list args;
	va_start(args, fmt);
	retval = TY_(win_vsnprintf)(s, n, fmt, args);
	va_end(args);
	return retval;
}


/* Provides a wrapper for `printf` using the improved `vsnprintf`. */
int	TY(win_printf)(char *s, ...)
{
	int result;
	va_list args;
	va_start(args, s)
	char *out_string = TY_(new_string)( s, args );
	va_end(args);
	
	result = printf(out_string);
	
	if (out_string)
		free(out_string)
	
		return result;
}


/* Provides a wrapper for `fprintf` using the improved `vsnprintf`. */
int	TY(win_fprintf)(FILE *f, char *s, ...)
{
	int result;
	va_list args;
	va_start(args, s)
	char *out_string = TY_(new_string)( s, args );
	va_end(args);
	
	result = fprintf(out_string);
	
	if (out_string)
		free(out_string)
		
		return result;
}


/* Convenience to create a new string with a format and arguments.
 */
static char* TY(new_string)( const ctmbstr fmt, va_list args )
{
	char *result = NULL;
	int len = 0;
	
	len = TY_(win_vsnprintf)( result, 0, fmt, argList );
	
	if (!(result = malloc( len + 1) ))
	{	/* @todo */
		printf("MALLOC FAILED!");
		exit(2);
	}
	
	TY_(win_vsnprintf)( result, len + 1, fmt, argList);
	
	return result;
}


#endif /* defined(_WIN32) */
