cmake_minimum_required(VERSION 3.10)

project(markovs_chain)

include_directories(${PROJECT_ROOT})

set(SOURCES
    MarkovsChain.h
    MarkovsChain.cpp
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})
#target_link_libraries(${PROJECT_NAME} )