all: blocksworld.o
	
state.o: state.cpp state.h
	g++ -std=c++11 -c -g state.cpp
node.o: node.cpp node.h
	g++ -std=c++11 -c -g node.cpp
blocksworld.o: blocksworld.cpp node.o state.o
	g++ -std=c++11 -g state.o node.o blocksworld.cpp -o blocksworld
clean: 
	rm *.o blocksworld 