/*
  tidy.c - HTML TidyLib command line driver

  Copyright (c) 1998-2008 World Wide Web Consortium
  (Massachusetts Institute of Technology, European Research 
  Consortium for Informatics and Mathematics, Keio University).
  All Rights Reserved.

  CVS Info :

    $Author: arnaud02 $ 
    $Date: 2008/03/22 20:53:08 $ 
    $Revision: 1.50 $ 
*/

#include "tidy.h"

static FILE* errout = NULL;  /* set to stderr */
/* static FILE* txtout = NULL; */  /* set to stdout */

static Bool samefile( ctmbstr filename1, ctmbstr filename2 )
{
#if FILENAMES_CASE_SENSITIVE
    return ( strcmp( filename1, filename2 ) == 0 );
#else
    return ( strcasecmp( filename1, filename2 ) == 0 );
#endif
}

static void outOfMemory(void)
{
    fprintf(stderr,"Out of memory. Bailing out.");
    exit(1);
}

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

static const char helpfmt[] = " %-19.19s %-58.58s\n";
static const char helpul[]
        = "-----------------------------------------------------------------";
static const char fmt[] = "%-27.27s %-9.9s  %-40.40s\n";
static const char valfmt[] = "%-27.27s %-9.9s %-1.1s%-39.39s\n";
static const char ul[]
        = "=================================================================";

typedef enum
{
  CmdOptFileManip,
  CmdOptCatFIRST = CmdOptFileManip,
  CmdOptProcDir,
  CmdOptCharEnc,
  CmdOptMisc,
  CmdOptCatLAST
} CmdOptCategory;

static const struct {
    ctmbstr mnemonic;
    ctmbstr name;
} cmdopt_catname[] = {
    { "file-manip", "File manipulation" },
    { "process-directives", "Processing directives" },
    { "char-encoding", "Character encodings" },
    { "misc", "Miscellaneous" }
};

typedef struct {
    ctmbstr name1;      /**< Name */
    ctmbstr desc;       /**< Description */
    ctmbstr eqconfig;   /**< Equivalent configuration option */
    CmdOptCategory cat; /**< Category */
    ctmbstr name2;      /**< Name */
    ctmbstr name3;      /**< Name */
} CmdOptDesc;

static const CmdOptDesc cmdopt_defs[] =  {
    { "-output <file>",
      "write output to the specified <file>",
      "output-file: <file>", CmdOptFileManip, "-o <file>" },
    { "-config <file>",
      "set configuration options from the specified <file>",
      NULL, CmdOptFileManip },
    { "-file <file>",
      "write errors and warnings to the specified <file>",
      "error-file: <file>", CmdOptFileManip, "-f <file>" },
    { "-modify",
      "modify the original input files",
      "write-back: yes", CmdOptFileManip, "-m" },
    { "-indent",
      "indent element content",
      "indent: auto", CmdOptProcDir, "-i" },
    { "-wrap <column>",
      "wrap text at the specified <column>"
      ". 0 is assumed if <column> is missing. "
      "When this option is omitted, the default of the configuration option "
      "\"wrap\" applies.",
      "wrap: <column>", CmdOptProcDir, "-w <column>" },
    { "-upper",
      "force tags to upper case",
      "uppercase-tags: yes", CmdOptProcDir, "-u" },
    { "-clean",
      "replace FONT, NOBR and CENTER tags by CSS",
      "clean: yes", CmdOptProcDir, "-c" },
    { "-bare",
      "strip out smart quotes and em dashes, etc.",
      "bare: yes", CmdOptProcDir, "-b" },
    { "-numeric",
      "output numeric rather than named entities",
      "numeric-entities: yes", CmdOptProcDir, "-n" },
    { "-errors",
      "show only errors and warnings",
      "markup: no", CmdOptProcDir, "-e" },
    { "-quiet",
      "suppress nonessential output",
      "quiet: yes", CmdOptProcDir, "-q" },
    { "-omit",
      "omit optional end tags",
      "hide-endtags: yes", CmdOptProcDir },
    { "-xml",
      "specify the input is well formed XML",
      "input-xml: yes", CmdOptProcDir },
    { "-asxml",
      "convert HTML to well formed XHTML",
      "output-xhtml: yes", CmdOptProcDir, "-asxhtml" },
    { "-ashtml",
      "force XHTML to well formed HTML",
      "output-html: yes", CmdOptProcDir },
#if SUPPORT_ACCESSIBILITY_CHECKS
    { "-access <level>",
      "do additional accessibility checks (<level> = 0, 1, 2, 3)"
      ". 0 is assumed if <level> is missing.",
      "accessibility-check: <level>", CmdOptProcDir },
#endif
    { "-raw",
      "output values above 127 without conversion to entities",
      NULL, CmdOptCharEnc },
    { "-ascii",
      "use ISO-8859-1 for input, US-ASCII for output",
      NULL, CmdOptCharEnc },
    { "-latin0",
      "use ISO-8859-15 for input, US-ASCII for output",
      NULL, CmdOptCharEnc },
    { "-latin1",
      "use ISO-8859-1 for both input and output",
      NULL, CmdOptCharEnc },
#ifndef NO_NATIVE_ISO2022_SUPPORT
    { "-iso2022",
      "use ISO-2022 for both input and output",
      NULL, CmdOptCharEnc },
#endif
    { "-utf8",
      "use UTF-8 for both input and output",
      NULL, CmdOptCharEnc },
    { "-mac",
      "use MacRoman for input, US-ASCII for output",
      NULL, CmdOptCharEnc },
    { "-win1252",
      "use Windows-1252 for input, US-ASCII for output",
      NULL, CmdOptCharEnc },
    { "-ibm858",
      "use IBM-858 (CP850+Euro) for input, US-ASCII for output",
      NULL, CmdOptCharEnc },
#if SUPPORT_UTF16_ENCODINGS
    { "-utf16le",
      "use UTF-16LE for both input and output",
      NULL, CmdOptCharEnc },
    { "-utf16be",
      "use UTF-16BE for both input and output",
      NULL, CmdOptCharEnc },
    { "-utf16",
      "use UTF-16 for both input and output",
      NULL, CmdOptCharEnc },
#endif
#if SUPPORT_ASIAN_ENCODINGS /* #431953 - RJ */
    { "-big5",
      "use Big5 for both input and output",
      NULL, CmdOptCharEnc },
    { "-shiftjis",
      "use Shift_JIS for both input and output",
      NULL, CmdOptCharEnc },
    { "-language <lang>",
      "set the two-letter language code <lang> (for future use)",
      "language: <lang>", CmdOptCharEnc },
#endif
    { "-version",
      "show the version of Tidy",
      NULL, CmdOptMisc, "-v" },
    { "-help",
      "list the command line options",
      NULL, CmdOptMisc, "-h", "-?" },
    { "-xml-help",
      "list the command line options in XML format",
      NULL, CmdOptMisc },
    { "-help-config",
      "list all configuration options",
      NULL, CmdOptMisc },
    { "-xml-config",
      "list all configuration options in XML format",
      NULL, CmdOptMisc },
    { "-show-config",
      "list the current configuration settings",
      NULL, CmdOptMisc },
    { NULL, NULL, NULL, CmdOptMisc }
};

