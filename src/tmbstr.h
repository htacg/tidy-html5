#ifndef __TMBSTR_H__
#define __TMBSTR_H__

/* tmbstr.h - Tidy string utility functions

  (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

*/

#include "tidyplatform.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* like strdup but using an allocator */
TY_PRIVATE tmbstr TY_(tmbstrdup)( TidyAllocator *allocator, ctmbstr str );

/* like strndup but using an allocator */
TY_PRIVATE tmbstr TY_(tmbstrndup)( TidyAllocator *allocator, ctmbstr str, uint len);

/* exactly same as strncpy */
TY_PRIVATE uint TY_(tmbstrncpy)( tmbstr s1, ctmbstr s2, uint size );

TY_PRIVATE uint TY_(tmbstrcpy)( tmbstr s1, ctmbstr s2 );

TY_PRIVATE uint TY_(tmbstrcat)( tmbstr s1, ctmbstr s2 );

/* exactly same as strcmp */
TY_PRIVATE int TY_(tmbstrcmp)( ctmbstr s1, ctmbstr s2 );

/* returns byte count, not char count */
TY_PRIVATE uint TY_(tmbstrlen)( ctmbstr str );

/*
  MS C 4.2 doesn't include strcasecmp.
  Note that tolower and toupper won't
  work on chars > 127.

  Neither do Lexer.ToLower() or Lexer.ToUpper()!

  We get away with this because, except for XML tags,
  we are always comparing to ascii element and
  attribute names defined by HTML specs.
*/
TY_PRIVATE int TY_(tmbstrcasecmp)( ctmbstr s1, ctmbstr s2 );

TY_PRIVATE int TY_(tmbstrncmp)( ctmbstr s1, ctmbstr s2, uint n );

TY_PRIVATE int TY_(tmbstrncasecmp)( ctmbstr s1, ctmbstr s2, uint n );

/* return offset of cc from beginning of s1,
** -1 if not found.
*/
/* TY_PRIVATE int TY_(tmbstrnchr)( ctmbstr s1, uint len1, tmbchar cc ); */

TY_PRIVATE ctmbstr TY_(tmbsubstrn)( ctmbstr s1, uint len1, ctmbstr s2 );
/* TY_PRIVATE ctmbstr TY_(tmbsubstrncase)( ctmbstr s1, uint len1, ctmbstr s2 ); */
TY_PRIVATE ctmbstr TY_(tmbsubstr)( ctmbstr s1, ctmbstr s2 );

/* transform string to lower case */
TY_PRIVATE tmbstr TY_(tmbstrtolower)( tmbstr s );

/* Transform ASCII chars in string to upper case */
TY_PRIVATE tmbstr TY_(tmbstrtoupper)( tmbstr s );

/* TY_PRIVATE Bool TY_(tmbsamefile)( ctmbstr filename1, ctmbstr filename2 ); */

TY_PRIVATE int TY_(tmbvsnprintf)(tmbstr buffer, size_t count, ctmbstr format, va_list args)
#ifdef __GNUC__
__attribute__((format(printf, 3, 0)))
#endif
;
TY_PRIVATE int TY_(tmbsnprintf)(tmbstr buffer, size_t count, ctmbstr format, ...)
#ifdef __GNUC__
__attribute__((format(printf, 3, 4)))
#endif
;

TY_PRIVATE void TY_(strrep)(tmbstr buffer, ctmbstr str, ctmbstr rep);


#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __TMBSTR_H__ */
