cmake_minimum_required(VERSION 3.22)
project(GLCraft)

set(CMAKE_CXX_STANDARD 14)
include_directories(${PROJECT_SOURCE_DIR}/third_parties/GLFW/include)
include_directories(${PROJECT_SOURCE_DIR}/third_parties/)

link_directories(${PROJECT_SOURCE_DIR}/third_parties/GLFW/lib-mingw-w64)
link_directories(${PROJECT_SOURCE_DIR}/third_parties/)
link_directories(${PROJECT_SOURCE_DIR}/third_parties/glad/)
link_directories(${PROJECT_SOURCE_DIR}/third_parties/json/)

set(SRCS
        third_parties/glad/glad.c
        src/main.cpp
        src/Application.cpp
        src/Scene.cpp
        src/Window.cpp
        src/World.cpp
        src/BlockData.cpp
        src/Chunk.cpp
        src/stb_image.cpp
        src/Rendering/TextureLoader.cpp
        )
set(HEADERS
        third_parties/glad/glad.h
        third_parties/json/json.hpp
        src/Application.h
        src/Scene.h
        src/Window.h
        src/World.h
        src/BlockData.h
        src/Camera.h
        src/Chunk.h
        src/stb_image.h
        src/Rendering/TextureLoader.h
        src/Rendering/Shader_s.h
        )

add_executable(GLCraft ${SRCS} ${HEADERS})

target_link_libraries(GLCraft glfw3)




