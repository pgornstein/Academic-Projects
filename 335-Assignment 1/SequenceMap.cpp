#include "SequenceMap.h"

bool SequenceMap::operator<(SequenceMap &other) {
  if (rec_sequence.compare(other.rec_sequence) < 0) return true; //compares recognition sequences of the two SequenceMaps 
  else return false;
}

void SequenceMap::merge(SequenceMap other) {
  strings.insert(other.strings.begin(), other.strings.end()); //merges the enzyme acronym of the other SequenceMap into the set of the current one
}
