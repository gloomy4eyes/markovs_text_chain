#include "Tokenizer.h"

#include <algorithm>
#include <cassert>
#include <codecvt>
#include <locale>

namespace string_manipulation {

using convert_type = std::codecvt_utf8<wchar_t>;

std::wstring toWstring(const std::string &str) {
  std::wstring_convert<convert_type, wchar_t> converter;
  std::wstring converted_str = converter.from_bytes(str);
  return converted_str;
}

std::string toString(const std::wstring &str) {
  std::wstring_convert<convert_type, wchar_t> converter;
  std::string converted_str = converter.to_bytes(str);
  return converted_str;
}

void toLower(std::wstring &str) {
  std::transform(std::begin(str), std::end(str), std::begin(str), [](auto c) {
    auto &f = std::use_facet<std::ctype<wchar_t>>(std::locale());
    return f.tolower(c);
  });
}

tokens_t tokenize(const std::wstring &string) {
  tokens_t tokens;
  std::wstring chunk;
  auto &f = std::use_facet<std::ctype<wchar_t>>(std::locale());
  bool isChunkReady{false};

  for (size_t i = 0; i < string.size();) {
    auto &symbol = string[i];
    if (!iswalpha(static_cast<wint_t>(symbol))) {
      isChunkReady = true;
    } else {
      chunk.push_back(f.tolower(symbol));
    }

    if (isChunkReady || (i + 1 == std::wstring::npos)) {
      isChunkReady = false;
      if (!chunk.empty()) {
        tokens.push_back(chunk);
        chunk.clear();
      }
    }

    ++i;
  }

  return tokens;
}

tokens_t split(const std::wstring &string, const std::wstring &separator) {
  size_t posIndex{0};
  size_t separatorIndex{0};
  tokens_t vec;

  while (separatorIndex != std::string::npos) {
    separatorIndex = string.find(separator, posIndex);
    if (separatorIndex != std::string::npos) {
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

std::wstring join(const std::deque<std::wstring> &dec, const std::wstring &separator) {
  assert(!dec.empty());
  std::wstring s;
  for (auto t = std::begin(dec); t != std::end(dec);) {
    s.append(*t++);
    if (t != std::end(dec)) {
      s.append(separator);
    }
  }
  return s;
}

} // namespace string_manipulation
