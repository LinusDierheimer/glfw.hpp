cmake_minimum_required(VERSION 3.0)

project(glfw_hpp_test)

add_executable(test
    test.cpp
)

target_include_directories(test PRIVATE
    "../Vulkan-Headers/include/"
    "../Vulkan-Hpp/"
    "../glfw/include/"
    "../include/"
)

find_library(LIBVULKAN
    NAMES "libvulkan" "vulkan"
)

find_library(LIBGLFW
    NAMES "libglfw" "glfw"
)

find_library(LIBGL
    NAMES "libGL" "libOpenGL" "GL" "OpenGL"
)

target_link_libraries(test PRIVATE
    "${LIBVULKAN}"
    "${LIBGLFW}"
    "${LIBGL}"
)
