cmake_minimum_required(VERSION 3.10)
project(sample1)

add_executable(sample1 sample1.cpp)

target_link_libraries(sample1 myCalculator -lgtest -lgmock pthread -Wl,--wrap=add,--wrap=powf,--wrap=sub,--wrap=malloc,--wrap=gethostname )
