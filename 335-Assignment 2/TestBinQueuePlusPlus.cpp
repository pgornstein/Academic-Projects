#include <fstream> 
#include "BinQueuePlusPlus.h" 

int main() {
  BinQueuePlusPlus<string> b;
  ifstream s;
  s.open("words.txt");
  string toInsert; 
  while (s >> toInsert) {
    if (toInsert[0] == 0) break; 
    b.insert(toInsert);
  }
  s.close();
  cout << "Part 2:" << endl;
  cout << "Total number of comparisons: " << b.getComparisons() << endl; 
  cout << "Total number of assignments: " << b.getAssignments() << endl;
  cout << endl; 
  cout << "Part 3:" << endl; 
  for (int i = 0; i < 10; i++) cout << b.deleteMin() << endl;
  cout << endl;
  cout << "Part 4:" << endl;
  string toFind;
  cout << "Please enter word to search: ";
  cin >> toFind;
  if (b.userFind(toFind)) cout << "Search was successful!" << endl;
  else cout << "Search was unsuccessful." << endl;
  cout << endl;
  cout << "Part 6:" << endl;
  string toRemove;
  for (int i = 0; i < 5; i++) {
    cout << "Please input a word: ";
    cin >> toRemove;
    bool found = b.userFind(toRemove);
    if (!found) cout << "Word is not in the database and thus can't be removed from it." << endl; 
    else {
      b.remove(toRemove);
      found = b.userFind(toRemove);
      if (!found) cout << "Success! Item has been removed!" << endl;
      else cout << "Failure! Item has not been removed!" << endl;
    }
    cout << endl; 
  }
  return 0; 
}
