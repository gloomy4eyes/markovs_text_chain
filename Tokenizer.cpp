#include "Tokenizer.h"
#include <algorithm>
#include <cassert>
#include <cstring>
#include "Misc.h"

bool isSym(char sym) {
  switch (sym) {
    case '\r':
    case '\n':
    case ' ':
    case '.':
    case ',':
    case '<':
    case '>':
    case ':':
    case ';':
    case '!':
    case '?':
    case '/':
    case '\\':
    case '-':
    case '_':
    case '$':
      return true;
    default:return false;
  }
}

std::vector<std::string> Tokenizer::tokenize(const std::string &string, char separator) {
  assert(!string.empty());
  size_t posBeg{0};
  size_t posEnd;
  std::vector<std::string> _tokens;
  std::string tmp;
  bool doWork{true};
  while (doWork) {
    posEnd = string.find(separator, posBeg);
    if (posEnd == std::string::npos) {
      doWork = false;
      tmp = string.substr(posBeg);
    } else {
      tmp = string.substr(posBeg, posEnd - posBeg);
    }
    trim(tmp);
    if (!tmp.empty()) {
      _tokens.emplace_back(tmp);
    }

    posBeg = ++posEnd;
  }
  return _tokens;
}

void Tokenizer::trim(std::string &str) {
//  return;
  size_t posB{0};
  size_t posE{0};

  auto f = str.size();
  for (size_t i = 0; i < f - 1; ++i) {
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
  if (++posE > 0) {
    str.erase(posE);
  }
}

