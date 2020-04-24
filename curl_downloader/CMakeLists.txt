add_library(curl_downloader CurlDownloader.cpp)

target_include_directories(curl_downloader
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

set_target_properties(curl_downloader
        PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        ARCHIVE_OUTPUT_DIRECTORY ${MC_LIBRARY_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${MC_BINARY_DIR}
        )

add_library(MC::curl_downloader ALIAS curl_downloader)