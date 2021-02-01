#include <set>

#include "Heuristics.hpp"

int Heuristics::GetManhattanDistance(
        const Puzzle &puzzle,
        const Puzzle &target_puzzle) {
    int heuristics = 0;

    for (size_t i = 0; i < puzzle.GetSize(); i++) {
        for (size_t j = 0; j < puzzle.GetSize(); j++) {
            int current_value = puzzle.At(i, j);
            if (current_value == 0)
                continue;

            std::tuple<int, int> target_value_pos = target_puzzle.GetPosition(current_value);

            heuristics += (std::abs(static_cast<int>(i) - std::get<0>(target_value_pos)));
            heuristics += (std::abs(static_cast<int>(j) - std::get<1>(target_value_pos)));
        }
    }

    return heuristics;
}

//TODO I know there is a lot of duplicated code, if you can please refactor
bool IsLinearConflictByRow(const Puzzle &puzzle, const Puzzle &target_puzzle, std::tuple<int, int> pos,
                           std::tuple<int, int> targetPos, int &linearConflictValue) {
    int row = std::get<0>(pos);
    int posCol = std::get<1>(pos);
    int targetPosCol = std::get<1>(targetPos);

    if (posCol < targetPosCol) {
        for (int col = posCol + 1; col <= targetPosCol; col++) {
            int tmpValue = puzzle.At(row, col);
            if (tmpValue == 0)
                continue;
            std::tuple<int, int> targetTmpValuePos = target_puzzle.GetPosition(tmpValue);
            if (std::get<0>(targetTmpValuePos) == row) {
                linearConflictValue = tmpValue;
                return true;
            }
        }
    } else {
        for (int col = posCol - 1; col >= targetPosCol; --col) {
            int tmpValue = puzzle.At(row, col);
            if (tmpValue == 0)
                continue;
            std::tuple<int, int> targetTmpValuePos = target_puzzle.GetPosition(tmpValue);
            if (std::get<0>(targetTmpValuePos) == row) {
                linearConflictValue = tmpValue;
                return true;
            }
        }
    }

    return false;
}

bool IsLinearConflictByColumn(const Puzzle &puzzle, const Puzzle &target_puzzle, std::tuple<int, int> pos,
                              std::tuple<int, int> targetPos, int &linearConflictValue) {
    int col = std::get<1>(pos);
    int posRow = std::get<0>(pos);
    int targetPosRow = std::get<0>(targetPos);

    if (posRow < targetPosRow) {
        for (int row = posRow + 1; row <= targetPosRow; row++) {
            int tmpValue = puzzle.At(row, col);
            if (tmpValue == 0)
                continue;
            std::tuple<int, int> targetTmpValuePos = target_puzzle.GetPosition(tmpValue);
            if (std::get<1>(targetTmpValuePos) == col) {
                linearConflictValue = tmpValue;
                return true;
            }
        }
    } else {
        for (int row = posRow - 1; row >= targetPosRow; row--) {
            int tmpValue = puzzle.At(row, col);
            if (tmpValue == 0)
                continue;
            std::tuple<int, int> targetTmpValuePos = target_puzzle.GetPosition(tmpValue);
            if (std::get<1>(targetTmpValuePos) == col) {
                linearConflictValue = tmpValue;
                return true;
            }
        }
    }

    return false;
}

int Heuristics::GetLinearConflicts(const Puzzle &puzzle, const Puzzle &target_puzzle) {
    std::vector<LinearConflict> linearConflicts;
    int linearConflictValue;

    for (int row = 0; row < static_cast<int>(puzzle.GetSize()); row++) {
        for (int col = 0; col < static_cast<int>(puzzle.GetSize()); col++) {
            int currentValue = puzzle.At(row, col);
            if (currentValue == 0)
                continue;
            std::tuple<int, int> targetValuePos = target_puzzle.GetPosition(currentValue);
            if (std::get<0>(targetValuePos) == row && std::get<1>(targetValuePos) == col)
                continue;
            if (std::get<0>(targetValuePos) == row) {
                if (IsLinearConflictByRow(puzzle, target_puzzle, std::tuple<int, int>(row, col), targetValuePos, linearConflictValue)) {
                    if (std::find(linearConflicts.begin(), linearConflicts.end(),
                                  LinearConflict(currentValue, linearConflictValue)) == linearConflicts.end())
                        linearConflicts.emplace_back(currentValue, linearConflictValue);
                }
            } else if (std::get<1>(targetValuePos) == col) {
                if (IsLinearConflictByColumn(puzzle, target_puzzle, std::tuple<int, int>(row, col), targetValuePos, linearConflictValue)) {
                    if (std::find(linearConflicts.begin(), linearConflicts.end(),
                                  LinearConflict(currentValue, linearConflictValue)) == linearConflicts.end())
                        linearConflicts.emplace_back(currentValue, linearConflictValue);
                }
            }
        }
    }
    return (static_cast<int>(linearConflicts.size()) * 2 + GetManhattanDistance(puzzle, target_puzzle));
}

int Heuristics::GetHammingDistance(
        const Puzzle &puzzle,
        const Puzzle &target_puzzle) {
    int heuristics = 0;

    for (size_t i = 0; i < puzzle.GetSize() * puzzle.GetSize(); ++i) {
        if (puzzle.At(i) != 0 && puzzle.At(i) != target_puzzle.At(i))
            ++heuristics;
    }

    return heuristics;
}

LinearConflict::LinearConflict(int x, int y)
        : x_(x),
          y_(y) {}

bool LinearConflict::operator==(const LinearConflict &linear_conflict) const {
    return ((x_ == linear_conflict.x_ && y_ == linear_conflict.y_) ||
            (x_ == linear_conflict.y_ && y_ == linear_conflict.x_));
}
