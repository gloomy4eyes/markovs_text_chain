#ifndef MARKOVS_TEXT_CHAIN_LEARNER_H
#define MARKOVS_TEXT_CHAIN_LEARNER_H

#include <unordered_map>
#include <string>

using arguments = std::unordered_map<std::string, std::string>;

class Learner {
 public:
  Learner(int argc, char *argv[]);
  ~Learner(){}

  void run();

 private:
  arguments _args;

};

#endif //MARKOVS_TEXT_CHAIN_LEARNER_H
