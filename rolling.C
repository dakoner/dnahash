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

int char_to_int(char c) {
  switch(c){
  case 'A': return 0;
  case 'C': return 1;
  case 'G': return 2;
  case 'T': return 3;
  default: return -1;
  }
}

char int_to_char(int i) {
  switch(i) {
  case 0: return 'A';
  case 1: return 'C';
  case 2: return 'G';
  case 3: return 'T';
  default:  return 255;
  }
}

std::string convert_2bit_to_kmer(uint16_t b) {
  std::string s;
  for(int i = 0 ; i < 8; ++i) {
    
    int ci = b & 3 ;
    char c = int_to_char(ci);
    if (c == 255) return "";
    s += c;
    b >>= 2;
  }
  std::string reversed(s.rbegin(), s.rend());
  return reversed;
}

uint16_t convert_kmer_to_2bit(std::string s) {
  uint16_t n = 0;
  for(int i = 0 ; i < 8; ++i) {
    int ci = char_to_int(s[i]);
    if (ci == -1) throw std::string("Unexpected char:", s[i]);
    n <<= 2;
    n |= ci;
  }
  return n;
}

int main(int argc, char *argv[]) {
  Fasta f(argv[1]);
  while (true) {
    Sequence s = f.readSequence();
    uint16_t n = 0;
    std::vector<unsigned int> kmer_counts(UINT16_MAX+1, 0);
    std::string seq = str_toupper(s.str());
    int conseq_valid = 0;
    for (size_t i = 0; i < seq.size(); ++i) {
      char c = seq[i];
      int ci = char_to_int(c);
      if (ci == -1) {
	n = 0;
	conseq_valid = 0;
	continue;
      }
      conseq_valid++;
      n <<= 2;
      n |= ci;
      if (conseq_valid >= 8) {
l;
	kmer_counts[n]++;
      }
    }

    for (size_t i = 0; i < kmer_counts.size(); ++i) {
      if (kmer_counts[i])
	std::cout << convert_2bit_to_kmer(i) << " " << kmer_counts[i] << std::endl;
    }
    // std::vector<uint16_t> idx(kmer_counts.size());
    // std::iota(idx.begin(), idx.end(), 0);
    // std::sort(idx.begin(), idx.end(),
    // 	      [&kmer_counts](size_t i1, size_t i2) {
    // 		return kmer_counts[i1] > kmer_counts[i2];
    // 	      });
    // for(size_t i = 0; i < idx.size(); i++) {
    //   std::cout << convert_2bit_to_kmer(idx[i]) << " " << kmer_counts[idx[i]] << std::endl;
    // }
    exit(0);
  }
  return 0;
}
