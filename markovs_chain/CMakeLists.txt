add_library(markovs_chain MarkovsChain.cpp)

target_link_libraries(markovs_chain
        PUBLIC
        MC::tokenizer
        )

target_include_directories(markovs_chain
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

set_target_properties(markovs_chain
        PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        ARCHIVE_OUTPUT_DIRECTORY ${MC_LIBRARY_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${MC_BINARY_DIR}
        )

add_library(MC::markovs_chain ALIAS markovs_chain)


