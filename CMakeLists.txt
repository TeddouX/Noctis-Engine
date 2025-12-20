cmake_minimum_required(VERSION 4.1)
project(NoctisEngine VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/glad)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/glm)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/glfw)

add_subdirectory(${CMAKE_SOURCE_DIR}/testing)

set(NOCTIS_ENGINE_SOURCES
    # -------------------
    #      Headers
    # -------------------
    "include/noctis_engine/core/assert.hpp"
    "include/noctis_engine/core/logging.hpp"
    "include/noctis_engine/input/key.hpp"
    "include/noctis_engine/input/input_system.hpp"
    "include/noctis_engine/math/color.hpp"
    "include/noctis_engine/rendering/opengl/ogl_handler.hpp"
    "include/noctis_engine/rendering/opengl/ogl_shader.hpp"
    "include/noctis_engine/rendering/opengl/ogl_ssbo.hpp"
    "include/noctis_engine/rendering/opengl/ogl_uniform_buffer.hpp"
    "include/noctis_engine/rendering/opengl/ogl_vertex_array.hpp"
    "include/noctis_engine/rendering/camera.hpp"
    "include/noctis_engine/rendering/handler.hpp"
    "include/noctis_engine/rendering/render_state.hpp"
    "include/noctis_engine/rendering/shader.hpp"
    "include/noctis_engine/rendering/ssbo.hpp"
    "include/noctis_engine/rendering/uniform_buffer.hpp"
    "include/noctis_engine/rendering/vertex_array.hpp"
    "include/noctis_engine/rendering/window.hpp"
    "include/noctis_engine/noctis_engine.hpp"

    # -------------------
    #    Source files
    # -------------------
    "src/input/input_system.cpp"
    "src/rendering/opengl/ogl_handler.cpp"
    "src/rendering/opengl/ogl_shader.cpp"
    "src/rendering/opengl/ogl_ssbo.cpp"
    "src/rendering/opengl/ogl_uniform_buffer.cpp"
    "src/rendering/opengl/ogl_vertex_array.cpp"
    "src/rendering/camera.cpp"
    "src/rendering/render_state.cpp"
    "src/rendering/shader.cpp"
    "src/rendering/ssbo.cpp"
    "src/rendering/uniform_buffer.cpp"
    "src/rendering/vertex_array.cpp"
    "src/rendering/window.cpp"
)

add_library(NoctisEngine SHARED ${NOCTIS_ENGINE_SOURCES})

target_link_libraries(NoctisEngine
    glm::glm
    glfw
    Glad
)

target_compile_definitions(NoctisEngine 
    PRIVATE 
        NCENG_BUILD
    PUBLIC
        GLM_ENABLE_EXPERIMENTAL
)

target_include_directories(NoctisEngine
    PUBLIC
        "include"
    PRIVATE
        "include/noctis_engine"
)
