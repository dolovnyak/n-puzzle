cmake_minimum_required(VERSION 3.5)
project(n_puzzle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_STANDARD 17)

################################################################################
# expert_system_lib target
################################################################################
set(N_PUZZLE_LIB "${PROJECT_NAME}_lib")
add_library(${N_PUZZLE_LIB}
        src/n_puzzle_lib/Heuristics.cpp
        src/n_puzzle_lib/Move.cpp
        src/n_puzzle_lib/Node.cpp
        src/n_puzzle_lib/Parser.cpp
        src/n_puzzle_lib/Puzzle.cpp
        src/n_puzzle_lib/Solver.cpp
        )
target_include_directories(${N_PUZZLE_LIB} PUBLIC include)


################################################################################
# project target
################################################################################
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Output.cpp
        )
target_link_libraries(${PROJECT_NAME} ${N_PUZZLE_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC include)

# replaced executable file to root dir
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )


################################################################################
# tests
################################################################################
set(N_PUZZLE_TESTS ${PROJECT_NAME}_tests)
add_subdirectory(libs/googletest)

add_executable(${N_PUZZLE_TESTS}
        tests/HeuristicsTests.cpp
        tests/MoveTests.cpp
        tests/ParserTests.cpp
        tests/PriorityQueueTests.cpp
        tests/SolverTests.cpp
        )
target_include_directories(${N_PUZZLE_TESTS} PUBLIC
        libs/googletest/googletest/include
        include)
target_link_libraries(${N_PUZZLE_TESTS}
        gtest
        gtest_main
        ${N_PUZZLE_LIB}
        )

# replaced executable file to root dir
set_target_properties(${N_PUZZLE_TESTS}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )
