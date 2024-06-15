cmake_minimum_required(VERSION 3.10)
project(sample1)

set(CMAKE_BUILD_TYPE Debug)

add_executable(test1 test1.cpp)
target_link_libraries(test1 -lgtest -lgmock pthread -Wl,--wrap=malloc )

add_executable(test2 test2.cpp)
target_link_libraries(test2 -lgtest -lgmock pthread -Wl,--wrap=malloc )

add_executable(test3 test3.cpp)
target_link_libraries(test3 -lgtest -lgmock pthread -Wl,--wrap=malloc,--wrap=gethostname)
