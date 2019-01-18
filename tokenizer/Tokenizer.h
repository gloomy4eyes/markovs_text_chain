#ifndef MARKOVS_TEXT_CHAIN_TOKENIZER_H
#define MARKOVS_TEXT_CHAIN_TOKENIZER_H

#include <vector>
#include <string>
#include <deque>

 class Tokenizer {
  public:
   static std::vector<std::wstring> tokenize(const std::wstring &string);
   static std::vector<std::wstring> split(const std::wstring &string, const std::wstring &separator);
//   static std::string join(const std::vector<std::string> &vec, const std::string &separator);
   static std::wstring join(const std::deque<std::wstring> &dec, const std::wstring &separator);
   static void toLower(std::wstring & str);

   static std::string wstringToString(const std::wstring &str);
   static std::wstring stringToWstring(const std::string &str);

  private:
   Tokenizer() = default;
   ~Tokenizer() = default;

};

#endif //MARKOVS_TEXT_CHAIN_TOKENIZER_H
