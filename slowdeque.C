#include "Fasta.h"
#include "Sequence.h"
#include "str_toupper.h"

#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cstdint>
#include <numeric>
#include <algorithm>
#include <cctype>
#include <queue>


int main(int argc, char *argv[]) {
  Fasta f(argv[1]);
  while (true) {
    Sequence s = f.readSequence();
    std::map<std::string, unsigned int> kmer_counts;
    std::string seq = str_toupper(s.str());
    std::deque<char> d;
    for (size_t i = 0; i < seq.size(); ++i) {
      d.push_back(seq[i]);
      if (d.size() > 8)
	d.pop_front();
      if (d.size() == 8) {
	std::deque<char> d2(d);
	std::string subseq;
	while(d2.size()) {
	  subseq += d2.front() ;
	  d2.pop_front();
	}
	kmer_counts[subseq]++;
      }
    }

    for (auto item : kmer_counts) {
      std::cout << item.first << " " << item.second << std::endl;
    }
    exit(0);
  }
  return 0;
}
