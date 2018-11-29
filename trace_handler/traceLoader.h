#ifndef __TRACE_LOADER_H__  
#define __TRACE_LOADER_H__ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include "../structDef.h"
#include "../util/utilcpp.h"
#include "../storage_layer/storageLayer.h"

using namespace std;



//ycsb benchmark record
typedef struct ycsbRecord_t{
	string objID;
	int serverID;
	int storageID;
	string op;
	string tableName;
	int isRead;
	map<string, string> content; //key: field, value: content
	
}ycsbRecord;

#ifdef __cplusplus
extern "C" {
#endif
	void loadRecord(char* filename, int numServer);
	void loadDataToStorage(char* filename, int numServer);
	void printTable();

	
#ifdef __cplusplus
};
#endif


ycsbRecord parseRecord(string r, int numServer);


#endif