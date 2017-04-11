/*
 * main.c
 *
 *  Created on: Sep 13, 2016
 *      Author: SaBra
 */

#include <stdio.h>
#include <stdlib.h>
#include "LIFO.h"


int main(void){
	List *class = createList();
	addList(class,9,98.99);
	addList(class,10,98.7);
	addList(class,11,87.6);
	addList(class,30,78.5);
	printList(class);
	return 0;
}

