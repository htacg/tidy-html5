/* attrs.c -- recognize HTML attributes

  (c) 1998-2009 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

*/

#include "tidy-int.h"
#include "attrs.h"
#include "message.h"
#include "tmbstr.h"
#include "utf8.h"

/*
 Bind attribute types to procedures to check values.
 You can add new procedures for better validation
 and each procedure has access to the node in which
 the attribute occurred as well as the attribute name
 and its value.

 By default, attributes are checked without regard
 to the element they are found on. You have the choice
 of making the procedure test which element is involved
 or in writing methods for each element which controls
 exactly how the attributes of that element are checked.
 This latter approach is best for detecting the absence
 of required attributes.
*/

static AttrCheck CheckAction;
static AttrCheck CheckScript;
static AttrCheck CheckName;
static AttrCheck CheckId;
static AttrCheck CheckAlign;
static AttrCheck CheckValign;
static AttrCheck CheckBool;
static AttrCheck CheckLength;
static AttrCheck CheckTarget;
static AttrCheck CheckFsubmit;
static AttrCheck CheckClear;
static AttrCheck CheckShape;
static AttrCheck CheckNumber;
static AttrCheck CheckScope;
static AttrCheck CheckColor;
static AttrCheck CheckVType;
static AttrCheck CheckScroll;
static AttrCheck CheckTextDir;
static AttrCheck CheckLang;
static AttrCheck CheckType;
static AttrCheck CheckRDFaSafeCURIE;
static AttrCheck CheckRDFaTerm;
static AttrCheck CheckRDFaPrefix;

#define CH_PCDATA      NULL
#define CH_CHARSET     NULL
#define CH_TYPE        CheckType
#define CH_XTYPE       NULL
#define CH_CHARACTER   NULL
#define CH_URLS        NULL
#define CH_URL         TY_(CheckUrl)
#define CH_SCRIPT      CheckScript
#define CH_ALIGN       CheckAlign
#define CH_VALIGN      CheckValign
#define CH_COLOR       CheckColor
#define CH_CLEAR       CheckClear
#define CH_BORDER      CheckBool     /* kludge */
#define CH_LANG        CheckLang
#define CH_BOOL        CheckBool
#define CH_COLS        NULL
#define CH_NUMBER      CheckNumber
#define CH_LENGTH      CheckLength
#define CH_COORDS      NULL
#define CH_DATE        NULL
#define CH_TEXTDIR     CheckTextDir
#define CH_IDREFS      NULL
#define CH_IDREF       NULL
#define CH_IDDEF       CheckId
#define CH_NAME        CheckName
#define CH_TFRAME      NULL
#define CH_FBORDER     NULL
#define CH_MEDIA       NULL
#define CH_FSUBMIT     CheckFsubmit
#define CH_LINKTYPES   NULL
#define CH_TRULES      NULL
#define CH_SCOPE       CheckScope
#define CH_SHAPE       CheckShape
#define CH_SCROLL      CheckScroll
#define CH_TARGET      CheckTarget
#define CH_VTYPE       CheckVType
#define CH_ACTION      CheckAction
#define CH_RDFAPREFIX  CheckRDFaPrefix
#define CH_RDFASCURIE  CheckRDFaSafeCURIE
#define CH_RDFASCURIES CheckRDFaSafeCURIE
#define CH_RDFATERM    CheckRDFaTerm
#define CH_RDFATERMS   CheckRDFaTerm

