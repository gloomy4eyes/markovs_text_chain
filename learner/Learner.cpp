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

  std::vector<std::string> urls;
//  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu1.txt");
  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu2.txt");
  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu3.txt");
  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu4.txt");
  urls.emplace_back("https://www.litmir.me/br/?b=631463");
  urls.emplace_back("https://libreed.ru/sataninskoe-tango.html/[1-6]");
  urls.emplace_back("https://libreed.ru/post-sdal.html/[1-25]");
  urls.emplace_back("https://habr.com/post/138862/");
//  std::list<std::string> urls{"file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tutest.txt"};

  MarkovsChain mc(std::stoull(_args.at(chainCountArg)));
  FileDownloader fd(urls);
  while (!fd.isDone()) {
    learn(fd.download(), mc);
  }

  mc.dump(_args.at(mcdumpArg));
}

Learner::Learner(int argc, char **argv) : _args(parseCommandArgs(argc, argv)) {}
