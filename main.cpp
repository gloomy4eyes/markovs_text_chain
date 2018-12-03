#include <iostream>

#include "FileDownloader.h"
#include "MarkovsChain.h"

int main(int argc, char *argv[]) {
// vpn:dfererw63dfa32@
  setlocale(LC_ALL, "Russian");
  std::cout << argv[0] << std::endl;
  std::list<std::string> urls;
  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu1.txt");
  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu2.txt");
  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu3.txt");
  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu4.txt");
//  std::list<std::string> urls{"file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tutest.txt"};

  MarkovsChain mc;
  FileDownloader fd(urls, mc);
  fd.download("urls");
//  mc.toFile("../mc.txt");
  mc.generate("что", 5);

  return 0;
}