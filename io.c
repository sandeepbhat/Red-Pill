#include <stdio.h>
#include "redpill.h"
#include "rpstring.h"
#include "io.h"


// Given a pointer into the first string of an array of strings,
// prints them to the given file stream, separating each string by
// the string in sep.

void rp_printstrings(char **strings, char *sep, FILE *stream)
{
    if (!strings || !stream)
    {
        WARNING("Invalid output stream or null char **");
    	return;
    }

    unsigned int i;

    for (i = 0; strings[i]; i++)
    {
        if ( fputs(strings[i], stream) == EOF ) 
            WARNING("failed to print string to given stream via fputs()");
        if (sep)
            if ( fputs(sep, stream) == EOF )
                WARNING("failed to print separator string to given stream via fputs()");
    }
}


// Similar to fgets, but returns the starting address of a buffer that grows dynamically
// to accomodate all the input until a newline is found.

char *rp_readline(FILE *fstream)
{

    unsigned int currbyte = 0;

    size_t bytecapacity = LINE_SIZE;

    char *ret = rp_malloc(bytecapacity, NULL, NULL);

    int inputbyte;

    for
    (
        inputbyte = fgetc(fstream);
        inputbyte != '\n' && inputbyte != EOF;
        inputbyte = fgetc(fstream)
    )
    {
        if (fstream == stdin && inputbyte == EOF)
            ERROR("fgetc() returned EOF.");

        if (currbyte >= bytecapacity)
        {
            bytecapacity *= 2;
            ret	          = rp_realloc(ret, bytecapacity, NULL, NULL);
        }

        ret[currbyte++] = inputbyte;
    }

    if (inputbyte == EOF)
	    return NULL;

    // lets return an empty string... yay.
    if (currbyte == 0) ret = rp_malloc(1, NULL, NULL);

    ret[currbyte] = '\0';
    return ret;
}



// Loads the entire content of a given text file, specified by
// its relative path. Returns the pointer to the start of the
// first string of the array of strings, each array representing
// one line of the input file.

char **rp_loadtxt(const char *filename)
{
    FILE *input = rp_fopen(filename, "r", NULL, NULL);

    int linecapacity = LINE_COUNT_START,
	currline     = 0;

    char **ret = rp_malloc(linecapacity * sizeof (char *), NULL, NULL);

    while (!feof(input))
    {
        if (currline >= linecapacity)
        {
            linecapacity *= 2;
            ret           = rp_realloc(ret, linecapacity * sizeof (char *), NULL, NULL);
        }

	ret[currline] = rp_readline(input);
        currline++;
    }

    ret           = rp_realloc(ret, (currline + 2) * sizeof (char *), NULL, NULL);
    ret[currline] = NULL;

    fclose(input);
    return ret;
}




// Reads all the content from a text file, but returns
// them in a single string, pointed to by its return value

char *rp_slurp(const char *filename)
{
    return rp_join(rp_loadtxt(filename), "\n");
}




FILE *rp_fopen(const char *filename, const char * mode, void (*errorhandler)(void *), void *errorstruct)
{
    FILE *ret = fopen(filename, mode);

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


