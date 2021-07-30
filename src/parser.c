/* parser.c -- HTML Parser

  (c) 1998-2007 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

*/

#include "tidy-int.h"
#include "lexer.h"
#include "parser.h"
#include "message.h"
#include "clean.h"
#include "tags.h"
#include "tmbstr.h"
#include "sprtf.h"


/****************************************************************************//*
 ** MARK: - Forward Declarations
 ***************************************************************************/


static void ParseTag( TidyDocImpl* doc, Node *node, GetTokenMode mode );


/****************************************************************************//*
 ** MARK: - Configuration Options
 ***************************************************************************/


/**
 *  Issue #72  - Need to know to avoid error-reporting - no warning only if
 *               --show-body-only yes.
 *  Issue #132 - Likewise avoid warning if showing body only.
 */
#define showingBodyOnly(doc) (cfgAutoBool(doc,TidyBodyOnly) == TidyYesState) ? yes : no


/****************************************************************************//*
 ** MARK: - Node Operations
 ***************************************************************************/


/**
 *  Insert "node" into markup tree in place of "element"
 *  which is moved to become the child of the node
 */
static void InsertNodeAsParent(Node *element, Node *node)
{
    node->content = element;
    node->last = element;
    node->parent = element->parent;
    element->parent = node;

    if (node->parent->content == element)
        node->parent->content = node;

    if (node->parent->last == element)
        node->parent->last = node;

    node->prev = element->prev;
    element->prev = NULL;

    if (node->prev)
        node->prev->next = node;

    node->next = element->next;
    element->next = NULL;

    if (node->next)
        node->next->prev = node;
}


/**
 *  Inserts node into element at an appropriate location based
 *  on the type of node being inserted.
 */
static Bool InsertMisc(Node *element, Node *node)
{
    if (node->type == CommentTag ||
        node->type == ProcInsTag ||
        node->type == CDATATag ||
        node->type == SectionTag ||
        node->type == AspTag ||
        node->type == JsteTag ||
        node->type == PhpTag )
    {
        TY_(InsertNodeAtEnd)(element, node);
        return yes;
    }

    if ( node->type == XmlDecl )
    {
        Node* root = element;
        while ( root && root->parent )
            root = root->parent;
        if ( root && !(root->content && root->content->type == XmlDecl))
        {
          TY_(InsertNodeAtStart)( root, node );
          return yes;
        }
    }

    /* Declared empty tags seem to be slipping through
    ** the cracks.  This is an experiment to figure out
    ** a decent place to pick them up.
    */
    if ( node->tag &&
         TY_(nodeIsElement)(node) &&
         TY_(nodeCMIsEmpty)(node) && TagId(node) == TidyTag_UNKNOWN &&
         (node->tag->versions & VERS_PROPRIETARY) != 0 )
    {
        TY_(InsertNodeAtEnd)(element, node);
        return yes;
    }

    return no;
}


/**
 *  Move node to the head, where element is used as starting
 *  point in hunt for head. normally called during parsing.
 */
static void MoveToHead( TidyDocImpl* doc, Node *element, Node *node )
{
    Node *head;

    TY_(RemoveNode)( node );  /* make sure that node is isolated */

    if ( TY_(nodeIsElement)(node) )
    {
        TY_(Report)(doc, element, node, TAG_NOT_ALLOWED_IN );

        head = TY_(FindHEAD)(doc);
        assert(head != NULL);

        TY_(InsertNodeAtEnd)(head, node);

        if ( node->tag->parser )
            ParseTag( doc, node, IgnoreWhitespace );
    }
    else
    {
        TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED);
        TY_(FreeNode)( doc, node );
    }
}


/**
 *  Moves given node to end of body element.
 */
static void MoveNodeToBody( TidyDocImpl* doc, Node* node )
{
    Node* body = TY_(FindBody)( doc );
    if ( body )
    {
        TY_(RemoveNode)( node );
        TY_(InsertNodeAtEnd)( body, node );
    }
}


/**
 *  Unexpected content in table row is moved to just before the table in
 *  in accordance with Netscape and IE. This code assumes that node hasn't
 *  been inserted into the row.
 */
static void MoveBeforeTable( TidyDocImpl* ARG_UNUSED(doc), Node *row,
                            Node *node )
{
    Node *table;

    /* first find the table element */
    for (table = row->parent; table; table = table->parent)
    {
        if ( nodeIsTABLE(table) )
        {
            TY_(InsertNodeBeforeElement)( table, node );
            return;
        }
    }
    /* No table element */
    TY_(InsertNodeBeforeElement)( row->parent, node );
}


/**
 *  Generalised search for duplicate elements.
 *  Issue #166 - repeated <main> element.
 */
static Bool findNodeWithId( Node *node, TidyTagId tid )
{
    Node *content;
    while (node)
    {
        if (TagIsId(node,tid))
            return yes;
        /*\
         *   Issue #459 - Under certain circumstances, with many node this use of
         *   'for (content = node->content; content; content = content->content)'
         *   would produce a **forever** circle, or at least a very extended loop...
         *   It is sufficient to test the content, if it exists,
         *   to quickly iterate all nodes. Now all nodes are tested only once.
        \*/
        content = node->content;
        if (content)
        {
            if ( findNodeWithId(content,tid) )
                return yes;
        }
        node = node->next;
    }
    return no;
}


/**
 *  Perform a global search for an element.
 *  Issue #166 - repeated <main> element
 */
static Bool findNodeById( TidyDocImpl* doc, TidyTagId tid )
{
    Node *node = (doc ? doc->root.content : NULL);
    return findNodeWithId( node,tid );
}


/***************************************************************************//*
 ** MARK: - Decision Making
 ***************************************************************************/


/**
 *  Indicates whether or not element can be pruned based on content,
 *  user settings, etc.
 */
static Bool CanPrune( TidyDocImpl* doc, Node *element )
{
    if ( !cfgBool(doc, TidyDropEmptyElems) )
        return no;

    if ( TY_(nodeIsText)(element) )
        return yes;

    if ( element->content )
        return no;

    if ( element->tag == NULL )
        return no;

    if ( element->tag->model & CM_BLOCK && element->attributes != NULL )
        return no;

    if ( nodeIsA(element) && element->attributes != NULL )
        return no;

    if ( nodeIsP(element) && !cfgBool(doc, TidyDropEmptyParas) )
        return no;

    if ( element->tag->model & CM_ROW )
        return no;

    if ( element->tag->model & CM_EMPTY )
        return no;

    if ( nodeIsAPPLET(element) )
        return no;

    if ( nodeIsOBJECT(element) )
        return no;

    if ( nodeIsSCRIPT(element) && attrGetSRC(element) )
        return no;

    if ( nodeIsTITLE(element) )
        return no;

    /* #433359 - fix by Randy Waki 12 Mar 01 */
    if ( nodeIsIFRAME(element) )
        return no;

    /* fix for bug 770297 */
    if (nodeIsTEXTAREA(element))
        return no;

    /* fix for ISSUE #7 https://github.com/w3c/tidy-html5/issues/7 */
    if (nodeIsCANVAS(element))
        return no;
    
    if (nodeIsPROGRESS(element))
        return no;

    if ( attrGetID(element) || attrGetNAME(element) )
        return no;

    /* fix for bug 695408; a better fix would look for unknown and    */
    /* known proprietary attributes that make the element significant */
    if (attrGetDATAFLD(element))
        return no;

    /* fix for bug 723772, don't trim new-...-tags */
    if (element->tag->id == TidyTag_UNKNOWN)
        return no;

    if (nodeIsBODY(element))
        return no;

    if (nodeIsCOLGROUP(element))
        return no;

    /* HTML5 - do NOT drop empty option if it has attributes */
    if ( nodeIsOPTION(element) && element->attributes != NULL )
        return no;

    /* fix for #103 - don't drop empty dd tags lest document not validate */
    if (nodeIsDD(element))
        return no;

    return yes;
}


/**
 *  Indicates whether or not node is a descendant of a tag of the given tid.
 */
static Bool DescendantOf( Node *element, TidyTagId tid )
{
    Node *parent;
    for ( parent = element->parent;
         parent != NULL;
         parent = parent->parent )
    {
        if ( TagIsId(parent, tid) )
            return yes;
    }
    return no;
}


/**
 *  Indicates whether or not node is a descendant of a pre tag.
 */
static Bool IsPreDescendant(Node* node)
{
    Node *parent = node->parent;

    while (parent)
    {
        if (parent->tag && parent->tag->parser == TY_(ParsePre))
            return yes;

        parent = parent->parent;
    }

    return no;
}


/**
 *  Indicates whether or not trailing whitespace should be cleaned.
 */
static Bool CleanTrailingWhitespace(TidyDocImpl* doc, Node* node)
{
    Node* next;

    if (!TY_(nodeIsText)(node))
        return no;

    if (node->parent->type == DocTypeTag)
        return no;

    if (IsPreDescendant(node))
        return no;

    if (node->parent->tag && node->parent->tag->parser == TY_(ParseScript))
        return no;

    next = node->next;

    /* <p>... </p> */
    if (!next && !TY_(nodeHasCM)(node->parent, CM_INLINE))
        return yes;

    /* <div><small>... </small><h3>...</h3></div> */
    if (!next && node->parent->next && !TY_(nodeHasCM)(node->parent->next, CM_INLINE))
        return yes;

    if (!next)
        return no;

    if (nodeIsBR(next))
        return yes;

    if (TY_(nodeHasCM)(next, CM_INLINE))
        return no;

    /* <a href='/'>...</a> <p>...</p> */
    if (next->type == StartTag)
        return yes;

    /* <strong>...</strong> <hr /> */
    if (next->type == StartEndTag)
        return yes;

    /* evil adjacent text nodes, Tidy should not generate these :-( */
    if (TY_(nodeIsText)(next) && next->start < next->end
        && TY_(IsWhite)(doc->lexer->lexbuf[next->start]))
        return yes;

    return no;
}


/**
 *  Indicates whether or not leading whitespace should be cleaned.
 */
static Bool CleanLeadingWhitespace(TidyDocImpl* ARG_UNUSED(doc), Node* node)
{
    if (!TY_(nodeIsText)(node))
        return no;

    if (node->parent->type == DocTypeTag)
        return no;

    if (IsPreDescendant(node))
        return no;

    if (node->parent->tag && node->parent->tag->parser == TY_(ParseScript))
        return no;

    /* <p>...<br> <em>...</em>...</p> */
    if (nodeIsBR(node->prev))
        return yes;

    /* <p> ...</p> */
    if (node->prev == NULL && !TY_(nodeHasCM)(node->parent, CM_INLINE))
        return yes;

    /* <h4>...</h4> <em>...</em> */
    if (node->prev && !TY_(nodeHasCM)(node->prev, CM_INLINE) &&
        TY_(nodeIsElement)(node->prev))
        return yes;

    /* <p><span> ...</span></p> */
    if (!node->prev && !node->parent->prev && !TY_(nodeHasCM)(node->parent->parent, CM_INLINE))
        return yes;

    return no;
}


/**
 *  Indicates whether or not the content of the given node is acceptable
 *  content for pre elements
 */
static Bool PreContent( TidyDocImpl* ARG_UNUSED(doc), Node* node )
{
    /* p is coerced to br's, Text OK too */
    if ( nodeIsP(node) || TY_(nodeIsText)(node) )
        return yes;

    if ( node->tag == NULL ||
         nodeIsPARAM(node) ||
         !TY_(nodeHasCM)(node, CM_INLINE|CM_NEW) )
        return no;

    return yes;
}


/**
 *  Indicates whether or not the only content model for the given node
 *  is CM_INLINE.
 */
static Bool nodeCMIsOnlyInline( Node* node )
{
    return TY_(nodeHasCM)( node, CM_INLINE ) && !TY_(nodeHasCM)( node, CM_BLOCK );
}


/***************************************************************************//*
 ** MARK: - Information Accumulation
 ***************************************************************************/


/**
 *  Errors in positioning of form start or end tags
 *  generally require human intervention to fix.
 *  Issue #166 - repeated <main> element also uses this flag
 *  to indicate duplicates, discarded.
 */
static void BadForm( TidyDocImpl* doc )
{
    doc->badForm |= flg_BadForm;
}


/***************************************************************************//*
 ** MARK: - Fixes and Touchup
 ***************************************************************************/


/**
 *  This maps
 *     <em>hello </em><strong>world</strong>
 *  to
 *     <em>hello</em> <strong>world</strong>
 *
 *  If last child of element is a text node
 *  then trim trailing white space character
 *  moving it to after element's end tag.
 */
static void TrimTrailingSpace( TidyDocImpl* doc, Node *element, Node *last )
{
    Lexer* lexer = doc->lexer;
    byte c;

    if (TY_(nodeIsText)(last))
    {
        if (last->end > last->start)
        {
            c = (byte) lexer->lexbuf[ last->end - 1 ];

            if ( c == ' ' )
            {
                last->end -= 1;
                if ( (element->tag->model & CM_INLINE) &&
                     !(element->tag->model & CM_FIELD) )
                    lexer->insertspace = yes;
            }
        }
    }
}


/**
 *  This maps
 *     <p>hello<em> world</em>
 *  to
 *     <p>hello <em>world</em>
 *
 *  Trims initial space, by moving it before the
 *  start tag, or if this element is the first in
 *  parent's content, then by discarding the space
 */
static void TrimInitialSpace( TidyDocImpl* doc, Node *element, Node *text )
{
    Lexer* lexer = doc->lexer;
    Node *prev, *node;

    if ( TY_(nodeIsText)(text) && 
         lexer->lexbuf[text->start] == ' ' && 
         text->start < text->end )
    {
        if ( (element->tag->model & CM_INLINE) &&
             !(element->tag->model & CM_FIELD) )
        {
            prev = element->prev;

            if (TY_(nodeIsText)(prev))
            {
                if (prev->end == 0 || lexer->lexbuf[prev->end - 1] != ' ')
                    lexer->lexbuf[(prev->end)++] = ' ';

                ++(element->start);
            }
            else /* create new node */
            {
                node = TY_(NewNode)(lexer->allocator, lexer);
                node->start = (element->start)++;
                node->end = element->start;
                lexer->lexbuf[node->start] = ' ';
                TY_(InsertNodeBeforeElement)(element ,node);
                DEBUG_LOG(SPRTF("TrimInitialSpace: Created text node, inserted before <%s>\n",
                    (element->element ? element->element : "unknown")));
            }
        }

        /* discard the space in current node */
        ++(text->start);
    }
}


/**
 *  Cleans whitespace from text nodes, and drops such nodes if emptied
 *  completely as a result.
 */
static void CleanSpaces(TidyDocImpl* doc, Node* node)
{
    Stack *stack = TY_(newStack)(doc, 16);
    Node *next;
    
    while (node)
    {
        next = node->next;

        if (TY_(nodeIsText)(node) && CleanLeadingWhitespace(doc, node))
            while (node->start < node->end && TY_(IsWhite)(doc->lexer->lexbuf[node->start]))
                ++(node->start);

        if (TY_(nodeIsText)(node) && CleanTrailingWhitespace(doc, node))
            while (node->end > node->start && TY_(IsWhite)(doc->lexer->lexbuf[node->end - 1]))
                --(node->end);

        if (TY_(nodeIsText)(node) && !(node->start < node->end))
        {
            TY_(RemoveNode)(node);
            TY_(FreeNode)(doc, node);
            node = next ? next : TY_(pop)(stack);
            continue;
        }

        if (node->content)
        {
            TY_(push)(stack, next);
            node = node->content;
            continue;
        }

        node = next ? next : TY_(pop)(stack);
    }
    TY_(freeStack)(stack);
}


/**
 *  Move initial and trailing space out.
 *  This routine maps:
 *     hello<em> world</em>
 *  to
 *     hello <em>world</em>
 *  and
 *     <em>hello </em><strong>world</strong>
 *  to
 *     <em>hello</em> <strong>world</strong>
 */
static void TrimSpaces( TidyDocImpl* doc, Node *element)
{
    Node* text = element->content;

    if (nodeIsPRE(element) || IsPreDescendant(element))
        return;

    if (TY_(nodeIsText)(text))
        TrimInitialSpace(doc, element, text);

    text = element->last;

    if (TY_(nodeIsText)(text))
        TrimTrailingSpace(doc, element, text);
}


/**
 *  The doctype has been found after other tags,
 *  and needs moving to before the html element
 */
static void InsertDocType( TidyDocImpl* doc, Node *element, Node *doctype )
{
    Node* existing = TY_(FindDocType)( doc );
    if ( existing )
    {
        TY_(Report)(doc, element, doctype, DISCARDING_UNEXPECTED );
        TY_(FreeNode)( doc, doctype );
    }
    else
    {
        TY_(Report)(doc, element, doctype, DOCTYPE_AFTER_TAGS );
        while ( !nodeIsHTML(element) )
            element = element->parent;
        TY_(InsertNodeBeforeElement)( element, doctype );
    }
}



/**
 *  Adds style information as a class in the document or a property
 *  of the node to prevent indentation of inferred UL tags.
 */
static void AddClassNoIndent( TidyDocImpl* doc, Node *node )
{
    ctmbstr sprop =
    "padding-left: 2ex; margin-left: 0ex"
    "; margin-top: 0ex; margin-bottom: 0ex";
    if ( !cfgBool(doc, TidyDecorateInferredUL) )
        return;
    if ( cfgBool(doc, TidyMakeClean) )
        TY_(AddStyleAsClass)( doc, node, sprop );
    else
        TY_(AddStyleProperty)( doc, node, sprop );
}


/**
 *  If a table row is empty then insert an empty cell. This practice is
 *  consistent with browser behavior and avoids potential problems with
 *  row spanning cells.
 */
static void FixEmptyRow(TidyDocImpl* doc, Node *row)
{
    Node *cell;

    if (row->content == NULL)
    {
        cell = TY_(InferredTag)(doc, TidyTag_TD);
        TY_(InsertNodeAtEnd)(row, cell);
        TY_(Report)(doc, row, cell, MISSING_STARTTAG);
    }
}


/***************************************************************************//*
 ** MARK: - Parsers Support
 ***************************************************************************/


/**
 *  Structure used by FindDescendant_cb.
 */
struct MatchingDescendantData
{
    Node *found_node;
    Bool *passed_marker_node;

    /* input: */
    TidyTagId matching_tagId;
    Node *node_to_find;
    Node *marker_node;
};


/**
 *  The main engine for FindMatchingDescendant.
 */
static NodeTraversalSignal FindDescendant_cb(TidyDocImpl* ARG_UNUSED(doc), Node* node, void *propagate)
{
    struct MatchingDescendantData *cb_data = (struct MatchingDescendantData *)propagate;

    if (TagId(node) == cb_data->matching_tagId)
    {
        /* make sure we match up 'unknown' tags exactly! */
        if (cb_data->matching_tagId != TidyTag_UNKNOWN ||
            (node->element != NULL &&
            cb_data->node_to_find != NULL &&
            cb_data->node_to_find->element != NULL &&
            0 == TY_(tmbstrcmp)(cb_data->node_to_find->element, node->element)))
        {
            cb_data->found_node = node;
            return ExitTraversal;
        }
    }

    if (cb_data->passed_marker_node && node == cb_data->marker_node)
        *cb_data->passed_marker_node = yes;

    return VisitParent;
}


/**
 *  Search the parent chain (from `parent` upwards up to the root) for a node
 *  matching the given 'node'.
 *
 *  When the search passes beyond the `marker_node` (which is assumed to sit
 *  in the parent chain), this will be flagged by setting the boolean
 *  referenced by `is_parent_of_marker` to `yes`.
 *
 *  'is_parent_of_marker' and 'marker_node' are optional parameters and may
 *  be NULL.
 */
static Node *FindMatchingDescendant( Node *parent, Node *node, Node *marker_node, Bool *is_parent_of_marker )
{
    struct MatchingDescendantData cb_data = { 0 };
    cb_data.matching_tagId = TagId(node);
    cb_data.node_to_find = node;
    cb_data.marker_node = marker_node;

    assert(node);

    if (is_parent_of_marker)
        *is_parent_of_marker = no;

    TY_(TraverseNodeTree)(NULL, parent, FindDescendant_cb, &cb_data);
    return cb_data.found_node;
}


/**
 *   Finds the last list item for the given list, providing it in the
 *   in-out parameter. Returns yes or no if the item was the last list
 *   item.
 */
static Bool FindLastLI( Node *list, Node **lastli )
{
    Node *node;

    *lastli = NULL;
    for ( node = list->content; node ; node = node->next )
        if ( nodeIsLI(node) && node->type == StartTag )
            *lastli=node;
    return *lastli ? yes:no;
}


/***************************************************************************//*
 ** MARK: - Parser Stack
 ***************************************************************************/


/**
 *  Allocates and initializes the parser's stack.
 */
void TY_(InitParserStack)( TidyDocImpl* doc )
{
    uint default_size = 16;
    TidyParserMemory *content = (TidyParserMemory *) TidyAlloc( doc->allocator, sizeof(TidyParserMemory) * default_size );

    doc->stack.content = content;
    doc->stack.size = default_size;
    doc->stack.top = -1;
    doc->stack.allocator = doc->allocator;
}


/**
 *  Frees the parser's stack when done.
 */
void TY_(FreeParserStack)( TidyDocImpl* doc )
{
    TidyFree( doc->stack.allocator, doc->stack.content );

    doc->stack.content = NULL;
    doc->stack.size = 0;
    doc->stack.top = -1;
}


/**
 *  Increase the stack size.
 *  TODO: don't overflow max_uint. Need a message when we can no longer increase the size beyond 429 million depth.
 */
static void growParserStack( TidyDocImpl* doc )
{
    TidyParserMemory *content;
    content = (TidyParserMemory *) TidyAlloc( doc->stack.allocator, sizeof(TidyParserMemory) * doc->stack.size * 2 );

    memcpy( content, doc->stack.content, sizeof(TidyParserMemory) * (doc->stack.top + 1) );
    TidyFree(doc->stack.allocator, doc->stack.content);

    doc->stack.content = content;
    doc->stack.size = doc->stack.size * 2;
}


/**
 *  Indicates whether or not the stack is empty.
 */
static Bool isEmptyParserStack( TidyDocImpl* doc )
{
    return doc->stack.top < 0;
}


/**
 * Push the parser memory to the stack.
 */
static void pushMemory( TidyDocImpl* doc, TidyParserMemory data )
{
    if ( doc->stack.top == doc->stack.size - 1 )
        growParserStack( doc );

    doc->stack.top++;
    doc->stack.content[doc->stack.top] = data;
}


/**
 *  Peek at the parser memory.
 */
static FUNC_UNUSED TidyParserMemory peekMemory( TidyDocImpl* doc )
{
    return doc->stack.content[doc->stack.top];
}


/**
 *  Peek at the parser memory "mode" field. This is just a convenience
 *  to avoid having to create a new struct instance in the caller.
 */
static GetTokenMode peekMemoryMode( TidyDocImpl* doc )
{
    return doc->stack.content[doc->stack.top].mode;
}


/**
 *  Peek at the parser memory "identity" field. This is just a convenience
 *  to avoid having to create a new struct instance in the caller.
 */
static Parser* peekMemoryIdentity( TidyDocImpl* doc )
{
    return doc->stack.content[doc->stack.top].identity;
}


/**
 *  Pop out a parser memory.
 */
static TidyParserMemory popMemory( TidyDocImpl* doc )
{
    if ( !isEmptyParserStack( doc ) )
    {
        TidyParserMemory data = doc->stack.content[doc->stack.top];
        doc->stack.top = doc->stack.top - 1;
        return data;
    }
    TidyParserMemory blank = { NULL };
    return blank;
}


/***************************************************************************//*
 ** MARK: - Parser Search and Instantiation
 ***************************************************************************/


/**
 *  Retrieves the correct parser for the given node, accounting for various
 *  conditions, and readies the lexer for parsing that node.
 */
