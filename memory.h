#ifndef RP_MEMORY_H
#define RP_MEMORY_H

#define OUT_OF_MEMORY 	"Out of memory. Aborting execution."
#define INVALID_ADDRESS "Invalid memory address."


// Memory Hash //

typedef struct bucket_
{
	void 	*address;
	struct 	bucket_ *next;
} bucket;

typedef struct
{
	bucket  **buckets;
} hashtable;




void *rp_malloc(size_t, void (*)(void *), void *);
void *rp_realloc(void *, size_t, void (*)(void *), void *);
void *rp_free(void *);

#endif
