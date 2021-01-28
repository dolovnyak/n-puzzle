#include "Heuristics.hpp"

int Heuristics::GetManhattanDistance(const Puzzle &field, const Puzzle &target_field) {
    auto &f = const_cast<Puzzle &>(field);
    auto &tf = const_cast<Puzzle &>(target_field);

    int heuristics = 0;

    // TODO optimize
    for (size_t i = 0; i < f.GetSize(); ++i) {
        for (size_t j = 0; j < f.GetSize(); ++j) {
            if (f.At(i, j) != 0 || f.At(i, j) == tf.At(i, j))
                continue;

            for (size_t ti = 0; ti < tf.GetSize(); ++ti) {
                for (size_t tj = 0; tj < tf.GetSize(); ++tj) {
                    if (f.At(i, j) == tf.At(ti, tj)) {
                        heuristics += std::abs(static_cast<int>(i) - static_cast<int>(ti));
                        heuristics += std::abs(static_cast<int>(j) - static_cast<int>(tj));
                    }
                }
            }
        }
    }

    return heuristics;
}

int Heuristics::GetHammingDistance(const Puzzle &field, const Puzzle &target_field)  {
    auto &f = const_cast<Puzzle &>(field);
    auto &tf = const_cast<Puzzle &>(target_field);

    int heuristics = 0;

    for (size_t i = 0; i < field.GetSize() * field.GetSize(); ++i) {
        if (f.At(i) != tf.At(i) && f.At(i) != 0) {
            ++heuristics;
        }
    }

    return heuristics;
}