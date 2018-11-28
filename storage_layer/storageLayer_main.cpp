#include "storageLayer.h"

int main(int argc, char *argv[]){
	
	// int numServer = atoi(argv[3]);
	int numServer = 3;
	int numDevPerServer = 1;
	
	string loadTracePath = argv[1];
	
	initCluster(numServer, numDevPerServer);
	printDevice();
	
	loadDataToStorage(loadTracePath, numServer);
	
	if(1){
		string objID = "user4409142221109489457";
		int serverID = genStrHash(objID)%numServer;
		int storageID = 0;
		cout<<"Read data from serverID: "<<serverID<<" storageID: "<<storageID<<endl;
		string content = readRecords(serverID, storageID, objID);
		cout<<content<<endl;
	}
	
	cleanDevice();

	return 0;
}