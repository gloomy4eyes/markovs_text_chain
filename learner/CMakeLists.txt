cmake_minimum_required(VERSION 3.10)

project(learner)

set(dir ${BINARIES_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${dir})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${dir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${dir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${dir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${dir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${dir})

include_directories(${PROJECT_ROOT})

set(SOURCES
    main.cpp
    FileDownloader.h
    FileDownloader.cpp
    Curl.h
    Curl.cpp
    Learner.cpp
    Learner.h
    )

link_directories(${LIBRARIES_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} -lcurl -ltokenizer -lmarkovs_chain)