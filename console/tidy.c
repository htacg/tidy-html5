/*
 tidy.c - HTML TidyLib command line driver

 Copyright (c) 1998-2008 World Wide Web Consortium
 (Massachusetts Institute of Technology, European Research
 Consortium for Informatics and Mathematics, Keio University).
 All Rights Reserved.

 */

#include "tidy.h"
#include "language.h"
#if !defined(NDEBUG) && defined(_MSC_VER)
#include "sprtf.h"
#endif

#ifndef SPRTF
#define SPRTF printf
#endif

static FILE* errout = NULL;  /* set to stderr */
/* static FILE* txtout = NULL; */  /* set to stdout */

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
 **  Exits with an error in the event of an out of memory condition.
 */
static void outOfMemory(void)
{
    fprintf(stderr,"%s", tidyLocalizedString(TC_STRING_OUT_OF_MEMORY));
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
        strncpy(sbuf,s,l);
        sbuf[l] = '\0';
        return s+n;
    }
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
static const char helpfmt[] = " %-19.19s %-58.58s\n";
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
    { "misc", TC_STRING_MISC }
};

/**
 **  The struct and subsequent array keep the help output structured
 **  because we _also_ output all of this stuff as as XML.
 **  @todo: replace .desc with .key.
 */
typedef struct {
    CmdOptCategory cat; /**< Category */
    ctmbstr name1;      /**< Name */
    uint key;           /**< Key to fetch the localized description. */
    ctmbstr eqconfig;   /**< Equivalent configuration option */
    ctmbstr name2;      /**< Name */
    ctmbstr name3;      /**< Name */
} CmdOptDesc;

/* All instances of %s will be substituted with localized
 'file' using the key TC_LABEL_FILE. */
static const CmdOptDesc cmdopt_defs[] =  {
    { CmdOptFileManip, "-output <%s>",     TC_OPT_OUTPUT,   "output-file: <%s>", "-o <%s>" },
    { CmdOptFileManip, "-config <%s>",     TC_OPT_CONFIG,   NULL },
    { CmdOptFileManip, "-file <%s>",       TC_OPT_FILE,     "error-file: <%s>", "-f <%s>" },
    { CmdOptFileManip, "-modify",          TC_OPT_MODIFY,   "write-back: yes", "-m" },
    { CmdOptProcDir,   "-indent",          TC_OPT_INDENT,   "indent: auto", "-i" },
    { CmdOptProcDir,   "-wrap <column>",   TC_OPT_WRAP,     "wrap: <column>", "-w <column>" },
    { CmdOptProcDir,   "-upper",           TC_OPT_UPPER,    "uppercase-tags: yes", "-u" },
    { CmdOptProcDir,   "-clean",           TC_OPT_CLEAN,    "clean: yes", "-c" },
    { CmdOptProcDir,   "-bare",            TC_OPT_BARE,     "bare: yes", "-b" },
    { CmdOptProcDir,   "-gdoc",            TC_OPT_GDOC,     "gdoc: yes", "-g" },
    { CmdOptProcDir,   "-numeric",         TC_OPT_NUMERIC,  "numeric-entities: yes", "-n" },
    { CmdOptProcDir,   "-errors",          TC_OPT_ERRORS,   "markup: no", "-e" },
    { CmdOptProcDir,   "-quiet",           TC_OPT_QUIET,    "quiet: yes", "-q" },
    { CmdOptProcDir,   "-omit",            TC_OPT_OMIT,     "omit-optional-tags: yes" },
    { CmdOptProcDir,   "-xml",             TC_OPT_XML,      "input-xml: yes" },
    { CmdOptProcDir,   "-asxml",           TC_OPT_ASXML,    "output-xhtml: yes", "-asxhtml" },
    { CmdOptProcDir,   "-ashtml",          TC_OPT_ASHTML,   "output-html: yes" },
#if SUPPORT_ACCESSIBILITY_CHECKS
    { CmdOptProcDir,   "-access <level>",  TC_OPT_ACCESS,   "accessibility-check: <level>" },
#endif
    { CmdOptCharEnc,   "-raw",             TC_OPT_RAW,      NULL },
    { CmdOptCharEnc,   "-ascii",           TC_OPT_ASCII,    NULL },
    { CmdOptCharEnc,   "-latin0",          TC_OPT_LATIN0,   NULL },
    { CmdOptCharEnc,   "-latin1",          TC_OPT_LATIN1,   NULL },
#ifndef NO_NATIVE_ISO2022_SUPPORT
    { CmdOptCharEnc,   "-iso2022",         TC_OPT_ISO2022,  NULL },
#endif
    { CmdOptCharEnc,   "-utf8",            TC_OPT_UTF8,     NULL },
    { CmdOptCharEnc,   "-mac",             TC_OPT_MAC,      NULL },
    { CmdOptCharEnc,   "-win1252",         TC_OPT_WIN1252,  NULL },
    { CmdOptCharEnc,   "-ibm858",          TC_OPT_IBM858,   NULL },
#if SUPPORT_UTF16_ENCODINGS
    { CmdOptCharEnc,   "-utf16le",         TC_OPT_UTF16LE,  NULL },
    { CmdOptCharEnc,   "-utf16be",         TC_OPT_UTF16BE,  NULL },
    { CmdOptCharEnc,   "-utf16",           TC_OPT_UTF16,    NULL },
#endif
#if SUPPORT_ASIAN_ENCODINGS /* #431953 - RJ */
    { CmdOptCharEnc,   "-big5",            TC_OPT_BIG5,     NULL },
    { CmdOptCharEnc,   "-shiftjis",        TC_OPT_SHIFTJIS, NULL },
    { CmdOptCharEnc,   "-language <lang>", TC_OPT_LANGUAGE, "language: <lang>" },
#endif
    { CmdOptMisc,      "-version",         TC_OPT_VERSION,  NULL,  "-v" },
    { CmdOptMisc,      "-help",            TC_OPT_HELP,     NULL,  "-h", "-?" },
    { CmdOptMisc,      "-xml-help",        TC_OPT_XMLHELP,  NULL },
    { CmdOptMisc,      "-help-config",     TC_OPT_HELPCFG,  NULL },
    { CmdOptMisc,      "-xml-config",      TC_OPT_XMLCFG,   NULL },
    { CmdOptMisc,      "-show-config",     TC_OPT_SHOWCFG,  NULL },
    { CmdOptMisc,      NULL,               0,               NULL }
};

