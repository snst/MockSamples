cmake_minimum_required(VERSION 3.10)
project(sample2)

add_executable(test1 test1.cpp)

target_link_libraries(test1 myCalculator -lgtest -lgmock pthread -Wl,--wrap=add,--wrap=powf )
