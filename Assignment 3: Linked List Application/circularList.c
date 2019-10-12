/***********************************************************
* Author: Oliver Solorzano
* Email: solorzao@oregonstate.edu
* Date Created: 29 Jul 2019
* Filename: circularList.c
*
* Overview:
*   This program is a circular doubly linked list implementation
*	of a deque with a front sentinel.
*	It allows for the following behavior:
*		- adding a new link to the front/back
*		- getting the value of the front/back links
*		- removing the front/back link
*		- checking if the deque is empty
*		- printing the values of all the links
*		- reversing the order of the links
*
*	Note that this implementation uses double links (links with
*	next and prev pointers) and that given that it is a circular
*	linked deque the last link points to the sentinel and the first
*	link points to the Sentinel -- instead of null.
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

#ifndef FORMAT_SPECIFIER
#define FORMAT_SPECIFIER "%g"
#endif

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
  	Allocates the deque's sentinel and sets the size to 0.
  	The sentinel's next and prev should point to the sentinel itself.
 	param: 	deque 	struct CircularList ptr
	pre: 	deque is not null
	post: 	deque sentinel not null
			sentinel next points to sentinel
			sentinel prev points to sentinel
			deque size is 0
 */
static void init(struct CircularList* deque)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure circular list was created and exists

	deque->sentinel = (struct Link*)malloc(sizeof(struct Link));
	assert(deque->sentinel != 0); //ensure memory for Link was allocated

	deque->sentinel->next = deque->sentinel; //have sentinel point to itself in empty CL
	deque->sentinel->prev = deque->sentinel;

	deque->size = 0; //set start size to 0
	deque->sentinel->value = 0; //set sentinel value to 0
}

/**
	Creates a link with the given value and NULL next and prev pointers.
	param: 	value 	TYPE
	pre: 	none
	post: 	newLink is not null
			newLink value init to value
			newLink next and prev init to NULL
 */
static struct Link* createLink(TYPE value)
{
	/* FIXME: You will write this function */
	struct Link *newLink = (struct Link*)malloc(sizeof(struct Link)); //allocate memory for new link
	assert(newLink != 0); //ensure new link was created

	newLink->next = 0; //set sides of new link to null
	newLink->prev = 0;
	newLink->value = value; //set value of new link

	return newLink; //return pointer to new link
}

/**
	Adds a new link with the given value after the given link and
	increments the deque's size.
	param: 	deque 	struct CircularList ptr
 	param:	link 	struct Link ptr
 	param: 	TYPE
	pre: 	deque and link are not null
	post: 	newLink is not null
			newLink w/ given value is added after param link
			deque size is incremented by 1
 */
static void addLinkAfter(struct CircularList* deque, struct Link* link, TYPE value)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque exists
	assert(link != 0); //ensure link was created before adding tp CL

	struct Link *newLink = createLink(value); //create new link

	newLink->next = link->next; //point new link to link that will follow it
	newLink->prev = link; //point back of new link to link it is being inserted after

	link->next = newLink; //point link that new link is being inserted after to new link
	newLink->next->prev = newLink; //point link after, to new link

	deque->size += 1; //increment deque size value
}

/**
	Removes the given link from the deque and decrements the deque's size.
	param: 	deque 	struct CircularList ptr
 	param:	link 	struct Link ptr
	pre: 	deque and link are not null
	post: 	param link is removed from param deque
			memory allocated to link is freed
			deque size is decremented by 1
 */
static void removeLink(struct CircularList* deque, struct Link* link)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque exists
	assert(!circularListIsEmpty(deque)); //ensure deque isn't empty
	assert(link != 0); //ensure link exists

	link->prev->next = link->next; //link prev link to next link
	link->next->prev = link->prev; //link next link to prev link

	free(link); //deallocate memory for link being removed
	deque->size -= 1; //decrement deque size
}

/**
	Allocates and initializes a deque.
	pre: 	none
	post: 	memory allocated for new struct CircularList ptr
			deque init (call to init func)
	return: deque
 */
struct CircularList* circularListCreate()
{
	struct CircularList* deque = malloc(sizeof(struct CircularList));
	init(deque);
	return deque;
}

/**
	Deallocates every link in the deque and frees the deque pointer.
	pre: 	deque is not null
	post: 	memory allocated to each link is freed
			" " sentinel " "
			" " deque " "
 */
