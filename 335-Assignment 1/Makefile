assignment2: queryTrees testTrees

queryTrees: queryTrees.o QueryObject.o Parser.o LazyAvlTree.o AvlTree.o BinarySearchTree.o SequenceMap.o
	g++ -o queryTrees queryTrees.o QueryObject.o Parser.o LazyAvlTree.o AvlTree.o BinarySearchTree.o SequenceMap.o -std=gnu++11 -g

testTrees: testTrees.o TestObject.o Parser.o LazyAvlTree.o AvlTree.o BinarySearchTree.o SequenceMap.o 
	g++ -o testTrees testTrees.o TestObject.o Parser.o LazyAvlTree.o AvlTree.o BinarySearchTree.o SequenceMap.o -std=gnu++11 -g

queryTrees.o: queryTrees.cpp SequenceMap.h BinarySearchTree.h BinarySearchTree.cpp AvlTree.h AvlTree.cpp LazyAvlTree.h LazyAvlTree.cpp QueryObject.h QueryObject.cpp 
	g++ -c queryTrees.cpp -std=gnu++11 -g

testTrees.o: testTrees.cpp SequenceMap.h BinarySearchTree.h BinarySearchTree.cpp AvlTree.h AvlTree.cpp LazyAvlTree.h LazyAvlTree.cpp TestObject.h TestObject.cpp 
	g++ -c testTrees.cpp -std=gnu++11 -g

QueryObject.o: QueryObject.cpp QueryObject.h  
	g++ -c QueryObject.cpp -std=gnu++11 -g

TestObject.o: TestObject.cpp TestObject.h 
	g++ -c TestObject.cpp -std=gnu++11 -g

Parser.o: Parser.cpp Parser.h  
	g++ -c Parser.cpp -std=gnu++11 -g

LazyAvlTree.o: LazyAvlTree.cpp LazyAvlTree.h 
	g++ -c LazyAvlTree.cpp -std=gnu++11 -g

AvlTree.o: LazyAvlTree.cpp LazyAvlTree.h
	g++ -c AvlTree.cpp -std=gnu++11 -g

BinarySearchTree.o: BinarySearchTree.cpp BinarySearchTree.h 
	g++ -c BinarySearchTree.cpp -std=gnu++11 -g

SequenceMap.o: SequenceMap.cpp SequenceMap.h 
	g++ -c SequenceMap.cpp -std=gnu++11 -g

clean:
	rm *.o
