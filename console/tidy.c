/*
 tidy.c - HTML TidyLib command line driver

 Copyright (c) 1998-2008 World Wide Web Consortium
 (Massachusetts Institute of Technology, European Research
 Consortium for Informatics and Mathematics, Keio University).
 All Rights Reserved.

 */

#include "tidy.h"
#include "language.h"
#include "locale.h"
#if defined(_WIN32)
#include <windows.h> /* Force console to UTF8. */
#endif
#if !defined(NDEBUG) && defined(_MSC_VER)
#include "sprtf.h"
#endif

#ifndef SPRTF
#define SPRTF printf
#endif

static FILE* errout = NULL;  /* set to stderr */
/* static FILE* txtout = NULL; */  /* set to stdout */

#if defined(_WIN32)
static uint win_cp; /* original Windows code page */
#endif

/**
 **  Indicates whether or not two filenames are the same.
 */
static Bool samefile( ctmbstr filename1, ctmbstr filename2 )
{
#if FILENAMES_CASE_SENSITIVE
    return ( strcmp( filename1, filename2 ) == 0 );
#else
    return ( strcasecmp( filename1, filename2 ) == 0 );
#endif
}


/**
 **  Handles exit cleanup.
 */
static void tidy_cleanup()
{
#if defined(_WIN32)
    /* Restore original Windows code page. */
    SetConsoleOutputCP(win_cp);
#endif
}

/**
 **  Exits with an error in the event of an out of memory condition.
 */
static void outOfMemory(void)
{
    fprintf(stderr, "%s", tidyLocalizedString(TC_STRING_OUT_OF_MEMORY));
    exit(1);
}


/**
 **  Used by `print2Columns` and `print3Columns` to manage whitespace.
 */
static const char *cutToWhiteSpace(const char *s, uint offset, char *sbuf)
{
    if (!s)
    {
        sbuf[0] = '\0';
        return NULL;
    }
    else if (strlen(s) <= offset)
    {
        strcpy(sbuf,s);
        sbuf[offset] = '\0';
        return NULL;
    }
    else
    {
        uint j, l, n;
        /* scan forward looking for newline */
        j = 0;
        while(j < offset && s[j] != '\n')
            ++j;
        if ( j == offset ) {
            /* scan backward looking for first space */
            j = offset;
            while(j && s[j] != ' ')
                --j;
            l = j;
            n = j+1;
            /* no white space */
            if (j==0)
            {
                l = offset;
                n = offset;
            }
        } else
        {
            l = j;
            n = j+1;
        }
        strncpy(sbuf,s,l);
        sbuf[l] = '\0';
        return s+n;
    }
}

/**
 **  Outputs one column of text.
 */
static void print1Column( const char* fmt, uint l1, const char *c1 )
{
    const char *pc1=c1;
    char *c1buf = (char *)malloc(l1+1);
    if (!c1buf) outOfMemory();

    do
    {
        pc1 = cutToWhiteSpace(pc1, l1, c1buf);
        printf(fmt, c1buf[0] !='\0' ? c1buf : "");
    } while (pc1);
    free(c1buf);
}

/**
 **  Outputs two columns of text.
 */
static void print2Columns( const char* fmt, uint l1, uint l2,
                          const char *c1, const char *c2 )
{
    const char *pc1=c1, *pc2=c2;
    char *c1buf = (char *)malloc(l1+1);
    char *c2buf = (char *)malloc(l2+1);
    if (!c1buf) outOfMemory();
    if (!c2buf) outOfMemory();

    do
    {
        pc1 = cutToWhiteSpace(pc1, l1, c1buf);
        pc2 = cutToWhiteSpace(pc2, l2, c2buf);
        printf(fmt,
               c1buf[0]!='\0'?c1buf:"",
               c2buf[0]!='\0'?c2buf:"");
    } while (pc1 || pc2);
    free(c1buf);
    free(c2buf);
}

/**
 **  Outputs three columns of text.
 */
static void print3Columns( const char* fmt, uint l1, uint l2, uint l3,
                          const char *c1, const char *c2, const char *c3 )
{
    const char *pc1=c1, *pc2=c2, *pc3=c3;
    char *c1buf = (char *)malloc(l1+1);
    char *c2buf = (char *)malloc(l2+1);
    char *c3buf = (char *)malloc(l3+1);
    if (!c1buf) outOfMemory();
    if (!c2buf) outOfMemory();
    if (!c3buf) outOfMemory();

    do
    {
        pc1 = cutToWhiteSpace(pc1, l1, c1buf);
        pc2 = cutToWhiteSpace(pc2, l2, c2buf);
        pc3 = cutToWhiteSpace(pc3, l3, c3buf);
        printf(fmt,
               c1buf[0]!='\0'?c1buf:"",
               c2buf[0]!='\0'?c2buf:"",
               c3buf[0]!='\0'?c3buf:"");
    } while (pc1 || pc2 || pc3);
    free(c1buf);
    free(c2buf);
    free(c3buf);
}

/**
 **  Format strings and decorations used in output.
 */
static const char helpfmt[] = " %-25.25s %-52.52s\n";
static const char helpul[]  = "-----------------------------------------------------------------";
static const char fmt[]     = "%-27.27s %-9.9s  %-40.40s\n";
static const char valfmt[]  = "%-27.27s %-9.9s %-1.1s%-39.39s\n";
static const char ul[]      = "=================================================================";

/**
 **  This enum is used to categorize the options for help output.
 */
typedef enum
{
    CmdOptFileManip,
    CmdOptCatFIRST = CmdOptFileManip,
    CmdOptProcDir,
    CmdOptCharEnc,
    CmdOptMisc,
    CmdOptXML,
    CmdOptCatLAST
} CmdOptCategory;

/**
 **  This array contains headings that will be used in help ouput.
 */
static const struct {
    ctmbstr mnemonic;  /**< Used in XML as a class. */
    uint key;          /**< Key to fetch the localized string. */
} cmdopt_catname[] = {
    { "file-manip", TC_STRING_FILE_MANIP },
    { "process-directives", TC_STRING_PROCESS_DIRECTIVES },
    { "char-encoding", TC_STRING_CHAR_ENCODING },
    { "misc", TC_STRING_MISC },
    { "xml", TC_STRING_XML }
};

/**
 **  The struct and subsequent array keep the help output structured
 **  because we _also_ output all of this stuff as as XML.
 */
typedef struct {
    CmdOptCategory cat; /**< Category */
    ctmbstr name1;      /**< Name */
    uint key;           /**< Key to fetch the localized description. */
    uint subKey;        /**< Secondary substitution key. */
    ctmbstr eqconfig;   /**< Equivalent configuration option */
    ctmbstr name2;      /**< Name */
    ctmbstr name3;      /**< Name */
} CmdOptDesc;

/* All instances of %s will be substituted with localized string
 specified by the subKey field. */
