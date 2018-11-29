#ifndef __STORAGE_LAYER_H__  
#define __STORAGE_LAYER_H__ 

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
#include <ctime>
#include <thread> 
#include <mutex> 
#include "../structDef.h"
#include "../util/utilcpp.h"
#include "../trace_handler/traceLoader.h"

using namespace std;


typedef struct  StorageDeviceMeta_t{
	int serverID;
	int storageID;
	string deviceName;
	
	pair<int, long long> sdDescriptor; //v1: file descriptor, v2: last offset
	mutex offsetMutex;
	unique_lock<mutex> offsetLocker;
	
	//record related metadata
	map<string, map<time_t,  long long>> recordTable; //k1: objID, k2: timestamp, v: record offset	
	map<string, unique_lock<mutex>> recordLocker; //k1: objID, k2: lock
	map<string, mutex> recordMutex; //k1: objectID, k2: mutex
}StorageDeviceMeta;

typedef struct serverMeta_t{
	int serverID;
	int numStorage;
	map<int, StorageDeviceMeta> storageDevices; //k1: storage, v: storage deveces
}serverMeta;


typedef struct clusterStoreMeta_t{
	int numServer;
	map<int, serverMeta> server; //k1: server, v: storage deveces
}clusterStoreMeta;

#ifdef __cplusplus
extern "C" {
#endif
	void initCluster(int numServer, int dps);
	void cleanDevice();
	void printDevice();
	void writeRecords(int serverID, int storageID, char* val);
	// char* readRecords(int serverID, int storageID, char* in_objID);
	void readRecords(int serverID, int storageID, char* in_objID, char** out_record);
#ifdef __cplusplus
};
#endif


void initServer(serverMeta* server, int serverID, int numStorage);
void initDevice(StorageDeviceMeta* sd, int serverID, int storageID);
string readLine(int fd, long long offset);

#endif