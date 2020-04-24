#include "CommandLineParser.h"
#include "CurlDownloader.h"
#include <MarkovsChain.h>

#include <fstream>
#include <iostream>
#include <list>

namespace {
constexpr auto chainCountArg = "--chaincount";
constexpr auto fileArg = "--file";
constexpr auto mcdumpArg = "--mcdump";

void help() {
  std::cout << "usage:\n\t--file \'file with text or urls\' --chaincount \' "
               "positive digital\' --mcdump \'file for markovs chain dump\'";
}

using fileLines_t = std::list<std::string>;
fileLines_t get_lines_from_file(const std::string &filePath) {
  std::ifstream ifs(filePath);

  if (!ifs.is_open()) {
    throw std::runtime_error(std::string("error on urls file open - ") + strerror(errno));
  }

  fileLines_t fileLines;
  std::string line;

  while (std::getline(ifs, line)) {
    if (line.back() == '\r') {
      line.pop_back();
    }

    fileLines.push_back(line);
  }

  return fileLines;
}

bool line_is_url(const std::string &line) {
  if (line.size() < 4) {
    return false;
  }

  return ((line[0] == 'h') && (line[1] == 't') && (line[2] == 't') && (line[3] == 'p'));
}
} // namespace

int main(int argc, char *argv[]) {
#if defined __APPLE__
  setlocale(LC_ALL, "en_US.UTF-8");
#else
  setlocale(LC_ALL, "en_US.UTF8");
#endif

  try {
    command_line::Parser parser(argc, argv);

    const auto lines = get_lines_from_file(parser.get(fileArg));
    MarkovsChain mc(std::stoull(parser.get(chainCountArg)));
    CurlDownloader curl;

    for (const auto &line : lines) {
      mc.learn((line_is_url(line)) ? curl.download(line) : line);
    }

    mc.dump(parser.get(mcdumpArg));
  } catch (const std::exception &exc) {
    std::cerr << exc.what() << std::endl;
    help();
  }

  return 0;
}