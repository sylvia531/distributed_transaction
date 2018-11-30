#!/bin/bash 

storage="./storage/server*"
chmod 777 $storage
trace="../workloads/ycsb_workloada_trace.txt"
./storage_test $trace





