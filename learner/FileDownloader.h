#ifndef MARKOVS_TEXT_CHAIN_FILEDOWNLOADER_H
#define MARKOVS_TEXT_CHAIN_FILEDOWNLOADER_H

#include <vector>
#include <string>
#include <sstream>


class Curl;

class FileDownloader {
 public:
  explicit FileDownloader(std::vector<std::string> &urls);
  ~FileDownloader();

  std::istream &download();
  bool isDone();

  static std::istream & download(const std::string& url);

 private:
  std::vector<std::string> _urls;
  bool _done;
  std::vector<std::string>::iterator _curItem;

};

#endif //MARKOVS_TEXT_CHAIN_FILEDOWNLOADER_H
