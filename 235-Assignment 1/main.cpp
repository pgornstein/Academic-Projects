#include "ArrayBag.h"
#include "ArrayBagEx.h"
#include "ArrayBag.cpp" 
#include "ArrayBagEx.cpp"
#include <iostream> 
using namespace std; 

template <class ItemType>
int replacement(ArrayBagEx<ItemType>& a, ItemType b, ItemType c);

int main() {
  ArrayBagEx<int> test;
  test.add(1);
  test.add(2);
  test.add(3);
  test.add(4);
  test.add(5);
  if (test.contains(3)) cout << "Contain function works." << endl; 
  else cout << "Contain function broken." << endl;
  if (!test.isEmpty()) cout << "Empty check works." << endl;
  else cout << "Empty check broken" << endl;
  if (1 == test.getFrequencyOf(4)) cout << "Frequency check works." << endl; 
  else cout << "Frequency check broken." << endl;
  test.remove(1);
  if (!test.contains(1)) cout << "Remove function works." << endl; 
  else cout << "Remove function broken." << endl; 
  test.clear();
  vector<int> vect = test.toVector();
  cout << "Vector conversion function working." << endl;
  if (!test.getCurrentSize()) cout << "Clear function works." << endl; 
  else cout << "Clear function broken." << endl;
  return 0;
} //end main

template <class ItemType>
int replacement(ArrayBagEx<ItemType>& a, ItemType b, ItemType c) {
  a.replace(b, c);
}
