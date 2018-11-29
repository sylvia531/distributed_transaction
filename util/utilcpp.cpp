#include "utilcpp.h"

hash<string> str_hash;


size_t genStrHash(char* objID){
	string str(objID);
	return str_hash(str);
}

// size_t genStrHash(string objID){
	// return str_hash(objID);
// }