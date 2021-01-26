#ifndef SOLVER_HPP_
# define SOLVER_HPP_

# include <cmath>

# include "Puzzle.hpp"

template<typename TValue>
class Solver {
public:
    bool IsSolvable(const Puzzle<TValue> &field) {
        int inversions = CountInversions(field);
        if (field.GetSize() % 2 != 0) {
            return inversions % 2 == 0;
        } else {
            int zeroRow = GetZeroRow(field);
            return (inversions + zeroRow) % 2 == 1;
        }
    }

private:
    int CountInversions(const Puzzle<TValue> &field) {
        int inversions = 0;

        TValue defaultValue = TValue{};
        size_t internalSize = field.GetSize() * field.GetSize();
        for (size_t i = 0; i < internalSize; ++i) {
            for (size_t j = i + 1; j < internalSize; ++j) {
                TValue vi = const_cast<Puzzle<TValue> &>(field).At(i).value;
                TValue vj = const_cast<Puzzle<TValue> &>(field).At(j).value;
                if (vi != defaultValue && vj != defaultValue && vi > vj) {
                    ++inversions;
                }
            }
        }

        return inversions;
    }

    int GetZeroRow(const Puzzle<TValue> &field) {
        int size = field.GetSize();

        TValue defaultValue = TValue{};
        for (int row = size - 1; row >= 0; --row) {
            for (int column = 0; column < size; ++column) {
                if (const_cast<Puzzle<TValue> &>(field).At(row, column).value == defaultValue) {
                    return size - row;
                }
            }
        }

        throw std::logic_error("Not found zero element");
    }
};

#endif // SOLVER_HPP_