static const CmdOptDesc cmdopt_defs[] =  {
    { CmdOptFileManip, "-output <%s>",         TC_OPT_OUTPUT,   TC_LABEL_FILE, "output-file: <%s>", "-o <%s>" },
    { CmdOptFileManip, "-config <%s>",         TC_OPT_CONFIG,   TC_LABEL_FILE, NULL },
    { CmdOptFileManip, "-file <%s>",           TC_OPT_FILE,     TC_LABEL_FILE, "error-file: <%s>", "-f <%s>" },
    { CmdOptFileManip, "-modify",              TC_OPT_MODIFY,   0,             "write-back: yes", "-m" },
    { CmdOptProcDir,   "-indent",              TC_OPT_INDENT,   0,             "indent: auto", "-i" },
    { CmdOptProcDir,   "-wrap <%s>",           TC_OPT_WRAP,     TC_LABEL_COL,  "wrap: <%s>", "-w <%s>" },
    { CmdOptProcDir,   "-upper",               TC_OPT_UPPER,    0,             "uppercase-tags: yes", "-u" },
    { CmdOptProcDir,   "-clean",               TC_OPT_CLEAN,    0,             "clean: yes", "-c" },
    { CmdOptProcDir,   "-bare",                TC_OPT_BARE,     0,             "bare: yes", "-b" },
    { CmdOptProcDir,   "-gdoc",                TC_OPT_GDOC,     0,             "gdoc: yes", "-g" },
    { CmdOptProcDir,   "-numeric",             TC_OPT_NUMERIC,  0,             "numeric-entities: yes", "-n" },
    { CmdOptProcDir,   "-errors",              TC_OPT_ERRORS,   0,             "markup: no", "-e" },
    { CmdOptProcDir,   "-quiet",               TC_OPT_QUIET,    0,             "quiet: yes", "-q" },
    { CmdOptProcDir,   "-omit",                TC_OPT_OMIT,     0,             "omit-optional-tags: yes" },
    { CmdOptProcDir,   "-xml",                 TC_OPT_XML,      0,             "input-xml: yes" },
    { CmdOptProcDir,   "-asxml",               TC_OPT_ASXML,    0,             "output-xhtml: yes", "-asxhtml" },
    { CmdOptProcDir,   "-ashtml",              TC_OPT_ASHTML,   0,             "output-html: yes" },
#if SUPPORT_ACCESSIBILITY_CHECKS
    { CmdOptProcDir,   "-access <%s>",         TC_OPT_ACCESS,   TC_LABEL_LEVL, "accessibility-check: <%s>" },
#endif
    { CmdOptCharEnc,   "-raw",                 TC_OPT_RAW,      0,             NULL },
    { CmdOptCharEnc,   "-ascii",               TC_OPT_ASCII,    0,             NULL },
    { CmdOptCharEnc,   "-latin0",              TC_OPT_LATIN0,   0,             NULL },
    { CmdOptCharEnc,   "-latin1",              TC_OPT_LATIN1,   0,             NULL },
#ifndef NO_NATIVE_ISO2022_SUPPORT
    { CmdOptCharEnc,   "-iso2022",             TC_OPT_ISO2022,  0,             NULL },
#endif
    { CmdOptCharEnc,   "-utf8",                TC_OPT_UTF8,     0,             NULL },
    { CmdOptCharEnc,   "-mac",                 TC_OPT_MAC,      0,             NULL },
    { CmdOptCharEnc,   "-win1252",             TC_OPT_WIN1252,  0,             NULL },
    { CmdOptCharEnc,   "-ibm858",              TC_OPT_IBM858,   0,             NULL },
#if SUPPORT_UTF16_ENCODINGS
    { CmdOptCharEnc,   "-utf16le",             TC_OPT_UTF16LE,  0,             NULL },
    { CmdOptCharEnc,   "-utf16be",             TC_OPT_UTF16BE,  0,             NULL },
    { CmdOptCharEnc,   "-utf16",               TC_OPT_UTF16,    0,             NULL },
#endif
#if SUPPORT_ASIAN_ENCODINGS /* #431953 - RJ */
    { CmdOptCharEnc,   "-big5",                TC_OPT_BIG5,     0,             NULL },
    { CmdOptCharEnc,   "-shiftjis",            TC_OPT_SHIFTJIS, 0,             NULL },
#endif
    { CmdOptMisc,      "-version",             TC_OPT_VERSION,  0,             NULL,  "-v" },
    { CmdOptMisc,      "-help",                TC_OPT_HELP,     0,             NULL,  "-h", "-?" },
    { CmdOptMisc,      "-help-config",         TC_OPT_HELPCFG,  0,             NULL },
    { CmdOptMisc,      "-show-config",         TC_OPT_SHOWCFG,  0,             NULL },
    { CmdOptMisc,      "-help-option <%s>",    TC_OPT_HELPOPT,  TC_LABEL_OPT,  NULL },
    { CmdOptMisc,      "-language <%s>",       TC_OPT_LANGUAGE, TC_LABEL_LANG, "language: <%s>" },
    { CmdOptXML,       "-xml-help",            TC_OPT_XMLHELP,  0,             NULL },
    { CmdOptXML,       "-xml-config",          TC_OPT_XMLCFG,   0,             NULL },
    { CmdOptXML,       "-xml-strings",         TC_OPT_XMLSTRG,  0,             NULL },
    { CmdOptXML,       "-xml-options-strings", TC_OPT_XMLOPTS,  0,             NULL },
    { CmdOptMisc,      NULL,                   0,               0,             NULL }
};

/**
 **  Create a new string with a format and arguments.
 */
static tmbstr stringWithFormat( const ctmbstr fmt, ... )
{
    va_list argList;
    tmbstr result = NULL;
    int len = 0;

    va_start(argList, fmt);
    len = vsnprintf( result, 0, fmt, argList );
    va_end(argList);

    if (!(result = malloc( len + 1) ))
        outOfMemory();

    va_start(argList, fmt);
    vsnprintf( result, len + 1, fmt, argList);
    va_end(argList);

    return result;
}


/**
 **  Option names aren't localized, but the  sample fields
 **  are, for example <file> should be <archivo> in Spanish.
 */
static void localize_option_names( CmdOptDesc *pos)
{
    ctmbstr fileString = tidyLocalizedString(pos->subKey);
    pos->name1 = stringWithFormat(pos->name1, fileString);
    if ( pos->name2 )
        pos->name2 = stringWithFormat(pos->name2, fileString);
    if ( pos->name3 )
        pos->name3 = stringWithFormat(pos->name3, fileString);
}

/**
 **  Retrieve the options' names from the structure as a single
 **  string.
 */
static tmbstr get_option_names( const CmdOptDesc* pos )
{
    tmbstr name;
    uint len;
    CmdOptDesc localPos = *pos;

    localize_option_names( &localPos );

    len = strlen(localPos.name1);
    if (localPos.name2)
        len += 2+strlen(localPos.name2);
    if (localPos.name3)
        len += 2+strlen(localPos.name3);

    name = (tmbstr)malloc(len+1);
    if (!name) outOfMemory();
    strcpy(name, localPos.name1);
    free((tmbstr)localPos.name1);
    if (localPos.name2)
    {
        strcat(name, ", ");
        strcat(name, localPos.name2);
        free((tmbstr)localPos.name2);
    }
    if (localPos.name3)
    {
        strcat(name, ", ");
        strcat(name, localPos.name3);
        free((tmbstr)localPos.name3);
    }
    return name;
}

/**
 **  Escape a name for XML output.
 */
static tmbstr get_escaped_name( ctmbstr name )
{
    tmbstr escpName;
    char aux[2];
    uint len = 0;
    ctmbstr c;
    for(c=name; *c!='\0'; ++c)
        switch(*c)
    {
        case '<':
        case '>':
            len += 4;
            break;
        case '"':
            len += 6;
            break;
        default:
            len += 1;
            break;
    }

    escpName = (tmbstr)malloc(len+1);
    if (!escpName) outOfMemory();
    escpName[0] = '\0';

    aux[1] = '\0';
    for(c=name; *c!='\0'; ++c)
        switch(*c)
    {
        case '<':
            strcat(escpName, "&lt;");
            break;
        case '>':
            strcat(escpName, "&gt;");
            break;
        case '"':
            strcat(escpName, "&quot;");
            break;
        default:
            aux[0] = *c;
            strcat(escpName, aux);
            break;
    }

    return escpName;
}

/**
 **  Outputs a complete help option (text)
 */
