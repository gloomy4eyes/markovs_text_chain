#include "Curl.h"
#include <curl/curl.h>
#include <cassert>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t s = size * nmemb;
  std::string retStr(s, '\0');
  std::copy((char *)contents, (char *)contents + s, retStr.begin());
  auto *str = (std::string*)userp;
  std::swap(*str, retStr);
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

std::string Curl::download(const std::string &url) {
  if (url.empty()) {
    return {};
  }
  std::string buffer;
  curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &buffer);
  CURLcode res = curl_easy_perform(_curl);
  if (res == CURLE_OK) {
    return buffer;
  } else {
    throw std::runtime_error("error on getting: " + url + ", error: " + curl_easy_strerror(res));
  }
}
