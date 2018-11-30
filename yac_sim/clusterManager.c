#include "yac.h"


void clusterManag(){
	int i = 0;
	int j = 0;
	cmInput* input = (cmInput*)ActivityGetArg(ME);
	int clusterManagID = input->cmID;
	char* traceName = input->traceName;
	int numServer = input->numServer;
	
	if (DEBUG){
		printf("\nCluster Manager %d with trace name %s, number of server: %d, Activated at time %5.2f\n", clusterManagID, traceName, numServer, GetSimTime());
	}
	
	FILE *fTrace = fopen(traceName, "r");
	char tmpLine[MAX_LINE_SIZE]; 
	while(!feof(fTrace)){
		fgets(tmpLine, MAX_LINE_SIZE, fTrace);
		if(tmpLine[0] == '"' || tmpLine[0] == '*' || tmpLine[0] == '['){
			continue;
		}
		
		//record release
		incRelease();

		//Create send msg
		int msgSize = strlen(tmpLine)+1;
		tmpLine[msgSize-1] = '\0';
		int serverID = getRecordServer(tmpLine, numServer);
		void* msg = (void*)malloc(msgSize*sizeof(char));
		memcpy(msg,tmpLine,msgSize*sizeof(char));
		IOMsg* strMsg = createStoreMsg(-1, serverID, STORE, msg, msgSize);
		
		
		//cluster send store msg to target server
		pushIntoPhyMQ("Cluster store data", strMsg);
		
	}
	
	fclose(fTrace);

}