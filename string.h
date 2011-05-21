#ifndef RP_STRING_H
#define RP_STRING_H


#include "redpill.h"


int rp_strfindequal(char *, char **);
int rp_strcopy(char *, char *, unsigned int);
char **rp_tokenize(char *, char *);
char *rp_strreverse(const char *);
char *rp_strdup(char *);


#endif

