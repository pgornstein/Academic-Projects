#ifndef _DOUBLENODE_H_
#define _DOUBLENODE_H_
#include <cstdio>
#include <iostream>

using namespace std;

template<class ItemType> 
class DoubleNode {

  ItemType data;
  DoubleNode *prvPtr, *nxtPtr;

 public:

  //Constructors
  DoubleNode();
  DoubleNode(ItemType i);
  DoubleNode(DoubleNode *d, DoubleNode *e);
  DoubleNode(DoubleNode *d, DoubleNode *e, ItemType i);

  //Accessors
  DoubleNode * getPrvPtr();
  DoubleNode * getNxtPtr();
  ItemType getData();

  //Mutators
  void setPrvPtr(DoubleNode *d);
  void setNxtPtr(DoubleNode *d);
  void setData(ItemType i);

}; //end DoubleNode 

#endif //end of definition file.  
