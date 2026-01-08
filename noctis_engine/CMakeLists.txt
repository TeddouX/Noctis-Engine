cmake_minimum_required(VERSION 4.1)
project(NoctisEngine VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(NOCTIS_ENGINE_SOURCES
    # -------------------
    #      Headers
    # -------------------
    "include/noctis_engine/asset/asset_manager.hpp"
    "include/noctis_engine/asset/loading.hpp"
    "include/noctis_engine/core/application.hpp"
    "include/noctis_engine/core/assert.hpp"
    "include/noctis_engine/core/entrypoint.hpp"
    "include/noctis_engine/core/logging.hpp"
    "include/noctis_engine/input/key.hpp"
    "include/noctis_engine/input/input_system.hpp"
    "include/noctis_engine/math/color.hpp"
    "include/noctis_engine/rendering/camera.hpp"
    "include/noctis_engine/rendering/gpu_buffer.hpp"
    "include/noctis_engine/rendering/graphics_handler.hpp"
    "include/noctis_engine/rendering/shader.hpp"
    "include/noctis_engine/rendering/texture.hpp"
    "include/noctis_engine/rendering/vertex_array.hpp"
    "include/noctis_engine/rendering/vertex.hpp"
    "include/noctis_engine/rendering/window.hpp"
    "include/noctis_engine/noctis_engine.hpp"

    # -------------------
    #    Source files
    # -------------------
    "src/asset/loading.cpp"
    "src/asset/asset_manager.cpp"
    "src/input/input_system.cpp"
    "src/rendering/camera.cpp"
    "src/rendering/gpu_buffer.cpp"
    "src/rendering/graphics_handler.cpp"
    "src/rendering/shader.cpp"
    "src/rendering/texture.cpp"
    "src/rendering/vertex_array.cpp"
    "src/rendering/window.cpp"
)

add_library(NoctisEngine SHARED ${NOCTIS_ENGINE_SOURCES})

target_link_libraries(NoctisEngine
    glm::glm
    glfw
    Glad
    stb
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