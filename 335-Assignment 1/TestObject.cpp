#include "TestObject.h" 

template<typename Comparable>
TestObject<Comparable>::TestObject() {
  database = "";
  queries = "";
}

template<typename Comparable>
TestObject<Comparable>::TestObject(string file1, string file2) {
  database = file1; 
  queries = file2;
}
template<typename Comparable>
void TestObject<Comparable>::test() {

  //Step 1
  vector<SequenceMap> v = p.parse(database);
  Comparable tree; 
  for (int i = 0; i < v.size(); i++) tree.insert(v[i]); //inserts parsed SequenceMaps into tree
  cout << "Total number of recursive calls to insert() function: " << tree.insertCount << endl;

  cout << endl;

  //Step 2
  double n = tree.nodes();
  cout << "Total number of nodes: " << n << endl;
  double ipl = tree.internalPathLength();
  double averageDepth = ipl / n;
  cout << "Average depth of tree: " << averageDepth << endl; 
  double logn = log2(n);
  double ratio = averageDepth / logn;
  cout << "Ratio of average depth to log2(number of nodes): " << ratio << endl; 

  cout << endl; 
  
  //Step 3
  ifstream queryStream(queries); 
  string search; 
  int successes = 0;
  //Following loop queries every single recognition sequence in queries file 
  while (getline(queryStream, search)) {
    if (0 == search[0]) break; // In case of end-of-file null character
    SequenceMap s; 
    s.rec_sequence = search; 
    if (tree.contains(s)) successes++;
  }
  cout << "Total number of successful queries: " << successes << endl; 
  cout << "Total number of recursive calls to contains() method: " << tree.containsCount << endl; 

  cout << endl; 

  //Step 4 
  ifstream removeStream(queries);
  string dummy; 
  string target; 
  int successfulRemoves = 0;
  //The following loop streams queries into two strings, one of which is a dummy, in order to remove every other item in the tree. 
  while (removeStream >> dummy >> target) {
    if (0 == dummy[0] || 0 == target[0]) break; //In case of end-of-file null character
    SequenceMap twig; 
    twig.rec_sequence = target;
    if (tree.contains(twig)) {
      tree.remove(twig); 
      successfulRemoves++;
    }
  }
  cout << "Total number of successful removals: " << successfulRemoves << endl; 
  cout << "Total number of recursive calls to remove() method: " << tree.removeCount << endl; 

  cout << endl; 

  //Step 5
  
  //Step 2 repeated
  n = tree.nodes();
  cout << "Total number of nodes: " << n << endl;
  ipl = tree.internalPathLength();
  averageDepth = ipl / n;
  cout << "Average depth of tree: " << averageDepth << endl; 
  logn = log2(n);
  ratio = averageDepth / logn;
  cout << "Ratio of average depth to log2(number of nodes): " << ratio << endl;

  //Step 3 repeated
  tree.containsCount = 0; //Resets counter for recursive calls to contains() function 
  ifstream queryStream2(queries);
  successes = 0; // resets counter of successful queries
  while (getline(queryStream2, search)) {
    if (0 == search[0]) break; //In case of end-of-file null character
    SequenceMap s2; 
    s2.rec_sequence = search; 
    if (tree.contains(s2)) successes++;
  }
  cout << "Total number of recursive calls to contains() method: " << tree.containsCount << endl; 
}
