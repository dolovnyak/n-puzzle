#pragma once

template<typename TValue>
struct PuzzleCell {
    TValue value;

    explicit PuzzleCell();
    explicit PuzzleCell(TValue value);
};

template<typename TValue>
PuzzleCell<TValue>::PuzzleCell() = default;

template<typename TValue>
PuzzleCell<TValue>::PuzzleCell(TValue value) : value(value) {}

template<typename TValue>
std::ostream &operator<<(std::ostream &os, const PuzzleCell<TValue> &c) {
    os << c.value;
    return os;
}
