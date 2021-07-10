#ifndef __ATTRDICT_H__
#define __ATTRDICT_H__

/* attrdict.h -- extended attribute information

   (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
   See tidy.h for the copyright notice.

*/

#include "tidy.h"

typedef struct _AttrVersion
{
    TidyAttrId attribute;
    uint versions;
} AttrVersion;

TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_A)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_ABBR)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_ACRONYM)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_ADDRESS)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_APPLET)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_AREA)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_B)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_BASE)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_BASEFONT)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_BDO)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_BIG)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_BLOCKQUOTE)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_BODY)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_BR)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_BUTTON)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_CAPTION)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_CENTER)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_CITE)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_CODE)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_COL)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_COLGROUP)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_DD)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_DEL)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_DFN)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_DIR)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_DIV)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_DL)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_DT)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_EM)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_FIELDSET)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_FONT)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_FORM)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_FRAME)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_FRAMESET)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_H1)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_H2)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_H3)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_H4)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_H5)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_H6)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_HEAD)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_HR)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_HTML)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_I)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_IFRAME)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_IMG)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_INPUT)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_INS)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_ISINDEX)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_KBD)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_LABEL)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_LEGEND)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_LI)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_LINK)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_LISTING)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_MAP)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_MATHML)[]; /* [i_a]2 */
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_MENU)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_META)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_NEXTID)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_NOFRAMES)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_NOSCRIPT)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_OBJECT)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_OL)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_OPTGROUP)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_OPTION)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_P)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_PARAM)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_PICTURE)[]; /* Issue #151 - html5 */
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_PLAINTEXT)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_PRE)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_Q)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_RB)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_RBC)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_RP)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_RT)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_RTC)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_RUBY)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_S)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_SAMP)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_SCRIPT)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_SELECT)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_SMALL)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_SPAN)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_STRIKE)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_STRONG)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_STYLE)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_SUB)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_SUP)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_SVG)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_TABLE)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_TBODY)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_TD)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_TEXTAREA)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_TFOOT)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_TH)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_THEAD)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_TITLE)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_TR)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_TT)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_U)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_UL)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_VAR)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_XMP)[];

TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_TRACK)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_SUMMARY)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_FIGCAPTION)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_HGROUP)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_FIGURE)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_ARTICLE)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_ASIDE)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_BDI)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_NAV)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_SECTION)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_FOOTER)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_HEADER)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_DETAILS)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_DIALOG)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_COMMAND)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_MAIN)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_MARK)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_OUTPUT)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_MENUITEM)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_METER)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_PROGRESS)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_SLOT)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_TEMPLATE)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_TIME)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_DATA)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_DATALIST)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_AUDIO)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_VIDEO)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_CANVAS)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_SOURCE)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_EMBED)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_KEYGEN)[];
TY_PRIVATE extern const AttrVersion TY_(W3CAttrsFor_WBR)[];

#endif /* __ATTRDICT_H__ */
