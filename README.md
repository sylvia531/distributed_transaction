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

## Util
1. C++ util functions
2. C util functions
