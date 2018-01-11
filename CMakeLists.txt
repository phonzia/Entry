cmake_minimum_required(VERSION 3.8)
set(PROJECT_NAME entry)
project(${PROJECT_NAME})

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 17)

set(TEST_TARGET entry_test)

add_executable(${TEST_TARGET}
        src/Entry.cpp
        src/Entry.h
        src/stringtool.cpp
        src/stringtool.h
        test/catch.hpp
        test/test.cpp)

set(COVERAGE_EXCLUDES '${CMAKE_CURRENT_SOURCE_DIR}/test/*' '/usr/include/*' 'v1/*')
include(CodeCoverage)
APPEND_COVERAGE_COMPILER_FLAGS()
setup_target_for_coverage(NAME ${PROJECT_NAME}_coverage
        EXECUTABLE ${TEST_TARGET} coverage)

