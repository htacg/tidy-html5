/* TidyNodeIter

  (c) 1998-2003 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.
  
  These files contain utility routines to perform in-order traversals of the
  Tidy document tree, beginning at an arbitrary node.

  A traversal of the tree can be performed in a manner similar to the following:

  Node *testNode;
  TidyNodeIter *iter = newTidyNodeIter( FindBody( tdoc ));
  for (testNode = nextTidyNode( &iter );
       NULL != testNode;
       testNode = nextTidyNode( &iter ))
  {
  }

  TODO:  Add a prevTidyNode() function.
*/

#include "lexer.h"

typedef struct _TidyNodeIter
{
    Node *pTop, *pCurrent;
} TidyNodeIter;

TidyNodeIter *newTidyNodeIter( Node *pStart );

/* 
    nextTidyNode( TidyNodeIter *pIter )

    if pCurrent is NULL, this function initializes it to match pTop, and
    returns that value, otherwise it advances to the next node in order, 
    and returns that value. When pTop == pCurrent, the function returns NULL
    to indicate that the entire tree has been visited.
*/
Node *nextTidyNode( TidyNodeIter *pIter );

/*
    setCurrentNode( TidyNodeIter *pThis, Node *newCurr )

    Resets pCurrent to match the passed value; useful if you need to back up
    to an unaltered point in the tree, or to skip a section. The next call to 
    nextTidyNode() will return the node which follows newCurr in order.

    Minimal error checking is performed; unexpected results _will_ occur if 
    newCurr is not a descendant node of pTop.
*/
void setCurrentNode( TidyNodeIter *pThis, Node *newCurr );
