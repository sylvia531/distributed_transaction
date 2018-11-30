#include "yac.h"
#include "../util/utilc.h"

void phyServer(){
	int i = 0;
	int j = 0;
	psInput* input = (psInput*)ActivityGetArg(ME);
	int serverID = input->psID;

	
	if (1){
		printf("\nserver_%d, Activated at time %5.2f\n", serverID);
	}
	
	while(1){
		
		SemaphoreWait(sem_WakePhyServer[serverID]);
		
		if (DEBUG){
			printf("Server_%d: wake up at time %5.2f\n", serverID, GetSimTime());
		}
		
		//Handle received msage
		handleMsg(serverID);
	}

}

void handleMsg(int serverID){
	int i =0;
	int j = 0;
	
	//1. Get request from queue
	IOMsg* recvReq;

	SemaphoreWait(sem_PhyMQAtomic[serverID]);
	getFromPhyMsgQueue(serverID, &recvReq);
	SemaphoreSignal(sem_PhyMQAtomic[serverID]);
	
	SemaphoreSignal(sem_PhyMQFull[serverID]);
	
	char* msg = (char*)recvReq->content;
	
	//2. Do the transmission delay
	double transmitTime = 0.0;
	transmitTime = normDis(RC_SEND_DATA, RC_SEND_DATA_STD);
	ProcessDelay(transmitTime);
	
	if(DEBUG){
		printf("In handleMsg: server_%d, receive IOMsg %lx from server_%d with content address %lx, at time %5.2f\n", serverID, recvReq, recvReq->from, recvReq->content, GetSimTime());
		// printf("Content: %s\n", msg);
	}
	
	//3. Write content into storage file
	writeRecords(serverID, 0, msg);
	incFinish(); //record finish
	
	free(recvReq->content);
	free(recvReq);
}