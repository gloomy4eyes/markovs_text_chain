#include "MarkovsChain.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>

#include "Tokenizer.h"

MarkovsChain::MarkovsChain(size_t chainCount) : _chainCount(chainCount) {}

void MarkovsChain::_addChainPart(const std::wstring &it, const std::vector<std::wstring> &vec) {
  auto str = Tokenizer::join(_window, L",");
  auto iterator = _chain.find(str);
  if (iterator == std::end(_chain)) {
    for (auto & word : _window) {
      if (std::find(std::begin(_dictionary), std::end(_dictionary), word) == std::end(_dictionary)) {
        _dictionary.push_back(word);
      }
    }
    _chain.emplace(str, _findAllNext(vec, str));
  }
  _window.pop_front();
  _window.push_back(it);
}

void MarkovsChain::learn(const std::vector<std::wstring> &vec) {
  if (vec.size() < _chainCount) {
    std::cerr << "to few data" << std::endl;
    return;
  }
  _window.clear();
  for (size_t i = 0; i < _chainCount; ++i) {
    _window.push_back(vec[i]);
  }
  for (auto it = std::begin(vec) + _chainCount; it != std::end(vec); ++it) {
    _addChainPart(*it, vec);
  }
}

MarkovsChain::~MarkovsChain() {}

std::vector<size_t> MarkovsChain::_findAllNext(const std::vector<std::wstring> &vec, const std::wstring &word) {
  auto vecIt = vec.begin();

  auto v = Tokenizer::split(word, L",");

  std::vector<size_t> retV;
  while (vecIt != std::end(vec)) {
    vecIt = std::search(std::begin(vec) + std::distance(std::begin(vec), vecIt), std::end(vec), std::begin(v), std::end(v));
    if (vecIt != std::end(vec)) {
      if (((vecIt + _chainCount) != std::end(vec))) {
        vecIt += _chainCount;
//        std::wstring strs =  *vecIt;
        auto found = std::find(std::begin(_dictionary), std::end(_dictionary), *vecIt);
        if (found != std::end(_dictionary)) {
          retV.push_back((size_t)(found - std::begin(_dictionary)));
        } else {
          _dictionary.push_back(*vecIt);
          retV.push_back((size_t)(_dictionary.size() - 1));
        }
      } else {
        break;
      }
    }
  }
  return retV;
}

std::wstring MarkovsChain::generate(const std::wstring &phrase, size_t sequenceCount) {
  assert(!phrase.empty());
  if (phrase.empty()) {
    return {};
  }
  if (_chainCount == 0) {
    auto vec = Tokenizer::split(_chain.begin()->first, L",");
    _chainCount = vec.size();
  }

  auto tokens = Tokenizer::tokenize(phrase);
  assert(!tokens.empty());
  std::deque<std::wstring> deq(std::begin(tokens) + tokens.size() - _chainCount, std::end(tokens));
  std::wstring str = Tokenizer::join(deq, L",");
  assert(!str.empty());
  std::wostringstream ss;
  auto &ostr = ss;
  ostr << "START " << phrase << " ";

  try {
    while (sequenceCount > 0) {
      auto &it = _chain.at(str);
      if (!it.empty()) {
        std::uniform_int_distribution<int> dist(0, it.size() - 1);
        auto randomIndex = static_cast<size_t>(dist(_rd));
        str = _dictionary.at(it.at(randomIndex));
        ostr << str << " ";
        deq.pop_front();
        deq.push_back(str);
        str = Tokenizer::join(deq, L",");
        --sequenceCount;
      } else {
        ostr << " NO MORE WORDS.";
        break;
      }
    }
  } catch (const std::out_of_range &) {
    ostr << "dont know word: " << str;
  }

  ostr << " END" << std::endl;
  return ss.str();
}

void MarkovsChain::toFile(const std::string &path) {
  std::wofstream ofs(path);
  if (ofs.is_open()) {
    print(ofs);
  } else {
    throw std::runtime_error("file" + path + " open error: " + std::to_string(errno));
  }
}

void MarkovsChain::print() {
  std::wostream &ostr = std::wcout;
  print(ostr);
}

void MarkovsChain::print(std::wostream &ostr) {
  for (auto & e : _chain) {
    ostr << e.first << " : ";
    auto &v = e.second;
    for (auto it = std::begin(v); it != std::end(v); ++it) {
      ostr << _dictionary.at(*it);
      if (it + 1 != std::end(v)) {
        ostr << "|";
      }
    }
    ostr << std::endl;
  }
}

void MarkovsChain::dump(const std::string &path) {
  std::wofstream ofs(path);
  if (!ofs.is_open()) {
    throw std::runtime_error("file" + path + " open error: " + std::to_string(errno));
  }
  for (auto& c : _chain) {
    ofs << c.first << ":";
    auto &v = c.second;
    for (auto it  = std::begin(v); it != std::end(v); ++it) {
      ofs << *it;
      if (it + 1 != std::end(v)) {
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
  std::wifstream ifs(path);
  if (!ifs.is_open()) {
    throw std::runtime_error("file" + path + " open error: " + std::to_string(errno));
  }
  std::wstring line;
  bool isDic{false};

  _chain.clear();
  _dictionary.clear();
  while (std::getline(ifs, line)) {
    if (!line.empty()) {
      if (!isDic) {
        auto iter = line.find_first_of(':');
        if (iter != std::string::npos) {
          _riseChainPart(line);
        } else {
          if(line == L"DICTIONARY") {
            isDic = true;
          }
        }
      } else {
        _dictionary = Tokenizer::split(line, L"|");
      }
    }
  }
}

void MarkovsChain::_riseChainPart(const std::wstring &line) {
  auto v = Tokenizer::split(line, L":");
  if (!v.empty()) {
    auto &str = *v.begin();
    _chain.emplace(str, std::vector<size_t >());
    for (auto it = v.begin() + 1; it != v.end(); ++it) {
      auto s = Tokenizer::split(*it, L"|");
      for (auto iit = std::begin(s); iit != std::end(s); ++iit) {
        _chain.at(str).push_back(stoi(*iit));
      }
    }
  }
}


