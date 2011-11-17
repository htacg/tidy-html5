#include "tmbstr.h"

#include "httpio.h"

int
makeConnection ( HTTPInputSource *pHttp )
{
    struct sockaddr_in sock;
    struct hostent *pHost;

    /* Get internet address of the host. */
    if (!(pHost = gethostbyname ( pHttp->pHostName )))
    {
        return -1;
    }
    /* Copy the address of the host to socket description.  */
    memcpy (&sock.sin_addr, pHost->h_addr, pHost->h_length);

    /* Set port and protocol */
    sock.sin_family = AF_INET;
    sock.sin_port = htons( pHttp->nPort );

    /* Make an internet socket, stream type.  */
    if ((pHttp->s = socket (AF_INET, SOCK_STREAM, 0)) == -1)
        return -1;

    /* Connect the socket to the remote host.  */
    if (connect (pHttp->s, (struct sockaddr *) &sock, sizeof( sock )))
    {
        if (errno == ECONNREFUSED)
            return ECONNREFUSED;
        else
            return -1;
    }
    return 0;
}


int parseURL( HTTPInputSource *pHttp, tmbstr url )
{
  int i, j = 0;
  ctmbstr pStr;

    pStr = tmbsubstr( url, "://" );

    /* If protocol is there, but not http, bail out, else assume http.  */
    if (NULL != pStr)
    {
        if (tmbstrncasecmp( url, "http://", 7 ))
            return -1;
    }

    if (NULL != pStr)
        j = pStr - url + 3;
    for (i = j; url[i] && url[i] != ':' && url[i] != '/'; i++) {}
    if (i == j)
        return -1;

    /* Get the hostname.  */
    pHttp->pHostName = tmbstrndup (&url[j], i - j );

    if (url[i] == ':')
    {
        /* We have a colon delimiting the hostname.  It should mean that
        a port number is following it */
        pHttp->nPort = 0;
        if (isdigit( url[++i] ))    /* A port number */
        {
            for (; url[i] && url[i] != '/'; i++)
            {
                if (isdigit( url[i] ))
                    pHttp->nPort = 10 * pHttp->nPort + (url[i] - '0');
                else
                    return -1;
            }
            if (!pHttp->nPort)
                return -1;
        }
        else                      /* or just a misformed port number */
            return -1;
    }
    else
        /* Assume default port.  */
        pHttp->nPort = 80;

    /* skip past the delimiting slash (we'll add it later )  */
    while (url[i] && url[i] == '/')
        i++;
    pHttp->pResource = tmbstrdup (url + i );
    return 0;
}


int fillBuffer( HTTPInputSource *in )
{
    if (0 < in->s)
    {
        in->nBufSize = recv( in->s, in->buffer, sizeof( in->buffer ), 0);
        in->nextBytePos = 0;
        if (in->nBufSize < sizeof( in->buffer ))
            in->buffer[in->nBufSize] = '\0';
    }
    else
        in->nBufSize = 0;
    return in->nBufSize;
}


int openURL( HTTPInputSource *in, tmbstr pUrl )
{
    int rc = -1;
#ifdef WIN32    
    WSADATA wsaData;

    rc = WSAStartup( 514, &wsaData );
#endif

    in->tis.getByte = (TidyGetByteFunc) HTTPGetByte; 
    in->tis.ungetByte = (TidyUngetByteFunc) HTTPUngetByte;
    in->tis.eof = (TidyEOFFunc) HTTPIsEOF;
    in->tis.sourceData = (uint) in;
    in->nextBytePos = in->nextUnGotBytePos = in->nBufSize = 0;
    parseURL( in, pUrl );
    if (0 == (rc = makeConnection( in )))
    {
        char ch, lastCh = '\0';
        int blanks = 0;

        char *getCmd = MemAlloc( 48 + strlen( in->pResource ));
        sprintf( getCmd, "GET /%s HTTP/1.0\r\nAccept: text/html\r\n\r\n", in->pResource );
        send( in->s, getCmd, strlen( getCmd ), 0 );
        MemFree( getCmd );

        /*  skip past the header information  */
        while (   in->nextBytePos >= in->nBufSize
               && 0 < (rc = fillBuffer( in )))
        {
            if (1 < blanks)
                break;
            for (; in->nextBytePos < sizeof( in->buffer ) 
                   && 0 != in->buffer[ in->nextBytePos ]; 
                 in->nextBytePos++ )
            {
                ch = in->buffer[ in->nextBytePos ];
                if (ch == '\r' || ch == '\n')
                {
                    if (ch == lastCh)
                    {
                        /*  Two carriage returns or two newlines in a row,
                            that's good enough */
                        blanks++;
                    }
                    if (lastCh == '\r' || lastCh == '\n')
                    {
                        blanks++;
                    }
                }
                else
                    blanks = 0;
                lastCh = ch;
                if (1 < blanks)
                {
                    /* end of header, scan to first non-white and return */
                    while ('\0' != ch && isspace( ch ))
                        ch = in->buffer[ ++in->nextBytePos ];
                    break;
                }
            }
        }
    }
    return rc;
}


void closeURL( HTTPInputSource *source )
{
    if (0 < source->s)
        closesocket( source->s );
    source->s = -1;
    source->tis.sourceData = 0;
#ifdef WIN32
    WSACleanup();
#endif
}


int HTTPGetByte( HTTPInputSource *source )
{
    if (source->nextUnGotBytePos)
        return source->unGetBuffer[ --source->nextUnGotBytePos ];
    if (0 != source->nBufSize && source->nextBytePos >= source->nBufSize)
    {
        fillBuffer( source );
    }
    if (0 == source->nBufSize)
        return EndOfStream;
    return source->buffer[ source->nextBytePos++ ];
}

void HTTPUngetByte( HTTPInputSource *source, uint byteValue )
{
    if (source->nextUnGotBytePos < 16 )  /* Only you can prevent buffer overflows */
        source->unGetBuffer[ source->nextUnGotBytePos++ ] = (char) byteValue;
}

Bool HTTPIsEOF( HTTPInputSource *source )
{
    if (source->nextUnGotBytePos)
        /* pending ungot bytes, not done */
        return no;

    if (   0 != source->nBufSize 
        && source->nextBytePos >= source->nBufSize)
        /* We've consumed the existing buffer, get another */
        fillBuffer( source );

    if (source->nextBytePos < source->nBufSize)
        /*  we have stuff in the buffer, must not be done. */
        return no;

    /* Nothing in the buffer, and the last receive failed, must be done.  */
    return yes;
}

