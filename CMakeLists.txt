cmake_minimum_required(VERSION 4.2)
project(VoyagerEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(VoyagerEngine main.cpp)

target_include_directories(VoyagerEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/src/runtime/core/public
)

add_subdirectory(lib/googletest)
add_subdirectory(tests)