static tmbstr get_option_names( const CmdOptDesc* pos )
{
    tmbstr name;
    uint len = strlen(pos->name1);
    if (pos->name2)
        len += 2+strlen(pos->name2);
    if (pos->name3)
        len += 2+strlen(pos->name3);

    name = (tmbstr)malloc(len+1);
    if (!name) outOfMemory();
    strcpy(name, pos->name1);
    if (pos->name2)
    {
        strcat(name, ", ");
        strcat(name, pos->name2);
    }
    if (pos->name3)
    {
        strcat(name, ", ");
        strcat(name, pos->name3);
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
        size_t len =  strlen(cmdopt_catname[cat].name);
        printf("%s\n", cmdopt_catname[cat].name );
        printf("%*.*s\n", (int)len, (int)len, helpul );
        for( pos=cmdopt_defs; pos->name1; ++pos)
        {
            tmbstr name;
            if (pos->cat != cat)
                continue;
            name = get_option_names( pos );
            print2Columns( helpfmt, 19, 58, name, pos->desc );
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
        print_xml_help_option_element("description", pos->desc);
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
            "<cmdline version=\"%s\">\n", tidyReleaseDate());
    print_xml_help_option();
    printf( "</cmdline>\n" );
}

static void help( ctmbstr prog )
{
    printf( "%s [option...] [file...] [option...] [file...]\n", prog );
    printf( "Utility to clean up and pretty print HTML/XHTML/XML\n");
    printf( "\n");

    printf( "This is an HTML5-aware experimental fork of HTML Tidy.\n");
    printf( "%s\n", tidyReleaseDate() );
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
    printf( "For more information on this HTML5-aware experimental fork of Tidy,\n" );
    printf( "see http://w3c.github.com/tidy-html5/\n" );
    printf( "\n");
    printf( "For more information on HTML, see the following:\n" );
    printf( "\n");
    printf( "  HTML: Edition for Web Authors (the latest HTML specification)\n");
    printf( "  http://dev.w3.org/html5/spec-author-view\n" );
    printf( "\n");
    printf( "  HTML: The Markup Language (an HTML language reference)\n" );
    printf( "  http://dev.w3.org/html5/markup/\n" );
    printf( "\n");
    printf( "File bug reports at https://github.com/w3c/tidy-html5/issues/\n" );
    printf( "or send questions and comments to html-tidy@w3.org\n" );
    printf( "\n");
    printf( "Validate your HTML documents using the W3C Nu Markup Validator:\n" );
    printf( "\n");
    printf( "  http://validator.w3.org/nu/" );
    printf( "\n");
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
            "<config version=\"%s\">\n", tidyReleaseDate());
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
    printf( "HTML Tidy for HTML5 (experimental) for %s %s\n",
             PLATFORM_NAME, tidyReleaseDate() );
#else
    printf( "HTML Tidy for HTML5 (experimental) %s\n", tidyReleaseDate() );
#endif
}

static void unknownOption( uint c )
{
    fprintf( errout, "HTML Tidy: unknown option: %c\n", (char)c );
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
    status = 0;
    
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
                tidyOptSetBool( tdoc, TidyHideEndTags, yes );

            else if ( strcasecmp(arg, "upper") == 0 )
                tidyOptSetBool( tdoc, TidyUpperCaseTags, yes );

            else if ( strcasecmp(arg, "clean") == 0 )
                tidyOptSetBool( tdoc, TidyMakeClean, yes );

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

        if ( status >= 0 )
            status = tidyRunDiagnostics( tdoc );

        if ( status > 1 ) /* If errors, do we want to force output? */
            status = ( tidyOptGetBool(tdoc, TidyForceOutput) ? status : -1 );

        if ( status >= 0 && tidyOptGetBool(tdoc, TidyShowMarkup) )
        {
            if ( tidyOptGetBool(tdoc, TidyWriteBack) && argc > 1 )
                status = tidySaveFile( tdoc, htmlfil );
            else
            {
                ctmbstr outfil = tidyOptGetValue( tdoc, TidyOutFile );
                if ( outfil )
                    status = tidySaveFile( tdoc, outfil );
                else
                    status = tidySaveStdout( tdoc );
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
