/*
//  queue.c
//  Created by Wenxiang Lei on 16/9/26.
//
*/
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
/*
typedef struct node_FIFO{
    int F_NodeId;
    double timeEnteredQueue;
    double timeInQueue;
    double timeInSystem;
    struct node_FIFO *next;
    //struct node_FIFO *prev;
} F_Node;

typedef struct Queue{
	F_Node *head; 
	F_Node *tail;
	//int size;
} F_Queue;
*/
F_Node *newNode(int Id, double timeEn)
{
    F_Node *temp = (F_Node*)malloc(sizeof(F_Node));
    temp->F_NodeId = Id;
    temp->timeEnteredQueue = timeEn;
    temp->next = NULL;
    return temp; 
}
 
// A utility function to create an empty queue
F_Queue *createQueue()
{
    F_Queue *q = (F_Queue*)malloc(sizeof(F_Queue));
    q->head = q->tail = NULL;
    return q;
}

void push(F_Queue *q, int Id, double timeEn)
{
    // Create a new LL node
    F_Node *temp = newNode(Id, timeEn);
    // If queue is empty, then new node is head and tail both
    if (q->tail == NULL)
    {
       q->head = q->tail = temp;
       return;
    }
    // Add the new node at the end of queue and change tail
    q->tail->next = temp;
    q->tail = temp;
}

F_Node *pop(F_Queue *q)
{
 	  // If queue is empty, return NULL.
    if (q->head == NULL)
       return NULL;
 
    // Store previous head and move head one node ahead
    F_Node *temp = q->head;
    q->head = q->head->next;
 
    // If head becomes NULL, then change tail also as NULL
    if (q->head == NULL)
       q->tail = NULL;
    return temp;
}

void freeMemo(F_Queue *q) 
{
    F_Node *thisNode = q->head;
    while (thisNode != NULL){
        F_Node *temp = thisNode->next;
        free(thisNode);
        thisNode = temp;
    }
    free(q);
}


int main()
{
    F_Queue *q = createQueue();
    push(q, 10,0.1);
    push(q, 20,0.1);
    push(q, 30,0.1);
    //pop(q);
    F_Node *n = pop(q);

    //push(q, 40,0.1);
    //push(q, 50,0.1);
    if (n != NULL)
      printf("Dequeued item is %d", n->F_NodeId);
    return 0;
}
