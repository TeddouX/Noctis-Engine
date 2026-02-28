cmake_minimum_required(VERSION 4.1)
project(Noctis VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/entt)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/stb)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/noctis_engine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/testing)
