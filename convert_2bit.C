#include "convert_2bit.h"

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
