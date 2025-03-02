cmake_minimum_required(VERSION 3.11)

project(matrix)

set ( CMAKE_CXX_STANDARD 20 )
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)

enable_testing()
add_subdirectory(tests/unit_test)
add_subdirectory(tests/e2e_test)

add_executable(matrix ./main.cpp)
target_include_directories(matrix PRIVATE ${CMAKE_SOURCE_DIR}/includes)
