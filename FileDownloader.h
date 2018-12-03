#ifndef MARKOVS_TEXT_CHAIN_FILEDOWNLOADER_H
#define MARKOVS_TEXT_CHAIN_FILEDOWNLOADER_H

#include <list>
#include <string>

//using CURL = void;

class MarkovsChain;

class FileDownloader {
 public:
  explicit FileDownloader(std::list<std::string> & urls, MarkovsChain & mc);
  ~FileDownloader();

  void download(const std::string& destinationPath);

  std::string generateUid();

 private:
//  CURL *_curl;
  std::list<std::string> _urls;
  MarkovsChain & _mc;
};

#endif //MARKOVS_TEXT_CHAIN_FILEDOWNLOADER_H
