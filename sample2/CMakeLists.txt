cmake_minimum_required(VERSION 3.10)
project(sample2)

set(CMAKE_BUILD_TYPE Debug)

add_executable(sample2_1 sample2_1.cpp)
target_link_libraries(sample2_1 -lgtest -lgmock pthread -Wl,--wrap=malloc )

add_executable(sample2_2 sample2_2.cpp)
target_link_libraries(sample2_2 -lgtest -lgmock pthread -Wl,--wrap=malloc )

add_executable(sample2_3 sample2_3.cpp)
target_link_libraries(sample2_3 -lgtest -lgmock pthread -Wl,--wrap=malloc )
