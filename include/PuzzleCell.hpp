#pragma once

template<class T>
struct PuzzleCell {
    T value;

    explicit PuzzleCell();

    explicit PuzzleCell(T value);
};

template<class T>
PuzzleCell<T>::PuzzleCell() = default;

template<class T>
PuzzleCell<T>::PuzzleCell(T value) : value(value) {}

template<class T>
std::ostream &operator<<(std::ostream &os, const PuzzleCell<T> &c) {
    os << c.value;
    return os;
}
