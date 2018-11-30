#ifndef __STRUCT_DEF_H__  
#define __STRUCT_DEF_H__ 

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <time.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <unistd.h>
#include <errno.h>

/**Predefined Parameters*/
#define TRUE 1
#define FALSE 0

#define DEBUG TRUE

#define MAX_LINE_SIZE 10240

//System parameters
#define NUM_CLUSTER_MANAGER 1
#define MAX_NUM_SERVER 3
#define DEV_PER_SERVER 1

//Msg type
#define STORE 1

/**Structures*/
//msg for communication between nodes
typedef struct IOMsg_t{
	int target; //server id
	int from; //-1 cluster, >0 server
	int msgType;
	int msgSize;
	void* content; 
}IOMsg;

typedef struct statistic_t{
	int numRelease;
	int numFinish;
}statistic;

//Statistic operations
void initialStatistic();
void incRelease();
void incFinish();
void printStatistic();


#endif