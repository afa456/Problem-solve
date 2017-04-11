#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "Queue.c"

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

int *Bread_First_Search(Node **graph_node, int s, int node) 
{
	int *ret = NULL;
    Queue q;
    queue_init(&q);
    int dist = -1;
    queue_push(&q, &node);
    int marked[s];
    for (int i = 0; i < s; i++) 
    {
        marked[i] = 0;
    }
    marked[node] = 1;
    while (queue_size(&q) > 0) 
    {
        dist++;
        int node_size = queue_size(&q);
        int *nodes[node_size];  //numbers of nodes at this distantce level
        for (int i = 0; i < node_size; i++) 
        {
            nodes[i] = queue_pop(&q);
            Node *p = graph_node[*nodes[i]];
            while (p != NULL) {
                if (!marked[p->id]) 
                {
                    queue_push(&q, &p->id);
                    marked[p->id] = 1;
                }
                p = p->next;
            }
        }
 		if (queue_size(&q) == 0) {  // most distant nodes
			ret = (int *) malloc((node_size + 2) * sizeof(int));
			ret[0] = dist;
			ret[1] = node_size;
			for (int i = 0; i < node_size; i++) {
				ret[i + 2] = *nodes[i];
			}
		}     
    }
    return ret;
}

int main(void)
{
	int size = 0;
	FILE *fp = fopen("10000tsv.tsv", "r");
	if(fp == NULL)
   {
      printf("\n file opening failed ");
      return -1 ;
   }
	fscanf(fp, "%d", &size);
	//printf("%d\n", *size);
    Node **graph_node = (Node **) malloc(size * sizeof(Node *));
    for (int i = 0; i < size; i++) {
    	graph_node[i] = NULL;  // initialize node
    }
    int n1, n2;
    while (fscanf(fp, "%d %d", &n1, &n2) != EOF) {
    	// add to n1 node next
    	Node *node = (Node *) malloc(sizeof(Node));
    	node->id = n2;
    	node->next = NULL; 
    	if (graph_node[n1] == NULL)
    		graph_node[n1] = node;
    	else {
			node->next = graph_node[n1]->next;
			graph_node[n1]->next = node;
    	}
    	// add to n2 node next
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
    //print_graph(graph_node, size);
    
    FILE *foutp = NULL;
    foutp = fopen("outgraph1.txt", "w");
    if (foutp == NULL) {
    	printf("\n file opening failed ");
		return -1;
    }

    int *max_dist[size];
	int diameter = 0;
	for (int i = 0; i < size; i++) 
	{
		max_dist[i] = Bread_First_Search(graph_node, size, i);
		if (max_dist[i][0] > diameter) 
			diameter = max_dist[i][0];
	}
	printf("the max diameter is: %d\n", diameter );
	fprintf(foutp, "%d\n", diameter);

	for (int i = 0; i < size; i++) {
		//if (fp == NULL)
			printf("%d, %d, (", i, max_dist[i][0]);
			fprintf(foutp, "%d, %d, (", i, max_dist[i][0]);

		//else
		//	fprintf(fp, "%d: %d, [", i, max_dist[i][0]);
		for (int j = 0; j < max_dist[i][1]; j++) 
		{
			//if (fp == NULL)
				printf("%d", max_dist[i][j + 2]);
				fprintf(foutp, "%d", max_dist[i][j+2]);

				if (j < max_dist[i][1] - 1) 
				{
				//if (fp == NULL)
					printf(", ");
					fprintf(foutp,",  ");
				}
		}
		printf(")\n");
		fprintf(foutp,")\n");
	}

	for (int i = 0; i < size; i++) 
	{
		free(graph_node[i]);
		graph_node[i] = NULL;
	}
	free(graph_node);

    fclose(fp);
    fclose(foutp);
	return 0;
}