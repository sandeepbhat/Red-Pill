#ifndef RP_LIST_H
#define RP_LIST_H

typedef struct linkedlist
{
	void *data;
	struct linkedlist *next;
	struct linkedlist *prev;
} list;

list *rplist_create(void *);
void rplist_destroy(list **, int);
void *rplist_shift(list **);
void rplist_unshift(list **, void *);
void rplist_push(list *, void *);
void *rplist_pop(list *);
int  rplist_remove(list **, void *, int);
void *rplist_get(list *, unsigned int);
void rplist_traverse(list *, void (*)(void *));


#endif
