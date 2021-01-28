#pragma once

#include <iostream>
#include <vector>

class Puzzle {
public:
    Puzzle(size_t size, std::vector<int> raw);

    Puzzle(const Puzzle &field);

    Puzzle &operator=(const Puzzle &puzzle);

    bool operator==(const Puzzle &puzzle) const;

    [[nodiscard]] size_t GetSize() const;

    [[nodiscard]] size_t GetHash() const;

    [[nodiscard]] std::pair<size_t, size_t> GetPosition(int value) const;

    [[nodiscard]] int At(size_t pos) const;
    [[nodiscard]] int At(size_t row, size_t column) const;

    [[nodiscard]] std::vector<int> GetCells() const;

public:
    friend std::ostream &operator<<(std::ostream &os, const Puzzle &field) {
        for (size_t row = 0; row < field.GetSize(); ++row) {
            for (size_t column = 0; column < field.GetSize(); ++column) {
                if (column != 0) {
                    os << " ";
                }
                os << const_cast<Puzzle &>(field).At(row, column);
            }
            os << std::endl;
        }
        return os;
    }

private:
    size_t size_;
    std::vector<int> cells_;
};
