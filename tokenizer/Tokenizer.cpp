#include "Tokenizer.h"
#include <algorithm>
#include <cassert>
#include <cstring>
#include <codecvt>
#include <locale>
#include <deque>

constexpr size_t DIC_SIZE = 59;
constexpr auto UPPER_DIC(L"ABCDEFGHIJKLMNOPQRSTUVWXYZАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
constexpr auto LOWER_DIC(L"abcdefghijklmnopqrstuvwxyzабвгдеёжзийклмнопрстуфхцчшщъыьэюя");

using convert_type = std::codecvt_utf8<wchar_t>;

std::wstring stringToWstring(const std::string &str) {
  std::wstring_convert<convert_type, wchar_t> converter;
  std::wstring converted_str = converter.from_bytes(str);
  return converted_str;
}

std::string wstringToString(const std::wstring &str) {
  std::wstring_convert<convert_type, wchar_t> converter;
  std::string converted_str = converter.to_bytes(str);
  return converted_str;
}

std::string toLower(std::string & str) {
  std::wstring tmpWStr = stringToWstring(str);
  std::wstring tmpWStr2;
  for (size_t i = 0; i < tmpWStr.size(); ++i) {
    for (size_t j = 0; j < DIC_SIZE; ++j) {
      if (tmpWStr[i] == UPPER_DIC[j]) {
        tmpWStr[i] = LOWER_DIC[j];
        break;
      }
    }
  }
  for (size_t i = 0; i < tmpWStr.size(); ++i) {
    if (iswalpha(tmpWStr[i])) {
      tmpWStr2.push_back(tmpWStr[i]);
    }
  }

  std::string retStr = wstringToString(tmpWStr2);
  return retStr;
}

bool isSym(char sym);

std::vector<std::string> Tokenizer::tokenize(const std::string &string) {
  assert(!string.empty());

  std::string chunk;
  std::vector<std::string> _tokens;
  for (auto &it : string) {
    if (!isSym(it)) {
      chunk.push_back(it);
    } else {
      if (!chunk.empty()) {
        _tokens.push_back(toLower(chunk));
        chunk.clear();
      }
    }
  }
  if (!chunk.empty()) {
    _tokens.push_back(toLower(chunk));
    chunk.clear();
  }
  return _tokens;
}

std::vector<std::string> Tokenizer::split(const std::string &string, const std::string &separator) {
  size_t posIndex{0};
  size_t separatorIndex{0};
  std::vector<std::string> vec;
  while (separatorIndex != std::string::npos) {
    separatorIndex = string.find(separator, posIndex);
    if (separatorIndex != std::string::npos) {
      std::string tmp(std::begin(string) + posIndex, std::begin(string) + separatorIndex);
      vec.push_back(string.substr(posIndex, separatorIndex - posIndex));
      if (separatorIndex + 1 != std::string::npos) {
        posIndex = ++separatorIndex;
      }
    } else {
      if (string.size() - posIndex > 0) {
        vec.push_back(string.substr(posIndex));
      }
    }
  }

  return vec;
}

std::string Tokenizer::join(const std::vector<std::string> &vec, const std::string &separator) {
  assert(!vec.empty());
  std::string s(*vec.begin());
  for (auto t = std::begin(vec) + 1; t != std::end(vec); ++t) {
    s.append(*t);
    if (t + 1 != std::end(vec)) {
      s.append(separator);
    }
  }
  return s;
}

std::string Tokenizer::join(const std::deque<std::string> &dec, const std::string &separator) {
  assert(!dec.empty());
  std::string s;
  for (auto t = std::begin(dec); t != std::end(dec);) {
    s.append(*t++);
    if (t != std::end(dec)) {
      s.append(separator);
    }
  }
  return s;
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