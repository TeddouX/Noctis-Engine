cmake_minimum_required(VERSION 4.1)
project(Noctis_Engine)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(NOCTIS_SOURCE
    # -------------------
    #      Headers
    # -------------------

    # -------------------
    #    Source files
    # -------------------
)

add_library(Noctis_Engine STATIC ${NOCTIS_SOURCE})

target_compile_definitions(Noctis_Engine 
    PRIVATE 
        NOCTIS_BUILD
)

target_include_directories(Noctis_Engine 
    PUBLIC 
        "include"
    PRIVATE
        "include/noctis_engine"
)