/** @file platform.h - Deprecated compatibility header. Use tidyplatform.h
**
** @deprecated This compatibility header is deprecated and 
** should be replaced by tidyplatform.h. This header will be removed!
**
*/
#ifdef __GNUC__
#warning "FIXME: Using compatibility tidy header (platform.h) that will go away!"
#endif
#ifdef _MSC_VER
#pragma message("WARNING: ** FIXME ** Using compatibility tidy header (platform.h) that will go away! Use tidyplatform.h")
#endif

#include "tidyplatform.h"

