cmake_minimum_required(VERSION 3.10)

project(markovs_text_chain)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/include")

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(BINARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_subdirectory(tokenizer)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

add_subdirectory(markovs_chain)
add_dependencies(markovs_chain tokenizer)

add_subdirectory(learner)
add_dependencies(learner markovs_chain)

add_subdirectory(text_generator)
add_dependencies(text_generator markovs_chain)