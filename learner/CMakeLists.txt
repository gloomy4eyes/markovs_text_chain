cmake_minimum_required(VERSION 3.10)

project(learner)

include_directories(${PROJECT_ROOT})

set(SOURCES
    main.cpp
    FileDownloader.h
    FileDownloader.cpp
    Curl.h
    Curl.cpp
    Learner.cpp Learner.h)

set(LIBMARKOVS_CHAIN ../markovs_chain)

link_directories(
    ${PROJECT_ROOT}/lib
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} -lcurl -ltokenizer -lmarkovs_chain)