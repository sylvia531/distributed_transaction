#include "util_cpp.h"

hash<string> str_hash;

size_t genStrHash(string objID){
	return str_hash(objID);
}