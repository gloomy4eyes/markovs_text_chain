add_library(tokenizer Tokenizer.cpp)

target_include_directories(tokenizer
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

set_target_properties(tokenizer
        PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        ARCHIVE_OUTPUT_DIRECTORY ${MC_LIBRARY_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${MC_BINARY_DIR}
        )

add_library(MC::tokenizer ALIAS tokenizer)