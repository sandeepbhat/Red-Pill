#include "rpstring.h"




char *rp_join(char *strs[], char *glue)
{

    if (!*strs)
	return NULL;

    char *result = NULL;
    
    int gluelen = strlen(glue), 
	lenres  = 0, 
	offset  = 0, 
	i;

    for (i = 0; strs[i]; i++)
    {
	int newstrlen = strlen(strs[i]);

	lenres += newstrlen + gluelen + 1;
	result  = rp_realloc(result, lenres, NULL, NULL);

	strcpy(result + offset, strs[i]);

	offset += newstrlen;
	strcpy(result + offset, glue);

	offset += gluelen;
    }

    result = rp_realloc(result, lenres - gluelen, NULL, NULL);
    result[ offset - gluelen ] = '\0';

    return result;
}




int rp_strfindequal(char *target, char *base[])
{
    if (!target || !base)
        return -1;

    register int index;

    for (index = 0; base[index]; index++)
        if (strcmp(target, base[index]) == 0)
            return index;

    return -1;
}




int rp_strcopy(char *dest, char *src, unsigned int mbytes)
{
 
    unsigned int count;

    if (!src || !dest)
        return 0;

    for (count = 0; count < mbytes && src[count]; count++)
        dest[count] = src[count];

    dest[count] = '\0';

    return count;
}




char **rp_split(char *target, char *separators)
{
    // worst-case scenario in terms os memory amount
    int addresses = strlen(target) / 2,
	i         = 0;

    char *current = strtok(target, separators), 
 	**ret 	  = rp_malloc(addresses * sizeof (char *), NULL, NULL);	
	
    while (current)
    {
        ret[i]  = current;
	current = strtok(NULL, separators);
	i      += 1;
    }

    ret[i] = NULL;
		
    ret = rp_realloc(ret, (i + 1) * sizeof (char *), NULL, NULL);
    return ret;
}




char *rp_strreverse(char *target)
{
    if (!target)
	return NULL;

    int length = strlen(target), 
	i      = 0,
	j      = length;

    char *ret = rp_malloc(length + 1, NULL, NULL);
    
    ret[length] = '\0';

    for (j--; j >= length / 2; i++, j--) 
    {
        ret[i] = target[j];
        ret[j] = target[i];
    }

    return ret;
}




char *rp_strdup(char *str)
{
	if (!str)
	    return NULL;

	char *ret = rp_malloc(strlen(str) + 1 , NULL, NULL);

	strcpy(ret, str);
	return ret;
}
