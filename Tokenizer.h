#ifndef MARKOVS_TEXT_CHAIN_TOKENIZER_H
#define MARKOVS_TEXT_CHAIN_TOKENIZER_H

#include <vector>
#include <string>
#include <iterator>

 class Tokenizer {
  public:
   static std::vector<std::string> tokenize(const std::string &string, char separator);
   static void trim(std::string& str);
   static void toLower(std::string& str);

  private:
   Tokenizer() = default;
   ~Tokenizer() = default;

};

#endif //MARKOVS_TEXT_CHAIN_TOKENIZER_H
