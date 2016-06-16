#include "Graph.h"

Graph::Graph(string file) {
  filename = file;
}

void Graph::populateGraph() {
  ifstream streamer(filename);
  string line; 
  bool passed = false;
  while (!streamer.eof()) {
    getline(streamer, line);
    if (line[0] == 0) break;
    if (!passed) { //for finding out the number of vertices in the graph
      stringstream s(line);
      int size;
      s >> size;
      graph.resize(size);
      passed = true;
      continue;
    }
    else {//for all other lines in the .txt file
      stringstream s(line);
      int num; 
      s >> num;
      Vertex v;
      v.number = num;//entering of Vertex's number
      int num1;
      double num2;
      while (s >> num1 >> num2) {
	if (num2 == 0) break;
	if (num1 == -1 || num2 == -1) break;
	v.vertices.push_back(num1); //entering of adjacent Vertex number
	v.weights.push_back(num2); //entering of adjacent Vertex's edge weight
      }
      v.dv = INFINITY; //setting dv to infinity by default (will be fixed later by Dijkstra's algorithm)
      v.prev = nullptr; //setting previous Vertex to nullptr by default (will be fixed later by Dijkstra's algorithm)
      graph[num] = v; //inserts Vertex into the graph
    }
  }
}

void Graph::printAdjacency() {
  cout << "Adjacency List:" << endl;
  for (int i = 0; i < graph.size(); i++) {
    cout << "Vertex " <<  graph[i].number << "--> ";
    for (int j = 0; j < graph[i].vertices.size(); j++) {
      if (j == graph[i].vertices.size() - 1) cout << "Vertex " << graph[i].vertices[j]; 
      else cout << "Vertex " <<  graph[i].vertices[j] << ", ";
    }
    if (graph[i].vertices.size() == 0) cout << "None";
    cout << endl;
  }
  cout << endl; 
}

void Graph::dijkstra(int v) {
  vector<Vertex *> ptrs; //work must be done with pointers, so that all changes to the Vertices inside the pqueue are actually altering the values on the graph
  ptrs.resize(graph.size());
  for (int i = 0; i < ptrs.size(); i++) ptrs[i] = &graph[i]; //each Vertex pointer in the array of pointers represents it's corresponding Vertex on the graph by number 
  priority_queue<Vertex *, vector<Vertex *>, Graph::great> pq; //pqueue declared to use comparator great defined in Graph.h
  ptrs[v]->dv = 0; //starting Vertex dv set to 0, Dijkstra's algorithm starts
  pq.push(ptrs[v]);
  while (!pq.empty()) {
    Vertex *current = pq.top();
    pq.pop();
    for (int i = 0; i < current->vertices.size(); i++) {
      if (current->dv + current->weights[i] < ptrs[current->vertices[i]]->dv) {
	ptrs[current->vertices[i]]->dv = current->dv + current->weights[i];
	ptrs[current->vertices[i]]->prev = current;
      }
      if (current->dv < ptrs[current->vertices[i]]->dv) pq.push(ptrs[current->vertices[i]]);
    }
  }// Dijkstra's algorithm finished
  int target; 
  cout << "Please enter target Vertex: ";
  cin >> target; //Target vertex entered
  if (target >= graph.size()) {
    cout << "No such vertex in graph." << endl;
    exit(1);
  }
  stack<Vertex *> s; //method for backtracking path
  Vertex *t = ptrs[target];
  s.push(t);
  while (t->prev != nullptr) {//backtracking loop
    t = t-> prev; 
    s.push(t);
  }
  if (t->number != v) cout << "There is no path from Vertex " << v << " to your target Vertex " << target << endl; //If target vertex not connected
  else {//if target Vertex connected to Starting Vertex
    cout << "Path: "; 
    while (!s.empty()) {
      Vertex *toPrint = s.top();
      s.pop();
      if (s.size() == 0) cout << "Vertex " << toPrint->number;
      else cout << "Vertex " << toPrint->number << " --> ";
    }
    cout << endl; 
    cout << "Path Weight: " << ptrs[target]->dv << endl; 
  }
}  
  


 
