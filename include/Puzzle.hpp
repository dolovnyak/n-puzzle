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
    
	[[nodiscard]] bool IsResolved() const;

private:
    size_t size_;
    std::vector<int> cells_;
};

std::ostream &operator<<(std::ostream &os, const Puzzle &field);
