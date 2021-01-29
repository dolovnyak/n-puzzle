#include "Puzzle.hpp"

#include <utility>

Puzzle::Puzzle(size_t size, std::vector<int> raw)
        : size_(size),
          cells_(std::move(raw)) {}

Puzzle::Puzzle(const Puzzle &puzzle)
        : size_(puzzle.size_),
          cells_(puzzle.cells_) {}

int Puzzle::At(size_t pos) const {
    return cells_[pos];
}

int Puzzle::At(size_t row, size_t column) const {
    return cells_[row * size_ + column];
}

Puzzle &Puzzle::operator=(const Puzzle &puzzle) {
    if (this == &puzzle)
        return *this;

    size_ = puzzle.size_;
    cells_ = puzzle.cells_;

    return *this;
}

bool Puzzle::operator==(const Puzzle &puzzle) const {
    for (size_t i = 0; i < cells_.size(); i++) {
        if (cells_[i] != puzzle.cells_[i])
            return false;
    }

    return true;
}

size_t Puzzle::GetSize() const {
    return size_;
}

size_t Puzzle::GetHash() const {
    size_t hash = 0;

    for (size_t i = 0; i < cells_.size(); i++)
        hash += (i + 1) * cells_[i];

    return hash;
}

std::vector<int> Puzzle::GetCells() const {
    return cells_;
}

std::tuple<size_t, size_t> Puzzle::GetPosition(int value) const {
    for (size_t row = 0; row < size_; ++row) {
        for (size_t column = 0; column < size_; ++column) {
            if (cells_[row * size_ + column] == value) {
                return std::tie(row, column);
            }
        }
    }
    throw std::exception(); //TODO handle or remake
}

Puzzle Puzzle::CreateSnailPuzzle(size_t size) {
    std::vector<int> cells(size * size);
    size_t lb = 0, rb = size - 1, tb = 1, bb = size - 1;
    size_t x = -1, y = 0;
    int dx = 1, dy = 0;
    for (size_t i = 1; i < size * size; ++i) {
        x += dx;
        y += dy;
        cells[y * size + x] = i;
        if (dx == 1 && x == rb) {
            dx = 0;
            dy = 1;
            --rb;
        } else if (dx == -1 && x == lb) {
            dx = 0;
            dy = -1;
            ++lb;
        } else if (dy == 1 && y == bb) {
            dy = 0;
            dx = -1;
            --bb;
        } else if (dy == -1 && y == tb) {
            dy = 0;
            dx = 1;
            ++tb;
        }
    }
    return Puzzle(size, cells);
}

std::map<size_t, Puzzle> Puzzle::target_puzzles_;

const Puzzle &Puzzle::GetSnailPuzzle(size_t size) {
    if (!target_puzzles_.contains(size)) {
        target_puzzles_.insert(std::pair<size_t, Puzzle>(size, CreateSnailPuzzle(size)));
    }
    return target_puzzles_.at(size);
}

std::ostream &operator<<(std::ostream &os, const Puzzle &field) {
    for (size_t row = 0; row < field.GetSize(); ++row) {
        for (size_t column = 0; column < field.GetSize(); ++column) {
            if (column != 0) {
                os << " ";
            }
            os << field.At(row, column);
        }
        os << std::endl;
    }
    return os;
}
