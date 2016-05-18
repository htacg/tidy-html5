#ifndef __PPRINT_H__
#define __PPRINT_H__

/* pprint.h -- pretty print parse tree  
  
   (c) 1998-2007 (W3C) MIT, ERCIM, Keio University
   See tidy.h for the copyright notice.
  
*/

#include "forward.h"

/*
  Block-level and unknown elements are printed on
  new lines and their contents indented 2 spaces

  Inline elements are printed inline.

  Inline content is wrapped on spaces (except in
  attribute values or preformatted text, after
  start tags and before end tags
*/

#define NORMAL        0u
#define PREFORMATTED  1u
#define COMMENT       2u
#define ATTRIBVALUE   4u
#define NOWRAP        8u
#define CDATA         16u


/* The pretty printer keeps at most two lines of text in the
** buffer before flushing output.  We need to capture the
** indent state (indent level) at the _beginning_ of _each_
** line, not the end of just the second line.
**
** We must also keep track "In Attribute" and "In String"
** states at the _end_ of each line, 
*/

typedef struct _TidyIndent
{
    int spaces;
    int attrValStart;
    int attrStringStart;
} TidyIndent;

typedef struct _TidyPrintImpl
{
    TidyAllocator *allocator; /* Allocator */

    uint *linebuf;
    uint lbufsize;
    uint linelen;
    uint wraphere;
    uint line;
  
    uint ixInd;
    TidyIndent indent[2];  /* Two lines worth of indent state */
} TidyPrintImpl;


#if 0 && SUPPORT_ASIAN_ENCODINGS
/* #431953 - start RJ Wraplen adjusted for smooth international ride */
uint CWrapLen( TidyDoc doc, uint ind );
#endif

void TY_(InitPrintBuf)( TidyDoc doc );
void TY_(FreePrintBuf)( TidyDoc doc );

void TY_(PFlushLine)( TidyDoc doc, uint indent );


/* print just the content of the body element.
** useful when you want to reuse material from
** other documents.
** 
** -- Sebastiano Vigna <vigna@dsi.unimi.it>
*/

void TY_(PrintBody)( TidyDoc doc );       /* you can print an entire document */
                                          /* node as body using PPrintTree() */

void TY_(PPrintTree)( TidyDoc doc, uint mode, uint indent, TidyNode node );

void TY_(PPrintXMLTree)( TidyDoc doc, uint mode, uint indent, TidyNode node );

/*\
 * 20150515 - support using tabs instead of spaces
\*/
void TY_(PPrintTabs)(void);
void TY_(PPrintSpaces)(void);

#endif /* __PPRINT_H__ */
