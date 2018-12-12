cmake_minimum_required(VERSION 3.10)

project(markovs_text_chain)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/include")

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(BINARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

add_subdirectory(tokenizer)
add_subdirectory(markovs_chain)
add_dependencies(markovs_chain tokenizer)

add_subdirectory(learner)
add_dependencies(learner tokenizer markovs_chain)

add_subdirectory(text_generator)
add_dependencies(text_generator markovs_chain)

option(ENABLE_TESTS OFF)
if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()