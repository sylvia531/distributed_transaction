#include "../structDef.h"
#include "../trace_handler/traceLoader.h"
#include "storageLayer.h"

int main(int argc, char *argv[]){
	
	// int numServer = atoi(argv[3]);
	int numServer = 3;
	int numDevPerServer = 1;
	
	string loadTracePath = argv[1];
	
	initDevice(numServer, numDevPerServer);
	printDevice();
	
	
	int recordCounter = 0;	
	FILE *fTrace = fopen((char*)loadTracePath.c_str(), "r");
	char tmpLine[MAX_LINE_SIZE]; 
	while(!feof(fTrace)){
		if(recordCounter<10){
			fgets(tmpLine, MAX_LINE_SIZE, fTrace);
			if(tmpLine[0] == '"' || tmpLine[0] == '*' || tmpLine[0] == '['){
				continue;
			}
			string tmpString(tmpLine);
			ycsbRecord tmpRecord = parseRecord(tmpString, numServer);
			string content = tmpRecord.objID+" "+tmpRecord.tableName;
			for(auto f: tmpRecord.content){
				content = content+" "+f.first+"="+f.second;
			}
			writeRecords(tmpRecord.serverID, tmpRecord.storageID, content);
			
			recordCounter++;
		}
		else{
			break;
		}
	}
	
	cleanDevice();

	return 0;
}