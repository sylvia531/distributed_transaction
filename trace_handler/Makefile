trace_load: storageLayer.o traceLoader.o utilcpp.o
	gcc -g traceLoader_main.c storageLayer.o traceLoader.o utilcpp.o -lm -O0 -o trace_load -lstdc++
storageLayer.o:
	g++ -std=c++11 -g -c ../storage_layer/storageLayer.cpp
traceLoader.o:
	g++ -std=c++11 -g -c traceLoader.cpp
utilcpp.o:
	g++ -std=c++11 -g -c ../util/utilcpp.cpp	
clean:
	rm -f *~ *.o *.out trace_load