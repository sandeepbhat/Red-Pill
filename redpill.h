#ifndef REDPILL_H
#define REDPILL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory.h"


#define LINE_SIZE		128
#define LINE_COUNT_START	128
#define MEMORY_HASH_SIZE	256



#define ERROR(message) do { fprintf(stderr, "\n\n Redpill Error - %s: %s (%s, line %d)\n\n", __func__, message, __FILE__, __LINE__); exit(EXIT_FAILURE); } while (0)
#define WARNING(message) fprintf(stderr, "\n\n Redpill Warning - %s: %s (%s, line %d) *****\n\n", __func__, message, __FILE__, __LINE__)


void	rp_swap(void *, void *, size_t);
int	rp_randomint(int min, int max);


#endif
