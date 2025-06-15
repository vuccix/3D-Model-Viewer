cmake_minimum_required(VERSION 3.20)
project(Playing_with_OpenGL LANGUAGES C CXX)

set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 20)

# ---------- GLFW ---------- #
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw-3.4)

# ---------- GLAD ---------- #
add_library(glad STATIC external/glad/src/gl.c)
target_include_directories(glad PUBLIC external/glad/include)

# ---------- exe ------ #
add_executable(Playing_with_OpenGL src/main.cpp)

find_package(OpenGL REQUIRED)
target_link_libraries(Playing_with_OpenGL PRIVATE
        glad
        glfw
        OpenGL::GL)

target_include_directories(Playing_with_OpenGL PRIVATE
        external/glad/include)
