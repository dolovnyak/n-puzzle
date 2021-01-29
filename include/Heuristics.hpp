#pragma once

#include "Puzzle.hpp"

class Heuristics {
public:
    enum Type {
        Hamming,
        Manhattan,
        LinearConflicts
    };

    static int GetManhattanDistance(const Puzzle &field);

    static int GetHammingDistance(const Puzzle &field);

private:
    Heuristics() = default;
};
