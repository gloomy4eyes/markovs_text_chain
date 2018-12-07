//
// Created by front on 30.11.2018.
//

#ifndef MARKOVS_TEXT_CHAIN_MARKOVSCHAIN_H
#define MARKOVS_TEXT_CHAIN_MARKOVSCHAIN_H

#include <string>
#include <vector>
#include <unordered_map>
#include <random>

class MarkovsChain {
 public:
  explicit MarkovsChain(size_t chainCount);
  ~MarkovsChain();

  void process(const std::vector<std::string> &vec);

  void generate(const std::string &phrase, size_t chainCount);

  void print();
  void print(std::ostream & ostr);

  void toFile(const std::string &path);

  void dump(const std::string &path);
  void riseDump(const std::string &path);

 private:
  std::unordered_map<std::string, std::vector<size_t >> _chain;
  std::vector<std::string> _dictionary;
  std::random_device _rd;
  size_t _chainCount;

  std::vector<size_t> _findAllNext(const std::vector<std::string> &vec, const std::string &word);
};

#endif //MARKOVS_TEXT_CHAIN_MARKOVSCHAIN_H
