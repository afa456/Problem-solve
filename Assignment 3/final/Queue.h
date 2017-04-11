/*
 * Queue.h
 *
 *  Created on: Sep 16, 2016
 * 
 */

#ifndef QUEUE_H
#define QUEUE_H

typedef struct _q_node {
	int *data;  // implement a generic queue by using void pointer
	struct _q_node *next;
} QNode;

typedef struct {
	QNode *head, *tail;
	int size;
} Queue;

void queue_init(Queue *q); 
int queue_size(Queue *q);  
void queue_push(Queue *q, void *p);  
void *queue_pop(Queue *q);  
void queue_clear(Queue *q, void (*free_data)(void *)); 

#endif /* QUEUE_H */

