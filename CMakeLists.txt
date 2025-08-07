cmake_minimum_required(VERSION 3.10)
project(OpenCore VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE LEGACY)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(OpenCore src/main.cpp)
add_library(glad include/glad/glad.h src/glad.c)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

target_link_libraries(OpenCore glad)
target_link_libraries(OpenCore glfw)
target_link_libraries(OpenCore OpenGL::GL)

