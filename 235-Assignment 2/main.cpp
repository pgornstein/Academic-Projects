#include "DoubleNode.h"
#include "DoubleNode.cpp" 
#include "DoubleList.h"
#include "DoubleList.cpp" 

int main() {
  DoubleNode<int> *node1= new DoubleNode<int>(50);
  DoubleNode<int> *node2 = new DoubleNode<int>(node1, NULL, 5);
  node1->setNxtPtr(node2);
  DoubleList<int> list(node1);
  DoubleNode<int> *node3 = new DoubleNode<int>(25);
  list.addFront(node3);
  if (list.getHeadPtr()->getData() == 25) cout << "Add function working." << endl;
  else cout << "Add function broken." << endl;
  list.removeFront();
  if (list.getHeadPtr()->getData() == 50) cout << "Remove function working." << endl; 
  else cout << "Remove function broken." << endl;
  return 0;
}
