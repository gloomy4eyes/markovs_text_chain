add_executable(text_generator TextGenerator.cpp)

target_link_libraries(text_generator
        PRIVATE
        MC::markovs_chain
        MC::command_line_parser
        )

set_target_properties(text_generator
        PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        RUNTIME_OUTPUT_DIRECTORY ${MC_BINARY_DIR}
        )