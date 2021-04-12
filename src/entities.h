#ifndef __ENTITIES_H__
#define __ENTITIES_H__

/* entities.h -- recognize character entities

  (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

*/

#include "forward.h"

/* entity starting with "&" returns zero on error */
/* uint    EntityCode( ctmbstr name, uint versions ); */
TY_PRIVATE ctmbstr TY_(EntityName)( uint charCode, uint versions );
TY_PRIVATE Bool    TY_(EntityInfo)( ctmbstr name, Bool isXml, uint* code, uint* versions );

#endif /* __ENTITIES_H__ */
