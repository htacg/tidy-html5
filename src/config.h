#ifndef __CONFIG_H__
#define __CONFIG_H__

/**************************************************************************//**
 * @file
 * Read configuration files and manage configuration properties.
 *
 * Config files associate a property name with a value.
 *
 * // comments can start at the beginning of a line
 * # comments can start at the beginning of a line
 * name: short values fit onto one line
 * name: a really long value that
 *  continues on the next line
 *
 * Property names are case insensitive and should be less than 60 characters
 * in length, and must start at the begining of the line, as whitespace at
 * the start of a line signifies a line continuation.
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
#include "tidy.h"
#include "streamio.h"

/** @addtogroup internal_api */
/** @{ */


/***************************************************************************//**
 ** @defgroup configuration_options Configuration Options
 **
 ** This module organizes all of Tidy's configuration options, including
 ** picklist management, option setting and retrieval, option file utilities,
 ** and so on.
 **
 ** @{
 ******************************************************************************/


/** Determines the maximum number of items in an option's picklist. PickLists
 ** may have up to 16 items. For some reason, this limit has been hard-coded
 ** into Tidy for some time. Feel free to increase this as needed.
 */
#define TIDY_PL_SIZE 16

/** Structs of this type contain information needed in order to present
 ** picklists, relate picklist entries to public enum values, and parse
 ** strings that are accepted in order to assign the value.
 */
typedef struct PickListItem {
    ctmbstr label;      /**< PickList label for this item. */
    const int value;    /**< The option value represented by this label. */
    ctmbstr inputs[10]; /**< String values that can select this value. */
} PickListItem;

/** An array of PickListItems, fixed in size for in-code declarations. 
 ** Arrays must be populated in 0 to 10 order, as the option value is assigned
 ** based on this index and *not* on the structures' value field. It remains
 ** a best practice, however, to assign a public enum value with the proper
 ** index value.
 */
typedef const PickListItem PickListItems[TIDY_PL_SIZE];


struct _tidy_option; /* forward */

/** The TidyOptionImpl type implements the `_tidy_option` structure.
 */
typedef struct _tidy_option TidyOptionImpl;


/** This typedef describes a function that is used for parsing the input
 ** given for a particular Tidy option.
 */
typedef Bool (ParseProperty)( TidyDocImpl* doc, const TidyOptionImpl* opt );


/** This structure defines the internal representation of a Tidy option.
 */
struct _tidy_option
{
    TidyOptionId        id;
    TidyConfigCategory  category;        /**< The category of the option. */
    ctmbstr             name;            /**< The name of the option. */
    TidyOptionType      type;            /**< The date type for the option. */
    ulong               dflt;            /**< Dfeault value for TidyInteger and TidyBoolean */
    ParseProperty*      parser;          /**< Function to parse input; read-only if NULL. */
    PickListItems*      pickList;        /**< The picklist of possible values for this option. */
    ctmbstr             pdflt;           /**< Default value for TidyString. */
};


/** Stored option values can be one of two internal types.
 */
typedef union
{
  ulong v;  /* Value for TidyInteger and TidyBoolean */
  char *p;  /* Value for TidyString */
} TidyOptionValue;

/** This type is used to define a structure for keeping track of the values
 ** for each option.
 */
typedef struct _tidy_config
{
    TidyOptionValue value[ N_TIDY_OPTIONS + 1 ];     /**< Current config values. */
    TidyOptionValue snapshot[ N_TIDY_OPTIONS + 1 ];  /**< Snapshot of values to be restored later. */
    uint  defined_tags;                              /**< Tracks user-defined tags. */
    uint c;                                          /**< Current char in input stream for reading options. */
    StreamIn* cfgIn;                                 /**< Current input source for reading options.*/
} TidyConfigImpl;


/** Used to build a table of documentation cross-references.
 */
typedef struct {
  TidyOptionId opt;          /**< Identifier. */
  TidyOptionId const *links; /**< Cross references. Last element must be 'TidyUnknownOption'. */
} TidyOptionDoc;


/** Given an option name, return an instance of an option.
 */
const TidyOptionImpl* TY_(lookupOption)( ctmbstr optnam );


/** Given an option ID, return an instance of an option.
 */
const TidyOptionImpl* TY_(getOption)( TidyOptionId optId );


/** Initiates an iterator to cycle through all of the available options.
 */
TidyIterator TY_(getOptionList)( TidyDocImpl* doc );


/** Gets the next option provided by the iterator.
 */
