/* attrget.c -- Locate attribute value by type

  (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.
  
*/

#include "tidy-int.h"
#include "tags.h"
#include "attrs.h"
#include "tidy.h"

TidyAttr TIDY_CALL tidyAttrGetById( TidyNode tnod, TidyAttrId attId )
{
    Node* nimp = tidyNodeToImpl(tnod);
    return tidyImplToAttr( TY_(AttrGetById)( nimp, attId ) );
}

/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
