cmake_minimum_required(VERSION 3.10)
project(MyMath)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)
add_subdirectory(test)
