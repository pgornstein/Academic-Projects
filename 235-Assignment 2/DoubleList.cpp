#include "DoubleList.h"

//Constructors 

template<class ItemType>
DoubleList<ItemType>::DoubleList() {headPtr = NULL;}

template<class ItemType>
DoubleList<ItemType>::DoubleList(DoubleNode<ItemType> *d) {headPtr = d;}

//Accessor 

template<class ItemType>
DoubleNode<ItemType> * DoubleList<ItemType>::getHeadPtr() {return headPtr;}

//Mutators

template<class ItemType>
void DoubleList<ItemType>::setHeadPtr(DoubleNode<ItemType> *d) {headPtr = d;}

template<class ItemType>
void DoubleList<ItemType>::addFront(DoubleNode<ItemType> *d) {
  d->setNxtPtr(headPtr);
  headPtr->setPrvPtr(d);
  setHeadPtr(d);
}

template<class ItemType>
void DoubleList<ItemType>::removeFront() {
  setHeadPtr(getHeadPtr()->getNxtPtr());
  getHeadPtr()->getPrvPtr()->setNxtPtr(NULL);
  getHeadPtr()->setPrvPtr(NULL);
}
