/***********************************************************
* Author: Oliver Solorzano
* Email: solorzao@oregonstate.edu
* Date Created: 12 Aug 2019
* Filename: bst.c
*
* Solution description: Implementation of a Binary Search Tree
* that can store any arbitrary struct in its nodes.
************************************************************/

#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"

/*----------------------------------------------------------------------------
 very similar to the compareTo method in java or the strcmp function in c. it
 returns an integer to tell you if the left value is greater then, less then, or
 equal to the right value. you are comparing the number variable, letter is not
 used in the comparison.

 if left < right return -1
 if left > right return 1
 if left = right return 0
 */

 /*Define this function, type casting the value of void * to the desired type.
  The current definition of TYPE in bst.h is void*, which means that left and
  right are void pointers. To compare left and right, you should first cast
  left and right to the corresponding pointer type (struct data *), and then
  compare the values pointed by the casted pointers.

  DO NOT compare the addresses pointed by left and right, i.e. "if (left < right)",
  which is really wrong.
 */
int compare(TYPE left, TYPE right)
{
    /*FIXME: write this*/

	assert(left != 0); //ensure left and right have values before comparing
	assert(right != 0);

	struct data* leftNode = (struct data*) left; //type cast passed arguments
	struct data* rightNode = (struct data*) right;

	if (leftNode->number < rightNode->number) { //if left node number is smaller, return -1
		return -1;
	}
	else if (leftNode->number > rightNode->number) { //if left node number is larger, return 1
		return 1;
	}
	return 0; //if equal, return 0

}

/*Define this function, type casting the value of void * to the desired type*/
void print_type(TYPE curval)
{
    /*FIXME: write this*/
	assert(curval != 0); //ensure curval exists
	struct data* cur = (struct data*) curval; //type cast passed argument
	printf("%d", cur->number); //print number of cur

}