static void print_help_option( void )
{
    CmdOptCategory cat = CmdOptCatFIRST;
    const CmdOptDesc* pos = cmdopt_defs;

    for( cat=CmdOptCatFIRST; cat!=CmdOptCatLAST; ++cat)
    {
        ctmbstr name = tidyLocalizedString(cmdopt_catname[cat].key);
        size_t len =  strlen(name);
        printf("%s\n", name );
        printf("%*.*s\n", (int)len, (int)len, helpul );
        for( pos=cmdopt_defs; pos->name1; ++pos)
        {
            tmbstr name;
            if (pos->cat != cat)
                continue;
            name = get_option_names( pos );
            print2Columns( helpfmt, 25, 52, name, tidyLocalizedString( pos->key ) );
            free(name);
        }
        printf("\n");
    }
}

/**
 **  Outputs an XML element for an option.
 */
static void print_xml_help_option_element( ctmbstr element, ctmbstr name )
{
    tmbstr escpName;
    if (!name)
        return;
    printf("  <%s>%s</%s>\n", element, escpName = get_escaped_name(name),
           element);
    free(escpName);
}

/**
 **  Outputs a complete help option (XML)
 */
static void print_xml_help_option( void )
{
    const CmdOptDesc* pos = cmdopt_defs;

    for( pos=cmdopt_defs; pos->name1; ++pos)
    {
        printf(" <option class=\"%s\">\n", cmdopt_catname[pos->cat].mnemonic );
        print_xml_help_option_element("name", pos->name1);
        print_xml_help_option_element("name", pos->name2);
        print_xml_help_option_element("name", pos->name3);
        print_xml_help_option_element("description", tidyLocalizedString( pos->key ) );
        if (pos->eqconfig)
            print_xml_help_option_element("eqconfig", pos->eqconfig);
        else
            printf("  <eqconfig />\n");
        printf(" </option>\n");
    }
}

/**
 **  Provides the -xml-help service.
 */
static void xml_help( void )
{
    printf( "<?xml version=\"1.0\"?>\n"
           "<cmdline version=\"%s\">\n", tidyLibraryVersion());
    print_xml_help_option();
    printf( "</cmdline>\n" );
}

/**
 **  Returns the final name of the tidy executable.
 */
static ctmbstr get_final_name( ctmbstr prog )
{
    ctmbstr name = prog;
    int c;
    size_t i, len = strlen(prog);
    for (i = 0; i < len; i++) {
        c = prog[i];
        if ((( c == '/' ) || ( c == '\\' )) && prog[i+1])
            name = &prog[i+1];
    }
    return name;
}

/**
 **  Handles the -help service.
 */
static void help( ctmbstr prog )
{
    tmbstr title_line = NULL;

    printf( tidyLocalizedString(TC_TXT_HELP_1), get_final_name(prog),tidyLibraryVersion() );

#ifdef PLATFORM_NAME
    title_line = stringWithFormat( tidyLocalizedString(TC_TXT_HELP_2A), PLATFORM_NAME);
#else
    title_line = stringWithFormat( tidyLocalizedString(TC_TXT_HELP_2B) );
#endif
    printf( "%s\n", title_line );
    printf("%*.*s\n", (int)strlen(title_line), (int)strlen(title_line), ul);
    free( title_line );
    printf( "\n");

    print_help_option();

    printf( "%s", tidyLocalizedString(TC_TXT_HELP_3) );
}

/**
 **  Utility to determine if an option is an AutoBool.
 */
static Bool isAutoBool( TidyOption topt )
{
    TidyIterator pos;
    ctmbstr def;

    if ( tidyOptGetType( topt ) != TidyInteger)
        return no;

    pos = tidyOptGetPickList( topt );
    while ( pos )
    {
        def = tidyOptGetNextPick( topt, &pos );
        if (0==strcmp(def,"yes"))
            return yes;
    }
    return no;
}

/**
 **  Returns the configuration category name for the
 **  specified configuration category id. This will be
 **  used as an XML class attribute value.
 */
static ctmbstr ConfigCategoryName( TidyConfigCategory id )
{
    switch( id )
    {
        case TidyMarkup:
            return tidyLocalizedString( TC_CAT_MARKUP );
        case TidyDiagnostics:
            return tidyLocalizedString( TC_CAT_DIAGNOSTICS );
        case TidyPrettyPrint:
            return tidyLocalizedString( TC_CAT_PRETTYPRINT );
        case TidyEncoding:
            return tidyLocalizedString( TC_CAT_ENCODING );
        case TidyMiscellaneous:
            return tidyLocalizedString( TC_CAT_MISC );
    }
    fprintf(stderr, tidyLocalizedString(TC_STRING_FATAL_ERROR), (int)id);
    fprintf(stderr, "\n");

    assert(0);
    abort();
    return "never_here"; /* only for the compiler warning */
}

/**
 ** Structure maintains a description of an option.
 */
typedef struct {
    ctmbstr name;  /**< Name */
    ctmbstr cat;   /**< Category */
    ctmbstr type;  /**< "String, ... */
    ctmbstr vals;  /**< Potential values. If NULL, use an external function */
    ctmbstr def;   /**< default */
    tmbchar tempdefs[80]; /**< storage for default such as integer */
    Bool haveVals; /**< if yes, vals is valid */
} OptionDesc;

typedef void (*OptionFunc)( TidyDoc, TidyOption, OptionDesc * );


/**
 ** Create OptionDesc "d" related to "opt"
 */
static
void GetOption( TidyDoc tdoc, TidyOption topt, OptionDesc *d )
{
    TidyOptionId optId = tidyOptGetId( topt );
    TidyOptionType optTyp = tidyOptGetType( topt );

    d->name = tidyOptGetName( topt );
    d->cat = ConfigCategoryName( tidyOptGetCategory( topt ) );
    d->vals = NULL;
    d->def = NULL;
    d->haveVals = yes;

    /* Handle special cases first.
     */
    switch ( optId )
    {
        case TidyDuplicateAttrs:
        case TidySortAttributes:
        case TidyNewline:
        case TidyAccessibilityCheckLevel:
            d->type = "enum";
            d->vals = NULL;
            d->def =
            optId==TidyNewline ?
            "<em>Platform dependent</em>"
            :tidyOptGetCurrPick( tdoc, optId );
            break;

        case TidyDoctype:
            d->type = "DocType";
            d->vals = NULL;
        {
            ctmbstr sdef = NULL;
            sdef = tidyOptGetCurrPick( tdoc, TidyDoctypeMode );
            if ( !sdef || *sdef == '*' )
                sdef = tidyOptGetValue( tdoc, TidyDoctype );
            d->def = sdef;
        }
            break;

        case TidyInlineTags:
        case TidyBlockTags:
        case TidyEmptyTags:
        case TidyPreTags:
            d->type = "Tag names";
            d->vals = "tagX, tagY, ...";
            d->def = NULL;
            break;

        case TidyCharEncoding:
        case TidyInCharEncoding:
        case TidyOutCharEncoding:
            d->type = "Encoding";
            d->def = tidyOptGetEncName( tdoc, optId );
            if (!d->def)
                d->def = "?";
            d->vals = NULL;
            break;

            /* General case will handle remaining */
        default:
            switch ( optTyp )
        {
            case TidyBoolean:
                d->type = "Boolean";
                d->vals = "y/n, yes/no, t/f, true/false, 1/0";
                d->def = tidyOptGetCurrPick( tdoc, optId );
                break;

            case TidyInteger:
                if (isAutoBool(topt))
                {
                    d->type = "AutoBool";
                    d->vals = "auto, y/n, yes/no, t/f, true/false, 1/0";
                    d->def = tidyOptGetCurrPick( tdoc, optId );
                }
                else
                {
                    uint idef;
                    d->type = "Integer";
                    if ( optId == TidyWrapLen )
                        d->vals = "0 (no wrapping), 1, 2, ...";
                    else
                        d->vals = "0, 1, 2, ...";

                    idef = tidyOptGetInt( tdoc, optId );
                    sprintf(d->tempdefs, "%u", idef);
                    d->def = d->tempdefs;
                }
                break;

            case TidyString:
                d->type = "String";
                d->vals = NULL;
                d->haveVals = no;
                d->def = tidyOptGetValue( tdoc, optId );
                break;
        }
    }
}

