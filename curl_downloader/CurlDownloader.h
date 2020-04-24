#pragma once

#include <memory>
#include <string>

using CURL = void;

class CurlDownloader {
public:
  CurlDownloader();

  std::string download(const std::string &url);

private:
  std::shared_ptr<CURL> m_curl;
};
