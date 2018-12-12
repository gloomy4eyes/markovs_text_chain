#include "FileDownloader.h"

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fstream>
#include <cstring>
#include <sstream>
#include "Tokenizer.h"
#include "MarkovsChain.h"
#include "Curl.h"

FileDownloader::FileDownloader(std::vector<std::string> &urls) : _urls(urls), _done(false), _index(0) {}

FileDownloader::~FileDownloader() {}

std::string FileDownloader::download() {
  if (_index < _urls.size()) {
    return FileDownloader::download(_urls.at(_index++));
  } else {
    _done = true;
  }
  return FileDownloader::download("");
}

bool FileDownloader::isDone() {
  return _done;
}

std::string FileDownloader::download(const std::string &url) {
  Curl curl;
  return curl.download(url);
}


