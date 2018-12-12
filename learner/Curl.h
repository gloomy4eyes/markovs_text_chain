#ifndef MARKOVS_TEXT_CHAIN_CURL_H
#define MARKOVS_TEXT_CHAIN_CURL_H

#include <iostream>
#include <sstream>

using CURL = void;

class Curl {
 public:
  Curl();
  virtual ~Curl();

  std::string download(const std::string &url);

 private:
  CURL *_curl;
};

#endif //MARKOVS_TEXT_CHAIN_CURL_H
