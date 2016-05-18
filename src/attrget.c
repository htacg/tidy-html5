/* attrget.c -- Locate attribute value by type

  (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.
  
*/

#include "tidy-int.h"
#include "tags.h"
#include "attrs.h"
#include "tidy.h"

TidyAttr TIDY_CALL tidyAttrGetById( TidyNode tnod, TidyAttrId attId )
{
    return TY_(AttrGetById)( tnod, attId );
}
TidyAttr TIDY_CALL tidyAttrGetHREF( TidyNode tnod )
{
    return attrGetHREF( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetSRC( TidyNode tnod )
{
    return attrGetSRC( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetID( TidyNode tnod )
{
    return attrGetID( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetNAME( TidyNode tnod )
{
    return attrGetNAME( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetSUMMARY( TidyNode tnod )
{
    return attrGetSUMMARY( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetALT( TidyNode tnod )
{
    return attrGetALT( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetLONGDESC( TidyNode tnod )
{
    return attrGetLONGDESC( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetUSEMAP( TidyNode tnod )
{
    return attrGetUSEMAP( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetISMAP( TidyNode tnod )
{
    return attrGetISMAP( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetLANGUAGE( TidyNode tnod )
{
    return attrGetLANGUAGE( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetTYPE( TidyNode tnod )
{
    return attrGetTYPE( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetVALUE( TidyNode tnod )
{
    return attrGetVALUE( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetCONTENT( TidyNode tnod )
{
    return attrGetCONTENT( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetTITLE( TidyNode tnod )
{
    return attrGetTITLE( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetXMLNS( TidyNode tnod )
{
    return attrGetXMLNS( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetDATAFLD( TidyNode tnod )
{
    return attrGetDATAFLD( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetWIDTH( TidyNode tnod )
{
    return attrGetWIDTH( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetHEIGHT( TidyNode tnod )
{
    return attrGetHEIGHT( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetFOR( TidyNode tnod )
{
    return attrGetFOR( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetSELECTED( TidyNode tnod )
{
    return attrGetSELECTED( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetCHECKED( TidyNode tnod )
{
    return attrGetCHECKED( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetLANG( TidyNode tnod )
{
    return attrGetLANG( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetTARGET( TidyNode tnod )
{
    return attrGetTARGET( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetHTTP_EQUIV( TidyNode tnod )
{
    return attrGetHTTP_EQUIV( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetREL( TidyNode tnod )
{
    return attrGetREL( tnod );
}

TidyAttr TIDY_CALL tidyAttrGetOnMOUSEMOVE( TidyNode tnod )
{
    return attrGetOnMOUSEMOVE( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetOnMOUSEDOWN( TidyNode tnod )
{
    return attrGetOnMOUSEDOWN( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetOnMOUSEUP( TidyNode tnod )
{
    return attrGetOnMOUSEUP( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetOnCLICK( TidyNode tnod )
{
    return attrGetOnCLICK( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetOnMOUSEOVER( TidyNode tnod )
{
    return attrGetOnMOUSEOVER( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetOnMOUSEOUT( TidyNode tnod )
{
    return attrGetOnMOUSEOUT( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetOnKEYDOWN( TidyNode tnod )
{
    return attrGetOnKEYDOWN( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetOnKEYUP( TidyNode tnod )
{
    return attrGetOnKEYUP( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetOnKEYPRESS( TidyNode tnod )
{
    return attrGetOnKEYPRESS( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetOnFOCUS( TidyNode tnod )
{
    return attrGetOnFOCUS( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetOnBLUR( TidyNode tnod )
{
    return attrGetOnBLUR( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetBGCOLOR( TidyNode tnod )
{
    return attrGetBGCOLOR( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetLINK( TidyNode tnod )
{
    return attrGetLINK( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetALINK( TidyNode tnod )
{
    return attrGetALINK( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetVLINK( TidyNode tnod )
{
    return attrGetVLINK( tnod );
}

TidyAttr TIDY_CALL tidyAttrGetTEXT( TidyNode tnod )
{
    return attrGetTEXT( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetSTYLE( TidyNode tnod )
{
    return attrGetSTYLE( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetABBR( TidyNode tnod )
{
    return attrGetABBR( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetCOLSPAN( TidyNode tnod )
{
    return attrGetCOLSPAN( tnod );
}
TidyAttr TIDY_CALL tidyAttrGetROWSPAN( TidyNode tnod )
{
    return attrGetROWSPAN( tnod );
}

/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