const TidyOptionImpl* TY_(getNextOption)( TidyDocImpl* doc, TidyIterator* iter );


/** Initiates an iterator to cycle through all of the available picklist
 ** possibilities.
 */
TidyIterator TY_(getOptionPickList)( const TidyOptionImpl* option );


/** Gets the next picklist possibility provided by the iterator.
 */
ctmbstr TY_(getNextOptionPick)( const TidyOptionImpl* option, TidyIterator* iter );

#if SUPPORT_CONSOLE_APP
const TidyOptionDoc* TY_(OptGetDocDesc)( TidyOptionId optId );
#endif /* SUPPORT_CONSOLE_APP */

void TY_(InitConfig)( TidyDocImpl* doc );
void TY_(FreeConfig)( TidyDocImpl* doc );

/* Bool SetOptionValue( TidyDocImpl* doc, TidyOptionId optId, ctmbstr val ); */
Bool TY_(SetOptionInt)( TidyDocImpl* doc, TidyOptionId optId, ulong val );
Bool TY_(SetOptionBool)( TidyDocImpl* doc, TidyOptionId optId, Bool val );

Bool TY_(ResetOptionToDefault)( TidyDocImpl* doc, TidyOptionId optId );
void TY_(ResetConfigToDefault)( TidyDocImpl* doc );
void TY_(TakeConfigSnapshot)( TidyDocImpl* doc );
void TY_(ResetConfigToSnapshot)( TidyDocImpl* doc );

void TY_(CopyConfig)( TidyDocImpl* docTo, TidyDocImpl* docFrom );

int  TY_(ParseConfigFile)( TidyDocImpl* doc, ctmbstr cfgfil );
int  TY_(ParseConfigFileEnc)( TidyDocImpl* doc,
                              ctmbstr cfgfil, ctmbstr charenc );

int  TY_(SaveConfigFile)( TidyDocImpl* doc, ctmbstr cfgfil );
int  TY_(SaveConfigSink)( TidyDocImpl* doc, TidyOutputSink* sink );

/* returns false if unknown option, missing parameter, or
   option doesn't use parameter
*/
Bool  TY_(ParseConfigOption)( TidyDocImpl* doc, ctmbstr optnam, ctmbstr optVal );
Bool  TY_(ParseConfigValue)( TidyDocImpl* doc, TidyOptionId optId, ctmbstr optVal );

/* ensure that char encodings are self consistent */
Bool  TY_(AdjustCharEncoding)( TidyDocImpl* doc, int encoding );

Bool  TY_(ConfigDiffThanDefault)( TidyDocImpl* doc );
Bool  TY_(ConfigDiffThanSnapshot)( TidyDocImpl* doc );

int TY_(CharEncodingId)( TidyDocImpl* doc, ctmbstr charenc );
ctmbstr TY_(CharEncodingName)( int encoding );
ctmbstr TY_(CharEncodingOptName)( int encoding );

/* Coordinates Config update and Tags data */
void TY_(DeclareUserTag)( TidyDocImpl* doc, TidyOptionId optId,
                         uint tagType, ctmbstr name );


#ifdef _DEBUG

/* Debug lookup functions will be type-safe and assert option type match */
ulong   TY_(_cfgGet)( TidyDocImpl* doc, TidyOptionId optId );
Bool    TY_(_cfgGetBool)( TidyDocImpl* doc, TidyOptionId optId );
TidyTriState TY_(_cfgGetAutoBool)( TidyDocImpl* doc, TidyOptionId optId );
ctmbstr TY_(_cfgGetString)( TidyDocImpl* doc, TidyOptionId optId );

#define cfg(doc, id)            TY_(_cfgGet)( (doc), (id) )
#define cfgBool(doc, id)        TY_(_cfgGetBool)( (doc), (id) )
#define cfgAutoBool(doc, id)    TY_(_cfgGetAutoBool)( (doc), (id) )
#define cfgStr(doc, id)         TY_(_cfgGetString)( (doc), (id) )

#else

/* Release build macros for speed */
#define cfg(doc, id)            ((doc)->config.value[ (id) ].v)
#define cfgBool(doc, id)        ((Bool) cfg(doc, id))
#define cfgAutoBool(doc, id)    ((TidyTriState) cfg(doc, id))
#define cfgStr(doc, id)         ((ctmbstr) (doc)->config.value[ (id) ].p)

#endif /* _DEBUG */


/** @} configuration_options group */
/** @} internal_api addtogroup */


#endif /* __CONFIG_H__ */
