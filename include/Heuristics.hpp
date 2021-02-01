#pragma once

#include "Puzzle.hpp"

class Heuristics {
public:
    enum Type {
        Hamming,
        Manhattan,
        LinearConflicts
    };

    using HeuristicsFunction = std::function<int(const Puzzle &, const Puzzle &)>;

    static int GetManhattanDistance(const Puzzle &puzzle, const Puzzle &target_puzzle);

    static int GetHammingDistance(const Puzzle &puzzle, const Puzzle &target_puzzle);

    static int GetLinearConflicts(const Puzzle &puzzle, const Puzzle &target_puzzle);

private:
    Heuristics() = default;
};

struct LinearConflict {
public:
    LinearConflict(int x, int y);

    bool operator==(const LinearConflict &linear_conflict) const;

private:
    int x_;
    int y_;
};
