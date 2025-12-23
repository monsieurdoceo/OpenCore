cmake_minimum_required(VERSION 3.10)
project(OpenCore VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)

set(SRC_DIR
    "src/main.cpp"
    "src/renderer/window.cpp"
    "src/scenes/editorscene.cpp"
    "src/systems/inputsystem.cpp"
    "src/renderer/camera.cpp"
    "src/renderer/shader.cpp"
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