static ctmbstr stringWithFormat( const ctmbstr fmt, ... )
{
    va_list argList = {};
    char *result = NULL;
    int len = 0;

    va_start(argList, fmt);
    len = vsnprintf( result, 0, fmt, argList );
    va_end(argList);

    if (!(result = malloc((len + 1) * sizeof(char))))
        outOfMemory();

    va_start(argList, fmt);
    len = vsnprintf( result, len + 1, fmt, argList);
    va_end(argList);

    return result;
}

static void localize_option_names( CmdOptDesc *pos)
{
    ctmbstr fileString = tidyLocalizedString(TC_LABEL_FILE);
    pos->name1 = stringWithFormat(pos->name1, fileString);
    if ( pos->name2 )
        pos->name2 = stringWithFormat(pos->name2, fileString);
    if ( pos->name3 )
        pos->name3 = stringWithFormat(pos->name3, fileString);
    if ( pos->eqconfig )
        pos->eqconfig = stringWithFormat(pos->eqconfig, fileString);
}

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
    if (localPos.name2)
    {
        strcat(name, ", ");
        strcat(name, localPos.name2);
    }
    if (localPos.name3)
    {
        strcat(name, ", ");
        strcat(name, localPos.name3);
    }
    return name;
}

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
            print2Columns( helpfmt, 19, 58, name, tidyLocalizedString( pos->key ) );
            free(name);
        }
        printf("\n");
    }
}

static void print_xml_help_option_element( ctmbstr element, ctmbstr name )
{
    tmbstr escpName;
    if (!name)
        return;
    printf("  <%s>%s</%s>\n", element, escpName = get_escaped_name(name),
           element);
    free(escpName);
}

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

static void xml_help( void )
{
    printf( "<?xml version=\"1.0\"?>\n"
           "<cmdline version=\"%s\">\n", tidyLibraryVersion());
    print_xml_help_option();
    printf( "</cmdline>\n" );
}

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