static const Attribute attribute_defs [] =
{
  { TidyAttr_UNKNOWN,                 "unknown!",                NULL         }, 
  { TidyAttr_ABBR,                    "abbr",                    CH_PCDATA    }, 
  { TidyAttr_ACCEPT,                  "accept",                  CH_XTYPE     }, 
  { TidyAttr_ACCEPT_CHARSET,          "accept-charset",          CH_CHARSET   }, 
  { TidyAttr_ACCESSKEY,               "accesskey",               CH_CHARACTER }, 
  { TidyAttr_ACTION,                  "action",                  CH_ACTION    }, 
  { TidyAttr_ADD_DATE,                "add_date",                CH_PCDATA    }, /* A */
  { TidyAttr_ALIGN,                   "align",                   CH_ALIGN     }, /* varies by element */
  { TidyAttr_ALINK,                   "alink",                   CH_COLOR     }, 
  { TidyAttr_ALLOWFULLSCREEN,         "allowfullscreen",         CH_BOOL      },
  { TidyAttr_ALT,                     "alt",                     CH_PCDATA    }, /* nowrap */
  { TidyAttr_ARCHIVE,                 "archive",                 CH_URLS      }, /* space or comma separated list */
  { TidyAttr_AXIS,                    "axis",                    CH_PCDATA    }, 
  { TidyAttr_BACKGROUND,              "background",              CH_URL       }, 
  { TidyAttr_BGCOLOR,                 "bgcolor",                 CH_COLOR     }, 
  { TidyAttr_BGPROPERTIES,            "bgproperties",            CH_PCDATA    }, /* BODY "fixed" fixes background */
  { TidyAttr_BORDER,                  "border",                  CH_BORDER    }, /* like LENGTH + "border" */
  { TidyAttr_BORDERCOLOR,             "bordercolor",             CH_COLOR     }, /* used on TABLE */
  { TidyAttr_BOTTOMMARGIN,            "bottommargin",            CH_NUMBER    }, /* used on BODY */
  { TidyAttr_CELLPADDING,             "cellpadding",             CH_LENGTH    }, /* % or pixel values */
  { TidyAttr_CELLSPACING,             "cellspacing",             CH_LENGTH    }, 
  { TidyAttr_CHAR,                    "char",                    CH_CHARACTER }, 
  { TidyAttr_CHAROFF,                 "charoff",                 CH_LENGTH    }, 
  { TidyAttr_CHARSET,                 "charset",                 CH_CHARSET   }, 
  { TidyAttr_CHECKED,                 "checked",                 CH_BOOL      }, /* i.e. "checked" or absent */
  { TidyAttr_CITE,                    "cite",                    CH_URL       }, 
  { TidyAttr_CLASS,                   "class",                   CH_PCDATA    }, 
  { TidyAttr_CLASSID,                 "classid",                 CH_URL       }, 
  { TidyAttr_CLEAR,                   "clear",                   CH_CLEAR     }, /* BR: left, right, all */
  { TidyAttr_CODE,                    "code",                    CH_PCDATA    }, /* APPLET */
  { TidyAttr_CODEBASE,                "codebase",                CH_URL       }, /* OBJECT */
  { TidyAttr_CODETYPE,                "codetype",                CH_XTYPE     }, /* OBJECT */
  { TidyAttr_COLOR,                   "color",                   CH_COLOR     }, /* BASEFONT, FONT */
  { TidyAttr_COLS,                    "cols",                    CH_COLS      }, /* TABLE & FRAMESET */
  { TidyAttr_COLSPAN,                 "colspan",                 CH_NUMBER    }, 
  { TidyAttr_COMPACT,                 "compact",                 CH_BOOL      }, /* lists */
  { TidyAttr_CONTENT,                 "content",                 CH_PCDATA    }, 
  { TidyAttr_COORDS,                  "coords",                  CH_COORDS    }, /* AREA, A */
  { TidyAttr_DATA,                    "data",                    CH_URL       }, /* OBJECT */
  { TidyAttr_DATAFLD,                 "datafld",                 CH_PCDATA    }, /* used on DIV, IMG */
  { TidyAttr_DATAFORMATAS,            "dataformatas",            CH_PCDATA    }, /* used on DIV, IMG */
  { TidyAttr_DATAPAGESIZE,            "datapagesize",            CH_NUMBER    }, /* used on DIV, IMG */
  { TidyAttr_DATASRC,                 "datasrc",                 CH_URL       }, /* used on TABLE */
  { TidyAttr_DATETIME,                "datetime",                CH_DATE      }, /* INS, DEL */
  { TidyAttr_DECLARE,                 "declare",                 CH_BOOL      }, /* OBJECT */
  { TidyAttr_DEFER,                   "defer",                   CH_BOOL      }, /* SCRIPT */
  { TidyAttr_DIR,                     "dir",                     CH_TEXTDIR   }, /* ltr or rtl */
  { TidyAttr_DISABLED,                "disabled",                CH_BOOL      }, /* form fields */
  { TidyAttr_ENCODING,                "encoding",                CH_PCDATA    }, /* <?xml?> */
  { TidyAttr_ENCTYPE,                 "enctype",                 CH_XTYPE     }, /* FORM */
  { TidyAttr_FACE,                    "face",                    CH_PCDATA    }, /* BASEFONT, FONT */
  { TidyAttr_FOR,                     "for",                     CH_IDREF     }, /* LABEL */
  { TidyAttr_FRAME,                   "frame",                   CH_TFRAME    }, /* TABLE */
  { TidyAttr_FRAMEBORDER,             "frameborder",             CH_FBORDER   }, /* 0 or 1 */
  { TidyAttr_FRAMESPACING,            "framespacing",            CH_NUMBER    }, 
  { TidyAttr_GRIDX,                   "gridx",                   CH_NUMBER    }, /* TABLE Adobe golive*/
  { TidyAttr_GRIDY,                   "gridy",                   CH_NUMBER    }, /* TABLE Adobe golive */
  { TidyAttr_HEADERS,                 "headers",                 CH_IDREFS    }, /* table cells */
  { TidyAttr_HEIGHT,                  "height",                  CH_LENGTH    }, /* pixels only for TH/TD */
  { TidyAttr_HREF,                    "href",                    CH_URL       }, /* A, AREA, LINK and BASE */
  { TidyAttr_HREFLANG,                "hreflang",                CH_LANG      }, /* A, LINK */
  { TidyAttr_HSPACE,                  "hspace",                  CH_NUMBER    }, /* APPLET, IMG, OBJECT */
  { TidyAttr_HTTP_EQUIV,              "http-equiv",              CH_PCDATA    }, /* META */
  { TidyAttr_ID,                      "id",                      CH_IDDEF     }, 
  { TidyAttr_ISMAP,                   "ismap",                   CH_BOOL      }, /* IMG */
  { TidyAttr_ITEMID,                  "itemid",                  CH_PCDATA    },
  { TidyAttr_ITEMPROP,                "itemprop",                CH_PCDATA    },
  { TidyAttr_ITEMREF,                 "itemref",                 CH_PCDATA    },
  { TidyAttr_ITEMSCOPE,               "itemscope",               CH_BOOL      },
  { TidyAttr_ITEMTYPE,                "itemtype",                CH_URL       },
  { TidyAttr_LABEL,                   "label",                   CH_PCDATA    }, /* OPT, OPTGROUP */
  { TidyAttr_LANG,                    "lang",                    CH_LANG      }, 
  { TidyAttr_LANGUAGE,                "language",                CH_PCDATA    }, /* SCRIPT */
  { TidyAttr_LAST_MODIFIED,           "last_modified",           CH_PCDATA    }, /* A */
  { TidyAttr_LAST_VISIT,              "last_visit",              CH_PCDATA    }, /* A */
  { TidyAttr_LEFTMARGIN,              "leftmargin",              CH_NUMBER    }, /* used on BODY */
  { TidyAttr_LINK,                    "link",                    CH_COLOR     }, /* BODY */
  { TidyAttr_LONGDESC,                "longdesc",                CH_URL       }, /* IMG */
  { TidyAttr_LOWSRC,                  "lowsrc",                  CH_URL       }, /* IMG */
  { TidyAttr_MARGINHEIGHT,            "marginheight",            CH_NUMBER    }, /* FRAME, IFRAME, BODY */
  { TidyAttr_MARGINWIDTH,             "marginwidth",             CH_NUMBER    }, /* ditto */
  { TidyAttr_MAXLENGTH,               "maxlength",               CH_NUMBER    }, /* INPUT */
  { TidyAttr_MEDIA,                   "media",                   CH_MEDIA     }, /* STYLE, LINK */
  { TidyAttr_METHOD,                  "method",                  CH_FSUBMIT   }, /* FORM: get or post */
  { TidyAttr_MULTIPLE,                "multiple",                CH_BOOL      }, /* SELECT */
  { TidyAttr_NAME,                    "name",                    CH_NAME      }, 
  { TidyAttr_NOHREF,                  "nohref",                  CH_BOOL      }, /* AREA */
  { TidyAttr_NORESIZE,                "noresize",                CH_BOOL      }, /* FRAME */
  { TidyAttr_NOSHADE,                 "noshade",                 CH_BOOL      }, /* HR */
  { TidyAttr_NOWRAP,                  "nowrap",                  CH_BOOL      }, /* table cells */
  { TidyAttr_OBJECT,                  "object",                  CH_PCDATA    }, /* APPLET */
  { TidyAttr_OnAFTERUPDATE,           "onafterupdate",           CH_SCRIPT    }, 
  { TidyAttr_OnBEFOREUNLOAD,          "onbeforeunload",          CH_SCRIPT    }, 
  { TidyAttr_OnBEFOREUPDATE,          "onbeforeupdate",          CH_SCRIPT    }, 
  { TidyAttr_OnBLUR,                  "onblur",                  CH_SCRIPT    }, /* event */
  { TidyAttr_OnCHANGE,                "onchange",                CH_SCRIPT    }, /* event */
  { TidyAttr_OnCLICK,                 "onclick",                 CH_SCRIPT    }, /* event */
  { TidyAttr_OnDATAAVAILABLE,         "ondataavailable",         CH_SCRIPT    }, /* object, applet */
  { TidyAttr_OnDATASETCHANGED,        "ondatasetchanged",        CH_SCRIPT    }, /* object, applet */
  { TidyAttr_OnDATASETCOMPLETE,       "ondatasetcomplete",       CH_SCRIPT    }, 
  { TidyAttr_OnDBLCLICK,              "ondblclick",              CH_SCRIPT    }, /* event */
  { TidyAttr_OnERRORUPDATE,           "onerrorupdate",           CH_SCRIPT    }, /* form fields */
  { TidyAttr_OnFOCUS,                 "onfocus",                 CH_SCRIPT    }, /* event */
  { TidyAttr_OnKEYDOWN,               "onkeydown",               CH_SCRIPT    }, /* event */
  { TidyAttr_OnKEYPRESS,              "onkeypress",              CH_SCRIPT    }, /* event */
  { TidyAttr_OnKEYUP,                 "onkeyup",                 CH_SCRIPT    }, /* event */
  { TidyAttr_OnLOAD,                  "onload",                  CH_SCRIPT    }, /* event */
  { TidyAttr_OnMOUSEDOWN,             "onmousedown",             CH_SCRIPT    }, /* event */
  { TidyAttr_OnMOUSEMOVE,             "onmousemove",             CH_SCRIPT    }, /* event */
  { TidyAttr_OnMOUSEOUT,              "onmouseout",              CH_SCRIPT    }, /* event */
  { TidyAttr_OnMOUSEOVER,             "onmouseover",             CH_SCRIPT    }, /* event */
  { TidyAttr_OnMOUSEUP,               "onmouseup",               CH_SCRIPT    }, /* event */
  { TidyAttr_OnRESET,                 "onreset",                 CH_SCRIPT    }, /* event */
  { TidyAttr_OnROWENTER,              "onrowenter",              CH_SCRIPT    }, /* form fields */
  { TidyAttr_OnROWEXIT,               "onrowexit",               CH_SCRIPT    }, /* form fields */
  { TidyAttr_OnSELECT,                "onselect",                CH_SCRIPT    }, /* event */
  { TidyAttr_OnSUBMIT,                "onsubmit",                CH_SCRIPT    }, /* event */
  { TidyAttr_OnUNLOAD,                "onunload",                CH_SCRIPT    }, /* event */
  { TidyAttr_PROFILE,                 "profile",                 CH_URL       }, /* HEAD */
  { TidyAttr_PROMPT,                  "prompt",                  CH_PCDATA    }, /* ISINDEX */
  { TidyAttr_RBSPAN,                  "rbspan",                  CH_NUMBER    }, /* ruby markup */
  { TidyAttr_READONLY,                "readonly",                CH_BOOL      }, /* form fields */
  { TidyAttr_REL,                     "rel",                     CH_LINKTYPES }, 
  { TidyAttr_REV,                     "rev",                     CH_LINKTYPES }, 
  { TidyAttr_RIGHTMARGIN,             "rightmargin",             CH_NUMBER    }, /* used on BODY */
  { TidyAttr_ROLE,                    "role",                    CH_PCDATA    },
  { TidyAttr_ROWS,                    "rows",                    CH_NUMBER    }, /* TEXTAREA */
  { TidyAttr_ROWSPAN,                 "rowspan",                 CH_NUMBER    }, /* table cells */
  { TidyAttr_RULES,                   "rules",                   CH_TRULES    }, /* TABLE */
  { TidyAttr_SCHEME,                  "scheme",                  CH_PCDATA    }, /* META */
  { TidyAttr_SCOPE,                   "scope",                   CH_SCOPE     }, /* table cells */
  { TidyAttr_SCROLLING,               "scrolling",               CH_SCROLL    }, /* yes, no or auto */
  { TidyAttr_SELECTED,                "selected",                CH_BOOL      }, /* OPTION */
  { TidyAttr_SHAPE,                   "shape",                   CH_SHAPE     }, /* AREA, A */
  { TidyAttr_SHOWGRID,                "showgrid",                CH_BOOL      }, /* TABLE Adobe golive */
  { TidyAttr_SHOWGRIDX,               "showgridx",               CH_BOOL      }, /* TABLE Adobe golive*/
  { TidyAttr_SHOWGRIDY,               "showgridy",               CH_BOOL      }, /* TABLE Adobe golive*/
  { TidyAttr_SIZE,                    "size",                    CH_NUMBER    }, /* HR, FONT, BASEFONT, SELECT */
  { TidyAttr_SPAN,                    "span",                    CH_NUMBER    }, /* COL, COLGROUP */
  { TidyAttr_SRC,                     "src",                     CH_URL       }, /* IMG, FRAME, IFRAME */
  { TidyAttr_SRCSET,                  "srcset",                  CH_PCDATA    }, /* IMG (HTML5) */
  { TidyAttr_STANDBY,                 "standby",                 CH_PCDATA    }, /* OBJECT */
  { TidyAttr_START,                   "start",                   CH_NUMBER    }, /* OL */
  { TidyAttr_STYLE,                   "style",                   CH_PCDATA    }, 
  { TidyAttr_SUMMARY,                 "summary",                 CH_PCDATA    }, /* TABLE */
  { TidyAttr_TABINDEX,                "tabindex",                CH_NUMBER    }, /* fields, OBJECT  and A */
  { TidyAttr_TARGET,                  "target",                  CH_TARGET    }, /* names a frame/window */
  { TidyAttr_TEXT,                    "text",                    CH_COLOR     }, /* BODY */
  { TidyAttr_TITLE,                   "title",                   CH_PCDATA    }, /* text tool tip */
  { TidyAttr_TOPMARGIN,               "topmargin",               CH_NUMBER    }, /* used on BODY */
  { TidyAttr_TRANSLATE,               "translate",               CH_BOOL      }, /* HTML5 global attribute */
  { TidyAttr_TYPE,                    "type",                    CH_TYPE      }, /* also used by SPACER */
  { TidyAttr_USEMAP,                  "usemap",                  CH_URL       }, /* things with images */
  { TidyAttr_VALIGN,                  "valign",                  CH_VALIGN    }, 
  { TidyAttr_VALUE,                   "value",                   CH_PCDATA    }, 
  { TidyAttr_VALUETYPE,               "valuetype",               CH_VTYPE     }, /* PARAM: data, ref, object */
  { TidyAttr_VERSION,                 "version",                 CH_PCDATA    }, /* HTML <?xml?> */
  { TidyAttr_VLINK,                   "vlink",                   CH_COLOR     }, /* BODY */
  { TidyAttr_VSPACE,                  "vspace",                  CH_NUMBER    }, /* IMG, OBJECT, APPLET */
  { TidyAttr_WIDTH,                   "width",                   CH_LENGTH    }, /* pixels only for TD/TH */
  { TidyAttr_WRAP,                    "wrap",                    CH_PCDATA    }, /* textarea */
  { TidyAttr_XML_LANG,                "xml:lang",                CH_LANG      }, /* XML language */
  { TidyAttr_XML_SPACE,               "xml:space",               CH_PCDATA    }, /* XML white space */

  /* todo: VERS_ALL is wrong! */
  { TidyAttr_XMLNS,                   "xmlns",                   CH_PCDATA    }, /* name space */
  { TidyAttr_EVENT,                   "event",                   CH_PCDATA    }, /* reserved for <script> */
  { TidyAttr_METHODS,                 "methods",                 CH_PCDATA    }, /* for <a>, never implemented */
  { TidyAttr_N,                       "n",                       CH_PCDATA    }, /* for <nextid> */
  { TidyAttr_SDAFORM,                 "sdaform",                 CH_PCDATA    }, /* SDATA attribute in HTML 2.0 */
  { TidyAttr_SDAPREF,                 "sdapref",                 CH_PCDATA    }, /* SDATA attribute in HTML 2.0 */
  { TidyAttr_SDASUFF,                 "sdasuff",                 CH_PCDATA    }, /* SDATA attribute in HTML 2.0 */
  { TidyAttr_URN,                     "urn",                     CH_PCDATA    }, /* for <a>, never implemented */

  /* HTML5 */
  { TidyAttr_ASYNC,                   "async",                   CH_BOOL     }, /* <script src="..." async> */
  { TidyAttr_AUTOCOMPLETE,            "autocomplete",            CH_PCDATA   },
  { TidyAttr_AUTOFOCUS,               "autofocus",               CH_PCDATA   },
  { TidyAttr_AUTOPLAY,                "autoplay",                CH_PCDATA   },
  { TidyAttr_CHALLENGE,               "challenge",               CH_PCDATA   },
  { TidyAttr_CONTENTEDITABLE,         "contenteditable",         CH_PCDATA   },
  { TidyAttr_CONTEXTMENU,             "contextmenu",             CH_PCDATA   },
  { TidyAttr_CONTROLS,                "controls",                CH_PCDATA   },
  { TidyAttr_DEFAULT,                 "default",                 CH_PCDATA   },
  { TidyAttr_DIRNAME,                 "dirname",                 CH_PCDATA   },
  { TidyAttr_DRAGGABLE,               "draggable",               CH_PCDATA   },
  { TidyAttr_DROPZONE,                "dropzone",                CH_PCDATA   },
  { TidyAttr_FORM,                    "form",                    CH_PCDATA   },
  { TidyAttr_FORMACTION,              "formaction",              CH_PCDATA   },
  { TidyAttr_FORMENCTYPE,             "formenctype",             CH_PCDATA   },
  { TidyAttr_FORMMETHOD,              "formmethod",              CH_PCDATA   },
  { TidyAttr_FORMNOVALIDATE,          "formnovalidate",          CH_PCDATA   },
  { TidyAttr_FORMTARGET,              "formtarget",              CH_PCDATA   },
  { TidyAttr_HIDDEN,                  "hidden",                  CH_PCDATA   },
  { TidyAttr_HIGH,                    "high",                    CH_PCDATA   },
  { TidyAttr_ICON,                    "icon",                    CH_PCDATA   },
  { TidyAttr_KEYTYPE,                 "keytype",                 CH_PCDATA   },
  { TidyAttr_KIND,                    "kind",                    CH_PCDATA   },
  { TidyAttr_LIST,                    "list",                    CH_PCDATA   },
  { TidyAttr_LOOP,                    "loop",                    CH_PCDATA   },
  { TidyAttr_LOW,                     "low",                     CH_PCDATA   },
  { TidyAttr_MANIFEST,                "manifest",                CH_PCDATA   },
  { TidyAttr_MAX,                     "max",                     CH_PCDATA   },
  { TidyAttr_MEDIAGROUP,              "mediagroup",              CH_PCDATA   },
  { TidyAttr_MIN,                     "min",                     CH_PCDATA   },
  { TidyAttr_NOVALIDATE,              "novalidate",              CH_PCDATA   },
  { TidyAttr_OPEN,                    "open",                    CH_PCDATA   },
  { TidyAttr_OPTIMUM,                 "optimum",                 CH_PCDATA   },
  { TidyAttr_OnABORT,                 "onabort",                 CH_PCDATA   },
  { TidyAttr_OnAFTERPRINT,            "onafterprint",            CH_PCDATA   },
  { TidyAttr_OnBEFOREPRINT,           "onbeforeprint",           CH_PCDATA   },
  { TidyAttr_OnCANPLAY,               "oncanplay",               CH_PCDATA   },
  { TidyAttr_OnCANPLAYTHROUGH,        "oncanplaythrough",        CH_PCDATA   },
  { TidyAttr_OnCONTEXTMENU,           "oncontextmenu",           CH_PCDATA   },
  { TidyAttr_OnCUECHANGE,             "oncuechange",             CH_PCDATA   },
  { TidyAttr_OnDRAG,                  "ondrag",                  CH_PCDATA   },
  { TidyAttr_OnDRAGEND,               "ondragend",               CH_PCDATA   },
  { TidyAttr_OnDRAGENTER,             "ondragenter",             CH_PCDATA   },
  { TidyAttr_OnDRAGLEAVE,             "ondragleave",             CH_PCDATA   },
  { TidyAttr_OnDRAGOVER,              "ondragover",              CH_PCDATA   },
  { TidyAttr_OnDRAGSTART,             "ondragstart",             CH_PCDATA   },
  { TidyAttr_OnDROP,                  "ondrop",                  CH_PCDATA   },
  { TidyAttr_OnDURATIONCHANGE,        "ondurationchange",        CH_PCDATA   },
  { TidyAttr_OnEMPTIED,               "onemptied",               CH_PCDATA   },
  { TidyAttr_OnENDED,                 "onended",                 CH_PCDATA   },
  { TidyAttr_OnERROR,                 "onerror",                 CH_PCDATA   },
  { TidyAttr_OnHASHCHANGE,            "onhashchange",            CH_PCDATA   },
  { TidyAttr_OnINPUT,                 "oninput",                 CH_PCDATA   },
  { TidyAttr_OnINVALID,               "oninvalid",               CH_PCDATA   },
  { TidyAttr_OnLOADEDDATA,            "onloadeddata",            CH_PCDATA   },
  { TidyAttr_OnLOADEDMETADATA,        "onloadedmetadata",        CH_PCDATA   },
  { TidyAttr_OnLOADSTART,             "onloadstart",             CH_PCDATA   },
  { TidyAttr_OnMESSAGE,               "onmessage",               CH_PCDATA   },
  { TidyAttr_OnMOUSEWHEEL,            "onmousewheel",            CH_PCDATA   },
  { TidyAttr_OnOFFLINE,               "onoffline",               CH_PCDATA   },
  { TidyAttr_OnONLINE,                "ononline",                CH_PCDATA   },
  { TidyAttr_OnPAGEHIDE,              "onpagehide",              CH_PCDATA   },
  { TidyAttr_OnPAGESHOW,              "onpageshow",              CH_PCDATA   },
  { TidyAttr_OnPAUSE,                 "onpause",                 CH_PCDATA   },
  { TidyAttr_OnPLAY,                  "onplay",                  CH_PCDATA   },
  { TidyAttr_OnPLAYING,               "onplaying",               CH_PCDATA   },
  { TidyAttr_OnPOPSTATE,              "onpopstate",              CH_PCDATA   },
  { TidyAttr_OnPROGRESS,              "onprogress",              CH_PCDATA   },
  { TidyAttr_OnRATECHANGE,            "onratechange",            CH_PCDATA   },
  { TidyAttr_OnREADYSTATECHANGE,      "onreadystatechange",      CH_PCDATA   },
  { TidyAttr_OnREDO,                  "onredo",                  CH_PCDATA   },
  { TidyAttr_OnRESIZE,                "onresize",                CH_PCDATA   },
  { TidyAttr_OnSCROLL,                "onscroll",                CH_PCDATA   },
  { TidyAttr_OnSEEKED,                "onseeked",                CH_PCDATA   },
  { TidyAttr_OnSEEKING,               "onseeking",               CH_PCDATA   },
  { TidyAttr_OnSHOW,                  "onshow",                  CH_PCDATA   },
  { TidyAttr_OnSTALLED,               "onstalled",               CH_PCDATA   },
  { TidyAttr_OnSTORAGE,               "onstorage",               CH_PCDATA   },
  { TidyAttr_OnSUSPEND,               "onsuspend",               CH_PCDATA   },
  { TidyAttr_OnTIMEUPDATE,            "ontimeupdate",            CH_PCDATA   },
  { TidyAttr_OnUNDO,                  "onundo",                  CH_PCDATA   },
  { TidyAttr_OnVOLUMECHANGE,          "onvolumechange",          CH_PCDATA   },
  { TidyAttr_OnWAITING,               "onwaiting",               CH_PCDATA   },
  { TidyAttr_PATTERN,                 "pattern",                 CH_PCDATA   },
  { TidyAttr_PLACEHOLDER,             "placeholder",             CH_PCDATA   },
  { TidyAttr_POSTER,                  "poster",                  CH_PCDATA   },
  { TidyAttr_PRELOAD,                 "preload",                 CH_PCDATA   },
  { TidyAttr_PUBDATE,                 "pubdate",                 CH_PCDATA   },
  { TidyAttr_RADIOGROUP,              "radiogroup",              CH_PCDATA   },
  { TidyAttr_REQUIRED,                "required",                CH_PCDATA   },
  { TidyAttr_REVERSED,                "reversed",                CH_PCDATA   },
  { TidyAttr_SANDBOX,                 "sandbox",                 CH_PCDATA   },
  { TidyAttr_SCOPED,                  "scoped",                  CH_PCDATA   },
  { TidyAttr_SEAMLESS,                "seamless",                CH_PCDATA   },
  { TidyAttr_SIZES,                   "sizes",                   CH_PCDATA   },
  { TidyAttr_SPELLCHECK,              "spellcheck",              CH_PCDATA   },
  { TidyAttr_SRCDOC,                  "srcdoc",                  CH_PCDATA   },
  { TidyAttr_SRCLANG,                 "srclang",                 CH_PCDATA   },
  { TidyAttr_STEP,                    "step",                    CH_PCDATA   },

  /* HTML5 Aria Attributes */
  { TidyAttr_ARIA_ACTIVEDESCENDANT,   "aria-activedescendant",   CH_PCDATA   },
  { TidyAttr_ARIA_ATOMIC,             "aria-atomic",             CH_PCDATA   },
  { TidyAttr_ARIA_AUTOCOMPLETE,       "aria-autocomplete",       CH_PCDATA   },
  { TidyAttr_ARIA_BUSY,               "aria-busy",               CH_PCDATA   },
  { TidyAttr_ARIA_CHECKED,            "aria-checked",            CH_PCDATA   },
  { TidyAttr_ARIA_CONTROLS,           "aria-controls",           CH_PCDATA   },
  { TidyAttr_ARIA_DESCRIBEDBY,        "aria-describedby",        CH_PCDATA   },
  { TidyAttr_ARIA_DISABLED,           "aria-disabled",           CH_PCDATA   },
  { TidyAttr_ARIA_DROPEFFECT,         "aria-dropeffect",         CH_PCDATA   },
  { TidyAttr_ARIA_EXPANDED,           "aria-expanded",           CH_PCDATA   },
  { TidyAttr_ARIA_FLOWTO,             "aria-flowto",             CH_PCDATA   },
  { TidyAttr_ARIA_GRABBED,            "aria-grabbed",            CH_PCDATA   },
  { TidyAttr_ARIA_HASPOPUP,           "aria-haspopup",           CH_PCDATA   },
  { TidyAttr_ARIA_HIDDEN,             "aria-hidden",             CH_PCDATA   },
  { TidyAttr_ARIA_INVALID,            "aria-invalid",            CH_PCDATA   },
  { TidyAttr_ARIA_LABEL,              "aria-label",              CH_PCDATA   },
  { TidyAttr_ARIA_LABELLEDBY,         "aria-labelledby",         CH_PCDATA   },
  { TidyAttr_ARIA_LEVEL,              "aria-level",              CH_PCDATA   },
  { TidyAttr_ARIA_LIVE,               "aria-live",               CH_PCDATA   },
  { TidyAttr_ARIA_MULTILINE,          "aria-multiline",          CH_PCDATA   },
  { TidyAttr_ARIA_MULTISELECTABLE,    "aria-multiselectable",    CH_PCDATA   },
  { TidyAttr_ARIA_ORIENTATION,        "aria-orientation",        CH_PCDATA   },
  { TidyAttr_ARIA_OWNS,               "aria-owns",               CH_PCDATA   },
  { TidyAttr_ARIA_POSINSET,           "aria-posinset",           CH_PCDATA   },
  { TidyAttr_ARIA_PRESSED,            "aria-pressed",            CH_PCDATA   },
  { TidyAttr_ARIA_READONLY,           "aria-readonly",           CH_PCDATA   },
  { TidyAttr_ARIA_RELEVANT,           "aria-relevant",           CH_PCDATA   },
  { TidyAttr_ARIA_REQUIRED,           "aria-required",           CH_PCDATA   },
  { TidyAttr_ARIA_SELECTED,           "aria-selected",           CH_PCDATA   },
  { TidyAttr_ARIA_SETSIZE,            "aria-setsize",            CH_PCDATA   },
  { TidyAttr_ARIA_SORT,               "aria-sort",               CH_PCDATA   },
  { TidyAttr_ARIA_VALUEMAX,           "aria-valuemax",           CH_PCDATA   },
  { TidyAttr_ARIA_VALUEMIN,           "aria-valuemin",           CH_PCDATA   },
  { TidyAttr_ARIA_VALUENOW,           "aria-valuenow",           CH_PCDATA   },
  { TidyAttr_ARIA_VALUETEXT,          "aria-valuetext",          CH_PCDATA   },

  { TidyAttr_X,                       "x",                       CH_PCDATA    }, /* for <svg> */
  { TidyAttr_Y,                       "y",                       CH_PCDATA    }, /* for <svg> */
#if 0   /* with uppercase chars taken directly from W3C; are these case-insensitive everywhere? */
  { TidyAttr_VIEWBOX,                 "viewBox",                 VERS_INLINE_SVG,   CH_PCDATA    }, /* for <svg> */
  { TidyAttr_PRESERVEASPECTRATIO,     "preserveAspectRatio",     VERS_INLINE_SVG,   CH_PCDATA    }, /* for <svg> */
  { TidyAttr_ZOOMANDPAN,              "zoomAndPan",              VERS_INLINE_SVG,   CH_PCDATA    }, /* for <svg> */
  { TidyAttr_BASEPROFILE,             "baseProfile",             VERS_INLINE_SVG,   CH_PCDATA    }, /* for <svg> */
  { TidyAttr_CONTENTSCRIPTTYPE,       "contentScriptType",       VERS_INLINE_SVG,   CH_PCDATA    }, /* for <svg> */
  { TidyAttr_CONTENTSTYLETYPE,        "contentStyleType",        VERS_INLINE_SVG,   CH_PCDATA    }, /* for <svg> */
#else
  { TidyAttr_VIEWBOX,                  "viewbox",                CH_PCDATA    }, /* for <svg> */
  { TidyAttr_PRESERVEASPECTRATIO,      "preserveaspectratio",    CH_PCDATA    }, /* for <svg> */
  { TidyAttr_ZOOMANDPAN,               "zoomandpan",             CH_PCDATA    }, /* for <svg> */
  { TidyAttr_BASEPROFILE,              "baseprofile",            CH_PCDATA    }, /* for <svg> */
  { TidyAttr_CONTENTSCRIPTTYPE,        "contentscripttype",      CH_PCDATA    }, /* for <svg> */
  { TidyAttr_CONTENTSTYLETYPE,         "contentstyletype",       CH_PCDATA    }, /* for <svg> */
#endif
  { TidyAttr_DISPLAY,                  "display",                CH_PCDATA   }, /* on MATH tag (html5) */

  /* RDFa Attributes */
  { TidyAttr_ABOUT,                    "about",                  CH_RDFASCURIE },
  { TidyAttr_DATATYPE,                 "datatype",               CH_RDFATERM   },
  { TidyAttr_INLIST,                   "inlist",                 CH_BOOL       },
  { TidyAttr_PREFIX,                   "prefix",                 CH_RDFAPREFIX },
  { TidyAttr_PROPERTY,                 "property",               CH_RDFATERMS  },
  { TidyAttr_RESOURCE,                 "resource",               CH_RDFASCURIE },
  { TidyAttr_TYPEOF,                   "typeof",                 CH_RDFATERMS  },
  { TidyAttr_VOCAB,                    "vocab",                  CH_URL        },

  /* this must be the final entry */
  { N_TIDY_ATTRIBS,                    NULL,                     NULL         }
};

