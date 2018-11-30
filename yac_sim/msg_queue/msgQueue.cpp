#include "msgQueue.h"

map<int, queue<IOMsg*> > phyMsgQG; //queue to handle request to phyCtroller. k1: phyID
vector<bool> phyMsgQGIsAllocated(MAX_LINE_SIZE, FALSE);



void makePhyMsgQueue(int serverID){
	if(serverID > MAX_NUM_SERVER){
		printf("ERROR: In msgQueue.cpp => makePhyMsgQueue: server msg queue Overflow!\n");
		exit(1);
	}
		
	if (phyMsgQGIsAllocated[serverID] == TRUE) {
		printf("ERROR: In msgQueue.cpp => makePhyMsgQueue: Trying to allocate a duplicate server msg queue with same id: %d\n", serverID);
		exit(1);
	}
	
	phyMsgQGIsAllocated[serverID] = TRUE;
	queue<IOMsg*> tmp;
	phyMsgQG[serverID] = tmp;
	
	if (0){
		printf("Make server msg queue %d \n", serverID);
	}
}

void insertPhyMsgQueue(int serverID, IOMsg* data){
	if(serverID > MAX_NUM_SERVER){
		printf("ERROR: In msgQueue.cpp => insertPhyMsgQueue: server msg queue Overflow!\n");
		exit(1);
	}
		
	if (phyMsgQGIsAllocated[serverID] == FALSE) {
		printf("ERROR: In msgQueue.c => insertPhyMsgQueue: Inserting into non-existent queue %d\n", serverID);
		exit(1);
	}
	
	phyMsgQG[serverID].push(data);
}


void getFromPhyMsgQueue(int serverID, IOMsg** out){
	if(serverID > MAX_NUM_SERVER){
		printf("ERROR: In msgQueue.c => getFromPhyMsgQueue: server msg queue group Overflow!\n");
		exit(1);
	}
		
	if (phyMsgQGIsAllocated[serverID] == FALSE) {
		printf("ERROR: In msgQueue.c => getFromPhyMsgQueue: remove from non-existent queue %d\n", serverID);
		exit(1);
	}
	
	*out = phyMsgQG[serverID].front();
	phyMsgQG[serverID].pop();

}

int getSizeOfPhyMsgQueue(int serverID){
	if(serverID > MAX_NUM_SERVER){
		printf("ERROR: In msgQueue.c => getSizeOfPhyMsgQueue: server msg queue group Overflow!\n");
		exit(1);
	}
		
	if (phyMsgQGIsAllocated[serverID] == FALSE) {
		printf("ERROR: In msgQueue.c => getSizeOfPhyMsgQueue: get size from non-existent queue %d\n", serverID);
		exit(1);
	}
	
	return phyMsgQG[serverID].size();
}

