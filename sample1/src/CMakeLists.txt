cmake_minimum_required(VERSION 3.12)
project(myCalculator)

add_library(myCalculator STATIC my_math.c my_calculator.c)

target_include_directories(myCalculator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