static Parser* GetParserForNode( TidyDocImpl* doc, Node *node )
{
    Lexer* lexer = doc->lexer;

    /* [i_a]2 prevent crash for active content (php, asp) docs */
    if (node->tag == NULL) 
        return NULL;

    /*
       Fix by GLP 2000-12-21.  Need to reset insertspace if this is both
       a non-inline and empty tag (base, link, meta, isindex, hr, area).
    */
    if (node->tag->model & CM_EMPTY)
    {
        lexer->waswhite = no;
        if (node->tag->parser == NULL)
            return NULL;
    }
    else if (!(node->tag->model & CM_INLINE))
        lexer->insertspace = no;

    if (node->tag->parser == NULL)
        return NULL;

    if (node->type == StartEndTag)
        return NULL;

    /* [i_a]2 added this - not sure why - CHECKME: */
    lexer->parent = node;

    return (node->tag->parser);
}


/**
 *  Instantiates the correct parser for the given node. This is currently
 *  maintained ONLY until the legacy parsers have been ported, as this
 *  introduces recursion when used.
 */
static void ParseTag( TidyDocImpl* doc, Node *node, GetTokenMode mode )
{
    Parser* parser = GetParserForNode( doc, node );

    if ( parser )
        (*parser)( doc, node, mode, no );
}


/**
 *  The main parser body will populate the document's document root starting
 *  with the provided node, which generally should be the HTML node after the
 *  pre-HTML stuff is handled at a higher level.
 *
 *  This parser works cooperatively with compliant parsers to pass state
 *  information back and forth in the TidyDocImpl's `stack`, which resides on
 *  the heap and prevents recursion and stack exhaustion, and also works well
 *  with the old-style parsers that do recurse.
 *
 *  (The goal is to update the old-style parsers slowly and deliberately
 *  without causing regressions, in a series of smaller commits and updates.)
 */
void ParseHTMLWithNode( TidyDocImpl* doc, Node* node )
{
    GetTokenMode mode = IgnoreWhitespace;
    Parser* parser = NULL;

    /*
     This main loop is only extinguished when all of the parser tokens are
     consumed. Note that most of the parsers consume tokens as well, and
     so what we're really doing here is managing parsers and preventing
     recursion with cooperating parsers.
     */
    while ( node )
    {
        if ( (parser = GetParserForNode( doc, node )) )
        {
            if ( (node = parser( doc, node, mode, no )) )
            {
                /*
                 When a parser returns a node, it means that we have
                 to continue the loop rather than moving on, because it
                 indicates that the parser encountered a token it does not
                 handle. It also tells us the correct GetTokenMode to use
                 for it via the struct that it pushed:
                 */
                mode = peekMemoryMode( doc );
                continue;
            }
        }

        /*
         If we've come this far, the parser has bottomed out, and won't be
         going any deeper. Now we run back up the stack to close all of the
         open elements and handle any parser post-processing that was needed.
         Of course, other nodes might cause us to deepen the stack again, too.
         */
        if ( !isEmptyParserStack( doc ) )
        {
            if ( (parser = peekMemoryIdentity( doc )) )
            {
                if ( (node = parser( doc, NULL, 0, yes )) )
                {
                    /* Another assignment from the parser. */
                    mode = peekMemoryMode( doc );
                    continue;
                }
            } else {
                /*
                 There's no identity in the stack (it was used to pass back
                 a GetToken mode, and nothing else, so remove discard it.
                 */
                popMemory( doc );
            }
        }

        /*
         Assuming we've gotten this far, there's no more work to do and
         so we can draw a nice, fresh token from the lexer.
         */
       node = TY_(GetToken)( doc, mode );
    }
}


/***************************************************************************//*
 ** MARK: - Old Parsers
 ***************************************************************************/


/** MARK: TY_(oldParseBlock)
 *  `element` is a node created by the lexer upon seeing the start tag, or
 *  by the parser when the start tag is inferred
 */
void* TY_(oldParseBlock)( TidyDocImpl* doc, Node *element, GetTokenMode mode)
{
#if defined(ENABLE_DEBUG_LOG)
    static int in_parse_block = 0;
    static int parse_block_cnt = 0;
#endif
    Lexer* lexer = doc->lexer;
    Node *node;
    Bool checkstack = yes;
    uint istackbase = 0;
#if defined(ENABLE_DEBUG_LOG)
    in_parse_block++;
    parse_block_cnt++;
    SPRTF("Entering ParseBlock %d... %d %s\n",in_parse_block,parse_block_cnt,
        ((element && element->element) ? element->element : ""));
#endif

    if ( element->tag->model & CM_EMPTY ) {
#if defined(ENABLE_DEBUG_LOG)
        in_parse_block--;
        SPRTF("Exit ParseBlockL 1 %d...\n",in_parse_block);
#endif
        return NULL;
    }

    if ( nodeIsFORM(element) &&
         DescendantOf(element, TidyTag_FORM) )
        TY_(Report)(doc, element, NULL, ILLEGAL_NESTING );

    /*
     InlineDup() asks the lexer to insert inline emphasis tags
     currently pushed on the istack, but take care to avoid
     propagating inline emphasis inside OBJECT or APPLET.
     For these elements a fresh inline stack context is created
     and disposed of upon reaching the end of the element.
     They thus behave like table cells in this respect.
    */
    if (element->tag->model & CM_OBJECT)
    {
        istackbase = lexer->istackbase;
        lexer->istackbase = lexer->istacksize;
    }

    if (!(element->tag->model & CM_MIXED))
        TY_(InlineDup)( doc, NULL );

    /*\
     *  Issue #212 - If it is likely that it may be necessary
     *  to move a leading space into a text node before this
     *  element, then keep the mode MixedContent to keep any
     *  leading space
    \*/
    if ( !(element->tag->model & CM_INLINE) ||
          (element->tag->model & CM_FIELD ) )
    {
        mode = IgnoreWhitespace;
    }
    else if (mode == IgnoreWhitespace)
    {
        /* Issue #212 - Further fix in case ParseBlock() is called with 'IgnoreWhitespace'
           when such a leading space may need to be inserted before this element to
           preverve the browser view */
        mode = MixedContent;
    }

    while ((node = TY_(GetToken)(doc, mode /*MixedContent*/)) != NULL)
    {
        /* end tag for this element */
        if (node->type == EndTag && node->tag &&
            (node->tag == element->tag || element->was == node->tag))
        {
            TY_(FreeNode)( doc, node );

            if (element->tag->model & CM_OBJECT)
            {
                /* pop inline stack */
                while (lexer->istacksize > lexer->istackbase)
                    TY_(PopInline)( doc, NULL );
                lexer->istackbase = istackbase;
            }

            element->closed = yes;
            TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
            in_parse_block--;
            SPRTF("Exit ParseBlock 2 %d...\n",in_parse_block);
#endif
            return NULL;
        }

        if ( nodeIsHTML(node) || nodeIsHEAD(node) || nodeIsBODY(node) )
        {
            if ( TY_(nodeIsElement)(node) )
                TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
            TY_(FreeNode)( doc, node );
            continue;
        }


        if (node->type == EndTag)
        {
            if (node->tag == NULL)
            {
                TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                TY_(FreeNode)( doc, node );
                continue;
            }
            else if ( nodeIsBR(node) )
                node->type = StartTag;
            else if ( nodeIsP(node) )
            {
                /* Cannot have a block inside a paragraph, so no checking
                   for an ancestor is necessary -- but we _can_ have
                   paragraphs inside a block, so change it to an implicit
                   empty paragraph, to be dealt with according to the user's
                   options
                */
                node->type = StartEndTag;
                node->implicit = yes;
            }
            else if (DescendantOf( element, node->tag->id ))
            {
                /*
                  if this is the end tag for an ancestor element
                  then infer end tag for this element
                */
                TY_(UngetToken)( doc );
                break;
            }
            else
            {
                /* special case </tr> etc. for stuff moved in front of table */
                if ( lexer->exiled
                     && (TY_(nodeHasCM)(node, CM_TABLE) || nodeIsTABLE(node)) )
                {
                    TY_(UngetToken)( doc );
                    TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
                    in_parse_block--;
                    SPRTF("Exit ParseBlock 2 %d...\n",in_parse_block);
#endif
                    return NULL;
                }
            }
        }

        /* mixed content model permits text */
        if (TY_(nodeIsText)(node))
        {
            if ( checkstack )
            {
                checkstack = no;
                if (!(element->tag->model & CM_MIXED))
                {
                    if ( TY_(InlineDup)(doc, node) > 0 )
                        continue;
                }
            }

            TY_(InsertNodeAtEnd)(element, node);
            mode = MixedContent;

            /*
              HTML4 strict doesn't allow mixed content for
              elements with %block; as their content model
            */
            /*
              But only body, map, blockquote, form and
              noscript have content model %block;
            */
            if ( nodeIsBODY(element)       ||
                 nodeIsMAP(element)        ||
                 nodeIsBLOCKQUOTE(element) ||
                 nodeIsFORM(element)       ||
                 nodeIsNOSCRIPT(element) )
                TY_(ConstrainVersion)( doc, ~VERS_HTML40_STRICT );
            continue;
        }

        if ( InsertMisc(element, node) )
            continue;

        /* allow PARAM elements? */
        if ( nodeIsPARAM(node) )
        {
            if ( TY_(nodeHasCM)(element, CM_PARAM) && TY_(nodeIsElement)(node) )
            {
                TY_(InsertNodeAtEnd)(element, node);
                continue;
            }

            /* otherwise discard it */
            TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
            TY_(FreeNode)( doc, node );
            continue;
        }

        /* allow AREA elements? */
        if ( nodeIsAREA(node) )
        {
            if ( nodeIsMAP(element) && TY_(nodeIsElement)(node) )
            {
                TY_(InsertNodeAtEnd)(element, node);
                continue;
            }

            /* otherwise discard it */
            TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
            TY_(FreeNode)( doc, node );
            continue;
        }

        /* ignore unknown start/end tags */
        if ( node->tag == NULL )
        {
            TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
            TY_(FreeNode)( doc, node );
            continue;
        }

        /*
          Allow CM_INLINE elements here.

          Allow CM_BLOCK elements here unless
          lexer->excludeBlocks is yes.

          LI and DD are special cased.

          Otherwise infer end tag for this element.
        */

        if ( !TY_(nodeHasCM)(node, CM_INLINE) )
        {
            if ( !TY_(nodeIsElement)(node) )
            {
                if ( nodeIsFORM(node) )
                    BadForm( doc );

                TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                TY_(FreeNode)( doc, node );
                continue;
            }

            /* #427671 - Fix by Randy Waki - 10 Aug 00 */
            /*
             If an LI contains an illegal FRAME, FRAMESET, OPTGROUP, or OPTION
             start tag, discard the start tag and let the subsequent content get
             parsed as content of the enclosing LI.  This seems to mimic IE and
             Netscape, and avoids an infinite loop: without this check,
             ParseBlock (which is parsing the LI's content) and ParseList (which
             is parsing the LI's parent's content) repeatedly defer to each
             other to parse the illegal start tag, each time inferring a missing
             </li> or <li> respectively.

             NOTE: This check is a bit fragile.  It specifically checks for the
             four tags that happen to weave their way through the current series
             of tests performed by ParseBlock and ParseList to trigger the
             infinite loop.
            */
            if ( nodeIsLI(element) )
            {
                if ( nodeIsFRAME(node)    ||
                     nodeIsFRAMESET(node) ||
                     nodeIsOPTGROUP(node) ||
                     nodeIsOPTION(node) )
                {
                    TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                    TY_(FreeNode)( doc, node );  /* DSR - 27Apr02 avoid memory leak */
                    continue;
                }
            }

            if ( nodeIsTD(element) || nodeIsTH(element) )
            {
                /* if parent is a table cell, avoid inferring the end of the cell */

                if ( TY_(nodeHasCM)(node, CM_HEAD) )
                {
                    MoveToHead( doc, element, node );
                    continue;
                }

                if ( TY_(nodeHasCM)(node, CM_LIST) )
                {
                    TY_(UngetToken)( doc );
                    node = TY_(InferredTag)(doc, TidyTag_UL);
                    AddClassNoIndent(doc, node);
                    lexer->excludeBlocks = yes;
                }
                else if ( TY_(nodeHasCM)(node, CM_DEFLIST) )
                {
                    TY_(UngetToken)( doc );
                    node = TY_(InferredTag)(doc, TidyTag_DL);
                    lexer->excludeBlocks = yes;
                }

                /* infer end of current table cell */
                if ( !TY_(nodeHasCM)(node, CM_BLOCK) )
                {
                    TY_(UngetToken)( doc );
                    TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
                    in_parse_block--;
                    SPRTF("Exit ParseBlock 3 %d...\n",in_parse_block);
#endif
                    return NULL;
                }
            }
            else if ( TY_(nodeHasCM)(node, CM_BLOCK) )
            {
                if ( lexer->excludeBlocks )
                {
                    if ( !TY_(nodeHasCM)(element, CM_OPT) )
                        TY_(Report)(doc, element, node, MISSING_ENDTAG_BEFORE );

                    TY_(UngetToken)( doc );

                    if ( TY_(nodeHasCM)(element, CM_OBJECT) )
                        lexer->istackbase = istackbase;

                    TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
                    in_parse_block--;
                    SPRTF("Exit ParseBlock 4 %d...\n",in_parse_block);
#endif
                    return NULL;
                }
            }
            else /* things like list items */
            {
                if (node->tag->model & CM_HEAD)
                {
                    MoveToHead( doc, element, node );
                    continue;
                }

                /*
                 special case where a form start tag
                 occurs in a tr and is followed by td or th
                */

                if ( nodeIsFORM(element) &&
                     nodeIsTD(element->parent) &&
                     element->parent->implicit )
                {
                    if ( nodeIsTD(node) )
                    {
                        TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                        TY_(FreeNode)( doc, node );
                        continue;
                    }

                    if ( nodeIsTH(node) )
                    {
                        TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                        TY_(FreeNode)( doc, node );
                        node = element->parent;
                        TidyDocFree(doc, node->element);
                        node->element = TY_(tmbstrdup)(doc->allocator, "th");
                        node->tag = TY_(LookupTagDef)( TidyTag_TH );
                        continue;
                    }
                }

                if ( !TY_(nodeHasCM)(element, CM_OPT) && !element->implicit )
                    TY_(Report)(doc, element, node, MISSING_ENDTAG_BEFORE );

                /* #521, warn on missing optional end-tags if not omitting them. */
                if ( cfgBool( doc, TidyOmitOptionalTags ) == no && TY_(nodeHasCM)(element, CM_OPT) )
                    TY_(Report)(doc, element, node, MISSING_ENDTAG_OPTIONAL );


                TY_(UngetToken)( doc );

                if ( TY_(nodeHasCM)(node, CM_LIST) )
                {
                    if ( element->parent && element->parent->tag &&
                         element->parent->tag->parser == TY_(ParseList) )
                    {
                        TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
                        in_parse_block--;
                        SPRTF("Exit ParseBlock 5 %d...\n",in_parse_block);
#endif
                        return NULL;
                    }

                    node = TY_(InferredTag)(doc, TidyTag_UL);
                    AddClassNoIndent(doc, node);
                }
                else if ( TY_(nodeHasCM)(node, CM_DEFLIST) )
                {
                    if ( nodeIsDL(element->parent) )
                    {
                        TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
                        in_parse_block--;
                        SPRTF("Exit ParseBlock 6 %d...\n",in_parse_block);
#endif
                        return NULL;
                    }

                    node = TY_(InferredTag)(doc, TidyTag_DL);
                }
                else if ( TY_(nodeHasCM)(node, CM_TABLE) || TY_(nodeHasCM)(node, CM_ROW) )
                {
                    /* http://tidy.sf.net/issue/1316307 */
                    /* In exiled mode, return so table processing can
                       continue. */
                    if (lexer->exiled) {
#if defined(ENABLE_DEBUG_LOG)
                        in_parse_block--;
                        SPRTF("Exit ParseBlock 7 %d...\n",in_parse_block);
#endif
                        return NULL;
                    }
                    node = TY_(InferredTag)(doc, TidyTag_TABLE);
                }
                else if ( TY_(nodeHasCM)(element, CM_OBJECT) )
                {
                    /* pop inline stack */
                    while ( lexer->istacksize > lexer->istackbase )
                        TY_(PopInline)( doc, NULL );
                    lexer->istackbase = istackbase;
                    TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
                    in_parse_block--;
                    SPRTF("Exit ParseBlock 8 %d...\n",in_parse_block);
#endif
                    return NULL;

                }
                else
                {
                    TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
                    in_parse_block--;
                    SPRTF("Exit ParseBlock 9 %d...\n",in_parse_block);
#endif
                    return NULL;
                }
            }
        }

        /*\
         *  Issue #307 - an <A> tag to ends any open <A> element
         *  Like #427827 - fixed by Randy Waki and Bjoern Hoehrmann 23 Aug 00
         *  in ParseInline(), fix copied HERE to ParseBlock()
         *  href: http://www.w3.org/TR/html-markup/a.html
         *  The interactive element a must not appear as a descendant of the a element.
        \*/
        if ( nodeIsA(node) && !node->implicit &&
             (nodeIsA(element) || DescendantOf(element, TidyTag_A)) )
        {
            if (node->type != EndTag && node->attributes == NULL
                && cfgBool(doc, TidyCoerceEndTags) )
            {
                node->type = EndTag;
                TY_(Report)(doc, element, node, COERCE_TO_ENDTAG);
                TY_(UngetToken)( doc );
                continue;
            }

            if (nodeIsA(element))
            {
                TY_(Report)(doc, element, node, MISSING_ENDTAG_BEFORE);
                TY_(UngetToken)( doc );
            }
            else
            {
                /* Issue #597 - if we not 'UngetToken' then it is being discarded.
                   Add message, and 'FreeNode' - thanks @ralfjunker */
                TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)(doc, node);
            }

            if (!(mode & Preformatted))
                TrimSpaces(doc, element);

#if defined(ENABLE_DEBUG_LOG)
            in_parse_block--;
            SPRTF("Exit ParseBlock 9b %d...\n",in_parse_block);
#endif
            return NULL;
        }

        /* parse known element */
        if (TY_(nodeIsElement)(node))
        {
            if (node->tag->model & CM_INLINE)
            {
                if (checkstack && !node->implicit)
                {
                    checkstack = no;

                    if (!(element->tag->model & CM_MIXED)) /* #431731 - fix by Randy Waki 25 Dec 00 */
                    {
                        if ( TY_(InlineDup)(doc, node) > 0 )
                            continue;
                    }
                }

                mode = MixedContent;
            }
            else
            {
                checkstack = yes;
                mode = IgnoreWhitespace;
            }

            /* trim white space before <br> */
            if ( nodeIsBR(node) )
                TrimSpaces( doc, element );

            TY_(InsertNodeAtEnd)(element, node);

            if (node->implicit)
                TY_(Report)(doc, element, node, INSERTING_TAG );

            /* Issue #212 - WHY is this hard coded to 'IgnoreWhitespace' while an
               effort has been made above to set a 'MixedContent' mode in some cases?
               WHY IS THE 'mode' VARIABLE NOT USED HERE???? */
            ParseTag( doc, node, IgnoreWhitespace /*MixedContent*/ );
            continue;
        }

        /* discard unexpected tags */
        if (node->type == EndTag)
            TY_(PopInline)( doc, node );  /* if inline end tag */

        TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
        TY_(FreeNode)( doc, node );
        continue;
    }

    if (!(element->tag->model & CM_OPT))
        TY_(Report)(doc, element, node, MISSING_ENDTAG_FOR);

    if (element->tag->model & CM_OBJECT)
    {
        /* pop inline stack */
        while ( lexer->istacksize > lexer->istackbase )
            TY_(PopInline)( doc, NULL );
        lexer->istackbase = istackbase;
    }

    TrimSpaces( doc, element );

#if defined(ENABLE_DEBUG_LOG)
    in_parse_block--;
    SPRTF("Exit ParseBlock 10 %d...\n",in_parse_block);
#endif
    return NULL;
}


/** MARK: TY_(oldParseInline)
 *  Parse inline element nodes.
 */
