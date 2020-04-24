#include "MarkovsChain.h"
#include "Tokenizer.h"
#include <CommandLineParser.h>

#include <iostream>

namespace {

constexpr auto chainSequenceArg = "--chainsequence";
constexpr auto mcdumpArg = "--mcdump";
constexpr auto phraseArg = "--phrase";

void help() {
  std::cout << "usage:\n\t--chainsequence \' positive digital\' --mcdump "
               "\'file for markovs chain dump\' --phrase \'some phrase\'";
}

void print_markovs_chain(const std::string &dumpFile, const std::string &phrase, const size_t chainSequence) {
  auto mc = MarkovsChain::riseDump(dumpFile);
  std::wcout << mc.generate(string_manipulation::toWstring(phrase), chainSequence) << std::endl;
}

} // namespace

int main(int argc, char *argv[]) {
#if defined __APPLE__
  setlocale(LC_ALL, "en_US.UTF-8");
#else
  setlocale(LC_ALL, "en_US.UTF8");
#endif

  std::string dumpFile;
  std::string phrase;
  size_t chainSequence = 0;

  try {
    command_line::Parser parser(argc, argv);
    dumpFile = parser.get(mcdumpArg);
    phrase = parser.get(phraseArg);
    chainSequence = std::stoul(parser.get(chainSequenceArg));

    print_markovs_chain(dumpFile, phrase, chainSequence);
  } catch (const std::exception &exc) {
    std::cerr << exc.what() << std::endl;
    help();
  }

  return 0;
}