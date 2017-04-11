/*
//  Ramdon.c
//  
//  Created by Wenxiang Lei on 16/9/26.
//
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "Ramdon.h"

double urand() 
{
	srand(time(NULL));
	return (double)rand() / ((double)RAND_MAX + 1);
}

double randexp(double umean) 
{
	return -umean * (log(1.0 - urand()));
}

int main()
{
	
	double r = urand();
	printf("%f\n", r );
	return 0;
}