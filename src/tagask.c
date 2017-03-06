/* tagask.c -- Interrogate node type

  (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

*/

#include "tidy-int.h"
#include "tags.h"
#include "tidy.h"

Bool TIDY_CALL tidyNodeIsText( TidyNode tnod )
{ return TY_(nodeIsText)( tidyNodeToImpl(tnod) );
}
Bool tidyNodeCMIsBlock( TidyNode tnod ); /* not exported yet */
Bool tidyNodeCMIsBlock( TidyNode tnod )
{ return TY_(nodeCMIsBlock)( tidyNodeToImpl(tnod) );
}
Bool tidyNodeCMIsInline( TidyNode tnod ); /* not exported yet */
Bool tidyNodeCMIsInline( TidyNode tnod )
{ return TY_(nodeCMIsInline)( tidyNodeToImpl(tnod) );
}
Bool tidyNodeCMIsEmpty( TidyNode tnod ); /* not exported yet */
Bool tidyNodeCMIsEmpty( TidyNode tnod )
{ return TY_(nodeCMIsEmpty)( tidyNodeToImpl(tnod) );
}
Bool TIDY_CALL tidyNodeIsHeader( TidyNode tnod )
{ return TY_(nodeIsHeader)( tidyNodeToImpl(tnod) );
}


/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
