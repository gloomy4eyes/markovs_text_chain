cmake_minimum_required(VERSION 3.10)
project(markovs_text_chain)

set(CMAKE_CXX_STANDARD 17)

option(ENABLE_TESTS OFF)


include_directories("/usr/include")

if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()

set(SOURCES
    main.cpp FileDownloader.h FileDownloader.cpp
    Tokenizer.cpp Tokenizer.h MarkovsChain.cpp MarkovsChain.h Misc.h)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} -lcurl)