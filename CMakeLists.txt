cmake_minimum_required(VERSION 3.20)

project(derelict LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create the executable first
add_executable(app)

set_target_properties(app PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED YES
)

# Include local headers
target_include_directories(app PRIVATE
        vendor/glm
        vendor/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Option to use vendored SDL3
option(USE_VENDORED_SDL "Use vendored SDL3" ON)

if (USE_VENDORED_SDL)
    add_subdirectory(vendor/SDL)
    target_link_libraries(app PRIVATE SDL3::SDL3)
else()
    find_package(SDL3 REQUIRED CONFIG)
    target_link_libraries(app PRIVATE SDL3::SDL3)
endif()

# Add spdlog
set(SPDLOG_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_BENCH OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/spdlog)
target_link_libraries(app PRIVATE spdlog::spdlog)

target_sources(app PRIVATE
        main.cpp
        vendor/glad/src/glad.c
        src/logging/logger.cpp
        src/graphics/shader.cpp
        src/graphics/vertex_array.cpp
        src/graphics/renderer.cpp
        src/window/window.cpp
        src/application/application.cpp
)

add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()
