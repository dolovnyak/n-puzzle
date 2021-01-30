#include "Heuristics.hpp"

int Heuristics::GetManhattanDistance(
        const Puzzle &puzzle,
        const Puzzle &target_puzzle) {
    int heuristics = 0;

    for (size_t i = 0; i < puzzle.GetSize(); i++)
	{
    	for (size_t j = 0; j < puzzle.GetSize(); j++)
		{
    		int currentValue = puzzle.At(i, j);
    		if (currentValue == 0)
				continue;
    		
    		std::tuple<int, int> targetValuePos = target_puzzle.GetPosition(currentValue);
    		
    		heuristics += (std::abs(static_cast<int>(i) - std::get<0>(targetValuePos)));
			heuristics += (std::abs(static_cast<int>(j) - std::get<1>(targetValuePos)));
		}
	}
    
    return heuristics;
}

int Heuristics::GetLinearConflicts(
        [[maybe_unused]] const Puzzle &puzzle,
        [[maybe_unused]] const Puzzle &target_puzzle)
{
	int heuristics = 0;
	
	return heuristics;
}

int Heuristics::GetHammingDistance(
        const Puzzle &puzzle,
        const Puzzle &target_puzzle) {
    int heuristics = 0;

    for (size_t i = 0; i < puzzle.GetSize() * puzzle.GetSize(); ++i) {
        if (puzzle.At(i) != target_puzzle.At(i))
            ++heuristics;
    }

    return heuristics;
}