/**
 ** Array holding all options. Contains a trailing sentinel.
 */
typedef struct {
    TidyOption topt[N_TIDY_OPTIONS];
} AllOption_t;

/**
 **  A simple option comparator.
 **/
static int cmpOpt(const void* e1_, const void *e2_)
{
    const TidyOption* e1 = (const TidyOption*)e1_;
    const TidyOption* e2 = (const TidyOption*)e2_;
    return strcmp(tidyOptGetName(*e1), tidyOptGetName(*e2));
}

/**
 **  Returns options sorted.
 **/
static void getSortedOption( TidyDoc tdoc, AllOption_t *tOption )
{
    TidyIterator pos = tidyGetOptionList( tdoc );
    uint i = 0;

    while ( pos )
    {
        TidyOption topt = tidyGetNextOption( tdoc, &pos );
        tOption->topt[i] = topt;
        ++i;
    }
    tOption->topt[i] = NULL; /* sentinel */

    qsort(tOption->topt,
          /* Do not sort the sentinel: hence `-1' */
          sizeof(tOption->topt)/sizeof(tOption->topt[0])-1,
          sizeof(tOption->topt[0]),
          cmpOpt);
}

/**
 **  An iterator for the sorted options.
 **/
static void ForEachSortedOption( TidyDoc tdoc, OptionFunc OptionPrint )
{
    AllOption_t tOption;
    const TidyOption *topt;

    getSortedOption( tdoc, &tOption );
    for( topt = tOption.topt; *topt; ++topt)
    {
        OptionDesc d;

        GetOption( tdoc, *topt, &d );
        (*OptionPrint)( tdoc, *topt, &d );
    }
}

/**
 **  An iterator for the unsorted options.
 **/
static void ForEachOption( TidyDoc tdoc, OptionFunc OptionPrint )
{
    TidyIterator pos = tidyGetOptionList( tdoc );

    while ( pos )
    {
        TidyOption topt = tidyGetNextOption( tdoc, &pos );
        OptionDesc d;

        GetOption( tdoc, topt, &d );
        (*OptionPrint)( tdoc, topt, &d );
    }
}

/**
 **  Prints an option's allowed value as specified in its pick list.
 **/
static void PrintAllowedValuesFromPick( TidyOption topt )
{
    TidyIterator pos = tidyOptGetPickList( topt );
    Bool first = yes;
    ctmbstr def;
    while ( pos )
    {
        if (first)
            first = no;
        else
            printf(", ");
        def = tidyOptGetNextPick( topt, &pos );
        printf("%s", def);
    }
}

/**
 **  Prints an option's allowed values.
 **/
static void PrintAllowedValues( TidyOption topt, const OptionDesc *d )
{
    if (d->vals)
        printf( "%s", d->vals );
    else
        PrintAllowedValuesFromPick( topt );
}

/**
 **  Prints for XML an option's <description>.
 **/
static void printXMLDescription( TidyDoc tdoc, TidyOption topt )
{
    ctmbstr doc = tidyOptGetDoc( tdoc, topt );

    if (doc)
        printf("  <description>%s</description>\n", doc);
    else
    {
        printf("  <description />\n");
        fprintf(stderr, tidyLocalizedString(TC_STRING_OPT_NOT_DOCUMENTED),
                tidyOptGetName( topt ));
        fprintf(stderr, "\n");

    }
}

/**
 **  Prints for XML an option's <seealso>.
 **/
static void printXMLCrossRef( TidyDoc tdoc, TidyOption topt )
{
    TidyOption optLinked;
    TidyIterator pos = tidyOptGetDocLinksList(tdoc, topt);
    while( pos )
    {
        optLinked = tidyOptGetNextDocLinks(tdoc, &pos );
        printf("  <seealso>%s</seealso>\n",tidyOptGetName(optLinked));
    }
}


/**
 **  Prints for XML an option.
 **/
static void printXMLOption( TidyDoc tdoc, TidyOption topt, OptionDesc *d )
{
    if ( tidyOptIsReadOnly(topt) )
        return;

    printf( " <option class=\"%s\">\n", d->cat );
    printf  ("  <name>%s</name>\n",d->name);
    printf  ("  <type>%s</type>\n",d->type);
    if (d->def)
        printf("  <default>%s</default>\n",d->def);
    else
        printf("  <default />\n");
    if (d->haveVals)
    {
        printf("  <example>");
        PrintAllowedValues( topt, d );
        printf("</example>\n");
    }
    else
    {
        printf("  <example />\n");
    }
    printXMLDescription( tdoc, topt );
    printXMLCrossRef( tdoc, topt );
    printf( " </option>\n" );
}


/**
 **  Handles the -xml-config service.
 **/
static void XMLoptionhelp( TidyDoc tdoc )
{
    printf( "<?xml version=\"1.0\"?>\n"
           "<config version=\"%s\">\n", tidyLibraryVersion());
    ForEachOption( tdoc, printXMLOption );
    printf( "</config>\n" );
}

/**
 *  Prints the Windows language names that Tidy recognizes,
 *  using the specified format string.
 */
void tidyPrintWindowsLanguageNames( ctmbstr format )
{
    const tidyLocaleMapItem *item;
    TidyIterator i = getWindowsLanguageList();

    while (i) {
        item = getNextWindowsLanguage(&i);
        if ( format )
            printf( format, item->winName, item->POSIXName );
        else
            printf( "%-20s -> %s\n", item->winName, item->POSIXName );
    }
}


/**
 *  Prints the languages the are currently built into Tidy,
 *  using the specified format string.
 */
void tidyPrintTidyLanguageNames( ctmbstr format )
{
    ctmbstr item;
    TidyIterator i = getInstalledLanguageList();

    while (i) {
        item = getNextInstalledLanguage(&i);
        if ( format )
            printf( format, item );
        else
            printf( "%s\n", item );
    }
}


/**
 **  Retrieves allowed values from an option's pick list.
 */
static tmbstr GetAllowedValuesFromPick( TidyOption topt )
{
    TidyIterator pos;
    Bool first;
    ctmbstr def;
    uint len = 0;
    tmbstr val;

    pos = tidyOptGetPickList( topt );
    first = yes;
    while ( pos )
    {
        if (first)
            first = no;
        else
            len += 2;
        def = tidyOptGetNextPick( topt, &pos );
        len += strlen(def);
    }
    val = (tmbstr)malloc(len+1);
    if (!val) outOfMemory();
    val[0] = '\0';
    pos = tidyOptGetPickList( topt );
    first = yes;
    while ( pos )
    {
        if (first)
            first = no;
        else
            strcat(val, ", ");
        def = tidyOptGetNextPick( topt, &pos );
        strcat(val, def);
    }
    return val;
}

/**
 **  Retrieves allowed values for an option.
 */
static tmbstr GetAllowedValues( TidyOption topt, const OptionDesc *d )
{
    if (d->vals)
    {
        tmbstr val = (tmbstr)malloc(1+strlen(d->vals));
        if (!val) outOfMemory();
        strcpy(val, d->vals);
        return val;
    }
    else
        return GetAllowedValuesFromPick( topt );
}

/**
 **  Prints a single option.
 */
static void printOption( TidyDoc ARG_UNUSED(tdoc), TidyOption topt,
                        OptionDesc *d )
{
    if ( tidyOptIsReadOnly(topt) )
        return;

    if ( *d->name || *d->type )
    {
        ctmbstr pval = d->vals;
        tmbstr val = NULL;
        if (!d->haveVals)
        {
            pval = "-";
        }
        else if (pval == NULL)
        {
            val = GetAllowedValues( topt, d);
            pval = val;
        }
        print3Columns( fmt, 27, 9, 40, d->name, d->type, pval );
        if (val)
            free(val);
    }
}

