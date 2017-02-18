/* attrget.c -- Additional attribute API

  (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.
  
*/

#include "tidy-int.h"
#include "tidy.h"

TidyAttr TIDY_CALL tidyAttrGetById( TidyNode tnod, TidyAttrId attId )
{
    Node* nimp = tidyNodeToImpl(tnod);
    return tidyImplToAttr( TY_(AttrGetById)( nimp, attId ) );
}


Bool TIDY_CALL tidyAttrIsEvent( TidyAttr tattr )
{
    return TY_(attrIsEvent)( tidyAttrToImpl(tattr) );
}


/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
