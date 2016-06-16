#ifndef _TESTOBJECT_H_
#define _TESTOBJECT_H_

#include "Parser.h" 
#include <cmath>

template <typename Comparable> 
class TestObject {

 public: 

  string database;
  string queries;
  Parser p; 

  TestObject(); //Default constructor
  TestObject(string file1, string file2); //Constructor that takes two filenames as parameters 

  void test(); // test function, performs operations of program testTrees 

};

#endif
