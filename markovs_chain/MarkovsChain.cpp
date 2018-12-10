#include "MarkovsChain.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <deque>
#include <cassert>
#include <sstream>

#include "tokenizer/Tokenizer.h"

MarkovsChain::MarkovsChain(size_t chainCount) : _chainCount(chainCount) {}

void MarkovsChain::learn(const std::vector<std::string> &vec) {
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

std::ostream & MarkovsChain::generate(const std::string &phrase, size_t chainCount) {
  assert(!phrase.empty());

  auto tokens = Tokenizer::tokenize(phrase);
  assert(!tokens.empty());

  auto str = tokens.back();
  assert(!str.empty());
  std::stringstream ss;
  auto &ostr = ss;
  ostr << "START " << phrase << " ";

  try {
    while (chainCount > 0) {
      auto &it = _chain.at(str);
      if (!it.empty()) {
        std::uniform_int_distribution<int> dist(0, it.size() - 1);
        auto randomIndex = static_cast<size_t>(dist(_rd));
        str = _dictionary.at(it.at(randomIndex));
        ostr << str << " ";
        --chainCount;
      } else {
        ostr << " NO MORE WORDS.";
        break;
      }
    }
  } catch (const std::out_of_range &) {
    ostr << "dont know word: " << str;
  }

  ostr << " END" << std::endl;
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
    auto &v = e.second;
    for (auto it = std::begin(v); it != std::end(v); ++it) {
      auto iit = it;
      ostr << _dictionary.at(*it);
      if (++iit != std::end(v)) {
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
    ofs << std::endl;
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

  _chain.clear();
  _dictionary.clear();
  while (std::getline(ifs, line)) {
    if (!line.empty()) {
      if (!isDic) {
        auto iter = line.find_first_of(':');
        if (iter != std::string::npos) {
          riseChainPart(line);
        } else {
          if(line == "DICTIONARY") {
            isDic = true;
          }
        }
      } else {
        _dictionary = Tokenizer::tokenize(line);
      }
    }
  }
}

void MarkovsChain::riseChainPart(const std::string &line) {
  auto v = Tokenizer::tokenize(line);
  if (!v.empty()) {
    auto &str = *v.begin();
    _chain.emplace(str, std::vector<size_t >());
    for (auto it = v.begin() + 1; it != v.end(); ++it) {
      _chain.at(str).push_back(stoi(*it));
    }
  }
}
