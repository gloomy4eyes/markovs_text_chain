#include "CurlDownloader.h"

#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t s = size * nmemb;
  std::string retStr(s, '\0');

  std::copy((char *)contents, (char *)contents + s, retStr.begin());
  auto *str = static_cast<std::string *>(userp);
  std::swap(*str, retStr);

  return s;
}

CurlDownloader::CurlDownloader()
    : m_curl([]() {
        auto curl = std::shared_ptr<CURL>(curl_easy_init(), [](CURL *p_curl) { curl_easy_cleanup(p_curl); });
        if (!curl) {
          throw std::runtime_error("error on curl init");
        }

        return curl;
      }()) { /**/
}

std::string CurlDownloader::download(const std::string &url) {
  if (url.empty()) {
    return {};
  }

  std::string buffer;
  auto curl_handle = m_curl.get();
  curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &buffer);
  curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 10);

  CURLcode res = curl_easy_perform(curl_handle);
  if (res != CURLE_OK) {
    throw std::runtime_error("error on getting: " + url + ", error: " + curl_easy_strerror(res));
  }

  return buffer;
}
