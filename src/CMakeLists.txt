cmake_minimum_required(VERSION 3.17)

target_sources(n_puzzle PUBLIC
        Heuristics.cpp
        Move.cpp
        Node.cpp
        Parser.cpp
        Puzzle.cpp
        Solver.cpp
        Output.cpp
        main.cpp)