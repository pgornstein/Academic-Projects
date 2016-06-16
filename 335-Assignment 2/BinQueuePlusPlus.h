#ifndef BIN_QUEUE_PLUS_PLUS_H
#define BIN_QUEUE_PLUS_PLUS_H

#include "BinomialQueue.h" 
#include "QuadraticProbing.h" 

template <typename Comparable> 
class BinQueuePlusPlus {

 public:
 
  BinQueuePlusPlus(); 
  BinQueuePlusPlus(const BinQueuePlusPlus & rhs);
  BinQueuePlusPlus(BinQueuePlusPlus && rhs);

  void insert(const Comparable & x);
  void insert(Comparable && x);
  bool deleteMin();
  void merge(BinQueuePlusPlus & rhs);

  int getComparisons();
  int getAssignments();
  void resetValues();

  //public accessor of private find() function 
  bool userFind(Comparable key);

  void decreaseKey(typename BinomialQueue<Comparable>::BinomialNode *node);
  void remove(Comparable toRemove);

  BinomialQueue<Comparable> binQueue;

  struct Pair {

    Pair() {}
    Pair(const Pair & rhs) {
      key = rhs.key;
      ptr = rhs.ptr;
    }
    Pair(const Pair && rhs) {
      key = rhs.key;
      ptr = rhs.ptr;
    }
    Pair & operator=(const Pair & rhs) {      
      key = rhs.key;
      ptr = rhs.ptr;
    }
    Pair & operator=(Pair && rhs) {      
      key = rhs.key;
      ptr = rhs.ptr;
      }
    Comparable key; 
    typename BinomialQueue<Comparable>::BinomialNode *ptr;

    bool operator!=(const Pair & rhs) const {
      if (key == rhs.key && ptr == rhs.ptr) return false; 
      else return true;
    }
  };

  HashTable<Pair> table;

  typename BinomialQueue<Comparable>::BinomialNode * find(Comparable keyToFind);

  //helper function for merge()
  void hasher(typename BinomialQueue<Comparable>::BinomialNode *node);

};

#include "BinQueuePlusPlus.cpp"

#endif


