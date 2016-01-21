/* win_vsnprintf.h -- Provides standard vsnprintf.h and
 *   additional printf routines to Tidy on Windows.
 *
 * Created by Jim Derry on 1/8/16.
 * (c) 2016 HTACG
 * See tidy.h and access.h for the copyright notice.
 */

#include <stdio.h>
#include <stdarg.h>
#include "forward.h"
#include "win_vsnprintf.h"

#if defined(__MINGW32__)
/* minGW.org doesn't automatically include these in its `libmsvcrt.a` although
 * `dumpbin /exports C:\Windows\System32\msvcrt.dll` indicates they are present.
 * We include our own import library `libmsvcrt_tidy.a` that adds these missing
 * definitions.
 *
 * Unfortunately `msvcrt.dll` only includes `_vscprintf_p_l` for some strange
 * reason, which takes a locale_t which is not available to minGW. Since we're
 * going to pass NULL anyway, we can import it as a void*.
 */
extern int _vscprintf_p_l(const char *fmt, void *locale, va_list ap);
extern int _vsprintf_p(char *s, uint n, const char *fmt, va_list ap);
#endif


#if defined(_WIN32)

static char* TY_(new_string)( const ctmbstr fmt, va_list args );


/* Provides a proper `vsnprintf` for Windows including correct return
 * values and with support for positional arguments.
 * Adapted from FFmpeg -- LGPL
 */
int TY_(win_vsnprintf)(char *s, uint n, const char *fmt, va_list ap)
{
    int ret;
    va_list ap_copy;
    
    if (n == 0)
        return _vscprintf_p_l(fmt, NULL, ap);
        
        memset(s, 0, n);
        va_copy(ap_copy, ap);
        ret = _vsprintf_p(s, n, fmt, ap_copy);
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
int	TY_(win_printf)(const char *s, ...)
{
    int result;
    char *out_string;
    va_list args;
    va_start(args, s);
    out_string = TY_(new_string)( s, args );
    va_end(args);
    
    result = printf("%s", out_string);
    
    if (out_string)
        free(out_string);
        
        return result;
}


/* Provides a wrapper for `fprintf` using the improved `vsnprintf`. */
int	TY_(win_fprintf)(FILE *f, const char *s, ...)
{
    int result;
    char *out_string;
    va_list args;
    va_start(args, s);
    out_string = TY_(new_string)( s, args );
    va_end(args);
    
    result = fprintf(f, "%s", out_string);
    
    if (out_string)
        free(out_string);
        
        return result;
}


/* Convenience to create a new string with a format and arguments.
 */
static char* TY_(new_string)( const ctmbstr fmt, va_list args )
{
    char *result = NULL;
    int len = 0;
    
    len = TY_(win_vsnprintf)( result, 0, fmt, args );
    if (!(result = malloc( len + 1) ))
    {	/* @todo */
        fprintf(stderr, "MALLOC FAILED in win_vsnprintf.c creating a new string!");
        exit(2);
    }
    
    TY_(win_vsnprintf)( result, len + 1, fmt, args );
    
    return result;
}


#endif /* defined(_WIN32) */
