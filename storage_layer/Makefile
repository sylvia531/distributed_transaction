storage_test: storageLayer.o traceLoader.o utilcpp.o
	gcc -g storageLayer_main.c storageLayer.o traceLoader.o utilcpp.o -lm -O0 -o storage_test -lstdc++
storageLayer.o:
	g++ -std=c++11 -g -c storageLayer.cpp
traceLoader.o:
	g++ -std=c++11 -g -c ../trace_handler/traceLoader.cpp
utilcpp.o:
	g++ -std=c++11 -g -c ../util/utilcpp.cpp	
clean:
	rm -f *~ *.o *.out storage_test