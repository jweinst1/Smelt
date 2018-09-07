cmake_minimum_required(VERSION 3.5)

project(Smelt)

######Smelt core source files#######
SET(core_files
    src/Smelt.c
)

####### Smelt Libraries ########

add_library(SmeltShared SHARED 
    "${core_files}"
)

###################################

target_include_directories(SmeltShared
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

# Tests for header file executable #
add_executable(SmeltHeaderTests
    tests/test_header_file.c
)

# Tests for shared lib executable #
add_executable(SmeltLibTests
    tests/test_shared_lib.c
)

target_include_directories(SmeltLibTests
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(SmeltHeaderTests
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

# links library to test executable
target_link_libraries( SmeltLibTests
    PRIVATE 
        SmeltShared
)
