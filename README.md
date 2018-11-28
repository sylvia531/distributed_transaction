# Distributed Transaction Management

## Storage Layer
1. Last offset lock for the storage file is mutex lock
2. Record lock is mutex lock 

## Trace Handler
1. Currently support ycsb load trace and operation trace
2. Simple hash method is used for decide the target of each object

##Util
1. C++ util functions
2. C util functions
