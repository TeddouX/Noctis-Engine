cmake_minimum_required(VERSION 4.1)
project(Bonjour_Rendering)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(BJR_SOURCES
    # -------------------
    #      Headers
    # -------------------
    "include/bjr/core/bonjour.hpp"
    "include/bjr/core/error.hpp"
    "include/bjr/core/window.hpp"
    "include/bjr/rendering/opengl/ogl_handler.hpp"
    "include/bjr/rendering/opengl/ogl_shader.hpp"
    "include/bjr/rendering/opengl/ogl_ssbo.hpp"
    "include/bjr/rendering/opengl/ogl_uniform_buffer.hpp"
    "include/bjr/rendering/opengl/ogl_vertex_array.hpp"
    "include/bjr/rendering/camera.hpp"
    "include/bjr/rendering/handler.hpp"
    "include/bjr/rendering/shader.hpp"
    "include/bjr/rendering/ssbo.hpp"
    "include/bjr/rendering/uniform_buffer.hpp"
    "include/bjr/rendering/vertex_array.hpp"

    # -------------------
    #    Source files
    # -------------------
    "src/core/bonjour.cpp"
    "src/core/window.cpp"
    "src/rendering/opengl/ogl_handler.cpp"
    "src/rendering/opengl/ogl_shader.cpp"
    "src/rendering/opengl/ogl_ssbo.cpp"
    "src/rendering/opengl/ogl_uniform_buffer.cpp"
    "src/rendering/opengl/ogl_vertex_array.cpp"
    "src/rendering/camera.cpp"
    "src/rendering/shader.cpp"
    "src/rendering/ssbo.cpp"
    "src/rendering/uniform_buffer.cpp"
    "src/rendering/vertex_array.cpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${BJR_SOURCES})

add_library(Bonjour_Rendering STATIC ${BJR_SOURCES})

target_link_libraries(Bonjour_Rendering
    glm::glm
	glfw
    Glad
)

target_compile_definitions(Bonjour_Rendering 
    PRIVATE 
        BJR_BUILD
    PUBLIC
        GLM_ENABLE_EXPERIMENTAL
)

target_include_directories(Bonjour_Rendering 
    PUBLIC 
        "include"
    PRIVATE
        "include/bjr"
)
