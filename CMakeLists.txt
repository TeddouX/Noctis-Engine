cmake_minimum_required(VERSION 4.1)
project(Noctis)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(${CMAKE_SOURCE_DIR}/bonjour_rendering)
# add_subdirectory(${CMAKE_SOURCE_DIR}/noctis_engine)

add_subdirectory(${CMAKE_SOURCE_DIR}/testing)

add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/glad)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/glm)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/glfw)
