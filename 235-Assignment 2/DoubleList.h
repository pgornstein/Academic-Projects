#ifndef _DOUBLELIST_H_
#define _DOUBLELIST_H_
#include "DoubleNode.h"

template<class ItemType>
class DoubleList {

  DoubleNode<ItemType> *headPtr;

 public: 

  //Constructors
  DoubleList();
  DoubleList(DoubleNode<ItemType> *d);

  //Accessor
  DoubleNode<ItemType> * getHeadPtr();

  //Mutators
  void setHeadPtr(DoubleNode<ItemType> *d);
  void addFront(DoubleNode<ItemType> *d);
  void removeFront();

};//end class DoubleList

#endif //end of header file DoubleList.h
