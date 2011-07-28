#include <stdlib.h>
#include <stdint.h>
#include "memory.h"
#include "redpill.h"

static void 	startmem(void);
static int 	addref(void *);
static void 	*getref(void *);
static int 	deleteref(void *);
static void 	updateref(void *, void *);
static void 	clearmem(void);
static unsigned	int hash(void *);



static hashtable *memoryhash;


// API //


void *rp_malloc(size_t bytes, void (*errorhandler)(void *), void *handlerargstruct)
{
    void *ptr = malloc(bytes);

    if (!ptr) 
    {
        if (!errorhandler)
            ERROR(OUT_OF_MEMORY);
        else
            errorhandler(handlerargstruct);
    }

    if (!memoryhash)
        startmem();

    addref(ptr);
    return ptr;
}


void *rp_realloc(void *ptr, size_t bytes, void (*errorhandler)(void *), void *handlerargstruct)
{
    void *ret = realloc(ptr, bytes);

    if (!ret) 
    {
        if (!errorhandler)
            ERROR("Problem encountered while trying to realloc().");
        else
            errorhandler(handlerargstruct);
    }

    if (!memoryhash)
        startmem();

    if (ret != ptr)
        updateref(ptr, ret);

    return ret;
}


void *rp_free(void *address)
{
    if (!address) return address;

    if (!memoryhash) // possible speed-up
    {
        WARNING(INVALID_ADDRESS);
        return address;
    }

    if (deleteref(address))
        free(address);
    
    return NULL;
}






// Internal //





static void startmem(void)
{
	memoryhash 	    = malloc(sizeof *memoryhash);
	memoryhash->buckets = malloc(MEMORY_HASH_SIZE * sizeof *memoryhash->buckets);

	if (!memoryhash)
		ERROR("Memory Hash Table could not be created. Continuing would be unsafe.");

	// nullify the buckets
	unsigned int i;
	for (i = 0; i < MEMORY_HASH_SIZE; i++) 
		memoryhash->buckets[i] = 0;

	atexit(clearmem);
}




/*
 	Memory cleaner. This will run through the memory reference list and call free() on the address pointed to by
	that element's "data" pointer. However, if the user has called free() directly on an element which is referenced
	on the memrefs list, the API will not know it (the list will not be consistent), and free() will be called again
	on the address held in "data" pointer of that reference's entry on the list. 
*/

void clearmem(void)
{
    unsigned int bucketindex;

    for (bucketindex = 0; bucketindex < MEMORY_HASH_SIZE; bucketindex++)
    {
        bucket *element, *next;
        for (element = memoryhash->buckets[bucketindex]; element; element = next)
        {
            next = element->next;
            free(element->address);
            free(element);
        }
    }
}




static int deleteref(void *address)
{
    unsigned int bucketindex = hash(address),
		 refposition = 0;

    if (!memoryhash->buckets[bucketindex])
        return 0;

    bucket *previous = NULL,
	   *current  = memoryhash->buckets[bucketindex];

    while (current && current->address != address)
    {
        previous = current;
        current  = current->next;
        refposition++;
    }

    if (!current)
	   return 0;	// not in the bucket
    
    bucket *nextref = current->next;

    if (previous)
        previous->next = nextref;

    if (refposition == 0)
        memoryhash->buckets[bucketindex] = nextref;

    free(current);
    return 1;
}




static int addref(void *address)
{
    // already in the memory hash table
    if (getref(address))
		return 0;

    unsigned int bucketindex = hash(address);

    bucket *new	= malloc(sizeof *new);

    if (!new)
	ERROR(OUT_OF_MEMORY);

    bucket **list = &(memoryhash->buckets[bucketindex]);
    new->address  = address;
    new->next     = *list;
    *list         = new;

    return 1;
}




static void *getref(void *address)
{
    unsigned int bucketindex = hash(address);

    if (!memoryhash->buckets[bucketindex])
        return NULL;

    else
    {
        bucket *cursor;

        for 
        (
            cursor = memoryhash->buckets[bucketindex]; 
            cursor && cursor->address != address;
            cursor = cursor->next
        );
	
	return (cursor) ? cursor : NULL;
    }
}




// Necessary evil. Used by rp_realloc()
static void updateref(void *oldaddr, void *newaddr)
{
	deleteref(oldaddr);
	addref(newaddr);
}




static unsigned int hash(void *address)
{
	return ((uintptr_t) address) % MEMORY_HASH_SIZE;
}