void* TY_(oldParseInline)( TidyDocImpl* doc, Node *element, GetTokenMode mode )
{
#if defined(ENABLE_DEBUG_LOG)
    static int in_parse_inline = 0;
#endif
    Lexer* lexer = doc->lexer;
    Node *node, *parent;
#if defined(ENABLE_DEBUG_LOG)
    in_parse_inline++;
    SPRTF("Entering ParseInline %d...\n",in_parse_inline);
#endif

    if (element->tag->model & CM_EMPTY) {
#if defined(ENABLE_DEBUG_LOG)
        in_parse_inline--;
        SPRTF("Exit ParseInline 1 %d...\n",in_parse_inline);
#endif
        return NULL;
    }

    /*
     ParseInline is used for some block level elements like H1 to H6
     For such elements we need to insert inline emphasis tags currently
     on the inline stack. For Inline elements, we normally push them
     onto the inline stack provided they aren't implicit or OBJECT/APPLET.
     This test is carried out in PushInline and PopInline, see istack.c

     InlineDup(...) is not called for elements with a CM_MIXED (inline and
     block) content model, e.g. <del> or <ins>, otherwise constructs like

       <p>111<a name='foo'>222<del>333</del>444</a>555</p>
       <p>111<span>222<del>333</del>444</span>555</p>
       <p>111<em>222<del>333</del>444</em>555</p>

     will get corrupted.
    */
    if ((TY_(nodeHasCM)(element, CM_BLOCK) || nodeIsDT(element)) &&
        !TY_(nodeHasCM)(element, CM_MIXED))
        TY_(InlineDup)(doc, NULL);
    else if (TY_(nodeHasCM)(element, CM_INLINE))
        TY_(PushInline)(doc, element);

    if ( nodeIsNOBR(element) )
        doc->badLayout |= USING_NOBR;
    else if ( nodeIsFONT(element) )
        doc->badLayout |= USING_FONT;

    /* Inline elements may or may not be within a preformatted element */
    if (mode != Preformatted)
        mode = MixedContent;

    while ((node = TY_(GetToken)(doc, mode)) != NULL)
    {
        /* end tag for current element */
        if (node->tag == element->tag && node->type == EndTag)
        {
            if (element->tag->model & CM_INLINE)
                TY_(PopInline)( doc, node );

            TY_(FreeNode)( doc, node );

            if (!(mode & Preformatted))
                TrimSpaces(doc, element);

            /*
             if a font element wraps an anchor and nothing else
             then move the font element inside the anchor since
             otherwise it won't alter the anchor text color
            */
            if ( nodeIsFONT(element) &&
                 element->content && element->content == element->last )
            {
                Node *child = element->content;

                if ( nodeIsA(child) )
                {
                    child->parent = element->parent;
                    child->next = element->next;
                    child->prev = element->prev;

                    element->next = NULL;
                    element->prev = NULL;
                    element->parent = child;

                    element->content = child->content;
                    element->last = child->last;
                    child->content = element;

                    TY_(FixNodeLinks)(child);
                    TY_(FixNodeLinks)(element);
                }
            }

            element->closed = yes;
            TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
            in_parse_inline--;
            SPRTF("Exit ParseInline 2 %d...\n",in_parse_inline);
#endif
            return NULL;
        }

        /* <u>...<u>  map 2nd <u> to </u> if 1st is explicit */
        /* (see additional conditions below) */
        /* otherwise emphasis nesting is probably unintentional */
        /* big, small, sub, sup have cumulative effect to leave them alone */
        if ( node->type == StartTag
             && node->tag == element->tag
             && TY_(IsPushed)( doc, node )
             && !node->implicit
             && !element->implicit
             && node->tag && (node->tag->model & CM_INLINE)
             && !nodeIsA(node)
             && !nodeIsFONT(node)
             && !nodeIsBIG(node)
             && !nodeIsSMALL(node)
             && !nodeIsSUB(node)
             && !nodeIsSUP(node)
             && !nodeIsQ(node)
             && !nodeIsSPAN(node)
             && cfgBool(doc, TidyCoerceEndTags)
           )
        {
            /* proceeds only if "node" does not have any attribute and
               follows a text node not finishing with a space */
            if (element->content != NULL && node->attributes == NULL
                && TY_(nodeIsText)(element->last)
                && !TY_(TextNodeEndWithSpace)(doc->lexer, element->last) )
            {
                TY_(Report)(doc, element, node, COERCE_TO_ENDTAG);
                node->type = EndTag;
                TY_(UngetToken)(doc);
                continue;
            }

            if (node->attributes == NULL || element->attributes == NULL)
                TY_(Report)(doc, element, node, NESTED_EMPHASIS);
        }
        else if ( TY_(IsPushed)(doc, node) && node->type == StartTag &&
                  nodeIsQ(node) )
        {
            /*\
             * Issue #215 - such nested quotes are NOT a problem if HTML5, so
             * only issue this warning if NOT HTML5 mode.
            \*/
            if (TY_(HTMLVersion)(doc) != HT50)
            {
                TY_(Report)(doc, element, node, NESTED_QUOTATION);
            }
        }

        if ( TY_(nodeIsText)(node) )
        {
            /* only called for 1st child */
            if ( element->content == NULL && !(mode & Preformatted) )
                TrimSpaces( doc, element );

            if ( node->start >= node->end )
            {
                TY_(FreeNode)( doc, node );
                continue;
            }

            TY_(InsertNodeAtEnd)(element, node);
            continue;
        }

        /* mixed content model so allow text */
        if (InsertMisc(element, node))
            continue;

        /* deal with HTML tags */
        if ( nodeIsHTML(node) )
        {
            if ( TY_(nodeIsElement)(node) )
            {
                TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                TY_(FreeNode)( doc, node );
                continue;
            }

            /* otherwise infer end of inline element */
            TY_(UngetToken)( doc );

            if (!(mode & Preformatted))
                TrimSpaces(doc, element);
#if defined(ENABLE_DEBUG_LOG)
            in_parse_inline--;
            SPRTF("Exit ParseInline 3 %d...\n",in_parse_inline);
#endif
            return NULL;
        }

        /* within <dt> or <pre> map <p> to <br> */
        if ( nodeIsP(node) &&
             node->type == StartTag &&
             ( (mode & Preformatted) ||
               nodeIsDT(element) ||
               DescendantOf(element, TidyTag_DT )
             )
           )
        {
            node->tag = TY_(LookupTagDef)( TidyTag_BR );
            TidyDocFree(doc, node->element);
            node->element = TY_(tmbstrdup)(doc->allocator, "br");
            TrimSpaces(doc, element);
            TY_(InsertNodeAtEnd)(element, node);
            continue;
        }

        /* <p> allowed within <address> in HTML 4.01 Transitional */
        if ( nodeIsP(node) &&
             node->type == StartTag &&
             nodeIsADDRESS(element) )
        {
            TY_(ConstrainVersion)( doc, ~VERS_HTML40_STRICT );
            TY_(InsertNodeAtEnd)(element, node);
            (*node->tag->parser)( doc, node, mode, no );
            continue;
        }

        /* ignore unknown and PARAM tags */
        if ( node->tag == NULL || nodeIsPARAM(node) )
        {
            TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node );
            continue;
        }

        if ( nodeIsBR(node) && node->type == EndTag )
            node->type = StartTag;

        if ( node->type == EndTag )
        {
           /* coerce </br> to <br> */
           if ( nodeIsBR(node) )
                node->type = StartTag;
           else if ( nodeIsP(node) )
           {
               /* coerce unmatched </p> to <br><br> */
                if ( !DescendantOf(element, TidyTag_P) )
                {
                    TY_(CoerceNode)(doc, node, TidyTag_BR, no, no);
                    TrimSpaces( doc, element );
                    TY_(InsertNodeAtEnd)( element, node );
                    node = TY_(InferredTag)(doc, TidyTag_BR);
                    TY_(InsertNodeAtEnd)( element, node ); /* todo: check this */
                    continue;
                }
           }
           else if ( TY_(nodeHasCM)(node, CM_INLINE)
                     && !nodeIsA(node)
                     && !TY_(nodeHasCM)(node, CM_OBJECT)
                     && TY_(nodeHasCM)(element, CM_INLINE) )
            {
                /* allow any inline end tag to end current element */

                /* http://tidy.sf.net/issue/1426419 */
                /* but, like the browser, retain an earlier inline element.
                   This is implemented by setting the lexer into a mode
                   where it gets tokens from the inline stack rather than
                   from the input stream. Check if the scenerio fits. */
                if ( !nodeIsA(element)
                     && (node->tag != element->tag)
                     && TY_(IsPushed)( doc, node )
                     && TY_(IsPushed)( doc, element ) )
                {
                    /* we have something like
                       <b>bold <i>bold and italic</b> italics</i> */
                    if ( TY_(SwitchInline)( doc, element, node ) )
                    {
                        TY_(Report)(doc, element, node, NON_MATCHING_ENDTAG);
                        TY_(UngetToken)( doc ); /* put this back */
                        TY_(InlineDup1)( doc, NULL, element ); /* dupe the <i>, after </b> */
                        if (!(mode & Preformatted))
                            TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
                        in_parse_inline--;
                        SPRTF("Exit ParseInline 4 %d...\n",in_parse_inline);
#endif
                        return NULL; /* close <i>, but will re-open it, after </b> */
                    }
                }
                TY_(PopInline)( doc, element );

                if ( !nodeIsA(element) )
                {
                    if ( nodeIsA(node) && node->tag != element->tag )
                    {
                       TY_(Report)(doc, element, node, MISSING_ENDTAG_BEFORE );
                       TY_(UngetToken)( doc );
                    }
                    else
                    {
                        TY_(Report)(doc, element, node, NON_MATCHING_ENDTAG);
                        TY_(FreeNode)( doc, node);
                    }

                    if (!(mode & Preformatted))
                        TrimSpaces(doc, element);
#if defined(ENABLE_DEBUG_LOG)
                    in_parse_inline--;
                    SPRTF("Exit ParseInline 5 %d...\n",in_parse_inline);
#endif
                    return NULL;
                }

                /* if parent is <a> then discard unexpected inline end tag */
                TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);
                continue;
            }  /* special case </tr> etc. for stuff moved in front of table */
            else if ( lexer->exiled
                     && (TY_(nodeHasCM)(node, CM_TABLE) || nodeIsTABLE(node)) )
            {
                TY_(UngetToken)( doc );
                TrimSpaces(doc, element);
#if defined(ENABLE_DEBUG_LOG)
                in_parse_inline--;
                SPRTF("Exit ParseInline 6 %d...\n",in_parse_inline);
#endif
                return NULL;
            }
        }

        /* allow any header tag to end current header */
        if ( TY_(nodeHasCM)(node, CM_HEADING) && TY_(nodeHasCM)(element, CM_HEADING) )
        {

            if ( node->tag == element->tag )
            {
                TY_(Report)(doc, element, node, NON_MATCHING_ENDTAG );
                TY_(FreeNode)( doc, node);
            }
            else
            {
                TY_(Report)(doc, element, node, MISSING_ENDTAG_BEFORE );
                TY_(UngetToken)( doc );
            }

            if (!(mode & Preformatted))
                TrimSpaces(doc, element);

#if defined(ENABLE_DEBUG_LOG)
            in_parse_inline--;
            SPRTF("Exit ParseInline 7 %d...\n",in_parse_inline);
#endif
            return NULL;
        }

        /*
           an <A> tag to ends any open <A> element
           but <A href=...> is mapped to </A><A href=...>
        */
        /* #427827 - fix by Randy Waki and Bjoern Hoehrmann 23 Aug 00 */
        /* if (node->tag == doc->tags.tag_a && !node->implicit && TY_(IsPushed)(doc, node)) */
        if ( nodeIsA(node) && !node->implicit &&
             (nodeIsA(element) || DescendantOf(element, TidyTag_A)) )
        {
            /* coerce <a> to </a> unless it has some attributes */
            /* #427827 - fix by Randy Waki and Bjoern Hoehrmann 23 Aug 00 */
            /* other fixes by Dave Raggett */
            /* if (node->attributes == NULL) */
            if (node->type != EndTag && node->attributes == NULL
                && cfgBool(doc, TidyCoerceEndTags) )
            {
                node->type = EndTag;
                TY_(Report)(doc, element, node, COERCE_TO_ENDTAG);
                /* TY_(PopInline)( doc, node ); */
                TY_(UngetToken)( doc );
                continue;
            }

            TY_(UngetToken)( doc );
            TY_(Report)(doc, element, node, MISSING_ENDTAG_BEFORE);
            /* TY_(PopInline)( doc, element ); */

            if (!(mode & Preformatted))
                TrimSpaces(doc, element);

#if defined(ENABLE_DEBUG_LOG)
            in_parse_inline--;
            SPRTF("Exit ParseInline 8 %d...\n",in_parse_inline);
#endif
            return NULL;
        }

        if (element->tag->model & CM_HEADING)
        {
            if ( nodeIsCENTER(node) || nodeIsDIV(node) )
            {
                if (!TY_(nodeIsElement)(node))
                {
                    TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED);
                    TY_(FreeNode)( doc, node);
                    continue;
                }

                TY_(Report)(doc, element, node, TAG_NOT_ALLOWED_IN);

                /* insert center as parent if heading is empty */
                if (element->content == NULL)
                {
                    InsertNodeAsParent(element, node);
                    continue;
                }

                /* split heading and make center parent of 2nd part */
                TY_(InsertNodeAfterElement)(element, node);

                if (!(mode & Preformatted))
                    TrimSpaces(doc, element);

                element = TY_(CloneNode)( doc, element );
                TY_(InsertNodeAtEnd)(node, element);
                continue;
            }

            if ( nodeIsHR(node) )
            {
                if ( !TY_(nodeIsElement)(node) )
                {
                    TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED);
                    TY_(FreeNode)( doc, node);
                    continue;
                }

                TY_(Report)(doc, element, node, TAG_NOT_ALLOWED_IN);

                /* insert hr before heading if heading is empty */
                if (element->content == NULL)
                {
                    TY_(InsertNodeBeforeElement)(element, node);
                    continue;
                }

                /* split heading and insert hr before 2nd part */
                TY_(InsertNodeAfterElement)(element, node);

                if (!(mode & Preformatted))
                    TrimSpaces(doc, element);

                element = TY_(CloneNode)( doc, element );
                TY_(InsertNodeAfterElement)(node, element);
                continue;
            }
        }

        if ( nodeIsDT(element) )
        {
            if ( nodeIsHR(node) )
            {
                Node *dd;
                if ( !TY_(nodeIsElement)(node) )
                {
                    TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED);
                    TY_(FreeNode)( doc, node);
                    continue;
                }

                TY_(Report)(doc, element, node, TAG_NOT_ALLOWED_IN);
                dd = TY_(InferredTag)(doc, TidyTag_DD);

                /* insert hr within dd before dt if dt is empty */
                if (element->content == NULL)
                {
                    TY_(InsertNodeBeforeElement)(element, dd);
                    TY_(InsertNodeAtEnd)(dd, node);
                    continue;
                }

                /* split dt and insert hr within dd before 2nd part */
                TY_(InsertNodeAfterElement)(element, dd);
                TY_(InsertNodeAtEnd)(dd, node);

                if (!(mode & Preformatted))
                    TrimSpaces(doc, element);

                element = TY_(CloneNode)( doc, element );
                TY_(InsertNodeAfterElement)(dd, element);
                continue;
            }
        }


        /*
          if this is the end tag for an ancestor element
          then infer end tag for this element
        */
        if (node->type == EndTag)
        {
            for (parent = element->parent;
                    parent != NULL; parent = parent->parent)
            {
                if (node->tag == parent->tag)
                {
                    if (!(element->tag->model & CM_OPT) && !element->implicit)
                        TY_(Report)(doc, element, node, MISSING_ENDTAG_BEFORE);

                    if( TY_(IsPushedLast)( doc, element, node ) )
                        TY_(PopInline)( doc, element );
                    TY_(UngetToken)( doc );

                    if (!(mode & Preformatted))
                        TrimSpaces(doc, element);

#if defined(ENABLE_DEBUG_LOG)
                    in_parse_inline--;
                    SPRTF("Exit ParseInline 9 %d...\n",in_parse_inline);
#endif
                    return NULL;
                }
            }
        }

        /*\
         *  block level tags end this element
         *  Issue #333 - There seems an exception if the element is a 'span',
         *  and the node just collected is a 'meta'. The 'meta' can not have
         *  CM_INLINE added, nor can the 'span' have CM_MIXED added without
         *  big consequences.
         *  There may be other exceptions to be added...
        \*/
        if (!(node->tag->model & CM_INLINE) &&
            !(element->tag->model & CM_MIXED) &&
            !(nodeIsSPAN(element) && nodeIsMETA(node)) )
        {
            if ( !TY_(nodeIsElement)(node) )
            {
                TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);
                continue;
            }
            /* HTML5 */
            if (nodeIsDATALIST(element)) {
                TY_(ConstrainVersion)( doc, ~VERS_HTML5 );
            } else
            if (!(element->tag->model & CM_OPT))
                TY_(Report)(doc, element, node, MISSING_ENDTAG_BEFORE);

            if (node->tag->model & CM_HEAD && !(node->tag->model & CM_BLOCK))
            {
                MoveToHead(doc, element, node);
                continue;
            }

            /*
               prevent anchors from propagating into block tags
               except for headings h1 to h6
            */
            if ( nodeIsA(element) )
            {
                if (node->tag && !(node->tag->model & CM_HEADING))
                    TY_(PopInline)( doc, element );
                else if (!(element->content))
                {
                    TY_(DiscardElement)( doc, element );
                    TY_(UngetToken)( doc );
#if defined(ENABLE_DEBUG_LOG)
                    in_parse_inline--;
                    SPRTF("Exit ParseInline 10 %d...\n",in_parse_inline);
#endif
                    return NULL;
                }
            }

            TY_(UngetToken)( doc );

            if (!(mode & Preformatted))
                TrimSpaces(doc, element);

#if defined(ENABLE_DEBUG_LOG)
            in_parse_inline--;
            SPRTF("Exit ParseInline 11 %d...\n",in_parse_inline);
#endif
            return NULL;
        }

        /* parse inline element */
        if (TY_(nodeIsElement)(node))
        {
            if (node->implicit)
                TY_(Report)(doc, element, node, INSERTING_TAG);

            /* trim white space before <br> */
            if ( nodeIsBR(node) )
                TrimSpaces(doc, element);

            TY_(InsertNodeAtEnd)(element, node);
            ParseTag(doc, node, mode);
            continue;
        }

        /* discard unexpected tags */
        TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED);
        TY_(FreeNode)( doc, node );
        continue;
    }

    if (!(element->tag->model & CM_OPT))
        TY_(Report)(doc, element, node, MISSING_ENDTAG_FOR);

#if defined(ENABLE_DEBUG_LOG)
    in_parse_inline--;
    SPRTF("Exit ParseInline 12 %d...\n",in_parse_inline);
#endif
    return NULL;
}


/** MARK: TY_(oldParseDefList)
 *  Parses the `dl` tag.
 */
