#include "redpill.h"
#include <time.h>


static int seed;	// automatically initialized to 0 - defines whether srand() was called










int rp_randomint(int min, int max)
{
    if (!seed)
    {
        seed = 1;
        srand( (unsigned) time(0) );
    }

    if (min > max) 
    ERROR("Invalid closed interval for random int generator.");

    // The formula below was taken directly from
    // http://c-faq.com/lib/randrange.html
    return (min + rand() / (RAND_MAX / (max - min + 1) + 1));
}



void rp_swap(void *a, void *b, size_t size)
{
    register char swapByte;

    char *one 	= a, 
    *other 	= b;

    while (size--)
    {
       swapByte	= *one;
       *one++	= *other;
       *other++	= swapByte;
    }
}
