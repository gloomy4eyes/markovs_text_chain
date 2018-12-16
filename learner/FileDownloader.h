#ifndef MARKOVS_TEXT_CHAIN_FILEDOWNLOADER_H
#define MARKOVS_TEXT_CHAIN_FILEDOWNLOADER_H

#include <vector>
#include <string>
#include <sstream>


class Curl;

class FileDownloader {
 public:
  explicit FileDownloader(const std::vector<std::string> &urls);
  ~FileDownloader();

  std::string download();
  bool isDone();

  static std::string download(const std::string &url);

 private:
  std::vector<std::string> _urls;
  bool _done;
  size_t _index;

};

#endif //MARKOVS_TEXT_CHAIN_FILEDOWNLOADER_H
