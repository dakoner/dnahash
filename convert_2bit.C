#include "convert_2bit.h"

unsigned short char_to_short(char c) {
  switch(c){
  case 'A': return 0;
  case 'C': return 1;
  case 'G': return 2;
  case 'T': return 3;
  default: return 4;
  }
}

char short_to_char(unsigned short i) {
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
    
    unsigned short ci = b & 3 ;
    char c = short_to_char(ci);
    if (c == 0) throw std::string("Unexpected short");
    s += c;
    b >>= 2;
  }
  std::string reversed(s.rbegin(), s.rend());
  return reversed;
}

uint16_t convert_kmer_to_2bit(std::string s) {
  uint16_t n = 0;
  for(int i = 0 ; i < 8; ++i) {
    unsigned short ci = char_to_short(s[i]);
    if (ci == 4) throw std::string("Unexpected char");
    n <<= 2;
    n |= ci;
  }
  return n;
}
