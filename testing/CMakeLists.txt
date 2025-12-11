cmake_minimum_required(VERSION 4.1)
project(testing)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(testing "main.cpp")

target_link_libraries(testing Bonjour_Rendering)
