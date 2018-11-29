#include "Tokenizer.h"
#include <algorithm>
#include <cassert>
#include <cstring>

bool isSym(char sym) {
  switch (sym) {
    case '\r':
    case '\n':
    case ' ':
    case '.':
    case ',':
    case '<':
    case '>':return true;
    default:return false;
  }
}

std::vector<std::string> Tokenizer::tokenize(const std::string &string, char separator) {
  assert(!string.empty());
  size_t posBeg{0};
  size_t posEnd;
  std::vector<std::string> _tokens;
  while (true) {
    posEnd = string.find(separator, posBeg);
    if (posEnd == std::string::npos) {
      break;
    }
    std::string tmp = string.substr(posBeg, --posEnd - posBeg);
    trim(tmp);
//    for (auto it = tmp.begin(); it != tmp.end(); it++) {
//      if (!isalnum(*it)) {
//        tmp.erase(it);
//      }
//    }
    if (!tmp.empty()) {
      _tokens.emplace_back(tmp);
    }

    posBeg = ++++posEnd;
  }
  return _tokens;
}

void Tokenizer::trim(std::string &str) {
  size_t posB{0};
  size_t posE{0};

  auto f = strlen(&str[0]);
  for (size_t i = 0; i < f; ++i) {
    if (!isSym(str[i])) {
      posB = i;
      break;
    }
  }

  for (size_t i = f - 1; i > posB ; --i) {
    if (!isSym(str[i])) {
      posE = i;
      break;
    }
  }

  if (posB > 0) {
    str.erase(0, posB);
  }
  if (posE > 0) {
    str.erase(posE);
  }
}

