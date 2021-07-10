#ifndef __CLEAN_H__
#define __CLEAN_H__

/* clean.h -- clean up misuse of presentation markup

  (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

*/

TY_PRIVATE void TY_(FixNodeLinks)(Node *node);

TY_PRIVATE void TY_(FreeStyles)( TidyDocImpl* doc );

/* Add class="foo" to node
*/
TY_PRIVATE void TY_(AddStyleAsClass)( TidyDocImpl* doc, Node *node, ctmbstr stylevalue );
TY_PRIVATE void TY_(AddStyleProperty)(TidyDocImpl* doc, Node *node, ctmbstr property );

TY_PRIVATE void TY_(CleanDocument)( TidyDocImpl* doc );

/* simplifies <b><b> ... </b> ...</b> etc. */
TY_PRIVATE void TY_(NestedEmphasis)( TidyDocImpl* doc, Node* node );

/* replace i by em and b by strong */
TY_PRIVATE void TY_(EmFromI)( TidyDocImpl* doc, Node* node );

/*
 Some people use dir or ul without an li
 to indent the content. The pattern to
 look for is a list with a single implicit
 li. This is recursively replaced by an
 implicit blockquote.
*/
TY_PRIVATE void TY_(List2BQ)( TidyDocImpl* doc, Node* node );

/*
 Replace implicit blockquote by div with an indent
 taking care to reduce nested blockquotes to a single
 div with the indent set to match the nesting depth
*/
TY_PRIVATE void TY_(BQ2Div)( TidyDocImpl* doc, Node* node );


TY_PRIVATE void TY_(DropSections)( TidyDocImpl* doc, Node* node );


/*
 This is a major clean up to strip out all the extra stuff you get
 when you save as web page from Word 2000. It doesn't yet know what
 to do with VML tags, but these will appear as errors unless you
 declare them as new tags, such as o:p which needs to be declared
 as inline.
*/
TY_PRIVATE void TY_(CleanWord2000)( TidyDocImpl* doc, Node *node);

TY_PRIVATE Bool TY_(IsWord2000)( TidyDocImpl* doc );

/* where appropriate move object elements from head to body */
TY_PRIVATE void TY_(BumpObject)( TidyDocImpl* doc, Node *html );

TY_PRIVATE Bool TY_(TidyMetaCharset)(TidyDocImpl* doc);

TY_PRIVATE void TY_(DropComments)(TidyDocImpl* doc, Node* node);
TY_PRIVATE void TY_(DropFontElements)(TidyDocImpl* doc, Node* node, Node **pnode);
TY_PRIVATE void TY_(WbrToSpace)(TidyDocImpl* doc, Node* node);
TY_PRIVATE void TY_(DowngradeTypography)(TidyDocImpl* doc, Node* node);
TY_PRIVATE void TY_(ReplacePreformattedSpaces)(TidyDocImpl* doc, Node* node);
TY_PRIVATE void TY_(NormalizeSpaces)(Lexer *lexer, Node *node);
TY_PRIVATE void TY_(ConvertCDATANodes)(TidyDocImpl* doc, Node* node);

TY_PRIVATE void TY_(FixAnchors)(TidyDocImpl* doc, Node *node, Bool wantName, Bool wantId);
TY_PRIVATE void TY_(FixXhtmlNamespace)(TidyDocImpl* doc, Bool wantXmlns);
TY_PRIVATE void TY_(FixLanguageInformation)(TidyDocImpl* doc, Node* node, Bool wantXmlLang, Bool wantLang);

/* Issue #567 - move style elements from body to head */
TY_PRIVATE void TY_(CleanStyle)(TidyDocImpl* doc, Node *html);
/* Issue #692 - discard multiple titles */
TY_PRIVATE void TY_(CleanHead)(TidyDocImpl* doc);

#endif /* __CLEAN_H__ */
