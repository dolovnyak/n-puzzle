#pragma once

#include "Puzzle.hpp"

class Move {
public:
    Move(int dx, int dy);

    [[nodiscard]] Puzzle *Execute(const Puzzle &puzzle) const;

private:
    int dx;
    int dy;
};