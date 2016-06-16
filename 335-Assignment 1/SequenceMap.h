#ifndef _SEQUENCEMAP_H_
#define _SEQUENCEMAP_H_
#include <iostream>
#include <fstream>
#include <string> 
#include <vector> 
#include <set>

using namespace std;

struct SequenceMap {

  string rec_sequence; //Recognition sequence
  set<string> strings; //Set to hold enzyme acronym(s)

  bool operator<(SequenceMap &other); //Overload of < operator
  void merge(SequenceMap other); // Merge class in case of multiple SequenceMaps with same recognition sequence

};

#endif 