static uint AttributeVersions(TidyNode node, TidyAttr attval)
{
    uint i;

    /* Override or add to items in attrdict.c */
    if (attval && attval->attribute) {
        /* HTML5 data-* attributes can't be added generically; handle here. */
        if (TY_(tmbstrncmp)(attval->attribute, "data-", 5) == 0)
            return (XH50 | HT50);
    }
    /* TODO: maybe this should return VERS_PROPRIETARY instead? */
    if (!attval || !attval->dict)
        return VERS_UNKNOWN;

    if (!(!node || !node->tag || !node->tag->attrvers))
        for (i = 0; node->tag->attrvers[i].attribute; ++i)
            if (node->tag->attrvers[i].attribute == attval->dict->id)
                return node->tag->attrvers[i].versions;

    return VERS_PROPRIETARY;
}


/* return the version of the attribute "id" of element "node" */
uint TY_(NodeAttributeVersions)( TidyNode node, TidyAttrId id )
{
    uint i;

    if (!node || !node->tag || !node->tag->attrvers)
        return VERS_UNKNOWN;

    for (i = 0; node->tag->attrvers[i].attribute; ++i)
        if (node->tag->attrvers[i].attribute == id)
            return node->tag->attrvers[i].versions;

    return VERS_UNKNOWN;
}

