#ifndef PUZZLE_HPP_
# define PUZZLE_HPP_

# include <vector>
# include "PuzzleCell.hpp"

template<typename TValue>
class Puzzle {
public:
    explicit Puzzle(size_t size) : size_(size), cells_(size * size) {}

    friend std::ostream &operator<<(std::ostream &os, const Puzzle<TValue> &field) {
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
    [[nodiscard]] PuzzleCell<TValue> &At(int pos);
    [[nodiscard]] PuzzleCell<TValue> &At(int row, int column);

private:
    size_t size_;
    std::vector<PuzzleCell<TValue>> cells_;
};

template<typename TValue>
size_t Puzzle<TValue>::GetSize() const {
    return size_;
}

template<typename TValue>
PuzzleCell<TValue> &Puzzle<TValue>::At(int pos) {
    return cells_[pos];
}

template<typename TValue>
PuzzleCell<TValue> &Puzzle<TValue>::At(int row, int column) {
    return cells_[row * size_ + column];
}

#endif // PUZZLE_HPP_