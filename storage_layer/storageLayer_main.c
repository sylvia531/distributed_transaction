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

int main(int argc, char *argv[]){
	
	// int numServer = atoi(argv[3]);
	int numServer = 3;
	int numDevPerServer = 1;
	
	char* loadTracePath = argv[1];
	
	initCluster(numServer, numDevPerServer);
	printDevice();
	
	loadDataToStorage(loadTracePath, numServer);
	
	if(1){
		char* objID = "user4409142221109489457";
		int serverID = genStrHash(objID)%numServer;
		int storageID = 0;
		printf("Read data from serverID: %d storageID: %d\n", serverID, storageID);
		
		// char* content = (char*)malloc(sizeof(char));
		// content= readRecords(serverID, storageID, objID);
		
		char* content;
		readRecords(serverID, storageID, objID, &content);
		printf("%s\n", content);
		
		free(content);

	}
	
	cleanDevice();

	return 0;
}