/* returns true if the element is a W3C defined element
 * but the element/attribute combination is not. We're
 * only defining as "proprietary" items that are not in
 * the element's AttrVersion structure.
 */
Bool TY_(AttributeIsProprietary)(TidyNode node, TidyAttr attval)
{
    if (!node || !attval)
        return no;

    if (!node->tag)
        return no;

    if (!(node->tag->versions & VERS_ALL))
        return no;

    if (AttributeVersions(node, attval) & VERS_ALL)
        return no;

    return yes;
}

/* returns true if the element is a W3C defined element
 * but the element/attribute combination is not. We're
 * considering it a mismatch if the document version
 * does not allow the attribute as called out in its
 * AttrVersion structure.
 */
Bool TY_(AttributeIsMismatched)(TidyNode node, TidyAttr attval, TidyDoc doc)
{
    uint doctype;
    
    if (!node || !attval)
        return no;
    
    if (!node->tag)
        return no;
    
    if (!(node->tag->versions & VERS_ALL))
        return no;

    doctype = doc->lexer->versionEmitted == 0 ? doc->lexer->doctype : doc->lexer->versionEmitted;

    if (AttributeVersions(node, attval) & doctype)
        return no;
    
    return yes;
}


/* used by CheckColor() */
struct _colors
{
    ctmbstr name;
    ctmbstr hex;
};

static const struct _colors colors[] =
{
    { "black",   "#000000" },
    { "green",   "#008000" },
    { "silver",  "#C0C0C0" },
    { "lime",    "#00FF00" },
    { "gray",    "#808080" },
    { "olive",   "#808000" },
    { "white",   "#FFFFFF" },
    { "yellow",  "#FFFF00" },
    { "maroon",  "#800000" },
    { "navy",    "#000080" },
    { "red",     "#FF0000" },
    { "blue",    "#0000FF" },
    { "purple",  "#800080" },
    { "teal",    "#008080" },
    { "fuchsia", "#FF00FF" },
    { "aqua",    "#00FFFF" },
    { NULL,      NULL      }
};

static ctmbstr GetColorCode(ctmbstr name)
{
    uint i;

    for (i = 0; colors[i].name; ++i)
        if (TY_(tmbstrcasecmp)(name, colors[i].name) == 0)
            return colors[i].hex;

    return NULL;
}

static ctmbstr GetColorName(ctmbstr code)
{
    uint i;

    for (i = 0; colors[i].name; ++i)
        if (TY_(tmbstrcasecmp)(code, colors[i].hex) == 0)
            return colors[i].name;

    return NULL;
}

#if 0
static const struct _colors fancy_colors[] =
{
    { "darkgreen",            "#006400" },
    { "antiquewhite",         "#FAEBD7" },
    { "aqua",                 "#00FFFF" },
    { "aquamarine",           "#7FFFD4" },
    { "azure",                "#F0FFFF" },
    { "beige",                "#F5F5DC" },
    { "bisque",               "#FFE4C4" },
    { "black",                "#000000" },
    { "blanchedalmond",       "#FFEBCD" },
    { "blue",                 "#0000FF" },
    { "blueviolet",           "#8A2BE2" },
    { "brown",                "#A52A2A" },
    { "burlywood",            "#DEB887" },
    { "cadetblue",            "#5F9EA0" },
    { "chartreuse",           "#7FFF00" },
    { "chocolate",            "#D2691E" },
    { "coral",                "#FF7F50" },
    { "cornflowerblue",       "#6495ED" },
    { "cornsilk",             "#FFF8DC" },
    { "crimson",              "#DC143C" },
    { "cyan",                 "#00FFFF" },
    { "darkblue",             "#00008B" },
    { "darkcyan",             "#008B8B" },
    { "darkgoldenrod",        "#B8860B" },
    { "darkgray",             "#A9A9A9" },
    { "darkgreen",            "#006400" },
    { "darkkhaki",            "#BDB76B" },
    { "darkmagenta",          "#8B008B" },
    { "darkolivegreen",       "#556B2F" },
    { "darkorange",           "#FF8C00" },
    { "darkorchid",           "#9932CC" },
    { "darkred",              "#8B0000" },
    { "darksalmon",           "#E9967A" },
    { "darkseagreen",         "#8FBC8F" },
    { "darkslateblue",        "#483D8B" },
    { "darkslategray",        "#2F4F4F" },
    { "darkturquoise",        "#00CED1" },
    { "darkviolet",           "#9400D3" },
    { "deeppink",             "#FF1493" },
    { "deepskyblue",          "#00BFFF" },
    { "dimgray",              "#696969" },
    { "dodgerblue",           "#1E90FF" },
    { "firebrick",            "#B22222" },
    { "floralwhite",          "#FFFAF0" },
    { "forestgreen",          "#228B22" },
    { "fuchsia",              "#FF00FF" },
    { "gainsboro",            "#DCDCDC" },
    { "ghostwhite",           "#F8F8FF" },
    { "gold",                 "#FFD700" },
    { "goldenrod",            "#DAA520" },
    { "gray",                 "#808080" },
    { "green",                "#008000" },
    { "greenyellow",          "#ADFF2F" },
    { "honeydew",             "#F0FFF0" },
    { "hotpink",              "#FF69B4" },
    { "indianred",            "#CD5C5C" },
    { "indigo",               "#4B0082" },
    { "ivory",                "#FFFFF0" },
    { "khaki",                "#F0E68C" },
    { "lavender",             "#E6E6FA" },
    { "lavenderblush",        "#FFF0F5" },
    { "lawngreen",            "#7CFC00" },
    { "lemonchiffon",         "#FFFACD" },
    { "lightblue",            "#ADD8E6" },
    { "lightcoral",           "#F08080" },
    { "lightcyan",            "#E0FFFF" },
    { "lightgoldenrodyellow", "#FAFAD2" },
    { "lightgreen",           "#90EE90" },
    { "lightgrey",            "#D3D3D3" },
    { "lightpink",            "#FFB6C1" },
    { "lightsalmon",          "#FFA07A" },
    { "lightseagreen",        "#20B2AA" },
    { "lightskyblue",         "#87CEFA" },
    { "lightslategray",       "#778899" },
    { "lightsteelblue",       "#B0C4DE" },
    { "lightyellow",          "#FFFFE0" },
    { "lime",                 "#00FF00" },
    { "limegreen",            "#32CD32" },
    { "linen",                "#FAF0E6" },
    { "magenta",              "#FF00FF" },
    { "maroon",               "#800000" },
    { "mediumaquamarine",     "#66CDAA" },
    { "mediumblue",           "#0000CD" },
    { "mediumorchid",         "#BA55D3" },
    { "mediumpurple",         "#9370DB" },
    { "mediumseagreen",       "#3CB371" },
    { "mediumslateblue",      "#7B68EE" },
    { "mediumspringgreen",    "#00FA9A" },
    { "mediumturquoise",      "#48D1CC" },
    { "mediumvioletred",      "#C71585" },
    { "midnightblue",         "#191970" },
    { "mintcream",            "#F5FFFA" },
    { "mistyrose",            "#FFE4E1" },
    { "moccasin",             "#FFE4B5" },
    { "navajowhite",          "#FFDEAD" },
    { "navy",                 "#000080" },
    { "oldlace",              "#FDF5E6" },
    { "olive",                "#808000" },
    { "olivedrab",            "#6B8E23" },
    { "orange",               "#FFA500" },
    { "orangered",            "#FF4500" },
    { "orchid",               "#DA70D6" },
    { "palegoldenrod",        "#EEE8AA" },
    { "palegreen",            "#98FB98" },
    { "paleturquoise",        "#AFEEEE" },
    { "palevioletred",        "#DB7093" },
    { "papayawhip",           "#FFEFD5" },
    { "peachpuff",            "#FFDAB9" },
    { "peru",                 "#CD853F" },
    { "pink",                 "#FFC0CB" },
    { "plum",                 "#DDA0DD" },
    { "powderblue",           "#B0E0E6" },
    { "purple",               "#800080" },
    { "red",                  "#FF0000" },
    { "rosybrown",            "#BC8F8F" },
    { "royalblue",            "#4169E1" },
    { "saddlebrown",          "#8B4513" },
    { "salmon",               "#FA8072" },
    { "sandybrown",           "#F4A460" },
    { "seagreen",             "#2E8B57" },
    { "seashell",             "#FFF5EE" },
    { "sienna",               "#A0522D" },
    { "silver",               "#C0C0C0" },
    { "skyblue",              "#87CEEB" },
    { "slateblue",            "#6A5ACD" },
    { "slategray",            "#708090" },
    { "snow",                 "#FFFAFA" },
    { "springgreen",          "#00FF7F" },
    { "steelblue",            "#4682B4" },
    { "tan",                  "#D2B48C" },
    { "teal",                 "#008080" },
    { "thistle",              "#D8BFD8" },
    { "tomato",               "#FF6347" },
    { "turquoise",            "#40E0D0" },
    { "violet",               "#EE82EE" },
    { "wheat",                "#F5DEB3" },
    { "white",                "#FFFFFF" },
    { "whitesmoke",           "#F5F5F5" },
    { "yellow",               "#FFFF00" },
    { "yellowgreen",          "#9ACD32" },
    { NULL,                   NULL      }
};
#endif

