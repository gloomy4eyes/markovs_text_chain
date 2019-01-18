cmake_minimum_required(VERSION 3.10)
project(markovs_text_chain_tests)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../)

link_directories(${LIBRARIES_DIR})

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TESTS_SOURCES
    main.cpp
    )

add_executable(${PROJECT_NAME} ${TESTS_SOURCES})
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} -ltokenizer -lpthread)