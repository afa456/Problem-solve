/*
//  PriorityQueue.h
//  
//  Created by Wenxiang Lei on 16/9/26.
//
*/

#ifndef PriorityQueue_h
#define PriorityQueue_h
#include <stdio.h>

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
}P_Node;

typedef struct pqQueue{
	P_Node *head; 
} P_Queue;

P_Queue *pq_createQueue();
void pq_push(P_Queue *q, P_Node *p);
P_Node *pq_pop(P_Queue *q);
void pq_freeMemo(P_Queue *q); 
F_Node *newNode(int Id, double timeEn);
P_Node *pq_Node(F_Node *fnode, int stationId, double timestamp);

#endif /* PriorityQueue_h */
