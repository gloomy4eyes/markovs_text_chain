#ifndef MARKOVS_TEXT_CHAIN_TOKENIZER_H
#define MARKOVS_TEXT_CHAIN_TOKENIZER_H

#include <vector>
#include <string>
#include <deque>

 class Tokenizer {
  public:
   static std::vector<std::string> tokenize(const std::string &string);
   static std::vector<std::string> split(const std::string &string, const std::string &separator);
   static std::string join(const std::vector<std::string> &vec, const std::string &separator);
   static std::string join(const std::deque<std::string> &dec, const std::string &separator);

//   static void toLower(std::string& str);

  private:
   Tokenizer() = default;
   ~Tokenizer() = default;

};

#endif //MARKOVS_TEXT_CHAIN_TOKENIZER_H
