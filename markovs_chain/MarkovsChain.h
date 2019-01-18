#ifndef MARKOVS_TEXT_CHAIN_MARKOVSCHAIN_H
#define MARKOVS_TEXT_CHAIN_MARKOVSCHAIN_H

#include <string>
#include <vector>
#include <unordered_map>
#include <random>
#include <deque>
#include <iterator>

class MarkovsChain {
 public:
  explicit MarkovsChain(size_t chainCount);
  ~MarkovsChain();

  void learn(const std::vector<std::wstring> &vec);

  std::wstring generate(const std::wstring &phrase, size_t sequenceCount);

  void print();
  void print(std::wostream & ostr);

  void toFile(const std::string &path);

  void dump(const std::string &path);
  void riseDump(const std::string &path);

 private:
  std::unordered_map<std::wstring, std::vector<size_t>> _chain;
  std::vector<std::wstring> _dictionary;
  std::deque<std::wstring> _window;
  std::random_device _rd;
  size_t _chainCount;

  std::vector<size_t> _findAllNext(const std::vector<std::wstring> &vec, const std::wstring &word);
  void _riseChainPart(const std::wstring &line);
  void _addChainPart(const std::wstring &it, const std::vector<std::wstring> &vec);

};

#endif //MARKOVS_TEXT_CHAIN_MARKOVSCHAIN_H
