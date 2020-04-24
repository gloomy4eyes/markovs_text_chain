#include "CommandLineParser.h"

namespace {

bool is_command(const std::string &command) {
  if (command.size() < 2) {
    return false;
  }

  if ((command.size() == 2) && (command[0] == '-') && (command[1] != '-')) {
    return true;
  }

  return ((command.size() > 2) && (command[0] == '-') && (command[1] == '-') && (command[2] != '-'));
}

command_line::arguments_t parse_arguments(int argc, char *argv[]) {
  command_line::arguments_t arguments;

  for (int i = 1; i < argc; ++i) {
    std::string curArgument = argv[i];

    if (is_command(curArgument)) {
      arguments.emplace(curArgument, argv[++i]);
    }
  }

  return arguments;
}

} // namespace

namespace command_line {

Parser::Parser(int argc, char **argv) : m_arguments(parse_arguments(argc, argv)) {}

std::string Parser::get(const std::string &key, bool required) {
  const auto found = m_arguments.find(key);
  if (found == m_arguments.end()) {
    if (required) {
      throw std::runtime_error(std::string("no such key:").append(key).append(" or empty value"));
    }

    return {};
  }

  return found->second;
}

} // namespace command_line
