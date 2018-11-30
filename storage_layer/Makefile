storage_test: storageLayer_main.c  storageLayer.o traceLoader.o utilcpp.o
	gcc -g storageLayer_main.c storageLayer.o traceLoader.o utilcpp.o -lm -O0 -o storage_test -lstdc++
storageLayer.o: storageLayer.cpp
	g++ -std=c++11 -g -c storageLayer.cpp
traceLoader.o: ../trace_handler/traceLoader.cpp
	g++ -std=c++11 -g -c ../trace_handler/traceLoader.cpp
utilcpp.o: ../util/utilcpp.cpp
	g++ -std=c++11 -g -c ../util/utilcpp.cpp	
clean:
	rm -f *~ *.o *.out storage_test