void circularListDestroy(struct CircularList* deque)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque exists

	while (!circularListIsEmpty(deque)) //while deque isn't empty, keep removing links
	{
		removeLink(deque, deque->sentinel->next);
	}
}

/**
	Adds a new link with the given value to the front of the deque.
	param:	deque 	struct CircularList ptr
	param: 	value 	TYPE
	pre: 	deque is not null
	post: 	link is created w/ given value before current first link
			(call to addLinkAfter)
 */
void circularListAddFront(struct CircularList* deque, TYPE value)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque exists

	addLinkAfter(deque, deque->sentinel, value); //add link right after sentinel
}

/**
	Adds a new link with the given value to the back of the deque.
	param: 	deque 	struct CircularList ptr
	param: 	value 	TYPE
	pre: 	deque is not null
	post: 	link is created w/ given value after the current last link
			(call to addLinkAfter)
 */
void circularListAddBack(struct CircularList* deque, TYPE value)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque exists

	addLinkAfter(deque, deque->sentinel->prev, value); //add link at back of deque (behind sentinel)
}

/**
	Returns the value of the link at the front of the deque.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	none
	ret:	first link's value
 */
TYPE circularListFront(struct CircularList* deque)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque exists
	assert(!circularListIsEmpty(deque)); //ensure CL isn't empty

	return deque->sentinel->next->value; //return value at link after sentinel (front)
}

/**
  	Returns the value of the link at the back of the deque.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	none
	ret:	last link's value
 */
TYPE circularListBack(struct CircularList* deque)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque exists
	assert(!circularListIsEmpty(deque)); //ensure CL isn't empty

	return deque->sentinel->prev->value; //return value at link before sentinel (back)
}

/**
	Removes the link at the front of the deque.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	first link is removed and freed (call to removeLink)
 */
void circularListRemoveFront(struct CircularList* deque)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque exists
	assert(!circularListIsEmpty(deque)); //ensure CL isn't empty

	removeLink(deque, deque->sentinel->next); //remove link right after sentinel (front)

}

/**
	Removes the link at the back of the deque.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	last link is removed and freed (call to removeLink)
 */
void circularListRemoveBack(struct CircularList* deque)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque exists
	assert(!circularListIsEmpty(deque)); //ensure CL isn't empty

	removeLink(deque, deque->sentinel->prev); //remove link right before sentinel (back)

}

/**
	Returns 1 if the deque is empty and 0 otherwise.
	param:	deque	struct CircularList ptr
	pre:	deque is not null
	post:	none
	ret:	1 if its size is 0 (empty), otherwise 0 (not empty)
 */
int circularListIsEmpty(struct CircularList* deque)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque isn't empty

	if (deque->size == 0)
	{
		return 1; //if size is 0, return true
	}
	else
	{
		return 0; //if size > 0, return false
	}

}

/**
	Prints the values of the links in the deque from front to back.
	param:	deque	struct CircularList ptr
	pre:	deque is not null
	post:	none
	ret:	outputs to the console the values of the links from front
			to back; if empty, prints msg that is empty
 */
void circularListPrint(struct CircularList* deque)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque exists
	assert(!circularListIsEmpty(deque)); //ensure CL isn't empty

	struct Link *temp = deque->sentinel->next; //set temp equal to first link in CL

	while (temp != deque->sentinel) //keep looping while haven't made full circle
	{
		printf("%g", temp->value); //print value of current link
		temp = temp->next; //move on to next link
	}
}

/**
	Reverses the deque in place without allocating any new memory.
	The process works as follows: current starts pointing to sentinel;
	tmp points to current's next, current's next points to current's prev,
	current's prev is assigned to tmp and current points to current's next
	(which points to current's prev), so you proceed stepping back through
	the deque, assigning current's next to current's prev, until current
	points to the sentinel then you know the each link has been looked at
	and the link order reversed.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	order of deque links is reversed
 */
void circularListReverse(struct CircularList* deque)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque exists
	assert(!circularListIsEmpty(deque)); //ensure CL isn't empty

	struct Link *forward = deque->sentinel->next;
	struct Link *back = deque->sentinel;

	for (int i = 0; i <= deque->size; i++) //keep looping for entirety of CL size
	{
		back->next = back->prev; //set back next to point other direction (backwards)
		back->prev = forward; //set back prev to point other direction (forward)

		back = forward; //set previous back link to current forward link (progress to next duo)
		forward = forward->next; //advance to new forward link
	}
}