void* TY_(oldParseDefList)(TidyDocImpl* doc, Node *list, GetTokenMode mode)
{
    Lexer* lexer = doc->lexer;
    Node *node, *parent;

    if (list->tag->model & CM_EMPTY)
        return NULL;

    lexer->insert = NULL;  /* defer implicit inline start tags */

    while ((node = TY_(GetToken)( doc, IgnoreWhitespace)) != NULL)
    {
        if (node->tag == list->tag && node->type == EndTag)
        {
            TY_(FreeNode)( doc, node);
            list->closed = yes;
            return NULL;
        }

        /* deal with comments etc. */
        if (InsertMisc(list, node))
            continue;

        if (TY_(nodeIsText)(node))
        {
            TY_(UngetToken)( doc );
            node = TY_(InferredTag)(doc, TidyTag_DT);
            TY_(Report)(doc, list, node, MISSING_STARTTAG);
        }

        if (node->tag == NULL)
        {
            TY_(Report)(doc, list, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        /*
          if this is the end tag for an ancestor element
          then infer end tag for this element
        */
        if (node->type == EndTag)
        {
            Bool discardIt = no;
            if ( nodeIsFORM(node) )
            {
                BadForm( doc );
                TY_(Report)(doc, list, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node );
                continue;
            }

            for (parent = list->parent;
                    parent != NULL; parent = parent->parent)
            {
               /* Do not match across BODY to avoid infinite loop
                  between ParseBody and this parser,
                  See http://tidy.sf.net/bug/1098012. */
                if (nodeIsBODY(parent))
                {
                    discardIt = yes;
                    break;
                }
                if (node->tag == parent->tag)
                {
                    TY_(Report)(doc, list, node, MISSING_ENDTAG_BEFORE);

                    TY_(UngetToken)( doc );
                    return NULL;
                }
            }
            if (discardIt)
            {
                TY_(Report)(doc, list, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);
                continue;
            }
        }

        /* center in a dt or a dl breaks the dl list in two */
        if ( nodeIsCENTER(node) )
        {
            if (list->content)
                TY_(InsertNodeAfterElement)(list, node);
            else /* trim empty dl list */
            {
                TY_(InsertNodeBeforeElement)(list, node);
            }

            /* #426885 - fix by Glenn Carroll 19 Apr 00, and
                         Gary Dechaines 11 Aug 00 */
            /* ParseTag can destroy node, if it finds that
             * this <center> is followed immediately by </center>.
             * It's awkward but necessary to determine if this
             * has happened.
             */
            parent = node->parent;

            /* and parse contents of center */
            lexer->excludeBlocks = no;
            ParseTag( doc, node, mode);
            lexer->excludeBlocks = yes;

            /* now create a new dl element,
             * unless node has been blown away because the
             * center was empty, as above.
             */
            if (parent && parent->last == node)
            {
                list = TY_(InferredTag)(doc, TidyTag_DL);
                TY_(InsertNodeAfterElement)(node, list);
            }
            continue;
        }

        if ( !(nodeIsDT(node) || nodeIsDD(node)) )
        {
            TY_(UngetToken)( doc );

            if (!(node->tag->model & (CM_BLOCK | CM_INLINE)))
            {
                TY_(Report)(doc, list, node, TAG_NOT_ALLOWED_IN);
                return NULL;
            }

            /* if DD appeared directly in BODY then exclude blocks */
            if (!(node->tag->model & CM_INLINE) && lexer->excludeBlocks)
                return NULL;

            node = TY_(InferredTag)(doc, TidyTag_DD);
            TY_(Report)(doc, list, node, MISSING_STARTTAG);
        }

        if (node->type == EndTag)
        {
            TY_(Report)(doc, list, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        /* node should be <DT> or <DD>*/
        TY_(InsertNodeAtEnd)(list, node);
        ParseTag( doc, node, IgnoreWhitespace);
    }

    TY_(Report)(doc, list, node, MISSING_ENDTAG_FOR);
    return NULL;
}


/** MARK: TY_(oldParseList)
 *  Parses list tags.
 */
void* TY_(oldParseList)(TidyDocImpl* doc, Node *list, GetTokenMode ARG_UNUSED(mode))
{
#if defined(ENABLE_DEBUG_LOG)
    static int in_parse_list = 0;
#endif
    Lexer* lexer = doc->lexer;
    Node *node, *parent, *lastli;
    Bool wasblock;
    Bool nodeisOL = nodeIsOL(list);

#if defined(ENABLE_DEBUG_LOG)
    in_parse_list++;
    SPRTF("Entering ParseList %d...\n",in_parse_list);
#endif
    if (list->tag->model & CM_EMPTY)
    {
#if defined(ENABLE_DEBUG_LOG)
        in_parse_list--;
        SPRTF("Exit ParseList 1 %d... CM_EMPTY\n",in_parse_list);
#endif
        return NULL;
    }
    lexer->insert = NULL;  /* defer implicit inline start tags */

    while ((node = TY_(GetToken)( doc, IgnoreWhitespace)) != NULL)
    {
        Bool foundLI = no;
        if (node->tag == list->tag && node->type == EndTag)
        {
            TY_(FreeNode)( doc, node);
            list->closed = yes;
#if defined(ENABLE_DEBUG_LOG)
            in_parse_list--;
            SPRTF("Exit ParseList 2 %d... Endtag\n",in_parse_list);
#endif
            return NULL;
        }

        /* deal with comments etc. */
        if (InsertMisc(list, node))
            continue;

        if (node->type != TextNode && node->tag == NULL)
        {
            TY_(Report)(doc, list, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }
        if (lexer && (node->type == TextNode))
        {
            uint ch, ix = node->start;
            /* Issue #572 - Skip whitespace. */
            while (ix < node->end && (ch = (lexer->lexbuf[ix] & 0xff))
                && (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'))
                ++ix;
            if (ix >= node->end)
            {
                /* Issue #572 - Discard if ALL whitespace. */
                TY_(FreeNode)(doc, node);
                continue;
            }
        }


        /*
          if this is the end tag for an ancestor element
          then infer end tag for this element
        */
        if (node->type == EndTag)
        {
            if ( nodeIsFORM(node) )
            {
                BadForm( doc );
                TY_(Report)(doc, list, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node );
                continue;
            }

            if (TY_(nodeHasCM)(node,CM_INLINE))
            {
                TY_(Report)(doc, list, node, DISCARDING_UNEXPECTED);
                TY_(PopInline)( doc, node );
                TY_(FreeNode)( doc, node);
                continue;
            }

            for ( parent = list->parent;
                  parent != NULL; parent = parent->parent )
            {
               /* Do not match across BODY to avoid infinite loop
                  between ParseBody and this parser,
                  See http://tidy.sf.net/bug/1053626. */
                if (nodeIsBODY(parent))
                    break;
                if (node->tag == parent->tag)
                {
                    TY_(Report)(doc, list, node, MISSING_ENDTAG_BEFORE);
                    TY_(UngetToken)( doc );
#if defined(ENABLE_DEBUG_LOG)
                    in_parse_list--;
                    SPRTF("Exit ParseList 3 %d... No End Tag\n",in_parse_list);
#endif
                    return NULL;
                }
            }

            TY_(Report)(doc, list, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        if ( !nodeIsLI(node) && nodeisOL )
        {
            /* Issue #572 - A <ol><li> can have nested <ol> elements */
            foundLI = FindLastLI(list, &lastli); /* find last <li> */
        }

        if ( nodeIsLI(node) || (TY_(IsHTML5Mode)(doc) && !foundLI) )
        {
            /* node is <LI> OR
               Issue #396 - A <ul> can have Zero or more <li> elements
             */
            TY_(InsertNodeAtEnd)(list,node);
        }
        else
        {
            TY_(UngetToken)( doc );

            if (TY_(nodeHasCM)(node,CM_BLOCK) && lexer->excludeBlocks)
            {
                TY_(Report)(doc, list, node, MISSING_ENDTAG_BEFORE);
#if defined(ENABLE_DEBUG_LOG)
                in_parse_list--;
                SPRTF("Exit ParseList 4 %d... No End Tag\n",in_parse_list);
#endif
                return NULL;
            }
            /* http://tidy.sf.net/issue/1316307 */
            /* In exiled mode, return so table processing can continue. */
            else if ( lexer->exiled
                      && (TY_(nodeHasCM)(node, CM_TABLE|CM_ROWGRP|CM_ROW)
                          || nodeIsTABLE(node)) )
            {
#if defined(ENABLE_DEBUG_LOG)
                in_parse_list--;
                SPRTF("Exit ParseList 5 %d... exiled\n",in_parse_list);
#endif
                return NULL;
            }
            /* http://tidy.sf.net/issue/836462
               If "list" is an unordered list, insert the next tag within
               the last <li> to preserve the numbering to match the visual
               rendering of most browsers. */
            if ( nodeIsOL(list) && FindLastLI(list, &lastli) )
            {
                /* Create a node for error reporting */
                node = TY_(InferredTag)(doc, TidyTag_LI);
                TY_(Report)(doc, list, node, MISSING_STARTTAG );
                TY_(FreeNode)( doc, node);
                node = lastli;
            }
            else
            {
                /* Add an inferred <li> */
                wasblock = TY_(nodeHasCM)(node,CM_BLOCK);
                node = TY_(InferredTag)(doc, TidyTag_LI);
                /* Add "display: inline" to avoid a blank line after <li> with
                   Internet Explorer. See http://tidy.sf.net/issue/836462 */
                TY_(AddStyleProperty)( doc, node,
                                       wasblock
                                       ? "list-style: none; display: inline"
                                       : "list-style: none"
                                       );
                TY_(Report)(doc, list, node, MISSING_STARTTAG );
                TY_(InsertNodeAtEnd)(list,node);
            }
        }

        ParseTag( doc, node, IgnoreWhitespace);
    }

    TY_(Report)(doc, list, node, MISSING_ENDTAG_FOR);
#if defined(ENABLE_DEBUG_LOG)
    in_parse_list--;
    SPRTF("Exit ParseList 6 %d... missing end tag\n",in_parse_list);
#endif
    return NULL;
}


/** MARK: TY_(oldParseRow)
 *  Parses the `row` tag.
 */
void* TY_(oldParseRow)(TidyDocImpl* doc, Node *row, GetTokenMode ARG_UNUSED(mode))
{
    Lexer* lexer = doc->lexer;
    Node *node;
    Bool exclude_state;

    if (row->tag->model & CM_EMPTY)
        return NULL;

    while ((node = TY_(GetToken)(doc, IgnoreWhitespace)) != NULL)
    {
        if (node->tag == row->tag)
        {
            if (node->type == EndTag)
            {
                TY_(FreeNode)( doc, node);
                row->closed = yes;
                FixEmptyRow( doc, row);
                return NULL;
            }

            /* New row start implies end of current row */
            TY_(UngetToken)( doc );
            FixEmptyRow( doc, row);
            return NULL;
        }

        /*
          if this is the end tag for an ancestor element
          then infer end tag for this element
        */
        if ( node->type == EndTag )
        {
            if ( (TY_(nodeHasCM)(node, CM_HTML|CM_TABLE) || nodeIsTABLE(node))
                 && DescendantOf(row, TagId(node)) )
            {
                TY_(UngetToken)( doc );
                return NULL;
            }

            if ( nodeIsFORM(node) || TY_(nodeHasCM)(node, CM_BLOCK|CM_INLINE) )
            {
                if ( nodeIsFORM(node) )
                    BadForm( doc );

                TY_(Report)(doc, row, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);
                continue;
            }

            if ( nodeIsTD(node) || nodeIsTH(node) )
            {
                TY_(Report)(doc, row, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);
                continue;
            }
        }

        /* deal with comments etc. */
        if (InsertMisc(row, node))
            continue;

        /* discard unknown tags */
        if (node->tag == NULL && node->type != TextNode)
        {
            TY_(Report)(doc, row, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        /* discard unexpected <table> element */
        if ( nodeIsTABLE(node) )
        {
            TY_(Report)(doc, row, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        /* THEAD, TFOOT or TBODY */
        if ( TY_(nodeHasCM)(node, CM_ROWGRP) )
        {
            TY_(UngetToken)( doc );
            return NULL;
        }

        if (node->type == EndTag)
        {
            TY_(Report)(doc, row, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        /*
          if text or inline or block move before table
          if head content move to head
        */

        if (node->type != EndTag)
        {
            if ( nodeIsFORM(node) )
            {
                TY_(UngetToken)( doc );
                node = TY_(InferredTag)(doc, TidyTag_TD);
                TY_(Report)(doc, row, node, MISSING_STARTTAG);
            }
            else if ( TY_(nodeIsText)(node)
                      || TY_(nodeHasCM)(node, CM_BLOCK | CM_INLINE) )
            {
                MoveBeforeTable( doc, row, node );
                TY_(Report)(doc, row, node, TAG_NOT_ALLOWED_IN);
                lexer->exiled = yes;
                exclude_state = lexer->excludeBlocks;
                lexer->excludeBlocks = no;

                if (node->type != TextNode)
                    ParseTag( doc, node, IgnoreWhitespace);

                lexer->exiled = no;
                lexer->excludeBlocks = exclude_state;
                continue;
            }
            else if (node->tag->model & CM_HEAD)
            {
                TY_(Report)(doc, row, node, TAG_NOT_ALLOWED_IN);
                MoveToHead( doc, row, node);
                continue;
            }
        }

        if ( !(nodeIsTD(node) || nodeIsTH(node)) )
        {
            TY_(Report)(doc, row, node, TAG_NOT_ALLOWED_IN);
            TY_(FreeNode)( doc, node);
            continue;
        }

        /* node should be <TD> or <TH> */
        TY_(InsertNodeAtEnd)(row, node);
        exclude_state = lexer->excludeBlocks;
        lexer->excludeBlocks = no;
        ParseTag( doc, node, IgnoreWhitespace);
        lexer->excludeBlocks = exclude_state;

        /* pop inline stack */

        while ( lexer->istacksize > lexer->istackbase )
            TY_(PopInline)( doc, NULL );
    }
    return NULL;
}


/** MARK: TY_(oldParseRowGroup)
 *  Parses the `rowgroup` tag.
 */
void* TY_(oldParseRowGroup)(TidyDocImpl* doc, Node *rowgroup, GetTokenMode ARG_UNUSED(mode))
{
    Lexer* lexer = doc->lexer;
    Node *node, *parent;

    if (rowgroup->tag->model & CM_EMPTY)
        return NULL;

    while ((node = TY_(GetToken)(doc, IgnoreWhitespace)) != NULL)
    {
        if (node->tag == rowgroup->tag)
        {
            if (node->type == EndTag)
            {
                rowgroup->closed = yes;
                TY_(FreeNode)( doc, node);
                return NULL;
            }

            TY_(UngetToken)( doc );
            return NULL;
        }

        /* if </table> infer end tag */
        if ( nodeIsTABLE(node) && node->type == EndTag )
        {
            TY_(UngetToken)( doc );
            return NULL;
        }

        /* deal with comments etc. */
        if (InsertMisc(rowgroup, node))
            continue;

        /* discard unknown tags */
        if (node->tag == NULL && node->type != TextNode)
        {
            TY_(Report)(doc, rowgroup, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        /*
          if TD or TH then infer <TR>
          if text or inline or block move before table
          if head content move to head
        */

        if (node->type != EndTag)
        {
            if ( nodeIsTD(node) || nodeIsTH(node) )
            {
                TY_(UngetToken)( doc );
                node = TY_(InferredTag)(doc, TidyTag_TR);
                TY_(Report)(doc, rowgroup, node, MISSING_STARTTAG);
            }
            else if ( TY_(nodeIsText)(node)
                      || TY_(nodeHasCM)(node, CM_BLOCK|CM_INLINE) )
            {
                MoveBeforeTable( doc, rowgroup, node );
                TY_(Report)(doc, rowgroup, node, TAG_NOT_ALLOWED_IN);
                lexer->exiled = yes;

                if (node->type != TextNode)
                    ParseTag(doc, node, IgnoreWhitespace);

                lexer->exiled = no;
                continue;
            }
            else if (node->tag->model & CM_HEAD)
            {
                TY_(Report)(doc, rowgroup, node, TAG_NOT_ALLOWED_IN);
                MoveToHead(doc, rowgroup, node);
                continue;
            }
        }

        /*
          if this is the end tag for ancestor element
          then infer end tag for this element
        */
        if (node->type == EndTag)
        {
            if ( nodeIsFORM(node) || TY_(nodeHasCM)(node, CM_BLOCK|CM_INLINE) )
            {
                if ( nodeIsFORM(node) )
                    BadForm( doc );

                TY_(Report)(doc, rowgroup, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);
                continue;
            }

            if ( nodeIsTR(node) || nodeIsTD(node) || nodeIsTH(node) )
            {
                TY_(Report)(doc, rowgroup, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);
                continue;
            }

            for ( parent = rowgroup->parent;
                  parent != NULL;
                  parent = parent->parent )
            {
                if (node->tag == parent->tag)
                {
                    TY_(UngetToken)( doc );
                    return NULL;
                }
            }
        }

        /*
          if THEAD, TFOOT or TBODY then implied end tag

        */
        if (node->tag->model & CM_ROWGRP)
        {
            if (node->type != EndTag)
            {
                TY_(UngetToken)( doc );
                return NULL;
            }
        }

        if (node->type == EndTag)
        {
            TY_(Report)(doc, rowgroup, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        if ( !nodeIsTR(node) )
        {
            node = TY_(InferredTag)(doc, TidyTag_TR);
            TY_(Report)(doc, rowgroup, node, MISSING_STARTTAG);
            TY_(UngetToken)( doc );
        }

       /* node should be <TR> */
        TY_(InsertNodeAtEnd)(rowgroup, node);
        ParseTag(doc, node, IgnoreWhitespace);
    }
    return NULL;
}


/** MARK: TY_(oldParseColGroup)
 *  Parses the `colgroup` tag.
 */
void* TY_(oldParseColGroup)(TidyDocImpl* doc, Node *colgroup, GetTokenMode ARG_UNUSED(mode))
{
    Node *node, *parent;

    if (colgroup->tag->model & CM_EMPTY)
        return NULL;

    while ((node = TY_(GetToken)(doc, IgnoreWhitespace)) != NULL)
    {
        if (node->tag == colgroup->tag && node->type == EndTag)
        {
            TY_(FreeNode)( doc, node);
            colgroup->closed = yes;
            return NULL;
        }

        /*
          if this is the end tag for an ancestor element
          then infer end tag for this element
        */
        if (node->type == EndTag)
        {
            if ( nodeIsFORM(node) )
            {
                BadForm( doc );
                TY_(Report)(doc, colgroup, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);
                continue;
            }

            for ( parent = colgroup->parent;
                  parent != NULL;
                  parent = parent->parent )
            {
                if (node->tag == parent->tag)
                {
                    TY_(UngetToken)( doc );
                    return NULL;
                }
            }
        }

        if (TY_(nodeIsText)(node))
        {
            TY_(UngetToken)( doc );
            return NULL;
        }

        /* deal with comments etc. */
        if (InsertMisc(colgroup, node))
            continue;

        /* discard unknown tags */
        if (node->tag == NULL)
        {
            TY_(Report)(doc, colgroup, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        if ( !nodeIsCOL(node) )
        {
            TY_(UngetToken)( doc );
            return NULL;
        }

        if (node->type == EndTag)
        {
            TY_(Report)(doc, colgroup, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        /* node should be <COL> */
        TY_(InsertNodeAtEnd)(colgroup, node);
        ParseTag(doc, node, IgnoreWhitespace);
    }
    return NULL;
}


/** MARK: TY_(oldParseTableTag)
 *  Parses the `table` tag.
 */
void* TY_(oldParseTableTag)(TidyDocImpl* doc, Node *table, GetTokenMode ARG_UNUSED(mode))
{
#if defined(ENABLE_DEBUG_LOG)
    static int in_parse_table = 0;
#endif
    Lexer* lexer = doc->lexer;
    Node *node, *parent;
    uint istackbase;

    TY_(DeferDup)( doc );
    istackbase = lexer->istackbase;
    lexer->istackbase = lexer->istacksize;
#if defined(ENABLE_DEBUG_LOG)
    in_parse_table++;
    SPRTF("Entering ParseTableTag %d...\n",in_parse_table);
#endif

    while ((node = TY_(GetToken)(doc, IgnoreWhitespace)) != NULL)
    {
        if (node->tag == table->tag )
        {
            if (node->type == EndTag)
            {
                TY_(FreeNode)(doc, node);
            }
            else
            {
                /* Issue #498 - If a <table> in a <table>
                 * just close the current table, and issue a
                 * warning. The previous action was to discard
                 * this second <table>
                 */
                TY_(UngetToken)(doc);
                TY_(Report)(doc, table, node, TAG_NOT_ALLOWED_IN);
            }
            lexer->istackbase = istackbase;
            table->closed = yes;
#if defined(ENABLE_DEBUG_LOG)
            in_parse_table--;
            SPRTF("Exit ParseTableTag 1 %d... EndTag\n",in_parse_table);
#endif
            return NULL;
        }

        /* deal with comments etc. */
        if (InsertMisc(table, node))
            continue;

        /* discard unknown tags */
        if (node->tag == NULL && node->type != TextNode)
        {
            TY_(Report)(doc, table, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        /* if TD or TH or text or inline or block then infer <TR> */

        if (node->type != EndTag)
        {
            if ( nodeIsTD(node) || nodeIsTH(node) || nodeIsTABLE(node) )
            {
                TY_(UngetToken)( doc );
                node = TY_(InferredTag)(doc, TidyTag_TR);
                TY_(Report)(doc, table, node, MISSING_STARTTAG);
            }
            else if ( TY_(nodeIsText)(node) ||TY_(nodeHasCM)(node,CM_BLOCK|CM_INLINE) )
            {
                TY_(InsertNodeBeforeElement)(table, node);
                TY_(Report)(doc, table, node, TAG_NOT_ALLOWED_IN);
                lexer->exiled = yes;

                if (node->type != TextNode)
                    ParseTag(doc, node, IgnoreWhitespace);

                lexer->exiled = no;
                continue;
            }
            else if (node->tag->model & CM_HEAD)
            {
                MoveToHead(doc, table, node);
                continue;
            }
        }

        /*
          if this is the end tag for an ancestor element
          then infer end tag for this element
        */
        if (node->type == EndTag)
        {
            if ( nodeIsFORM(node) )
            {
                BadForm( doc );
                TY_(Report)(doc, table, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);
                continue;
            }

            /* best to discard unexpected block/inline end tags */
            if ( TY_(nodeHasCM)(node, CM_TABLE|CM_ROW) ||
                 TY_(nodeHasCM)(node, CM_BLOCK|CM_INLINE) )
            {
                TY_(Report)(doc, table, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);
                continue;
            }

            for ( parent = table->parent;
                  parent != NULL;
                  parent = parent->parent )
            {
                if (node->tag == parent->tag)
                {
                    TY_(Report)(doc, table, node, MISSING_ENDTAG_BEFORE );
                    TY_(UngetToken)( doc );
                    lexer->istackbase = istackbase;
#if defined(ENABLE_DEBUG_LOG)
                    in_parse_table--;
                    SPRTF("Exit ParseTableTag 2 %d... missing EndTag\n",in_parse_table);
#endif
                    return NULL;
                }
            }
        }

        if (!(node->tag->model & CM_TABLE))
        {
            TY_(UngetToken)( doc );
            TY_(Report)(doc, table, node, TAG_NOT_ALLOWED_IN);
            lexer->istackbase = istackbase;
#if defined(ENABLE_DEBUG_LOG)
            in_parse_table--;
            SPRTF("Exit ParseTableTag 3 %d... CM_TABLE\n",in_parse_table);
#endif
            return NULL;
        }

        if (TY_(nodeIsElement)(node))
        {
            TY_(InsertNodeAtEnd)(table, node);
            ParseTag(doc, node, IgnoreWhitespace);
            continue;
        }

        /* discard unexpected text nodes and end tags */
        TY_(Report)(doc, table, node, DISCARDING_UNEXPECTED);
        TY_(FreeNode)( doc, node);
    }

    TY_(Report)(doc, table, node, MISSING_ENDTAG_FOR);
    lexer->istackbase = istackbase;
#if defined(ENABLE_DEBUG_LOG)
    in_parse_table--;
    SPRTF("Exit ParseTableTag 4 %d... missing end\n",in_parse_table);
#endif
    return NULL;
}


/** MARK: TY_(oldParsePre)
 *  Parses the `pre` tag.
 */
void* TY_(oldParsePre)( TidyDocImpl* doc, Node *pre, GetTokenMode ARG_UNUSED(mode) )
{
    Node *node;

    if (pre->tag->model & CM_EMPTY)
        return NULL;

    TY_(InlineDup)( doc, NULL ); /* tell lexer to insert inlines if needed */

    while ((node = TY_(GetToken)(doc, Preformatted)) != NULL)
    {
        if ( node->type == EndTag &&
             (node->tag == pre->tag || DescendantOf(pre, TagId(node))) )
        {
            if (nodeIsBODY(node) || nodeIsHTML(node))
            {
                TY_(Report)(doc, pre, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)(doc, node);
                continue;
            }
            if (node->tag == pre->tag)
            {
                TY_(FreeNode)(doc, node);
            }
            else
            {
                TY_(Report)(doc, pre, node, MISSING_ENDTAG_BEFORE );
                TY_(UngetToken)( doc );
            }
            pre->closed = yes;
            TrimSpaces(doc, pre);
            return NULL;
        }

        if (TY_(nodeIsText)(node))
        {
            TY_(InsertNodeAtEnd)(pre, node);
            continue;
        }

        /* deal with comments etc. */
        if (InsertMisc(pre, node))
            continue;

        if (node->tag == NULL)
        {
            TY_(Report)(doc, pre, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)(doc, node);
            continue;
        }

        /* strip unexpected tags */
        if ( !PreContent(doc, node) )
        {
            Node *newnode;

            /* fix for http://tidy.sf.net/bug/772205 */
            if (node->type == EndTag)
            {
                /* http://tidy.sf.net/issue/1590220 */
               if ( doc->lexer->exiled
                   && (TY_(nodeHasCM)(node, CM_TABLE) || nodeIsTABLE(node)) )
               {
                  TY_(UngetToken)(doc);
                  TrimSpaces(doc, pre);
                  return NULL;
               }

               TY_(Report)(doc, pre, node, DISCARDING_UNEXPECTED);
               TY_(FreeNode)(doc, node);
               continue;
            }
            /* http://tidy.sf.net/issue/1590220 */
            else if (TY_(nodeHasCM)(node, CM_TABLE|CM_ROW)
                     || nodeIsTABLE(node) )
            {
                if (!doc->lexer->exiled)
                    /* No missing close warning if exiled. */
                    TY_(Report)(doc, pre, node, MISSING_ENDTAG_BEFORE);

                TY_(UngetToken)(doc);
                return NULL;
            }

            /*
              This is basically what Tidy 04 August 2000 did and far more accurate
              with respect to browser behaivour than the code commented out above.
              Tidy could try to propagate the <pre> into each disallowed child where
              <pre> is allowed in order to replicate some browsers behaivour, but
              there are a lot of exceptions, e.g. Internet Explorer does not propagate
              <pre> into table cells while Mozilla does. Opera 6 never propagates
              <pre> into blocklevel elements while Opera 7 behaves much like Mozilla.

              Tidy behaves thus mostly like Opera 6 except for nested <pre> elements
              which are handled like Mozilla takes them (Opera6 closes all <pre> after
              the first </pre>).

              There are similar issues like replacing <p> in <pre> with <br>, for
              example

                <pre>...<p>...</pre>                 (Input)
                <pre>...<br>...</pre>                (Tidy)
                <pre>...<br>...</pre>                (Opera 7 and Internet Explorer)
                <pre>...<br><br>...</pre>            (Opera 6 and Mozilla)

                <pre>...<p>...</p>...</pre>          (Input)
                <pre>...<br>......</pre>             (Tidy, BUG!)
                <pre>...<br>...<br>...</pre>         (Internet Explorer)
                <pre>...<br><br>...<br><br>...</pre> (Mozilla, Opera 6)
                <pre>...<br>...<br><br>...</pre>     (Opera 7)

              or something similar, they could also be closing the <pre> and propagate
              the <pre> into the newly opened <p>.

              Todo: IMG, OBJECT, APPLET, BIG, SMALL, SUB, SUP, FONT, and BASEFONT are
              disallowed in <pre>, Tidy neither detects this nor does it perform any
              cleanup operation. Tidy should at least issue a warning if it encounters
              such constructs.

              Todo: discarding </p> is abviously a bug, it should be replaced by <br>.
            */
            TY_(InsertNodeAfterElement)(pre, node);
            TY_(Report)(doc, pre, node, MISSING_ENDTAG_BEFORE);
            ParseTag(doc, node, IgnoreWhitespace);

            newnode = TY_(InferredTag)(doc, TidyTag_PRE);
            TY_(Report)(doc, pre, newnode, INSERTING_TAG);
            pre = newnode;
            TY_(InsertNodeAfterElement)(node, pre);

            continue;
        }

        if ( nodeIsP(node) )
        {
            if (node->type == StartTag)
            {
                TY_(Report)(doc, pre, node, USING_BR_INPLACE_OF);

                /* trim white space before <p> in <pre>*/
                TrimSpaces(doc, pre);

                /* coerce both <p> and </p> to <br> */
                TY_(CoerceNode)(doc, node, TidyTag_BR, no, no);
                TY_(FreeAttrs)( doc, node ); /* discard align attribute etc. */
                TY_(InsertNodeAtEnd)( pre, node );
            }
            else
            {
                TY_(Report)(doc, pre, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);
            }
            continue;
        }

        if ( TY_(nodeIsElement)(node) )
        {
            /* trim white space before <br> */
            if ( nodeIsBR(node) )
                TrimSpaces(doc, pre);

            TY_(InsertNodeAtEnd)(pre, node);
            ParseTag(doc, node, Preformatted);
            continue;
        }

        /* discard unexpected tags */
        TY_(Report)(doc, pre, node, DISCARDING_UNEXPECTED);
        TY_(FreeNode)( doc, node);
    }

    TY_(Report)(doc, pre, node, MISSING_ENDTAG_FOR);
    return NULL;
}


/** MARK: TY_(oldParseOptGroup)
 *  Parses the `optgroup` tag.
 */
void* TY_(oldParseOptGroup)(TidyDocImpl* doc, Node *field, GetTokenMode ARG_UNUSED(mode))
{
    Lexer* lexer = doc->lexer;
    Node *node;

    lexer->insert = NULL;  /* defer implicit inline start tags */

    while ((node = TY_(GetToken)(doc, IgnoreWhitespace)) != NULL)
    {
        if (node->tag == field->tag && node->type == EndTag)
        {
            TY_(FreeNode)( doc, node);
            field->closed = yes;
            TrimSpaces(doc, field);
            return NULL;
        }

        /* deal with comments etc. */
        if (InsertMisc(field, node))
            continue;

        if ( node->type == StartTag &&
             (nodeIsOPTION(node) || nodeIsOPTGROUP(node)) )
        {
            if ( nodeIsOPTGROUP(node) )
                TY_(Report)(doc, field, node, CANT_BE_NESTED);

            TY_(InsertNodeAtEnd)(field, node);
            ParseTag(doc, node, MixedContent);
            continue;
        }

        /* discard unexpected tags */
        TY_(Report)(doc, field, node, DISCARDING_UNEXPECTED );
        TY_(FreeNode)( doc, node);
    }
    return NULL;
}


/** MARK: TY_(oldParseSelect)
 *  Parses the `select` tag.
 */
void* TY_(oldParseSelect)(TidyDocImpl* doc, Node *field, GetTokenMode ARG_UNUSED(mode))
{
#if defined(ENABLE_DEBUG_LOG)
    static int in_parse_select = 0;
#endif
    Lexer* lexer = doc->lexer;
    Node *node;

    lexer->insert = NULL;  /* defer implicit inline start tags */
#if defined(ENABLE_DEBUG_LOG)
    in_parse_select++;
    SPRTF("Entering ParseSelect %d...\n",in_parse_select);
#endif

    while ((node = TY_(GetToken)(doc, IgnoreWhitespace)) != NULL)
    {
        if (node->tag == field->tag && node->type == EndTag)
        {
            TY_(FreeNode)( doc, node);
            field->closed = yes;
            TrimSpaces(doc, field);
#if defined(ENABLE_DEBUG_LOG)
            in_parse_select--;
            SPRTF("Exit ParseSelect 1 %d...\n",in_parse_select);
#endif
            return NULL;
        }

        /* deal with comments etc. */
        if (InsertMisc(field, node))
            continue;

        if ( node->type == StartTag &&
             ( nodeIsOPTION(node)   ||
               nodeIsOPTGROUP(node) ||
               nodeIsDATALIST(node) ||
               nodeIsSCRIPT(node))
           )
        {
            TY_(InsertNodeAtEnd)(field, node);
            ParseTag(doc, node, IgnoreWhitespace);
            continue;
        }

        /* discard unexpected tags */
        TY_(Report)(doc, field, node, DISCARDING_UNEXPECTED);
        TY_(FreeNode)( doc, node);
    }

    TY_(Report)(doc, field, node, MISSING_ENDTAG_FOR);
#if defined(ENABLE_DEBUG_LOG)
    in_parse_select--;
    SPRTF("Exit ParseSelect 2 %d...\n",in_parse_select);
#endif
    return NULL;
}


/** MARK: TY_(oldParseDataList)
 *  Parses the `datalist` tag.
 */
void* TY_(oldParseDatalist)(TidyDocImpl* doc, Node *field, GetTokenMode ARG_UNUSED(mode))
{
#if defined(ENABLE_DEBUG_LOG)
    static int in_parse_datalist = 0;
#endif
    Lexer* lexer = doc->lexer;
    Node *node;

    lexer->insert = NULL;  /* defer implicit inline start tags */
#if defined(ENABLE_DEBUG_LOG)
    in_parse_datalist++;
    SPRTF("Entering ParseDatalist %d...\n",in_parse_datalist);
#endif

    while ((node = TY_(GetToken)(doc, IgnoreWhitespace)) != NULL)
    {
        if (node->tag == field->tag && node->type == EndTag)
        {
            TY_(FreeNode)( doc, node);
            field->closed = yes;
            TrimSpaces(doc, field);
#if defined(ENABLE_DEBUG_LOG)
            in_parse_datalist--;
            SPRTF("Exit ParseDatalist 1 %d...\n",in_parse_datalist);
#endif
            return NULL;
        }

        /* deal with comments etc. */
        if (InsertMisc(field, node))
            continue;

        if ( node->type == StartTag &&
             ( nodeIsOPTION(node)   ||
               nodeIsOPTGROUP(node) ||
               nodeIsDATALIST(node) ||
               nodeIsSCRIPT(node))
           )
        {
            TY_(InsertNodeAtEnd)(field, node);
            ParseTag(doc, node, IgnoreWhitespace);
            continue;
        }

        /* discard unexpected tags */
        TY_(Report)(doc, field, node, DISCARDING_UNEXPECTED);
        TY_(FreeNode)( doc, node);
    }

    TY_(Report)(doc, field, node, MISSING_ENDTAG_FOR);
#if defined(ENABLE_DEBUG_LOG)
    in_parse_datalist--;
    SPRTF("Exit ParseDatalist 2 %d...\n",in_parse_datalist);
#endif
    return NULL;
}


/** MARK: TY_(oldParseText)
 *  Parses the `option` and `textarea` tags.
 */
void* TY_(oldParseText)(TidyDocImpl* doc, Node *field, GetTokenMode mode)
{
    Lexer* lexer = doc->lexer;
    Node *node;

    lexer->insert = NULL;  /* defer implicit inline start tags */

    if ( nodeIsTEXTAREA(field) )
        mode = Preformatted;
    else
        mode = MixedContent;  /* kludge for font tags */

    while ((node = TY_(GetToken)(doc, mode)) != NULL)
    {
        if (node->tag == field->tag && node->type == EndTag)
        {
            TY_(FreeNode)( doc, node);
            field->closed = yes;
            TrimSpaces(doc, field);
            return NULL;
        }

        /* deal with comments etc. */
        if (InsertMisc(field, node))
            continue;

        if (TY_(nodeIsText)(node))
        {
            /* only called for 1st child */
            if (field->content == NULL && !(mode & Preformatted))
                TrimSpaces(doc, field);

            if (node->start >= node->end)
            {
                TY_(FreeNode)( doc, node);
                continue;
            }

            TY_(InsertNodeAtEnd)(field, node);
            continue;
        }

        /* for textarea should all cases of < and & be escaped? */

        /* discard inline tags e.g. font */
        if (   node->tag
            && node->tag->model & CM_INLINE
            && !(node->tag->model & CM_FIELD)) /* #487283 - fix by Lee Passey 25 Jan 02 */
        {
            TY_(Report)(doc, field, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        /* terminate element on other tags */
        if (!(field->tag->model & CM_OPT))
            TY_(Report)(doc, field, node, MISSING_ENDTAG_BEFORE);

        TY_(UngetToken)( doc );
        TrimSpaces(doc, field);
        return NULL;
    }

    if (!(field->tag->model & CM_OPT))
        TY_(Report)(doc, field, node, MISSING_ENDTAG_FOR);
    return NULL;
}


/** MARK: TY_(oldParseTitle)
 *  Parses the `title` tag.
 */
void* TY_(oldParseTitle)(TidyDocImpl* doc, Node *title, GetTokenMode ARG_UNUSED(mode))
{
    Node *node;
    while ((node = TY_(GetToken)(doc, MixedContent)) != NULL)
    {
        if (node->tag == title->tag && node->type == StartTag
            && cfgBool(doc, TidyCoerceEndTags) )
        {
            TY_(Report)(doc, title, node, COERCE_TO_ENDTAG);
            node->type = EndTag;
            TY_(UngetToken)( doc );
            continue;
        }
        else if (node->tag == title->tag && node->type == EndTag)
        {
            TY_(FreeNode)( doc, node);
            title->closed = yes;
            TrimSpaces(doc, title);
            return NULL;
        }

        if (TY_(nodeIsText)(node))
        {
            /* only called for 1st child */
            if (title->content == NULL)
                TrimInitialSpace(doc, title, node);

            if (node->start >= node->end)
            {
                TY_(FreeNode)( doc, node);
                continue;
            }

            TY_(InsertNodeAtEnd)(title, node);
            continue;
        }

        /* deal with comments etc. */
        if (InsertMisc(title, node))
            continue;

        /* discard unknown tags */
        if (node->tag == NULL)
        {
            TY_(Report)(doc, title, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        /* pushback unexpected tokens */
        TY_(Report)(doc, title, node, MISSING_ENDTAG_BEFORE);
        TY_(UngetToken)( doc );
        TrimSpaces(doc, title);
        return NULL;
    }

    TY_(Report)(doc, title, node, MISSING_ENDTAG_FOR);
    return NULL;
}


/** MARK: TY_(oldParseScript)
 *  Parses the `script` tag.
 *
 *  @todo This isn't quite right for CDATA content as it recognises tags
 *  within the content and parses them accordingly. This will unfortunately
 *  screw up scripts which include:
 *    < + letter
 *    < + !
 *    < + ?
 *    < + / + letter
 */
void* TY_(oldParseScript)(TidyDocImpl* doc, Node *script, GetTokenMode ARG_UNUSED(mode))
{
    Node *node;

    doc->lexer->parent = script;
    node = TY_(GetToken)(doc, CdataContent);
    doc->lexer->parent = NULL;

    if (node)
    {
        TY_(InsertNodeAtEnd)(script, node);
    }
    else
    {
        /* handle e.g. a document like "<script>" */
        TY_(Report)(doc, script, NULL, MISSING_ENDTAG_FOR);
        return NULL;
    }

    node = TY_(GetToken)(doc, IgnoreWhitespace);

    if (!(node && node->type == EndTag && node->tag &&
        node->tag->id == script->tag->id))
    {
        TY_(Report)(doc, script, node, MISSING_ENDTAG_FOR);

        if (node)
            TY_(UngetToken)(doc);
    }
    else
    {
        TY_(FreeNode)(doc, node);
    }
    return NULL;
}


/** MARK: TY_(oldParseHead)
 *  Parses the `head` tag.
 */
void* TY_(oldParseHead)(TidyDocImpl* doc, Node *head, GetTokenMode ARG_UNUSED(mode))
{
    Lexer* lexer = doc->lexer;
    Node *node;
    int HasTitle = 0;
    int HasBase = 0;

    DEBUG_LOG(SPRTF("Enter ParseHead...\n"));
    while ((node = TY_(GetToken)(doc, IgnoreWhitespace)) != NULL)
    {
        if (node->tag == head->tag && node->type == EndTag)
        {
            TY_(FreeNode)( doc, node);
            head->closed = yes;
            break;
        }

        /* find and discard multiple <head> elements */
        /* find and discard <html> in <head> elements */
        if ((node->tag == head->tag || nodeIsHTML(node)) && node->type == StartTag)
        {
            TY_(Report)(doc, head, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)(doc, node);
            continue;
        }

        if (TY_(nodeIsText)(node))
        {
            /*\ Issue #132 - avoid warning for missing body tag,
             *  if configured to --omit-otpional-tags yes
             *  Issue #314 - and if --show-body-only
            \*/
            if (!cfgBool( doc, TidyOmitOptionalTags ) &&
                !showingBodyOnly(doc) )
            {
                TY_(Report)(doc, head, node, TAG_NOT_ALLOWED_IN);
            }
            TY_(UngetToken)( doc );
            break;
        }

        if (node->type == ProcInsTag && node->element &&
            TY_(tmbstrcmp)(node->element, "xml-stylesheet") == 0)
        {
            TY_(Report)(doc, head, node, TAG_NOT_ALLOWED_IN);
            TY_(InsertNodeBeforeElement)(TY_(FindHTML)(doc), node);
            continue;
        }

        /* deal with comments etc. */
        if (InsertMisc(head, node))
            continue;

        if (node->type == DocTypeTag)
        {
            InsertDocType(doc, head, node);
            continue;
        }

        /* discard unknown tags */
        if (node->tag == NULL)
        {
            TY_(Report)(doc, head, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        /*
         if it doesn't belong in the head then
         treat as implicit end of head and deal
         with as part of the body
        */
        if (!(node->tag->model & CM_HEAD))
        {
            /* #545067 Implicit closing of head broken - warn only for XHTML input */
            if ( lexer->isvoyager )
                TY_(Report)(doc, head, node, TAG_NOT_ALLOWED_IN );
            TY_(UngetToken)( doc );
            break;
        }

        if (TY_(nodeIsElement)(node))
        {
            if ( nodeIsTITLE(node) )
            {
                ++HasTitle;

                if (HasTitle > 1)
                    TY_(Report)(doc, head, node,
                                     head ?
                                     TOO_MANY_ELEMENTS_IN : TOO_MANY_ELEMENTS);
            }
            else if ( nodeIsBASE(node) )
            {
                ++HasBase;

                if (HasBase > 1)
                    TY_(Report)(doc, head, node,
                                     head ?
                                     TOO_MANY_ELEMENTS_IN : TOO_MANY_ELEMENTS);
            }

            TY_(InsertNodeAtEnd)(head, node);
            ParseTag(doc, node, IgnoreWhitespace);
            continue;
        }

        /* discard unexpected text nodes and end tags */
        TY_(Report)(doc, head, node, DISCARDING_UNEXPECTED);
        TY_(FreeNode)( doc, node);
    }
    DEBUG_LOG(SPRTF("Exit ParseHead 1...\n"));
    return NULL;
}


/** MARK: TY_(oldParseBody)
 *  Parses the `body` tag.
 */
void* TY_(oldParseBody)(TidyDocImpl* doc, Node *body, GetTokenMode mode)
{
    Lexer* lexer = doc->lexer;
    Node *node;
    Bool checkstack, iswhitenode;

    mode = IgnoreWhitespace;
    checkstack = yes;

    TY_(BumpObject)( doc, body->parent );

    DEBUG_LOG(SPRTF("Enter ParseBody...\n"));
    while ((node = TY_(GetToken)(doc, mode)) != NULL)
    {
        /* find and discard multiple <body> elements */
        if (node->tag == body->tag && node->type == StartTag)
        {
            TY_(Report)(doc, body, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)(doc, node);
            continue;
        }

        /* #538536 Extra endtags not detected */
        if ( nodeIsHTML(node) )
        {
            if (TY_(nodeIsElement)(node) || lexer->seenEndHtml)
                TY_(Report)(doc, body, node, DISCARDING_UNEXPECTED);
            else
                lexer->seenEndHtml = 1;

            TY_(FreeNode)( doc, node);
            continue;
        }

        if ( lexer->seenEndBody &&
             ( node->type == StartTag ||
               node->type == EndTag   ||
               node->type == StartEndTag ) )
        {
            TY_(Report)(doc, body, node, CONTENT_AFTER_BODY );
        }

        if ( node->tag == body->tag && node->type == EndTag )
        {
            body->closed = yes;
            TrimSpaces(doc, body);
            TY_(FreeNode)( doc, node);
            lexer->seenEndBody = 1;
            mode = IgnoreWhitespace;

            if ( nodeIsNOFRAMES(body->parent) )
                break;

            continue;
        }

        if ( nodeIsNOFRAMES(node) )
        {
            if (node->type == StartTag)
            {
                TY_(InsertNodeAtEnd)(body, node);
                TY_(oldParseBlock)(doc, node, mode);
                continue;
            }

            if (node->type == EndTag && nodeIsNOFRAMES(body->parent) )
            {
                TrimSpaces(doc, body);
                TY_(UngetToken)( doc );
                break;
            }
        }

        if ( (nodeIsFRAME(node) || nodeIsFRAMESET(node))
             && nodeIsNOFRAMES(body->parent) )
        {
            TrimSpaces(doc, body);
            TY_(UngetToken)( doc );
            break;
        }

        iswhitenode = no;

        if ( TY_(nodeIsText)(node) &&
             node->end <= node->start + 1 &&
             lexer->lexbuf[node->start] == ' ' )
            iswhitenode = yes;

        /* deal with comments etc. */
        if (InsertMisc(body, node))
            continue;

        /* mixed content model permits text */
        if (TY_(nodeIsText)(node))
        {
            if (iswhitenode && mode == IgnoreWhitespace)
            {
                TY_(FreeNode)( doc, node);
                continue;
            }

            /* HTML 2 and HTML4 strict don't allow text here */
            TY_(ConstrainVersion)(doc, ~(VERS_HTML40_STRICT | VERS_HTML20));

            if (checkstack)
            {
                checkstack = no;

                if ( TY_(InlineDup)(doc, node) > 0 )
                    continue;
            }

            TY_(InsertNodeAtEnd)(body, node);
            mode = MixedContent;
            continue;
        }

        if (node->type == DocTypeTag)
        {
            InsertDocType(doc, body, node);
            continue;
        }
        /* discard unknown  and PARAM tags */
        if ( node->tag == NULL || nodeIsPARAM(node) )
        {
            TY_(Report)(doc, body, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        /*
          Netscape allows LI and DD directly in BODY
          We infer UL or DL respectively and use this
          Bool to exclude block-level elements so as
          to match Netscape's observed behaviour.
        */
        lexer->excludeBlocks = no;

        if (( nodeIsINPUT(node) ||
             (!TY_(nodeHasCM)(node, CM_BLOCK) && !TY_(nodeHasCM)(node, CM_INLINE))
           ) && !TY_(IsHTML5Mode)(doc) )
        {
            /* avoid this error message being issued twice */
            if (!(node->tag->model & CM_HEAD))
                TY_(Report)(doc, body, node, TAG_NOT_ALLOWED_IN);

            if (node->tag->model & CM_HTML)
            {
                /* copy body attributes if current body was inferred */
                if ( nodeIsBODY(node) && body->implicit
                     && body->attributes == NULL )
                {
                    body->attributes = node->attributes;
                    node->attributes = NULL;
                }

                TY_(FreeNode)( doc, node);
                continue;
            }

            if (node->tag->model & CM_HEAD)
            {
                MoveToHead(doc, body, node);
                continue;
            }

            if (node->tag->model & CM_LIST)
            {
                TY_(UngetToken)( doc );
                node = TY_(InferredTag)(doc, TidyTag_UL);
                AddClassNoIndent(doc, node);
                lexer->excludeBlocks = yes;
            }
            else if (node->tag->model & CM_DEFLIST)
            {
                TY_(UngetToken)( doc );
                node = TY_(InferredTag)(doc, TidyTag_DL);
                lexer->excludeBlocks = yes;
            }
            else if (node->tag->model & (CM_TABLE | CM_ROWGRP | CM_ROW))
            {
                /* http://tidy.sf.net/issue/2855621 */
                if (node->type != EndTag) {
                    TY_(UngetToken)( doc );
                    node = TY_(InferredTag)(doc, TidyTag_TABLE);
                }
                lexer->excludeBlocks = yes;
            }
            else if ( nodeIsINPUT(node) )
            {
                TY_(UngetToken)( doc );
                node = TY_(InferredTag)(doc, TidyTag_FORM);
                lexer->excludeBlocks = yes;
            }
            else
            {
                if ( !TY_(nodeHasCM)(node, CM_ROW | CM_FIELD) )
                {
                    TY_(UngetToken)( doc );
                    return NULL;
                }

                /* ignore </td> </th> <option> etc. */
                TY_(FreeNode)( doc, node );
                continue;
            }
        }

        if (node->type == EndTag)
        {
            if ( nodeIsBR(node) )
                node->type = StartTag;
            else if ( nodeIsP(node) )
            {
                node->type = StartEndTag;
                node->implicit = yes;
            }
            else if ( TY_(nodeHasCM)(node, CM_INLINE) )
                TY_(PopInline)( doc, node );
        }

        if (TY_(nodeIsElement)(node))
        {
            if (nodeIsMAIN(node))
            {
                /*\ Issue #166 - repeated <main> element
                 *  How to efficiently search for a previous main element?
                \*/
                if ( findNodeById(doc, TidyTag_MAIN) )
                {
                    doc->badForm |= flg_BadMain; /* this is an ERROR in format */
                    TY_(Report)(doc, body, node, DISCARDING_UNEXPECTED);
                    TY_(FreeNode)( doc, node);
                    continue;
                }
            }
            /* Issue #20 - merging from Ger Hobbelt fork put back CM_MIXED, which had been
               removed to fix this issue - reverting to fix 880221e
             */
            if ( TY_(nodeHasCM)(node, CM_INLINE) )
            {
                /* HTML4 strict doesn't allow inline content here */
                /* but HTML2 does allow img elements as children of body */
                if ( nodeIsIMG(node) )
                    TY_(ConstrainVersion)(doc, ~VERS_HTML40_STRICT);
                else
                    TY_(ConstrainVersion)(doc, ~(VERS_HTML40_STRICT|VERS_HTML20));

                if (checkstack && !node->implicit)
                {
                    checkstack = no;

                    if ( TY_(InlineDup)(doc, node) > 0 )
                        continue;
                }

                mode = MixedContent;
            }
            else
            {
                checkstack = yes;
                mode = IgnoreWhitespace;
            }

            if (node->implicit)
                TY_(Report)(doc, body, node, INSERTING_TAG);

            TY_(InsertNodeAtEnd)(body, node);
            ParseTag(doc, node, mode);
            continue;
        }

        /* discard unexpected tags */
        TY_(Report)(doc, body, node, DISCARDING_UNEXPECTED);
        TY_(FreeNode)( doc, node);
    }
    DEBUG_LOG(SPRTF("Exit ParseBody 1...\n"));
    return NULL;
}


/** MARK: TY_(oldParseNoFrames)
 *  Parses the `noframes` tag.
 */
void* TY_(oldParseNoFrames)(TidyDocImpl* doc, Node *noframes, GetTokenMode mode)
{
    Lexer* lexer = doc->lexer;
    Node *node;

    if ( cfg(doc, TidyAccessibilityCheckLevel) == 0 )
    {
        doc->badAccess |=  BA_USING_NOFRAMES;
    }
    mode = IgnoreWhitespace;

    while ( (node = TY_(GetToken)(doc, mode)) != NULL )
    {
        if ( node->tag == noframes->tag && node->type == EndTag )
        {
            TY_(FreeNode)( doc, node);
            noframes->closed = yes;
            TrimSpaces(doc, noframes);
            return NULL;
        }

        if ( nodeIsFRAME(node) || nodeIsFRAMESET(node) )
        {
            TrimSpaces(doc, noframes);
            if (node->type == EndTag)
            {
                TY_(Report)(doc, noframes, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);       /* Throw it away */
            }
            else
            {
                TY_(Report)(doc, noframes, node, MISSING_ENDTAG_BEFORE);
                TY_(UngetToken)( doc );
            }
            return NULL;
        }

        if ( nodeIsHTML(node) )
        {
            if (TY_(nodeIsElement)(node))
                TY_(Report)(doc, noframes, node, DISCARDING_UNEXPECTED);

            TY_(FreeNode)( doc, node);
            continue;
        }

        /* deal with comments etc. */
        if (InsertMisc(noframes, node))
            continue;

        if ( nodeIsBODY(node) && node->type == StartTag )
        {
            Bool seen_body = lexer->seenEndBody;
            TY_(InsertNodeAtEnd)(noframes, node);
            ParseTag(doc, node, IgnoreWhitespace /*MixedContent*/);

            /* fix for bug http://tidy.sf.net/bug/887259 */
            if (seen_body && TY_(FindBody)(doc) != node)
            {
                TY_(CoerceNode)(doc, node, TidyTag_DIV, no, no);
                MoveNodeToBody(doc, node);
            }
            continue;
        }

        /* implicit body element inferred */
        if (TY_(nodeIsText)(node) || (node->tag && node->type != EndTag))
        {
            Node *body = TY_(FindBody)( doc );
            if ( body || lexer->seenEndBody )
            {
                if ( body == NULL )
                {
                    TY_(Report)(doc, noframes, node, DISCARDING_UNEXPECTED);
                    TY_(FreeNode)( doc, node);
                    continue;
                }
                if ( TY_(nodeIsText)(node) )
                {
                    TY_(UngetToken)( doc );
                    node = TY_(InferredTag)(doc, TidyTag_P);
                    TY_(Report)(doc, noframes, node, CONTENT_AFTER_BODY );
                }
                TY_(InsertNodeAtEnd)( body, node );
            }
            else
            {
                TY_(UngetToken)( doc );
                node = TY_(InferredTag)(doc, TidyTag_BODY);
                if ( cfgBool(doc, TidyXmlOut) )
                    TY_(Report)(doc, noframes, node, INSERTING_TAG);
                TY_(InsertNodeAtEnd)( noframes, node );
            }

            ParseTag( doc, node, IgnoreWhitespace /*MixedContent*/ );
            continue;
        }

        /* discard unexpected end tags */
        TY_(Report)(doc, noframes, node, DISCARDING_UNEXPECTED);
        TY_(FreeNode)( doc, node);
    }

    TY_(Report)(doc, noframes, node, MISSING_ENDTAG_FOR);
    return NULL;
}


/** MARK: TY_(oldParseFrameSet)
 *  Parses the `frameset` tag.
 */
void* TY_(oldParseFrameSet)(TidyDocImpl* doc, Node *frameset, GetTokenMode ARG_UNUSED(mode))
{
    Lexer* lexer = doc->lexer;
    Node *node;

    if ( cfg(doc, TidyAccessibilityCheckLevel) == 0 )
    {
        doc->badAccess |= BA_USING_FRAMES;
    }

    while ((node = TY_(GetToken)(doc, IgnoreWhitespace)) != NULL)
    {
        if (node->tag == frameset->tag && node->type == EndTag)
        {
            TY_(FreeNode)( doc, node);
            frameset->closed = yes;
            TrimSpaces(doc, frameset);
            return NULL;
        }

        /* deal with comments etc. */
        if (InsertMisc(frameset, node))
            continue;

        if (node->tag == NULL)
        {
            TY_(Report)(doc, frameset, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        if (TY_(nodeIsElement)(node))
        {
            if (node->tag && node->tag->model & CM_HEAD)
            {
                MoveToHead(doc, frameset, node);
                continue;
            }
        }

        if ( nodeIsBODY(node) )
        {
            TY_(UngetToken)( doc );
            node = TY_(InferredTag)(doc, TidyTag_NOFRAMES);
            TY_(Report)(doc, frameset, node, INSERTING_TAG);
        }

        if (node->type == StartTag && (node->tag && node->tag->model & CM_FRAMES))
        {
            TY_(InsertNodeAtEnd)(frameset, node);
            lexer->excludeBlocks = no;
            ParseTag(doc, node, MixedContent);
            continue;
        }
        else if (node->type == StartEndTag && (node->tag && node->tag->model & CM_FRAMES))
        {
            TY_(InsertNodeAtEnd)(frameset, node);
            continue;
        }

        /* discard unexpected tags */
        /* WAI [6.5.1.4] link is being discarded outside of NOFRAME */
        if ( nodeIsA(node) )
           doc->badAccess |= BA_INVALID_LINK_NOFRAMES;

        TY_(Report)(doc, frameset, node, DISCARDING_UNEXPECTED);
        TY_(FreeNode)( doc, node);
    }

    TY_(Report)(doc, frameset, node, MISSING_ENDTAG_FOR);
    return NULL;
}


/***************************************************************************//*
 ** MARK: - Parsers
 ***************************************************************************/


/** MARK: TY_(ParseHTML)
 *  Parses the `html` tag. At this point, other root-level stuff (doctype,
 *  comments) are already set up, and the bulk of the parsing can be
 *  conducted from here as our nexus.
 */
Node* TY_(ParseHTML)( TidyDocImpl *doc, Node *html, GetTokenMode mode, Bool popStack )
{
#if defined(ENABLE_DEBUG_LOG)
    static int parser_depth = 0;
    static int parser_count = 0;
#endif
    Node *node = NULL;
    Node *head = NULL;
    Node *frameset = NULL;
    Node *noframes = NULL;
    Bool keepToken = no;
    parserState state = STATE_INITIAL;

#if defined(ENABLE_DEBUG_LOG)
    parser_depth++;
    parser_count++;
    DEBUG_LOG(SPRTF("***Entering ParseHTML, count: %d, depth %d\n", parser_count, parser_depth));
#endif

    TY_(SetOptionBool)( doc, TidyXmlTags, no );

    /*
     If we're re-entering, then we need to setup from a previous state,
     instead of starting fresh. We can pull what we need from the document's
     stack.
     */
    if ( popStack )
    {
        TidyParserMemory memory = popMemory( doc );
        node = memory.reentry_node;
        mode = memory.reentry_mode;
        state = memory.reentry_state;
        html = memory.original_node;
        keepToken = node != NULL;
    }

    /*
     This main loop pulls tokens from the lexer until we're out of tokens,
     or until there's no more work to do.
     */
    while ( state != STATE_COMPLETE )
    {
        /*
         We don't want to get the next token unless we're
         done with this one. Using this flag is much quicker
         than using `UngetToken()` every time we want to keep
         the token.
         */
        if ( !keepToken )
            node = TY_(GetToken)( doc, IgnoreWhitespace );
        keepToken = no;

        switch ( state )
        {
            /**************************************************************
             This case is all about finding a head tag and dealing with
             cases were we don't, so that we can move on to parsing a head
             tag.
             **************************************************************/
            case STATE_INITIAL:
            {
                /*
                 The only way we can possibly be here is if the lexer
                 had nothing to give us. Thus we'll create our own
                 head, and set the signal to start parsing it.
                 */
                if (node == NULL)
                {
                    node = TY_(InferredTag)(doc, TidyTag_HEAD);
                    state = STATE_PARSE_HEAD;
                    keepToken = yes;
                    continue;
                }

                /* We found exactly what we expected: head. */
                if ( nodeIsHEAD(node) )
                {
                    state = STATE_PARSE_HEAD;
                    keepToken = yes;
                    continue;
                }

                /* We did not expect to find an html closing tag here! */
                if (html && (node->tag == html->tag) && (node->type == EndTag))
                {
                    TY_(Report)(doc, html, node, DISCARDING_UNEXPECTED);
                    TY_(FreeNode)( doc, node);
                    continue;
                }

                /* Find and discard multiple <html> elements. */
                if (html && (node->tag == html->tag) && (node->type == StartTag))
                {
                    TY_(Report)(doc, html, node, DISCARDING_UNEXPECTED);
                    TY_(FreeNode)(doc, node);
                    continue;
                }

                /* Deal with comments etc. */
                if (InsertMisc(html, node))
                    continue;

                /* At this point, we didn't find a head tag, so put the
                 token back and create our own head tag, so we can
                 move on.
                 */
                TY_(UngetToken)( doc );
                node = TY_(InferredTag)(doc, TidyTag_HEAD);
                state = STATE_PARSE_HEAD;
                keepToken = yes;
                continue;
            } break;


            /**************************************************************
             This case determines whether we're dealing with body or
             frameset + noframes, and sets things up accordingly.
             **************************************************************/
            case STATE_PRE_BODY:
            {
                if (node == NULL )
                {
                    if (frameset == NULL) /* Implied body. */
                    {
                        node = TY_(InferredTag)(doc, TidyTag_BODY);
                        state = STATE_PARSE_BODY;
                        keepToken = yes;
                    } else {
                        state = STATE_COMPLETE;
                    }

                    continue;
                }

                /* Robustly handle html tags. */
                if (node->tag == html->tag)
                {
                    if (node->type != StartTag && frameset == NULL)
                        TY_(Report)(doc, html, node, DISCARDING_UNEXPECTED);

                    TY_(FreeNode)( doc, node);
                    continue;
                }

                /* Deal with comments etc. */
                if (InsertMisc(html, node))
                    continue;

                /* If frameset document, coerce <body> to <noframes> */
                if ( nodeIsBODY(node) )
                {
                    if (node->type != StartTag)
                    {
                        TY_(Report)(doc, html, node, DISCARDING_UNEXPECTED);
                        TY_(FreeNode)( doc, node);
                        continue;
                    }

                    if ( cfg(doc, TidyAccessibilityCheckLevel) == 0 )
                    {
                        if (frameset != NULL)
                        {
                            TY_(UngetToken)( doc );

                            if (noframes == NULL)
                            {
                                noframes = TY_(InferredTag)(doc, TidyTag_NOFRAMES);
                                TY_(InsertNodeAtEnd)(frameset, noframes);
                                TY_(Report)(doc, html, noframes, INSERTING_TAG);
                            }
                            else
                            {
                                if (noframes->type == StartEndTag)
                                    noframes->type = StartTag;
                            }

                            state = STATE_PARSE_NOFRAMES;
                            keepToken = yes;
                            continue;
                        }
                    }

                    TY_(ConstrainVersion)(doc, ~VERS_FRAMESET);
                    state = STATE_PARSE_BODY;
                    keepToken = yes;
                    continue;
                }

                /* Flag an error if we see more than one frameset. */
                if ( nodeIsFRAMESET(node) )
                {
                    if (node->type != StartTag)
                    {
                        TY_(Report)(doc, html, node, DISCARDING_UNEXPECTED);
                        TY_(FreeNode)( doc, node);
                        continue;
                    }

                    if (frameset != NULL)
                        TY_(Report)(doc, html, node, DUPLICATE_FRAMESET);
                    else
                        frameset = node;

                    state = STATE_PARSE_FRAMESET;
                    keepToken = yes;
                    continue;
                }

                /* If not a frameset document coerce <noframes> to <body>. */
                if ( nodeIsNOFRAMES(node) )
                {
                    if (node->type != StartTag)
                    {
                        TY_(Report)(doc, html, node, DISCARDING_UNEXPECTED);
                        TY_(FreeNode)( doc, node);
                        continue;
                    }

                    if (frameset == NULL)
                    {
                        TY_(Report)(doc, html, node, DISCARDING_UNEXPECTED);
                        TY_(FreeNode)( doc, node);
                        node = TY_(InferredTag)(doc, TidyTag_BODY);
                        state = STATE_PARSE_BODY;
                        keepToken = yes;
                        continue;
                    }

                    if (noframes == NULL)
                    {
                        noframes = node;
                        TY_(InsertNodeAtEnd)(frameset, noframes);
                        state = STATE_PARSE_NOFRAMES;
                        keepToken = yes;
                    }
                    else
                    {
                        TY_(FreeNode)( doc, node);
                    }

                    continue;
                }

                /* Deal with some other element that we're not expecting. */
                if (TY_(nodeIsElement)(node))
                {
                    if (node->tag && node->tag->model & CM_HEAD)
                    {
                        MoveToHead(doc, html, node);
                        continue;
                    }

                    /* Discard illegal frame element following a frameset. */
                    if ( frameset != NULL && nodeIsFRAME(node) )
                    {
                        TY_(Report)(doc, html, node, DISCARDING_UNEXPECTED);
                        TY_(FreeNode)(doc, node);
                        continue;
                    }
                }

                TY_(UngetToken)( doc );

                /* Insert other content into noframes element. */
                if (frameset)
                {
                    if (noframes == NULL)
                    {
                        noframes = TY_(InferredTag)(doc, TidyTag_NOFRAMES);
                        TY_(InsertNodeAtEnd)(frameset, noframes);
                    }
                    else
                    {
                        TY_(Report)(doc, html, node, NOFRAMES_CONTENT);
                        if (noframes->type == StartEndTag)
                            noframes->type = StartTag;
                    }

                    TY_(ConstrainVersion)(doc, VERS_FRAMESET);
                    state = STATE_PARSE_NOFRAMES;
                    keepToken = yes;
                    continue;
                }

                node = TY_(InferredTag)(doc, TidyTag_BODY);

                /* Issue #132 - disable inserting BODY tag warning
                 BUT only if NOT --show-body-only yes */
                if (!showingBodyOnly(doc))
                    TY_(Report)(doc, html, node, INSERTING_TAG );

                TY_(ConstrainVersion)(doc, ~VERS_FRAMESET);
                state = STATE_PARSE_BODY;
                keepToken = yes;
                continue;
            } break;


            /**************************************************************
             In this case, we're ready to parse the head, and move on to
             look for the body or body alternative.
             **************************************************************/
            case STATE_PARSE_HEAD:
            {
                TidyParserMemory memory;
                memory.identity = TY_(ParseHTML);
                memory.mode = mode;
                memory.original_node = html;
                memory.reentry_node = node;
                memory.reentry_mode = mode;
                memory.reentry_state = STATE_PARSE_HEAD_DONE;
                TY_(InsertNodeAtEnd)(html, node);
                pushMemory( doc, memory );
#if defined(ENABLE_DEBUG_LOG)
                parser_depth--;
                DEBUG_LOG(SPRTF("***Exiting ParseHTML, count: %d, depth %d\n", parser_count, parser_depth));
#endif
                return node;
            } break;

            case STATE_PARSE_HEAD_DONE:
            {
                head = node;
                state = STATE_PRE_BODY;
            } break;


            /**************************************************************
             In this case, we can finally parse a body.
             **************************************************************/
            case STATE_PARSE_BODY:
            {
                TidyParserMemory memory;
                memory.identity = NULL; /* we don't need to reenter */
                memory.mode = mode;
                memory.original_node = html;
                memory.reentry_node = NULL;
                memory.reentry_mode = mode;
                memory.reentry_state = STATE_COMPLETE;
                TY_(InsertNodeAtEnd)(html, node);
                pushMemory( doc, memory );
#if defined(ENABLE_DEBUG_LOG)
                parser_depth--;
                DEBUG_LOG(SPRTF("***Exiting ParseHTML, count: %d, depth %d\n", parser_count, parser_depth));
#endif
                return node;
            } break;


            /**************************************************************
             In this case, we will parse noframes. If necessary, the
             node is already inserted in the proper spot.
             **************************************************************/
            case STATE_PARSE_NOFRAMES:
            {
                TidyParserMemory memory;
                memory.identity = TY_(ParseHTML);
                memory.mode = mode;
                memory.original_node = html;
                memory.reentry_node = frameset;
                memory.reentry_mode = mode;
                memory.reentry_state = STATE_PARSE_NOFRAMES_DONE;
                pushMemory( doc, memory );
#if defined(ENABLE_DEBUG_LOG)
                parser_depth--;
                DEBUG_LOG(SPRTF("***Exiting ParseHTML, count: %d, depth %d\n", parser_count, parser_depth));
#endif
                return noframes;
            } break;

            case STATE_PARSE_NOFRAMES_DONE:
            {
                frameset = node;
                state = STATE_PRE_BODY;
            } break;


            /**************************************************************
             In this case, we parse the frameset, and look for noframes
             content to merge later if necessary.
             **************************************************************/
            case STATE_PARSE_FRAMESET:
            {
                TidyParserMemory memory;
                memory.identity = TY_(ParseHTML);
                memory.mode = mode;
                memory.original_node = html;
                memory.reentry_node = frameset;
                memory.reentry_mode = mode;
                memory.reentry_state = STATE_PARSE_FRAMESET_DONE;
                TY_(InsertNodeAtEnd)(html, node);
                pushMemory( doc, memory );
#if defined(ENABLE_DEBUG_LOG)
                parser_depth--;
                DEBUG_LOG(SPRTF("***Exiting ParseHTML, count: %d, depth %d\n", parser_count, parser_depth));
#endif
                return node;
            } break;

            case STATE_PARSE_FRAMESET_DONE:
            {
                frameset = node;
                /* See if it includes a noframes element so that
                 we can merge subsequent noframes elements.
                 */
                for (node = frameset->content; node; node = node->next)
                {
                    if ( nodeIsNOFRAMES(node) )
                        noframes = node;
                }
                state = STATE_PRE_BODY;
            } break;


            /**************************************************************
             We really shouldn't get here, but if we do, finish nicely.
             **************************************************************/
            default:
            {
                state = STATE_COMPLETE;
            }
        } /* switch */
    } /* while */

#if defined(ENABLE_DEBUG_LOG)
    parser_depth--;
    DEBUG_LOG(SPRTF("***Exiting ParseHTML, count: %d, depth %d\n", parser_count, parser_depth));
#endif
    return NULL;
}


/** MARK: TY_(ParseBlock)
 *  `element` is a node created by the lexer upon seeing the start tag, or
 *  by the parser when the start tag is inferred
 */
Node* TY_(ParseBlock)( TidyDocImpl* doc, Node *element, GetTokenMode mode, Bool popStack )
{
    TY_(oldParseBlock)( doc, element, mode );
    return NULL;
    
#if 0
#if defined(ENABLE_DEBUG_LOG)
    static int in_parse_block = 0;
    static int parse_block_cnt = 0;
#endif
    Lexer* lexer = doc->lexer;
    Node *node = NULL;
    Bool checkstack = yes;
    uint istackbase = 0;
    Bool keepToken = no;
    parserState state = STATE_INITIAL;

#if defined(ENABLE_DEBUG_LOG)
    in_parse_block++;
    parse_block_cnt++;
    SPRTF("Entering ParseBlock %d... %d %s\n",in_parse_block,parse_block_cnt,
          ((element && element->element) ? element->element : ""));
#endif

    /*
     If we're re-entering, then we need to setup from a previous state,
     instead of starting fresh. We can pull what we need from the document's
     stack.
     */
    if ( popStack )
    {
        TidyParserMemory memory = popMemory( doc );
        node = memory.reentry_node;
        mode = memory.reentry_mode;
        state = memory.reentry_state;
        element = memory.original_node;
        keepToken = node != NULL;
    }


    if ( element->tag->model & CM_EMPTY ) {
#if defined(ENABLE_DEBUG_LOG)
        in_parse_block--;
        SPRTF("Exit ParseBlockL 1 %d...\n",in_parse_block);
#endif
        return NULL;
    }

    if ( nodeIsFORM(element) && DescendantOf(element, TidyTag_FORM) )
        TY_(Report)(doc, element, NULL, ILLEGAL_NESTING );

    /*
     InlineDup() asks the lexer to insert inline emphasis tags
     currently pushed on the istack, but take care to avoid
     propagating inline emphasis inside OBJECT or APPLET.
     For these elements a fresh inline stack context is created
     and disposed of upon reaching the end of the element.
     They thus behave like table cells in this respect.
     */
    if (element->tag->model & CM_OBJECT)
    {
        istackbase = lexer->istackbase;
        lexer->istackbase = lexer->istacksize;
    }

    if (!(element->tag->model & CM_MIXED))
        TY_(InlineDup)( doc, NULL );

    /*\
     *  Issue #212 - If it is likely that it may be necessary
     *  to move a leading space into a text node before this
     *  element, then keep the mode MixedContent to keep any
     *  leading space
     \*/
    if ( !(element->tag->model & CM_INLINE) || (element->tag->model & CM_FIELD ) )
    {
        mode = IgnoreWhitespace;
    }
    else if (mode == IgnoreWhitespace)
    {
        /* Issue #212 - Further fix in case ParseBlock() is called with 'IgnoreWhitespace'
         when such a leading space may need to be inserted before this element to
         preverve the browser view */
        mode = MixedContent;
    }

    while ( state != STATE_COMPLETE )
    {
        if ( !keepToken )
            node = TY_(GetToken)(doc, mode /*MixedContent*/);
        keepToken = no;

        if ( !node )
            state = STATE_COMPLETE;

        switch ( state )
        {
            case STATE_INITIAL:
            {
                /* end tag for this element */
                if (node->type == EndTag && node->tag &&
                    (node->tag == element->tag || element->was == node->tag))
                {
                    TY_(FreeNode)( doc, node );

                    if (element->tag->model & CM_OBJECT)
                    {
                        /* pop inline stack */
                        while (lexer->istacksize > lexer->istackbase)
                            TY_(PopInline)( doc, NULL );
                        lexer->istackbase = istackbase;
                    }

                    element->closed = yes;
                    TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
in_parse_block--;
SPRTF("Exit ParseBlock 2 %d...\n",in_parse_block);
#endif
                    return NULL;
                }

                if ( nodeIsHTML(node) || nodeIsHEAD(node) || nodeIsBODY(node) )
                {
                    if ( TY_(nodeIsElement)(node) )
                        TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                    TY_(FreeNode)( doc, node );
                    continue;
                }


                if (node->type == EndTag)
                {
                    if (node->tag == NULL)
                    {
                        TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                        TY_(FreeNode)( doc, node );
                        continue;
                    }
                    else if ( nodeIsBR(node) )
                        node->type = StartTag;
                    else if ( nodeIsP(node) )
                    {
                        /* Cannot have a block inside a paragraph, so no checking
                         for an ancestor is necessary -- but we _can_ have
                         paragraphs inside a block, so change it to an implicit
                         empty paragraph, to be dealt with according to the user's
                         options
                         */
                        node->type = StartEndTag;
                        node->implicit = yes;
                    }
                    else if (DescendantOf( element, node->tag->id ))
                    {
                        /*
                         if this is the end tag for an ancestor element
                         then infer end tag for this element
                         */
                        TY_(UngetToken)( doc );
                        state = STATE_COMPLETE;
                        continue;
                    }
                    else
                    {
                        /* special case </tr> etc. for stuff moved in front of table */
                        if ( lexer->exiled
                            && (TY_(nodeHasCM)(node, CM_TABLE) || nodeIsTABLE(node)) )
                        {
                            TY_(UngetToken)( doc );
                            TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
in_parse_block--;
SPRTF("Exit ParseBlock 2 %d...\n",in_parse_block);
#endif
                            return NULL;
                        }
                    }
                }

                /* mixed content model permits text */
                if (TY_(nodeIsText)(node))
                {
                    if ( checkstack )
                    {
                        checkstack = no;
                        if (!(element->tag->model & CM_MIXED))
                        {
                            if ( TY_(InlineDup)(doc, node) > 0 )
                                continue;
                        }
                    }

                    TY_(InsertNodeAtEnd)(element, node);
                    mode = MixedContent;

                    /*
                     HTML4 strict doesn't allow mixed content for
                     elements with %block; as their content model
                     */
                    /*
                     But only body, map, blockquote, form and
                     noscript have content model %block;
                     */
                    if ( nodeIsBODY(element)       ||
                        nodeIsMAP(element)        ||
                        nodeIsBLOCKQUOTE(element) ||
                        nodeIsFORM(element)       ||
                        nodeIsNOSCRIPT(element) )
                        TY_(ConstrainVersion)( doc, ~VERS_HTML40_STRICT );
                    continue;
                }

                if ( InsertMisc(element, node) )
                    continue;

                /* allow PARAM elements? */
                if ( nodeIsPARAM(node) )
                {
                    if ( TY_(nodeHasCM)(element, CM_PARAM) && TY_(nodeIsElement)(node) )
                    {
                        TY_(InsertNodeAtEnd)(element, node);
                        continue;
                    }

                    /* otherwise discard it */
                    TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                    TY_(FreeNode)( doc, node );
                    continue;
                }

                /* allow AREA elements? */
                if ( nodeIsAREA(node) )
                {
                    if ( nodeIsMAP(element) && TY_(nodeIsElement)(node) )
                    {
                        TY_(InsertNodeAtEnd)(element, node);
                        continue;
                    }

                    /* otherwise discard it */
                    TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                    TY_(FreeNode)( doc, node );
                    continue;
                }

                /* ignore unknown start/end tags */
                if ( node->tag == NULL )
                {
                    TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                    TY_(FreeNode)( doc, node );
                    continue;
                }

                /*
                 Allow CM_INLINE elements here.

                 Allow CM_BLOCK elements here unless
                 lexer->excludeBlocks is yes.

                 LI and DD are special cased.

                 Otherwise infer end tag for this element.
                 */

                if ( !TY_(nodeHasCM)(node, CM_INLINE) )
                {
                    if ( !TY_(nodeIsElement)(node) )
                    {
                        if ( nodeIsFORM(node) )
                            BadForm( doc );

                        TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                        TY_(FreeNode)( doc, node );
                        continue;
                    }

                    /* #427671 - Fix by Randy Waki - 10 Aug 00 */
                    /*
                     If an LI contains an illegal FRAME, FRAMESET, OPTGROUP, or OPTION
                     start tag, discard the start tag and let the subsequent content get
                     parsed as content of the enclosing LI.  This seems to mimic IE and
                     Netscape, and avoids an infinite loop: without this check,
                     ParseBlock (which is parsing the LI's content) and ParseList (which
                     is parsing the LI's parent's content) repeatedly defer to each
                     other to parse the illegal start tag, each time inferring a missing
                     </li> or <li> respectively.

                     NOTE: This check is a bit fragile.  It specifically checks for the
                     four tags that happen to weave their way through the current series
                     of tests performed by ParseBlock and ParseList to trigger the
                     infinite loop.
                     */
                    if ( nodeIsLI(element) )
                    {
                        if ( nodeIsFRAME(node)    ||
                            nodeIsFRAMESET(node) ||
                            nodeIsOPTGROUP(node) ||
                            nodeIsOPTION(node) )
                        {
                            TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                            TY_(FreeNode)( doc, node );  /* DSR - 27Apr02 avoid memory leak */
                            continue;
                        }
                    }

                    if ( nodeIsTD(element) || nodeIsTH(element) )
                    {
                        /* if parent is a table cell, avoid inferring the end of the cell */

                        if ( TY_(nodeHasCM)(node, CM_HEAD) )
                        {
                            MoveToHead( doc, element, node );
                            continue;
                        }

                        if ( TY_(nodeHasCM)(node, CM_LIST) )
                        {
                            TY_(UngetToken)( doc );
                            node = TY_(InferredTag)(doc, TidyTag_UL);
                            AddClassNoIndent(doc, node);
                            lexer->excludeBlocks = yes;
                        }
                        else if ( TY_(nodeHasCM)(node, CM_DEFLIST) )
                        {
                            TY_(UngetToken)( doc );
                            node = TY_(InferredTag)(doc, TidyTag_DL);
                            lexer->excludeBlocks = yes;
                        }

                        /* infer end of current table cell */
                        if ( !TY_(nodeHasCM)(node, CM_BLOCK) )
                        {
                            TY_(UngetToken)( doc );
                            TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
in_parse_block--;
SPRTF("Exit ParseBlock 3 %d...\n",in_parse_block);
#endif
                            return NULL;
                        }
                    }
                    else if ( TY_(nodeHasCM)(node, CM_BLOCK) )
                    {
                        if ( lexer->excludeBlocks )
                        {
                            if ( !TY_(nodeHasCM)(element, CM_OPT) )
                                TY_(Report)(doc, element, node, MISSING_ENDTAG_BEFORE );

                            TY_(UngetToken)( doc );

                            if ( TY_(nodeHasCM)(element, CM_OBJECT) )
                                lexer->istackbase = istackbase;

                            TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
in_parse_block--;
SPRTF("Exit ParseBlock 4 %d...\n",in_parse_block);
#endif
                            return NULL;
                        }
                    }
                    else /* things like list items */
                    {
                        if (node->tag->model & CM_HEAD)
                        {
                            MoveToHead( doc, element, node );
                            continue;
                        }

                        /*
                         special case where a form start tag
                         occurs in a tr and is followed by td or th
                         */

                        if ( nodeIsFORM(element) &&
                            nodeIsTD(element->parent) &&
                            element->parent->implicit )
                        {
                            if ( nodeIsTD(node) )
                            {
                                TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                                TY_(FreeNode)( doc, node );
                                continue;
                            }

                            if ( nodeIsTH(node) )
                            {
                                TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                                TY_(FreeNode)( doc, node );
                                node = element->parent;
                                TidyDocFree(doc, node->element);
                                node->element = TY_(tmbstrdup)(doc->allocator, "th");
                                node->tag = TY_(LookupTagDef)( TidyTag_TH );
                                continue;
                            }
                        }

                        if ( !TY_(nodeHasCM)(element, CM_OPT) && !element->implicit )
                            TY_(Report)(doc, element, node, MISSING_ENDTAG_BEFORE );

                        /* #521, warn on missing optional end-tags if not omitting them. */
                        if ( cfgBool( doc, TidyOmitOptionalTags ) == no && TY_(nodeHasCM)(element, CM_OPT) )
                            TY_(Report)(doc, element, node, MISSING_ENDTAG_OPTIONAL );


                        TY_(UngetToken)( doc );

                        if ( TY_(nodeHasCM)(node, CM_LIST) )
                        {
                            if ( element->parent && element->parent->tag &&
                                element->parent->tag->parser == TY_(ParseList) )
                            {
                                TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
in_parse_block--;
SPRTF("Exit ParseBlock 5 %d...\n",in_parse_block);
#endif
                                return NULL;
                            }

                            node = TY_(InferredTag)(doc, TidyTag_UL);
                            AddClassNoIndent(doc, node);
                        }
                        else if ( TY_(nodeHasCM)(node, CM_DEFLIST) )
                        {
                            if ( nodeIsDL(element->parent) )
                            {
                                TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
in_parse_block--;
SPRTF("Exit ParseBlock 6 %d...\n",in_parse_block);
#endif
                                return NULL;
                            }

                            node = TY_(InferredTag)(doc, TidyTag_DL);
                        }
                        else if ( TY_(nodeHasCM)(node, CM_TABLE) || TY_(nodeHasCM)(node, CM_ROW) )
                        {
                            /* http://tidy.sf.net/issue/1316307 */
                            /* In exiled mode, return so table processing can
                             continue. */
                            if (lexer->exiled) {
#if defined(ENABLE_DEBUG_LOG)
in_parse_block--;
SPRTF("Exit ParseBlock 7 %d...\n",in_parse_block);
#endif
                                return NULL;
                            }
                            node = TY_(InferredTag)(doc, TidyTag_TABLE);
                        }
                        else if ( TY_(nodeHasCM)(element, CM_OBJECT) )
                        {
                            /* pop inline stack */
                            while ( lexer->istacksize > lexer->istackbase )
                                TY_(PopInline)( doc, NULL );
                            lexer->istackbase = istackbase;
                            TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
in_parse_block--;
SPRTF("Exit ParseBlock 8 %d...\n",in_parse_block);
#endif
                            return NULL;

                        }
                        else
                        {
                            TrimSpaces( doc, element );
#if defined(ENABLE_DEBUG_LOG)
in_parse_block--;
SPRTF("Exit ParseBlock 9 %d...\n",in_parse_block);
#endif
                            return NULL;
                        }
                    }
                }

                /*\
                 *  Issue #307 - an <A> tag to ends any open <A> element
                 *  Like #427827 - fixed by Randy Waki and Bjoern Hoehrmann 23 Aug 00
                 *  in ParseInline(), fix copied HERE to ParseBlock()
                 *  href: http://www.w3.org/TR/html-markup/a.html
                 *  The interactive element a must not appear as a descendant of the a element.
                 \*/
                if ( nodeIsA(node) && !node->implicit &&
                    (nodeIsA(element) || DescendantOf(element, TidyTag_A)) )
                {
                    if (node->type != EndTag && node->attributes == NULL
                        && cfgBool(doc, TidyCoerceEndTags) )
                    {
                        node->type = EndTag;
                        TY_(Report)(doc, element, node, COERCE_TO_ENDTAG);
                        TY_(UngetToken)( doc );
                        continue;
                    }

                    if (nodeIsA(element))
                    {
                        TY_(Report)(doc, element, node, MISSING_ENDTAG_BEFORE);
                        TY_(UngetToken)( doc );
                    }
                    else
                    {
                        /* Issue #597 - if we not 'UngetToken' then it is being discarded.
                         Add message, and 'FreeNode' - thanks @ralfjunker */
                        TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED);
                        TY_(FreeNode)(doc, node);
                    }

                    if (!(mode & Preformatted))
                        TrimSpaces(doc, element);

#if defined(ENABLE_DEBUG_LOG)
in_parse_block--;
SPRTF("Exit ParseBlock 9b %d...\n",in_parse_block);
#endif
                    return NULL;
                }

                /* parse known element */
                if (TY_(nodeIsElement)(node))
                {
                    if (node->tag->model & CM_INLINE)
                    {
                        if (checkstack && !node->implicit)
                        {
                            checkstack = no;

                            if (!(element->tag->model & CM_MIXED)) /* #431731 - fix by Randy Waki 25 Dec 00 */
                            {
                                if ( TY_(InlineDup)(doc, node) > 0 )
                                    continue;
                            }
                        }

                        mode = MixedContent;
                    }
                    else
                    {
                        checkstack = yes;
                        mode = IgnoreWhitespace;
                    }

                    /* trim white space before <br> */
                    if ( nodeIsBR(node) )
                        TrimSpaces( doc, element );

                    TY_(InsertNodeAtEnd)(element, node);

                    if (node->implicit)
                        TY_(Report)(doc, element, node, INSERTING_TAG );

                    /* Issue #212 - WHY is this hard coded to 'IgnoreWhitespace' while an
                     effort has been made above to set a 'MixedContent' mode in some cases?
                     WHY IS THE 'mode' VARIABLE NOT USED HERE???? */
//                    ParseTag( doc, node, IgnoreWhitespace /*MixedContent*/ );
//                    continue;
                    {
                        TidyParserMemory memory;
                        memory.identity = TY_(ParseBlock);
                        memory.mode = IgnoreWhitespace; /* mode; */
                        memory.original_node = element;
                        memory.reentry_node = node;
                        memory.reentry_mode = mode;
                        memory.reentry_state = STATE_COMPLETE;
                        pushMemory( doc, memory );
                        return node;
                    }
                }

                /* discard unexpected tags */
                if (node->type == EndTag)
                    TY_(PopInline)( doc, node );  /* if inline end tag */

                TY_(Report)(doc, element, node, DISCARDING_UNEXPECTED );
                TY_(FreeNode)( doc, node );
                continue;
            } break; /* STATE_INITIAL */

            default:
            {
                state = STATE_COMPLETE;
            } break; /* default */

        } /* switch */
    } /* while */

    if (!(element->tag->model & CM_OPT))
        TY_(Report)(doc, element, node, MISSING_ENDTAG_FOR);

    if (element->tag->model & CM_OBJECT)
    {
        /* pop inline stack */
        while ( lexer->istacksize > lexer->istackbase )
            TY_(PopInline)( doc, NULL );
        lexer->istackbase = istackbase;
    }

    TrimSpaces( doc, element );

#if defined(ENABLE_DEBUG_LOG)
    in_parse_block--;
    SPRTF("Exit ParseBlock 10 %d...\n",in_parse_block);
#endif
    return NULL;
#endif
}


/** MARK: TY_(ParseNamespace)
 *  Act as a generic XML (sub)tree parser: collect each node and add it
 *  to the DOM, without any further validation. It's useful for tags that
 *  have XML-like content, such as `svg` and `math`.
 *  @note Perhaps this is poorly named, as we're not parsing the namespace
 *    of a particular tag, but a tag with XML-like content.
 *  @note This is a non-recursive parser.
 *  @todo Add schema- or other-hierarchy-definition-based validation
 *    of the subtree here.
 */
Node* TY_(ParseNamespace)( TidyDocImpl* doc, Node *basenode, GetTokenMode mode, Bool popStack )
{
    Lexer* lexer = doc->lexer;
    Node *node;
    Node *parent = basenode;
    uint istackbase;
    AttVal* av; /* #130 MathML attr and entity fix! */

    /* a la <table>: defer popping elements off the inline stack */
    TY_(DeferDup)( doc );
    istackbase = lexer->istackbase;
    lexer->istackbase = lexer->istacksize;

    mode = OtherNamespace; /* Preformatted; IgnoreWhitespace; */

    while ((node = TY_(GetToken)(doc, mode)) != NULL)
    {
        /*
        fix check to skip action in InsertMisc for regular/empty
        nodes, which we don't want here...

        The way we do it here is by checking and processing everything
        and only what remains goes into InsertMisc()
        */

        /* is this a close tag? And does it match the current parent node? */
        if (node->type == EndTag)
        {
            /*
            to prevent end tags flowing from one 'alternate namespace' we
            check this in two phases: first we check if the tag is a
            descendant of the current node, and when it is, we check whether
            it is the end tag for a node /within/ or /outside/ the basenode.
            */
            Bool outside;
            Node *mp = FindMatchingDescendant(parent, node, basenode, &outside);

            if (mp != NULL)
            {
                /*
                when mp != parent as we might expect,
                infer end tags until we 'hit' the matched
                parent or the basenode
                */
                Node *n;

                for (n = parent;
                     n != NULL && n != basenode->parent && n != mp;
                     n = n->parent)
                {
                    /* n->implicit = yes; */
                    n->closed = yes;
                    TY_(Report)(doc, n->parent, n, MISSING_ENDTAG_BEFORE);
                }

                /* Issue #369 - Since 'assert' is DEBUG only, and there are
                   simple cases where these can be fired, removing them
                   pending feedback from the original author!
                   assert(outside == no ? n == mp : 1);
                   assert(outside == yes ? n == basenode->parent : 1);
                   =================================================== */

                if (outside == no)
                {
                    /* EndTag for a node within the basenode subtree. Roll on... */
                    if (n)
                        n->closed = yes;
                    TY_(FreeNode)(doc, node);

                    node = n;
                    parent = node ? node->parent : NULL;
                }
                else
                {
                    /* EndTag for a node outside the basenode subtree: let the caller handle that. */
                    TY_(UngetToken)( doc );
                    node = basenode;
                    parent = node->parent;
                }

                /* when we've arrived at the end-node for the base node, it's quitting time */
                if (node == basenode)
                {
                    lexer->istackbase = istackbase;
                    assert(basenode && basenode->closed == yes);
                    return NULL;
                }
            }
            else
            {
                /* unmatched close tag: report an error and discard */
                /* TY_(Report)(doc, parent, node, NON_MATCHING_ENDTAG); Issue #308 - Seems wrong warning! */
                TY_(Report)(doc, parent, node, DISCARDING_UNEXPECTED);
                assert(parent);
                /* assert(parent->tag != node->tag); Issue #308 - Seems would always be true! */
                TY_(FreeNode)( doc, node); /* Issue #308 - Discard unexpected end tag memory */
            }
        }
        else if (node->type == StartTag)
        {
            /* #130 MathML attr and entity fix!
               care if it has attributes, and 'accidently' any of those attributes match known */
            for ( av = node->attributes; av; av = av->next )
            {
                av->dict = 0; /* does something need to be freed? */
            }
            /* add another child to the current parent */
            TY_(InsertNodeAtEnd)(parent, node);
            parent = node;
        }
        else
        {
            /* #130 MathML attr and entity fix!
               care if it has attributes, and 'accidently' any of those attributes match known */
            for ( av = node->attributes; av; av = av->next )
            {
                av->dict = 0; /* does something need to be freed? */
            }
            TY_(InsertNodeAtEnd)(parent, node);
        }
    }

    TY_(Report)(doc, basenode->parent, basenode, MISSING_ENDTAG_FOR);
    return NULL;
}


/** MARK: TY_(ParseInline)
 *  Parse inline element nodes.
 */
Node* TY_(ParseInline)( TidyDocImpl *doc, Node *node, GetTokenMode mode, Bool popStack )
{
    TY_(oldParseInline)( doc, node, mode );
    return NULL;
}


/** MARK: TY_(ParseEmpty)
 *  Parse empty element nodes.
 *  @note This is a non-recursive parser.
  */
Node* TY_(ParseEmpty)( TidyDocImpl* doc, Node *element, GetTokenMode mode, Bool popStack )
{
    Lexer* lexer = doc->lexer;
    if ( lexer->isvoyager )
    {
        Node *node = TY_(GetToken)( doc, mode);
        if ( node )
        {
            if ( !(node->type == EndTag && node->tag == element->tag) )
            {
                /* TY_(Report)(doc, element, node, ELEMENT_NOT_EMPTY); */
                TY_(UngetToken)( doc );
            }
            else
            {
                TY_(FreeNode)( doc, node );
            }
        }
    }
    return NULL;
}


/** MARK: TY_(ParseDefList)
 *  Parses the `dl` tag.
 */
Node* TY_(ParseDefList)( TidyDocImpl* doc, Node *list, GetTokenMode mode, Bool popStack )
{
    TY_(oldParseDefList)( doc, list, mode );
    return NULL;
}


/** MARK: TY_(ParseList)
 *  Parses list tags.
 */
Node* TY_(ParseList)( TidyDocImpl* doc, Node *list, GetTokenMode ARG_UNUSED(mode), Bool popStack )
{
    TY_(oldParseList)( doc, list, mode );
    return NULL;
}


/** MARK: TY_(ParseRow)
 *  Parses the `row` tag.
 */
Node* TY_(ParseRow)( TidyDocImpl* doc, Node *row, GetTokenMode ARG_UNUSED(mode), Bool popStack )
{
    TY_(oldParseRow)( doc, row, mode );
    return NULL;
}


/** MARK: TY_(ParseRowGroup)
 *  Parses the `rowgroup` tag.
 */
Node* TY_(ParseRowGroup)( TidyDocImpl* doc, Node *rowgroup, GetTokenMode ARG_UNUSED(mode), Bool popStack )
{
    TY_(oldParseRowGroup)( doc, rowgroup, mode );
    return NULL;
}


/** MARK: TY_(ParseColGroup)
 *  Parses the `colgroup` tag.
 */
Node* TY_(ParseColGroup)( TidyDocImpl* doc, Node *colgroup, GetTokenMode ARG_UNUSED(mode), Bool popStack )
{
    TY_(oldParseColGroup)( doc, colgroup, mode );
    return NULL;
}


/** MARK: TY_(ParseTableTag)
 *  Parses the `table` tag.
 */
Node* TY_(ParseTableTag)( TidyDocImpl* doc, Node *table, GetTokenMode ARG_UNUSED(mode), Bool popStack )
{
    TY_(oldParseTableTag)( doc, table, mode );
    return NULL;
}


/** MARK: TY_(ParsePre)
 *  Parses the `pre` tag.
 */
Node* TY_(ParsePre)( TidyDocImpl* doc, Node *pre, GetTokenMode ARG_UNUSED(mode), Bool popStack )
{
    TY_(oldParsePre)( doc, pre, mode );
    return NULL;
}


/** MARK: TY_(ParseOptGroup)
 *  Parses the `optgroup` tag.
 */
Node* TY_(ParseOptGroup)( TidyDocImpl* doc, Node *field, GetTokenMode ARG_UNUSED(mode), Bool popStack )
{
    TY_(oldParseOptGroup)( doc, field, mode );
    return NULL;
}


/** MARK: TY_(ParseSelect)
 *  Parses the `select` tag.
 */
Node* TY_(ParseSelect)( TidyDocImpl* doc, Node *field, GetTokenMode ARG_UNUSED(mode), Bool popStack )
{
    TY_(oldParseSelect)( doc, field, mode );
    return NULL;
}


/** MARK: TY_(ParseDataList)
 *  Parses the `datalist` tag.
 */
Node* TY_(ParseDatalist)( TidyDocImpl* doc, Node *field, GetTokenMode ARG_UNUSED(mode), Bool popStack )
{
    TY_(oldParseDatalist)( doc, field, mode );
    return NULL;
}


/** MARK: TY_(ParseText)
 *  Parses the `option` and `textarea` tags.
 */
Node* TY_(ParseText)( TidyDocImpl* doc, Node *field, GetTokenMode mode, Bool popStack )
{
    TY_(oldParseText)( doc, field, mode );
    return NULL;
}


/** MARK: TY_(ParseTitle)
 *  Parses the `title` tag.
 */
Node* TY_(ParseTitle)( TidyDocImpl* doc, Node *title, GetTokenMode ARG_UNUSED(mode), Bool popStack )
{
    TY_(oldParseTitle)( doc, title, mode );
    return NULL;
}


/** MARK: TY_(ParseScript)
 *  Parses the `script` tag.
 *
 *  @todo This isn't quite right for CDATA content as it recognises tags
 *  within the content and parses them accordingly. This will unfortunately
 *  screw up scripts which include:
 *    < + letter
 *    < + !
 *    < + ?
 *    < + / + letter
 */
Node* TY_(ParseScript)( TidyDocImpl* doc, Node *script, GetTokenMode ARG_UNUSED(mode), Bool popStack )
{
    TY_(oldParseScript)( doc, script, mode );
    return NULL;
}


/** MARK: TY_(ParseHead)
 *  Parses the `head` tag.
 */
Node* TY_(ParseHead)( TidyDocImpl* doc, Node *head, GetTokenMode ARG_UNUSED(mode), Bool popStack )
{
    TY_(oldParseHead)( doc, head, mode );
    return NULL;
}


/** MARK: TY_(ParseBody)
 *  Parses the `body` tag.
 */
Node* TY_(ParseBody)( TidyDocImpl* doc, Node *body, GetTokenMode mode, Bool popStack )
{
    TY_(oldParseBody)( doc, body, mode);
    return NULL;
#if 0
    Lexer* lexer = doc->lexer;
    Node *node = NULL;
    Bool checkstack, iswhitenode;
    Bool keepToken = no;
    parserState state = STATE_INITIAL;

    mode = IgnoreWhitespace;
    checkstack = yes;

    /*
     If we're re-entering, then we need to setup from a previous state,
     instead of starting fresh. We can pull what we need from the document's
     stack.
     */
    if ( popStack )
    {
        TidyParserMemory memory = popMemory( doc );
        node = memory.reentry_node;
        mode = memory.reentry_mode;
        state = memory.reentry_state;
        body = memory.original_node;
        keepToken = node != NULL;
    }

    TY_(BumpObject)( doc, body->parent );

    DEBUG_LOG(SPRTF("Enter ParseBody...\n"));
    while ( state != STATE_COMPLETE )
    {
        if ( !keepToken )
            node = TY_(GetToken)( doc, mode );
        keepToken = no;

        if ( !node )
            state = STATE_COMPLETE;

        switch ( state )
        {
            case STATE_INITIAL:
            {
                /* find and discard multiple <body> elements */
                if (node->tag == body->tag && node->type == StartTag)
                {
                    TY_(Report)(doc, body, node, DISCARDING_UNEXPECTED);
                    TY_(FreeNode)(doc, node);
                    continue;
                }

                /* #538536 Extra endtags not detected */
                if ( nodeIsHTML(node) )
                {
                    if (TY_(nodeIsElement)(node) || lexer->seenEndHtml)
                        TY_(Report)(doc, body, node, DISCARDING_UNEXPECTED);
                    else
                        lexer->seenEndHtml = 1;

                    TY_(FreeNode)( doc, node);
                    continue;
                }

                if ( lexer->seenEndBody &&
                    ( node->type == StartTag ||
                     node->type == EndTag   ||
                     node->type == StartEndTag ) )
                {
                    TY_(Report)(doc, body, node, CONTENT_AFTER_BODY );
                }

                if ( node->tag == body->tag && node->type == EndTag )
                {
                    body->closed = yes;
                    TrimSpaces(doc, body);
                    TY_(FreeNode)( doc, node);
                    lexer->seenEndBody = 1;
                    mode = IgnoreWhitespace;

                    if ( nodeIsNOFRAMES(body->parent) )
                    {
                        keepToken = yes;
                        state = STATE_COMPLETE;
                        continue;
                    }

                    continue;
                }

                if ( nodeIsNOFRAMES(node) )
                {
                    if (node->type == StartTag)
                    {
                        TY_(InsertNodeAtEnd)(body, node);
                        TY_(ParseBlock)(doc, node, mode, no);
                        continue;
                    }

                    if (node->type == EndTag && nodeIsNOFRAMES(body->parent) )
                    {
                        TrimSpaces(doc, body);
                        TY_(UngetToken)( doc );
                        keepToken = yes;
                        state = STATE_COMPLETE;
                        continue;
                    }
                }

                if ( (nodeIsFRAME(node) || nodeIsFRAMESET(node))
                    && nodeIsNOFRAMES(body->parent) )
                {
                    TrimSpaces(doc, body);
                    TY_(UngetToken)( doc );
                    keepToken = yes;
                    state = STATE_COMPLETE;
                    continue;
                }

                iswhitenode = no;

                if ( TY_(nodeIsText)(node) &&
                    node->end <= node->start + 1 &&
                    lexer->lexbuf[node->start] == ' ' )
                    iswhitenode = yes;

                /* deal with comments etc. */
                if (InsertMisc(body, node))
                    continue;

                /* mixed content model permits text */
                if (TY_(nodeIsText)(node))
                {
                    if (iswhitenode && mode == IgnoreWhitespace)
                    {
                        TY_(FreeNode)( doc, node);
                        continue;
                    }

                    /* HTML 2 and HTML4 strict don't allow text here */
                    TY_(ConstrainVersion)(doc, ~(VERS_HTML40_STRICT | VERS_HTML20));

                    if (checkstack)
                    {
                        checkstack = no;

                        if ( TY_(InlineDup)(doc, node) > 0 )
                            continue;
                    }

                    TY_(InsertNodeAtEnd)(body, node);
                    mode = MixedContent;
                    continue;
                }

                if (node->type == DocTypeTag)
                {
                    InsertDocType(doc, body, node);
                    continue;
                }
                /* discard unknown  and PARAM tags */
                if ( node->tag == NULL || nodeIsPARAM(node) )
                {
                    TY_(Report)(doc, body, node, DISCARDING_UNEXPECTED);
                    TY_(FreeNode)( doc, node);
                    continue;
                }

                /*
                 Netscape allows LI and DD directly in BODY
                 We infer UL or DL respectively and use this
                 Bool to exclude block-level elements so as
                 to match Netscape's observed behaviour.
                 */
                lexer->excludeBlocks = no;

                if (( nodeIsINPUT(node) ||
                     (!TY_(nodeHasCM)(node, CM_BLOCK) && !TY_(nodeHasCM)(node, CM_INLINE))
                     ) && !TY_(IsHTML5Mode)(doc) )
                {
                    /* avoid this error message being issued twice */
                    if (!(node->tag->model & CM_HEAD))
                        TY_(Report)(doc, body, node, TAG_NOT_ALLOWED_IN);

                    if (node->tag->model & CM_HTML)
                    {
                        /* copy body attributes if current body was inferred */
                        if ( nodeIsBODY(node) && body->implicit
                            && body->attributes == NULL )
                        {
                            body->attributes = node->attributes;
                            node->attributes = NULL;
                        }

                        TY_(FreeNode)( doc, node);
                        continue;
                    }

                    if (node->tag->model & CM_HEAD)
                    {
                        MoveToHead(doc, body, node);
                        continue;
                    }

                    if (node->tag->model & CM_LIST)
                    {
                        TY_(UngetToken)( doc );
                        node = TY_(InferredTag)(doc, TidyTag_UL);
                        AddClassNoIndent(doc, node);
                        lexer->excludeBlocks = yes;
                    }
                    else if (node->tag->model & CM_DEFLIST)
                    {
                        TY_(UngetToken)( doc );
                        node = TY_(InferredTag)(doc, TidyTag_DL);
                        lexer->excludeBlocks = yes;
                    }
                    else if (node->tag->model & (CM_TABLE | CM_ROWGRP | CM_ROW))
                    {
                        /* http://tidy.sf.net/issue/2855621 */
                        if (node->type != EndTag) {
                            TY_(UngetToken)( doc );
                            node = TY_(InferredTag)(doc, TidyTag_TABLE);
                        }
                        lexer->excludeBlocks = yes;
                    }
                    else if ( nodeIsINPUT(node) )
                    {
                        TY_(UngetToken)( doc );
                        node = TY_(InferredTag)(doc, TidyTag_FORM);
                        lexer->excludeBlocks = yes;
                    }
                    else
                    {
                        if ( !TY_(nodeHasCM)(node, CM_ROW | CM_FIELD) )
                        {
                            TY_(UngetToken)( doc );
                            return NULL;
                        }

                        /* ignore </td> </th> <option> etc. */
                        TY_(FreeNode)( doc, node );
                        continue;
                    }
                }

                if (node->type == EndTag)
                {
                    if ( nodeIsBR(node) )
                        node->type = StartTag;
                    else if ( nodeIsP(node) )
                    {
                        node->type = StartEndTag;
                        node->implicit = yes;
                    }
                    else if ( TY_(nodeHasCM)(node, CM_INLINE) )
                        TY_(PopInline)( doc, node );
                }

                if (TY_(nodeIsElement)(node))
                {
                    if (nodeIsMAIN(node))
                    {
                        /*\ Issue #166 - repeated <main> element
                         *  How to efficiently search for a previous main element?
                         \*/
                        if ( findNodeById(doc, TidyTag_MAIN) )
                        {
                            doc->badForm |= flg_BadMain; /* this is an ERROR in format */
                            TY_(Report)(doc, body, node, DISCARDING_UNEXPECTED);
                            TY_(FreeNode)( doc, node);
                            continue;
                        }
                    }
                    /* Issue #20 - merging from Ger Hobbelt fork put back CM_MIXED, which had been
                     removed to fix this issue - reverting to fix 880221e
                     */
                    if ( TY_(nodeHasCM)(node, CM_INLINE) )
                    {
                        /* HTML4 strict doesn't allow inline content here */
                        /* but HTML2 does allow img elements as children of body */
                        if ( nodeIsIMG(node) )
                            TY_(ConstrainVersion)(doc, ~VERS_HTML40_STRICT);
                        else
                            TY_(ConstrainVersion)(doc, ~(VERS_HTML40_STRICT|VERS_HTML20));

                        if (checkstack && !node->implicit)
                        {
                            checkstack = no;

                            if ( TY_(InlineDup)(doc, node) > 0 )
                                continue;
                        }

                        mode = MixedContent;
                    }
                    else
                    {
                        checkstack = yes;
                        mode = IgnoreWhitespace;
                    }

                    if (node->implicit)
                        TY_(Report)(doc, body, node, INSERTING_TAG);

                    TY_(InsertNodeAtEnd)(body, node);
//                    ParseTag(doc, node, mode);
//                    continue;
                    state = STATE_PARSE_TAG;
                    keepToken = yes;
                    continue;
                }

                /* discard unexpected tags */
                TY_(Report)(doc, body, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);
            } break;  /* STATE_INITIAL */


            case STATE_PARSE_TAG:
            {
                TidyParserMemory memory;
                memory.identity = TY_(ParseBody);
                memory.mode = mode;
                memory.original_node = body;
                memory.reentry_node = NULL;
                memory.reentry_mode = mode;
                memory.reentry_state = STATE_INITIAL;
                pushMemory( doc, memory );
                return node;
            } break;

            default:
            {
                state = STATE_COMPLETE;
            } break;

        } /* switch */
    } /* while */
    DEBUG_LOG(SPRTF("Exit ParseBody 1...\n"));
    return NULL;
#endif
}


/** MARK: TY_(ParseNoFrames)
 *  Parses the `noframes` tag.
 */
Node* TY_(ParseNoFrames)( TidyDocImpl* doc, Node *noframes, GetTokenMode mode, Bool popStack )
{
    TY_(oldParseNoFrames)( doc, noframes, mode );
    return NULL;
}


/** MARK: TY_(ParseFrameSet)
 *  Parses the `frameset` tag.
 */
Node* TY_(ParseFrameSet)( TidyDocImpl* doc, Node *frameset, GetTokenMode ARG_UNUSED(mode), Bool popStack )
{
    TY_(oldParseFrameSet)( doc, frameset, mode );
    return NULL;
}



/***************************************************************************//*
 ** MARK: - Post-Parse Operations
 ***************************************************************************/


/**
 *  Encloses all naked body text within `p` tags.
 */
static void EncloseBodyText(TidyDocImpl* doc)
{
    Node* node;
    Node* body = TY_(FindBody)(doc);

    if (!body)
        return;

    node = body->content;

    while (node)
    {
        if ((TY_(nodeIsText)(node) && !TY_(IsBlank)(doc->lexer, node)) ||
            (TY_(nodeIsElement)(node) && nodeCMIsOnlyInline(node)))
        {
            Node* p = TY_(InferredTag)(doc, TidyTag_P);
            TY_(InsertNodeBeforeElement)(node, p);
            while (node && (!TY_(nodeIsElement)(node) || nodeCMIsOnlyInline(node)))
            {
                Node* next = node->next;
                TY_(RemoveNode)(node);
                TY_(InsertNodeAtEnd)(p, node);
                node = next;
            }
            TrimSpaces(doc, p);
            continue;
        }
        node = node->next;
    }
}


/**
 *  Encloses naked text in certain elements within `p` tags.
 *
 *  <form>, <blockquote>, and <noscript> do not allow #PCDATA in
 *  HTML 4.01 Strict (%block; model instead of %flow;).
 */
static void EncloseBlockText(TidyDocImpl* doc, Node* node)
{
    Node *next;
    Node *block;

    while (node)
    {
        next = node->next;

        if (node->content)
            EncloseBlockText(doc, node->content);

        if (!(nodeIsFORM(node) || nodeIsNOSCRIPT(node) ||
              nodeIsBLOCKQUOTE(node))
            || !node->content)
        {
            node = next;
            continue;
        }

        block = node->content;

        if ((TY_(nodeIsText)(block) && !TY_(IsBlank)(doc->lexer, block)) ||
            (TY_(nodeIsElement)(block) && nodeCMIsOnlyInline(block)))
        {
            Node* p = TY_(InferredTag)(doc, TidyTag_P);
            TY_(InsertNodeBeforeElement)(block, p);
            while (block &&
                   (!TY_(nodeIsElement)(block) || nodeCMIsOnlyInline(block)))
            {
                Node* tempNext = block->next;
                TY_(RemoveNode)(block);
                TY_(InsertNodeAtEnd)(p, block);
                block = tempNext;
            }
            TrimSpaces(doc, p);
            continue;
        }

        node = next;
    }
}


/**
 *  Replaces elements that are obsolete with appropriate substitute tags.
 */
static void ReplaceObsoleteElements(TidyDocImpl* doc, Node* node)
{
    Node *next;

    while (node)
    {
        next = node->next;

        /* if (nodeIsDIR(node) || nodeIsMENU(node)) */
        /* HTML5 - <menu ... > is no longer obsolete */
        if (nodeIsDIR(node))
            TY_(CoerceNode)(doc, node, TidyTag_UL, yes, yes);

        if (nodeIsXMP(node) || nodeIsLISTING(node) ||
            (node->tag && node->tag->id == TidyTag_PLAINTEXT))
            TY_(CoerceNode)(doc, node, TidyTag_PRE, yes, yes);

        if (node->content)
            ReplaceObsoleteElements(doc, node->content);

        node = next;
    }
}


/**
 *  Performs checking of all attributes recursively starting at `node`.
 */
static void AttributeChecks(TidyDocImpl* doc, Node* node)
{
    Node *next;

    while (node)
    {
        next = node->next;

        if (TY_(nodeIsElement)(node))
        {
            if (node->tag && node->tag->chkattrs) /* [i_a]2 fix crash after adding SVG support with alt/unknown tag subtree insertion there */
                node->tag->chkattrs(doc, node);
            else
                TY_(CheckAttributes)(doc, node);
        }

        if (node->content)
            AttributeChecks(doc, node->content);

        assert( next != node ); /* http://tidy.sf.net/issue/1603538 */
        node = next;
    }
}


/***************************************************************************//*
 ** MARK: - Internal API Implementation
 ***************************************************************************/


/** MARK: TY_(CheckNodeIntegrity)
 *  Is used to perform a node integrity check after parsing an HTML or XML
 *  document.
 *  @note Actual performance of this check can be disabled by defining the
 *  macro NO_NODE_INTEGRITY_CHECK.
 */
Bool TY_(CheckNodeIntegrity)(Node *node)
{
#ifndef NO_NODE_INTEGRITY_CHECK
    Node *child;

    if (node->prev)
    {
        if (node->prev->next != node)
            return no;
    }

    if (node->next)
    {
        if (node->next == node || node->next->prev != node)
            return no;
    }

    if (node->parent)
    {
        if (node->prev == NULL && node->parent->content != node)
            return no;

        if (node->next == NULL && node->parent->last != node)
            return no;
    }

    for (child = node->content; child; child = child->next)
        if ( child->parent != node || !TY_(CheckNodeIntegrity)(child) )
            return no;

#endif
    return yes;
}


/** MARK: TY_(IsNewNode)
 *  Used to check if a node uses CM_NEW, which determines how attributes
 *  without values should be printed. This was introduced to deal with
 *  user-defined tags e.g. ColdFusion.
 */
Bool TY_(IsNewNode)(Node *node)
{
    if (node && node->tag)
    {
        return (node->tag->model & CM_NEW);
    }
    return yes;
}


/** MARK: TY_(CoerceNode)
 *  Transforms a given node to another element, for example, from a <p>
 *  to a <br>.
 */
void TY_(CoerceNode)(TidyDocImpl* doc, Node *node, TidyTagId tid, Bool obsolete, Bool unexpected)
{
    const Dict* tag = TY_(LookupTagDef)(tid);
    Node* tmp = TY_(InferredTag)(doc, tag->id);

    if (obsolete)
        TY_(Report)(doc, node, tmp, OBSOLETE_ELEMENT);
    else if (unexpected)
        TY_(Report)(doc, node, tmp, REPLACING_UNEX_ELEMENT);
    else
        TY_(Report)(doc, node, tmp, REPLACING_ELEMENT);

    TidyDocFree(doc, tmp->element);
    TidyDocFree(doc, tmp);

    node->was = node->tag;
    node->tag = tag;
    node->type = StartTag;
    node->implicit = yes;
    TidyDocFree(doc, node->element);
    node->element = TY_(tmbstrdup)(doc->allocator, tag->name);
}


/** MARK: TY_(RemoveNode)
 *  Extract a node and its children from a markup tree
 */
Node *TY_(RemoveNode)(Node *node)
{
    if (node->prev)
        node->prev->next = node->next;

    if (node->next)
        node->next->prev = node->prev;

    if (node->parent)
    {
        if (node->parent->content == node)
            node->parent->content = node->next;

        if (node->parent->last == node)
            node->parent->last = node->prev;
    }

    node->parent = node->prev = node->next = NULL;
    return node;
}


/** MARK: TY_(DiscardElement)
 *  Remove node from markup tree and discard it.
 */
Node *TY_(DiscardElement)( TidyDocImpl* doc, Node *element )
{
    Node *next = NULL;

    if (element)
    {
        next = element->next;
        TY_(RemoveNode)(element);
        TY_(FreeNode)( doc, element);
    }

    return next;
}


/** MARK: TY_(InsertNodeAtStart)
 *  Insert node into markup tree as the firt element of content of element.
 */
void TY_(InsertNodeAtStart)(Node *element, Node *node)
{
    node->parent = element;

    if (element->content == NULL)
        element->last = node;
    else
        element->content->prev = node;

    node->next = element->content;
    node->prev = NULL;
    element->content = node;
}


/** MARK: TY_(InsertNodeAtEnd)
 *  Insert node into markup tree as the last element of content of element.
 */
void TY_(InsertNodeAtEnd)(Node *element, Node *node)
{
    node->parent = element;
    node->prev = element ? element->last : NULL;

    if (element && element->last != NULL)
        element->last->next = node;
    else
        if (element)
            element->content = node;

    if (element)
        element->last = node;
}


/** MARK: TY_(InsertNodeBeforeElement)
 *  Insert node into markup tree before element.
 */
void TY_(InsertNodeBeforeElement)(Node *element, Node *node)
{
    Node *parent;

    parent = element ? element->parent : NULL;
    node->parent = parent;
    node->next = element;
    node->prev = element ? element->prev : NULL;
    if (element)
        element->prev = node;

    if (node->prev)
        node->prev->next = node;

    if (parent && parent->content == element)
        parent->content = node;
}


/** MARK: TY_(InsertNodeAfterElement)
 *  Insert node into markup tree after element.
 */
void TY_(InsertNodeAfterElement)(Node *element, Node *node)
{
    Node *parent;

    parent = element->parent;
    node->parent = parent;

    /* AQ - 13 Jan 2000 fix for parent == NULL */
    if (parent != NULL && parent->last == element)
        parent->last = node;
    else
    {
        node->next = element->next;
        /* AQ - 13 Jan 2000 fix for node->next == NULL */
        if (node->next != NULL)
            node->next->prev = node;
    }

    element->next = node;
    node->prev = element;
}


/** MARK: TY_(TrimEmptyElement)
 *  Trims a single, empty element, returning the next node.
 */
Node *TY_(TrimEmptyElement)( TidyDocImpl* doc, Node *element )
{
    if ( CanPrune(doc, element) )
    {
        if (element->type != TextNode)
        {
            doc->footnotes |= FN_TRIM_EMPTY_ELEMENT;
            TY_(Report)(doc, element, NULL, TRIM_EMPTY_ELEMENT);
        }

        return TY_(DiscardElement)(doc, element);
    }
    return element->next;
}


/** MARK: TY_(DropEmptyElements)
 *  Trims a tree of empty elements recursively, returning the next node.
 */
Node* TY_(DropEmptyElements)(TidyDocImpl* doc, Node* node)
{
    Node* next;

    while (node)
    {
        next = node->next;

        if (node->content)
            TY_(DropEmptyElements)(doc, node->content);

        if (!TY_(nodeIsElement)(node) &&
            !(TY_(nodeIsText)(node) && !(node->start < node->end)))
        {
            node = next;
            continue;
        }

        next = TY_(TrimEmptyElement)(doc, node);
        node = next;
    }

    return node;
}


/** MARK: TY_(IsBlank)
 *  Indicates whether or not a text node is blank, meaning that it consists
 *  of nothing, or a single space.
 */
Bool TY_(IsBlank)(Lexer *lexer, Node *node)
{
    Bool isBlank = TY_(nodeIsText)(node);
    if ( isBlank )
        isBlank = ( node->end == node->start ||       /* Zero length */
                   ( node->end == node->start+1      /* or one blank. */
                    && lexer->lexbuf[node->start] == ' ' ) );
        return isBlank;
}


/** MARK: TY_(IsJavaScript)
 *  Indicates whether or not a node is declared as containing javascript
 *  code.
 */
Bool TY_(IsJavaScript)(Node *node)
{
    Bool result = no;
    AttVal *attr;

    if (node->attributes == NULL)
        return yes;

    for (attr = node->attributes; attr; attr = attr->next)
    {
        if ( (attrIsLANGUAGE(attr) || attrIsTYPE(attr))
             && AttrContains(attr, "javascript") )
        {
            result = yes;
            break;
        }
    }

    return result;
}


/** MARK: TY_(ParseDocument)
 *  Parses an HTML document after lexing. It begins by properly configuring
 *  the overall HTML structure, and subsequently processes all remaining
 *  nodes.
 */
void TY_(ParseDocument)(TidyDocImpl* doc)
{
    Node *node, *html, *doctype = NULL;

    while ((node = TY_(GetToken)(doc, IgnoreWhitespace)) != NULL)
    {
        if (node->type == XmlDecl)
        {
            doc->xmlDetected = yes;

            if (TY_(FindXmlDecl)(doc) && doc->root.content)
            {
                TY_(Report)(doc, &doc->root, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)(doc, node);
                continue;
            }
            if (node->line > 1 || node->column != 1)
            {
                TY_(Report)(doc, &doc->root, node, SPACE_PRECEDING_XMLDECL);
            }
        }

        /* deal with comments etc. */
        if (InsertMisc( &doc->root, node ))
            continue;

        if (node->type == DocTypeTag)
        {
            if (doctype == NULL)
            {
                TY_(InsertNodeAtEnd)( &doc->root, node);
                doctype = node;
            }
            else
            {
                TY_(Report)(doc, &doc->root, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);
            }
            continue;
        }

        if (node->type == EndTag)
        {
            TY_(Report)(doc, &doc->root, node, DISCARDING_UNEXPECTED);
            TY_(FreeNode)( doc, node);
            continue;
        }

        if (node->type == StartTag && nodeIsHTML(node))
        {
            AttVal *xmlns = TY_(AttrGetById)(node, TidyAttr_XMLNS);

            if (AttrValueIs(xmlns, XHTML_NAMESPACE))
            {
                Bool htmlOut = cfgBool( doc, TidyHtmlOut );
                doc->lexer->isvoyager = yes;                  /* Unless plain HTML */
                TY_(SetOptionBool)( doc, TidyXhtmlOut, !htmlOut ); /* is specified, output*/
                TY_(SetOptionBool)( doc, TidyXmlOut, !htmlOut );   /* will be XHTML. */

                /* adjust other config options, just as in config.c */
                if ( !htmlOut )
                {
                    TY_(SetOptionBool)( doc, TidyUpperCaseTags, no );
                    TY_(SetOptionInt)( doc, TidyUpperCaseAttrs, no );
                }
            }
        }

        if ( node->type != StartTag || !nodeIsHTML(node) )
        {
            TY_(UngetToken)( doc );
            html = TY_(InferredTag)(doc, TidyTag_HTML);
        }
        else
            html = node;

        /*\
         *  #72, avoid MISSING_DOCTYPE if show-body-only.
         *  #191, also if --doctype omit, that is TidyDoctypeOmit
         *  #342, adjust tags to html4-- if not 'auto' or 'html5'
        \*/
        if (!TY_(FindDocType)(doc))
        {
            ulong dtmode = cfg( doc, TidyDoctypeMode );
            if ((dtmode != TidyDoctypeOmit) && !showingBodyOnly(doc))
                TY_(Report)(doc, NULL, NULL, MISSING_DOCTYPE);
            if ((dtmode != TidyDoctypeAuto) && (dtmode != TidyDoctypeHtml5))
            {
                /*\
                 *  Issue #342 - if not doctype 'auto', or 'html5'
                 *  then reset mode htm4-- parsing
                \*/
                TY_(AdjustTags)(doc); /* Dynamically modify the tags table to html4-- mode */
            }
        }
        TY_(InsertNodeAtEnd)( &doc->root, html);
        ParseHTMLWithNode( doc, html );
        break;
    }

    /* do this before any more document fixes */
    if ( cfg( doc, TidyAccessibilityCheckLevel ) > 0 )
        TY_(AccessibilityChecks)( doc );

    if (!TY_(FindHTML)(doc))
    {
        /* a later check should complain if <body> is empty */
        html = TY_(InferredTag)(doc, TidyTag_HTML);
        TY_(InsertNodeAtEnd)( &doc->root, html);
        ParseHTMLWithNode( doc, html );
    }

    node = TY_(FindTITLE)(doc);
    if (!node)
    {
        Node* head = TY_(FindHEAD)(doc);
        /* #72, avoid MISSING_TITLE_ELEMENT if show-body-only (but allow InsertNodeAtEnd to avoid new warning) */
        if (!showingBodyOnly(doc))
        {
            TY_(Report)(doc, head, NULL, MISSING_TITLE_ELEMENT);
        }
        TY_(InsertNodeAtEnd)(head, TY_(InferredTag)(doc, TidyTag_TITLE));
    }
    else if (!node->content && !showingBodyOnly(doc))
    {
        /* Is #839 - warn node is blank in HTML5 */
        if (TY_(IsHTML5Mode)(doc))
        {
            TY_(Report)(doc, node, NULL, BLANK_TITLE_ELEMENT);
        }
    }

    AttributeChecks(doc, &doc->root);
    ReplaceObsoleteElements(doc, &doc->root);
    TY_(DropEmptyElements)(doc, &doc->root);
    CleanSpaces(doc, &doc->root);

    if (cfgBool(doc, TidyEncloseBodyText))
        EncloseBodyText(doc);
    if (cfgBool(doc, TidyEncloseBlockText))
        EncloseBlockText(doc, &doc->root);
}


/** MARK: TY_(XMLPreserveWhiteSpace)
 *  Indicates whether or not whitespace is to be preserved in XHTML/XML
 *  documents.
 */
Bool TY_(XMLPreserveWhiteSpace)( TidyDocImpl* doc, Node *element)
{
    AttVal *attribute;

    /* search attributes for xml:space */
    for (attribute = element->attributes; attribute; attribute = attribute->next)
    {
        if (attrIsXML_SPACE(attribute))
        {
            if (AttrValueIs(attribute, "preserve"))
                return yes;

            return no;
        }
    }

    if (element->element == NULL)
        return no;
        
    /* kludge for html docs without explicit xml:space attribute */
    if (nodeIsPRE(element)    ||
        nodeIsSCRIPT(element) ||
        nodeIsSTYLE(element)  ||
        TY_(FindParser)(doc, element) == TY_(ParsePre))
        return yes;

    /* kludge for XSL docs */
    if ( TY_(tmbstrcasecmp)(element->element, "xsl:text") == 0 )
        return yes;

    return no;
}


/** MARK: TY_(ParseXMLElement)
 *  Parses the given XML element.
 */
static void ParseXMLElement(TidyDocImpl* doc, Node *element, GetTokenMode mode)
{
    Lexer* lexer = doc->lexer;
    Node *node;

    /* if node is pre or has xml:space="preserve" then do so */

    if ( TY_(XMLPreserveWhiteSpace)(doc, element) )
        mode = Preformatted;

    while ((node = TY_(GetToken)(doc, mode)) != NULL)
    {
        if (node->type == EndTag &&
           node->element && element->element &&
           TY_(tmbstrcmp)(node->element, element->element) == 0)
        {
            TY_(FreeNode)( doc, node);
            element->closed = yes;
            break;
        }

        /* discard unexpected end tags */
        if (node->type == EndTag)
        {
            if (element)
                TY_(Report)(doc, element, node, UNEXPECTED_ENDTAG_IN);
            else
                TY_(Report)(doc, element, node, UNEXPECTED_ENDTAG_ERR);

            TY_(FreeNode)( doc, node);
            continue;
        }

        /* parse content on seeing start tag */
        if (node->type == StartTag)
            ParseXMLElement( doc, node, mode );

        TY_(InsertNodeAtEnd)(element, node);
    }

    /*
     if first child is text then trim initial space and
     delete text node if it is empty.
    */

    node = element->content;

    if (TY_(nodeIsText)(node) && mode != Preformatted)
    {
        if ( lexer->lexbuf[node->start] == ' ' )
        {
            node->start++;

            if (node->start >= node->end)
                TY_(DiscardElement)( doc, node );
        }
    }

    /*
     if last child is text then trim final space and
     delete the text node if it is empty
    */

    node = element->last;

    if (TY_(nodeIsText)(node) && mode != Preformatted)
    {
        if ( lexer->lexbuf[node->end - 1] == ' ' )
        {
            node->end--;

            if (node->start >= node->end)
                TY_(DiscardElement)( doc, node );
        }
    }
}


/** MARK: TY_(ParseXMLDocument)
 *  Parses the document using Tidy's XML parser.
 */
void TY_(ParseXMLDocument)(TidyDocImpl* doc)
{
    Node *node, *doctype = NULL;

    TY_(SetOptionBool)( doc, TidyXmlTags, yes );

    doc->xmlDetected = yes;

    while ((node = TY_(GetToken)(doc, IgnoreWhitespace)) != NULL)
    {
        /* discard unexpected end tags */
        if (node->type == EndTag)
        {
            TY_(Report)(doc, NULL, node, UNEXPECTED_ENDTAG);
            TY_(FreeNode)( doc, node);
            continue;
        }

         /* deal with comments etc. */
        if (InsertMisc( &doc->root, node))
            continue;

        if (node->type == DocTypeTag)
        {
            if (doctype == NULL)
            {
                TY_(InsertNodeAtEnd)( &doc->root, node);
                doctype = node;
            }
            else
            {
                TY_(Report)(doc, &doc->root, node, DISCARDING_UNEXPECTED);
                TY_(FreeNode)( doc, node);
            }
            continue;
        }

        if (node->type == StartEndTag)
        {
            TY_(InsertNodeAtEnd)( &doc->root, node);
            continue;
        }

       /* if start tag then parse element's content */
        if (node->type == StartTag)
        {
            TY_(InsertNodeAtEnd)( &doc->root, node );
            ParseXMLElement( doc, node, IgnoreWhitespace );
            continue;
        }

        TY_(Report)(doc, &doc->root, node, DISCARDING_UNEXPECTED);
        TY_(FreeNode)( doc, node);
    }

    /* ensure presence of initial <?xml version="1.0"?> */
    if ( cfgBool(doc, TidyXmlDecl) )
        TY_(FixXmlDecl)( doc );
}



/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
