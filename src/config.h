#ifndef __CONFIG_H__
#define __CONFIG_H__

/* config.h -- read config file and manage config properties
  
  (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

  config files associate a property name with a value.

  // comments can start at the beginning of a line
  # comments can start at the beginning of a line
  name: short values fit onto one line
  name: a really long value that
   continues on the next line

  property names are case insensitive and should be less than
  60 characters in length and must start at the begining of
  the line, as whitespace at the start of a line signifies a
  line continuation.

*/

#include "forward.h"
#include "tidy.h"
#include "streamio.h"

typedef Bool (ParseProperty)( TidyDoc doc, TidyOption opt );

struct _tidy_option
{
    TidyOptionId        id;
    TidyConfigCategory  category;   /* put 'em in groups */
    ctmbstr             name;       /* property name */
    TidyOptionType      type;       /* string, int or bool */
    ulong               dflt;       /* default for TidyInteger and TidyBoolean */
    ParseProperty*      parser;     /* parsing method, read-only if NULL */
    const ctmbstr*      pickList;   /* pick list */
    ctmbstr             pdflt;      /* default for TidyString */
};

typedef union
{
  ulong v;  /* Value for TidyInteger and TidyBoolean */
  char *p;  /* Value for TidyString */
} TidyOptionValue;

typedef struct _tidy_config
{
    TidyOptionValue value[ N_TIDY_OPTIONS + 1 ];     /* current config values */
    TidyOptionValue snapshot[ N_TIDY_OPTIONS + 1 ];  /* Snapshot of values to be restored later */

    /* track what tags user has defined to eliminate unnecessary searches */
    uint  defined_tags;

    uint c;           /* current char in input stream */
    StreamIn* cfgIn;  /* current input source */

} TidyConfigImpl;


/* Used to build a table of documentation cross-references. */
typedef struct {
  TidyOptionId opt;          /**< Identifier. */
  TidyOptionId const *links; /**< Cross references. Last element must be 'TidyUnknownOption'. */
} TidyOptionDoc;


TidyOption TY_(lookupOption)( ctmbstr optnam );
TidyOption TY_(getOption)( TidyOptionId optId );

TidyIterator TY_(getOptionList)( TidyDoc doc );
TidyOption TY_(getNextOption)( TidyDoc doc, TidyIterator* iter );

TidyIterator TY_(getOptionPickList)( TidyOption option );
ctmbstr TY_(getNextOptionPick)( TidyOption option, TidyIterator* iter );

const TidyOptionDoc* TY_(OptGetDocDesc)( TidyOptionId optId );

void TY_(InitConfig)( TidyDoc doc );
void TY_(FreeConfig)( TidyDoc doc );

/* Bool SetOptionValue( TidyDoc doc, TidyOptionId optId, ctmbstr val ); */
Bool TY_(SetOptionInt)( TidyDoc doc, TidyOptionId optId, ulong val );
Bool TY_(SetOptionBool)( TidyDoc doc, TidyOptionId optId, Bool val );

Bool TY_(ResetOptionToDefault)( TidyDoc doc, TidyOptionId optId );
void TY_(ResetConfigToDefault)( TidyDoc doc );
void TY_(TakeConfigSnapshot)( TidyDoc doc );
void TY_(ResetConfigToSnapshot)( TidyDoc doc );

void TY_(CopyConfig)( TidyDoc docTo, TidyDoc docFrom );

int  TY_(ParseConfigFile)( TidyDoc doc, ctmbstr cfgfil );
int  TY_(ParseConfigFileEnc)( TidyDoc doc,
                              ctmbstr cfgfil, ctmbstr charenc );

int  TY_(SaveConfigFile)( TidyDoc doc, ctmbstr cfgfil );
int  TY_(SaveConfigSink)( TidyDoc doc, TidyOutputSink* sink );

/* returns false if unknown option, missing parameter, or
   option doesn't use parameter
*/
Bool  TY_(ParseConfigOption)( TidyDoc doc, ctmbstr optnam, ctmbstr optVal );
Bool  TY_(ParseConfigValue)( TidyDoc doc, TidyOptionId optId, ctmbstr optVal );

/* ensure that char encodings are self consistent */
Bool  TY_(AdjustCharEncoding)( TidyDoc doc, int encoding );

Bool  TY_(ConfigDiffThanDefault)( TidyDoc doc );
Bool  TY_(ConfigDiffThanSnapshot)( TidyDoc doc );

int TY_(CharEncodingId)( TidyDoc doc, ctmbstr charenc );
ctmbstr TY_(CharEncodingName)( int encoding );
ctmbstr TY_(CharEncodingOptName)( int encoding );

/* void SetEmacsFilename( TidyDoc doc, ctmbstr filename ); */


#ifdef _DEBUG

/* Debug lookup functions will be type-safe and assert option type match */
ulong   TY_(_cfgGet)( TidyDoc doc, TidyOptionId optId );
Bool    TY_(_cfgGetBool)( TidyDoc doc, TidyOptionId optId );
TidyTriState TY_(_cfgGetAutoBool)( TidyDoc doc, TidyOptionId optId );
ctmbstr TY_(_cfgGetString)( TidyDoc doc, TidyOptionId optId );

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

#endif /* __CONFIG_H__ */
