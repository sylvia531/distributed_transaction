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

	char* loadTracePath = argv[1];
	char* opTracePath = argv[2];
	int numServer = atoi(argv[3]);
	loadRecord(loadTracePath, numServer);
	loadRecord(opTracePath, numServer);
	printTable();
		
	return 0;
}