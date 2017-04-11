//
//  main.c
//  6010A3
//
//  Created by Yuzhou Li on 10/10/16.
//  Copyright © 2016 Yuzhou Li. All rights reserved.
//

#include <stdio.h>
#include "time.h"
#include "string.h"
#include "stdlib.h"


/*
 The Node in this program is stored in an array called Graph. Other arrays such as node, numberofedge is used for track the generation steps. Array numberofedge has N elements, and each of them reveals the number of edges correspond to the node which has the label the same as array index.
 */




/*
 This function is used for initialize the graph. Generating n0 nodes and connect them with each other.
 */

void initial(int N,int n0,int node[],int numberofedge[],int graph[N][2], int totaldeg){
    int count = 0;
    for (int i=0;i<n0;i++){
        for (int j=i+1;j<n0;j++){
            node[i] = 1;
            node[j] = 1;
            numberofedge[i]++;
            numberofedge[j]++;
            totaldeg+=2;
            printf("This is a node, node %d, and connected %d\n",i,j);
            graph[count][0] = i;
            graph[count][1] = j;
            count++;
        }
    }
}

/*
 This function is used for generating a random picked node, according to the rich get richer. Array prob is used for calculating the degree proportion of a node in the graph. Parameter totaldeg is used for showing the total degree of current existing graph.
 */

int randompick(int N,float prob[], int numberofedge[], int totaldeg){
    for(int k=0;k<N;k++){
        prob[k] = ((float)numberofedge[k]/(float)totaldeg);
        //printf("%f",prob[k]);
    }
    int flag = 0;
    int ii = 0;
    float acc = 0.0;
    float rd = ((float)rand()/(float)(RAND_MAX));
    //printf("%f\n",rd);
    while (flag==0){
        acc += prob[ii];
        ii++;
        if(acc>rd){
            flag = 1;
        }
        
    }
    printf("ii-1 is %d\n",ii-1);
    return ii-1;
}


/*
 This function is used for inserting a new node to the graph.
 */

void insertnewnode(int N, int node[],int numberofedge[],int graph[N][2],int N0,int totaldeg, float prob[]){
    for(int n = N0;n<N;n++){
        node[n] = 1;
        int selectednode = randompick(N,prob,numberofedge,totaldeg);
        while (selectednode>=n){
            selectednode = randompick(N,prob,numberofedge,totaldeg);
        }
        numberofedge[n]++;
        printf("the selected node is %d\n",selectednode);
        numberofedge[selectednode]++;
        
        totaldeg+=2;
        printf("This is a new node, node %d, and connected %d\n",n,selectednode);
        graph[n][0] = n;
        graph[n][1] = selectednode;
    }
}

/*
 This function is designed for finding the node which has the max degree.
 */
int findmaxdegree(int numberofedge[],int N){
    int max = numberofedge[0];
    for (int ii = 0;ii<N;ii++){
        if(numberofedge[ii]>max){
            max = numberofedge[ii];
        }
    }
    return max;
}


/*
 This function is used for printing an array.
 */
void printarr(int a[], int x){
    for (int i=0;i<x-1;i++){
        printf("%d,",a[i]);
    }
    printf("%d",a[x-1]);
    printf("\n");
}


/*
 This function is used for generating the statistical data used for plots.
 */

void histinfo(int numberofedge[],int N){
    FILE *fp;
    //fp = fopen("DegreeDistribution.csv", "w+");
    //char header[2000] = "Degree,Number of Nodes,Detail\n";
    int max = findmaxdegree(numberofedge,N);
    for (int i = 1;i<=max;i++){
        int numN = 0;
        for(int j=0;j<N;j++){
            if (numberofedge[j]==i){
                numN++;
            }
        }
        if (numN!=0){
            int detailnumN[numN];
            int count = 0;
            for (int x = 0; x<N;x++){
                if(numberofedge[x]==i){
                    detailnumN[count]=x;
                    count++;
                }
            }
            printf("The degree %d has %d nodes, including ",i,numN);
            printarr(detailnumN, numN);
            /*fprintf(fp, "%d,%d,",i,numN);
            for(int ss = 0;ss<numN-1;ss++){
                fprintf(fp,"%d,",detailnumN[ss]);
            }
            fprintf(fp, "%d\n",detailnumN[numN-1]);*/
        }
        
    }
    //fclose(fp);
}


/*
 This function is used for printing the graph into csv file.
 */

void printoutgraph(int N,const char* ag2,int graph[N][2]){
    FILE *file;
    file = fopen(ag2, "w+");
    fprintf(file, "%d\n",N);
    for(int i=0;i<N;i++){
        int p1 = graph[i][0];
        int p2 = graph[i][1];
        printf("%d\t%d\n",p1,p2);
        fprintf(file, "%d\t%d\n",p1,p2);
    }
    fclose(file);
}


int main(int argc, const char * argv[]) {
    
    srand((unsigned int)time(NULL));
    int N0 = 3;
    
    const char* ag1 = argv[1];
    int N = atoi(ag1);
    const char* ag2 = argv[2];
    
    /*
     int N = 50000;
     const char* ag2 = "output.csv";
     */
    int node[N];
    int numberofedge[N];
    int totaldeg = 0;
    float prob[N];
    int graph[N][2];
    
    
    
    initial(N, N0, node, numberofedge, graph, totaldeg);
    insertnewnode(N, node, numberofedge, graph, N0, totaldeg, prob);
    // insert code here...
    //printf("%d,%d,%d\n",numberofedge[0],numberofedge[1],numberofedge[2]);
    /*
     for(int z = 0; z<N;z++){
     printf("The node %d has %d Edges\n",z,numberofedge[z]);
     printf("ij =%d,%d\n ",graph[z][0],graph[z][1]);
     }
     */
    //histinfo(numberofedge, N);
    printoutgraph(N, ag2, graph);
    
    return 0;
}