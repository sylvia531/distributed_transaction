#include "structDef.h"

statistic sum;
void initialStatistic(){
	sum.numRelease = 0;
	sum.numFinish = 0;
}

void incRelease(){
	sum.numRelease++;
}

void incFinish(){
	sum.numFinish++;
}

void printStatistic(){
	printf("Simulation Summary:\n");
	printf("Number of release: %d\n", sum.numRelease);
	printf("Number of finish: %d\n", sum.numFinish);
}