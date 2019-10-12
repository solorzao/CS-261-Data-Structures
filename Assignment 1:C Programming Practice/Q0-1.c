/* CS261- Assignment 1 - Q. 0*/
/* Name: Oliver Solorzano
 * Date: 07 Jul 2019
 * Solution description: C Programming practice. Modifies the addresses and values of various pointers as an example/proof-of-theory exercise. 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr){
  
    /*Print the value and address of the integer pointed to by iptr*/

    printf("%d\n", *iptr);    

	printf("%p\n", &(*iptr));

    /*Increment the value of the integer pointed to by iptr by 5*/

	*iptr += 5;

    /*Print the address of iptr itself*/
	
	printf("%p\n", &iptr);

    /*Dummy variable, ignore the warning*/
   int c=5;  
}


void fooB(int* jptr){
  
     /*Print the value and address of the integer pointed to by jptr*/

	printf("%d\n", *jptr);

	printf("%p\n", &(*jptr));

    /*Decrement the address by 1 pointed to by jptr using jptr */

	jptr -= 1;
      
     /*Print the address of jptr itself*/

	printf("%p\n", &jptr);
}


int main(){
    
    /*Declare an integer x and initialize it randomly to a value in [0,10] 
*/
	int x;

	x = (rand() % 10) + 0;

    /*Print the value and address of x*/
    
	printf("%d\n", x);

	printf("%p\n", &x);

    /*Call fooA() with the address of x*/

	fooA(&x);

    /*Print the value of x*/
    
	printf("%d\n", x);

	/*Is the value of x different than the value that was printed at first ? Why or why not?*/
    
	/*A: The value of x is different than what was printed at first because it was passed into fooA() by reference (address), not by value. */


	/*Call fooB() with the address of x*/
    
	fooB(&x);

    /*Print the value and address of x*/
	
	printf("%d\n", x);

	printf("%p\n", &x);

	/*Are the value and address of x different than the value and address that were printed before the call to fooB(..) ? Why or why not?*/

	/*Qa: The value of x and address of x are the same after the call to fooB(). The value of x isn't modified in any way, but the address 
	pointed to by jptr is decremented, not the address of jptr itself (or x in this case).*/
    
    return 0;
}