#if ATTRIBUTE_HASH_LOOKUP
static uint attrsHash(ctmbstr s)
{
    uint hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31*hashval;

    return hashval % ATTRIBUTE_HASH_SIZE;
}

static const Attribute *attrsInstall(TidyDoc doc, TidyAttribImpl * attribs,
                                const Attribute* old)
{
    AttrHash *np;
    uint hashval;

    if (old)
    {
        np = (AttrHash *)TidyDocAlloc(doc, sizeof(*np));
        np->attr = old;

        hashval = attrsHash(old->name);
        np->next = attribs->hashtab[hashval];
        attribs->hashtab[hashval] = np;
    }

    return old;
}

static void attrsRemoveFromHash( TidyDoc doc, TidyAttribImpl *attribs,
                            ctmbstr s )
{
    uint h = attrsHash(s);
    AttrHash *p, *prev = NULL;
    for (p = attribs->hashtab[h]; p && p->attr; p = p->next)
    {
        if (TY_(tmbstrcmp)(s, p->attr->name) == 0)
        {
            AttrHash* next = p->next;
            if ( prev )
                prev->next = next; 
            else
                attribs->hashtab[h] = next;
            TidyDocFree(doc, p);
            return;
        }
        prev = p;
    }
}

static void attrsEmptyHash( TidyDoc doc, TidyAttribImpl * attribs )
{
    AttrHash *dict, *next;
    uint i;

    for (i = 0; i < ATTRIBUTE_HASH_SIZE; ++i)
    {
        dict = attribs->hashtab[i];

        while(dict)
        {
            next = dict->next;
            TidyDocFree(doc, dict);
            dict = next;
        }

        attribs->hashtab[i] = NULL;
    }
}
#endif

static const Attribute* attrsLookup(TidyDoc doc,
                               TidyAttribImpl* ARG_UNUSED(attribs),
                               ctmbstr atnam)
{
    const Attribute *np;
#if ATTRIBUTE_HASH_LOOKUP
    const AttrHash *p;
#endif

    if (!atnam)
        return NULL;

#if ATTRIBUTE_HASH_LOOKUP
    for (p = attribs->hashtab[attrsHash(atnam)]; p && p->attr; p = p->next)
        if (TY_(tmbstrcmp)(atnam, p->attr->name) == 0)
            return p->attr;

    for (np = attribute_defs; np && np->name; ++np)
        if (TY_(tmbstrcmp)(atnam, np->name) == 0)
            return attrsInstall(doc, attribs, np);
#else
    for (np = attribute_defs; np && np->name; ++np)
        if (TY_(tmbstrcmp)(atnam, np->name) == 0)
            return np;
#endif

    return NULL;
}


/* Locate attributes by type */
TidyAttr TY_(AttrGetById)( TidyNode node, TidyAttrId id )
{
   TidyAttr av;
   for ( av = node->attributes; av; av = av->next )
   {
     if ( AttrIsId(av, id) )
         return av;
   }
   return NULL;
}

/* public method for finding attribute definition by name */
const Attribute* TY_(FindAttribute)( TidyDoc doc, TidyAttr attval )
{
    if ( attval )
       return attrsLookup( doc, &doc->attribs, attval->attribute );
    return NULL;
}

TidyAttr TY_(GetAttrByName)( TidyNode node, ctmbstr name )
{
    TidyAttr attr;
    for (attr = node->attributes; attr != NULL; attr = attr->next)
    {
        if (attr->attribute && TY_(tmbstrcmp)(attr->attribute, name) == 0)
            break;
    }
    return attr;
}

void TY_(DropAttrByName)( TidyDoc doc, TidyNode node, ctmbstr name )
{
    TidyAttr attr, prev = NULL, next;

    for (attr = node->attributes; attr != NULL; prev = attr, attr = next)
    {
        next = attr->next;

        if (attr->attribute && TY_(tmbstrcmp)(attr->attribute, name) == 0)
        {
            if (prev)
                 prev->next = next;
            else
                 node->attributes = next;

            TY_(FreeAttribute)( doc, attr ); 
            break;
        }
    }
}

TidyAttr TY_(AddAttribute)( TidyDoc doc,
                           TidyNode node, ctmbstr name, ctmbstr value )
{
    TidyAttr av = TY_(NewAttribute)(doc);
    av->delim = '"';
    av->attribute = TY_(tmbstrdup)(doc->allocator, name);

    if (value)
        av->value = TY_(tmbstrdup)(doc->allocator, value);
    else
        av->value = NULL;

    av->dict = attrsLookup(doc, &doc->attribs, name);

    TY_(InsertAttributeAtEnd)(node, av);
    return av;
}

TidyAttr TY_(RepairAttrValue)(TidyDoc doc, TidyNode node, ctmbstr name, ctmbstr value)
{
    TidyAttr old = TY_(GetAttrByName)(node, name);

    if (old)
    {
        if (old->value)
            TidyDocFree(doc, old->value);
        if (value)
            old->value = TY_(tmbstrdup)(doc->allocator, value);
        else
            old->value = NULL;

        return old;
    }
    else
        return TY_(AddAttribute)(doc, node, name, value);
}

static Bool CheckAttrType( TidyDoc doc,
                           ctmbstr attrname, AttrCheck type )
{
    const Attribute* np = attrsLookup( doc, &doc->attribs, attrname );
    return (Bool)( np && np->attrchk == type );
}

Bool TY_(IsUrl)( TidyDoc doc, ctmbstr attrname )
{
    return CheckAttrType( doc, attrname, CH_URL );
}

/*
Bool IsBool( TidyDoc doc, ctmbstr attrname )
{
    return CheckAttrType( doc, attrname, CH_BOOL );
}
*/

Bool TY_(IsScript)( TidyDoc doc, ctmbstr attrname )
{
    return CheckAttrType( doc, attrname, CH_SCRIPT );
}

/* may id or name serve as anchor? */
Bool TY_(IsAnchorElement)( TidyDoc ARG_UNUSED(doc), TidyNode node)
{
    TidyTagId tid = TagId( node );
    if ( tid == TidyTag_A      ||
         tid == TidyTag_APPLET ||
         tid == TidyTag_FORM   ||
         tid == TidyTag_FRAME  ||
         tid == TidyTag_IFRAME ||
         tid == TidyTag_IMG    ||
         tid == TidyTag_MAP )
        return yes;

    return no;
}

/*
  In CSS1, selectors can contain only the characters A-Z, 0-9,
  and Unicode characters 161-255, plus dash (-); they cannot start
  with a dash or a digit; they can also contain escaped characters
  and any Unicode character as a numeric code (see next item).

  The backslash followed by at most four hexadecimal digits
  (0..9A..F) stands for the Unicode character with that number.

  Any character except a hexadecimal digit can be escaped to remove
  its special meaning, by putting a backslash in front.

  #508936 - CSS class naming for -clean option
*/
Bool TY_(IsCSS1Selector)( ctmbstr buf )
{
    Bool valid = yes;
    int esclen = 0;
    byte c;
    int pos;

    for ( pos=0; valid && (c = *buf++); ++pos )
    {
        if ( c == '\\' )
        {
            esclen = 1;  /* ab\555\444 is 4 chars {'a', 'b', \555, \444} */
        }
        else if ( isdigit( c ) )
        {
            /* Digit not 1st, unless escaped (Max length "\112F") */
            if ( esclen > 0 )
                valid = ( ++esclen < 6 );
            if ( valid )
                valid = ( pos>0 || esclen>0 );
        }
        else
        {
            valid = (
                esclen > 0                       /* Escaped? Anything goes. */
                || ( pos>0 && c == '-' )         /* Dash cannot be 1st char */
                || isalpha(c)                    /* a-z, A-Z anywhere */
                || ( c >= 161 )                  /* Unicode 161-255 anywhere */
            );
            esclen = 0;
        }
    }
    return valid;
}

/* free single anchor */
static void FreeAnchor(TidyDoc doc, Anchor *a)
{
    if ( a )
        TidyDocFree( doc, a->name );
    TidyDocFree( doc, a );
}

static uint anchorNameHash(ctmbstr s)
{
    uint hashval = 0;
    /* Issue #149 - an inferred name can be null. avoid crash */
    if (s) 
    {
        for ( ; *s != '\0'; s++) {
            tmbchar c = TY_(ToLower)( *s );
            hashval = c + 31*hashval;
        }
    }
    return hashval % ANCHOR_HASH_SIZE;
}

/*\
 *  New Service for HTML5
 *  Issue #185 - Treat elements ids as case-sensitive
 *  if in HTML5 modes, make hash of value AS IS!
\*/
static uint anchorNameHash5(ctmbstr s)
{
    uint hashval = 0;
    /* Issue #149 - an inferred name can be null. avoid crash */
    if (s) 
    {
        for ( ; *s != '\0'; s++) {
            tmbchar c = *s;
            hashval = c + 31*hashval;
        }
    }
    return hashval % ANCHOR_HASH_SIZE;
}


