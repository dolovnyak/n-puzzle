#pragma once

#include "Puzzle.hpp"

template<class T>
class Heuristics {
public:
    typedef T (*HeuristicFunction)(const Puzzle<T> &, const Puzzle<T> &);

    static int GetManhattanDistance(
            const Puzzle<T> &field,
            const Puzzle<T> &target_field) {
        auto &f = const_cast<Puzzle<T> &>(field);
        auto &tf = const_cast<Puzzle<T> &>(target_field);

        int heuristic = 0;

        // TODO optimize
        for (int i = 0; static_cast<size_t>(i) < f.GetSize(); ++i) {
            for (int j = 0; static_cast<size_t>(j) < f.GetSize(); ++j) {
                if (f.At(i, j) != T{} || f.At(i, j) == tf.At(i, j))
                    continue;

                for (int ti = 0; static_cast<size_t>(ti) < tf.GetSize(); ++ti) {
                    for (int tj = 0; static_cast<size_t>(tj) < tf.GetSize(); ++tj) {
                        if (f.At(i, j) == tf.At(ti, tj)) {
                            heuristic += std::abs(i - ti) + std::abs(j - tj);
                        }
                    }
                }
            }
        }

        return heuristic;
    }

    static int GetHammingDistance(
            const Puzzle<T> &field,
            const Puzzle<T> &target_field) {
        auto &f = const_cast<Puzzle<T> &>(field);
        auto &tf = const_cast<Puzzle<T> &>(target_field);

        int heuristic = 0;

        for (int i = 0; static_cast<size_t>(i) < field.GetSize() * field.GetSize(); ++i) {
            if (f.At(i) != tf.At(i) && f.At(i) != T{}) {
                ++heuristic;
            }
        }

        return heuristic;
    }

private:
    Heuristics() = default;
};
