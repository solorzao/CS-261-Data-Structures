/* CS261- Assignment 1 - Q.3*/
/* Name: Oliver Solorzano
 * Date: 08 Jul 2019
 * Solution description: Program that takes user string input, filters for only alphabetic characters, and converts the filtered string to camel case.
 */

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)


char toUpperCase(char ch){
  /*Convert ch to upper case, assuming it is in lower case currently*/
	return (ch - 32);
}

char toLowerCase(char ch){
  /*Convert ch to lower case, assuming it is in upper case currently*/                          
	return (ch + 32);
}

int stringLength(char s[]) {
   /*Return the length of the string*/
	int length = 0; //declare length counter, intialize to 0

	while (s[length] != '\0') //keep moving through array until terminating character is reached
	{
		length++; //increment length count
	}
	
	return length; 
}


void camelCase(char* word){ 
	/*Convert to camelCase*/
	char tempArray[256]; //create array to hold converted camel case word
	char tempChar; //holder for char to convert to lower/upper
	char*tmpPtr = tempArray;

	int tempLength = 0; //length count for converted word
	int passedWordLength = stringLength(word); //length of passed word, used for iteration count
	

	for (int i = 0; i < passedWordLength; i++)
	{
		if (word[i] != '_') //if not underscore, transfer normally
		{
			tempArray[tempLength] = word[i];
			tempLength++;
		}

		else if (word[i] == '_') //if underscore, convert next char to upper
		{
			tempChar = word[i + 1];
			tempChar = toUpperCase(tempChar);
			tempArray[tempLength] = tempChar;
			tempLength++;
			i += 1; //skip ahead by 1
		}

	}

	tempArray[tempLength] = '\0'; //add null terminator

	int tempWordLength = stringLength(tempArray);

	printf("Your converted word is: ");

	for (int i = 0; i < tempWordLength; i++)
	{
		printf("%c", tempArray[i]);
	}

	word = tmpPtr;
}

int main(){

	/*Read the string from the keyboard*/
	char userInput[256]; //create array of characters to hold input
	char filteredInput[256]; //create array to hold filtered input
	char *wordPtr; //create pointer to array
	wordPtr = filteredInput; //set pointer to point to array

	printf("Please enter a word: "); //prompt user for input

	scanf("%[^\n]%*c", userInput); //save input in userWord character array, took method of taking string input with spaces from https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/
	
	int userWordLength;
	int filteredCount = 0; //counter for valid characters
	
	char temp;

	userWordLength = stringLength(userInput); //find user input length to set counter for loop
	
	int lastCharUnderscore = 0; //bool to check if previous character was underscore
	
	if ((userInput[0] < 65) || (userInput[0] > 122) || (userInput[0] < 97 && userInput[0] > 90)) //if first char of input is not alpha, prevent underscore, set bool to true
	{
		lastCharUnderscore = 1;
	}

	for (int i = 0; i < userWordLength; i++)
	{
		if ((userInput[i] >= 65) && (userInput[i] <= 90)) //if uppercase alphabetic, convert to lowercase, transfer over
		{
			temp = userInput[i];
			temp = toLowerCase(temp);

			filteredInput[filteredCount] = temp;
			filteredCount++;
			lastCharUnderscore = 0;
		}
		else if ((userInput[i] >= 97) && (userInput[i] <= 122)) //if lowercase alphabetic, transfer over
		{
			filteredInput[filteredCount] = userInput[i];
			filteredCount++;
			lastCharUnderscore = 0;
		}
		else if (((userInput[i] < 65) || (userInput[i] > 122) || (userInput[i] < 97 && userInput[i] > 90)) && (lastCharUnderscore == 0) && (userInput[i] != '_')) //if anything besides alphabetic, replace with underscore, set lastCharUnderscore to true to prevent repeat underscores
		{
			filteredInput[filteredCount] = '_';
			filteredCount++;
			lastCharUnderscore = 1;
		}
		else if ((userInput[i] == '_') && (lastCharUnderscore == 0) && (i != userWordLength -1)) //if underscore, and no underscore previously, transfer over. Set lastCharUnderscore to true to prevent repeat underscores. Check for underscore at end
		{
			filteredInput[filteredCount] = userInput[i];
			filteredCount++;
			lastCharUnderscore = 1;
		}
			
	}

	filteredInput[filteredCount] = '\0'; //add null terminator

	/*Call camelCase*/
	
	camelCase(wordPtr);
	
	/*Print the new string*/

	int finishedWordLength = stringLength(wordPtr);

	printf("\nYour converted word is: "); //couldn't figure out how to make changes to array by reference and not value, fully converted word prints within camelCase function, but not after

	for (int i = 0; i < finishedWordLength; i++)
	{
		printf("%c", wordPtr[i]);
	}
	
	return 0;
}

