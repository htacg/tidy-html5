#ifndef __CLEAN_H__
#define __CLEAN_H__

/* clean.h -- clean up misuse of presentation markup

  (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

*/

void TY_(FixNodeLinks)(TidyNode node);

void TY_(FreeStyles)( TidyDoc doc );

/* Add class="foo" to node
*/
void TY_(AddStyleAsClass)( TidyDoc doc, TidyNode node, ctmbstr stylevalue );
void TY_(AddStyleProperty)(TidyDoc doc, TidyNode node, ctmbstr property );

void TY_(CleanDocument)( TidyDoc doc );

/* simplifies <b><b> ... </b> ...</b> etc. */
void TY_(NestedEmphasis)( TidyDoc doc, TidyNode node );

/* replace i by em and b by strong */
void TY_(EmFromI)( TidyDoc doc, TidyNode node );

/*
 Some people use dir or ul without an li
 to indent the content. The pattern to
 look for is a list with a single implicit
 li. This is recursively replaced by an
 implicit blockquote.
*/
void TY_(List2BQ)( TidyDoc doc, TidyNode node );

/*
 Replace implicit blockquote by div with an indent
 taking care to reduce nested blockquotes to a single
 div with the indent set to match the nesting depth
*/
void TY_(BQ2Div)( TidyDoc doc, TidyNode node );


void TY_(DropSections)( TidyDoc doc, TidyNode node );


/*
 This is a major clean up to strip out all the extra stuff you get
 when you save as web page from Word 2000. It doesn't yet know what
 to do with VML tags, but these will appear as errors unless you
 declare them as new tags, such as o:p which needs to be declared
 as inline.
*/
void TY_(CleanWord2000)( TidyDoc doc, TidyNode node);

Bool TY_(IsWord2000)( TidyDoc doc );

/* where appropriate move object elements from head to body */
void TY_(BumpObject)( TidyDoc doc, TidyNode html );

/* This is disabled due to http://tidy.sf.net/bug/681116 */
#if 0
void TY_(FixBrakes)( TidyDoc pDoc, TidyNode pParent );
#endif

void TY_(VerifyHTTPEquiv)( TidyDoc pDoc, TidyNode pParent );

void TY_(DropComments)(TidyDoc doc, TidyNode node);
void TY_(DropFontElements)(TidyDoc doc, TidyNode node, TidyNode *pnode);
void TY_(WbrToSpace)(TidyDoc doc, TidyNode node);
void TY_(DowngradeTypography)(TidyDoc doc, TidyNode node);
void TY_(ReplacePreformattedSpaces)(TidyDoc doc, TidyNode node);
void TY_(NormalizeSpaces)(Lexer *lexer, TidyNode node);
void TY_(ConvertCDATANodes)(TidyDoc doc, TidyNode node);

void TY_(FixAnchors)(TidyDoc doc, TidyNode node, Bool wantName, Bool wantId);
void TY_(FixXhtmlNamespace)(TidyDoc doc, Bool wantXmlns);
void TY_(FixLanguageInformation)(TidyDoc doc, TidyNode node, Bool wantXmlLang, Bool wantLang);


#endif /* __CLEAN_H__ */
