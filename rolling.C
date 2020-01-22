#include "Fasta.h"
#include "Sequence.h"
#include "str_toupper.h"
#include "convert_2bit.h"

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
    uint16_t n = 0;
    std::vector<unsigned int> kmer_counts(UINT16_MAX+1, 0);
    std::string seq = str_toupper(s.str());
    int conseq_valid = 0;
    for (size_t i = 0; i < seq.size(); ++i) {
      char c = seq[i];
      unsigned short ci = char_to_short(c);
      if (ci == 4) {
	n = 0;
	conseq_valid = 0;
	continue;
      }
      conseq_valid++;
      n <<= 2;
      n |= ci;
      if (conseq_valid >= 8) {
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
