#include "list.h"
#include "../redpill.h"
#include "../memory.h"
#include <stdlib.h>


// Allocates and populates a node containing the given data
// pointer.

list *rplist_create(void *data)
{
    list *new = rp_malloc(sizeof *new, 0, 0);

    new->data = data;
    new->prev = new->next = 0;

    return new;
}




// Frees all container nodes. If destroydata is not 0,
// also frees the data pointers within them.

void rplist_destroy(list **head, int destroydata)
{
    if (!head || !*head)
        return;

    if (destroydata)
    {
        for (; *head; *head = (*head)->next)
	{
	    rp_free((*head)->data);
	    rp_free(*head);
	}
    }
    else
    {
        for (; *head; *head = (*head)->next)
            rp_free(*head);
    }
}



// Pops off the "leftmost" (prev-most) node, frees the container and 
// returns the data pointer's value.

void *rplist_shift(list **head)
{
    if (!head || !*head)
        return 0;

    list *todelete = *head;
    *head = (*head)->next;

    void *data = todelete->data;
	
    rp_free(todelete);
    return data;
}



// Appends a new node containing the given data address to
// the "leftmost" (prev-most) node.

void rplist_unshift(list **head, void *data)
{
    if (!head || !*head)
        return;	    

    list *new = rplist_create(data);
    new->prev = 0;
    new->next = *head;

    (*head)->prev = new;
    *head = new;
}



// Appends a new node containing the given data address to the
// "rightmost" (next-most) node.

void rplist_push(list *head, void *data)
{
    if (!head)
        return;

    while (head->next)
        head = head->next;

    head->next = rplist_create(data);
    head->next->prev = head;
    head->next->next = 0;
}




// Pops off the "rightmost" (next-most) element of the list, returning
// the value of the data pointer and freeing the container node.

void *rplist_pop(list *head)
{
    if (!head)
        return 0;	    

    while (head->next)
        head = head->next;

    void *data = head->data;

    if (head->prev)
        head->prev->next = 0;

    rp_free(head);
    return data;
}




// This removes an element from the list, given its address.
// If 'destroydata' is not 0, it will free the element's address
// as well as the list node containing it. If it is 0, it will only
// free the list node.

int rplist_remove(list **head, void *data, int destroydata)
{
    if (!head || !*head)
        return 0;

    list *backwards;

    for (backwards = (*head)->prev; backwards; backwards = backwards->prev)
    {
        if (backwards->data == data)
        {
	    if (destroydata) 
	    {
	        rp_free(backwards->data);
		backwards->data = 0;
	    }
	    if (backwards->next)
                backwards->next->prev = backwards->prev;
	    if (backwards->prev)
                backwards->prev->next = backwards->next;

            rp_free(backwards);
            return 1;
        }
    }

    list *forward;
    for (forward = *head; forward; forward = forward->next)
    {
        if (forward->data == data)
        {
	    if (destroydata) 
	    {
	        rp_free(forward->data);
		forward->data = 0;
	    }
	    if (forward->prev)
                forward->prev->next = forward->next;
	    if (forward->next)
                forward->next->prev = forward->prev;
            if (forward == *head)
	        *head = (*head)->next;

            rp_free(forward);
            return 1;
        }
    }

    return 0;
}




void *rplist_get(list *head, unsigned int position)
{
    int counter = position;

    while (head && counter-- > 0)
        head = head->next;

    return (counter == -1) ? head->data : 0;
}




void rplist_traverse(list *head, void (*process)(void *))
{
    for (; head; head = head->next)
        process(head->data);
}
