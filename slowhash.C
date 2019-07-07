#include "str_toupper.h"
#include "Fasta.h"
#include "Sequence.h"

#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cstdint>
#include <numeric>
#include <cctype>
#include <queue>


int main(int argc, char *argv[]) {
  Fasta f(argv[1]);
  while (true) {
    Sequence s = f.readSequence();
    std::map<std::string, unsigned int> kmer_counts;
    std::string seq = str_toupper(s.str());
    for (size_t i = 0; i < seq.size()-7; ++i) {
      std::string substr = seq.substr(i, 8);
      kmer_counts[substr]++;
    }

    for (auto item : kmer_counts) {
      std::cout << item.first << " " << item.second << std::endl;
    }
    exit(0);
  }
  return 0;
}