/**
 **  Handles the -help-config service.
 */
static void optionhelp( TidyDoc tdoc )
{
    printf( "%s", tidyLocalizedString( TC_TXT_HELP_CONFIG ) );

    printf( fmt,
           tidyLocalizedString( TC_TXT_HELP_CONFIG_NAME ),
           tidyLocalizedString( TC_TXT_HELP_CONFIG_TYPE ),
           tidyLocalizedString( TC_TXT_HELP_CONFIG_ALLW ) );

    printf( fmt, ul, ul, ul );

    ForEachSortedOption( tdoc, printOption );
}


/**
 **  Cleans up the HTML-laden option descriptions for console
 **  output. It's just a simple HTML filtering/replacement function.
 **  Will return an allocated string.
 */
static tmbstr cleanup_description( ctmbstr description )
{
    /* Substitutions - this might be a good spot to introduce platform
     dependent definitions for colorized output on different terminals
     that support, for example, ANSI escape sequences. The assumption
     is made the Mac and Linux targets support ANSI colors, but even
     so debugger terminals may not. Note that the line-wrapping
     function also doesn't account for non-printing characters. */
    static struct {
        ctmbstr tag;
        ctmbstr replacement;
    } const replacements[] = {
        { "lt",       "<"          },
        { "gt",       ">"          },
        { "br/",      "\n\n"       },
#if defined(LINUX_OS) || defined(MAC_OS_X)
        { "code",     "\x1b[36m"   },
        { "/code",    "\x1b[0m"    },
        { "em",       "\x1b[4m"   },
        { "/em",      "\x1b[0m"    },
        { "strong",   "\x1b[31m"   },
        { "/strong",  "\x1b[0m"    },
#endif
        /* MUST be last */
        { NULL,       NULL         },
    };

    /* State Machine Setup */
    typedef enum {
        s_DONE,
        s_DATA,
        s_WRITING,
        s_TAG_OPEN,
        s_TAG_NAME,
        s_ERROR,
        s_LAST /* MUST be last */
    } states;

    typedef enum {
        c_NIL,
        c_EOF,
        c_BRACKET_CLOSE,
        c_BRACKET_OPEN,
        c_OTHER
    } charstates;

    typedef enum {
        a_NIL,
        a_BUILD_NAME,
        a_CONSUME,
        a_EMIT,
        a_EMIT_SUBS,
        a_WRITE,
        a_ERROR
    } actions;

    typedef struct {
        states state;
        charstates charstate;
        actions action;
        states next_state;
    } transitionType;

    const transitionType transitions[] = {
        { s_DATA,           c_EOF,           a_NIL,        s_DONE           },
        { s_DATA,           c_BRACKET_OPEN,  a_CONSUME,    s_TAG_OPEN       },
        /* special case allows ; */
        { s_DATA,           c_BRACKET_CLOSE, a_EMIT,       s_WRITING        },
        { s_DATA,           c_OTHER,         a_EMIT,       s_WRITING        },
        { s_WRITING,        c_OTHER,         a_WRITE,      s_DATA           },
        { s_WRITING,        c_BRACKET_CLOSE, a_WRITE,      s_DATA           },
        { s_TAG_OPEN,       c_EOF,           a_ERROR,      s_DONE           },
        { s_TAG_OPEN,       c_OTHER,         a_NIL,        s_TAG_NAME       },
        { s_TAG_NAME,       c_BRACKET_OPEN,  a_ERROR,      s_DONE           },
        { s_TAG_NAME,       c_EOF,           a_ERROR,      s_DONE           },
        { s_TAG_NAME,       c_BRACKET_CLOSE, a_EMIT_SUBS,  s_WRITING        },
        { s_TAG_NAME,       c_OTHER,         a_BUILD_NAME, s_TAG_NAME       },
        { s_ERROR,          0,               a_ERROR,      s_DONE           },
        { s_DONE,           0,               a_NIL,        0                },
        /* MUST be last: */
        { s_LAST,           0,               0,            0                },
    };

    /* Output Setup */
    tmbstr result = NULL;
    int g_result = 100;  // minimum buffer grow size
    int l_result = 0;    // buffer current size
    int i_result = 0;    // current string position
    int writer_len = 0;  // writer length

    ctmbstr writer = NULL;

    /* Current tag name setup */
    tmbstr name = NULL; // tag name
    int g_name = 10;    // buffer grow size
    int l_name = 0;     // buffer current size
    int i_name = 0;     // current string position

    /* Pump Setup */
    int i = 0;
    states state = s_DATA;
    charstates charstate;
    char c;
    int j = 0, k = 0;
    transitionType transition;

    if ( !description || (strlen(description) < 1) )
    {
        return NULL;
    }

    /* Process the HTML Snippet */
    do {
        c = description[i];

        /* Determine secondary state. */
        switch (c)
        {
            case '\0':
                charstate = c_EOF;
                break;

            case '<':
            case '&':
                charstate = c_BRACKET_OPEN;
                break;

            case '>':
            case ';':
                charstate = c_BRACKET_CLOSE;
                break;

            default:
                charstate = c_OTHER;
                break;
        }

        /* Find the correct instruction */
        j = 0;
        while (transitions[j].state != s_LAST)
        {
            transition = transitions[j];
            if ( transition.state == state && transition.charstate == charstate ) {
                switch ( transition.action )
                {
                        /* This action is building the name of an HTML tag. */
                    case a_BUILD_NAME:
                        if ( !name )
                        {
                            l_name = g_name;
                            name = calloc(l_name, 1);
                        }

                        if ( i_name >= l_name )
                        {
                            l_name = l_name + g_name;
                            name = realloc(name, l_name);
                        }

                        strncpy(name + i_name, &c, 1);
                        i_name++;
                        i++;
                        break;

                        /* This character will be emitted into the output
                         stream. The only purpose of this action is to
                         ensure that `writer` is NULL as a flag that we
                         will output the current `c` */
                    case a_EMIT:
                        writer = NULL; // flag to use c
                        break;

                        /* Now that we've consumed a tag, we will emit the
                         substitution if any has been specified in
                         `replacements`. */
                    case a_EMIT_SUBS:
                        name[i_name] = '\0';
                        i_name = 0;
                        k = 0;
                        writer = "";
                        while ( replacements[k].tag )
                        {
                            if ( strcmp( replacements[k].tag, name ) == 0 )
                            {
                                writer = replacements[k].replacement;
                            }
                            k++;
                        }
                        break;

                        /* This action will add to our `result` string, expanding
                         the buffer as necessary in reasonable chunks. */
                    case a_WRITE:
                        if ( !writer )
                            writer_len = 1;
                        else
                            writer_len = strlen( writer );
                        /* Lazy buffer creation */
                        if ( !result )
                        {
                            l_result = writer_len + g_result;
                            result = calloc(l_result, 1);
                        }
                        /* Grow the buffer if needed */
                        if ( i_result + writer_len >= l_result )
                        {
                            l_result = l_result + writer_len + g_result;
                            result = realloc(result, l_result);
                        }
                        /* Add current writer to the buffer */
                        if ( !writer )
                        {
                            result[i_result] = c;
                            result[i_result +1] = '\0';
                        }
                        else
                        {
                            strncpy( result + i_result, writer, writer_len );
                        }

                        i_result += writer_len;
                        i++;
                        break;

                        /* This action could be more robust but it serves the
                         current purpose. Cross our fingers and count on our
                         localizers not to give bad HTML descriptions. */
                    case a_ERROR:
                        printf("<Error> The localized string probably has bad HTML.\n");
                        goto EXIT_CLEANLY;

                        /* Just a NOP. */
                    case a_NIL:
                        break;

                        /* The default case also handles the CONSUME action. */
                    default:
                        i++;
                        break;
                }

                state = transition.next_state;
                break;
            }
            j++;
        }
    } while ( description[i] );

EXIT_CLEANLY:

    if ( name )
        free(name);
    return result;
}


