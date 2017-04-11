/*
 * LIFO.c
 *
 *  Created on: Sep 13, 2016
 *      Author: SaBra
 */
#include <stdio.h>
#include <stdlib.h>
#include "LIFO.h"



List* createList(){
	//allocate memory for the list
	List* class = (List*) malloc(sizeof(struct List));

	if(class == NULL){
		printf("Fatal Error: Out of memory \n");
		exit(1);
	}
	//sets the counter to the list to empty
	class->top = NULL;
	class->counter = 0;
	return class;
}

void addList(List *class, int id, double grade){
	/*n->value = value;
    n->next = s->top;
    s->top = n;*/
	student *new = (student*) malloc(sizeof(struct student));
	if(new == NULL){
		printf("Fatal Error: Out of memory \n");
		exit(1);
	}
	new->id = id;
	new->grade = grade;
	new->next = class->top;
	class->top = new;
	class->counter++;
}

void printList(List* class){
	int print = class->counter;
	student *current = class->top;
	while(current != NULL){
		printf("Student id: %d, grade: %f \n",current->id, current->grade);
		current = current->next;
		print--;
	}
}
void freeList(List* class){
	student *current;
	while(class->top != NULL){
		current = class->top;
		class->top = class->top->next;
		free(current);
	}
	free(class);
}

