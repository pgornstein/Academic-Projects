#include "SequenceMap.h"
#include "BinarySearchTree.h" 
#include "BinarySearchTree.cpp" 
#include "AvlTree.h" 
#include "AvlTree.cpp" 
#include "LazyAvlTree.h" 
#include "LazyAvlTree.cpp" 
#include "QueryObject.h" 
#include "QueryObject.cpp" 

int main(int argc, char *argv[]) {
  string file = argv[1];
  string choice = argv[2];
  //Following code allows user to choose which tree they would like to build and query.
  if ("AVL" == choice) {
    QueryObject<AvlTree<SequenceMap>> q(file);
    q.query();
  }
  else if ("BST" == choice) {
    QueryObject<BinarySearchTree<SequenceMap>> q(file);
    q.query();
  }
  else if ("LazyAVL" == choice) {
    QueryObject<LazyAvlTree<SequenceMap>> q(file);
    q.query();
  }
  else cout << "Error: Invalid flag entered." << endl; 
  return 0;
}
