#ifndef __YAC_H__  
#define __YAC_H__

#include "sim.h"
#include "../structDef.h"



//Message Queue
#define QUEUE_CAP 128

//Simulation parameters
#define SIMULATION_TIME 500000.0
#define CLOCK_CYCLE 1.0
#define RC_SEND_DATA 4.0
#define RC_SEND_DATA_STD 0.411


typedef struct cmInput_t{
	int cmID;
	int numServer;
	char* traceName;	
}cmInput;

typedef struct psInput_t{
	int psID;
}psInput;



//Process
PROCESS *ClusterManag[NUM_CLUSTER_MANAGER];
PROCESS *PhyServer[MAX_NUM_SERVER];

//semaphor
SEMAPHORE *sem_PhyMQFull[MAX_NUM_SERVER]; //physical node i inner msg queue full
SEMAPHORE *sem_PhyMQAtomic[MAX_NUM_SERVER]; //atomic access physical node i inner msg queue 
SEMAPHORE *sem_WakePhyServer[MAX_NUM_SERVER]; //wake up physical node i controller


//Predefine functions
//msgOprt.c:
IOMsg* createStoreMsg(int from, int to, int type, void* msg, int msgSize);
void pushIntoPhyMQ(char* name, IOMsg* sendReq);

//clusterManager.c
void clusterManag();

//phyServer.c
void phyServer();
void handleMsg(int serverID);
#endif