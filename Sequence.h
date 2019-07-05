#ifndef Sequence_h_
#define Sequence_h_

#include <string>
#include <ostream>
typedef size_t size_type;

class Sequence {
  std::string id_;
  std::string sequence_;
public:
  Sequence(std::string id, std::string sequence): id_(id), sequence_(sequence) {}
  Sequence(): id_("") { }
  Sequence(const Sequence &s): id_(s.id_), sequence_(s.sequence_) {}
  std::string &id() { return id_; }
  std::string &str() { return sequence_; }

};

#endif
