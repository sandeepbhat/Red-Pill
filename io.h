#ifndef RP_IO_H
#define RP_IO_H

void rp_printstrings(char **, char *, FILE *);
char *rp_readline(FILE *);
char **rp_loadtxt(const char *);
char *rp_readtext(FILE *);
FILE *rp_fopen(const char *, const char *, void (*)(void *), void *);
long rp_filesize(const char *);

#endif
