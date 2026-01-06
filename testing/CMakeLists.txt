cmake_minimum_required(VERSION 4.1)
project(testing)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(testing "main.cpp")

target_link_libraries(testing NoctisEngine)

add_custom_command(TARGET testing POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:NoctisEngine>
        # $<TARGET_PDB_FILE:NoctisEngine>
        $<TARGET_FILE_DIR:testing>
)
