//default constructor 
template <typename Comparable> 
BinQueuePlusPlus<Comparable>::BinQueuePlusPlus() {}

//copy constructor
template <typename Comparable> 
BinQueuePlusPlus<Comparable>::BinQueuePlusPlus(const BinQueuePlusPlus & rhs) {
  binQueue = rhs.binQueue; 
  table = rhs.table; 
}

//move constructor 
template <typename Comparable> 
BinQueuePlusPlus<Comparable>::BinQueuePlusPlus(BinQueuePlusPlus && rhs) {
  binQueue = rhs.binQueue; 
  table = rhs.table;
}

//insert
template <typename Comparable> 
void BinQueuePlusPlus<Comparable>::insert(const Comparable & x) {
  typename BinomialQueue<Comparable>::BinomialNode *b = binQueue.insert(x);
  Pair p; 
  p.key = x; 
  p.ptr = b;
  table.insert(p);
}

//rvalue insert
template <typename Comparable>
void BinQueuePlusPlus<Comparable>::insert(Comparable && x) {
  Comparable y(x);
  insert(y);
}

//deleteMin
template <typename Comparable> 
bool BinQueuePlusPlus<Comparable>::deleteMin() {
  int min = binQueue.findMinIndex();
  Pair p; 
  p.key = binQueue.theTrees[min]->element;
  p.ptr = binQueue.theTrees[min];
  binQueue.deleteMin();
  table.remove(p);
  if (!table.contains(p)) return true; 
  else return false;
}

//merge
template<typename Comparable> 
void BinQueuePlusPlus<Comparable>::merge(BinQueuePlusPlus & rhs) {
  binQueue.merge(rhs.binQueue);
  table.makeEmpty();
  for (int i = 0; i < binQueue.theTrees.size(); i++) {
    if (binQueue.theTrees[i] != nullptr) hasher(binQueue.theTrees[i]);
  }
}

//returns total comparisons of internal binQueue
template <typename Comparable>
int BinQueuePlusPlus<Comparable>::getComparisons() {
  return binQueue.comparisonCount;
}

//returns total assignments of internal binQueue
template <typename Comparable>
int BinQueuePlusPlus<Comparable>::getAssignments() {
  return binQueue.assignmentCount;
}

//resets binQueue's comparisonCount and assignmentCount values 
template <typename Comparable> 
void BinQueuePlusPlus<Comparable>::resetValues() {
  binQueue.comparisonCount = 0;
  binQueue.assignmentCount = 0;
}

//public accessor of private find() function 
template <typename Comparable> 
bool BinQueuePlusPlus<Comparable>::userFind(Comparable key) {
  if (find(key) == nullptr) return false; 
  else return true;
}

//decreaseKey
template <typename Comparable> 
void BinQueuePlusPlus<Comparable>::decreaseKey(typename BinomialQueue<Comparable>::BinomialNode *node) {
  node->element = "";
}

//remove
template <typename Comparable>
void BinQueuePlusPlus<Comparable>::remove(Comparable toRemove) {
  if (find(toRemove) == nullptr) return; 
  typename BinomialQueue<Comparable>::BinomialNode *node; 
  node = find(toRemove);
  Pair p; 
  p.key = toRemove;
  p.ptr = node; 
  table.remove(p);
  decreaseKey(node);
  while (node->parent != nullptr) {
    Comparable temp = node->parent->element;
    node->parent->element = node->element; 
    node->element = temp;
    p.key = temp;
    table.array[table.findPos(p)].element.ptr = node;
    node = node->parent;
  }
  binQueue.deleteMin();
}


//internal find function
template <typename Comparable> 
typename BinomialQueue<Comparable>::BinomialNode * BinQueuePlusPlus<Comparable>::find(Comparable keyToFind) {
  Pair p; 
  p.key = keyToFind;
  if (!table.contains(p)) return nullptr;  
  int position = table.findPos(p);
  return table.array[position].element.ptr;
}


//internal merge helper function 
template <typename Comparable> 
void BinQueuePlusPlus<Comparable>::hasher(typename BinomialQueue<Comparable>::BinomialNode *node) {
  Pair p; 
  p.key = node->element; 
  p.ptr = node; 
  table.insert(p);
  if (node->leftChild != nullptr) hasher(node->leftChild);
  if (node->nextSibling != nullptr) hasher(node->nextSibling);
}
