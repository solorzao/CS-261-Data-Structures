/***********************************************************
* Author: Oliver Solorzano
* Email: solorzao@oregonstate.edu
* Date Created: 29 Jul 2019
* Filename: linkedList.c
*
* Overview:
*   This program is a linked list implementation of the deque
*	(as worked on in Worksheet 19) and bag (as worked on in
*	Worksheet 22) ADTs.
*	The deque ADT allows for the following behavior:
*		- adding a new link to the front/back
*		- getting the value of the front/back links
*		- removing the front/back link
*	The bag ADT allows for the following behavior:
*		- adding a new link
*		- checking if a link exists with a given value
*		- removing a link  with a given value if it exists
*	Both allow for:
*		- checking if empty
*		- printing the values of all of the links
*
*	Note that both implementations utilize a linked list with
*	both a front and back sentinel and double links (links with
*	next and prev pointers).
************************************************************/
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef FORMAT_SPECIFIER
#define FORMAT_SPECIFIER "%d"
#endif

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	struct Link* frontSentinel;
	struct Link* backSentinel;
	int size;
};

/**
  	Allocates the list's sentinel and sets the size to 0.
  	The sentinels' next and prev should point to eachother or NULL
  	as appropriate.
	param: 	list 	struct LinkedList ptr
	pre: 	list is not null
	post: 	list front and back sentinel not null
			front sentinel next points to back
			front sentinel prev points to null
			back sentinel prev points to front
			back sentinel next points to null
			list size is 0
 */
static void init(struct LinkedList* list) {

	/* FIXME: You will write this function */
	list->frontSentinel = malloc(sizeof(struct Link)); //allocate memory for front sentinel
	assert(list->frontSentinel != 0); //ensure that memory was allocated

	list->backSentinel = malloc(sizeof(struct Link)); //allocate memory for back sentinel
	assert(list->backSentinel); //ensure that memory was allocated

	list->frontSentinel->next = list->backSentinel; //point sentinels to each other (empty list)
	list->backSentinel->prev = list->frontSentinel;

	list->size = 0; //intialize list size to 0
}

/**
 	Adds a new link with the given value before the given link and
	increments the list's size.
 	param: 	list 	struct LinkedList ptr
 	param:	link 	struct Link ptr
 	param: 	TYPE
	pre: 	list and link are not null
	post: 	newLink is not null
			newLink w/ given value is added before param link
			list size is incremented by 1
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	/* FIXME: You will write this function */
	struct Link *newLink = (struct Link *)malloc(sizeof(struct Link)); //allocate memory for new link
	assert(newLink != 0); //ensure memory was allocated
	assert(list != 0); //ensure current list exists

	newLink->value = value; //assign passed value to new link
	newLink->next = link; //point new link to link it is being inserted before
	newLink->prev = link->prev; //point new link back at the link that the link it is being inserted before was pointing to

	link->prev->next = newLink; //point link behind to new link
	link->prev = newLink; //point link it was inserted before back at new link

	list->size++; //increment list size
}

/**
	Removes the given link from the list and
	decrements the list's size.
	param: 	list 	struct LinkedList ptr
 	param:	link 	struct Link ptr
	pre: 	list and link are not null
	post: 	param link is removed from param list
			memory allocated to link is freed
			list size is decremented by 1
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	/* FIXME: You will write this function */
	assert(list != 0); //ensure list object exists

	link->prev->next = link->next; //point prev link to link after the one being removed
	link->next->prev = link->prev; //point link after to one being removed, back at the link before the one being removed

	free(link); //free the memory
	link = 0; //set link pointer equal to null

	list->size--; //decrement list size
}

/**
	Allocates and initializes a list.
	pre: 	none
	post: 	memory allocated for new struct LinkedList ptr
			list init (call to init func)
	return: list
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* list = malloc(sizeof(struct LinkedList));
	init(list);
	return list;
}

/**
	Deallocates every link in the list including the sentinels,
	and frees the list itself.
	param:	list 	struct LinkedList ptr
	pre: 	list is not null
	post: 	memory allocated to each link is freed
			" " front and back sentinel " "
			" " list " "
 */
