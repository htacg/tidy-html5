/* tags.c -- recognize HTML tags

  (c) 1998-2008 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

  The HTML tags are stored as 8 bit ASCII strings.

*/

#include "tidy-int.h"
#include "message.h"
#include "tmbstr.h"
#if !defined(NDEBUG) && defined(_MSC_VER)
#include "sprtf.h"
#endif
/* Attribute checking methods */
static CheckAttribs CheckIMG;
static CheckAttribs CheckLINK;
static CheckAttribs CheckAREA;
static CheckAttribs CheckTABLE;
static CheckAttribs CheckCaption;
static CheckAttribs CheckHTML;

#define VERS_ELEM_A          (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_ABBR       (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_ACRONYM    (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|xxxx|xxxx)
#define VERS_ELEM_ADDRESS    (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_APPLET     (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx)
#define VERS_ELEM_AREA       (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_B          (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_BASE       (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_BASEFONT   (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx)
#define VERS_ELEM_BDO        (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_BIG        (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|xxxx|xxxx)
#define VERS_ELEM_BLOCKQUOTE (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_BODY       (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_BR         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_BUTTON     (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_CAPTION    (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_CENTER     (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx)
#define VERS_ELEM_CITE       (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_CODE       (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_COL        (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_COLGROUP   (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_DD         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_DEL        (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_DFN        (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_DIR        (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx)
#define VERS_ELEM_DIV        (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_DL         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_DT         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_EM         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_FIELDSET   (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_FONT       (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx)
#define VERS_ELEM_FORM       (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_FRAME      (xxxx|xxxx|xxxx|xxxx|xxxx|H40F|H41F|X10F|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx)
#define VERS_ELEM_FRAMESET   (xxxx|xxxx|xxxx|xxxx|xxxx|H40F|H41F|X10F|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx)
#define VERS_ELEM_H1         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_H2         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_H3         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_H4         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_H5         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_H6         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_HEAD       (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_HR         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_HTML       (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_I          (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_IFRAME     (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_IMG        (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_INPUT      (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_INS        (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_ISINDEX    (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx)
#define VERS_ELEM_KBD        (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_LABEL      (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_LEGEND     (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_LI         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_LINK       (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_LISTING    (HT20|HT32|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx)
#define VERS_ELEM_MAP        (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_MATHML     (xxxx|xxxx|xxxx|H41T|X10T|xxxx|H41F|X10F|xxxx|H41S|X10S|XH11|xxxx|HT50|XH50) /* [i_a]2 */
#define VERS_ELEM_MENU       (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_META       (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_NEXTID     (HT20|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx)
#define VERS_ELEM_NOFRAMES   (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx)
#define VERS_ELEM_NOSCRIPT   (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_OBJECT     (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_OL         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_OPTGROUP   (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_OPTION     (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_P          (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_PARAM      (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_PICTURE    (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_PLAINTEXT  (HT20|HT32|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx)
#define VERS_ELEM_PRE        (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_Q          (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_RB         (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|XH11|xxxx|xxxx|xxxx)
#define VERS_ELEM_RBC        (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|XH11|xxxx|xxxx|xxxx)
#define VERS_ELEM_RP         (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_RT         (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_RTC        (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|XH11|xxxx|xxxx|xxxx)
#define VERS_ELEM_RUBY       (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_S          (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_SAMP       (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_SCRIPT     (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_SELECT     (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_SMALL      (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_SPAN       (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_STRIKE     (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx)
#define VERS_ELEM_STRONG     (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_STYLE      (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_SUB        (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_SUP        (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_SVG        (xxxx|xxxx|xxxx|H41T|X10T|xxxx|H41F|X10F|xxxx|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_TABLE      (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_TBODY      (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_TD         (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_TEXTAREA   (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_TFOOT      (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_TH         (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_THEAD      (xxxx|xxxx|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|HT50|XH50)
#define VERS_ELEM_TITLE      (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_TR         (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_TT         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|xxxx|xxxx|xxxx)
#define VERS_ELEM_U          (xxxx|HT32|H40T|H41T|X10T|H40F|H41F|X10F|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_UL         (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_VAR        (HT20|HT32|H40T|H41T|X10T|H40F|H41F|X10F|H40S|H41S|X10S|XH11|XB10|HT50|XH50)
#define VERS_ELEM_XMP        (HT20|HT32|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx)

#define VERS_ELEM_ARTICLE    (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_ASIDE      (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_AUDIO      (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_BDI        (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_CANVAS     (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_COMMAND    (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_DATALIST   (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_DETAILS    (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_DIALOG     (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_EMBED      (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_FIGCAPTION (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_FIGURE     (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_FOOTER     (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_HEADER     (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_HGROUP     (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_KEYGEN     (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_MAIN       (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_MARK       (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_MENUITEM   (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_KEYGEN     (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_METER      (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_NAV        (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_OUTPUT     (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_PROGRESS   (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_SECTION    (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_SOURCE     (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_SUMMARY    (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_TEMPLATE   (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_TIME       (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_TRACK      (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_VIDEO      (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)
#define VERS_ELEM_WBR        (xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|HT50|XH50)

