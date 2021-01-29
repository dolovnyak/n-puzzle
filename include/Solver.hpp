#pragma once

#include <cmath>
#include <vector>
#include <queue>
#include <unordered_set>

#include "Puzzle.hpp"
#include "Node.hpp"
#include "Move.hpp"

class Solver {
public:
    static bool IsSolvable(const Puzzle &puzzle);
    static void Solve(const Puzzle &puzzle, Heuristics::Type heuristicsType, OpenSetComparator::Type algorithmType);
};

using OpenNodes = std::priority_queue<Node *, std::vector<Node *>, std::function<bool(Node *, Node *)>>;
using ClosedNodes = std::unordered_set<Node *, HashNodeByPuzzle, EqualNodeByPuzzle>;
