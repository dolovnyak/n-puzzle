#include <set>

#include "Heuristics.hpp"

int Heuristics::GetManhattanDistance(
        const Puzzle &puzzle,
        const Puzzle &target_puzzle) {
    int heuristics = 0;

    for (size_t row = 0; row < puzzle.GetSize(); row++) {
        for (size_t column = 0; column < puzzle.GetSize(); column++) {
            int current_value = puzzle.At(row, column);
            if (current_value == 0)
                continue;

            Position target_value_pos = target_puzzle.GetPosition(current_value);

            heuristics += (std::abs(static_cast<int>(row) - static_cast<int>(target_value_pos.row)));
            heuristics += (std::abs(static_cast<int>(column) - static_cast<int>(target_value_pos.col)));
        }
    }

    return heuristics;
}

bool IsContains(const std::vector<LinearConflict> &linear_conflicts, const LinearConflict &linear_conflict) {
	if (std::find(linear_conflicts.begin(), linear_conflicts.end(), linear_conflict) != linear_conflicts.end()) {
		return true;
	}
	
	return false;
}

void AddLinearConflictByRow(const Puzzle &puzzle, const Puzzle &target_puzzle, Position current_value_pos,
							Position target_pos, std::vector<LinearConflict> &linear_conflicts)
{
	int current_value = puzzle.At(current_value_pos);
	int current_linear_conflict_value;
	
	std::function<bool(int)> is_border_reached;
	int dir;
	
	if (current_value_pos.col < target_pos.col) {
		dir = 1;
		is_border_reached = [target_pos](int col) { return col <= static_cast<int>(target_pos.col); };
	}
	else {
		dir = -1;
		is_border_reached = [target_pos](int col) { return col >= static_cast<int>(target_pos.col); };
	}
	
	for (int col = static_cast<int>(current_value_pos.col) + dir; is_border_reached(col); col += dir) {
		current_linear_conflict_value = puzzle.At(current_value_pos.row, col);
		if (current_linear_conflict_value == 0)
			continue;
		if (target_puzzle.GetPosition(current_linear_conflict_value).row == current_value_pos.row) {
			if (!IsContains(linear_conflicts, LinearConflict(current_value, current_linear_conflict_value))) {
				linear_conflicts.emplace_back(current_value, current_linear_conflict_value);
				return;
			}
		}
	}
}

void AddLinearConflictByColumn(const Puzzle &puzzle, const Puzzle &target_puzzle, Position current_value_pos,
							   Position target_pos, std::vector<LinearConflict> &linear_conflicts)
{
	int current_value = puzzle.At(current_value_pos);
	int current_linear_conflict_value;
	
	std::function<bool(int)> is_border_reached;
	int dir;
	
	if (current_value_pos.row < target_pos.row) {
		dir = 1;
		is_border_reached = [target_pos](int row) { return row <= static_cast<int>(target_pos.row); };
	}
	else {
		dir = -1;
		is_border_reached = [target_pos](int row) { return row >= static_cast<int>(target_pos.row); };
	}
	
	for (int row = static_cast<int>(current_value_pos.row) + dir; is_border_reached(row); row += dir) {
		current_linear_conflict_value = puzzle.At(row, current_value_pos.col);
		if (current_linear_conflict_value == 0)
			continue;
		if (target_puzzle.GetPosition(current_linear_conflict_value).col == current_value_pos.col) {
			if (!IsContains(linear_conflicts, LinearConflict(current_value, current_linear_conflict_value))) {
				linear_conflicts.emplace_back(current_value, current_linear_conflict_value);
				return;
			}
		}
	}
}

int Heuristics::GetLinearConflicts(const Puzzle &puzzle, const Puzzle &target_puzzle)
{
	std::vector<LinearConflict> linearConflicts;
	
	for (size_t row = 0; row < puzzle.GetSize(); row++) {
		for (size_t col = 0; col < puzzle.GetSize(); col++) {
			int currentValue = puzzle.At(row, col);
			if (currentValue == 0)
				continue;
			
			Position target_value_position = target_puzzle.GetPosition(currentValue);
			if (target_value_position.row == row && target_value_position.col == col)
				continue;
			
			if (target_value_position.row == row)
				AddLinearConflictByRow(puzzle, target_puzzle, Position(row, col), target_value_position, linearConflicts);
			else if (target_value_position.col == col)
				AddLinearConflictByColumn(puzzle, target_puzzle, Position(row, col), target_value_position, linearConflicts);
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

