
#ifndef MARKOVS_TEXT_CHAIN_CURL_H
#define MARKOVS_TEXT_CHAIN_CURL_H

#include <iostream>
#include <sstream>

using CURL = void;

class Curl {
 public:
  Curl();

  std::istream & download(const std::string& url);

  virtual ~Curl();

 private:
  CURL *_curl;
  std::stringstream _ss;

};

#endif //MARKOVS_TEXT_CHAIN_CURL_H
