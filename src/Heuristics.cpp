#include "Heuristics.hpp"

int Heuristics::GetManhattanDistance(const Puzzle &field) {
    int heuristics = 0;

    for (size_t i = 0; i < field.GetSize(); i++)
	{
    	for (size_t j = 0; j < field.GetSize(); j++)
		{
    		int currentValue = field.At(i, j);
    		if (currentValue == 0)
				continue;
    		
    		int realPosRow = (currentValue - 1) / field.GetSize();
    		int realPosCol = (currentValue - 1) % field.GetSize();
    		
    		heuristics += (std::abs(static_cast<int>(i) - realPosRow));
			heuristics += (std::abs(static_cast<int>(j) - realPosCol));
		}
	}
    
    return heuristics;
}

int Heuristics::GetHammingDistance(const Puzzle &field) {
    int heuristics = 0;

    for (size_t i = 0; i < field.GetSize() * field.GetSize(); ++i) {
        if (field.At(i) != i + 1 && field.At(i) != 0)
            ++heuristics;
    }

    return heuristics;
}