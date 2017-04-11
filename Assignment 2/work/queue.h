/*
//  queue.h
//  Created by Wenxiang Lei on 16/9/26.
//
*/

#ifndef queue_h
#define queue_h

typedef struct node_FIFO{
    int F_NodeId;
    double timeEnteredQueue;
    double timeInQueue;
    double timeInSystem;
    struct node_FIFO *next;
} F_Node;

typedef struct Queue{
	F_Node *head; 
	F_Node *tail;
} F_Queue;

F_Node *newNode(int Id, double timeEn);
F_Queue *createQueue();
void push(F_Queue *q, int Id, double timeEn);
F_Node *pop(F_Queue *q);
void freeFifo(F_Queue *q); 



/*
void q_init(Queue *q);  // initialize
int q_size(Queue *q);  // get the number of elements in the queue
void q_push(Queue *q, void *p);  // add an element to the queue; void *p is the pointer pointing to your data
void *q_peek(Queue *q);  // get the first element in the queue
void *q_pop(Queue *q);  // remove and get the first element
void q_clear(Queue *q, void (*free_data)(void *));  // free all the remaining elements in the queue; the second arg tells how to free your data
*/
#endif /* queue_h */