/* CS261- Assignment 1 - Q.2*/
/* Name: Oliver Solorzano
 * Date: 07 Jul 2019
 * Solution description: Contains function that swaps the address values of two variables and increments the value of the third.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    /*Swap the addresses stored in the pointer variables a and b*/

	int *temp = a;
	a = b;
	b = temp;
    
    /*Decrement the value of integer variable c*/

	c -= 1;

	return c;
    /*Return c*/
}

int main(){
    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
	int x, y, z, fooValue;

	x = (rand() % 10) + 0;
	y = (rand() % 10) + 0;
	z = (rand() % 10) + 0;

    /*Print the values of x, y and z*/
    
	printf("The values are x: %d, y: %d, z: %d\n", x, y, z);

    /*Call foo() appropriately, passing x,y,z as parameters*/

	fooValue = foo(&x, &y, z);
	
    /*Print the values of x, y and z*/

	printf("The values are x: %d, y: %d, z: %d\n", x, y, z);

    /*Print the value returned by foo*/
 
	printf("The value returned by foo is: %d\n", fooValue);

	/*Qa: The value returned by foo is different because the value was decremented within the function and 
	returned. A copy of c was made in the function and decremented, not the original, so outside the function "z" will retain its original value.
	Qb: The values of x and y changed after calling foo() because the addresses of a and b were swapped in the function.*/

    return 0;
}
    
    


