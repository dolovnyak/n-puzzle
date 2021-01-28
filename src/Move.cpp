#include "Move.hpp"

Puzzle *MoveLeft::Execute(const Puzzle &puzzle) const {
    std::vector<int> cells = puzzle.GetCells();
    const auto& [row, column] = puzzle.GetPosition(0);

    if (column == 0) {
        return nullptr;
    }

    std::swap(cells[row * puzzle.GetSize() + column], cells[row * puzzle.GetSize() + column - 1]);
    return new Puzzle(puzzle.GetSize(), cells);
}

Puzzle *MoveRight::Execute(const Puzzle &puzzle) const {
    std::vector<int> cells = puzzle.GetCells();
    const auto& [row, column] = puzzle.GetPosition(0);

    if (column == puzzle.GetSize() - 1) {
        return nullptr;
    }

    std::swap(cells[row * puzzle.GetSize() + column], cells[row * puzzle.GetSize() + column + 1]);
    return new Puzzle(puzzle.GetSize(), cells);
}

Puzzle *MoveDown::Execute(const Puzzle &puzzle) const {
    std::vector<int> cells = puzzle.GetCells();
    const auto& [row, column] = puzzle.GetPosition(0);

    if (row == 0) {
        return nullptr;
    }

    std::swap(cells[row * puzzle.GetSize() + column], cells[(row - 1) * puzzle.GetSize() + column]);
    return new Puzzle(puzzle.GetSize(), cells);
}

Puzzle *MoveUp::Execute(const Puzzle &puzzle) const {
    std::vector<int> cells = puzzle.GetCells();
    const auto& [row, column] = puzzle.GetPosition(0);

    if (row == puzzle.GetSize() - 1) {
        return nullptr;
    }

    std::swap(cells[row * puzzle.GetSize() + column], cells[(row + 1) * puzzle.GetSize() + column]);
    return new Puzzle(puzzle.GetSize(), cells);
}