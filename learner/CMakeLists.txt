list(APPEND LEARNER_SOURCES
        Learner.cpp
        )

add_executable(learner ${LEARNER_SOURCES})

find_package(Curl REQUIRED)

target_link_libraries(learner
        PRIVATE
        MC::markovs_chain
        MC::command_line_parser
        MC::curl_downloader
        CURL::libcurl
        )

set_target_properties(learner
        PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        RUNTIME_OUTPUT_DIRECTORY ${MC_BINARY_DIR}
        )