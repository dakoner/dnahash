#include "Fasta.h"
#include "Sequence.h"

#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cstdint>
#include <numeric>
#include <algorithm>
#include <cctype>

int char_to_int(char c) {
  switch(c){
  case 'A': return 0;
  case 'C': return 1;
  case 'G': return 2;
  case 'T': return 3;
  default:  return -1;
  }
}

char int_to_char(int i) {
  switch(i) {
  case 0: return 'A';
  case 1: return 'C';
  case 2: return 'G';
  case 3: return 'T';
  default:  return 0;
  }
}

std::string convert_2bit_to_kmer(uint16_t b) {
  std::string s;
  for(int i = 0 ; i < 8; ++i) {
    
    int ci = b & 3 ;
    char c = int_to_char(ci);
    if (c == 0) return "";
    s += c;
    b >>= 2;
  }
  std::string reversed(s.rbegin(), s.rend());
  return reversed;
}

int main(int argc, char *argv[]) {
  Fasta f(argv[1]);
  while (true) {
    Sequence s = f.readSequence();
    uint16_t n = 0;
    std::vector<int> kmer_counts(UINT16_MAX, 0);
    std::string seq = s.str();
    std::cout << "s: " << s.id() << " " << seq.size() << std::endl;
    for (unsigned int i = 0; i < seq.size(); ++i) {
      char c = std::toupper(seq[i]);
      int ci = char_to_int(c);
      if (ci > -1) {
	n <<= 2;
	n += ci;
	kmer_counts[n]++;
	// std::cout << "c: " << c << " n:" << n << std::endl;
      }
    }
	  	      
    std::vector<size_t> idx(kmer_counts.size());
    std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(),
	      [&kmer_counts](size_t i1, size_t i2) {
		return kmer_counts[i1] > kmer_counts[i2];
	      });
    for(int i = 0; i < 100; i++) {
      std::cout << convert_2bit_to_kmer(idx[i]) << " " << kmer_counts[idx[i]] << std::endl;
    }
  }
  return 0;
}
