# Example executable that uses the lib
add_executable(derelict_example main.cpp)

set_target_properties(derelict_example PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(derelict_example PRIVATE derelict)

target_include_directories(derelict_example PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_custom_command(TARGET derelict_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/examples/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
)