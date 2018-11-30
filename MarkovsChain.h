//
// Created by front on 30.11.2018.
//

#ifndef MARKOVS_TEXT_CHAIN_MARKOVSCHAIN_H
#define MARKOVS_TEXT_CHAIN_MARKOVSCHAIN_H

#include <string>
#include <vector>
#include <unordered_map>

class MarkovsChain {
 public:
  MarkovsChain();
  ~MarkovsChain();

  void process(const std::vector<std::string> &vec);

  void toFile();

 private:
  std::unordered_map<std::string, std::vector<std::string>> _chain;
  bool isNewDict;

  std::vector<std::string> _findAllNext(const std::vector<std::string> &vec, const std::string & word);
};

#endif //MARKOVS_TEXT_CHAIN_MARKOVSCHAIN_H