/*\ 
 *  removes anchor for specific node 
 *  Issue #185 - Treat elements ids as case-sensitive
 *  if in HTML5 modes, make hash of value AS IS!
\*/
void TY_(RemoveAnchorByNode)( TidyDoc doc, ctmbstr name, TidyNode node )
{
    TidyAttribImpl* attribs = &doc->attribs;
    Anchor *delme = NULL, *curr, *prev = NULL;
    uint h;
    if (TY_(HTMLVersion)(doc) == HT50)
        h = anchorNameHash5(name);
    else
        h = anchorNameHash(name);

    for ( curr=attribs->anchor_hash[h]; curr!=NULL; curr=curr->next )
    {
        if ( curr->node == node )
        {
            if ( prev )
                prev->next = curr->next;
            else
                attribs->anchor_hash[h] = curr->next;
            delme = curr;
            break;
        }
        prev = curr;
    }
    FreeAnchor( doc, delme );
}

/* initialize new anchor */
static Anchor* NewAnchor( TidyDoc doc, ctmbstr name, TidyNode node )
{
    Anchor *a = (Anchor*) TidyDocAlloc( doc, sizeof(Anchor) );

    a->name = TY_(tmbstrdup)( doc->allocator, name );
    a->name = TY_(tmbstrtolower)(a->name);
    a->node = node;
    a->next = NULL;

    return a;
}

/*\
 *  add new anchor to namespace 
 *  Issue #185 - Treat elements ids as case-sensitive
 *  if in HTML5 modes, make hash of value AS IS!
\*/
static Anchor* AddAnchor( TidyDoc doc, ctmbstr name, TidyNode node )
{
    TidyAttribImpl* attribs = &doc->attribs;
    Anchor *a = NewAnchor( doc, name, node );
    uint h;
    if (TY_(HTMLVersion)(doc) == HT50)
        h = anchorNameHash5(name);
    else
        h = anchorNameHash(name);

    if ( attribs->anchor_hash[h] == NULL)
         attribs->anchor_hash[h] = a;
    else
    {
        Anchor *here =  attribs->anchor_hash[h];
        while (here->next)
            here = here->next;
        here->next = a;
    }

    return attribs->anchor_hash[h];
}

/*\
 *  return node associated with anchor 
 *  Issue #185 - Treat elements ids as case-sensitive
 *  if in HTML5 modes, make hash of value AS IS!
\*/
static TidyNode GetNodeByAnchor( TidyDoc doc, ctmbstr name )
{
    TidyAttribImpl* attribs = &doc->attribs;
    Anchor *found;
    uint h;
    tmbstr lname = TY_(tmbstrdup)(doc->allocator, name);
    if (TY_(HTMLVersion)(doc) == HT50) {
        h = anchorNameHash5(name);
    }
    else
    {
        h = anchorNameHash(name);
        lname = TY_(tmbstrtolower)(lname);
    }

    for ( found = attribs->anchor_hash[h]; found != NULL; found = found->next )
    {
        if ( TY_(tmbstrcmp)(found->name, lname) == 0 )
            break;
    }
    
    TidyDocFree(doc, lname);
    if ( found )
        return found->node;
    return NULL;
}

/* free all anchors */
void TY_(FreeAnchors)( TidyDoc doc )
{
    TidyAttribImpl* attribs = &doc->attribs;
    Anchor* a;
    uint h;
    for (h = 0; h < ANCHOR_HASH_SIZE; h++) {
        while (NULL != (a = attribs->anchor_hash[h]) )
        {
            attribs->anchor_hash[h] = a->next;
            FreeAnchor(doc, a);
        }
    }
}

/* public method for inititializing attribute dictionary */
void TY_(InitAttrs)( TidyDoc doc )
{
    TidyClearMemory( &doc->attribs, sizeof(TidyAttribImpl) );
#ifdef _DEBUG
    {
      /* Attribute ID is index position in Attribute type lookup table */
      uint ix;
      for ( ix=0; ix < N_TIDY_ATTRIBS; ++ix )
      {
        const Attribute* dict = &attribute_defs[ ix ];
        assert( (uint) dict->id == ix );
      }
    }
#endif
}

/* free all declared attributes */
static void FreeDeclaredAttributes( TidyDoc doc )
{
    TidyAttribImpl* attribs = &doc->attribs;
    Attribute* dict;
    while ( NULL != (dict = attribs->declared_attr_list) )
    {
        attribs->declared_attr_list = dict->next;
#if ATTRIBUTE_HASH_LOOKUP
        attrsRemoveFromHash( doc, &doc->attribs, dict->name );
#endif
        TidyDocFree( doc, dict->name );
        TidyDocFree( doc, dict );
    }
}

void TY_(FreeAttrTable)( TidyDoc doc )
{
#if ATTRIBUTE_HASH_LOOKUP
    attrsEmptyHash( doc, &doc->attribs );
#endif
    TY_(FreeAnchors)( doc );
    FreeDeclaredAttributes( doc );
}

void TY_(AppendToClassAttr)( TidyDoc doc, TidyAttr classattr, ctmbstr classname )
{
    uint len = TY_(tmbstrlen)(classattr->value) +
        TY_(tmbstrlen)(classname) + 2;
    tmbstr s = (tmbstr) TidyDocAlloc( doc, len );
    s[0] = '\0';
    if (classattr->value)
    {
        TY_(tmbstrcpy)( s, classattr->value );
        TY_(tmbstrcat)( s, " " );
    }
    TY_(tmbstrcat)( s, classname );
    if (classattr->value)
        TidyDocFree( doc, classattr->value );
    classattr->value = s;
}

/* concatenate styles */
static void AppendToStyleAttr( TidyDoc doc, TidyAttr styleattr, ctmbstr styleprop )
{
    /*
    this doesn't handle CSS comments and
    leading/trailing white-space very well
    see http://www.w3.org/TR/css-style-attr
    */
    uint end = TY_(tmbstrlen)(styleattr->value);

    if (end >0 && styleattr->value[end - 1] == ';')
    {
        /* attribute ends with declaration seperator */

        styleattr->value = (tmbstr) TidyDocRealloc(doc, styleattr->value,
            end + TY_(tmbstrlen)(styleprop) + 2);

        TY_(tmbstrcat)(styleattr->value, " ");
        TY_(tmbstrcat)(styleattr->value, styleprop);
    }
    else if (end >0 && styleattr->value[end - 1] == '}')
    {
        /* attribute ends with rule set */

        styleattr->value = (tmbstr) TidyDocRealloc(doc, styleattr->value,
            end + TY_(tmbstrlen)(styleprop) + 6);

        TY_(tmbstrcat)(styleattr->value, " { ");
        TY_(tmbstrcat)(styleattr->value, styleprop);
        TY_(tmbstrcat)(styleattr->value, " }");
    }
    else
    {
        /* attribute ends with property value */

        styleattr->value = (tmbstr) TidyDocRealloc(doc, styleattr->value,
            end + TY_(tmbstrlen)(styleprop) + 3);

        if (end > 0)
            TY_(tmbstrcat)(styleattr->value, "; ");
        TY_(tmbstrcat)(styleattr->value, styleprop);
    }
}

/*
 the same attribute name can't be used
 more than once in each element
*/
static Bool AttrsHaveSameName( TidyAttr av1, TidyAttr av2)
{
    TidyAttrId id1, id2;

    id1 = AttrId(av1);
    id2 = AttrId(av2);
    if (id1 != TidyAttr_UNKNOWN && id2 != TidyAttr_UNKNOWN)
        return AttrsHaveSameId(av1, av2);
    if (id1 != TidyAttr_UNKNOWN || id2 != TidyAttr_UNKNOWN)
        return no;
    if (av1->attribute && av2->attribute)
        return TY_(tmbstrcmp)(av1->attribute, av2->attribute) == 0;
     return no;
}

void TY_(RepairDuplicateAttributes)( TidyDoc doc, TidyNode node, Bool isXml )
{
    TidyAttr first;

    for (first = node->attributes; first != NULL;)
    {
        TidyAttr second;
        Bool firstRedefined = no;

        if (!(first->asp == NULL && first->php == NULL))
        {
            first = first->next;
            continue;
        }

        for (second = first->next; second != NULL;)
        {
            TidyAttr temp;

            if (!(second->asp == NULL && second->php == NULL
                  && AttrsHaveSameName(first, second)))
            {
                second = second->next;
                continue;
            }

            /* first and second attribute have same local name */
            /* now determine what to do with this duplicate... */

            if (!isXml
                && attrIsCLASS(first) && cfgBool(doc, TidyJoinClasses)
                && AttrHasValue(first) && AttrHasValue(second))
            {
                /* concatenate classes */

                TY_(AppendToClassAttr)(doc, first, second->value);

                temp = second->next;
                TY_(ReportAttrError)( doc, node, second, JOINING_ATTRIBUTE);
                TY_(RemoveAttribute)( doc, node, second );
                second = temp;
            }
            else if (!isXml
                     && attrIsSTYLE(first) && cfgBool(doc, TidyJoinStyles)
                     && AttrHasValue(first) && AttrHasValue(second))
            {
                AppendToStyleAttr( doc, first, second->value );

                temp = second->next;
                TY_(ReportAttrError)( doc, node, second, JOINING_ATTRIBUTE);
                TY_(RemoveAttribute)( doc, node, second );
                second = temp;
            }
            else if ( cfg(doc, TidyDuplicateAttrs) == TidyKeepLast )
            {
                temp = first->next;
                TY_(ReportAttrError)( doc, node, first, REPEATED_ATTRIBUTE);
                TY_(RemoveAttribute)( doc, node, first );
                firstRedefined = yes;
                first = temp;
                second = second->next;
            }
            else /* TidyDuplicateAttrs == TidyKeepFirst */
            {
                temp = second->next;
                TY_(ReportAttrError)( doc, node, second, REPEATED_ATTRIBUTE);
                TY_(RemoveAttribute)( doc, node, second );
                second = temp;
            }
        }
        if (!firstRedefined)
            first = first->next;
    }
}

/* ignore unknown attributes for proprietary elements */
const Attribute* TY_(CheckAttribute)( TidyDoc doc, TidyNode node, TidyAttr attval )
{
    const Attribute* attribute = attval->dict;

    if ( attribute != NULL )
    {
        if (attrIsXML_LANG(attval) || attrIsXML_SPACE(attval))
        {
            doc->lexer->isvoyager = yes;
            if (!cfgBool(doc, TidyHtmlOut))
            {
                TY_(SetOptionBool)(doc, TidyXhtmlOut, yes);
                TY_(SetOptionBool)(doc, TidyXmlOut, yes);
            }
        }

        TY_(ConstrainVersion)(doc, AttributeVersions(node, attval));
        
        if (attribute->attrchk)
            attribute->attrchk( doc, node, attval );
    }

    return attribute;
}

Bool TY_(IsBoolAttribute)(TidyAttr attval)
{
    const Attribute *attribute = ( attval ? attval->dict : NULL );
    if ( attribute && attribute->attrchk == CH_BOOL )
        return yes;
    return no;
}

