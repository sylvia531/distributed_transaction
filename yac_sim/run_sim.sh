#!/bin/bash 

storage="./storage/server*"
chmod 777 $storage
trace="../workloads/ycsb_workloada_trace.txt"
numServer=3
./sim_main $numServer $trace





