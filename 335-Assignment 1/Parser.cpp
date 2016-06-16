#include "Parser.h" 

vector<SequenceMap> Parser::parse(string filename) {
  ifstream ifsEnzyme(filename);
  string enzyme; 
  vector<SequenceMap> v;
  bool through = false; 
  while (getline(ifsEnzyme, enzyme)) {
    if (0 == enzyme[0]) break; //In case of end of file character
 // To get through part of text file that isn't sequences
    while (!through) {
      int h = 0; 
      while (h < enzyme.size()) {
	if (' ' == enzyme[h]) {
	  getline(ifsEnzyme, enzyme);
	  h = 0;
	}
	else if (h == enzyme.size() - 1) {
	  through = true;
	  break;
	} 
	else h++;
      }
    }   
    int i = 0; 
    while ('/' != enzyme[i]) i++; // to locate first slash
    string acronym = enzyme.substr(0, i); // to capture acronym
    i++; // to jump the /
    bool stop = false;
    while (!stop) {
      int j = i; 
      while ('/' != enzyme[j]) j++; // to locate next slash
      string sequence = enzyme.substr(i, j - i); // to capture recognition sequence
      SequenceMap s; 
      s.rec_sequence = sequence;
      s.strings.insert(acronym); 
      v.push_back(s); // Adds parsed recognition sequence with acronym to vector
      if (enzyme[j + 1] == '/') stop = true; // ends parsing iff double slash is reached
      i = j + 1;
    }
  }
  return v;
} 

