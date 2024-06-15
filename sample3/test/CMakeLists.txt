cmake_minimum_required(VERSION 3.10)
project(Sample3)

add_executable(test1 test1.cpp test2.cpp test3.cpp main.cpp mocks/mock_sample.cpp)

target_link_libraries(test1 -lgtest -lgmock pthread -Wl,--wrap=malloc,--wrap=gethostname )
