set(LIBMARKOVS_CHAIN_DIR ${CMAKE_CURRENT_LIST_DIR}/../markovs_chain)

find_path(LIBMARKOVS_CHAIN_INCLUDE_DIR
    NAMES MarkovsChain.h
    PATHS ${LIBMARKOVS_CHAIN_DIR})

#find_library(LIBMARKOVS_CHAIN_LIB
#    NAMES libmarkovs_chain.so libmarkovs_chain.a
#    PATHS ${CMAKE_CURRENT_LIST_DIR}/../lib)

set(LIBMARKOVS_CHAIN_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/../lib)
set(LIBMARKOVS_CHAIN_LIB -lmarkovs_chain)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(LIBMARKOVS_CHAIN DEFAULT_MSG
    LIBMARKOVS_CHAIN_LIB
    LIBMARKOVS_CHAIN_INCLUDE_DIR
    )

mark_as_advanced(
    LIBMARKOVS_CHAIN_LIB
    LIBMARKOVS_CHAIN_INCLUDE_DIR
)

