#include <string>

unsigned short char_to_short(char c);
char short_to_char(unsigned short i);
std::string convert_2bit_to_kmer(uint16_t b);
uint16_t convert_kmer_to_2bit(std::string s);
