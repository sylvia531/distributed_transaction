#ifndef __UTILCPP_H__  
#define __UTILCPP_H__ 

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

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif
	 size_t genStrHash(char* objID);
#ifdef __cplusplus
};
#endif

// size_t genStrHash(string objID);

#endif