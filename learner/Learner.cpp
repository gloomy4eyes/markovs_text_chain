#include <fstream>
#include <cstring>
#include "Learner.h"

#include "FileDownloader.h"
#include "MarkovsChain.h"
#include "Tokenizer.h"

constexpr auto chainCountArg = "--chaincount";
constexpr auto urlsArg = "--urls";
constexpr auto mcdumpArg = "--mcdump";

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

  if (!checkArgument(cm, urlsArg) || !checkArgument(cm, chainCountArg) || !checkArgument(cm, mcdumpArg) || std::stoull(cm.at(chainCountArg)) < 1) {
    throw std::runtime_error("usage");
  }

  return cm;
}

void learn(const std::string &data, MarkovsChain &mc) {
  std::istringstream istr(data);
  std::string line;
  while (std::getline(istr, line)) {
    if (!line.empty()) {
      mc.learn(Tokenizer::tokenize(line));
    }
  }
}

void Learner::run() {
  std::ifstream ifs(_args.at(urlsArg));
  if (!ifs.is_open()) {
    throw std::runtime_error(std::string("error on urls file open - ") + strerror(errno));
  }

  std::vector<std::string> urls;
  std::string line;
  while (std::getline(ifs, line)) {
    if (line.back() == '\r') {
      line.pop_back();
    }
    urls.push_back(line);
  }

  MarkovsChain mc(std::stoull(_args.at(chainCountArg)));
  FileDownloader fd(urls);
  while (!fd.isDone()) {
    learn(fd.download(), mc);
  }

  mc.dump(_args.at(mcdumpArg));
}

Learner::Learner(int argc, char **argv) : _args(parseCommandArgs(argc, argv)) {}
