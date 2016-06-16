#include "Graph.h"

int main(int argc, char * argv[]) {
  string file = argv[1];
  string start = argv[2];
  stringstream s(start);
  int starting_vertex;
  s >> starting_vertex;
  Graph g(file);
  g.populateGraph();
  g.printAdjacency();
  g.dijkstra(starting_vertex); 
  return 0;
}
