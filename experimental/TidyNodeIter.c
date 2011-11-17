#include "platform.h"
#include "tidy-int.h"

#include "TidyNodeIter.h"

TidyNodeIter *newTidyNodeIter( Node *pStart )
{
    TidyNodeIter *pThis = NULL;
    if (NULL != (pThis = MemAlloc( sizeof( TidyNodeIter ))))
    {
        ClearMemory( pThis, sizeof( TidyNodeIter ));
        pThis->pTop = pStart;
    }
    return pThis;
}

Node *nextTidyNode( TidyNodeIter *pThis )
{
    if (NULL == pThis->pCurrent)
    {
        // just starting out, initialize
        pThis->pCurrent = pThis->pTop->content;
    }
    else if (NULL != pThis->pCurrent->content)
    {
        // the next element, if any, is my first-born child
        pThis->pCurrent = pThis->pCurrent->content;
    }
    else 
    {
        // no children, I guess my next younger brother inherits the throne.
        while (   NULL == pThis->pCurrent->next
               && pThis->pTop != pThis->pCurrent->parent )
        {
            //  no siblings, do any of my ancestors have younger sibs?
            pThis->pCurrent = pThis->pCurrent->parent;
        }
        pThis->pCurrent = pThis->pCurrent->next;
    }
    return pThis->pCurrent;
}

void setCurrentNode( TidyNodeIter *pThis, Node *newCurr )
{
    if (NULL != newCurr)
        pThis->pCurrent = newCurr;
}
