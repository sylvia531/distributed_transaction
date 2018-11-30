#ifndef __MSGQ_H__  
#define __MSGQ_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <cmath>

#include "../../structDef.h"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif
	void makePhyMsgQueue(int serverID);
	void insertPhyMsgQueue(int serverID, IOMsg* data);
	void getFromPhyMsgQueue(int serverID, IOMsg** out);
	int getSizeOfPhyMsgQueue(int serverID);	
#ifdef __cplusplus
};
#endif


#endif