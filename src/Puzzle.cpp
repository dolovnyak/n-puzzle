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

std::pair<size_t, size_t> Puzzle::GetPosition(int value) const {
    for (size_t i = 0; i < size_; i++) {
        for (size_t j = 0; j < size_; j++) {
            if (cells_[i * size_ + j] == value) {
                return std::make_pair(i, j);
            }
        }
    }
    throw std::exception(); //TODO handle or remake
}

bool Puzzle::IsResolved() const
{
	for (size_t i = 0; i < size_ * size_; i++) {
		if (cells_[i] != i + 1 && cells_[i] != 0) {
			return false;
		}
	}
	
	return true;
}

std::ostream &operator<<(std::ostream &os, const Puzzle &field) {
	for (size_t row = 0; row < field.GetSize(); ++row) {
		for (size_t column = 0; column < field.GetSize(); ++column) {
			if (column != 0) {
				os << " ";
			}
			os << const_cast<Puzzle&>(field).At(row, column);
		}
		os << std::endl;
	}
	return os;
}
