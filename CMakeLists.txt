cmake_minimum_required(VERSION 3.8)
project(Entry)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall -fprofile-arcs -ftest-coverage")


add_executable(entry_test
        src/Entry.cpp
        src/Entry.h
        src/stringtool.cpp
        src/stringtool.h
        test/catch.hpp
        test/test.cpp)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(entry_test gcov)
endif()
