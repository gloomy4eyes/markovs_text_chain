#include "Tokenizer.h"
#include <algorithm>
#include <cassert>
#include <cstring>
#include <codecvt>
#include <locale>
#include <iostream>

using convert_type = std::codecvt_utf8<wchar_t>;

std::wstring Tokenizer::stringToWstring(const std::string &str) {
  std::wstring_convert<convert_type, wchar_t> converter;
  std::wstring converted_str = converter.from_bytes(str);
  return converted_str;
}

std::string Tokenizer::wstringToString(const std::wstring &str) {
  std::wstring_convert<convert_type, wchar_t> converter;
  std::string converted_str = converter.to_bytes(str);
  return converted_str;
}

void Tokenizer::toLower(std::wstring & str) {
  std::transform(std::begin(str), std::end(str), std::begin(str), [](wchar_t c){
    auto& f = std::use_facet<std::ctype<wchar_t>>(std::locale());
    return f.tolower(c);
  });
}

std::vector<std::wstring> Tokenizer::tokenize(const std::wstring &string) {
  assert(!string.empty());

  std::vector<std::wstring> _tokens;
  std::wstring chunk;
  auto& f = std::use_facet<std::ctype<wchar_t>>(std::locale());
  bool isChunkReady{false};
  for (auto it = std::begin(string); it != std::end(string);) {
    if (!iswalpha(static_cast<wint_t>(*it))) {
      isChunkReady = true;
    } else {
      chunk.push_back(f.tolower(*it));
    }
    if (isChunkReady || (it + 1 == std::end(string))) {
      isChunkReady = false;
      if (!chunk.empty()) {
        _tokens.push_back(chunk);
        chunk.clear();
      }
    }
    ++it;
  }
  return _tokens;
}

std::vector<std::wstring> Tokenizer::split(const std::wstring &string, const std::wstring &separator) {
  size_t posIndex{0};
  size_t separatorIndex{0};
  std::vector<std::wstring> vec;
  while (separatorIndex != std::string::npos) {
    separatorIndex = string.find(separator, posIndex);
    if (separatorIndex != std::string::npos) {
      std::wstring tmp(std::begin(string) + posIndex, std::begin(string) + separatorIndex);
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

std::wstring Tokenizer::join(const std::deque<std::wstring> &dec, const std::wstring &separator) {
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