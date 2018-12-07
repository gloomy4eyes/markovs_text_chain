#include <iostream>

#include "FileDownloader.h"
#include "MarkovsChain.h"

int main(int argc, char *argv[]) {
// vpn:dfererw63dfa32@
  setlocale(LC_ALL, "ru_RU.UTF8");
  std::list<std::string> urls;
  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu1.txt");
  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu2.txt");
  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu3.txt");
  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu4.txt");
  urls.emplace_back("https://www.litmir.me/br/?b=631463");
  urls.emplace_back("https://libreed.ru/sataninskoe-tango.html/[1-6]");
  urls.emplace_back("https://habr.com/post/138862/");
//  std::list<std::string> urls{"file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tutest.txt"};

  MarkovsChain mc(0);
  FileDownloader fd(urls, mc);
  fd.download("urls");
//  mc.print();
//  mc.toFile("../mc.txt");
  mc.generate("может", 1000);

  return 0;
}