void linkedListDestroy(struct LinkedList* list)
{
	assert(list != NULL);
	while (!linkedListIsEmpty(list)) {
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
	list = NULL;
}

/**
	Adds a new link with the given value to the front of the deque.
	param: 	deque 	struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	deque is not null
	post: 	link is created w/ param value stored before current first link
			(call to addLinkBefore)
 */
void linkedListAddFront(struct LinkedList* deque, TYPE value)
{
	/* FIXME: You will write this function */
	addLinkBefore(deque, deque->frontSentinel->next, value); //call function to add link after front sentinel and before current first link
}

/**
	Adds a new link with the given value to the back of the deque.
	param: 	deque 	struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	deque is not null
	post: 	link is created with given value before last link (sentinel)
			(call to addLinkBefore)
 */
void linkedListAddBack(struct LinkedList* deque, TYPE value)
{
	/* FIXME: You will write this function */
	addLinkBefore(deque, deque->backSentinel, value); //call function to add link before the back sentinel
}

/**
	Returns the value of the link at the front of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	none
	ret:	first link's value
 */
TYPE linkedListFront(struct LinkedList* deque)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure that deque exists
	assert(!linkedListIsEmpty(deque)); //ensure that deck is not empty, before trying to call link at the front

	return deque->frontSentinel->next->value; //return value of the front link
}

/**
	Returns the value of the link at the back of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	none
	ret:	last link's value
 */
TYPE linkedListBack(struct LinkedList* deque)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure that deque exists
	assert(!linkedListIsEmpty(deque)); //ensure that linked list isn't empty before trying to pull the bakc value

	return deque->backSentinel->prev->value; //return value of link at back of deque (right before back sentinel)
}

/**
	Removes the link at the front of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	first link is removed and freed (call to removeLink)
 */
void linkedListRemoveFront(struct LinkedList* deque)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque exists 
	assert(!linkedListIsEmpty(deque)); //ensure deque isn't empty

	removeLink(deque, deque->frontSentinel->next); //remove link after front sentinel
}

/**
	Removes the link at the back of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	last link is removed and freed (call to removeLink)
 */
void linkedListRemoveBack(struct LinkedList* deque)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque exists
	assert(!linkedListIsEmpty(deque)); //ensure deque isn't empty

	removeLink(deque, deque->backSentinel->prev); //remove link before back sentinel
}

/**
	Returns 1 if the deque is empty and 0 otherwise.
	param:	deque	struct LinkedList ptr
	pre:	deque is not null
	post:	none
	ret:	1 if its size is 0 (empty), otherwise 0 (not empty)
 */
int linkedListIsEmpty(struct LinkedList* deque)
{
	/* FIXME: You will write this function */
	return deque->size == 0; //if size is zero, deque is empty, return true
}

/**
	Prints the values of the links in the deque from front to back.
	param:	deque	struct LinkedList ptr
	pre:	deque is not null
	post:	none
	ret:	outputs to the console the values of the links from front
			to back; if empty, prints msg that is empty
 */
void linkedListPrint(struct LinkedList* deque)
{
	/* FIXME: You will write this function */
	assert(deque != 0); //ensure deque exists
	assert(!linkedListIsEmpty(deque)); //ensure deque isn't empty

	struct Link *temp = deque->frontSentinel->next;

	while (temp != deque->backSentinel)
	{
		printf("%d", temp->value);
		temp = temp->next;
	}
}

/**
	Adds a link with the given value to the bag.
	param:	bag		struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	bag is not null
	post: 	link is created w/ given value before current first link
			(call to addLinkBefore)
			Note that bag doesn't specify where new link should be added;
			can be anywhere in bag according to its ADT.
 */
void linkedListAdd(struct LinkedList* bag, TYPE value)
{
	/* FIXME: You will write this function */
	addLinkBefore(bag, bag->frontSentinel->next, value); //add link after front sentinel
}

/**
	Returns 1 if a link with the value is in the bag and 0 otherwise.
	param:	bag		struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	bag is not null
	post:	none
	ret:	1 if link with given value found; otherwise, 0
 */
int linkedListContains(struct LinkedList* bag, TYPE value)
{

	/* FIXME: You will write this function */
	assert(bag != 0); //ensure bag exists
	assert(!linkedListIsEmpty(bag)); //ensure bag isn't empty

	struct Link *temp = bag->frontSentinel->next; //create temp to hold current link

	while (temp != bag->backSentinel) //keep looping until back sentinel is reached
	{
		if (temp->value == value) //if value is found, return true
		{
			return 1;
		}

		temp = temp->next; //move to next link
	}
	return 0; //if not found, return false
}

/**
	Removes the first occurrence of a link with the given value.
	param:	bag		struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	bag is not null
	post:	if link with given value found, link is removed
			(call to removeLink)
 */
void linkedListRemove(struct LinkedList* bag, TYPE value)
{
	/* FIXME: You will write this function */
	assert(bag != 0); //ensure bag exists
	assert(!linkedListIsEmpty(bag)); //ensure bag isn't empty

	struct Link *temp = bag->frontSentinel->next; //create temp to hold current link

	while (temp != bag->backSentinel) //keep looping until end is reached
	{
		if (temp->value == value) //if found, call remove
		{
			removeLink(bag, temp);
			return;
		}

		temp = temp->next; //move to next link
	}
}
