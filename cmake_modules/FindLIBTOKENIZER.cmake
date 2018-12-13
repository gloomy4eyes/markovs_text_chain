set(LIBTOKENIZER_DIR ${CMAKE_CURRENT_LIST_DIR}/../tokenizer)

find_path(LIBTOKENIZER_INCLUDE_DIR
    NAMES Tokenizer.h
    PATHS ${LIBTOKENIZER_DIR})

#find_library(LIBTOKENIZER_LIB
#    NAMES libtokenizer.so -ltokenizer
#    PATHS ${CMAKE_CURRENT_LIST_DIR}/../lib
#          ${CMAKE_CURRENT_LIST_DIR}
#          ${LIBTOKENIZER_INCLUDE_DIR}
#          ${LIBTOKENIZER_DIR}
#        )
set(LIBTOKENIZER_LIB -ltokenizer)
set(LIBTOKENIZER_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/../lib)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(LIBTOKENIZER DEFAULT_MSG
    LIBTOKENIZER_LIB
    LIBTOKENIZER_INCLUDE_DIR
    )

mark_as_advanced(
    LIBTOKENIZER_LIB
    LIBTOKENIZER_INCLUDE_DIR
)

