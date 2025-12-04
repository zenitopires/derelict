cmake_minimum_required(VERSION 3.20)

project(derelict LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(glad STATIC vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC vendor/glad/include)

add_library(derelict SHARED
        src/derelict/logging/logger.cpp
        src/derelict/graphics/shader.cpp
        src/derelict/graphics/vertex_array.cpp
        src/derelict/graphics/renderer.cpp
        src/derelict/window/window.cpp
        src/derelict/application/application.cpp
)

set_target_properties(derelict PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED YES
        LINKER_LANGUAGE CXX
)

target_include_directories(derelict PUBLIC include)

target_include_directories(derelict PRIVATE
        vendor/SDL/include
)

target_include_directories(derelict PUBLIC
        vendor/glad/include
        vendor/glm
)

add_subdirectory(vendor/SDL)
target_link_libraries(derelict PUBLIC SDL3::SDL3)

set(SPDLOG_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_BENCH OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/spdlog)
target_link_libraries(derelict PUBLIC spdlog::spdlog)


target_link_libraries(derelict PRIVATE glad)


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(derelict PRIVATE DEBUG)
endif()

# Examples
add_subdirectory(examples)