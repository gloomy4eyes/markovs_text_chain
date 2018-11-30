//
// Created by front on 30.11.2018.
//

#include <algorithm>
#include "MarkovsChain.h"
#include <iostream>

MarkovsChain::MarkovsChain() : isNewDict(true) {

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

void MarkovsChain::toFile() {
  for (auto & e : _chain) {
    std::cout << e.first << " : ";
    for (auto & w : e.second) {
      std::cout << w << " ";
    }
    std::cout << std::endl;
  }
}

MarkovsChain::~MarkovsChain() {}

std::vector<std::string> MarkovsChain::_findAllNext(const std::vector<std::string> &vec, const std::string & word) {
  auto vecIt = vec.begin();

  std::vector<std::string> retV;
  while (vecIt != std::end(vec)) {
    vecIt = std::find(vecIt, std::end(vec), word);
    if (vecIt != std::end(vec)) {
      ++vecIt;
      retV.push_back(*vecIt);
    }
  }

  return retV;
}
