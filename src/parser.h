#ifndef __PARSER_H__
#define __PARSER_H__

/**************************************************************************//**
 * @file
 * HTML and XML Parsers.
 *
 * Tidy's HTML parser corrects many conditions and enforces certain user
 * preferences during the parsing process. The XML parser produces a tree
 * of nodes useful to Tidy but also suitable for use in other XML processing
 * applications.
 *
 * @author  HTACG, et al (consult git log)
 *
 * @copyright
 *     Copyright (c) 1998-2017 World Wide Web Consortium (Massachusetts
 *     Institute of Technology, European Research Consortium for Informatics
 *     and Mathematics, Keio University) and HTACG.
 * @par
 *     All Rights Reserved.
 * @par
 *     See `tidy.h` for the complete license.
 *
 * @date Additional updates: consult git log
 *
 ******************************************************************************/

#include "forward.h"

/** @addtogroup internal_api */
/** @{ */


/***************************************************************************//**
 ** @defgroup parser_h HTML and XML Parsing
 **
 ** These functions and structures form the internal API for document
 ** parsing.
 **
 ** @{
 ******************************************************************************/


/**
 *  Is used to perform a node integrity check recursively after parsing
 *  an HTML or XML document.
 *  @note Actual performance of this check can be disabled by defining the
 *  macro NO_NODE_INTEGRITY_CHECK.
 *  @param node The root node for the integrity check.
 *  @returns Returns yes or no indicating integrity of the node structure.
 */
Bool TY_(CheckNodeIntegrity)(Node *node);


/**
 *  Indicates whether or not a text node ends with a space or newline.
 *  @note Implementation of this method is found in `pprint.c` for
 *  some reason.
 *  @param lexer A reference to the lexer used to lex the document.
 *  @param node The node to check.
 *  @returns The result of the check.
 */
Bool TY_(TextNodeEndWithSpace)( Lexer *lexer, Node *node );


/**
 *  Used to check if a node uses CM_NEW, which determines how attributes
 *  without values should be printed. This was introduced to deal with
 *  user-defined tags e.g. ColdFusion.
 *  @param node The node to check.
 *  @returns The result of the check.
 */
Bool TY_(IsNewNode)(Node *node);


/**
 *  Transforms a given node to another element, for example, from a `p`
 *  to a `br`.
 *  @param doc The document which the node belongs to.
 *  @param node The node to coerce.
 *  @param tid The tag type to coerce the node into.
 *  @param obsolete If the old node was obsolete, a report will be generated.
 *  @param expected If the old node was not expected to be found in this
 *    particular location, a report will be generated.
 */
void TY_(CoerceNode)(TidyDocImpl* doc, Node *node, TidyTagId tid, Bool obsolete, Bool expected);


/**
 *  Extract a node and its children from a markup tree.
 *  @param node The node to remove.
 *  @returns Returns the removed node.
 */
Node *TY_(RemoveNode)(Node *node);


/**
 *  Remove node from markup tree and discard it.
 *  @param doc The Tidy document from which to discarb the node.
 *  @param element The node to discard.
 *  @returns Returns the next node.
 */
Node *TY_(DiscardElement)( TidyDocImpl* doc, Node *element);


/**
 *  Insert node into markup tree as the firt element of content of element.
 *  @param element The new destination node.
 *  @param node The node to insert.
 */
void TY_(InsertNodeAtStart)(Node *element, Node *node);


/**
 *  Insert node into markup tree as the last element of content of element.
 *  @param element The new destination node.
 *  @param node The node to insert.
 */
void TY_(InsertNodeAtEnd)(Node *element, Node *node);


/**
 *  Insert node into markup tree before element.
 *  @param element The node before which the node is inserted.
 *  @param node The node to insert.
 */
void TY_(InsertNodeBeforeElement)(Node *element, Node *node);


/**
 *  Insert node into markup tree after element.
 *  @param element The node after which the node is inserted.
 *  @param node The node to insert.
 */
void TY_(InsertNodeAfterElement)(Node *element, Node *node);


/**
 *  Trims a single, empty element, returning the next node.
 *  @param doc The Tidy document.
 *  @param element The element to trim.
 *  @returns Returns the next node.
 */
Node *TY_(TrimEmptyElement)( TidyDocImpl* doc, Node *element );


/**
 *  Trims a tree of empty elements recursively, returning the next node.
 *  @param doc The Tidy document.
 *  @param node The element to trim.
 *  @returns Returns the next node.
 */
Node* TY_(DropEmptyElements)(TidyDocImpl* doc, Node* node);


/**
 *  Indicates whether or not a text node is blank, meaning that it consists
 *  of nothing, or a single space.
 *  @param lexer The lexer used to lex the document.
 *  @param node The node to test.
 *  @returns Returns the result of the test.
 */
Bool TY_(IsBlank)(Lexer *lexer, Node *node);


/**
 *  Indicates whether or not a node is declared as containing javascript
 *  code.
 *  @param node The node to test.
 *  @returns Returns the result of the test.
 */
Bool TY_(IsJavaScript)(Node *node);


/**
 *  Parses a document after lexing using the HTML parser. It begins by properly
 *  configuring the overall HTML structure, and subsequently processes all
 *  remaining nodes. HTML is the root node.
 *  @param doc The Tidy document.
 */
void TY_(ParseDocument)( TidyDocImpl* doc );


/**
 *  Indicates whether or not whitespace is to be preserved in XHTML/XML
 *  documents.
 *  @param doc The Tidy document.
 *  @param element The node to test.
 *  @returns Returns the result of the test.
 */
Bool TY_(XMLPreserveWhiteSpace)( TidyDocImpl* doc, Node *element );


/**
 *  Parses a document after lexing using the XML parser.
 *  @param doc The Tidy document.
 */
void TY_(ParseXMLDocument)( TidyDocImpl* doc );


/** @} end parser_h group */
/** @} end internal_api group */

#endif /* __PARSER_H__ */

