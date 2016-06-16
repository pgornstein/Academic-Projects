all: TestBinQueuePlusPlus

TestBinQueuePlusPlus.o: TestBinQueuePlusPlus.cpp BinQueuePlusPlus.h QuadraticProbing.h BinomialQueue.h 
	g++ -c TestBinQueuePlusPlus.cpp -std=gnu++11 -g

TestBinQueuePlusPlus: TestBinQueuePlusPlus.o BinQueuePlusPlus.cpp QuadraticProbing.cpp BinomialQueue.cpp 
	g++ -o TestBinQueuePlusPlus TestBinQueuePlusPlus.o -std=gnu++11 -g

clean:
	rm *.o
