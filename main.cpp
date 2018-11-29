#include <iostream>

#include "FileDownloader.h"

int main(int argc, char *argv[]) {
// vpn:dfererw63dfa32@
  setlocale(LC_ALL, "Russian");
  std::cout << argv[0] << std::endl;
  std::list<std::string> urls{"file:///mnt/d/workspace/cpp/markovs_text_chain/cmake-build-debug-wsl/test_urls/tu1.txt"};
  FileDownloader fd(urls);
  fd.download("urls");
  return 0;
}