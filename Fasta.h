#ifndef Fasta_h_
#define Fasta_h_

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "Sequence.h"

class Fasta {
private:
  int currline;
  std::ifstream _f;
  
public:
  Fasta(std::string filename): currline(0) {
    _f = std::ifstream(filename.c_str());
    currline = 1;
  }
  Sequence readSequence();
};

#endif
