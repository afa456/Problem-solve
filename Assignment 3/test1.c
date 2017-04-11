#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "Queue.c"

typedef struct new_node {
    int id;
    struct new_node *next;

} Node;

int func(){
    int dist = 10;

    return dist;
}


int Bread_First_Search(Node **graph_node, int s, int node) 
{
    Queue q;
    queue_init(&q);
    int dist = -1;
    queue_push(&q, &node);
    int visited[s];
    for (int i = 0; i < s; i++) 
    {
        visited[i] = 0;
    }
    visited[node] = 1;
    printf("%d\n", visited[0]);
    
    /*dist++;
    int node_size = queue_size(&q);
    printf("node_size %d\n", node_size);
    int *nodes[node_size]; 

    nodes[0] = queue_pop(&q);
    printf("%d\n", *nodes[0]);
    //Node *p = graph[*nodes[0]];

    for (int i = 0; i < node_size; i++) 
    {

        Node *p = graph[*nodes[i]];
        while (p != NULL) {
            if (visited[p->id] != 1) 
            {
                queue_push(&q, &p->id);
                visited[p->id] = 1;
            }
            p = p->next;
        }
    }*/

    while (queue_size(&q) > 0) 
    {
        dist++;
        int node_size = queue_size(&q);
        int *nodes[node_size];  //numbers of nodes at this distantce
        for (int i = 0; i < node_size; i++) 
        {
            nodes[i] = queue_pop(&q);
            Node *p = graph_node[*nodes[i]];
            while (p != NULL) {
                if (!visited[p->id]) 
                {
                    queue_push(&q, &p->id);
                    visited[p->id] = 1;
                }
                p = p->next;
            }
        }
    }
    return dist;
}

int main()
{
    int size;
    FILE *fp = fopen("graph.txt", "r");
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
        //printf("%d, %d\n", n1, n2);
        // add to n1's list
        Node *node = (Node *) malloc(sizeof(Node));
        node->id = n2;
        node->next = NULL; 
        if (graph_node[n1] == NULL)
            graph_node[n1] = node;
        else {
            node->next = graph_node[n1]->next;
            graph_node[n1]->next = node;
        }
        // add to n2's list
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

    int max_dist[30];
    int diameter = 0;
    max_dist[1] = Bread_First_Search(graph_node, 30, 1);
    printf("%d\n", max_dist[1]);

    fclose(fp);

    int q = 0, w = 3;
    q = func();
    printf("%d\n", q);


    return 0;
}