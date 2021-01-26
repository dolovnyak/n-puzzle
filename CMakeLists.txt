cmake_minimum_required(VERSION 3.17)
project(n_puzzle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(n_puzzle)
target_link_libraries(n_puzzle
        GTest::GTest
        GTest::Main)

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)
