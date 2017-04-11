/*
 * main.c
 *
 *  Created on: 2016年9月25日
 *      Author: Wenxiang Lei
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ROWS 100
#define COLUMNS 100
#define STEPS 1000
#define PROB_F 0.05
/*
 The PROB_F means probility of each cell catching fire, need to manually change from 0.01 to 0.05
 */

double get_rand() {
    return rand()/(double)(RAND_MAX);
}
void initialize(int grid[ROWS][COLUMNS]){
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			grid[i][j]=0;
		}
	}
}

void growth_phase(int grid[ROWS][COLUMNS], double PROB_G) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
        	double p = get_rand();
            if (grid[i][j] != 1 && p < PROB_G)
            	grid[i][j]=1;
        }
    }
}

/*
Using fire_dfs function to search each cell adjacent to the cell that catch fire.
 */
void fire_dfs(int grid[ROWS][COLUMNS], int i, int j){
	if(i<0 || j<0 || i >= ROWS || j >= COLUMNS || grid[i][j]==0)
		return;
    grid[i][j] = 0;
    fire_dfs(grid, i + 1, j);
    fire_dfs(grid, i - 1, j);
    fire_dfs(grid, i, j + 1);
    fire_dfs(grid, i, j - 1);
}

void fire_phase(int grid[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
        	double f = get_rand();
            if (grid[i][j] == 1 && f < PROB_F)
                fire_dfs(grid, i, j);
        }
    }
}



int count_trees(int grid[ROWS][COLUMNS]) {
    int count = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (grid[i][j] == 1)
                count++;
        }
    }
    return count;
}

/*
print function is to prints the state of the forest after each time step
 */

void print_forest(int grid[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (grid[i][j] == 1)
                printf("T");
            else
                printf(".");
        }
        printf("\n");
    }
    printf("\n");
}

int main(void){
	int grid[ROWS][COLUMNS];
	srand((unsigned)time(0));
    initialize(grid);
    for(int j=1; j<100; j++){
        double prob = j/(double) (100);
        int Avg = 0;
        int sum=0;
        for(int i=0;i<STEPS;i++){
            growth_phase(grid, prob);
            fire_phase(grid);
            int a = count_trees(grid); 
            sum += a;
        }
        Avg = sum/STEPS;
        printf("the average occupied cells is %d for probability %f \n", Avg, prob);
    }
	return 0;
}


