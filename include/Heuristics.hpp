#pragma once

#include "Puzzle.hpp"

class Heuristics {
public:
    enum Type {
        Hamming,
        Manhattan,
        LinearConflicts
    };

    typedef int (*HeuristicsFunction)(const Puzzle &, const Puzzle &);

    static int GetManhattanDistance(const Puzzle &puzzle, const Puzzle &target_puzzle);

    static int GetHammingDistance(const Puzzle &puzzle, const Puzzle &target_puzzle);
    
    static int GetLinearConflicts(const Puzzle &puzzle, const Puzzle &target_puzzle);

private:
    Heuristics() = default;
};
