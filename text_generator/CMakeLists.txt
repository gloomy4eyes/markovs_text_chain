cmake_minimum_required(VERSION 3.10)

project(text_generator)

include_directories(${PROJECT_ROOT})

set(SOURCES
    main.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})