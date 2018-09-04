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

target_include_directories(SmeltStatic
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

# Add test executables to build
add_executable(SmeltTests
    tests/test_main.c
)

target_include_directories(SmeltTests
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

# links library to test executable
target_link_libraries( SmeltTests
    PRIVATE 
        SmeltShared
)
