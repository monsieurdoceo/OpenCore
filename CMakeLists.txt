cmake_minimum_required(VERSION 3.10)
project(OpenCore VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(SRC_DIR
    "src/main.cpp"
    "src/window.cpp"
    "src/inputsystem.cpp"
    "src/camera.cpp"
    "src/shader.cpp"
    "src/texture.cpp"
)

add_executable(OpenCore ${SRC_DIR})
add_library(glad include/glad/glad.h src/glad.c)

target_include_directories(OpenCore PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
target_include_directories(glad PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(OpenCore PRIVATE
    glad
    glfw
    OpenGL::GL
)
