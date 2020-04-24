#pragma once

#include <string>
#include <unordered_map>

namespace command_line {

using arguments_t = std::unordered_map<std::string, std::string>;

class Parser {
public:
  Parser(int argc, char *argv[]);

  std::string get(const std::string &key, bool required = true);

private:
  arguments_t m_arguments;
};

} // namespace command_line