all: assignment3

assignment3: main.o Graph.o
	g++ -o assignment3 main.o Graph.o -std=gnu++11 -g

main.o: main.cpp Graph.h 
	g++ -c main.cpp -std=gnu++11 -g

Graph.o: Graph.cpp Graph.h 
	g++ -c Graph.cpp -std=gnu++11 -g

clean: 
	rm *.o