Bool TY_(attrIsEvent)( TidyAttr attval )
{
    TidyAttrId atid = AttrId( attval );

    return (atid == TidyAttr_OnAFTERUPDATE     ||
            atid == TidyAttr_OnBEFOREUNLOAD    ||
            atid == TidyAttr_OnBEFOREUPDATE    ||
            atid == TidyAttr_OnBLUR            ||
            atid == TidyAttr_OnCHANGE          ||
            atid == TidyAttr_OnCLICK           ||
            atid == TidyAttr_OnDATAAVAILABLE   ||
            atid == TidyAttr_OnDATASETCHANGED  ||
            atid == TidyAttr_OnDATASETCOMPLETE ||
            atid == TidyAttr_OnDBLCLICK        ||
            atid == TidyAttr_OnERRORUPDATE     ||
            atid == TidyAttr_OnFOCUS           ||
            atid == TidyAttr_OnKEYDOWN         ||
            atid == TidyAttr_OnKEYPRESS        ||
            atid == TidyAttr_OnKEYUP           ||
            atid == TidyAttr_OnLOAD            ||
            atid == TidyAttr_OnMOUSEDOWN       ||
            atid == TidyAttr_OnMOUSEMOVE       ||
            atid == TidyAttr_OnMOUSEOUT        ||
            atid == TidyAttr_OnMOUSEOVER       ||
            atid == TidyAttr_OnMOUSEUP         ||
            atid == TidyAttr_OnRESET           ||
            atid == TidyAttr_OnROWENTER        ||
            atid == TidyAttr_OnROWEXIT         ||
            atid == TidyAttr_OnSELECT          ||
            atid == TidyAttr_OnSUBMIT          ||
            atid == TidyAttr_OnUNLOAD);
}

static void CheckLowerCaseAttrValue( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    tmbstr p;
    Bool hasUpper = no;
    
    if (!AttrHasValue(attval))
        return;

    p = attval->value;
    
    while (*p)
    {
        if (TY_(IsUpper)(*p)) /* #501230 - fix by Terry Teague - 09 Jan 02 */
        {
            hasUpper = yes;
            break;
        }
        p++;
    }

    if (hasUpper)
    {
        Lexer* lexer = doc->lexer;
        if (lexer->isvoyager)
            TY_(ReportAttrError)( doc, node, attval, ATTR_VALUE_NOT_LCASE);
  
        if ( lexer->isvoyager || cfgBool(doc, TidyLowerLiterals) )
            attval->value = TY_(tmbstrtolower)(attval->value);
    }
}

/* methods for checking value of a specific attribute */

void TY_(CheckUrl)( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    tmbchar c; 
    tmbstr dest, p;
    uint escape_count = 0, backslash_count = 0;
    uint i, pos = 0;
    uint len;
    Bool isJavascript = no;
    
    if (!AttrHasValue(attval))
    {
        TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
        return;
    }

    p = attval->value;
    
    isJavascript =
        TY_(tmbstrncmp)(p,"javascript:",sizeof("javascript:")-1)==0;

    for (i = 0; '\0' != (c = p[i]); ++i)
    {
        if (c == '\\')
        {
            ++backslash_count;
            if ( cfgBool(doc, TidyFixBackslash) && !isJavascript)
                p[i] = '/';
        }
        else if ((c > 0x7e) || (c <= 0x20) || (strchr("<>", c)))
            ++escape_count;
    }

    if ( cfgBool(doc, TidyFixUri) && escape_count )
    {
        Bool hadnonspace = no;
        len = TY_(tmbstrlen)(p) + escape_count * 2 + 1;
        dest = (tmbstr) TidyDocAlloc(doc, len);
 
        for (i = 0; 0 != (c = p[i]); ++i)
        {
            if ((c > 0x7e) || (c <= 0x20) || (strchr("<>", c)))
            {
                if (c == 0x20)
                {
                    /* #345 - special case for leading spaces - discard */
                    if (hadnonspace)
                        pos += sprintf( dest + pos, "%%%02X", (byte)c );
                }
                else
                {
                    pos += sprintf( dest + pos, "%%%02X", (byte)c );
                    hadnonspace = yes;
                }
            }
            else
            {
                hadnonspace = yes;
                dest[pos++] = c;
            }
        }
        dest[pos] = 0;

        TidyDocFree(doc, attval->value);
        attval->value = dest;
    }
    if ( backslash_count )
    {
        if ( cfgBool(doc, TidyFixBackslash) && !isJavascript )
            TY_(ReportAttrError)( doc, node, attval, FIXED_BACKSLASH );
        else
            TY_(ReportAttrError)( doc, node, attval, BACKSLASH_IN_URI );
    }
    if ( escape_count )
    {
        if ( cfgBool(doc, TidyFixUri) )
            TY_(ReportAttrError)( doc, node, attval, ESCAPED_ILLEGAL_URI);
        else
            TY_(ReportAttrError)( doc, node, attval, ILLEGAL_URI_REFERENCE);

        doc->badChars |= BC_INVALID_URI;
    }
}

/* RFC 2396, section 4.2 states:
     "[...] in the case of HTML's FORM element, [...] an
     empty URI reference represents the base URI of the
     current document and should be replaced by that URI
     when transformed into a request."
*/
void CheckAction( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    if (AttrHasValue(attval))
        TY_(CheckUrl)( doc, node, attval );
}

void CheckScript( TidyDoc ARG_UNUSED(doc), TidyNode ARG_UNUSED(node),
                  TidyAttr ARG_UNUSED(attval))
{
}

Bool TY_(IsValidHTMLID)(ctmbstr id)
{
    ctmbstr s = id;

    if (!s)
        return no;

    while (*s)
        if (TY_(IsHTMLSpace)(*s++))
            return no;

    return yes;

}

Bool TY_(IsValidXMLID)(ctmbstr id)
{
    ctmbstr s = id;
    tchar c;

    if (!s)
        return no;

    c = *s++;
    if (c > 0x7F)
        s += TY_(GetUTF8)(s, &c);

    if (!(TY_(IsXMLLetter)(c) || c == '_' || c == ':'))
        return no;

    while (*s)
    {
        c = (unsigned char)*s;

        if (c > 0x7F)
            s += TY_(GetUTF8)(s, &c);

        ++s;

        if (!TY_(IsXMLNamechar)(c))
            return no;
    }

    return yes;
}

static Bool IsValidNMTOKEN(ctmbstr name)
{
    ctmbstr s = name;
    tchar c;

    if (!s)
        return no;

    while (*s)
    {
        c = (unsigned char)*s;

        if (c > 0x7F)
            s += TY_(GetUTF8)(s, &c);

        ++s;

        if (!TY_(IsXMLNamechar)(c))
            return no;
    }

    return yes;
}

static Bool AttrValueIsAmong(TidyAttr attval, ctmbstr const list[])
{
    const ctmbstr *v;   
    for (v = list; *v; ++v)
        if (AttrValueIs(attval, *v))
            return yes;
    return no;
}

static void CheckAttrValidity( TidyDoc doc, TidyNode node, TidyAttr attval,
                               ctmbstr const list[])
{
    if (!AttrHasValue(attval))
    {
        TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
        return;
    }

    CheckLowerCaseAttrValue( doc, node, attval );

    if (!AttrValueIsAmong(attval, list))
        TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
}

void CheckName( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    TidyNode old;

    if (!AttrHasValue(attval))
    {
        TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
        return;
    }

    if ( TY_(IsAnchorElement)(doc, node) )
    {
        if (cfgBool(doc, TidyXmlOut) && !IsValidNMTOKEN(attval->value))
            TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);

        if ((old = GetNodeByAnchor(doc, attval->value)) &&  old != node)
        {
            TY_(ReportAttrError)( doc, node, attval, ANCHOR_NOT_UNIQUE);
        }
        else
            AddAnchor( doc, attval->value, node );
    }
}

void CheckId( TidyDoc doc, TidyNode node, TidyAttr attval )
{
    Lexer* lexer = doc->lexer;
    TidyNode old;

    if (!AttrHasValue(attval))
    {
        TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
        return;
    }

    if (!TY_(IsValidHTMLID)(attval->value))
    {
        if (lexer->isvoyager && TY_(IsValidXMLID)(attval->value))
            TY_(ReportAttrError)( doc, node, attval, XML_ID_SYNTAX);
        else
            TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
    }

    if ((old = GetNodeByAnchor(doc, attval->value)) &&  old != node)
    {
        TY_(ReportAttrError)( doc, node, attval, ANCHOR_NOT_UNIQUE);
    }
    else
        AddAnchor( doc, attval->value, node );
}

void CheckBool( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    if (!AttrHasValue(attval))
        return;

    CheckLowerCaseAttrValue( doc, node, attval );
}

void CheckAlign( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    ctmbstr const values[] = {"left", "right", "center", "justify", NULL};

    /* IMG, OBJECT, APPLET and EMBED use align for vertical position */
    if (node->tag && (node->tag->model & CM_IMG))
    {
        CheckValign( doc, node, attval );
        return;
    }

    if (!AttrHasValue(attval))
    {
        TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
        return;
    }

    CheckLowerCaseAttrValue( doc, node, attval);

    /* currently CheckCaption(...) takes care of the remaining cases */
    if (nodeIsCAPTION(node))
        return;

    if (!AttrValueIsAmong(attval, values))
    {
        /* align="char" is allowed for elements with CM_TABLE|CM_ROW
           except CAPTION which is excluded above, */
        if( !(AttrValueIs(attval, "char")
              && TY_(nodeHasCM)(node, CM_TABLE|CM_ROW)) )
             TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
    }
}

void CheckValign( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    ctmbstr const values[] = {"top", "middle", "bottom", "baseline", NULL};
    ctmbstr const values2[] = {"left", "right", NULL};
    ctmbstr const valuesp[] = {"texttop", "absmiddle", "absbottom",
                               "textbottom", NULL};

    if (!AttrHasValue(attval))
    {
        TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
        return;
    }

    CheckLowerCaseAttrValue( doc, node, attval );

    if (AttrValueIsAmong(attval, values))
    {
            /* all is fine */
    }
    else if (AttrValueIsAmong(attval, values2))
    {
        if (!(node->tag && (node->tag->model & CM_IMG)))
            TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
    }
    else if (AttrValueIsAmong(attval, valuesp))
    {
        TY_(ConstrainVersion)( doc, VERS_PROPRIETARY );
        TY_(ReportAttrError)( doc, node, attval, PROPRIETARY_ATTR_VALUE);
    }
    else
        TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
}

void CheckLength( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    tmbstr p;
    
    if (!AttrHasValue(attval))
    {
        TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
        return;
    }

    /* don't check for <col width=...> and <colgroup width=...> */
    if (attrIsWIDTH(attval) && (nodeIsCOL(node) || nodeIsCOLGROUP(node)))
        return;

    p = attval->value;
    
    if (!TY_(IsDigit)(*p++))
    {
        TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
    }
    else
    {
        while (*p)
        {
            if (!TY_(IsDigit)(*p) && *p != '%')
            {
                TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
                break;
            }
            ++p;
        }
    }
}

void CheckTarget( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    ctmbstr const values[] = {"_blank", "_self", "_parent", "_top", NULL};

    if (!AttrHasValue(attval))
    {
        TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
        return;
    }

    /* target names must begin with A-Za-z ... */
    if (TY_(IsLetter)(attval->value[0]))
        return;

    /* or be one of the allowed list */
    if (!AttrValueIsAmong(attval, values))
        TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
}

void CheckFsubmit( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    ctmbstr const values[] = {"get", "post", NULL};
    CheckAttrValidity( doc, node, attval, values );
}