/**
 **  Handles the -help-option service.
 */
static void optionDescribe( TidyDoc tdoc, char *tag )
{
    tmbstr result = NULL;
    TidyOptionId topt;

    topt = tidyOptGetIdForName( tag );

    if (topt < N_TIDY_OPTIONS)
    {
        result = cleanup_description( tidyOptGetDoc( tdoc, tidyGetOption( tdoc, topt ) ) );
    }
    else
    {
        result = (tmbstr)tidyLocalizedString(TC_STRING_UNKNOWN_OPTION_B);
    }

    printf( "\n" );
    printf( "`--%s`\n\n", tag );
    print1Column( "%-68.68s\n", 68, result );
    printf( "\n" );
    if ( (topt < N_TIDY_OPTIONS) && ( result ) )
        free ( result );
}


/**
 *  Prints the option value for a given option.
 */
static void printOptionValues( TidyDoc ARG_UNUSED(tdoc), TidyOption topt,
                              OptionDesc *d )
{
    TidyOptionId optId = tidyOptGetId( topt );
    ctmbstr ro = tidyOptIsReadOnly( topt ) ? "*" : "" ;

    switch ( optId )
    {
        case TidyInlineTags:
        case TidyBlockTags:
        case TidyEmptyTags:
        case TidyPreTags:
        {
            TidyIterator pos = tidyOptGetDeclTagList( tdoc );
            while ( pos )
            {
                d->def = tidyOptGetNextDeclTag(tdoc, optId, &pos);
                if ( pos )
                {
                    if ( *d->name )
                        printf( valfmt, d->name, d->type, ro, d->def );
                    else
                        printf( fmt, d->name, d->type, d->def );
                    d->name = "";
                    d->type = "";
                }
            }
        }
            break;
        case TidyNewline:
            d->def = tidyOptGetCurrPick( tdoc, optId );
            break;
        default:
            break;
    }

    /* fix for http://tidy.sf.net/bug/873921 */
    if ( *d->name || *d->type || (d->def && *d->def) )
    {
        if ( ! d->def )
            d->def = "";
        if ( *d->name )
            printf( valfmt, d->name, d->type, ro, d->def );
        else
            printf( fmt, d->name, d->type, d->def );
    }
}

/**
 **  Handles the -show-config service.
 */
static void optionvalues( TidyDoc tdoc )
{
    printf( "\n%s\n\n", tidyLocalizedString(TC_STRING_CONF_HEADER) );
    printf( fmt, tidyLocalizedString(TC_STRING_CONF_NAME),
           tidyLocalizedString(TC_STRING_CONF_TYPE),
           tidyLocalizedString(TC_STRING_CONF_VALUE) );
    printf( fmt, ul, ul, ul );

    ForEachSortedOption( tdoc, printOptionValues );

    printf( "\n\n%s\n\n", tidyLocalizedString(TC_STRING_CONF_NOTE) );
}

/**
 **  Handles the -version service.
 */
static void version( void )
{
#ifdef PLATFORM_NAME
    printf( tidyLocalizedString( TC_STRING_VERS_A ), PLATFORM_NAME, tidyLibraryVersion() );
#else
    printf( tidyLocalizedString( TC_STRING_VERS_B ), tidyLibraryVersion() );
#endif
    printf("\n");
}


/**
 **  Handles the printing of option description for
 **  -xml-options-strings service.
 **/
static void printXMLOptionString( TidyDoc tdoc, TidyOption topt, OptionDesc *d )
{
    tmbstr description;

    if ( tidyOptIsReadOnly(topt) )
        return;

    description = cleanup_description( tidyOptGetDoc( tdoc, topt ) );

    printf( " <option>\n" );
    printf( "  <name>%s</name>\n",d->name);
    printf( "  <description class=\"%s\">%s</description>\n", tidyGetLanguage(), description );
    printf( " </option>\n" );
    free( description );
}

/**
 **  Handles the -xml-options-strings service.
 **  This service is primarily helppful to developers and localizers to test
 **  that option description strings as represented on screen output are
 **  correct and do not break tidy.
 **/
static void xml_options_strings( TidyDoc tdoc )
{
    printf( "<?xml version=\"1.0\"?>\n"
           "<options_strings version=\"%s\">\n", tidyLibraryVersion());
    ForEachOption( tdoc, printXMLOptionString);
    printf( "</options_strings>\n" );
}


/**
 **  Handles the -xml-strings service.
 **  This service is primarily helpful to developers and localizers to
 **  compare localized strings to the built in `en` strings.
 */
static void xml_strings( void )
{
    uint i;
    TidyIterator j;

    ctmbstr current_language = tidyGetLanguage();
    Bool skip_current = strcmp( current_language, "en" ) == 0;
    Bool matches_base;

    printf( "<?xml version=\"1.0\"?>\n"
           "<localized_strings version=\"%s\">\n", tidyLibraryVersion());

    j = getStringKeyList();
    while (j) {
        i = getNextStringKey(&j);
        printf( "<localized_string id=\"%u\">\n", i );
        printf( " <string class=\"%s\">", "en" );
        printf("%s", tidyDefaultString(i));
        printf( "</string>\n" );
        if ( !skip_current ) {
            matches_base = strcmp( tidyLocalizedString(i), tidyDefaultString(i) ) == 0;
            printf( " <string class=\"%s\" same_as_base=\"%s\">", tidyGetLanguage(), matches_base ? "yes" : "no" );
            printf("%s", tidyLocalizedString(i));
            printf( "</string>\n" );
        }
        printf( "</localized_string>\n");
    }

    printf( "</localized_strings>\n" );
}


/**
 **  Handles the -lang help service.
 */
static void lang_help( void )
{
    printf( "%s", tidyLocalizedString(TC_TXT_HELP_LANG_1) );
    tidyPrintWindowsLanguageNames("  %-20s -> %s\n");
    printf( "%s", tidyLocalizedString(TC_TXT_HELP_LANG_2) );
    tidyPrintTidyLanguageNames("  %s\n");
    printf( "%s", tidyLocalizedString(TC_TXT_HELP_LANG_3) );
}


/**
 **  Provides the `unknown option` output.
 */
static void unknownOption( uint c )
{
    fprintf( errout, tidyLocalizedString( TC_STRING_UNKNOWN_OPTION ), (char)c );
    fprintf( errout, "\n");
}


/**
 **  MAIN --  let's do something here.
 */
int main( int argc, char** argv )
{
    ctmbstr prog = argv[0];
    ctmbstr cfgfil = NULL, errfil = NULL, htmlfil = NULL;
    TidyDoc tdoc = tidyCreate();
    int status = 0;
    tmbstr locale = NULL;

    uint contentErrors = 0;
    uint contentWarnings = 0;
    uint accessWarnings = 0;

    errout = stderr;  /* initialize to stderr */

    /* Set an atexit handler. */
    atexit( tidy_cleanup );
    
    /* Set the locale for tidy's output. */
    locale = tidySystemLocale(locale);
    tidySetLanguage(locale);
    if ( locale )
        free( locale );

#if defined(_WIN32)
    /* Force Windows console to use UTF, otherwise many characters will
     * be garbage. Note that East Asian languages *are* supported, but
     * only when Windows OS locale (not console only!) is set to an
     * East Asian language.
     */
    win_cp = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);
#endif

#if !defined(NDEBUG) && defined(_MSC_VER)
    set_log_file((char *)"temptidy.txt", 0);
    // add_append_log(1);
#endif

    /*
     * Look for default configuration files using any of
     * the following possibilities:
     *  - TIDY_CONFIG_FILE - from tidyplatform.h, typically /etc/tidy.conf
     *  - HTML_TIDY        - environment variable
     *  - TIDY_USER_CONFIG_FILE - from tidyplatform.h, typically ~/tidy.conf
     */

