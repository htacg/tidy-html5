#ifndef __PARSER_H__
#define __PARSER_H__

/* parser.h -- HTML Parser

  (c) 1998-2007 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.
  
*/

#include "forward.h"

Bool TY_(CheckNodeIntegrity)(TidyNode node);

Bool TY_(TextNodeEndWithSpace)( Lexer *lexer, TidyNode node );

/*
 used to determine how attributes
 without values should be printed
 this was introduced to deal with
 user defined tags e.g. Cold Fusion
*/
Bool TY_(IsNewNode)(TidyNode node);

void TY_(CoerceNode)(TidyDoc doc, TidyNode node, TidyTagId tid, Bool obsolete, Bool expected);

/* extract a node and its children from a markup tree */
TidyNode TY_(RemoveNode)(TidyNode node);

/* remove node from markup tree and discard it */
TidyNode TY_(DiscardElement)( TidyDoc doc, TidyNode element);

/* insert node into markup tree as the firt element
 of content of element */
void TY_(InsertNodeAtStart)(TidyNode element, TidyNode node);

/* insert node into markup tree as the last element
 of content of "element" */
void TY_(InsertNodeAtEnd)(TidyNode element, TidyNode node);

/* insert node into markup tree before element */
void TY_(InsertNodeBeforeElement)(TidyNode element, TidyNode node);

/* insert node into markup tree after element */
void TY_(InsertNodeAfterElement)(TidyNode element, TidyNode node);

TidyNode TY_(TrimEmptyElement)( TidyDoc doc, TidyNode element );
TidyNode TY_(DropEmptyElements)(TidyDoc doc, TidyNode node);


/* assumes node is a text node */
Bool TY_(IsBlank)(Lexer *lexer, TidyNode node);

Bool TY_(IsJavaScript)(TidyNode node);

/*
  HTML is the top level element
*/
void TY_(ParseDocument)( TidyDoc doc );



/*
  XML documents
*/
Bool TY_(XMLPreserveWhiteSpace)( TidyDoc doc, TidyNode element );

void TY_(ParseXMLDocument)( TidyDoc doc );

#endif /* __PARSER_H__ */