static void help( ctmbstr prog )
{
    printf( "\n");
    printf( "%s [options...] [file...] [options...] [file...]\n", get_final_name(prog) );
    printf( "Utility to clean up and pretty print HTML/XHTML/XML.\n");
    printf( "\n");

    printf( "This is modern HTML Tidy version %s.\n", tidyLibraryVersion() );
    printf( "\n");

#ifdef PLATFORM_NAME
    printf( "Options for HTML Tidy for %s:\n", PLATFORM_NAME );
#else
    printf( "Options for HTML Tidy:\n");
#endif
    printf( "\n");

    print_help_option();

    printf( "Use --optionX valueX for any configuration option \"optionX\" with argument\n"
           "\"valueX\". For a list of the configuration options, use \"-help-config\" or refer\n"
           "to the man page.\n\n");

    printf( "Input/Output default to stdin/stdout respectively.\n");
    printf( "\n");
    printf( "Single letter options apart from -f may be combined\n");
    printf( "as in:  tidy -f errs.txt -imu foo.html\n");
    printf( "\n");
    printf( "For more information about HTML Tidy, see\n" );
    printf( "  http://www.html-tidy.org/\n" );
    printf( "\n");
    printf( "For more information on HTML, see the following:\n" );
    printf( "\n");
    printf( "  HTML: Edition for Web Authors (the latest HTML specification)\n");
    printf( "  http://dev.w3.org/html5/spec-author-view\n" );
    printf( "\n");
    printf( "  HTML: The Markup Language (an HTML language reference)\n" );
    printf( "  http://dev.w3.org/html5/markup/\n" );
    printf( "\n");
    printf( "File bug reports at https://github.com/htacg/tidy-html5/issues/\n" );
    printf( "or send questions and comments to public-htacg@w3.org.\n" );
    printf( "\n");
    printf( "Validate your HTML documents using the W3C Nu Markup Validator:\n" );
    printf( "\n");
    printf( "  http://validator.w3.org/nu/" );
    printf( "\n\n");
}

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

static
ctmbstr ConfigCategoryName( TidyConfigCategory id )
{
    switch( id )
    {
        case TidyMarkup:
            return "markup";
        case TidyDiagnostics:
            return "diagnostics";
        case TidyPrettyPrint:
            return "print";
        case TidyEncoding:
            return "encoding";
        case TidyMiscellaneous:
            return "misc";
    }
    fprintf(stderr, "Fatal error: impossible value for id='%d'.\n", (int)id);
    assert(0);
    abort();
    return "never_here"; /* only for the compiler warning */
}

/* Description of an option */
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


/* Create description "d" related to "opt" */
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

/* Array holding all options. Contains a trailing sentinel. */
typedef struct {
    TidyOption topt[N_TIDY_OPTIONS];
} AllOption_t;

static
int cmpOpt(const void* e1_, const void *e2_)
{
    const TidyOption* e1 = (const TidyOption*)e1_;
    const TidyOption* e2 = (const TidyOption*)e2_;
    return strcmp(tidyOptGetName(*e1), tidyOptGetName(*e2));
}

static
void getSortedOption( TidyDoc tdoc, AllOption_t *tOption )
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

static
void PrintAllowedValuesFromPick( TidyOption topt )
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

static
void PrintAllowedValues( TidyOption topt, const OptionDesc *d )
{
    if (d->vals)
        printf( "%s", d->vals );
    else
        PrintAllowedValuesFromPick( topt );
}

static
void printXMLDescription( TidyDoc tdoc, TidyOption topt )
{
    ctmbstr doc = tidyOptGetDoc( tdoc, topt );

    if (doc)
        printf("  <description>%s</description>\n", doc);
    else
    {
        printf("  <description />\n");
        fprintf(stderr, "Warning: option `%s' is not documented.\n",
                tidyOptGetName( topt ));
    }
}

static
void printXMLCrossRef( TidyDoc tdoc, TidyOption topt )
{
    TidyOption optLinked;
    TidyIterator pos = tidyOptGetDocLinksList(tdoc, topt);
    while( pos )
    {
        optLinked = tidyOptGetNextDocLinks(tdoc, &pos );
        printf("  <seealso>%s</seealso>\n",tidyOptGetName(optLinked));
    }
}

static
void printXMLOption( TidyDoc tdoc, TidyOption topt, OptionDesc *d )
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

static void XMLoptionhelp( TidyDoc tdoc )
{
    printf( "<?xml version=\"1.0\"?>\n"
           "<config version=\"%s\">\n", tidyLibraryVersion());
    ForEachOption( tdoc, printXMLOption );
    printf( "</config>\n" );
}

static
tmbstr GetAllowedValuesFromPick( TidyOption topt )
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

static
tmbstr GetAllowedValues( TidyOption topt, const OptionDesc *d )
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

