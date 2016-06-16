#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <iostream>
#include <fstream>
#include <iostream> 
#include <vector>
#include <sstream>
#include <stack>
#include <queue>

using namespace std;

class Graph {

public:

  const int INFINITY = 999999;

  explicit Graph(string file);

  string filename; //for reading file

  struct Vertex {
    int number; //vertex number
    vector<int> vertices; 
    vector<double> weights;
    double dv; //same dv as in dijkstra algorithm 
    Vertex * prev; //previous Vertex in path
  };

  vector<Vertex> graph;

  struct great { //comparator structure like std::greater() but to work with Vertex pointers, making the priority queue a minheap 

    bool operator() (const Vertex *v1, const Vertex *v2) {
      return (v1->dv > v2->dv);
    }

  };

  void populateGraph(); //populates the graph 

  void printAdjacency(); //prints adjacency list

  void dijkstra(int v); //performs Dijkstra's algorithm on the graph from the starting vertex, asks for target vertex, returns path from starting vertex as well as total path weight

};

#endif

