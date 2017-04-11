/*
//  graph.c
//  
//  Created by Wenxiang Lei on 17/10/26.
//
*/

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Queue.h"


Node **read_graph(const char *filename) {
	int *siz
	FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
      	printf("\n file opening failed ");
		return NULL;
    }
    // first line is the total number of nodes
    fscanf(fp, "%d", siz);
    Node **graph = (Node **) malloc(*siz * sizeof(Node *));
    for (int i = 0; i < *siz; i++) {
    	graph[i] = NULL;  // initialize node
    }
    // construct the graph
    int id1 = 0, id2 = 0;
    while (fscanf(fp, "%d, %d", &id1, &id2) != EOF) {
    	// add to id1's list
    	Node *node = (Node *) malloc(sizeof(Node));
    	node->id = id2;
    	node->next = NULL; 
    	if (graph[id1] == NULL)
    		graph[id1] = node;
    	else {
			node->next = graph[id1]->next;
			graph[id1]->next = node;
    	}
    	// add to id2's list
    	node = (Node *) malloc(sizeof(Node));
    	node->id = id1;
    	node->next = NULL;
    	if (graph[id2] == NULL)
    		graph[id2] = node;
    	else {
			node->next = graph[id2]->next;
			graph[id2]->next = node;
    	}
    }
    fclose(fp);
    return graph;  // CANNOT PASS AS A PARAMETER (PASS BY VALUE)
}

void print_graph(Node **graph, int N) {
	printf("%d\n", N);
	if (graph == NULL) {
		printf("NULL\n");
		return;
	}
	for (int i = 0; i < N; i++) {
		printf("%d: ", i);
		Node *p = graph[i];
		while (p != NULL) {
			printf("%d ", p->id);
			p = p->next;
		}
		printf("\n");
	}
}

int main(void)
{
	/* code */
	int N = 0;
	char *graph_filename = "graph.csv";
	Node **graph = read_graph(graph_filename, &N);
	print_graph(graph, N);
	return 0;
}













