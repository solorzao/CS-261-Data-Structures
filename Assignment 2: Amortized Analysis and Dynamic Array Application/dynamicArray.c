/*	dynamicArray.c: Dynamic Array implementation. */
#include <assert.h>
#include <stdlib.h>
#include "dynArray.h"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};


/* ************************************************************************
	Dynamic Array Functions
************************************************************************ */

/* Initialize (including allocation of data array) dynamic array.

	param: 	v		pointer to the dynamic array
	param:	cap 	capacity of the dynamic array
	pre:	v is not null
	post:	internal data array can hold cap elements
	post:	v->data is not null
*/
void initDynArr(DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v!= 0);
	v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;	
}

/* Allocate and initialize dynamic array.

	param:	cap 	desired capacity for the dyn array
	pre:	none
	post:	none
	ret:	a non-null pointer to a dynArr of cap capacity
			and 0 elements in it.		
*/
DynArr* newDynArr(int cap)
{
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r,cap);
	return r;
}

/* Deallocate data array in dynamic array. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	d.data points to null
	post:	size and capacity are 0
	post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v)
{
	if(v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/* Deallocate data array and the dynamic array ure. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	the memory used by v->data is freed
	post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

/* Resizes the underlying array to be the size cap 

	param: 	v		pointer to the dynamic array
	param:	cap		the new desired capacity
	pre:	v is not null
	post:	v has capacity newCap
*/
void _dynArrSetCapacity(DynArr *v, int newCap)
{	
	assert(v != 0); //check that array exits

	TYPE *temp = malloc(sizeof(TYPE) * newCap); //create temp array
	assert(temp != 0);	//check to see that memory was allocated 

	for (int i = 0; i < v->size; i++)  //copy elements over to new array
	{
		temp[i] = v->data[i];
	}

	free(v->data);  //free old array memory

	v->data = temp; //set pointer to point to new array
	temp; //set temp to null
	
	v->capacity = newCap; //set new capacity
}

/* Get the size of the dynamic array

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	none
	ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v)
{
	return v->size;
}

/* 	Adds an element to the end of the dynamic array

	param: 	v		pointer to the dynamic array
	param:	val		the value to add to the end of the dynamic array
	pre:	the dynArry is not null
	post:	size increases by 1
	pre:	if reached capacity, capacity is doubled
	post:	val is in the last utilized position in the array
*/
void addDynArr(DynArr *v, TYPE val)
{
	if (v->size >= v->capacity) //if size is greater than/equal to capacity, double capacity
	{
		_dynArrSetCapacity(v, 2 * v->capacity); //call function to set new capacity
	}

	v->data[v->size] = val; //set index at size to value
	v->size++; //increment size count

}

/*	Get an element from the dynamic array from a specified position
	
	param: 	v		pointer to the dynamic array
	param:	pos		integer index to get the element from
	pre:	v is not null
	pre:	v is not empty
	pre:	pos < size of the dyn array and >= 0
	post:	no changes to the dyn Array
	ret:	value stored at index pos
*/

TYPE getDynArr(DynArr *v, int pos)
{
	assert(v != 0 && v->size != 0); //check that array exists and contains elements

	assert(pos >= 0 && pos < v->size); //check that position is within the array index range (capacity)
	
	return v->data[pos]; //return data value at pos

}

/*	Put an item into the dynamic array at the specified location,
	overwriting the element that was there

	param: 	v		pointer to the dynamic array
	param:	pos		the index to put the value into
	param:	val		the value to insert 
	pre:	v is not null
	pre:	v is not empty
	pre:	pos >= 0 and pos < size of the array
	post:	index pos contains new value, val
*/
void putDynArr(DynArr *v, int pos, TYPE val)
{
	assert(v != 0 && v->size != 0); //check that array exists and memory has been allocated

	assert(pos >= 0 && pos < v->size); //check that position is within the array range
	
	v->data[pos] = val; //set data value at index pos to val
}

