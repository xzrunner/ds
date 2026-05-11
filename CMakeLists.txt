cmake_minimum_required(VERSION 3.16)

project(ds)

################################################################################
# Source groups
################################################################################

set(inc
    "ds_array.h"
    "ds_freelist.h"
    "ds_hash.h"
    "ds_imap.h"
    "ds_stack.h"
)
source_group("inc" FILES ${inc})

set(src
    "ds_array.c"
    "ds_hash.c"
    "ds_imap.c"
    "ds_stack.c"
)
source_group("src" FILES ${src})

set(ALL_FILES
    ${inc}
    ${src}
)

add_library(ds ${ALL_FILES})

target_include_directories(ds PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
