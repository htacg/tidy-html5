/* attrask.c -- Interrogate attribute type

  (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.
  
*/

#include "tidy-int.h"
#include "tidy.h"
#include "attrs.h"

Bool TIDY_CALL tidyAttrIsHREF( TidyAttr tattr )
{
    return attrIsHREF( tattr );
}
Bool TIDY_CALL tidyAttrIsSRC( TidyAttr tattr )
{
    return attrIsSRC( tattr );
}
Bool TIDY_CALL tidyAttrIsID( TidyAttr tattr )
{
    return attrIsID( tattr );
}
Bool TIDY_CALL tidyAttrIsNAME( TidyAttr tattr )
{
    return attrIsNAME( tattr );
}
Bool TIDY_CALL tidyAttrIsSUMMARY( TidyAttr tattr )
{
    return attrIsSUMMARY( tattr );
}
Bool TIDY_CALL tidyAttrIsALT( TidyAttr tattr )
{
    return attrIsALT( tattr );
}
Bool TIDY_CALL tidyAttrIsLONGDESC( TidyAttr tattr )
{
    return attrIsLONGDESC( tattr );
}
Bool TIDY_CALL tidyAttrIsUSEMAP( TidyAttr tattr )
{
    return attrIsUSEMAP( tattr );
}
Bool TIDY_CALL tidyAttrIsISMAP( TidyAttr tattr )
{
    return attrIsISMAP( tattr );
}
Bool TIDY_CALL tidyAttrIsLANGUAGE( TidyAttr tattr )
{
    return attrIsLANGUAGE( tattr );
}
Bool TIDY_CALL tidyAttrIsTYPE( TidyAttr tattr )
{
    return attrIsTYPE( tattr );
}
Bool TIDY_CALL tidyAttrIsVALUE( TidyAttr tattr )
{
    return attrIsVALUE( tattr );
}
Bool TIDY_CALL tidyAttrIsCONTENT( TidyAttr tattr )
{
    return attrIsCONTENT( tattr );
}
Bool TIDY_CALL tidyAttrIsTITLE( TidyAttr tattr )
{
    return attrIsTITLE( tattr );
}
Bool TIDY_CALL tidyAttrIsXMLNS( TidyAttr tattr )
{
    return attrIsXMLNS( tattr );
}
Bool TIDY_CALL tidyAttrIsDATAFLD( TidyAttr tattr )
{
    return attrIsDATAFLD( tattr );
}
Bool TIDY_CALL tidyAttrIsWIDTH( TidyAttr tattr )
{
    return attrIsWIDTH( tattr );
}
Bool TIDY_CALL tidyAttrIsHEIGHT( TidyAttr tattr )
{
    return attrIsHEIGHT( tattr );
}
Bool TIDY_CALL tidyAttrIsFOR( TidyAttr tattr )
{
    return attrIsFOR( tattr );
}
Bool TIDY_CALL tidyAttrIsSELECTED( TidyAttr tattr )
{
    return attrIsSELECTED( tattr );
}
Bool TIDY_CALL tidyAttrIsCHECKED( TidyAttr tattr )
{
    return attrIsCHECKED( tattr );
}
Bool TIDY_CALL tidyAttrIsLANG( TidyAttr tattr )
{
    return attrIsLANG( tattr );
}
Bool TIDY_CALL tidyAttrIsTARGET( TidyAttr tattr )
{
    return attrIsTARGET( tattr );
}
Bool TIDY_CALL tidyAttrIsHTTP_EQUIV( TidyAttr tattr )
{
    return attrIsHTTP_EQUIV( tattr );
}
Bool TIDY_CALL tidyAttrIsREL( TidyAttr tattr )
{
    return attrIsREL( tattr );
}
Bool TIDY_CALL tidyAttrIsEvent( TidyAttr tattr )
{
    return TY_(attrIsEvent)( tattr );
}
Bool TIDY_CALL tidyAttrIsOnMOUSEMOVE( TidyAttr tattr )
{
    return attrIsOnMOUSEMOVE( tattr );
}
Bool TIDY_CALL tidyAttrIsOnMOUSEDOWN( TidyAttr tattr )
{
    return attrIsOnMOUSEDOWN( tattr );
}
Bool TIDY_CALL tidyAttrIsOnMOUSEUP( TidyAttr tattr )
{
    return attrIsOnMOUSEUP( tattr );
}
Bool TIDY_CALL tidyAttrIsOnCLICK( TidyAttr tattr )
{
    return attrIsOnCLICK( tattr );
}
Bool TIDY_CALL tidyAttrIsOnMOUSEOVER( TidyAttr tattr )
{
    return attrIsOnMOUSEOVER( tattr );
}
Bool TIDY_CALL tidyAttrIsOnMOUSEOUT( TidyAttr tattr )
{
    return attrIsOnMOUSEOUT( tattr );
}
Bool TIDY_CALL tidyAttrIsOnKEYDOWN( TidyAttr tattr )
{
    return attrIsOnKEYDOWN( tattr );
}
Bool TIDY_CALL tidyAttrIsOnKEYUP( TidyAttr tattr )
{
    return attrIsOnKEYUP( tattr );
}
Bool TIDY_CALL tidyAttrIsOnKEYPRESS( TidyAttr tattr )
{
    return attrIsOnKEYPRESS( tattr );
}
Bool TIDY_CALL tidyAttrIsOnFOCUS( TidyAttr tattr )
{
    return attrIsOnFOCUS( tattr );
}
Bool TIDY_CALL tidyAttrIsOnBLUR( TidyAttr tattr )
{
    return attrIsOnBLUR( tattr );
}
Bool TIDY_CALL tidyAttrIsBGCOLOR( TidyAttr tattr )
{
    return attrIsBGCOLOR( tattr );
}
Bool TIDY_CALL tidyAttrIsLINK( TidyAttr tattr )
{
    return attrIsLINK( tattr );
}
Bool TIDY_CALL tidyAttrIsALINK( TidyAttr tattr )
{
    return attrIsALINK( tattr );
}
Bool TIDY_CALL tidyAttrIsVLINK( TidyAttr tattr )
{
    return attrIsVLINK( tattr );
}
Bool TIDY_CALL tidyAttrIsTEXT( TidyAttr tattr )
{
    return attrIsTEXT( tattr );
}
Bool TIDY_CALL tidyAttrIsSTYLE( TidyAttr tattr )
{
    return attrIsSTYLE( tattr );
}
Bool TIDY_CALL tidyAttrIsABBR( TidyAttr tattr )
{
    return attrIsABBR( tattr );
}
Bool TIDY_CALL tidyAttrIsCOLSPAN( TidyAttr tattr )
{
    return attrIsCOLSPAN( tattr );
}
Bool TIDY_CALL tidyAttrIsROWSPAN( TidyAttr tattr )
{
    return attrIsROWSPAN( tattr );
}

/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
