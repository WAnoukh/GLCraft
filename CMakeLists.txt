cmake_minimum_required(VERSION 3.23)
project(GLCraft)

set(CMAKE_CXX_STANDARD 14)
include_directories(${PROJECT_SOURCE_DIR}/third_parties/GLFW/include)

link_directories(${PROJECT_SOURCE_DIR}/third_parties/GLFW/lib-mingw-w64)
link_directories(${PROJECT_SOURCE_DIR}/third_parties/)

set(SRCS
        third_parties/glad/glad.c
        src/main.cpp
        src/Application.cpp
        src/Scene.cpp
        src/Window.cpp
        src/World.cpp
        )
set(HEADERS
        third_parties/glad/glad.h
        src/Application.h
        src/Scene.h
        src/Window.h
        src/World.h
        )

add_executable(GLCraft ${SRCS} ${HEADERS})

target_link_libraries(GLCraft glfw3)




