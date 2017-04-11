#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Queue.h"

typedef struct new_node {
	int id;
	struct new_node *next;

} Node;

void print_graph(Node **graph_node, int s) {
	printf("%d\n", s);
	if (graph_node == NULL) {
		printf("NULL\n");
		return;
	}
	for (int i = 0; i < s; i++) {
		printf("%d: ", i);
		Node *p = graph_node[i];
		while (p != NULL) {
			printf("%d ", p->id);
			p = p->next;
		}
		printf("\n");
	}
}

int *bfs(Node **graph, int s, int node) {
	Queue q;
	q_init(&q);
	int dist = -1;
	q_push(&q, node);
	int *ret = NULL;
	bool visited[s];
	for (int i = 0; i < s; i++) {
		visited[i] = false;
	}
	visited[node] = true;
	while (q_size(&q) > 0) {
		dist++;
		int siz = q_size(&q);
		int nodes[siz];  /* nodes at this level */
		for (int i = 0; i < siz; i++) {
			nodes[i] = (int) q_pop(&q);
			Node *p = graph[nodes[i]];
			while (p != NULL) {
				if (!visited[p->id]) {
					q_push(&q, p->id);
					visited[p->id] = true;
				}
				p = p->next;
			}
		}
		if (q_size(&q) == 0) {  /* most distant nodes*/
			ret = (int *) malloc((siz + 2) * sizeof(int));
			ret[0] = dist;
			ret[1] = siz;
			int OFFSET = 2;
			for (int i = 0; i < siz; i++) {
				ret[i + OFFSET] = nodes[i];
			}
		}
	}
	return ret;
}

int main(void)
{
	int *size;
	FILE *fp = fopen("graph.txt", "r");
	if(fp == NULL)
   {
      printf("\n file opening failed ");
      return -1 ;
   }
	fscanf(fp, "%d", size);
	/*printf("%d\n", *size);*/
    Node **graph_node = (Node **) malloc(*size * sizeof(Node *));
    for (int i = 0; i < *size; i++) {
    	graph_node[i] = NULL;  /* initialize node */
    }
    int n1, n2;
    while (fscanf(fp, "%d %d", &n1, &n2) != EOF) {
    	/*printf("%d, %d\n", n1, n2);
    	 add to n1's list*/
    	Node *node = (Node *) malloc(sizeof(Node));
    	node->id = n2;
    	node->next = NULL; 
    	if (graph_node[n1] == NULL)
    		graph_node[n1] = node;
    	else {
			node->next = graph_node[n1]->next;
			graph_node[n1]->next = node;
    	}
    	/* add to n2's list*/
    	node = (Node *) malloc(sizeof(Node));
    	node->id = n1;
    	node->next = NULL;
    	if (graph_node[n2] == NULL)
    		graph_node[n2] = node;
    	else {
			node->next = graph_node[n2]->next;
			graph_node[n2]->next = node;
    	}
    }

    print_graph(graph_node, *size);


    fclose(fp);
	return 0;
}

/*
 * Queue.c
 *
 * Created on: Sep 16, 2016
 *   
 */

void q_init(Queue *q) {
	q->head = q->tail = NULL;
	q->size = 0;
}

int q_size(Queue *q) {
	return q->size;
}

void q_push(Queue *q, void *p) {
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

void *q_peek(Queue *q) {
	void *ret = NULL;
	if (q->size == 0) {
		printf("The Queue is empty\n");
		return ret;
	}
	return q->head->data;
}

void *q_pop(Queue *q) {
	void *ret = NULL;
	if (q->size == 0) {
		printf("Cannot pop from an empty Queue\n");
		return ret;
	}
	QNode *temp = q->head;
	ret = temp->data;
	q->head = temp->next;
	if (temp == q->tail)  /* important!!*/
		q->tail = NULL;
	free(temp);
	q->size--;
	return ret;
}

void q_clear(Queue *q, void (*free_data)(void *)) {
	while (q->size > 0) {
		QNode *temp = q->head;
		q->head = temp->next;
		free_data(temp->data);
		free(temp);
		q->size--;
	}
	q->head = q->tail = NULL;
}

