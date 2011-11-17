#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "platform.h"

#define true       1
#define false      0
#define TABSIZE    4

#define DOS_CRLF   0
#define UNIX_LF    1
#define MAC_CR     2

typedef struct
{
    Bool pushed;
    int tabs;
    int curcol;
    int lastcol;
    int maxcol;
    int curline;
    int pushed_char;
    uint size;
    uint length;
    char *buf;
    FILE *fp;
} Stream;

static int tabsize = TABSIZE;
static int endline = DOS_CRLF;
static Bool tabs = false;

/*
 Memory allocation functions vary from one environment to
 the next, and experience shows that wrapping the local
 mechanisms up provides for greater flexibility and allows
 out of memory conditions to be detected in one place.
*/
void *MemAlloc(size_t size)
{
    void *p;

    p = malloc(size);

    if (!p)
    {
        fprintf(stderr, "***** Out of memory! *****\n");
        exit(1);
    }

    return p;
}

void *MemRealloc(void *old, size_t size)
{
    void *p;

    p = realloc(old, size);

    if (!p)
    {
        fprintf(stderr, "***** Out of memory! *****\n");
        return NULL;
    }

    return p;
}

void MemFree(void *p)
{
    free(p);
    p = NULL;
}

static Stream *NewStream(FILE *fp)
{
    Stream *in;

    in = (Stream *)MemAlloc(sizeof(Stream));

    memset(in, 0, sizeof(Stream));
    in->fp = fp;
    return in;
}

static void FreeStream(Stream *in)
{
    if (in->buf)
        MemFree(in->buf);

    MemFree(in);
}

static void AddByte(Stream *in, uint c)
{
    if (in->size + 1 >= in->length)
    {
        while (in->size + 1 >= in->length)
        {
            if (in->length == 0)
                in->length = 8192;
            else
                in->length = in->length * 2;
        }

        in->buf = (char *)MemRealloc(in->buf, in->length*sizeof(char));
    }

    in->buf[in->size++] = (char)c;
    in->buf[in->size] = '\0';  /* debug */
}



/*
  Read a character from a stream, keeping track
  of lines, columns etc. This is used for parsing
  markup and plain text etc. A single level
  pushback is allowed with UngetChar(c, in).
  Returns EndOfStream if there's nothing more to read.
*/
static int ReadChar(Stream *in)
{
    int c;

    if (in->pushed)
    {
        in->pushed = false;

        if (in->pushed_char == '\n')
            in->curline--;

        return in->pushed_char;
    }

    in->lastcol = in->curcol;

    /* expanding tab ? */
    if (in->tabs > 0)
    {
        in->curcol++;
        in->tabs--;
        return ' ';
    }
    
    /* Else go on with normal buffer: */
    for (;;)
    {
        c = getc(in->fp);

        /* end of file? */
        if (c == EOF)
            break;

        /* coerce \r\n  and isolated \r as equivalent to \n : */
        if (c == '\r')
        {
            c = getc(in->fp);

            if (c != '\n')
                ungetc(c, in->fp);

            c = '\n';
        }

        if (c == '\n')
        {
            if (in->maxcol < in->curcol)
                in->maxcol = in->curcol;

            in->curcol = 1;
            in->curline++;
            break;
        }

        if (c == '\t')
        {
            if (tabs)
              in->curcol += tabsize - ((in->curcol - 1) % tabsize);
            else /* expand to spaces */
            {
                in->tabs = tabsize - ((in->curcol - 1) % tabsize) - 1;
                in->curcol++;
                c = ' ';
            }

            break;
        }

        if (c == '\033')
            break;

        /* strip control characters including '\r' */

        if (0 < c && c < 32)
            continue;

        in->curcol++;
        break;
    }

    return c;
}

static Stream *ReadFile(FILE *fin)
{
    int c;
    Stream *in  = NewStream(fin);

    while ((c = ReadChar(in)) >= 0)
        AddByte(in, (uint)c);

    return in;
}

static void WriteFile(Stream *in, FILE *fout)
{
    int i, c;
    char *p;

    i = in->size;
    p = in->buf;

    while (i--)
    {
        c = *p++;

        if (c == '\n')
        {
            if (endline == DOS_CRLF)
            {
                putc('\r', fout);
                putc('\n', fout);
            }
            else if (endline == UNIX_LF)
                putc('\n', fout);
            else if (endline == MAC_CR)
                putc('\r', fout);

            continue;
        }

        putc(c, fout);
    }
}

static void HelpText(FILE *errout, char *prog)
{
    fprintf(errout, "%s: [options] [infile [outfile]] ...\n", prog);
    fprintf(errout, "Utility to expand tabs and ensure consistent line endings\n");
    fprintf(errout, "options for tab2space vers: 6th February 2003\n");
    fprintf(errout, "  -help or -h     display this help message\n");
    fprintf(errout, "  -dos  or -crlf  set line ends to CRLF (PC-DOS/Windows - default)\n");
    fprintf(errout, "  -mac  or -cr    set line ends to CR (classic Mac OS)\n");
    fprintf(errout, "  -unix or -lf    set line ends to LF (Unix)\n");
    fprintf(errout, "  -tabs           preserve tabs, e.g. for Makefile\n");
    fprintf(errout, "  -t<n>           set tabs to <n> (default is 4) spaces\n");
    fprintf(errout, "\nNote this utility doesn't map spaces to tabs!\n");
}

int main(int argc, char **argv)
{
    char const *infile, *outfile;
    char *prog;
    FILE *fin, *fout;
    Stream *in = NULL;

    prog = argv[0];

    while (argc > 0)
    {
        if (argc > 1 && argv[1][0] == '-')
        {
            if (strcmp(argv[1], "-help") == 0 || argv[1][1] == 'h')
            {
                HelpText(stdout, prog);
                return 1;
            }

            if (strcmp(argv[1], "-dos") == 0 ||
                strcmp(argv[1], "-crlf") == 0)
                 endline = DOS_CRLF;

            else if (strcmp(argv[1], "-mac") == 0 ||
                strcmp(argv[1], "-cr") == 0)
                endline = MAC_CR;

            else if (strcmp(argv[1], "-unix") == 0 ||
                strcmp(argv[1], "-lf") == 0)
                endline = UNIX_LF;

            else if (strcmp(argv[1], "-tabs") == 0)
                tabs = true;

            else if (strncmp(argv[1], "-t", 2) == 0)
                sscanf(argv[1]+2, "%d", &tabsize);

            --argc;
            ++argv;
            continue;
        }

        if (argc > 1)
        {
            infile = argv[1];
            fin = fopen(infile, "rb");
        }
        else
        {
            infile = "stdin";
            fin = stdin;
        }

        if (argc > 2)
        {
            outfile = argv[2];
            fout = NULL;
            --argc;
            ++argv;
        }
        else
        {
            outfile = "stdout";
            fout = stdout;
        }

        if (fin)
        {
            in = ReadFile(fin);

            if (fin != stdin)
                fclose(fin);
            
            if (fout != stdout)
               fout = fopen(outfile, "wb");
            
            if (fout)
            {
               WriteFile(in, fout);
                
               if (fout != stdout)
                  fclose(fout);
            }
            else
                fprintf(stderr, "%s - can't open \"%s\" for writing\n", prog, outfile);

            FreeStream(in);
        }
        else
            fprintf(stderr, "%s - can't open \"%s\" for reading\n", prog, infile);

        --argc;
        ++argv;
        
        if (argc <= 1)
            break;
    }

    return 0;
}

