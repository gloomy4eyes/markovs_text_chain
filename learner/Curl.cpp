#include "Curl.h"
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t s = size * nmemb;
//  ((std::stringstream*)userp)->clear();
  ((std::stringstream*)userp)->write((char *)contents, s);
  return s;
}

Curl::Curl()
    : _curl([]() {
        CURL *curl = curl_easy_init();
        if (!curl) {
          throw std::runtime_error("error on curl init");
        }
        return curl;
      }()) {}

Curl::~Curl() {
  curl_easy_cleanup(_curl);
}

std::istream &Curl::download(const std::string &url) {
  if (url.empty()) {
    _ss.clear();
    return _ss;
  }
  curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_ss);
  CURLcode res = curl_easy_perform(_curl);
  if (res == CURLE_OK) {
    return _ss;
  } else {
    throw std::runtime_error("error on getting: " + url + ", error: " + std::to_string(res));
  }
}
