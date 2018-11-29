# Distributed Transaction Management

## Storage Layer
1. All the write records are append only
2. Record table records all the location of object and different version if there is update (future: clean up periodically to get rid of old value)
3. Last offset lock for the storage file is mutex lock
	* Offset Lock for write only
2. Record lock is mutex lock 
	* Record lock for both read and write (Need to change into read write lock instead)

## Trace Handler
1. Currently support ycsb load trace and operation trace
2. Simple hash method is used for decide the target of each object
	* Available functions:
		void loadRecord(char* filename, int numServer); //load record to data structure
		void loadDataToStorage(char* filename, int numServer); //load record to storage files
		void printTable();

## Util
1. C++ util functions
	* Available functions:
		size_t genStrHash(char* objID); //generate hash value from string
2. C util functions
	
