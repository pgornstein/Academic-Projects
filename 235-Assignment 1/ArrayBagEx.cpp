#include "ArrayBagEx.h"

template<class ItemType> 
ArrayBagEx<ItemType>::ArrayBagEx() {}

template<class ItemType>
int ArrayBagEx<ItemType>::sum() const {
  int sum = 0;
  for (int i = 0; i < this->getCurrentSize(); i++) sum += this->items[i];
  return sum;
} //end sum

template<class ItemType>
int ArrayBagEx<ItemType>::replace(const ItemType& curEntry, const ItemType& newEntry) {
  int counter = 0;
  for (int i = 0; i < this->getCurrentSize(); i++) {
    if (this->items[i] == curEntry) this->toVector()[i] = newEntry;
    counter++; 
  }
  return counter;
} //end replace 

template<class ItemType>
void ArrayBagEx<ItemType>::addToVector(vector<ItemType>& v, int i, int size) const {
  v.push_back(this->items[i]);
  if (i < size - 1) addToVector(v, i + 1, size);
} //end addToVector

template<class ItemType>
vector<ItemType> ArrayBagEx<ItemType>::toVector() const {
  vector<ItemType> bagContents;
  addToVector(bagContents, 0, this->getCurrentSize());
  return bagContents;
}  //end toVector
