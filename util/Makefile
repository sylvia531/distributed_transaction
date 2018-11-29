util: util_main.c utilcpp.o
	gcc -g  util_main.c utilcpp.o -lm -O0 -o util -lstdc++
utilcpp.o:
	g++ -std=c++11 -g -c utilcpp.cpp
clean:
	rm -f *~ *.o *.out util