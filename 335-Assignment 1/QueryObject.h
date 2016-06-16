#ifndef _QUERYOBJECT_H_
#define _QUERYOBJECT_H_

#include "Parser.h"

template <typename Comparable> 
class QueryObject {

 public: 

  string filename; 
  Parser p; 

  QueryObject(); //Default constructor
  QueryObject(string file); //Constructor taking name of file as paramater


  void query(); //query function, performs queryTree program 

};

#endif
