/*
 * LIFO.h
 *
 *  Created on: Sep 13, 2016
 *      Author: SaBra
 */

#ifndef LIFO_H_
#define LIFO_H_
//define type Student
typedef struct student{
	int id;
	double grade;
	struct student *next;
}student;

//define type of List
typedef struct List{
	//pointer to the list of students
	student *top;
	//number of elements in the list
	int counter;
}List;

//function to create the List
List* createList();

//function to add students to the list
void addList(List* class, int id, double grade);

//function to print the list of students in LIFO order
void printList(List* class);
/*
 * free the memory allocated for the list
 */
void freeList(List* class);



#endif /* LIFO_H_ */
