//
// Created by front on 30.11.2018.
//

#include <algorithm>
#include "MarkovsChain.h"
#include <iostream>
#include "Tokenizer.h"
#include <fstream>

MarkovsChain::MarkovsChain() {

}
void MarkovsChain::process(const std::vector<std::string> &vec) {

  for (auto & word : vec) {
//    _chain.emplace(word);
    _chain[word];
  }

  for (auto & t : _chain) {
    for (auto & an : _findAllNext(vec, t.first)) {
      t.second.emplace_back(an) ;
    }
  }
}

void MarkovsChain::print() {
  for (auto & e : _chain) {
    std::cout << e.first << " : ";
    for (auto it = e.second.begin(); it != e.second.end(); ++it) {
      auto iit = it;
      std::cout << *it;
      if (++iit != e.second.end()) {
        std::cout << " | ";
      }
    }
//    for (auto & w : e.second) {
//      std::cout << w << " | ";
//    }
    std::cout << std::endl;
  }
}

MarkovsChain::~MarkovsChain() {}

std::vector<std::string> MarkovsChain::_findAllNext(const std::vector<std::string> &vec, const std::string & word) {
  auto vecIt = vec.begin();

  std::vector<std::string> retV;
  while (vecIt != std::end(vec)) {
    vecIt = std::find(vecIt, std::end(vec), word);
    if (vecIt != std::end(vec) && (++vecIt != std::end(vec))) {
      retV.push_back(*vecIt);
    }
  }

  return retV;
}
void MarkovsChain::generate(const std::string &phrase, size_t chainCount) {
  auto tokens = Tokenizer::tokenize(phrase, ' ');

  auto str = tokens.back();

  std::cout << phrase << " ";
  while (chainCount > 0) {
    auto it = _chain.find(str);
    if (it == _chain.end()) {
      break;
    }
    auto &tv = it->second;
    std::uniform_int_distribution<int> dist(0, tv.size() - 1);
    size_t randomIndex = dist(_rd);
    str = tv[randomIndex];
    std::cout << str << " ";
    --chainCount;
  }
  std::cout << std::endl;
}

void MarkovsChain::toFile(const std::string &path) {
  std::ofstream ofs(path);
  for (auto & e : _chain) {
    ofs << e.first << " : ";
    for (auto it = e.second.begin(); it != e.second.end(); ++it) {
      auto iit = it;
      ofs << *it;
      if (++iit != e.second.end()) {
        ofs << " | ";
      }
    }
//    for (auto & w : e.second) {
//      std::cout << w << " | ";
//    }
    ofs << std::endl;
  }
}
