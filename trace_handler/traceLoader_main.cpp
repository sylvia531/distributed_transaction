#include "traceLoader.h"

int main(int argc, char *argv[]){

	string loadTracePath = argv[1];
	string opTracePath = argv[2];
	int numServer = atoi(argv[3]);
	loadRecord(loadTracePath, numServer);
	loadRecord(opTracePath, numServer);
	printTable();
		
	return 0;
}