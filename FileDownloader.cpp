#include "FileDownloader.h"

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fstream>
#include <cstring>
#include "Tokenizer.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

FileDownloader::FileDownloader(std::list<std::string> &urls) : /*_curl(curl_easy_init()),*/ _urls(urls) {

}

FileDownloader::~FileDownloader() {

}

void FileDownloader::download(const std::string &destinationPath) {

  auto result = mkdir(destinationPath.c_str(), S_IREAD | S_IWRITE);
  if (result != 0 && errno != EEXIST) {
    std::cout << strerror(errno) << std::endl;
  }
  for (auto & url : _urls) {
    std::string readBuffer;

    CURL *curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
      CURLcode res = curl_easy_perform(curl);
      if (res == CURLE_OK) {
        curl_easy_cleanup(curl);
//        std::cout << readBuffer << std::endl;

        auto tokens = Tokenizer::tokenize(readBuffer, ' ');
        for (auto &token : tokens) {
          std::cout << token << std::endl;
        }
//        std::string fdstp = std::string(destinationPath).append("/").append(generateUid()).append(".txt");
//        std::ofstream ofs(fdstp, std::ios::binary | std::ios::trunc);
//        if (!ofs.is_open()) {
//          std::cerr << "file " + fdstp + " open error: " + strerror(errno) << std::endl;
//        } else {
//          ofs << readBuffer;
//          ofs.close();
//        }
      } else {
        std::cout << "error on getting: " << url << ", error: " << res << std::endl;
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

