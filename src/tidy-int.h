#ifndef __TIDY_INT_H__
#define __TIDY_INT_H__

/* tidy-int.h -- internal library declarations

  (c) 1998-2007 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

*/

#include "tidy.h"
#include "config.h"
#include "lexer.h"
#include "tags.h"
#include "attrs.h"
#include "pprint.h"
#include "access.h"

#ifndef MAX
#define MAX(a,b) (((a) > (b))?(a):(b))
#endif
#ifndef MIN
#define MIN(a,b) (((a) < (b))?(a):(b))
#endif

/*\
 *  Issue #166 - repeated <main> element
 *  Change the previous on/off uint flag badForm
 *  to a BIT flag to support other than <form>
 *  errors. This could be extended more...
\*/
#define flg_BadForm     0x00000001
#define flg_BadMain     0x00000002

struct _TidyDocImpl
{
    /* The Document Tree (and backing store buffer) */
    Node                root;       /* This MUST remain the first declared 
                                       variable in this structure */
    Lexer*              lexer;

    /* Config + Markup Declarations */
    TidyConfigImpl      config;
    TidyTagImpl         tags;
    TidyAttribImpl      attribs;

#if SUPPORT_ACCESSIBILITY_CHECKS
    /* Accessibility Checks state */
    TidyAccessImpl      access;
#endif

    /* The Pretty Print buffer */
    TidyPrintImpl       pprint;

    /* I/O */
    StreamIn*           docIn;
    StreamOut*          docOut;
    StreamOut*          errout;
    TidyReportFilter    mssgFilt;
    TidyReportFilter2   mssgFilt2;
    TidyReportFilter3   mssgFilt3;
    TidyOptCallback     pOptCallback;
    TidyPPProgress      progressCallback;

    /* Parse + Repair Results */
    uint                optionErrors;
    uint                errors;
    uint                warnings;
    uint                accessErrors;
    uint                infoMessages;
    uint                docErrors;
    int                 parseStatus;

    uint                badAccess;   /* for accessibility errors */
    uint                badLayout;   /* for bad style errors */
    uint                badChars;    /* for bad char encodings */
    uint                badForm;     /* bit field, for badly placed form tags, or other format errors */

    Bool                HTML5Mode;  /* current mode is html5 */

    /* Memory allocator */
    TidyAllocator*      allocator;

    /* Miscellaneous */
    void*               appData;
    uint                nClassId;
    Bool                inputHadBOM;

#ifdef TIDY_STORE_ORIGINAL_TEXT
    Bool                storeText;
#endif

#if PRESERVE_FILE_TIMES
    struct utimbuf      filetimes;
#endif
    tmbstr              givenDoctype;
};


/* Twizzle internal/external types */
#ifdef NEVER
TidyDocImpl* tidyDocToImpl( TidyDoc tdoc );
TidyDoc      tidyImplToDoc( TidyDocImpl* impl );

Node*        tidyNodeToImpl( TidyNode tnod );
TidyNode     tidyImplToNode( Node* node );

AttVal*      tidyAttrToImpl( TidyAttr tattr );
TidyAttr     tidyImplToAttr( AttVal* attval );

const TidyOptionImpl* tidyOptionToImpl( TidyOption topt );
TidyOption   tidyImplToOption( const TidyOptionImpl* option );
#else

#define tidyDocToImpl( tdoc )       ((TidyDocImpl*)(tdoc))
#define tidyImplToDoc( doc )        ((TidyDoc)(doc))

#define tidyNodeToImpl( tnod )      ((Node*)(tnod))
#define tidyImplToNode( node )      ((TidyNode)(node))

#define tidyAttrToImpl( tattr )     ((AttVal*)(tattr))
#define tidyImplToAttr( attval )    ((TidyAttr)(attval))

#define tidyOptionToImpl( topt )    ((const TidyOptionImpl*)(topt))
#define tidyImplToOption( option )  ((TidyOption)(option))

#endif

/** Wrappers for easy memory allocation using the document's allocator */
#define TidyDocAlloc(doc, size) TidyAlloc((doc)->allocator, size)
#define TidyDocRealloc(doc, block, size) TidyRealloc((doc)->allocator, block, size)
#define TidyDocFree(doc, block) TidyFree((doc)->allocator, block)
#define TidyDocPanic(doc, msg) TidyPanic((doc)->allocator, msg)

int          TY_(DocParseStream)( TidyDocImpl* impl, StreamIn* in );

/*
   [i_a] generic node tree traversal code; used in several spots.

   Define your own callback, which returns one of the NodeTraversalSignal values
   to instruct the tree traversal routine TraverseNodeTree() what to do.

   Pass custom data to/from the callback using the 'propagate' reference.
 */
typedef enum
{
    ContinueTraversal,       /* visit siblings and children */
    SkipChildren,            /* visit siblings of this node; ignore its children */
    SkipSiblings,            /* ignore subsequent siblings of this node; ignore their children; traverse  */
    SkipChildrenAndSiblings, /* visit siblings of this node; ignore its children */
    VisitParent,             /* REVERSE traversal: visit the parent of the current node */
    ExitTraversal            /* terminate traversal on the spot */
} NodeTraversalSignal;

typedef NodeTraversalSignal NodeTraversalCallBack(TidyDocImpl* doc, Node* node, void *propagate);

NodeTraversalSignal TY_(TraverseNodeTree)(TidyDocImpl* doc, Node* node, NodeTraversalCallBack *cb, void *propagate);

#endif /* __TIDY_INT_H__ */
