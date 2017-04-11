/*
//  PriorityQueue.c
//  
//  Created by Wenxiang Lei on 16/9/26.
//
*/

#include <stdlib.h>
#include <stdio.h>
#include "PriorityQueue.h"
/*
typedef struct node_FIFO{
    int F_NodeId;
    double timeEnteredQueue;
    double timeInQueue;
    double timeInSystem;
    struct node_FIFO *next;
} F_Node;

typedef struct node_PriorityQueue{
    double timestamp;
    F_Node *FNode;
    int stationId;
    struct node_PriorityQueue *next;
    struct node_PriorityQueue *prev;
    //struct node_FIFO *prev;
}P_Node;

typedef struct pqQueue{
	P_Node *head; 
	//P_Node *tail;
	//int size;
} P_Queue;
*/

P_Queue *pq_createQueue()
{
    P_Queue *q = (P_Queue*)malloc(sizeof(P_Queue));
    q->head = NULL;
    return q;
}
/*
P_Node *newNode(int Id, double timeSt)
{
    P_Node *temp = (P_Node*)malloc(sizeof(P_Node));
    temp->P_NodeId = Id;
    temp->timestamp = timeSt;
    temp->next = NULL;
    return temp; 
}*/


void pq_push(P_Queue *q, P_Node *p)
{
	p->prev = NULL;
	p->next = NULL;

	P_Node *temp = q->head;
    if (q->head == NULL ) {
        q->head = p;
        return;
    }
    //If we need to insert to very front of list
    if (p->timestamp < temp->timestamp){
        q->head = p;
        p->next = temp;
        temp->prev = p;
        return;
    }
    while ((temp->timestamp) <= (p->timestamp)){
        if (temp->next == NULL ) {
            temp->next = p;
            p->prev = temp;
            p->next = NULL;
            return;
        }
        temp = temp->next;
    }
    temp->prev->next = p;
    p->next = temp;
    p->prev = temp->prev;
    temp->prev = p;
}

P_Node *pq_pop(P_Queue *q)
{
	P_Node *firstNode = q->head;
    if (firstNode == NULL )
        return NULL;

    if (firstNode->next == NULL ){
        q->head = NULL;
        return firstNode;
    }
    else {
        P_Node *temp = firstNode->next;
        temp->prev = NULL;
        q->head = temp;
        return firstNode;
    }
 }

void pq_freeMemo(P_Queue *q) 
{
    P_Node *thisNode = q->head;
    while (thisNode != NULL) {
        P_Node *tmp = thisNode->next;
        free(thisNode);
        thisNode = tmp;
    }
    free(q);
}

F_Node *newNode(int Id, double timeEn)
{
    F_Node *temp = (F_Node*)malloc(sizeof(F_Node));
    temp->F_NodeId = Id;
    temp->timeEnteredQueue = timeEn;
    temp->next = NULL;
    return temp; 
}

P_Node *pq_Node(F_Node *fnode, int stationId, double timestamp)
{
    P_Node *temp = (P_Node*)malloc(sizeof(P_Node));
    temp->FNode = fnode;
    temp->stationId = stationId;
    temp->next = NULL;
    temp->prev = NULL;
    temp->timestamp = timestamp;
    return temp;
}





// Test
int main()
{
    P_Queue *q = pq_createQueue();
    F_Node *a = newNode(10,0.1);
    F_Node *b = newNode(20,0.2);
    F_Node *c = newNode(30,0.3);
    P_Node *aa = pq_Node(a, 1, 0.002);
    P_Node *bb = pq_Node(b, 1, 0.003);
    P_Node *cc = pq_Node(c, 1, 0.001);
    pq_push(q, aa);
    pq_push(q, bb);
    pq_push(q, cc);
    pq_pop(q);
    P_Node *n = pq_pop(q);
	printf("Dequeued item is %f", n->timestamp);

    return 0;
}








