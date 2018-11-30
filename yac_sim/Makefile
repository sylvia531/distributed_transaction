sim_main: sim_main.c clusterManager.c phyServer.c ./msg_queue/msgOprt.c ../util/utilc.c ../statistics.c msgQueue.o storageLayer.o traceLoader.o utilcpp.o
	gcc -g sim_main.c clusterManager.c phyServer.c ./msg_queue/msgOprt.c ../util/utilc.c ../statistics.c msgQueue.o storageLayer.o traceLoader.o utilcpp.o  ./yacsim.a -lm -O0 -o sim_main  -lstdc++ 
storageLayer.o: ../storage_layer/storageLayer.cpp
	g++ -std=c++11 -g -c ../storage_layer/storageLayer.cpp
traceLoader.o: ../trace_handler/traceLoader.cpp
	g++ -std=c++11 -g -c ../trace_handler/traceLoader.cpp
msgQueue.o: ./msg_queue/msgQueue.cpp
	g++ -std=c++11 -g -c ./msg_queue/msgQueue.cpp
utilcpp.o: ../util/utilcpp.cpp
	g++ -std=c++11 -g -c ../util/utilcpp.cpp
clean:
	rm -f *~ *.o *.out sim_main