void CheckClear( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    ctmbstr const values[] = {"none", "left", "right", "all", NULL};

    if (!AttrHasValue(attval))
    {
        TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
        if (attval->value == NULL)
            attval->value = TY_(tmbstrdup)( doc->allocator, "none" );
        return;
    }

    CheckLowerCaseAttrValue( doc, node, attval );
        
    if (!AttrValueIsAmong(attval, values))
        TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
}

void CheckShape( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    ctmbstr const values[] = {"rect", "default", "circle", "poly", NULL};
    CheckAttrValidity( doc, node, attval, values );
}

void CheckScope( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    ctmbstr const values[] = {"row", "rowgroup", "col", "colgroup", NULL};
    CheckAttrValidity( doc, node, attval, values );
}

void CheckNumber( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    tmbstr p;
    
    if (!AttrHasValue(attval))
    {
        TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
        return;
    }

    /* don't check <frameset cols=... rows=...> */
    if ( nodeIsFRAMESET(node) &&
        (attrIsCOLS(attval) || attrIsROWS(attval)))
     return;

    p  = attval->value;
    
    /* font size may be preceded by + or - */
    if ( nodeIsFONT(node) && (*p == '+' || *p == '-') )
        ++p;
    /* tabindex may be preceeded by - */
    if (attval->attribute && (strcmp(attval->attribute,"tabindex") == 0) && (*p == '-'))
        ++p;

    while (*p)
    {
        if (!TY_(IsDigit)(*p))
        {
            TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
            break;
        }
        ++p;
    }
}

/* check hexadecimal color value */
static Bool IsValidColorCode(ctmbstr color)
{
    uint i;

    if (TY_(tmbstrlen)(color) != 6)
        return no;

    /* check if valid hex digits and letters */
    for (i = 0; i < 6; i++)
        if (!TY_(IsDigit)(color[i]) && !strchr("abcdef", TY_(ToLower)(color[i])))
            return no;

    return yes;
}

/* check color syntax and beautify value by option */
void CheckColor( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    Bool valid = no;
    tmbstr given;

    if (!AttrHasValue(attval))
    {
        TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
        return;
    }

    given = attval->value;

    /* 727851 - add hash to hash-less color values */
    if (given[0] != '#' && (valid = IsValidColorCode(given)))
    {
        tmbstr cp, s;

        cp = s = (tmbstr) TidyDocAlloc(doc, 2 + TY_(tmbstrlen)(given));
        *cp++ = '#';
        while ('\0' != (*cp++ = *given++))
            continue;

        TY_(ReportAttrError)(doc, node, attval, BAD_ATTRIBUTE_VALUE_REPLACED);

        TidyDocFree(doc, attval->value);
        given = attval->value = s;
    }

    if (!valid && given[0] == '#')
        valid = IsValidColorCode(given + 1);

    if (valid && given[0] == '#' && cfgBool(doc, TidyReplaceColor))
    {
        ctmbstr newName = GetColorName(given);

        if (newName)
        {
            TidyDocFree(doc, attval->value);
            given = attval->value = TY_(tmbstrdup)(doc->allocator, newName);
        }
    }

    /* if it is not a valid color code, it is a color name */
    if (!valid)
        valid = GetColorCode(given) != NULL;

    if (valid && given[0] == '#')
        attval->value = TY_(tmbstrtoupper)(attval->value);
    else if (valid)
        attval->value = TY_(tmbstrtolower)(attval->value);

    if (!valid)
        TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
}

/* check valuetype attribute for element param */
void CheckVType( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    ctmbstr const values[] = {"data", "object", "ref", NULL};
    CheckAttrValidity( doc, node, attval, values );
}

/* checks scrolling attribute */
void CheckScroll( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    ctmbstr const values[] = {"no", "auto", "yes", NULL};
    CheckAttrValidity( doc, node, attval, values );
}

/* checks dir attribute */
void CheckTextDir( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    ctmbstr const values[] = {"rtl", "ltr", NULL};
    CheckAttrValidity( doc, node, attval, values );
}

/* checks lang and xml:lang attributes */
void CheckLang( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    /* empty xml:lang is allowed through XML 1.0 SE errata */
    if (!AttrHasValue(attval) && !attrIsXML_LANG(attval))
    {
        if ( cfg(doc, TidyAccessibilityCheckLevel) == 0 )
        {
            TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE );
        }
        return;
    }
}

/* checks type attribute */
void CheckType( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    ctmbstr const valuesINPUT[] = {
        "text", "password", "checkbox", "radio", "submit", "reset", "file",
        "hidden", "image", "button", "color", "date", "datetime",
        "datetime-local", "email", "month", "number", "range", "search",
        "tel", "time", "url", "week", NULL};
    ctmbstr const valuesBUTTON[] = {"button", "submit", "reset", NULL};
    ctmbstr const valuesUL[] = {"disc", "square", "circle", NULL};
    ctmbstr const valuesOL[] = {"1", "a", "i", NULL};

    if (nodeIsINPUT(node))
        CheckAttrValidity( doc, node, attval, valuesINPUT );
    else if (nodeIsBUTTON(node))
        CheckAttrValidity( doc, node, attval, valuesBUTTON );
    else if (nodeIsUL(node))
        CheckAttrValidity( doc, node, attval, valuesUL );
    else if (nodeIsOL(node))
    {
        if (!AttrHasValue(attval))
        {
            TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
            return;
        }
        if (!AttrValueIsAmong(attval, valuesOL))
            TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
    }
    else if (nodeIsLI(node))
    {
        if (!AttrHasValue(attval))
        {
            TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
            return;
        }
        if (AttrValueIsAmong(attval, valuesUL))
            CheckLowerCaseAttrValue( doc, node, attval );
        else if (!AttrValueIsAmong(attval, valuesOL))
            TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
    }
    return;
}

static
TidyAttr SortAttVal( TidyAttr list, TidyAttrSortStrategy strat );

void TY_(SortAttributes)(TidyNode node, TidyAttrSortStrategy strat)
{
    while (node)
    {
        node->attributes = SortAttVal( node->attributes, strat );
        if (node->content)
            TY_(SortAttributes)(node->content, strat);
        node = node->next;
    }
}

/**
* Attribute sorting contributed by Adrian Wilkins, 2007
* 
* Portions copyright Simon Tatham 2001.
*
* Merge sort algortithm adpated from listsort.c linked from 
* http://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.html
* 
* Original copyright notice proceeds below.
* 
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following
* conditions:
* 
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT.  IN NO EVENT SHALL SIMON TATHAM BE LIABLE FOR
* ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
* CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

typedef int(*ptAttValComparator)(TidyAttr one, TidyAttr two);

/* Comparison function for TidySortAttrAlpha */
static
int AlphaComparator(TidyAttr one, TidyAttr two)
{
    return TY_(tmbstrcmp)(one->attribute, two->attribute);
}


/* The "factory method" that returns a pointer to the comparator function */
static
ptAttValComparator GetAttValComparator(TidyAttrSortStrategy strat)
{
    switch (strat)
    {
    case TidySortAttrAlpha:
        return AlphaComparator;
    case TidySortAttrNone:
        break;
    }
    return 0;
}

/* The sort routine */
static
TidyAttr SortAttVal( TidyAttr list, TidyAttrSortStrategy strat)
{
    ptAttValComparator ptComparator = GetAttValComparator(strat);
    TidyAttr p, q, e, tail;
    int insize, nmerges, psize, qsize, i;

    /*
    * Silly special case: if `list' was passed in as NULL, return
    * NULL immediately.
    */
    if (!list)
        return NULL;

    insize = 1;

    while (1) {
        p = list;
        list = NULL;
        tail = NULL;

        nmerges = 0;  /* count number of merges we do in this pass */

        while (p) {
            nmerges++;  /* there exists a merge to be done */
            /* step `insize' places along from p */
            q = p;
            psize = 0;
            for (i = 0; i < insize; i++) {
                psize++;
                q = q->next;
                if(!q) break;
            }

            /* if q hasn't fallen off end, we have two lists to merge */
            qsize = insize;

            /* now we have two lists; merge them */
            while (psize > 0 || (qsize > 0 && q)) {

                /* decide whether next element of merge comes from p or q */
                if (psize == 0) {
                    /* p is empty; e must come from q. */
                    e = q; q = q->next; qsize--;
                } else if (qsize == 0 || !q) {
                    /* q is empty; e must come from p. */
                    e = p; p = p->next; psize--;
                } else if (ptComparator(p,q) <= 0) {
                    /* First element of p is lower (or same);
                    * e must come from p. */
                    e = p; p = p->next; psize--;
                } else {
                    /* First element of q is lower; e must come from q. */
                    e = q; q = q->next; qsize--;
                }

                /* add the next element to the merged list */
                if (tail) {
                    tail->next = e;
                } else {
                    list = e;
                }

                tail = e;
            }

            /* now p has stepped `insize' places along, and q has too */
            p = q;
        }

        tail->next = NULL;

        /* If we have done only one merge, we're finished. */
        if (nmerges <= 1)   /* allow for nmerges==0, the empty list case */
            return list;

        /* Otherwise repeat, merging lists twice the size */
        insize *= 2;
    }
}

/* RDFA support checkers
 *
 */

/* CheckRDFAPrefix - ensure the prefix attribute value is
 * correct
 *
 * @prefix takes prefix value pairs in the form:
 * 
 *      NCName ':' ' '+ AnyURI
 */

void CheckRDFaPrefix ( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    if (!AttrHasValue(attval))
    {
        TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
        return;
    }

    /* Copy the attribute value so we can split it */
    if (attval->value) {
        tmbstr t, tPtr ;

        uint prefixCount = 0;
        /* isPrefix toggles - start at 1 and change to 0 as we
         * iterate over the components of the value */
        uint isPrefix = 1;

        /* Copy it over */

        uint len = TY_(tmbstrlen)(attval->value);
        tmbstr s = (tmbstr) TidyDocAlloc( doc, len + 1 );
        s[0] = '\0';
        TY_(tmbstrcpy)( s, attval->value );

        /* iterate over value */
        tPtr = s;

        while ( ( t = strtok(tPtr, " ") ) != NULL ) {
            tPtr = NULL;
            if (isPrefix) {
                /* this piece should be a prefix */
                /* prefix rules are that it can have any
                 * character except a colon - that one must be
                 * at the end */
                tmbstr i = strchr(t, ':') ;
                if (i == NULL) {
                    /* no colon - bad! */
                    TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
                } else if (i != ( t + TY_(tmbstrlen)(t) - 1) ) {
                    /* not at the end - also bad */
                    TY_(ReportAttrError)( doc, node, attval, BAD_ATTRIBUTE_VALUE);
                }
            } else {
                /* this piece should be a URL */
                prefixCount ++;
            }
            isPrefix = !isPrefix;
        }
        TidyDocFree( doc, s ) ;
    }
}

/* CheckRDFaTerm - are terms valid
 *
 */

void CheckRDFaTerm ( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    if (!AttrHasValue(attval))
    {
        TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
        return;
    }

}

/* CheckRDFaSafeCURIE - is a CURIE legal
 *
 */

void CheckRDFaSafeCURIE ( TidyDoc doc, TidyNode node, TidyAttr attval)
{
    if (!AttrHasValue(attval))
    {
        TY_(ReportAttrError)( doc, node, attval, MISSING_ATTR_VALUE);
        return;
    }

}

/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
