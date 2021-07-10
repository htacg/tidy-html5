#ifndef __CHARSETS_H__
#define __CHARSETS_H__

/* charsets.h -- character set information and mappings

  (c) 1998-2021 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

*/

TY_PRIVATE uint TY_(GetEncodingIdFromName)(ctmbstr name);
TY_PRIVATE uint TY_(GetEncodingIdFromCodePage)(uint cp);
TY_PRIVATE uint TY_(GetEncodingCodePageFromName)(ctmbstr name);
TY_PRIVATE uint TY_(GetEncodingCodePageFromId)(uint id);
TY_PRIVATE ctmbstr TY_(GetEncodingNameFromId)(uint id);
TY_PRIVATE ctmbstr TY_(GetEncodingNameFromCodePage)(uint cp);

#endif /* __CHARSETS_H__ */