/*	Swap two specified elements in the dynamic array

	param: 	v		pointer to the dynamic array
	param:	i,j		the elements to be swapped
	pre:	v is not null
	pre:	v is not empty
	pre:	i, j >= 0 and i,j < size of the dynamic array
	post:	index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(DynArr *v, int i, int  j)
{
	assert(v != 0 && v->size != 0); //check to ensure array memory has been allocated

	assert(i >= 0 && i < v->size);  //check to make sure value to be swapped exists within range

	assert(j >= 0 && j < v->size);  ////check to make sure value to be swapped exists within range

	TYPE temp = getDynArr(v, i); //get value at position i, in array v

	putDynArr(v, i, getDynArr(v, j)); //put value at position j, in array v, in position i, in array v

	putDynArr(v, j, temp);  //put saved temp value in position j, in array v
}

/*	Remove the element at the specified location from the array,
	shifts other elements back one to fill the gap

	param: 	v		pointer to the dynamic array
	param:	idx		location of element to remove
	pre:	v is not null
	pre:	v is not empty
	pre:	idx < size and idx >= 0
	post:	the element at idx is removed
	post:	the elements past idx are moved back one
*/
void removeAtDynArr(DynArr *v, int idx)
{
	assert(v != 0 && v->size != 0); //check to see that index value is valid and array has memory allocated
	assert(idx >= 0 && idx < v->size);
	
	for (int i = idx; i <= (v->size - 1); i++)
	{
		if (i+1 < v->size)
		{
			putDynArr(v, i, getDynArr(v, (i + 1)));  //move values over starting at index where value is to be removed
		}
	}

	v->size--; //update array size
}



/* ************************************************************************
	Stack Interface Functions
************************************************************************ */

/*	Returns boolean (encoded in an int) demonstrating whether or not the 
	dynamic array stack has an item on it.

	param:	v		pointer to the dynamic array
	pre:	the dynArr is not null
	post:	none
	ret:	1 if empty, otherwise 0
*/
int isEmptyDynArr(DynArr *v)
{
	assert(v != 0); //ensure array exists

	if (sizeDynArr(v) == 0)
	{
		return 1; //if size is 0, return true
	}
	else
	{
		return 0; //else return false
	}
}

/* 	Push an element onto the top of the stack

	param:	v		pointer to the dynamic array
	param:	val		the value to push onto the stack
	pre:	v is not null
	post:	size increases by 1
			if reached capacity, capacity is doubled
			val is on the top of the stack
*/
void pushDynArr(DynArr *v, TYPE val)
{
	assert(v != 0); //check to ensure array memory is allocated

	addDynArr(v, val); //add value to array at end
}

/*	Returns the element at the top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the stack
*/
TYPE topDynArr(DynArr *v)
{
	assert(v != 0); //ensure array exists

	assert(sizeDynArr(v) > 0); //ensure that array isn't empty

	return getDynArr(v, (sizeDynArr(v) - 1)); //get value at end of array
}

/* Removes the element on top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	size is decremented by 1
			the top has been removed
*/
void popDynArr(DynArr *v)
{
	assert(v != 0); //ensure array exists

	assert(sizeDynArr(v) >= 1); //ensure array has at least one element to pop

	removeAtDynArr(v, (sizeDynArr(v) - 1)); //remove value at end of array
}

/* ************************************************************************
	Bag Interface Functions
************************************************************************ */

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	v		pointer to the dynamic array
	param:	val		the value to look for in the bag
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the bag
*/
int containsDynArr(DynArr *v, TYPE val)
{
	assert(!isEmptyDynArr(v)); //check to ensure array isn't empty before checking

	for (int i = 0; i < v->size; i++) { //loop through entire array to check for value
		if (val == v->data[i])  //if value found, return true
		{
			return 1;
		}
	}
	return 0; //else return 0 (false)
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	v		pointer to the dynamic array
	param:	val		the value to remove from the array
	pre:	v is not null
	pre:	v is not empty
	post:	val has been removed
	post:	size of the bag is reduced by 1
*/
void removeDynArr(DynArr *v, TYPE val)
{
	for (int i = 0; i < v->size; i++) { //loop through entire array
		if (val == v->data[i]) { //if value is found in array
			removeAtDynArr(v, i); //remove value at position
			return; //when found return
		}
	}

}
