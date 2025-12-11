cmake_minimum_required(VERSION 4.1)
project(Bonjour_Rendering)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(BJR_SOURCES
    # -------------------
    #      Headers
    # -------------------
    "include/bjr/rendering/opengl/ogl_graphics_ctx.hpp"
    "include/bjr/rendering/graphics_ctx.hpp"
    "include/bjr/bonjour.hpp"
    "include/bjr/window.hpp"

    # -------------------
    #    Source files
    # -------------------
    "src/rendering/opengl/ogl_graphics_ctx.cpp"
    "src/window.cpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_SOURCES})

add_library(Bonjour_Rendering STATIC ${BJR_SOURCES})

target_link_libraries(Bonjour_Rendering
    glm::glm
	glfw
    Glad
)

target_compile_definitions(Bonjour_Rendering 
    PRIVATE 
        BJR_BUILD
)

target_include_directories(Bonjour_Rendering 
    PUBLIC 
        "include"
    PRIVATE
        "include/bjr_rendering"
)
