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

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t s = size * nmemb;
  ((std::stringstream*)userp)->write((char *)contents, s);
  return s;
}

FileDownloader::FileDownloader(std::list<std::string> &urls, MarkovsChain & mc) : /*_curl(curl_easy_init()),*/ _urls(urls), _mc(mc) {

}

FileDownloader::~FileDownloader() {

}

void FileDownloader::download(const std::string &destinationPath) {
  for (auto & url : _urls) {
    CURL *curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      std::string readBuffer;
      std::stringstream ss;
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ss);
      CURLcode res = curl_easy_perform(curl);
      if (res == CURLE_OK) {
        curl_easy_cleanup(curl);
        std::string line;
        while (std::getline(ss, line)) {
          if (!line.empty()) {
            auto tokens = Tokenizer::tokenize(line);
            _mc.process(tokens);
          }
        }
      } else {
        std::cerr << "error on getting: " << url << ", error: " << res << std::endl;
      }
    }
  }
}

std::string FileDownloader::generateUid() {
  srand(time(NULL));
  std::string strUuid(36, '\0');
  sprintf(&strUuid[0], "%x%x-%x-%x-%x-%x%x%x",
          rand(), rand(),                 // Generates a 64-bit Hex number
          rand(),                         // Generates a 32-bit Hex number
          ((rand() & 0x0fff) | 0x4000),   // Generates a 32-bit Hex number of the form 4xxx (4 indicates the UUID version)
          rand() % 0x3fff + 0x8000,       // Generates a 32-bit Hex number in the range [0x8000, 0xbfff]
          rand(), rand(), rand());        // Generates a 96-bit Hex number
  return strUuid;
}


