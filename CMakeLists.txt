cmake_minimum_required(VERSION 3.10)

project(markovs_text_chain)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/include")

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(BINARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_subdirectory(markovs_chain)
add_subdirectory(tokenizer)
add_subdirectory(learner)
add_subdirectory(text_generator)

add_dependencies(markovs_chain tokenizer)
add_dependencies(learner markovs_chain)
add_dependencies(text_generator markovs_chain)

option(ENABLE_TESTS OFF)
if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()

#set(SOURCES
#    main.cpp FileDownloader.h FileDownloader.cpp
#    Tokenizer.cpp Tokenizer.h markovs_chain/MarkovsChain.cpp markovs_chain/MarkovsChain.h Misc.h learner/Curl.cpp learner/Curl.h)

#add_executable(${PROJECT_NAME} ${SOURCES})
#target_link_libraries(${PROJECT_NAME})