static
void printOption( TidyDoc ARG_UNUSED(tdoc), TidyOption topt,
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

static void optionhelp( TidyDoc tdoc )
{
    printf( "\nHTML Tidy Configuration Settings\n\n" );
    printf( "Within a file, use the form:\n\n" );
    printf( "wrap: 72\n" );
    printf( "indent: no\n\n" );
    printf( "When specified on the command line, use the form:\n\n" );
    printf( "--wrap 72 --indent no\n\n");

    printf( fmt, "Name", "Type", "Allowable values" );
    printf( fmt, ul, ul, ul );

    ForEachSortedOption( tdoc, printOption );
}

static void optiondescribe( TidyDoc tdoc, char *tag )
{
    char *result = NULL;
    TidyOptionId topt;

    printf( "\nNote this help function is UNDOCUMENTED, and still needs work.\n" );

    printf( "\n`%s`\n\n", tag );

    topt = tidyOptGetIdForName( tag );

    if (topt < N_TIDY_OPTIONS)
    {
        result = (char*)tidyOptGetDoc( tdoc, tidyGetOption( tdoc, topt ) );
    } else
    {
        result = "Unknown option.";
    }

    printf( "%s\n\n", result );
}

static
void printOptionValues( TidyDoc ARG_UNUSED(tdoc), TidyOption topt,
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

static void optionvalues( TidyDoc tdoc )
{
    printf( "\nConfiguration File Settings:\n\n" );
    printf( fmt, "Name", "Type", "Current Value" );
    printf( fmt, ul, ul, ul );

    ForEachSortedOption( tdoc, printOptionValues );

    printf( "\n\nValues marked with an *asterisk are calculated \n"
           "internally by HTML Tidy\n\n" );
}

static void version( void )
{
#ifdef PLATFORM_NAME
    printf( "HTML Tidy for %s version %s\n",
           PLATFORM_NAME, tidyLibraryVersion() );
#else
    printf( "HTML Tidy version %s\n", tidyLibraryVersion() );
#endif
}

static void unknownOption( uint c )
{
    fprintf( errout, "HTML Tidy: unknown option: %c\n", (char)c );
}

void progressTester( TidyDoc tdoc, uint srcLine, uint srcCol, uint dstLine)
{
    //   fprintf(stderr, "srcLine = %u, srcCol = %u, dstLine = %u\n", srcLine, srcCol, dstLine);
}

int main( int argc, char** argv )
{
    ctmbstr prog = argv[0];
    ctmbstr cfgfil = NULL, errfil = NULL, htmlfil = NULL;
    TidyDoc tdoc = tidyCreate();
    int status = 0;

    uint contentErrors = 0;
    uint contentWarnings = 0;
    uint accessWarnings = 0;

    errout = stderr;  /* initialize to stderr */

    tidySetPrettyPrinterCallback(tdoc, progressTester);

#if !defined(NDEBUG) && defined(_MSC_VER)
    set_log_file((char *)"temptidy.txt", 0);
    // add_append_log(1);
#endif

#ifdef TIDY_CONFIG_FILE
    if ( tidyFileExists( tdoc, TIDY_CONFIG_FILE) )
    {
        status = tidyLoadConfig( tdoc, TIDY_CONFIG_FILE );
        if ( status != 0 )
            fprintf(errout, "Loading config file \"%s\" failed, err = %d\n", TIDY_CONFIG_FILE, status);
    }
#endif /* TIDY_CONFIG_FILE */

    /* look for env var "HTML_TIDY" */
    /* then for ~/.tidyrc (on platforms defining $HOME) */

    if ( (cfgfil = getenv("HTML_TIDY")) != NULL )
    {
        status = tidyLoadConfig( tdoc, cfgfil );
        if ( status != 0 )
            fprintf(errout, "Loading config file \"%s\" failed, err = %d\n", cfgfil, status);
    }
#ifdef TIDY_USER_CONFIG_FILE
    else if ( tidyFileExists( tdoc, TIDY_USER_CONFIG_FILE) )
    {
        status = tidyLoadConfig( tdoc, TIDY_USER_CONFIG_FILE );
        if ( status != 0 )
            fprintf(errout, "Loading config file \"%s\" failed, err = %d\n", TIDY_USER_CONFIG_FILE, status);
    }
#endif /* TIDY_USER_CONFIG_FILE */

    /* read command line */
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

            else if ( strcasecmp(arg, "raw") == 0      ||
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
                    optiondescribe( tdoc, argv[2] );
                }
                else
                {
                    printf( "%s", "Tidy option name must be specified.\n");
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

#if SUPPORT_ASIAN_ENCODINGS
            else if ( strcasecmp(arg, "language") == 0 ||
                     strcasecmp(arg,     "lang") == 0 )
            {
                if ( argc >= 3 )
                {
                    tidyOptSetValue( tdoc, TidyLanguage, argv[2] );
                    --argc;
                    ++argv;
                }
            }
#endif

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
    }
    
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
