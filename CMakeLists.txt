cmake_minimum_required(VERSION 3.23)
project(GLCraft)

set(CMAKE_CXX_STANDARD 14)
include_directories(${PROJECT_SOURCE_DIR}/GLFW/include)

link_directories(${PROJECT_SOURCE_DIR}/GLFW/lib-mingw-w64)
link_directories(Includes)

add_executable(GLCraft main.cpp glad.c)

target_link_libraries(GLCraft glfw3)




