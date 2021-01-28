#pragma once

#include "Puzzle.hpp"

class Heuristics {
public:
    enum Type {
        Hamming,
        Manhattan,
        LinearConflicts
    };

    static int GetManhattanDistance(
            const Puzzle &field,
            const Puzzle &target_field);

    static int GetHammingDistance(
            const Puzzle &field,
            const Puzzle &target_field);

private:
    Heuristics() = default;
};
