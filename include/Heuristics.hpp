#pragma once

template<class T>
class Heuristics {
public:
    typedef T (*HeuristicFunction)(const Puzzle<T> &, const Puzzle<T> &);

    T GetManhattanDistance(
            [[maybe_unused]] const Puzzle<T> &field,
            [[maybe_unused]] const Puzzle<T> &finishField) {
        T heuristic = 0;

        //TODO not implemented

        return heuristic;
    }

    T GetHammingDistance(
            [[maybe_unused]] const Puzzle<T> &field,
            [[maybe_unused]] const Puzzle<T> &finishField) {
        T heuristic = 0;

        for (int i = 0; i < field.GetSize() * field.GetSize(); i++) {
            if (field.GetCellValue(i) != finishField.GetCellValue(i) && field.GetCellValue(i) != 0)
                heuristic++;
        }

        return heuristic;
    }

private:
    Heuristics() = default;
};
