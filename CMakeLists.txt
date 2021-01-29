cmake_minimum_required(VERSION 3.17)
project(n_puzzle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_STANDARD 20)

find_package(GTest PATHS ~/.brew)
find_package(Boost PATHS ~/.brew)

find_package(GTest REQUIRED)
find_package(Boost REQUIRED)

add_executable(n_puzzle)
target_link_libraries(n_puzzle
        GTest::GTest
        GTest::Main)
target_link_libraries(n_puzzle
        Boost::headers)

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )