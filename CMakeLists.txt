cmake_minimum_required(VERSION 3.10)

project(markovs_text_chain)

option(ENABLE_TESTS "enables tests" )
option(${BUILD_SHARED_LIBS} "build shared libs" ON)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(MC_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(MC_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_subdirectory(tokenizer)
add_subdirectory(markovs_chain)

add_subdirectory(command_line_parser)
add_subdirectory(text_generator)
add_subdirectory(curl_downloader)
add_subdirectory(learner)

if (ENABLE_TESTS)
    add_subdirectory(tests)
    add_dependencies(markovs_text_chain_tests learner text_generator)
endif (ENABLE_TESTS)