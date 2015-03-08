

#include <tidy.h>;
#include <buffio.h>;
#include <stdio.h>;
#include <errno.h>;

int main(int argc, char **argv )
{
    const char* input = "<title>Hello</title><p>World!";
    TidyBuffer output = {0};
    TidyBuffer errbuf = {0};
    int rc = -1;
    Bool ok;

    // Initialize "document"
    TidyDoc tdoc = tidyCreate();
    printf( "Tidying:\t%s\n", input );

    // Convert to XHTML
    ok = tidyOptSetBool( tdoc, TidyXhtmlOut, yes );  
    if ( ok )
        rc = tidySetErrorBuffer( tdoc, &errbuf );    // Capture diagnostics
    if ( rc >= 0 )
        rc = tidyParseString( tdoc, input );         // Parse the input
    if ( rc >= 0 )
        rc = tidyCleanAndRepair( tdoc );             // Tidy it up!
    if ( rc >= 0 )
        rc = tidyRunDiagnostics( tdoc );             // Kvetch
    if ( rc > 1 )                                    // If error, force output.
        rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1 );
    if ( rc >= 0 )
        rc = tidySaveBuffer( tdoc, &output );        // Pretty Print

    if ( rc >= 0 )
    {
    if ( rc > 0 )
        printf( "\nDiagnostics:\n\n%s", errbuf.bp );
    printf( "\nAnd here is the result:\n\n%s", output.bp );
    }
    else
        printf( "A severe error (%d) occurred.\n", rc );

    tidyBufFree( &output );
    tidyBufFree( &errbuf );
    tidyRelease( tdoc );
    return rc;
}