#ifdef TIDY_CONFIG_FILE
    if ( tidyFileExists( tdoc, TIDY_CONFIG_FILE) )
    {
        status = tidyLoadConfig( tdoc, TIDY_CONFIG_FILE );
        if ( status != 0 ) {
            fprintf(errout, tidyLocalizedString( TC_MAIN_ERROR_LOAD_CONFIG ), TIDY_CONFIG_FILE, status);
            fprintf(errout, "\n");
        }
    }
#endif /* TIDY_CONFIG_FILE */

    if ( (cfgfil = getenv("HTML_TIDY")) != NULL )
    {
        status = tidyLoadConfig( tdoc, cfgfil );
        if ( status != 0 ) {
            fprintf(errout, tidyLocalizedString( TC_MAIN_ERROR_LOAD_CONFIG ), cfgfil, status);
            fprintf(errout, "\n");
        }
    }
#ifdef TIDY_USER_CONFIG_FILE
    else if ( tidyFileExists( tdoc, TIDY_USER_CONFIG_FILE) )
    {
        status = tidyLoadConfig( tdoc, TIDY_USER_CONFIG_FILE );
        if ( status != 0 ) {
            fprintf(errout, tidyLocalizedString( TC_MAIN_ERROR_LOAD_CONFIG ), TIDY_USER_CONFIG_FILE, status);
            fprintf(errout, "\n");
        }
    }
