// Todo: rp_readline - and use it for rp_loadtxt

#include <stdio.h>
#include "redpill.h"
#include "io.h"



void rp_printstrings(char **strings, char *sep, FILE *stream)
{
    if (!strings || !stream)
    {
        WARNING("Invalid output stream or null char **");
    	return;
    }

    register unsigned int i;
    register char **str    = strings;
    register FILE *fstream = stream;

    for (i = 0; str[i]; i++)
    {
        if ( fputs(str[i], fstream) == EOF ) 
            WARNING("failed to print string to given stream via fputs()");
        if (sep)
            if ( fputs(sep, fstream) == EOF )
                WARNING("failed to print separator string to given stream via fputs()");
    }
}




char **rp_loadtxt(const char *filename)
{
    char **ret = 0;
    int currline, currbyte, charcapacity, linecapacity, inputbyte;

    FILE *input = rp_fopen(filename, "r", 0, 0);

    linecapacity = LINE_COUNT_START;
    ret          = rp_malloc(linecapacity * sizeof (char *), 0, 0);

    currline = 0;

    while (!feof(input))
    {
        if (currline >= linecapacity)
        {
            linecapacity *= 2;
            ret           = rp_realloc(ret, linecapacity * sizeof (char *), 0, 0);
        }

        charcapacity  = LINE_SIZE;
        ret[currline] = rp_malloc(charcapacity, 0, 0);
        currbyte      = 0;

        for (inputbyte = fgetc(input); inputbyte != EOF && inputbyte != '\n'; inputbyte = fgetc(input))
        {
            if (currbyte >= charcapacity)
            {
                charcapacity  *= 2;
                ret[currline]  = rp_realloc(ret[currline], charcapacity * sizeof (char *), 0, 0);
            }

            ret[currline][currbyte++] = (char) inputbyte;
        }

        ret[currline][currbyte]	= 0;
        ret[currline] 		= rp_realloc(ret[currline], currbyte + 1, 0, 0);

        currline++;
    }

    ret           = rp_realloc(ret, (currline + 2) * sizeof (char *), 0, 0);
    ret[currline] = 0;

    fclose(input);
    return ret;
}




char *rp_readtext(FILE *fstream)
{
    int inputbyte;
    size_t bytecapacity;
    char *ret         = 0;
    unsigned currbyte = 0;


    bytecapacity = LINE_SIZE;
    ret          = rp_malloc(bytecapacity, 0, 0);

    for
    (
        inputbyte = fgetc(fstream);
        inputbyte != ( (fstream == stdin) ? '\n' : EOF );
        inputbyte = fgetc(fstream)
    )
    {
        if (fstream == stdin && inputbyte == EOF)
            ERROR("fgetc() returned EOF.");
        if (currbyte >= bytecapacity)
        {
            bytecapacity *= 2;
            ret	          = rp_realloc(ret, bytecapacity, 0, 0);
        }

        ret[currbyte++] = inputbyte;
    }
 
    // lets return an empty string... yay.
    if (currbyte == 0) ret = rp_malloc(1, 0, 0);

    ret[currbyte] = 0;
    return ret;
}


FILE *rp_fopen(const char *filename, const char * mode, void (*errorhandler)(void *), void *errorstruct)
{
    FILE *ret;

    ret = fopen(filename, mode);
    if (!ret)
    {
        if (errorhandler)
            errorhandler(errorstruct);
        else
            ERROR("Failed to open given filename.");
    }

    return ret;
}




long rp_filesize(const char *fname)
{
    FILE *fhandle = fopen(fname, "r");

    if (!fhandle) 
        return -1L;

    fseek(fhandle, 0L, SEEK_END);
    long size = ftell(fhandle);

    fclose(fhandle);

    return size;
}


