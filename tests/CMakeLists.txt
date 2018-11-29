cmake_minimum_required(VERSION 3.10)
project(markovs_text_chain_tests)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../)

set(TESTS_SOURCES
    main.cpp
    FileDownloaderTest.cpp
    )


add_test(NAME markovs_text_chain_tests
    COMMAND TextMiningApp -i "${CMAKE_SOURCE_DIR}/test.txt" "totoro.txt"
    )