#endif /* TIDY_USER_CONFIG_FILE */


    /*
     * Read command line
     */

    while ( argc > 0 )
    {
        if (argc > 1 && argv[1][0] == '-')
        {
            /* support -foo and --foo */
            ctmbstr arg = argv[1] + 1;

            if ( strcasecmp(arg, "xml") == 0)
                tidyOptSetBool( tdoc, TidyXmlTags, yes );

            else if ( strcasecmp(arg,   "asxml") == 0 ||
                     strcasecmp(arg, "asxhtml") == 0 )
            {
                tidyOptSetBool( tdoc, TidyXhtmlOut, yes );
            }
            else if ( strcasecmp(arg,   "ashtml") == 0 )
                tidyOptSetBool( tdoc, TidyHtmlOut, yes );

            else if ( strcasecmp(arg, "indent") == 0 )
            {
                tidyOptSetInt( tdoc, TidyIndentContent, TidyAutoState );
                if ( tidyOptGetInt(tdoc, TidyIndentSpaces) == 0 )
                    tidyOptResetToDefault( tdoc, TidyIndentSpaces );
            }
            else if ( strcasecmp(arg, "omit") == 0 )
                tidyOptSetBool( tdoc, TidyOmitOptionalTags, yes );

            else if ( strcasecmp(arg, "upper") == 0 )
                tidyOptSetBool( tdoc, TidyUpperCaseTags, yes );

            else if ( strcasecmp(arg, "clean") == 0 )
                tidyOptSetBool( tdoc, TidyMakeClean, yes );

            else if ( strcasecmp(arg, "gdoc") == 0 )
                tidyOptSetBool( tdoc, TidyGDocClean, yes );

            else if ( strcasecmp(arg, "bare") == 0 )
                tidyOptSetBool( tdoc, TidyMakeBare, yes );

            else if ( strcasecmp(arg, "raw") == 0     ||
                     strcasecmp(arg, "ascii") == 0    ||
                     strcasecmp(arg, "latin0") == 0   ||
                     strcasecmp(arg, "latin1") == 0   ||
                     strcasecmp(arg, "utf8") == 0     ||
#ifndef NO_NATIVE_ISO2022_SUPPORT
                     strcasecmp(arg, "iso2022") == 0  ||
#endif
#if SUPPORT_UTF16_ENCODINGS
                     strcasecmp(arg, "utf16le") == 0  ||
                     strcasecmp(arg, "utf16be") == 0  ||
                     strcasecmp(arg, "utf16") == 0    ||
#endif
#if SUPPORT_ASIAN_ENCODINGS
                     strcasecmp(arg, "shiftjis") == 0 ||
                     strcasecmp(arg, "big5") == 0     ||
#endif
                     strcasecmp(arg, "mac") == 0      ||
                     strcasecmp(arg, "win1252") == 0  ||
                     strcasecmp(arg, "ibm858") == 0 )
            {
                tidySetCharEncoding( tdoc, arg );
            }
            else if ( strcasecmp(arg, "numeric") == 0 )
                tidyOptSetBool( tdoc, TidyNumEntities, yes );

            else if ( strcasecmp(arg, "modify") == 0 ||
                     strcasecmp(arg, "change") == 0 ||  /* obsolete */
                     strcasecmp(arg, "update") == 0 )   /* obsolete */
            {
                tidyOptSetBool( tdoc, TidyWriteBack, yes );
            }
            else if ( strcasecmp(arg, "errors") == 0 )
                tidyOptSetBool( tdoc, TidyShowMarkup, no );

            else if ( strcasecmp(arg, "quiet") == 0 )
                tidyOptSetBool( tdoc, TidyQuiet, yes );

            /* Currenly user must specify a language
             prior to anything that causes output */
            else if ( strcasecmp(arg, "language") == 0 ||
                     strcasecmp(arg,     "lang") == 0 )
                if ( argc >= 3)
                {
                    if ( strcasecmp(argv[2], "help") == 0 )
                    {
                        lang_help();
                        exit(0);
                    }
                    if ( !tidySetLanguage( argv[2] ) )
                    {
                        printf(tidyLocalizedString(TC_STRING_LANG_NOT_FOUND),
                               argv[2], tidyGetLanguage());
                        printf("\n");
                    }
                    --argc;
                    ++argv;
                }
                else
                {
                    printf( "%s\n", tidyLocalizedString(TC_STRING_LANG_MUST_SPECIFY));
                }

                else if ( strcasecmp(arg, "help") == 0 ||
                         strcasecmp(arg, "-help") == 0 ||
                         strcasecmp(arg,    "h") == 0 || *arg == '?' )
                {
                    help( prog );
                    tidyRelease( tdoc );
                    return 0; /* success */
                }
                else if ( strcasecmp(arg, "xml-help") == 0)
                {
                    xml_help( );
                    tidyRelease( tdoc );
                    return 0; /* success */
                }
                else if ( strcasecmp(arg, "xml-options-strings") == 0)
                {
                    xml_options_strings( tdoc );
                    tidyRelease( tdoc );
                    return 0; /* success */
                }
                else if ( strcasecmp(arg, "xml-strings") == 0)
                {
                    xml_strings( );
                    tidyRelease( tdoc );
                    return 0; /* success */
                }
                else if ( strcasecmp(arg, "help-config") == 0 )
                {
                    optionhelp( tdoc );
                    tidyRelease( tdoc );
                    return 0; /* success */
                }
                else if ( strcasecmp(arg, "help-option") == 0 )
                {
                    if ( argc >= 3)
                    {
                        optionDescribe( tdoc, argv[2] );
                    }
                    else
                    {
                        printf( "%s\n", tidyLocalizedString(TC_STRING_MUST_SPECIFY));
                    }
                    tidyRelease( tdoc );
                    return 0; /* success */
                }
                else if ( strcasecmp(arg, "xml-config") == 0 )
                {
                    XMLoptionhelp( tdoc );
                    tidyRelease( tdoc );
                    return 0; /* success */
                }
                else if ( strcasecmp(arg, "show-config") == 0 )
                {
                    optionvalues( tdoc );
                    tidyRelease( tdoc );
                    return 0; /* success */
                }
                else if ( strcasecmp(arg, "config") == 0 )
                {
                    if ( argc >= 3 )
                    {
                        ctmbstr post;

                        tidyLoadConfig( tdoc, argv[2] );

                        /* Set new error output stream if setting changed */
                        post = tidyOptGetValue( tdoc, TidyErrFile );
                        if ( post && (!errfil || !samefile(errfil, post)) )
                        {
                            errfil = post;
                            errout = tidySetErrorFile( tdoc, post );
                        }

                        --argc;
                        ++argv;
                    }
                }

                else if ( strcasecmp(arg, "output") == 0 ||
                         strcasecmp(arg, "-output-file") == 0 ||
                         strcasecmp(arg, "o") == 0 )
                {
                    if ( argc >= 3 )
                    {
                        tidyOptSetValue( tdoc, TidyOutFile, argv[2] );
                        --argc;
                        ++argv;
                    }
                }
                else if ( strcasecmp(arg,  "file") == 0 ||
                         strcasecmp(arg, "-file") == 0 ||
                         strcasecmp(arg,     "f") == 0 )
                {
                    if ( argc >= 3 )
                    {
                        errfil = argv[2];
                        errout = tidySetErrorFile( tdoc, errfil );
                        --argc;
                        ++argv;
                    }
                }
                else if ( strcasecmp(arg,  "wrap") == 0 ||
                         strcasecmp(arg, "-wrap") == 0 ||
                         strcasecmp(arg,     "w") == 0 )
                {
                    if ( argc >= 3 )
                    {
                        uint wraplen = 0;
                        int nfields = sscanf( argv[2], "%u", &wraplen );
                        tidyOptSetInt( tdoc, TidyWrapLen, wraplen );
                        if (nfields > 0)
                        {
                            --argc;
                            ++argv;
                        }
                    }
                }
                else if ( strcasecmp(arg,  "version") == 0 ||
                         strcasecmp(arg, "-version") == 0 ||
                         strcasecmp(arg,        "v") == 0 )
                {
                    version();
                    tidyRelease( tdoc );
                    return 0;  /* success */

                }
                else if ( strncmp(argv[1], "--", 2 ) == 0)
                {
                    if ( tidyOptParseValue(tdoc, argv[1]+2, argv[2]) )
                    {
                        /* Set new error output stream if setting changed */
                        ctmbstr post = tidyOptGetValue( tdoc, TidyErrFile );
                        if ( post && (!errfil || !samefile(errfil, post)) )
                        {
                            errfil = post;
                            errout = tidySetErrorFile( tdoc, post );
                        }

                        ++argv;
                        --argc;
                    }
                }

#if SUPPORT_ACCESSIBILITY_CHECKS
                else if ( strcasecmp(arg, "access") == 0 )
                {
                    if ( argc >= 3 )
                    {
                        uint acclvl = 0;
                        int nfields = sscanf( argv[2], "%u", &acclvl );
                        tidyOptSetInt( tdoc, TidyAccessibilityCheckLevel, acclvl );
                        if (nfields > 0)
                        {
                            --argc;
                            ++argv;
                        }
                    }
                }
#endif

                else
                {
                    uint c;
                    ctmbstr s = argv[1];

                    while ( (c = *++s) != '\0' )
                    {
                        switch ( c )
                        {
                            case 'i':
                                tidyOptSetInt( tdoc, TidyIndentContent, TidyAutoState );
                                if ( tidyOptGetInt(tdoc, TidyIndentSpaces) == 0 )
                                    tidyOptResetToDefault( tdoc, TidyIndentSpaces );
                                break;

                                /* Usurp -o for output file.  Anyone hiding end tags?
                                 case 'o':
                                 tidyOptSetBool( tdoc, TidyHideEndTags, yes );
                                 break;
                                 */

                            case 'u':
                                tidyOptSetBool( tdoc, TidyUpperCaseTags, yes );
                                break;

                            case 'c':
                                tidyOptSetBool( tdoc, TidyMakeClean, yes );
                                break;

                            case 'g':
                                tidyOptSetBool( tdoc, TidyGDocClean, yes );
                                break;

                            case 'b':
                                tidyOptSetBool( tdoc, TidyMakeBare, yes );
                                break;

                            case 'n':
                                tidyOptSetBool( tdoc, TidyNumEntities, yes );
                                break;

                            case 'm':
                                tidyOptSetBool( tdoc, TidyWriteBack, yes );
                                break;

                            case 'e':
                                tidyOptSetBool( tdoc, TidyShowMarkup, no );
                                break;

                            case 'q':
                                tidyOptSetBool( tdoc, TidyQuiet, yes );
                                break;

                            default:
                                unknownOption( c );
                                break;
                        }
                    }
                }

            --argc;
            ++argv;
            continue;
        }

        if ( argc > 1 )
        {
            htmlfil = argv[1];
#if (!defined(NDEBUG) && defined(_MSC_VER))
            SPRTF("Tidying '%s'\n", htmlfil);
#endif // DEBUG outout
            if ( tidyOptGetBool(tdoc, TidyEmacs) )
                tidyOptSetValue( tdoc, TidyEmacsFile, htmlfil );
            status = tidyParseFile( tdoc, htmlfil );
        }
        else
        {
            htmlfil = "stdin";
            status = tidyParseStdin( tdoc );
        }

        if ( status >= 0 )
            status = tidyCleanAndRepair( tdoc );

        if ( status >= 0 ) {
            status = tidyRunDiagnostics( tdoc );
            if ( !tidyOptGetBool(tdoc, TidyQuiet) ) {
                /* NOT quiet, show DOCTYPE, if not already shown */
                if (!tidyOptGetBool(tdoc, TidyShowInfo)) {
                    tidyOptSetBool( tdoc, TidyShowInfo, yes );
                    tidyReportDoctype( tdoc );  /* FIX20140913: like warnings, errors, ALWAYS report DOCTYPE */
                    tidyOptSetBool( tdoc, TidyShowInfo, no );
                }
            }

        }
        if ( status > 1 ) /* If errors, do we want to force output? */
            status = ( tidyOptGetBool(tdoc, TidyForceOutput) ? status : -1 );

        if ( status >= 0 && tidyOptGetBool(tdoc, TidyShowMarkup) )
        {
            if ( tidyOptGetBool(tdoc, TidyWriteBack) && argc > 1 )
                status = tidySaveFile( tdoc, htmlfil );
            else
            {
                ctmbstr outfil = tidyOptGetValue( tdoc, TidyOutFile );
                if ( outfil ) {
                    status = tidySaveFile( tdoc, outfil );
                } else {
#if !defined(NDEBUG) && defined(_MSC_VER)
                    static char tmp_buf[264];
                    sprintf(tmp_buf,"%s.html",get_log_file());
                    status = tidySaveFile( tdoc, tmp_buf );
                    SPRTF("Saved tidied content to '%s'\n",tmp_buf);
#else
                    status = tidySaveStdout( tdoc );
#endif
                }
            }
        }
        
        contentErrors   += tidyErrorCount( tdoc );
        contentWarnings += tidyWarningCount( tdoc );
        accessWarnings  += tidyAccessWarningCount( tdoc );
        
        --argc;
        ++argv;
        
        if ( argc <= 1 )
            break;
    } /* read command line loop */
    
    
    if (!tidyOptGetBool(tdoc, TidyQuiet) &&
        errout == stderr && !contentErrors)
        fprintf(errout, "\n");
    
    if (contentErrors + contentWarnings > 0 &&
        !tidyOptGetBool(tdoc, TidyQuiet))
        tidyErrorSummary(tdoc);
    
    if (!tidyOptGetBool(tdoc, TidyQuiet))
        tidyGeneralInfo(tdoc);
    
    /* called to free hash tables etc. */
    tidyRelease( tdoc );
    
    /* return status can be used by scripts */
    if ( contentErrors > 0 )
        return 2;
    
    if ( contentWarnings > 0 )
        return 1;
    
    /* 0 signifies all is ok */
    return 0;
}

/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
