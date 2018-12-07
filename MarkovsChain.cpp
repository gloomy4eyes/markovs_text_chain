#include <algorithm>
#include "MarkovsChain.h"
#include <iostream>
#include "Tokenizer.h"
#include <fstream>
#include <deque>
#include <algorithm>
#include <cassert>

MarkovsChain::MarkovsChain(size_t chainCount) : _chainCount(chainCount) {}

void MarkovsChain::process(const std::vector<std::string> &vec) {
  for (auto & word : vec) {
    auto iterator = _chain.find(word);
    if (iterator == std::end(_chain)) {
      _dictionary.push_back(word);
      _chain.emplace(word, std::vector<size_t>());
    }
  }

  for (auto & t : _chain) {
    for (auto & an : _findAllNext(vec, t.first)) {
      t.second.emplace_back(an) ;
    }
  }
}

MarkovsChain::~MarkovsChain() {}

std::vector<size_t> MarkovsChain::_findAllNext(const std::vector<std::string> &vec, const std::string &word) {
  auto vecIt = vec.begin();

  std::vector<size_t> retV;
  while (vecIt != std::end(vec)) {
    vecIt = std::find(vecIt, std::end(vec), word);
    if (vecIt != std::end(vec) && (++vecIt != std::end(vec))) {
      auto found = std::find(std::begin(_dictionary), std::end(_dictionary), *vecIt);
      if (found != std::end(_dictionary)) {
        retV.push_back((size_t)(found - std::begin(_dictionary)));
      }
    }
  }
  return retV;
}
void MarkovsChain::generate(const std::string &phrase, size_t chainCount) {
  assert(!phrase.empty());

  auto tokens = Tokenizer::tokenize(phrase);
  assert(!tokens.empty());

  auto str = tokens.back();
  assert(!str.empty());

  std::cout << "START " << phrase << " ";

  try {
    while (chainCount > 0) {
      auto &it = _chain.at(str);
      if (!it.empty()) {
        std::uniform_int_distribution<int> dist(0, it.size() - 1);
        auto randomIndex = static_cast<size_t>(dist(_rd));
        str = _dictionary.at(it.at(randomIndex));
        std::cout << str << " ";
        --chainCount;
      } else {
        std::cout << " NO MORE WORDS.";
        break;
      }
    }
  } catch (const std::out_of_range &) {
    std::cerr << "dont know word: " << str;
  }

  std::cout << " END" << std::endl;
}

void MarkovsChain::toFile(const std::string &path) {
  std::ofstream ofs(path);
  if (ofs.is_open()) {
    print(ofs);
  } else {
    throw std::runtime_error("file" + path + " open error: " + std::to_string(errno));
  }
}

void MarkovsChain::print() {
  std::ostream &ostr = std::cout;
  print(ostr);
}

void MarkovsChain::print(std::ostream &ostr) {
  for (auto & e : _chain) {
    ostr << e.first << " : ";
    for (auto it = std::begin(e.second); it != std::end(e.second); ++it) {
      auto iit = it;
      ostr << _dictionary.at(*it);
      if (++iit != std::end(e.second)) {
        ostr << "|";
      }
    }
    ostr << std::endl;
  }
}

void MarkovsChain::dump(const std::string &path) {
  std::ofstream ofs(path);
  if (!ofs.is_open()) {
    throw std::runtime_error("file" + path + " open error: " + std::to_string(errno));
  }
  for (auto& c : _chain) {
    ofs << c.first << ":";
    auto &v = c.second;
    for (auto it  = std::begin(v); it != std::end(v); ++it) {
      auto iit = it;
      ofs << *it;
      if (++iit != std::end(v)) {
        ofs << "|";
      }
    }
  }
  ofs << "\nDICTIONARY\n";
  for (auto it  = std::begin(_dictionary); it != std::end(_dictionary); ++it) {
    ofs << *it;
    if (it + 1 != std::end(_dictionary)) {
      ofs << "|";
    }
  }
  ofs << std::endl;
}

void MarkovsChain::riseDump(const std::string &path) {
  std::ifstream ifs(path);
  if (!ifs.is_open()) {
    throw std::runtime_error("file" + path + " open error: " + std::to_string(errno));
  }
  std::string line;
  bool isDic{false};

  while (std::getline(ifs, line)) {
    if (!line.empty()) {
      if (!isDic) {
        auto iter = line.find_first_of(':');
        if (iter != std::string::npos) {
          // fill chain
        } else {
          if(line == "DICTIONARY") {
            isDic = true;
          }
        }
      } else {
        // fill dictionary
      }
    }
  }

  for (auto& c : _chain) {
    ofs << c.first << ":";
    auto &v = c.second;
    for (auto it  = std::begin(v); it != std::end(v); ++it) {
      auto iit = it;
      ofs << *it;
      if (++iit != std::end(v)) {
        ofs << "|";
      }
    }
  }
  ofs << "\nDICTIONARY\n";
  for (auto it  = std::begin(_dictionary); it != std::end(_dictionary); ++it) {
    ofs << *it;
    if (it + 1 != std::end(_dictionary)) {
      ofs << "|";
    }
  }
  ofs << std::endl;
}
