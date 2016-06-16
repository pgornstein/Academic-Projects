#ifndef _ARRAY_BAG_EX
#define _ARRAY_BAG_EX
#include "ArrayBag.h"

template<class ItemType>
class ArrayBagEx : public ArrayBag <ItemType>
    {
    // Private recursive helper:
      void addToVector(vector<ItemType>& v, int i, int size) const;

    public:
       ArrayBagEx();
       int sum() const;
       int replace(const ItemType& curEntry, const ItemType& newEntry);
       vector<ItemType> toVector() const;
    }; // end ArrayBagEx

    #endif
