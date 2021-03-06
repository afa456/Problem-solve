/*
 * Queue.c
 *
 * Created on: Sep 16, 2016
 *   
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct _q_node {
	int *data;  // implement a generic queue by using void pointer
	struct _q_node *next;
} QNode;

typedef struct {
	QNode *head, *tail;
	int size;
} Queue;


void queue_init(Queue *q) {
	q->head = q->tail = NULL;
	q->size = 0;
}

int queue_size(Queue *q) {
	return q->size;
}

void queue_push(Queue *q, int *p) {
	QNode *new_node = (QNode *) malloc(sizeof(QNode));
	new_node->data = p;
	if (q->tail == NULL)
		q->head = q->tail = new_node;
	else {
		q->tail->next = new_node;
		q->tail = new_node;
	}
	q->size++;
}

void *queue_pop(Queue *q) {
	void *ret = NULL;
	if (q->size == 0) {
		printf("Cannot pop from an empty Queue\n");
		return ret;
	}
	QNode *temp = q->head;
	ret = temp->data;
	q->head = temp->next;
	if (temp == q->tail)  // important!!
		q->tail = NULL;
	free(temp);
	q->size--;
	return ret;
}

void queue_clear(Queue *q, void (*free_data)(void *)) {
	while (q->size > 0) {
		QNode *temp = q->head;
		q->head = temp->next;
		free_data(temp->data);
		free(temp);
		q->size--;
	}
	q->head = q->tail = NULL;
}


int main(void)
{
	Queue q;
    queue_init(&q);

    int node = 3;
    queue_push(&q, &node);
    int *res = queue_pop(&q);
    printf("%d\n", *res );

	return 0;
}