#include "DoubleNode.h"

//Constructors 

template<class ItemType>
DoubleNode<ItemType>::DoubleNode() {
  prvPtr = NULL;
  nxtPtr = NULL;
}

template<class ItemType>
DoubleNode<ItemType>::DoubleNode(ItemType i) {
  data = i;
  prvPtr = NULL;
  nxtPtr = NULL;
}

template<class ItemType>
DoubleNode<ItemType>::DoubleNode(DoubleNode *d, DoubleNode *e) {
  prvPtr = d;
  nxtPtr = e;
}

template<class ItemType>
DoubleNode<ItemType>::DoubleNode(DoubleNode *d, DoubleNode *e, ItemType i) {
  prvPtr = d;
  nxtPtr = e;
  data = i;
}

//Accessors 

template<class ItemType>
DoubleNode<ItemType> * DoubleNode<ItemType>::getPrvPtr() {return prvPtr;}

template<class ItemType>
DoubleNode<ItemType> * DoubleNode<ItemType>::getNxtPtr() {return nxtPtr;}

template<class ItemType>
ItemType DoubleNode<ItemType>::getData() {return data;}

//Mutators

template<class ItemType>
void DoubleNode<ItemType>::setPrvPtr(DoubleNode *d) {prvPtr = d;}

template<class ItemType>
void DoubleNode<ItemType>::setNxtPtr(DoubleNode *d) {nxtPtr = d;}

template<class ItemType>
void DoubleNode<ItemType>::setData(ItemType i) {data = i;}
