/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
			
*/
char nextChar(char* s)
{
	static int i = -1;
	char c;
	++i;
	c = *(s + i);
	if (c == '\0')
		return '\0';
	else
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: 	string input from user
	post:	returns true/false depending on whether or not the statement was balanced
*/
int isBalanced(char* s)
{
	if (s == NULL)
	{
		return 1; //if empty, return true, exit
	}

	DynArr *stack = newDynArr(100); //create new temp array to act as stack structure, arbitrary size

	char c = nextChar(s); //declare ch to hold character being evaluated
	
	while (c != '\0') { //keep looping until null character is found

		if (c == '(') { //for ever opening parenthesis found, push opposite to stack
			pushDynArr(stack, ')');
		}
		else if (c == '{') {
			pushDynArr(stack, '}');
		}
		else if (c == '[') {
			pushDynArr(stack, ']');
		}
		else if (!isEmptyDynArr(stack)) { 
			if (c == topDynArr(stack)) {  //if character is equal to top of stack, pop off
				popDynArr(stack);
			}
		}
		else if ((c == ')' || c == '}' || c == ']') && isEmptyDynArr(stack)) { //if closing parenthesis is found, and stack is empty, string is unbalanced, exit
			deleteDynArr(stack);
			return 0;
		}
		else { //else move to next
		}

		c = nextChar(s); //move to next character in string
	}

	int check = isEmptyDynArr(stack); //check if stack is empty, if empty string, is balanced
	deleteDynArr(stack); //delete stack structure, free memory

	return check; //return true or false for empty stack
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	

	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

