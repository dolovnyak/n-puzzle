#pragma once

#include <tuple>
#include <iostream>
#include <vector>
#include <map>

class Puzzle {
public:
    Puzzle() = default;

    Puzzle(size_t size, std::vector<int> raw);

    bool operator==(const Puzzle &puzzle) const;

    [[nodiscard]] size_t GetSize() const;

    [[nodiscard]] size_t GetHash() const;

    [[nodiscard]] std::tuple<size_t, size_t> GetPosition(int value) const;

    [[nodiscard]] int At(size_t pos) const;

    [[nodiscard]] int At(size_t row, size_t column) const;

    [[nodiscard]] std::vector<int> GetCells() const;

    const static Puzzle &GetSnailPuzzle(size_t size);

    static int CountInversions(const Puzzle &puzzle);

private:
    size_t size_ = 0;
    std::vector<int> cells_;

    static std::map<size_t, Puzzle> target_puzzles_;

    static Puzzle CreateSnailPuzzle(size_t size);
};

std::ostream &operator<<(std::ostream &os, const Puzzle &field);
