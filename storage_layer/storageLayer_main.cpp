#include "../structDef.h"
#include "../trace_handler/traceLoader.h"
#include "storageLayer.h"

int main(int argc, char *argv[]){
	initDevice(3, 1);
	printDevice();
	
	
	int recordCounter = 0;
	string loadTracePath = argv[1];
	FILE *fTrace = fopen((char*)loadTracePath.c_str(), "r");
	char tmpLine[MAX_LINE_SIZE]; 
	while(!feof(fTrace)){
		if(recordCounter<10){
			fgets(tmpLine, MAX_LINE_SIZE, fTrace);
			if(tmpLine[0] == '"' || tmpLine[0] == '*' || tmpLine[0] == '['){
				continue;
			}
			string tmpString(tmpLine);
			ycsbRecord tmpRecord = parseRecord(tmpString);
			string content = tmpRecord.objID+" "+tmpRecord.tableName;
			for(auto f: tmpRecord.content){
				content = content+" "+f.first+"="+f.second;
			}
			writeRecords(0, 0, content);
			
			recordCounter++;
		}
		else{
			break;
		}
	}
	
	cleanDevice();

	return 0;
}