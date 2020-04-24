#pragma once

#include <deque>
#include <list>
#include <string>
#include <vector>

namespace string_manipulation {

using tokens_t = std::vector<std::wstring>;

tokens_t tokenize(const std::wstring &string);

tokens_t split(const std::wstring &string, const std::wstring &separator);

std::wstring join(const std::deque<std::wstring> &dec, const std::wstring &separator);

void toLower(std::wstring &str);

std::string toString(const std::wstring &str);

std::wstring toWstring(const std::string &str);

} // namespace string_manipulation
