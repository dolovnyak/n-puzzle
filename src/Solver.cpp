#include "Solver.hpp"

Solver::Solver(Heuristics::Type heuristics_type)
        : heuristics_type_(heuristics_type) {}

int Solver::GetZeroRow(const Puzzle &puzzle) {
    int size = puzzle.GetSize();

    for (int row = size - 1; row >= 0; --row) {
        for (int column = 0; column < size; ++column) {
            if (puzzle.At(row, column) == 0) {
                return size - row;
            }
        }
    }

    throw std::logic_error("Not found zero element");
}

int Solver::CountInversions(const Puzzle &puzzle) {
    int inversions = 0;

    size_t internalSize = puzzle.GetSize() * puzzle.GetSize();
    for (size_t i = 0; i < internalSize; ++i) {
        for (size_t j = i + 1; j < internalSize; ++j) {
            if (puzzle.At(i) != 0 && puzzle.At(j) != 0 && puzzle.At(i) > puzzle.At(j)) {
                ++inversions;
            }
        }
    }

    return inversions;
}

bool Solver::IsSolvable(const Puzzle &puzzle) {
    int inversions = CountInversions(puzzle);
    if (puzzle.GetSize() % 2 != 0) {
        return inversions % 2 == 0;
    } else {
        int zeroRow = GetZeroRow(puzzle);
        return (inversions + zeroRow) % 2 == 1;
    }
}
