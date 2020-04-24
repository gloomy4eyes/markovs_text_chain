#pragma once

#include <deque>
#include <list>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

class MarkovsChain {
public:
  using probabilities_t = std::vector<size_t>;
  using chain_t = std::unordered_map<std::wstring, probabilities_t>;
  using dictionary_t = std::vector<std::wstring>;
  using window_t = std::deque<std::wstring>;

  MarkovsChain() = default;
  explicit MarkovsChain(size_t chainCount);

  ~MarkovsChain() = default;

  MarkovsChain(const MarkovsChain &rhs) = default;
  MarkovsChain(MarkovsChain &&rhs) = default;
  MarkovsChain &operator=(const MarkovsChain &rhs) = default;
  MarkovsChain &operator=(MarkovsChain &&rhs) = default;

  using tokens_t = std::vector<std::wstring>;

  void learn(const tokens_t &dictionary);
  void learn(const std::string &data);

  std::wstring generate(const std::wstring &phrase, size_t sequenceCount);

  void print();
  void print(std::wostream &ostr);

  void toFile(const std::string &path);

  void dump(const std::string &path);
  void dump(std::wostream &ostr);

  static MarkovsChain riseDump(const std::string &path);
  static MarkovsChain riseDump(std::wistream &istr);

private:
  chain_t m_chain;
  dictionary_t m_dictionary;
  window_t m_window;
  size_t m_chainCount = 0;
};
