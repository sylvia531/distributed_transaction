#include "../yac.h"

IOMsg* createStoreMsg(int from, int to, int type, void* msg, int msgSize){
	IOMsg* strMsg  = (IOMsg*)malloc(sizeof(IOMsg));
	strMsg->target = to;
	strMsg->from = from;
	strMsg->msgType = type;
	strMsg->msgSize = msgSize;
	strMsg->content = msg;
	
	if(DEBUG){
		printf("In createStoreMsg, malloc strMsg msg: %lx, related data address: %lx, %lx, send to: server_%d\n", strMsg, msg, strMsg->content, to);
		// printf("content: %s\n", (char*)msg);
	}
	return strMsg;
}

void pushIntoPhyMQ(char* name, IOMsg* sendReq){
	if(DEBUG){
		printf("In pushIntoPhyMQ: %s sendReq: %lx\n", name, sendReq);
	}
	
	int destID = sendReq->target;
	
	SemaphoreWait(sem_PhyMQFull[destID]);
	
	SemaphoreWait(sem_PhyMQAtomic[destID]);
	insertPhyMsgQueue(destID, sendReq);
	SemaphoreSignal(sem_PhyMQAtomic[destID]);
		
	//signal the sem_memrequest
	SemaphoreSignal(sem_WakePhyServer[destID]);  // Signal  memory controller to handle this request. 
}