/*\ 
 * Issue #167 & #169 & #232
 * Tidy defaults to HTML5 mode
 * but allow this table to be ADJUSTED if NOT HTML5
 * was static const Dict tag_defs[] = 
\*/
static Dict tag_defs[] =
{
  { TidyTag_UNKNOWN,    "unknown!",   VERS_UNKNOWN,         NULL,                       (0),                                           NULL,          NULL           },

  /* W3C defined elements */
  { TidyTag_A,          "a",          VERS_ELEM_A,          &TY_(W3CAttrsFor_A)[0],          (CM_INLINE|CM_BLOCK|CM_MIXED),                 TY_(ParseBlock),    NULL           }, /* Issue #167 & #169 - default HTML5 */
  { TidyTag_ABBR,       "abbr",       VERS_ELEM_ABBR,       &TY_(W3CAttrsFor_ABBR)[0],       (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_ACRONYM,    "acronym",    VERS_ELEM_ACRONYM,    &TY_(W3CAttrsFor_ACRONYM)[0],    (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_ADDRESS,    "address",    VERS_ELEM_ADDRESS,    &TY_(W3CAttrsFor_ADDRESS)[0],    (CM_BLOCK),                                    TY_(ParseBlock),    NULL           },
  { TidyTag_APPLET,     "applet",     VERS_ELEM_APPLET,     &TY_(W3CAttrsFor_APPLET)[0],     (CM_OBJECT|CM_IMG|CM_INLINE|CM_PARAM),         TY_(ParseBlock),    NULL           },
  { TidyTag_AREA,       "area",       VERS_ELEM_AREA,       &TY_(W3CAttrsFor_AREA)[0],       (CM_BLOCK|CM_EMPTY),                           TY_(ParseEmpty),    CheckAREA      },
  { TidyTag_B,          "b",          VERS_ELEM_B,          &TY_(W3CAttrsFor_B)[0],          (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_BASE,       "base",       VERS_ELEM_BASE,       &TY_(W3CAttrsFor_BASE)[0],       (CM_HEAD|CM_EMPTY),                            TY_(ParseEmpty),    NULL           },
  { TidyTag_BASEFONT,   "basefont",   VERS_ELEM_BASEFONT,   &TY_(W3CAttrsFor_BASEFONT)[0],   (CM_INLINE|CM_EMPTY),                          TY_(ParseEmpty),    NULL           },
  { TidyTag_BDO,        "bdo",        VERS_ELEM_BDO,        &TY_(W3CAttrsFor_BDO)[0],        (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_BIG,        "big",        VERS_ELEM_BIG,        &TY_(W3CAttrsFor_BIG)[0],        (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_BLOCKQUOTE, "blockquote", VERS_ELEM_BLOCKQUOTE, &TY_(W3CAttrsFor_BLOCKQUOTE)[0], (CM_BLOCK),                                    TY_(ParseBlock),    NULL           },
  { TidyTag_BODY,       "body",       VERS_ELEM_BODY,       &TY_(W3CAttrsFor_BODY)[0],       (CM_HTML|CM_OPT|CM_OMITST),                    TY_(ParseBody),     NULL           },
  { TidyTag_BR,         "br",         VERS_ELEM_BR,         &TY_(W3CAttrsFor_BR)[0],         (CM_INLINE|CM_EMPTY),                          TY_(ParseEmpty),    NULL           },
  { TidyTag_BUTTON,     "button",     VERS_ELEM_BUTTON,     &TY_(W3CAttrsFor_BUTTON)[0],     (CM_INLINE),                                   TY_(ParseBlock),    NULL           },
  { TidyTag_CAPTION,    "caption",    VERS_ELEM_CAPTION,    &TY_(W3CAttrsFor_CAPTION)[0],    (CM_TABLE),                                    TY_(ParseBlock),    CheckCaption   },
  { TidyTag_CENTER,     "center",     VERS_ELEM_CENTER,     &TY_(W3CAttrsFor_CENTER)[0],     (CM_BLOCK),                                    TY_(ParseBlock),    NULL           },
  { TidyTag_CITE,       "cite",       VERS_ELEM_CITE,       &TY_(W3CAttrsFor_CITE)[0],       (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_CODE,       "code",       VERS_ELEM_CODE,       &TY_(W3CAttrsFor_CODE)[0],       (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_COL,        "col",        VERS_ELEM_COL,        &TY_(W3CAttrsFor_COL)[0],        (CM_TABLE|CM_EMPTY),                           TY_(ParseEmpty),    NULL           },
  { TidyTag_COLGROUP,   "colgroup",   VERS_ELEM_COLGROUP,   &TY_(W3CAttrsFor_COLGROUP)[0],   (CM_TABLE|CM_OPT),                             TY_(ParseColGroup), NULL           },
  { TidyTag_DD,         "dd",         VERS_ELEM_DD,         &TY_(W3CAttrsFor_DD)[0],         (CM_DEFLIST|CM_OPT|CM_NO_INDENT),              TY_(ParseBlock),    NULL           },
  { TidyTag_DEL,        "del",        VERS_ELEM_DEL,        &TY_(W3CAttrsFor_DEL)[0],        (CM_INLINE|CM_BLOCK|CM_MIXED),                 TY_(ParseInline),   NULL           },
  { TidyTag_DFN,        "dfn",        VERS_ELEM_DFN,        &TY_(W3CAttrsFor_DFN)[0],        (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_DIR,        "dir",        VERS_ELEM_DIR,        &TY_(W3CAttrsFor_DIR)[0],        (CM_BLOCK|CM_OBSOLETE),                        TY_(ParseList),     NULL           },
  { TidyTag_DIV,        "div",        VERS_ELEM_DIV,        &TY_(W3CAttrsFor_DIV)[0],        (CM_BLOCK),                                    TY_(ParseBlock),    NULL           },
  { TidyTag_DL,         "dl",         VERS_ELEM_DL,         &TY_(W3CAttrsFor_DL)[0],         (CM_BLOCK),                                    TY_(ParseDefList),  NULL           },
  { TidyTag_DT,         "dt",         VERS_ELEM_DT,         &TY_(W3CAttrsFor_DT)[0],         (CM_DEFLIST|CM_OPT|CM_NO_INDENT),              TY_(ParseInline),   NULL           },
  { TidyTag_EM,         "em",         VERS_ELEM_EM,         &TY_(W3CAttrsFor_EM)[0],         (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_FIELDSET,   "fieldset",   VERS_ELEM_FIELDSET,   &TY_(W3CAttrsFor_FIELDSET)[0],   (CM_BLOCK),                                    TY_(ParseBlock),    NULL           },
  { TidyTag_FONT,       "font",       VERS_ELEM_FONT,       &TY_(W3CAttrsFor_FONT)[0],       (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  /* HTML5 Form Elements has several new elements and attributes - datalist keygen output */
  { TidyTag_FORM,       "form",       VERS_ELEM_FORM,       &TY_(W3CAttrsFor_FORM)[0],       (CM_BLOCK),                                    TY_(ParseBlock),    NULL           },
  { TidyTag_FRAME,      "frame",      VERS_ELEM_FRAME,      &TY_(W3CAttrsFor_FRAME)[0],      (CM_FRAMES|CM_EMPTY),                          TY_(ParseEmpty),    NULL           },
  { TidyTag_FRAMESET,   "frameset",   VERS_ELEM_FRAMESET,   &TY_(W3CAttrsFor_FRAMESET)[0],   (CM_HTML|CM_FRAMES),                           TY_(ParseFrameSet), NULL           },
  { TidyTag_H1,         "h1",         VERS_ELEM_H1,         &TY_(W3CAttrsFor_H1)[0],         (CM_BLOCK|CM_HEADING),                         TY_(ParseInline),   NULL           },
  { TidyTag_H2,         "h2",         VERS_ELEM_H2,         &TY_(W3CAttrsFor_H2)[0],         (CM_BLOCK|CM_HEADING),                         TY_(ParseInline),   NULL           },
  { TidyTag_H3,         "h3",         VERS_ELEM_H3,         &TY_(W3CAttrsFor_H3)[0],         (CM_BLOCK|CM_HEADING),                         TY_(ParseInline),   NULL           },
  { TidyTag_H4,         "h4",         VERS_ELEM_H4,         &TY_(W3CAttrsFor_H4)[0],         (CM_BLOCK|CM_HEADING),                         TY_(ParseInline),   NULL           },
  { TidyTag_H5,         "h5",         VERS_ELEM_H5,         &TY_(W3CAttrsFor_H5)[0],         (CM_BLOCK|CM_HEADING),                         TY_(ParseInline),   NULL           },
  { TidyTag_H6,         "h6",         VERS_ELEM_H6,         &TY_(W3CAttrsFor_H6)[0],         (CM_BLOCK|CM_HEADING),                         TY_(ParseInline),   NULL           },
  { TidyTag_HEAD,       "head",       VERS_ELEM_HEAD,       &TY_(W3CAttrsFor_HEAD)[0],       (CM_HTML|CM_OPT|CM_OMITST),                    TY_(ParseHead),     NULL           },
  { TidyTag_HR,         "hr",         VERS_ELEM_HR,         &TY_(W3CAttrsFor_HR)[0],         (CM_BLOCK|CM_EMPTY),                           TY_(ParseEmpty),    NULL           },
  { TidyTag_HTML,       "html",       VERS_ELEM_HTML,       &TY_(W3CAttrsFor_HTML)[0],       (CM_HTML|CM_OPT|CM_OMITST),                    TY_(ParseHTML),     CheckHTML      },
  { TidyTag_I,          "i",          VERS_ELEM_I,          &TY_(W3CAttrsFor_I)[0],          (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_IFRAME,     "iframe",     VERS_ELEM_IFRAME,     &TY_(W3CAttrsFor_IFRAME)[0],     (CM_INLINE),                                   TY_(ParseBlock),    NULL           },
  { TidyTag_IMG,        "img",        VERS_ELEM_IMG,        &TY_(W3CAttrsFor_IMG)[0],        (CM_INLINE|CM_IMG|CM_EMPTY),                   TY_(ParseEmpty),    CheckIMG       },
  { TidyTag_INPUT,      "input",      VERS_ELEM_INPUT,      &TY_(W3CAttrsFor_INPUT)[0],      (CM_INLINE|CM_IMG|CM_EMPTY),                   TY_(ParseEmpty),    NULL           },
  { TidyTag_INS,        "ins",        VERS_ELEM_INS,        &TY_(W3CAttrsFor_INS)[0],        (CM_INLINE|CM_BLOCK|CM_MIXED),                 TY_(ParseInline),   NULL           },
  { TidyTag_ISINDEX,    "isindex",    VERS_ELEM_ISINDEX,    &TY_(W3CAttrsFor_ISINDEX)[0],    (CM_BLOCK|CM_EMPTY),                           TY_(ParseEmpty),    NULL           },
  { TidyTag_KBD,        "kbd",        VERS_ELEM_KBD,        &TY_(W3CAttrsFor_KBD)[0],        (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_LABEL,      "label",      VERS_ELEM_LABEL,      &TY_(W3CAttrsFor_LABEL)[0],      (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_LEGEND,     "legend",     VERS_ELEM_LEGEND,     &TY_(W3CAttrsFor_LEGEND)[0],     (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_LI,         "li",         VERS_ELEM_LI,         &TY_(W3CAttrsFor_LI)[0],         (CM_LIST|CM_OPT|CM_NO_INDENT),                 TY_(ParseBlock),    NULL           },
  { TidyTag_LINK,       "link",       VERS_ELEM_LINK,       &TY_(W3CAttrsFor_LINK)[0],       (CM_HEAD|CM_BLOCK|CM_EMPTY),                   TY_(ParseEmpty),    CheckLINK      },
  { TidyTag_LISTING,    "listing",    VERS_ELEM_LISTING,    &TY_(W3CAttrsFor_LISTING)[0],    (CM_BLOCK|CM_OBSOLETE),                        TY_(ParsePre),      NULL           },
  { TidyTag_MAP,        "map",        VERS_ELEM_MAP,        &TY_(W3CAttrsFor_MAP)[0],        (CM_INLINE),                                   TY_(ParseBlock),    NULL           },
  { TidyTag_MATHML,     "math",       VERS_ELEM_MATHML,     &TY_(W3CAttrsFor_MATHML)[0],     (CM_INLINE|CM_BLOCK|CM_MIXED),                 TY_(ParseNamespace),NULL           }, /* [i_a]2 */
  /* { TidyTag_MENU,       "menu",       VERS_ELEM_MENU,       &TY_(W3CAttrsFor_MENU)[0],       (CM_BLOCK|CM_OBSOLETE),                        TY_(ParseList),     NULL           }, */
  { TidyTag_META,       "meta",       VERS_ELEM_META,       &TY_(W3CAttrsFor_META)[0],       (CM_HEAD|CM_BLOCK|CM_EMPTY),                   TY_(ParseEmpty),    NULL           },
  { TidyTag_NOFRAMES,   "noframes",   VERS_ELEM_NOFRAMES,   &TY_(W3CAttrsFor_NOFRAMES)[0],   (CM_BLOCK|CM_FRAMES),                          TY_(ParseNoFrames), NULL           },
  { TidyTag_NOSCRIPT,   "noscript",   VERS_ELEM_NOSCRIPT,   &TY_(W3CAttrsFor_NOSCRIPT)[0],   (CM_HEAD|CM_BLOCK|CM_INLINE|CM_MIXED),         TY_(ParseBlock),    NULL           },
  { TidyTag_OBJECT,     "object",     VERS_ELEM_OBJECT,     &TY_(W3CAttrsFor_OBJECT)[0],     (CM_OBJECT|CM_IMG|CM_INLINE|CM_PARAM),         TY_(ParseBlock),    NULL           },
  { TidyTag_OL,         "ol",         VERS_ELEM_OL,         &TY_(W3CAttrsFor_OL)[0],         (CM_BLOCK),                                    TY_(ParseList),     NULL           },
  { TidyTag_OPTGROUP,   "optgroup",   VERS_ELEM_OPTGROUP,   &TY_(W3CAttrsFor_OPTGROUP)[0],   (CM_FIELD|CM_OPT),                             TY_(ParseOptGroup), NULL           },
  { TidyTag_OPTION,     "option",     VERS_ELEM_OPTION,     &TY_(W3CAttrsFor_OPTION)[0],     (CM_FIELD|CM_OPT),                             TY_(ParseText),     NULL           },
  { TidyTag_P,          "p",          VERS_ELEM_P,          &TY_(W3CAttrsFor_P)[0],          (CM_BLOCK|CM_OPT),                             TY_(ParseInline),   NULL           },
  { TidyTag_PARAM,      "param",      VERS_ELEM_PARAM,      &TY_(W3CAttrsFor_PARAM)[0],      (CM_INLINE|CM_EMPTY),                          TY_(ParseEmpty),    NULL           },
  { TidyTag_PICTURE,    "picture",    VERS_ELEM_PICTURE,    &TY_(W3CAttrsFor_PICTURE)[0],    (CM_INLINE),                                   TY_(ParseInline),   NULL           }, /* Issue #151 html5 */
  { TidyTag_PLAINTEXT,  "plaintext",  VERS_ELEM_PLAINTEXT,  &TY_(W3CAttrsFor_PLAINTEXT)[0],  (CM_BLOCK|CM_OBSOLETE),                        TY_(ParsePre),      NULL           },
  { TidyTag_PRE,        "pre",        VERS_ELEM_PRE,        &TY_(W3CAttrsFor_PRE)[0],        (CM_BLOCK),                                    TY_(ParsePre),      NULL           },
  { TidyTag_Q,          "q",          VERS_ELEM_Q,          &TY_(W3CAttrsFor_Q)[0],          (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_RB,         "rb",         VERS_ELEM_RB,         &TY_(W3CAttrsFor_RB)[0],         (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_RBC,        "rbc",        VERS_ELEM_RBC,        &TY_(W3CAttrsFor_RBC)[0],        (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_RP,         "rp",         VERS_ELEM_RP,         &TY_(W3CAttrsFor_RP)[0],         (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_RT,         "rt",         VERS_ELEM_RT,         &TY_(W3CAttrsFor_RT)[0],         (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_RTC,        "rtc",        VERS_ELEM_RTC,        &TY_(W3CAttrsFor_RTC)[0],        (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_RUBY,       "ruby",       VERS_ELEM_RUBY,       &TY_(W3CAttrsFor_RUBY)[0],       (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_S,          "s",          VERS_ELEM_S,          &TY_(W3CAttrsFor_S)[0],          (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_SAMP,       "samp",       VERS_ELEM_SAMP,       &TY_(W3CAttrsFor_SAMP)[0],       (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_SCRIPT,     "script",     VERS_ELEM_SCRIPT,     &TY_(W3CAttrsFor_SCRIPT)[0],     (CM_HEAD|CM_MIXED|CM_BLOCK|CM_INLINE),         TY_(ParseScript),   NULL           },
  { TidyTag_SELECT,     "select",     VERS_ELEM_SELECT,     &TY_(W3CAttrsFor_SELECT)[0],     (CM_INLINE|CM_FIELD),                          TY_(ParseSelect),   NULL           },
  { TidyTag_SMALL,      "small",      VERS_ELEM_SMALL,      &TY_(W3CAttrsFor_SMALL)[0],      (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_SPAN,       "span",       VERS_ELEM_SPAN,       &TY_(W3CAttrsFor_SPAN)[0],       (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_STRIKE,     "strike",     VERS_ELEM_STRIKE,     &TY_(W3CAttrsFor_STRIKE)[0],     (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_STRONG,     "strong",     VERS_ELEM_STRONG,     &TY_(W3CAttrsFor_STRONG)[0],     (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_STYLE,      "style",      VERS_ELEM_STYLE,      &TY_(W3CAttrsFor_STYLE)[0],      (CM_HEAD|CM_BLOCK),                            TY_(ParseScript),   NULL           },
  { TidyTag_SUB,        "sub",        VERS_ELEM_SUB,        &TY_(W3CAttrsFor_SUB)[0],        (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_SUP,        "sup",        VERS_ELEM_SUP,        &TY_(W3CAttrsFor_SUP)[0],        (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_SVG,        "svg",        VERS_ELEM_SVG,        &TY_(W3CAttrsFor_SVG)[0],        (CM_INLINE|CM_BLOCK|CM_MIXED),                 TY_(ParseNamespace),NULL           },
  { TidyTag_TABLE,      "table",      VERS_ELEM_TABLE,      &TY_(W3CAttrsFor_TABLE)[0],      (CM_BLOCK),                                    TY_(ParseTableTag), CheckTABLE     },
  { TidyTag_TBODY,      "tbody",      VERS_ELEM_TBODY,      &TY_(W3CAttrsFor_TBODY)[0],      (CM_TABLE|CM_ROWGRP|CM_OPT),                   TY_(ParseRowGroup), NULL           },
  { TidyTag_TD,         "td",         VERS_ELEM_TD,         &TY_(W3CAttrsFor_TD)[0],         (CM_ROW|CM_OPT|CM_NO_INDENT),                  TY_(ParseBlock),    NULL           },
  { TidyTag_TEXTAREA,   "textarea",   VERS_ELEM_TEXTAREA,   &TY_(W3CAttrsFor_TEXTAREA)[0],   (CM_INLINE|CM_FIELD),                          TY_(ParseText),     NULL           },
  { TidyTag_TFOOT,      "tfoot",      VERS_ELEM_TFOOT,      &TY_(W3CAttrsFor_TFOOT)[0],      (CM_TABLE|CM_ROWGRP|CM_OPT),                   TY_(ParseRowGroup), NULL           },
  { TidyTag_TH,         "th",         VERS_ELEM_TH,         &TY_(W3CAttrsFor_TH)[0],         (CM_ROW|CM_OPT|CM_NO_INDENT),                  TY_(ParseBlock),    NULL           },
  { TidyTag_THEAD,      "thead",      VERS_ELEM_THEAD,      &TY_(W3CAttrsFor_THEAD)[0],      (CM_TABLE|CM_ROWGRP|CM_OPT),                   TY_(ParseRowGroup), NULL           },
  { TidyTag_TITLE,      "title",      VERS_ELEM_TITLE,      &TY_(W3CAttrsFor_TITLE)[0],      (CM_HEAD),                                     TY_(ParseTitle),    NULL           },
  { TidyTag_TR,         "tr",         VERS_ELEM_TR,         &TY_(W3CAttrsFor_TR)[0],         (CM_TABLE|CM_OPT),                             TY_(ParseRow),      NULL           },
  { TidyTag_TT,         "tt",         VERS_ELEM_TT,         &TY_(W3CAttrsFor_TT)[0],         (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_U,          "u",          VERS_ELEM_U,          &TY_(W3CAttrsFor_U)[0],          (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_UL,         "ul",         VERS_ELEM_UL,         &TY_(W3CAttrsFor_UL)[0],         (CM_BLOCK),                                    TY_(ParseList),     NULL           },
  { TidyTag_VAR,        "var",        VERS_ELEM_VAR,        &TY_(W3CAttrsFor_VAR)[0],        (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_XMP,        "xmp",        VERS_ELEM_XMP,        &TY_(W3CAttrsFor_XMP)[0],        (CM_BLOCK|CM_OBSOLETE),                        TY_(ParsePre),      NULL           },
  { TidyTag_NEXTID,     "nextid",     VERS_ELEM_NEXTID,     &TY_(W3CAttrsFor_NEXTID)[0],     (CM_HEAD|CM_EMPTY),                            TY_(ParseEmpty),    NULL           },

  /* proprietary elements */
  { TidyTag_ALIGN,      "align",      VERS_NETSCAPE,        NULL,                       (CM_BLOCK),                                    TY_(ParseBlock),    NULL           },
  { TidyTag_BGSOUND,    "bgsound",    VERS_MICROSOFT,       NULL,                       (CM_HEAD|CM_EMPTY),                            TY_(ParseEmpty),    NULL           },
  { TidyTag_BLINK,      "blink",      VERS_PROPRIETARY,     NULL,                       (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_COMMENT,    "comment",    VERS_MICROSOFT,       NULL,                       (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_ILAYER,     "ilayer",     VERS_NETSCAPE,        NULL,                       (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_LAYER,      "layer",      VERS_NETSCAPE,        NULL,                       (CM_BLOCK),                                    TY_(ParseBlock),    NULL           },
  { TidyTag_MARQUEE,    "marquee",    VERS_MICROSOFT,       NULL,                       (CM_INLINE|CM_OPT),                            TY_(ParseInline),   NULL           },
  { TidyTag_MULTICOL,   "multicol",   VERS_NETSCAPE,        NULL,                       (CM_BLOCK),                                    TY_(ParseBlock),    NULL           },
  { TidyTag_NOBR,       "nobr",       VERS_PROPRIETARY,     NULL,                       (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_NOEMBED,    "noembed",    VERS_NETSCAPE,        NULL,                       (CM_INLINE),                                   TY_(ParseInline),   NULL           },
  { TidyTag_NOLAYER,    "nolayer",    VERS_NETSCAPE,        NULL,                       (CM_BLOCK|CM_INLINE|CM_MIXED),                 TY_(ParseBlock),    NULL           },
  { TidyTag_NOSAVE,     "nosave",     VERS_NETSCAPE,        NULL,                       (CM_BLOCK),                                    TY_(ParseBlock),    NULL           },
  { TidyTag_SERVER,     "server",     VERS_NETSCAPE,        NULL,                       (CM_HEAD|CM_MIXED|CM_BLOCK|CM_INLINE),         TY_(ParseScript),   NULL           },
  { TidyTag_SERVLET,    "servlet",    VERS_SUN,             NULL,                       (CM_OBJECT|CM_IMG|CM_INLINE|CM_PARAM),         TY_(ParseBlock),    NULL           },
  { TidyTag_SPACER,     "spacer",     VERS_NETSCAPE,        NULL,                       (CM_INLINE|CM_EMPTY),                          TY_(ParseEmpty),    NULL           },

  /* HTML5 */
  { TidyTag_ARTICLE,     "article",      VERS_ELEM_ARTICLE,     &TY_(W3CAttrsFor_ARTICLE)[0],     (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_ASIDE,       "aside",        VERS_ELEM_ASIDE,       &TY_(W3CAttrsFor_ASIDE)[0],       (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_AUDIO,       "audio",        VERS_ELEM_AUDIO,       &TY_(W3CAttrsFor_AUDIO)[0],       (CM_BLOCK|CM_INLINE),          TY_(ParseBlock),     NULL           },
  { TidyTag_BDI,         "bdi",          VERS_ELEM_BDI,         &TY_(W3CAttrsFor_BDI)[0],         (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_CANVAS,      "canvas",       VERS_ELEM_CANVAS,      &TY_(W3CAttrsFor_CANVAS)[0],      (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_COMMAND,     "command",      VERS_ELEM_COMMAND,     &TY_(W3CAttrsFor_COMMAND)[0],     (CM_HEAD|CM_INLINE|CM_EMPTY),  TY_(ParseEmpty),     NULL           },
  { TidyTag_DATALIST,    "datalist",     VERS_ELEM_DATALIST,    &TY_(W3CAttrsFor_DATALIST)[0],    (CM_INLINE|CM_FIELD),          TY_(ParseDatalist),  NULL           },
  //{ TidyTag_DATALIST,    "datalist",     VERS_ELEM_DATALIST,    &TY_(W3CAttrsFor_DATALIST)[0],    (CM_FIELD),                   TY_(ParseInline),    NULL           },
  { TidyTag_DETAILS,     "details",      VERS_ELEM_DETAILS,     &TY_(W3CAttrsFor_DETAILS)[0],     (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_DIALOG,      "dialog",       VERS_ELEM_DIALOG,      &TY_(W3CAttrsFor_DIALOG)[0],      (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_EMBED,       "embed",        VERS_ELEM_EMBED,       &TY_(W3CAttrsFor_EMBED)[0],       (CM_INLINE|CM_IMG|CM_EMPTY),   TY_(ParseEmpty),     NULL           },
  { TidyTag_FIGCAPTION,  "figcaption",   VERS_ELEM_FIGCAPTION,  &TY_(W3CAttrsFor_FIGCAPTION)[0],  (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_FIGURE,      "figure",       VERS_ELEM_FIGURE,      &TY_(W3CAttrsFor_FIGURE)[0],      (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_FOOTER,      "footer",       VERS_ELEM_FOOTER,      &TY_(W3CAttrsFor_FOOTER)[0],      (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_HEADER,      "header",       VERS_ELEM_HEADER,      &TY_(W3CAttrsFor_HEADER)[0],      (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_HGROUP,      "hgroup",       VERS_ELEM_HGROUP,      &TY_(W3CAttrsFor_HGROUP)[0],      (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_KEYGEN,      "keygen",       VERS_ELEM_KEYGEN,      &TY_(W3CAttrsFor_KEYGEN)[0],      (CM_INLINE|CM_EMPTY),          TY_(ParseEmpty),     NULL           },
  { TidyTag_MAIN,        "main",         VERS_ELEM_MAIN,        &TY_(W3CAttrsFor_MAIN)[0],        (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_MARK,        "mark",         VERS_ELEM_MARK,        &TY_(W3CAttrsFor_MARK)[0],        (CM_INLINE),                   TY_(ParseInline),    NULL           },
  { TidyTag_MENU,        "menu",         VERS_ELEM_MENU,        &TY_(W3CAttrsFor_MENU)[0],        (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_MENUITEM,    "menuitem",     VERS_ELEM_MENUITEM,    &TY_(W3CAttrsFor_MENUITEM)[0],    (CM_INLINE|CM_BLOCK|CM_MIXED), TY_(ParseInline),    NULL           },
  { TidyTag_METER,       "meter",        VERS_ELEM_METER,       &TY_(W3CAttrsFor_METER)[0],       (CM_INLINE),                   TY_(ParseInline),    NULL           },
  { TidyTag_NAV,         "nav",          VERS_ELEM_NAV,         &TY_(W3CAttrsFor_NAV)[0],         (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_OUTPUT,      "output",       VERS_ELEM_OUTPUT,      &TY_(W3CAttrsFor_OUTPUT)[0],      (CM_INLINE),                   TY_(ParseInline),    NULL           },
  { TidyTag_PROGRESS,    "progress",     VERS_ELEM_PROGRESS,    &TY_(W3CAttrsFor_PROGRESS)[0],    (CM_INLINE),                   TY_(ParseInline),    NULL           },
  { TidyTag_SECTION,     "section",      VERS_ELEM_SECTION,     &TY_(W3CAttrsFor_SECTION)[0],     (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_SOURCE,      "source",       VERS_ELEM_SOURCE,      &TY_(W3CAttrsFor_SOURCE)[0],      (CM_BLOCK|CM_INLINE|CM_EMPTY), TY_(ParseBlock),     NULL           },
  { TidyTag_SUMMARY,     "summary",      VERS_ELEM_SUMMARY,     &TY_(W3CAttrsFor_SUMMARY)[0],     (CM_BLOCK),                    TY_(ParseInline),    NULL           },
  { TidyTag_TEMPLATE,    "template",     VERS_ELEM_TEMPLATE,    &TY_(W3CAttrsFor_TEMPLATE)[0],    (CM_BLOCK),                    TY_(ParseBlock),     NULL           },
  { TidyTag_TIME,        "time",         VERS_ELEM_TIME,        &TY_(W3CAttrsFor_TIME)[0],        (CM_INLINE),                   TY_(ParseInline),    NULL           },
  { TidyTag_TRACK,       "track",        VERS_ELEM_TRACK,       &TY_(W3CAttrsFor_TRACK)[0],       (CM_BLOCK|CM_EMPTY),           TY_(ParseBlock),     NULL           },
  { TidyTag_VIDEO,       "video",        VERS_ELEM_VIDEO,       &TY_(W3CAttrsFor_VIDEO)[0],       (CM_BLOCK|CM_INLINE),          TY_(ParseBlock),     NULL           },
  { TidyTag_WBR,         "wbr",          VERS_ELEM_WBR,         &TY_(W3CAttrsFor_WBR)[0],         (CM_INLINE|CM_EMPTY),          TY_(ParseEmpty),     NULL           },

  /* this must be the final entry */
  { (TidyTagId)0,        NULL,         0,                    NULL,                       (0),                                           NULL,          NULL           }
};

#if ELEMENT_HASH_LOOKUP
static uint tagsHash(ctmbstr s)
{
    uint hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31*hashval;

    return hashval % ELEMENT_HASH_SIZE;
}

static const Dict *tagsInstall(TidyDoc doc, TidyTagImpl* tags, const Dict* old)
{
    DictHash *np;
    uint hashval;

    if (old)
    {
        np = (DictHash *)TidyDocAlloc(doc, sizeof(*np));
        np->tag = old;

        hashval = tagsHash(old->name);
        np->next = tags->hashtab[hashval];
        tags->hashtab[hashval] = np;
    }

    return old;
}

static void tagsRemoveFromHash( TidyDoc doc, TidyTagImpl* tags, ctmbstr s )
{
    uint h = tagsHash(s);
    DictHash *p, *prev = NULL;
    for (p = tags->hashtab[h]; p && p->tag; p = p->next)
    {
        if (TY_(tmbstrcmp)(s, p->tag->name) == 0)
        {
            DictHash* next = p->next;
            if ( prev )
                prev->next = next;
            else
                tags->hashtab[h] = next;
            TidyDocFree(doc, p);
            return;
        }
        prev = p;
    }
}

static void tagsEmptyHash( TidyDoc doc, TidyTagImpl* tags )
{
    uint i;
    DictHash *prev, *next;

    for (i = 0; i < ELEMENT_HASH_SIZE; ++i)
    {
        prev = NULL;
        next = tags->hashtab[i];

        while(next)
        {
            prev = next->next;
            TidyDocFree(doc, next);
            next = prev;
        }

        tags->hashtab[i] = NULL;
    }
}
#endif /* ELEMENT_HASH_LOOKUP */

static const Dict* tagsLookup( TidyDoc doc, TidyTagImpl* tags, ctmbstr s )
{
    const Dict *np;
#if ELEMENT_HASH_LOOKUP
    const DictHash* p;
#endif

    if (!s)
        return NULL;

#if ELEMENT_HASH_LOOKUP
    /* this breaks if declared elements get changed between two   */
    /* parser runs since Tidy would use the cached version rather */
    /* than the new one.                                          */
    /* However, as FreeDeclaredTags() correctly cleans the hash   */
    /* this should not be true anymore.                           */
    for (p = tags->hashtab[tagsHash(s)]; p && p->tag; p = p->next)
        if (TY_(tmbstrcmp)(s, p->tag->name) == 0)
            return p->tag;

    for (np = tag_defs + 1; np < tag_defs + N_TIDY_TAGS; ++np)
        if (TY_(tmbstrcmp)(s, np->name) == 0)
            return tagsInstall(doc, tags, np);

    for (np = tags->declared_tag_list; np; np = np->next)
        if (TY_(tmbstrcmp)(s, np->name) == 0)
            return tagsInstall(doc, tags, np);
#else

    for (np = tag_defs + 1; np < tag_defs + N_TIDY_TAGS; ++np)
        if (TY_(tmbstrcmp)(s, np->name) == 0)
            return np;

    for (np = tags->declared_tag_list; np; np = np->next)
        if (TY_(tmbstrcmp)(s, np->name) == 0)
            return np;

#endif /* ELEMENT_HASH_LOOKUP */

    return NULL;
}

static Dict* NewDict( TidyDoc doc, ctmbstr name )
{
    Dict *np = (Dict*) TidyDocAlloc( doc, sizeof(Dict) );
    np->id = TidyTag_UNKNOWN;
    np->name = name ? TY_(tmbstrdup)( doc->allocator, name ) : NULL;
    np->versions = VERS_UNKNOWN;
    np->attrvers = NULL;
    np->model = CM_UNKNOWN;
    np->parser = 0;
    np->chkattrs = 0;
    np->next = NULL;
    return np;
}

static void FreeDict( TidyDoc doc, Dict *d )
{
    if ( d )
        TidyDocFree( doc, d->name );
    TidyDocFree( doc, d );
}

static void declare( TidyDoc doc, TidyTagImpl* tags,
                     ctmbstr name, uint versions, uint model,
                     Parser *parser, CheckAttribs *chkattrs )
{
    if ( name )
    {
        Dict* np = (Dict*) tagsLookup( doc, tags, name );
        if ( np == NULL )
        {
            np = NewDict( doc, name );
            np->next = tags->declared_tag_list;
            tags->declared_tag_list = np;
        }

        /* Make sure we are not over-writing predefined tags */
        if ( np->id == TidyTag_UNKNOWN )
        {
          np->versions = versions;
          np->model   |= model;
          np->parser   = parser;
          np->chkattrs = chkattrs;
          np->attrvers = NULL;
        }
    }
}

#if !defined(NDEBUG) && defined(_MSC_VER)
/* ==================================================================== 
   MSVC DEBUG ONLY
 */
void ListElementsPerVersion( uint vers, Bool has )
{
    uint val, cnt, total, wrap = 10;
    const Dict *np = tag_defs + 1;
    const Dict *end = tag_defs + N_TIDY_TAGS;
    cnt = 0;
    total = 0;
    for ( ; np < end; np++) {
        val = (np->versions & vers);
        if (has) {
            if (val) {
                SPRTF("%s ",np->name);
                cnt++;
                total++;
            }
        } else {
            if (!val) {
                SPRTF("%s ",np->name);
                cnt++;
                total++;
            }
        }
        if (cnt == wrap) {
            SPRTF("\n");
            cnt = 0;
        }
    }
    if (cnt)
        SPRTF("\n");
    SPRTF("Listed total %u tags that %s version %u\n", total,
        (has ? "have" : "do not have"),
        vers );

}

void show_not_html5(void)
{
    SPRTF("List tags that do not have version HTML5 (HT50|XH50)\n"),
    ListElementsPerVersion( VERS_HTML5, no );
}
void show_have_html5(void)
{
    ListElementsPerVersion( VERS_HTML5, yes );
}

#endif

/* public interface for finding tag by name */
Bool TY_(FindTag)( TidyDoc doc, TidyNode node )
{
    const Dict *np = NULL;
    if ( cfgBool(doc, TidyXmlTags) )
    {
        node->tag = doc->tags.xml_tags;
        return yes;
    }

    if ( node->element && (np = tagsLookup(doc, &doc->tags, node->element)) )
    {
        node->tag = np;
        return yes;
    }

    return no;
}

const Dict* TY_(LookupTagDef)( TidyTagId tid )
{
    const Dict *np;

    for (np = tag_defs + 1; np < tag_defs + N_TIDY_TAGS; ++np )
        if (np->id == tid)
            return np;

    return NULL;
}

Parser* TY_(FindParser)( TidyDoc doc, TidyNode node )
{
    const Dict* np = tagsLookup( doc, &doc->tags, node->element );
    if ( np )
        return np->parser;
    return NULL;
}

void TY_(DefineTag)( TidyDoc doc, UserTagType tagType, ctmbstr name )
{
    Parser* parser = 0;
    uint cm = CM_UNKNOWN;
    uint vers = VERS_PROPRIETARY;

    switch (tagType)
    {
    case tagtype_empty:
        cm = CM_EMPTY|CM_NO_INDENT|CM_NEW;
        parser = TY_(ParseBlock);
        break;

    case tagtype_inline:
        cm = CM_INLINE|CM_NO_INDENT|CM_NEW;
        parser = TY_(ParseInline);
        break;

    case tagtype_block:
        cm = CM_BLOCK|CM_NO_INDENT|CM_NEW;
        parser = TY_(ParseBlock);
        break;

    case tagtype_pre:
        cm = CM_BLOCK|CM_NO_INDENT|CM_NEW;
        parser = TY_(ParsePre);
        break;

    case tagtype_null:
        break;
    }
    if ( cm && parser )
        declare( doc, &doc->tags, name, vers, cm, parser, 0 );
}

TidyIterator   TY_(GetDeclaredTagList)( TidyDoc doc )
{
    return (TidyIterator) doc->tags.declared_tag_list;
}

ctmbstr        TY_(GetNextDeclaredTag)( TidyDoc ARG_UNUSED(doc),
                                        UserTagType tagType, TidyIterator* iter )
{
    ctmbstr name = NULL;
    Dict* curr;
    for ( curr = (Dict*) *iter; name == NULL && curr != NULL; curr = curr->next )
    {
        switch ( tagType )
        {
        case tagtype_empty:
            if ( (curr->model & CM_EMPTY) != 0 )
                name = curr->name;
            break;

        case tagtype_inline:
            if ( (curr->model & CM_INLINE) != 0 )
                name = curr->name;
            break;

        case tagtype_block:
            if ( (curr->model & CM_BLOCK) != 0 &&
                 curr->parser == TY_(ParseBlock) )
                name = curr->name;
            break;

        case tagtype_pre:
            if ( (curr->model & CM_BLOCK) != 0 &&
                 curr->parser == TY_(ParsePre) )
                name = curr->name;
            break;

        case tagtype_null:
            break;
        }
    }
    *iter = (TidyIterator) curr;
    return name;
}

void TY_(InitTags)( TidyDoc doc )
{
    Dict* xml;
    TidyTagImpl* tags = &doc->tags;

    TidyClearMemory( tags, sizeof(TidyTagImpl) );

    /* create dummy entry for all xml tags */
    xml =  NewDict( doc, NULL );
    xml->versions = VERS_XML;
    xml->model = CM_BLOCK;
    xml->parser = 0;
    xml->chkattrs = 0;
    xml->attrvers = NULL;
    tags->xml_tags = xml;
}

/* By default, zap all of them.  But allow
** an single type to be specified.
*/
void TY_(FreeDeclaredTags)( TidyDoc doc, UserTagType tagType )
{
    TidyTagImpl* tags = &doc->tags;
    Dict *curr, *next = NULL, *prev = NULL;

    for ( curr=tags->declared_tag_list; curr; curr = next )
    {
        Bool deleteIt = yes;
        next = curr->next;
        switch ( tagType )
        {
        case tagtype_empty:
            deleteIt = ( curr->model & CM_EMPTY ) != 0;
            break;

        case tagtype_inline:
            deleteIt = ( curr->model & CM_INLINE ) != 0;
            break;

        case tagtype_block:
            deleteIt = ( (curr->model & CM_BLOCK) != 0 &&
                         curr->parser == TY_(ParseBlock) );
            break;

        case tagtype_pre:
            deleteIt = ( (curr->model & CM_BLOCK) != 0 &&
                         curr->parser == TY_(ParsePre) );
            break;

        case tagtype_null:
            break;
        }

        if ( deleteIt )
        {
#if ELEMENT_HASH_LOOKUP
          tagsRemoveFromHash( doc, &doc->tags, curr->name );
#endif
          FreeDict( doc, curr );
          if ( prev )
            prev->next = next;
          else
            tags->declared_tag_list = next;
        }
        else
          prev = curr;
    }
}

/*\
 * Issue #167 & #169
 * Tidy defaults to HTML5 mode
 * If the <!DOCTYPE ...> is found to NOT be HTML5,
 * then adjust tags to HTML4 mode
 *
 * NOTE: For each change added to here, there must 
 * be a RESET added in TY_(ResetTags) below!
\*/
void TY_(AdjustTags)( TidyDoc doc )
{
    Dict *np = (Dict *)TY_(LookupTagDef)( TidyTag_A );
    TidyTagImpl* tags = &doc->tags;
    if (np) 
    {
        np->parser = TY_(ParseInline);
        np->model  = CM_INLINE;
#if ELEMENT_HASH_LOOKUP
        tagsEmptyHash( doc, tags );
#endif
    }

/*\
 * Issue #196
 * TidyTag_CAPTION allows %flow; in HTML5,
 * but only %inline; in HTML4
\*/
    np = (Dict *)TY_(LookupTagDef)( TidyTag_CAPTION );
    if (np)
    {
        np->parser = TY_(ParseInline);
#if ELEMENT_HASH_LOOKUP
        tagsEmptyHash( doc, tags );
#endif
    }

/*\
 * Issue #232
 * TidyTag_OBJECT not in head in HTML5,
 * but still allowed in HTML4
\*/
    np = (Dict *)TY_(LookupTagDef)( TidyTag_OBJECT );
    if (np)
    {
        np->model |= CM_HEAD; /* add back allowed in head */
#if ELEMENT_HASH_LOOKUP
        tagsEmptyHash( doc, tags );
#endif
    }
}

Bool TY_(IsHTML5Mode)( TidyDoc doc )
{
    return doc->HTML5Mode;
}


/*\
 * Issue #285
 * Reset the table to default HTML5 mode.
 * For every change made in the above AdjustTags,
 * the equivalent reset must be added here.
\*/
void TY_(ResetTags)( TidyDoc doc )
{
    Dict *np = (Dict *)TY_(LookupTagDef)( TidyTag_A );
    TidyTagImpl* tags = &doc->tags;
    if (np) 
    {
        np->parser = TY_(ParseBlock);
        np->model  = (CM_INLINE|CM_BLOCK|CM_MIXED);
    }
    np = (Dict *)TY_(LookupTagDef)( TidyTag_CAPTION );
    if (np)
    {
        np->parser = TY_(ParseBlock);
    }

    np = (Dict *)TY_(LookupTagDef)( TidyTag_OBJECT );
    if (np)
    {
        np->model = (CM_OBJECT|CM_IMG|CM_INLINE|CM_PARAM); /* reset */
    }
#if ELEMENT_HASH_LOOKUP
    tagsEmptyHash( doc, tags ); /* not sure this is really required, but to be sure */
#endif
    doc->HTML5Mode = yes;   /* set HTML5 mode */
}

void TY_(FreeTags)( TidyDoc doc )
{
    TidyTagImpl* tags = &doc->tags;

#if ELEMENT_HASH_LOOKUP
    tagsEmptyHash( doc, tags );
#endif
    TY_(FreeDeclaredTags)( doc, tagtype_null );
    FreeDict( doc, tags->xml_tags );

    /* get rid of dangling tag references */
    TidyClearMemory( tags, sizeof(TidyTagImpl) );

    doc->HTML5Mode = no;    /* reset html5 mode == legacy html4 mode */
}


/* default method for checking an element's attributes */
void TY_(CheckAttributes)( TidyDoc doc, TidyNode node )
{
    TidyAttr next, attval = node->attributes;
    while (attval)
    {
        next = attval->next;
        TY_(CheckAttribute)( doc, node, attval );
        attval = next;
    }
}

/* methods for checking attributes for specific elements */

void CheckIMG( TidyDoc doc, TidyNode node )
{
    Bool HasAlt = TY_(AttrGetById)(node, TidyAttr_ALT) != NULL;
    Bool HasSrc = TY_(AttrGetById)(node, TidyAttr_SRC) != NULL;
    Bool HasUseMap = TY_(AttrGetById)(node, TidyAttr_USEMAP) != NULL;
    Bool HasIsMap = TY_(AttrGetById)(node, TidyAttr_ISMAP) != NULL;
    Bool HasDataFld = TY_(AttrGetById)(node, TidyAttr_DATAFLD) != NULL;

    TY_(CheckAttributes)(doc, node);

    if ( !HasAlt )
    {
        ctmbstr alttext = cfgStr(doc, TidyAltText);
        if ( ( cfg(doc, TidyAccessibilityCheckLevel) == 0 ) && ( !alttext ) )
        {
            doc->badAccess |= BA_MISSING_IMAGE_ALT;
            TY_(ReportMissingAttr)( doc, node, "alt" );
        }

        if ( alttext ) {
            TidyAttr attval = TY_(AddAttribute)( doc, node, "alt", alttext );
            TY_(ReportAttrError)( doc, node, attval, INSERTING_AUTO_ATTRIBUTE);
        }
    }

    if ( !HasSrc && !HasDataFld )
        TY_(ReportMissingAttr)( doc, node, "src" );

    if ( cfg(doc, TidyAccessibilityCheckLevel) == 0 )
    {
        if ( HasIsMap && !HasUseMap )
            TY_(ReportAttrError)( doc, node, NULL, MISSING_IMAGEMAP);
    }
}

void CheckCaption(TidyDoc doc, TidyNode node)
{
    TidyAttr attval;

    TY_(CheckAttributes)(doc, node);

    attval = TY_(AttrGetById)(node, TidyAttr_ALIGN);

    if (!AttrHasValue(attval))
        return;

    if (AttrValueIs(attval, "left") || AttrValueIs(attval, "right"))
        TY_(ConstrainVersion)(doc, VERS_HTML40_LOOSE);
    else if (AttrValueIs(attval, "top") || AttrValueIs(attval, "bottom"))
        TY_(ConstrainVersion)(doc, ~(VERS_HTML20|VERS_HTML32));
    else
        TY_(ReportAttrError)(doc, node, attval, BAD_ATTRIBUTE_VALUE);
}

void CheckHTML( TidyDoc doc, TidyNode node )
{
    TY_(CheckAttributes)(doc, node);
}

void CheckAREA( TidyDoc doc, TidyNode node )
{
    Bool HasAlt = TY_(AttrGetById)(node, TidyAttr_ALT) != NULL;
    Bool HasHref = TY_(AttrGetById)(node, TidyAttr_HREF) != NULL;
    Bool HasNohref = TY_(AttrGetById)(node, TidyAttr_NOHREF) != NULL;

    TY_(CheckAttributes)(doc, node);

    if ( !HasAlt )
    {
        if ( cfg(doc, TidyAccessibilityCheckLevel) == 0 )
        {
            doc->badAccess |= BA_MISSING_LINK_ALT;
            TY_(ReportMissingAttr)( doc, node, "alt" );
        }
    }

    if ( !HasHref && !HasNohref )
        TY_(ReportMissingAttr)( doc, node, "href" );
}

void CheckTABLE( TidyDoc doc, TidyNode node )
{
    TidyAttr attval;
    Bool HasSummary = (TY_(AttrGetById)(node, TidyAttr_SUMMARY) != NULL) ? yes : no;
    uint vers = TY_(HTMLVersion)(doc);  /* Issue #377 - Also applies to XHTML5 */
    Bool isHTML5 = ((vers == HT50)||(vers == XH50)) ? yes : no;

    TY_(CheckAttributes)(doc, node);

    /* Issue #210 - a missing summary attribute is bad accessibility, no matter
       what HTML version is involved; a document without is valid 
       EXCEPT for HTML5, when to have a summary is wrong */
    if (cfg(doc, TidyAccessibilityCheckLevel) == 0)
    {
        if (HasSummary && isHTML5)
        {
            /* #210 - has summary, and is HTML5, then report obsolete */
            TY_(ReportWarning)(doc, node, node, BAD_SUMMARY_HTML5);
        } 
        else if (!HasSummary && !isHTML5) 
        {
            /* #210 - No summary, and NOT HTML5, then report as before */
            doc->badAccess |= BA_MISSING_SUMMARY;
            TY_(ReportMissingAttr)( doc, node, "summary");
        }
    }

    /* convert <table border> to <table border="1"> */
    if ( cfgBool(doc, TidyXmlOut) && (attval = TY_(AttrGetById)(node, TidyAttr_BORDER)) )
    {
        if (attval->value == NULL)
            attval->value = TY_(tmbstrdup)(doc->allocator, "1");
    }
}

/* report missing href attribute; report missing rel attribute */
void CheckLINK( TidyDoc doc, TidyNode node )
{
    Bool HasHref = TY_(AttrGetById)(node, TidyAttr_HREF) != NULL;
    Bool HasRel = TY_(AttrGetById)(node, TidyAttr_REL) != NULL;
    Bool HasItemprop = TY_(AttrGetById)(node, TidyAttr_ITEMPROP) != NULL;

    if (!HasHref)
    {
      TY_(ReportMissingAttr)( doc, node, "href" );
    }

    if (!HasItemprop && !HasRel)
    {
      TY_(ReportMissingAttr)( doc, node, "rel" );
    }
}

Bool TY_(nodeIsText)( TidyNode node )
{
  return ( node && node->type == TextNode );
}

Bool TY_(nodeHasText)( TidyDoc doc, TidyNode node )
{
  if ( doc && node )
  {
    uint ix;
    Lexer* lexer = doc->lexer;
    for ( ix = node->start; ix < node->end; ++ix )
    {
        /* whitespace */
        if ( !TY_(IsWhite)( lexer->lexbuf[ix] ) )
            return yes;
    }
  }
  return no;
}

Bool TY_(nodeIsElement)( TidyNode node )
{
  return ( node &&
           (node->type == StartTag || node->type == StartEndTag) );
}

#if 0
/* Compare & result to operand.  If equal, then all bits
** requested are set.
*/
Bool nodeMatchCM( TidyNode node, uint contentModel )
{
  return ( node && node->tag &&
           (node->tag->model & contentModel) == contentModel );
}
#endif

/* True if any of the bits requested are set.
*/
Bool TY_(nodeHasCM)( TidyNode node, uint contentModel )
{
  return ( node && node->tag &&
           (node->tag->model & contentModel) != 0 );
}

Bool TY_(nodeCMIsBlock)( TidyNode node )
{
  return TY_(nodeHasCM)( node, CM_BLOCK );
}
Bool TY_(nodeCMIsInline)( TidyNode node )
{
  return TY_(nodeHasCM)( node, CM_INLINE );
}
Bool TY_(nodeCMIsEmpty)( TidyNode node )
{
  return TY_(nodeHasCM)( node, CM_EMPTY );
}

Bool TY_(nodeIsHeader)( TidyNode node )
{
    TidyTagId tid = TagId( node  );
    return ( tid && (
             tid == TidyTag_H1 ||
             tid == TidyTag_H2 ||
             tid == TidyTag_H3 ||
             tid == TidyTag_H4 ||
             tid == TidyTag_H5 ||
             tid == TidyTag_H6 ));
}

uint TY_(nodeHeaderLevel)( TidyNode node )
{
    TidyTagId tid = TagId( node  );
    switch ( tid )
    {
    case TidyTag_H1:
        return 1;
    case TidyTag_H2:
        return 2;
    case TidyTag_H3:
        return 3;
    case TidyTag_H4:
        return 4;
    case TidyTag_H5:
        return 5;
    case TidyTag_H6:
        return 6;
    default:
    {
        /* fall through */
    }
    }
    return 0;
}

/* [i_a] generic node tree traversal; see also <tidy-int.h> */
NodeTraversalSignal TY_(TraverseNodeTree)(TidyDoc doc, TidyNode node, NodeTraversalCallBack *cb, void *propagate )
{
    while (node)
    {
        NodeTraversalSignal s = (*cb)(doc, node, propagate);

        if (node->content && (s == ContinueTraversal || s == SkipSiblings))
        {
            s = TY_(TraverseNodeTree)(doc, node->content, cb, propagate);
        }

        switch (s)
        {
        case ExitTraversal:
            return ExitTraversal;

        case VisitParent:
            node = node->parent;
            continue;

        case SkipSiblings:
        case SkipChildrenAndSiblings:
            return ContinueTraversal;

        default:
            node = node->next;
            break;
        }
    }
    return ContinueTraversal;
}



/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
