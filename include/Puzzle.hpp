#pragma once

#include <iostream>
#include <vector>
#include "PuzzleCell.hpp"

template<class T>
class Puzzle {
public:
    explicit Puzzle(size_t size) : size_(size), cells_(size * size) {}

    Puzzle() : size_(0) {}

    Puzzle(const Puzzle<T> &field);

    Puzzle<T> &operator=(const Puzzle<T> &field);

    bool operator==(const Puzzle<T> &field) const;

    friend std::ostream &operator<<(std::ostream &os, const Puzzle<T> &field) {
        for (size_t row = 0; row < field.GetSize(); ++row) {
            for (size_t column = 0; column < field.GetSize(); ++column) {
                if (column != 0) {
                    os << " ";
                }
                os << const_cast<Puzzle &>(field).At(row, column).value;
            }
            os << std::endl;
        }
        return os;
    }

    [[nodiscard]] size_t GetSize() const;

    [[nodiscard]] size_t GetHash() const;

    [[nodiscard]] size_t GetIndexByValue(T value) const;

    [[nodiscard]] T GetCellValue(int pos) const;

    [[nodiscard]] PuzzleCell<T> &At(int pos);

    [[nodiscard]] PuzzleCell<T> &At(int row, int column);

private:
    size_t size_;
    std::vector<PuzzleCell<T>> cells_;
};

template<class T>
size_t Puzzle<T>::GetSize() const {
    return size_;
}

template<class T>
PuzzleCell<T> &Puzzle<T>::At(int pos) {
    return cells_[pos];
}

template<class T>
T Puzzle<T>::GetCellValue(int pos) const {
    return cells_[pos].value;
}

template<class T>
PuzzleCell<T> &Puzzle<T>::At(int row, int column) {
    return cells_[row * size_ + column];
}

template<class T>
Puzzle<T>::Puzzle(const Puzzle<T> &field) {
    size_ = field.size_;
    cells_ = field.cells_;
}

template<class T>
Puzzle<T> &Puzzle<T>::operator=(const Puzzle<T> &field) {
    if (this == &field)
        return *this;

    size_ = field.size_;
    cells_ = field.cells_;

    return *this;
}

template<class T>
bool Puzzle<T>::operator==(const Puzzle<T> &field) const {
    for (size_t i = 0; i < cells_.size(); i++) {
        if (cells_[i].value != field.cells_[i].value)
            return false;
    }

    return true;
}

template<class T>
size_t Puzzle<T>::GetHash() const {
    size_t hash = 0;

    for (size_t i = 0; i < cells_.size(); i++)
        hash += (i + 1) * cells_[i].value;

    return hash;
}

template<class T>
size_t Puzzle<T>::GetIndexByValue(T value) const {
    for (size_t i = 0; i < cells_.size(); i++) {
        if (cells_[i].value == value)
            return i;
    }
    throw std::exception(); //TODO handle or remake
}