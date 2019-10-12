/* CS261- Assignment 1 - Q.1*/
/* Name: Oliver Solorzano
 * Date: 08 Jun 2019
 * Solution description: Create roster of students with scores and associated IDs. Scores and IDs are generated randomly 
 * and the results are displayed. The lowest, highest, and average scores from the roster are calculated and displayed.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
	struct student *students = (struct student*)malloc(10 * sizeof(struct student));
     
     /*Return the pointer*/
	return students;
}

void generate(struct student* students){
     /*Generate random and unique IDs and random scores for ten students, IDs being between 1 and 10, scores between 0 and 100*/
	
	int idUnique = 0; //create bool, set to false 
	int i, j;

	students[0].id = ((rand() % 10) + 1);  //set ID and score for first student to have something to compare
	students[0].score = ((rand() % 100) + 1);

	for (i = 1; i < 10; i++)
	{
		while (idUnique == 0)  //while number isn't unique, keep generating new one
		{
			students[i].id = ((rand() % 10) + 1);  //generate random number between 1 and 10
			
			for (j = 0; j < i; j++) //check uniqueness against number of finalized IDs
			{
				if (students[i].id == students[j].id)
				{
					idUnique = 0;	//if id is same, set unique flag to false
					j = 10;  //exit for loop
				}
				else
				{
					idUnique = 1;	//else set true, exit while loop
				}


			}
		
		}

		students[i].score = ((rand() % 100) + 1);  //set student score, between 0-100
		idUnique = 0;  //reset bool
	}
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	int i;

	for (i = 0; i < 10; i++)
	{
		printf("ID%d ", students[i].id);
		printf(" Score: %d\n", students[i].score);
	}
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the 
ten students*/
	int sum = 0, min, max;
	float average;
	int i;

	for (i = 0; i < 10; i++)
	{
		sum += students[i].score;
	}

	average = sum / 10;

	min = max = students[0].score;  //set min/max to first student score

	for (i = 0; i < 10; i++)
	{
		if (students[i].score < min)
		{
			min = students[i].score;
		}
	}

	for (i = 0; i < 10; i++)
	{
		if (students[i].score > max)
		{
			max = students[i].score;
		}
	}

	printf("The lowest score is: %d\n", min);
	printf("The highest score is: %d\n", max);
	printf("The average score is: %f\n", average);

}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	if (stud != 0)
	{
		free(stud);
	}
}

int main(){
    struct student* st = 0;  //per instructions
	printf("hello");
    /*Call allocate*/
	st = allocate();  //allocate memory for structure
    /*Call generate*/
	generate(st);  //fill with scores, ID
    /*Call output*/
	output(st);  //output student information
    /*Call summary*/
	summary(st);	//output lowest, highest, and average
    /*Call deallocate*/
	deallocate(st);		//free memory

    return 0;
}

