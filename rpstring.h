#ifndef RP_STRING_H
#define RP_STRING_H


#include "redpill.h"


int rp_strfindequal(char *, char *[]);
int rp_strcopy(char *, char *, unsigned int);
char *rp_strreverse(char *);
char *rp_strdup(char *);
char *rp_join(char *[], char *);
char **rp_split(char *, char *);

#endif

