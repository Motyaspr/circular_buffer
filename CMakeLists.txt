cmake_minimum_required(VERSION 3.10)
project(circular_buffer)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,return -Wall --std=c++17")
add_executable(circular_buffer_simple main.cpp circularbuffer.h)
add_executable(circular_buffer_hard testing.cpp
        circularbuffer.h
        gtest/gtest.h gtest/gtest-all.cc gtest/gtest_main.cc
        counted.cpp counted.h fault_injection.cpp fault_injection.h)
target_link_libraries(circular_buffer_hard -lpthread)
