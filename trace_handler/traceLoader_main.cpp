#include "../structDef.h"
#include "traceLoader.h"

int main(int argc, char *argv[]){

	string loadTracePath = argv[1];
	string opTracePath = argv[2];
	loadRecord(loadTracePath);
	loadRecord(opTracePath);
	printTable();
		
	return 0;
}