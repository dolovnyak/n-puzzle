#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP

template<typename T>
T find_manhattan_distance_heuristic(const Puzzle<T>& field, const Puzzle<T>& finishField)
{
	T heuristic = 0;
	
	//TODO
	
	return heuristic;
}

template<typename T>
T find_hamming_distance_heuristic(const Puzzle<T>& field, const Puzzle<T>& finishField)
{
	T heuristic = 0;
	
	for (int i = 0; i < field.GetSize() * field.GetSize(); i++)
	{
		if (field.GetCellValue(i) != finishField.GetCellValue(i) && field.GetCellValue(i) != 0)
			heuristic++;
	}
	
	return heuristic;
}

#endif
