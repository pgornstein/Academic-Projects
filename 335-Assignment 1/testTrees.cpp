#include "SequenceMap.h"
#include "BinarySearchTree.h" 
#include "BinarySearchTree.cpp" 
#include "AvlTree.h" 
#include "AvlTree.cpp" 
#include "LazyAvlTree.h" 
#include "LazyAvlTree.cpp" 
#include "TestObject.h" 
#include "TestObject.cpp" 

int main(int argc, char *argv[]) {
  string database = argv[1];
  string queries = argv[2];
  string choice = argv[3];
  //Following code allows the user to choose which tree they would like to build and test
  if("AVL" == choice) {
    TestObject<AvlTree<SequenceMap>> t(database, queries);
    t.test();
  }
  else if ("BST" == choice) {
    TestObject<BinarySearchTree<SequenceMap>> t(database, queries); 
    t.test();
  }
  else if("LazyAVL" == choice) {
    TestObject<LazyAvlTree<SequenceMap>> t(database, queries);
    t.test();
  }
  else cout << "Error: Invalid flag entered." << endl;
  return 0;
}
 
