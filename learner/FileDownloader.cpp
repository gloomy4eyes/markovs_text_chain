#include "FileDownloader.h"

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fstream>
#include <cstring>
#include <sstream>
#include "tokenizer/Tokenizer.h"
#include "markovs_chain/MarkovsChain.h"
#include "Curl.h"

FileDownloader::FileDownloader(std::vector<std::string> &urls) : _urls(urls), _done(false), _curItem(_urls.begin()) {}

FileDownloader::~FileDownloader() {}

std::istream & FileDownloader::download() {
  Curl curl;
  if (_curItem != std::end(_urls)) {
    return curl.download(*_curItem++);
  } else {
    _done = true;
  }
  return curl.download("");
}

bool FileDownloader::isDone() {
  return _done;
}
std::istream &FileDownloader::download(const std::string &url) {
  Curl curl;
  return curl.download(url);;
}

//std::string FileDownloader::generateUid() {
//  srand(time(NULL));
//  std::string strUuid(36, '\0');
//  sprintf(&strUuid[0], "%x%x-%x-%x-%x-%x%x%x",
//          rand(), rand(),                 // Generates a 64-bit Hex number
//          rand(),                         // Generates a 32-bit Hex number
//          ((rand() & 0x0fff) | 0x4000),   // Generates a 32-bit Hex number of the form 4xxx (4 indicates the UUID version)
//          rand() % 0x3fff + 0x8000,       // Generates a 32-bit Hex number in the range [0x8000, 0xbfff]
//          rand(), rand(), rand());        // Generates a 96-bit Hex number
//  return strUuid;
//}


