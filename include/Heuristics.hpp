#pragma once

template<class T>
class Heuristics {
public:
    typedef T (*HeuristicFunction)(const Puzzle<T> &, const Puzzle<T> &);

    int GetManhattanDistance(
            [[maybe_unused]] const Puzzle<T> &field,
            [[maybe_unused]] const Puzzle<T> &target_field) {
        int heuristic = 0;

        // TODO optimize
        for (int i = 0; i < field.GetSize(); ++i) {
            for (int j = 0; j < field.GetSize(); ++j) {
                if (field.At(i, j) == target_field.At(i, j))
                    continue;

                for (int ti = 0; ti < field.GetSize(); ++ti) {
                    for (int tj = 0; tj < field.GetSize(); ++tj) {
                        if (field.At(i, j) == target_field.At(ti, tj)) {
                            heuristic += std::abs(i - ti) + std::abs(j - tj);
                        }
                    }
                }
            }
        }

        return heuristic;
    }

    int GetHammingDistance(
            [[maybe_unused]] const Puzzle<T> &field,
            [[maybe_unused]] const Puzzle<T> &target_field) {
        int heuristic = 0;

        for (int i = 0; i < field.GetSize() * field.GetSize(); ++i) {
            if (field.At(i).value != target_field.At(i).value) {
                ++heuristic;
            }
        }

        return heuristic;
    }

private:
    Heuristics() = default;
};
