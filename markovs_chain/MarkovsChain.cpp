#include "MarkovsChain.h"
#include "Tokenizer.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

namespace {

MarkovsChain::probabilities_t findProbabilities(MarkovsChain::dictionary_t &dictionary, const std::wstring &word,
                                                const size_t chainCount) {
  auto vecIt = dictionary.begin();

  auto v = string_manipulation::split(word, L",");

  MarkovsChain::probabilities_t probabilities;
  while (vecIt != dictionary.end()) {
    vecIt = std::search(dictionary.begin() + std::distance(dictionary.begin(), vecIt), dictionary.end(), v.begin(),
                        v.end());
    if (vecIt != dictionary.end()) {
      if (((vecIt + chainCount) != dictionary.end())) {
        vecIt += chainCount;
        auto found = std::find(dictionary.begin(), dictionary.end(), *vecIt);
        if (found != std::end(dictionary)) {
          probabilities.push_back(static_cast<size_t>(found - dictionary.begin()));
        } else {
          dictionary.push_back(*vecIt);
          probabilities.push_back(static_cast<size_t>(dictionary.size() - 1));
        }
      } else {
        break;
      }
    }
  }

  return probabilities;
}

void addChainPart(const std::wstring &it, MarkovsChain::dictionary_t &dictionary, MarkovsChain::window_t &window,
                  MarkovsChain::chain_t &chain, const size_t chainCount) {
  auto str = string_manipulation::join(window, L",");

  if (std::none_of(chain.begin(), chain.end(), [&str](const auto &pair) { return pair.first == str; })) {
    for (auto &word : window) {
      if (std::none_of(dictionary.begin(), dictionary.end(),
                       [&word](const auto &dictWord) { return dictWord == word; })) {
        dictionary.push_back(word);
      }
    }

    chain.emplace(str, findProbabilities(dictionary, str, chainCount));
  }

  window.pop_front();
  window.push_back(it);
}

void riseChainPart(const std::wstring &line, MarkovsChain::chain_t &chain) {
  auto tokens = string_manipulation::split(line, L":");

  if (tokens.empty()) {
    return;
  }

  auto &key = *tokens.begin();
  chain.emplace(key, std::vector<size_t>());

  for (auto value = tokens.begin() + 1; value != tokens.end(); ++value) {
    auto probabilities = string_manipulation::split(*value, L"|");

    for (const auto &probability : probabilities) {
      chain.at(key).push_back(stoi(probability));
    }
  }
}

} // namespace

MarkovsChain::MarkovsChain(size_t chainCount) : m_chainCount(chainCount) {}

void MarkovsChain::learn(const dictionary_t &dictionary) {
  if (dictionary.size() < m_chainCount) {
    std::cerr << "to few data" << std::endl;
    return;
  }
  m_window.clear();
  for (size_t i = 0; i < m_chainCount; ++i) {
    m_window.push_back(dictionary[i]);
  }
  for (auto word = dictionary.begin() + m_chainCount; word != dictionary.end(); ++word) {
    addChainPart(*word, m_dictionary, m_window, m_chain, m_chainCount);
  }
}

void MarkovsChain::learn(const std::string &data) {
  std::istringstream istr(data);
  std::string line;
  while (std::getline(istr, line)) {
    if (!line.empty()) {
      auto tmp = string_manipulation::toWstring(line);
      auto tmp1 = string_manipulation::tokenize(tmp);
      learn(tmp1);
    }
  }
}

std::wstring MarkovsChain::generate(const std::wstring &phrase, size_t sequenceCount) {
  if (phrase.empty()) {
    return {};
  }

  if (m_chainCount == 0) {
    auto vec = string_manipulation::split(m_chain.begin()->first, L",");
    m_chainCount = vec.size();
  }

  auto tokens = string_manipulation::tokenize(phrase);

  std::deque<std::wstring> deq(std::begin(tokens) + tokens.size() - m_chainCount, std::end(tokens));
  std::wstring str = string_manipulation::join(deq, L",");

  std::wostringstream ss;
  auto &ostr = ss;
  ostr << "START " << phrase << " ";

  std::random_device rd;

  try {
    while (sequenceCount > 0) {
      auto &it = m_chain.at(str);
      if (!it.empty()) {
        std::uniform_int_distribution<int> dist(0, it.size() - 1);
        auto randomIndex = static_cast<size_t>(dist(rd));
        str = m_dictionary.at(it.at(randomIndex));
        ostr << str << " ";
        deq.pop_front();
        deq.push_back(str);
        str = string_manipulation::join(deq, L",");
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
  for (auto &e : m_chain) {
    ostr << e.first << " : ";
    auto &v = e.second;

    for (auto it = std::begin(v); it != std::end(v); ++it) {
      ostr << m_dictionary.at(*it);

      if (it + 1 != std::end(v)) {
        ostr << "|";
      }
    }

    ostr << std::endl;
  }
}

void MarkovsChain::dump(const std::string &path) {
  std::wofstream ofs(path);
  if (ofs.bad()) {
    throw std::runtime_error("file " + path + " open error: " + std::to_string(errno));
  }

  dump(ofs);

  if (ofs.bad()) {
    throw std::runtime_error("file " + path + " is bad, error: " + std::to_string(errno));
  }
}

void MarkovsChain::dump(std::wostream &ostr) {
  for (const auto &pair : m_chain) {
    auto &chain = pair.first;
    ostr << chain << ":";
    auto &probabilities = pair.second;
    auto &v = probabilities;
    for (auto probability = probabilities.begin(); probability != probabilities.end(); ++probability) {
      ostr << *probability;
      if (probability + 1 != probabilities.end()) {
        ostr << "|";
      }
    }
    ostr << '\n';
  }
  ostr << "\nDICTIONARY\n";
  for (auto it = m_dictionary.begin(); it != m_dictionary.end(); ++it) {
    auto &word = *it;
    ostr << word;
    if (it + 1 != m_dictionary.end()) {
      ostr << "|";
    }
  }
  ostr << '\n';
}

MarkovsChain MarkovsChain::riseDump(std::wistream &istr) {
  std::wstring line;
  bool isDic{false};

  MarkovsChain mc;
  while (std::getline(istr, line)) {
    if (!line.empty()) {
      if (!isDic) {
        auto colon_position = line.find_first_of(':');
        if (colon_position != std::string::npos) {
          riseChainPart(line, mc.m_chain);
        } else {
          if (line == L"DICTIONARY") {
            isDic = true;
          }
        }
      } else {
        mc.m_dictionary = string_manipulation::split(line, L"|");
      }
    }
  }

  return mc;
}

MarkovsChain MarkovsChain::riseDump(const std::string &path) {
  std::wifstream ifs(path);
  if (!ifs.is_open()) {
    throw std::runtime_error("file" + path + " open error: " + std::to_string(errno));
  }

  return riseDump(ifs);
}
