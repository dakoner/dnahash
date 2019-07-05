#include "Fasta.h"

Sequence Fasta::readSequence() {
  std::string id;
  std::string sequence;

  // if we're at eof, just return
  if (_f.bad() || _f.eof()) throw std::string("End of file");

  // read the ID line of the FASTA file
  if (!getline(_f, id)) {
    std::stringstream s;
    s << "Error trying to read sequence id at line " << currline;
    throw std::runtime_error(s.str());
  }

  currline++;
  // now read any number of lines of sequence until reading EOF or another ID line
  std::string tmp;
  while(1) {
    if ( _f.peek() == '>' || _f.eof()) break;
    if (!getline(_f, tmp)) {
      std::stringstream s;
      s << "Unable to read sequence at line " << currline << " with id ";
      s << id;
      throw std::runtime_error(s.str());
    }
    currline++;
    sequence += tmp;
  }
    
  return Sequence(id, sequence);
}
