#include "QueryObject.h" 

template<typename Comparable> 
QueryObject<Comparable>::QueryObject() {
  filename = ""; 
}

template<typename Comparable> 
QueryObject<Comparable>::QueryObject(string file) {
  filename = file; 
} 

template<typename Comparable> 
void QueryObject<Comparable>::query() {
  vector<SequenceMap> v = p.parse(filename);
  Comparable tree; 
  for (int i = 0; i < v.size(); i++) tree.insert(v[i]); //Inserts parsed SequenceMaps into tree 
  string input;
  cout << "Please type in sequence to be queried: ";
  cin >> input; 
  SequenceMap s; 
  s.rec_sequence = input;
  if (!tree.contains(s)) cout << "Sequence not found in database."  << endl;
  else { 
    SequenceMap retrieved = tree.find(s); //Saves found node from the tree to check enzyme acronyms
    cout << "The following enzyme acronyms are associated with sequence " << input << " :" << endl;
    set<string>::iterator iter;
    for (iter = retrieved.strings.begin(); iter != retrieved.strings.end(); iter++) cout << *iter << endl; //Prints all the enzyme acronyms in the set of the found SequenceMap
  }
}
