cmake_minimum_required(VERSION 3.17)
project(n_puzzle)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(n_puzzle_tests
        ParserTests.cpp
        SolverTests.cpp
        PriorityQueueTests.cpp
        HeuristicsTests.cpp
        ../src/Output.cpp)

include_directories(../include)

target_link_libraries(n_puzzle_tests
        GTest::GTest
        GTest::Main)
