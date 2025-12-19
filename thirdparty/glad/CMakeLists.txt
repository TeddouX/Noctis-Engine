cmake_minimum_required(VERSION 3.10)
project(Glad)

add_library(Glad
    "include/glad/glad.h"
    "src/glad.c"
)

target_include_directories(Glad PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)
