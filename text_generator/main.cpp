#include <iostream>

#include "MarkovsChain.h"
#include "Tokenizer.h"

constexpr auto chainSequenceArg = "--chainsequence";
constexpr auto mcdumpArg = "--mcdump";
constexpr auto phraseArg = "--phrase";

using arguments = std::unordered_map<std::string, std::string>;

bool checkArgument(arguments & args, const std::string & arg) {
  auto checkItem = args.find(arg);
  return (checkItem != std::end(args)) ? !checkItem->second.empty() : false;
}

arguments parseCommandArgs(int argc, char* argv[]){
  if (argc != 7) {
    throw std::runtime_error("usage");
  }
  arguments cm;
  std::string curOption;
  for (int i = 1; i < argc; ++i) {
    curOption = argv[i];
    if (curOption[0] == '-' && curOption[1] == '-') {
      cm.emplace(curOption, argv[++i]);
    }
  }

  if (!checkArgument(cm, chainSequenceArg) || !checkArgument(cm, mcdumpArg) || !checkArgument(cm, phraseArg) || std::stoull(cm.at(chainSequenceArg)) < 1) {
    throw std::runtime_error("usage");
  }

  return cm;
}

void help() {
  std::cout << "usage:\n\t--chainsequence \' positive digital\' --mcdump \'file for markovs chain dump\' --phrase \'some phrase\'";
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "en_US.UTF8");
  try {
    auto args = parseCommandArgs(argc, argv);

    MarkovsChain mc(0);
    mc.riseDump(args.at(mcdumpArg));
    std::wcout << mc.generate(Tokenizer::stringToWstring(args.at(phraseArg)), std::stoull(args.at(chainSequenceArg))) << std::endl;
  } catch (const std::exception & exc) {
    std::cerr << exc.what() << std::endl;
  }

  return 0;
}