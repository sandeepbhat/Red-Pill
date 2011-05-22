#include "string.h"


int rp_strfindequal(char *target, char **base)
{
    register char *str = target, **strbase = base;

    if (!str || !strbase)
        return -1;

    register int index;

    for (index = 0; strbase[index]; index++)
        if ( strcmp(str, strbase[index] ) == 0)
            return index;

    return -1;
}




int rp_strcopy(char *dest, char *src, unsigned int mbytes)
{
    register char *destination	= dest, 
                    *source	= src;

    register unsigned int maxbytes = mbytes,
                            count;

    if (!source)
        return 0;

    for (count = 0; count < maxbytes - 1 && source[count]; count++)
        destination[count] = source[count];

    destination[count] = '\0';

    return count;
}




char **rp_tokenize(char *target, char *separators)
{
    // worst-case scenario, so we don't have to check on every entry whether we have space
    register int addresses 	= strlen(target) / 2;

    register int i 		= 0;

    register char *current	= NULL, 
                *str 	= target, 
                *seps 	= separators,
                **ret 	= rp_malloc(addresses * sizeof (char *), NULL, NULL);	
	
    // we're always splitting on the same separators
    for (current = strtok(str, seps); current; current = strtok(NULL, seps), i++)
        ret[i] = current;

    // sinalize the end of the tokens
    ret[i] = NULL;
		
    // shrink to optimize memory usage
    ret = rp_realloc(ret, (i + 1) * sizeof (char *), NULL, NULL);

    return ret;
}



char *rp_strreverse(const char *target)
{
    register int i = 0,
    length         = strlen(target), 
    j              = length;

    register char *ret       = rp_malloc(length + 1, NULL, NULL);
    register const char *str = target;

    ret[length] = '\0';

    for (j--; j >= length / 2; i++, j--) 
    {
        ret[i] = str[j];
        ret[j] = str[i];
    }

    return ret;
}




char *rp_strdup(char *str)
{
	if (!str)
	    return NULL;

	char *ret = rp_malloc( strlen(str) + 1 , NULL, NULL);
	strcpy(ret, str);

	return ret;
}
