add_library(command_line_parser CommandLineParser.cpp)

target_include_directories(command_line_parser
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

set_target_properties(command_line_parser
        PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        ARCHIVE_OUTPUT_DIRECTORY ${MC_LIBRARY_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${MC_BINARY_DIR}
        )

add_library(MC::command_line_parser ALIAS command_line_parser)