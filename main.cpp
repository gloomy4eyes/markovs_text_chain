#include <iostream>

#include "FileDownloader.h"

int main(int argc, char *argv[]) {
// vpn:dfererw63dfa32@
  setlocale(LC_ALL, "Russian");
  std::cout << argv[0] << std::endl;
  std::list<std::string> urls;
  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu1.txt");
  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu2.txt");
  urls.emplace_back("file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tu3.txt");
//  std::list<std::string> urls{"file:///mnt/d/workspace/cpp/markovs_text_chain/test_urls/tutest.txt"};
  FileDownloader fd(urls);
  fd.download("urls");
  return 0;
}