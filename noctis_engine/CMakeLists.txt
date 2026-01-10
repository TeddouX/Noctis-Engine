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
    "include/noctis_engine/ecs/component/transform.hpp"
    "include/noctis_engine/ecs/ecs.hpp"
    "include/noctis_engine/ecs/entity.hpp"
    "include/noctis_engine/ecs/component/transform.hpp"
    "include/noctis_engine/ecs/system/system_storage.hpp"
    "include/noctis_engine/ecs/system/system.hpp"
    "include/noctis_engine/input/key.hpp"
    "include/noctis_engine/input/input_system.hpp"
    "include/noctis_engine/math/color.hpp"
    "include/noctis_engine/rendering/mesh/mesh_info.hpp"
    "include/noctis_engine/rendering/mesh/mesh_manager.hpp"
    "include/noctis_engine/rendering/mesh/mesh_view.hpp"
    "include/noctis_engine/rendering/camera.hpp"
    "include/noctis_engine/rendering/command_buffer.hpp"
    "include/noctis_engine/rendering/gpu_buffer.hpp"
    "include/noctis_engine/rendering/graphics_handler.hpp"
    "include/noctis_engine/rendering/shader.hpp"
    "include/noctis_engine/rendering/texture.hpp"
    "include/noctis_engine/rendering/vertex.hpp"
    "include/noctis_engine/rendering/window.hpp"
    "include/noctis_engine/noctis_engine.hpp"

    # -------------------
    #    Source files
    # -------------------
    "src/asset/loading.cpp"
    "src/asset/asset_manager.cpp"
    "src/input/input_system.cpp"
    "src/core/scene.cpp"
    "src/debug/debug_ui.cpp"
    "src/ecs/component/transform.cpp"
    "src/rendering/material/material_manager.cpp"
    "src/rendering/mesh/mesh_manager.cpp"
    "src/rendering/bindless_texture.cpp"
    "src/rendering/camera.cpp"
    "src/rendering/command_buffer.cpp"
    "src/rendering/gpu_buffer.cpp"
    "src/rendering/graphics_handler.cpp"
    "src/rendering/renderer.cpp"
    "src/rendering/shader.cpp"
    "src/rendering/texture.cpp"
    "src/rendering/window.cpp"
)

add_library(NoctisEngine SHARED ${NOCTIS_ENGINE_SOURCES})

target_link_libraries(NoctisEngine
    EnTT::EnTT
    glm::glm
    ImGui
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