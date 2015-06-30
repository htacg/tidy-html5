/*\ 
 *  20150206 - Test app for Issue #71
 *
 *  A simple API example of getting the body text, first as html,
 *  and then as a raw stream.
 *
 *  Note: This simple test app has no error checking
 *
\*/

#include <stdio.h>
#include "tidybuffio.h"
#include "tidy.h"

static const char *sample =
    "<!DOCTYPE html>\n"
    "<head>\n"
    "<meta charset=utf-8>\n"
    "<title>Test app for Issue #71</title>\n"
    "<body>something &amp; escaped</body>\n"
    "</html>";

int main() {
    printf("\nSimple example of HTML Tidy API use.\n");
    TidyDoc tdoc = tidyCreate();
    TidyBuffer buff;
    tidyBufInit(&buff);
    tidyBufAppend(&buff, (void *)sample, strlen(sample));
    tidyParseBuffer(tdoc, &buff);
    TidyNode body = tidyGetBody(tdoc);
    TidyNode text_node = tidyGetChild(body);
    TidyBuffer buff2;
    tidyBufInit(&buff2);
    printf("This is the 'escaped' text, from tidyNodeGetText(...), suitable for html use...\n");
    tidyNodeGetText(tdoc, text_node, &buff2);
    fwrite(buff2.bp, buff2.size, 1, stdout);
    printf("This is the 'raw' lexer values, from tidyNodeGetValue(...).\n");
    tidyNodeGetValue(tdoc, text_node, &buff2);
    fwrite(buff2.bp, buff2.size, 1, stdout);
    printf("\n");
    return 0;
}

// eof
