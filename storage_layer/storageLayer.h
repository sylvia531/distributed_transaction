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
#include "../structDef.h"
#include "../util/util_cpp.h"
#include "../trace_handler/traceLoader.h"

using namespace std;

void initDevice(int numServer, int dps);
void cleanDevice();
void printDevice();
void writeRecords(int serverID, int storageID, string val);
string readRecords(int serverID, int storageID, string objID);
string readLine(int fd, long long offset);



#endif