#include "Tokenizer.h"
#include <algorithm>
#include <cassert>
#include <cstring>

using char_t = std::string::value_type;

bool isSym(char sym);
char_t lowcase(char_t ch);

const static std::string UPPER_DIC("ABCDEFGHIJKLMNOPQRSTUVWXYZАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
const static std::string LOWER_DIC("ABCDEFGHIJKLMNOPQRSTUVWXYZАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");

//std::array<char, 56> UPPER_LET {'ABCDEFGHIJKLMNOPQRSTUVWXYZ',
//                            'АБ' , 'ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ'};
//
//std::array<char, 56> LOWER_LET {'abcdefghijklmnopqrstuvwxyz',
//                            'абвгдеёжзийклмнопрстуфхцчшщъыьэюя'};
//
//
void toLower(std::string & str) {
  for (auto & s : str) {
    for (int i = 0; i < UPPER_DIC.size(); ++i) {
      if (s == UPPER_DIC[i]) {
        s = LOWER_DIC[i];
        break;
      }
    }
  }
}

std::vector<std::string> Tokenizer::tokenize(const std::string &string) {
  assert(!string.empty());

  std::string chunk;
  std::vector<std::string> _tokens;
  for (auto &it : string) {
    if (!isSym(it)) {
//      chunk.push_back(lowcase(it));
      chunk.push_back(it);
    } else {
      if (!chunk.empty()) {
        toLower(chunk);
        _tokens.push_back(chunk);
        chunk.clear();
      }
    }
  }
  if (!chunk.empty()) {
    _tokens.push_back(chunk);
    chunk.clear();
  }
  return _tokens;
}

char_t lowcase(char_t ch) {
  return std::use_facet<std::ctype<char_t>>(std::locale()).tolower(ch);
}

bool isSym(char sym) {
  switch (sym) {
  case '`':
  case '~':
  case '!':
  case '@':
  case '"':
  case '#':
  case '$':
  case ';':
  case '%':
  case '^':
  case ':':
  case '&':
  case '?':
  case '*':

  case '(':
  case ')':

  case '-':
  case '_':

  case '+':
  case '=':

  case '{':
  case '}':
  case '[':
  case ']':

  case '/':
  case '\\':
  case '|':

  case '\'':

  case '<':
  case '>':

  case '.':
  case ',':
  case ' ':

  case '\a':
  case '\b':
  case '\f':
  case '\n':
  case '\r':
  case '\t':
  case '\v':
    return true;
  default:
    return false;
  }
}