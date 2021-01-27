#ifndef SOLVER_HPP_
# define SOLVER_HPP_

# include <cmath>
# include <queue>
# include <unordered_set>

# include "Puzzle.hpp"
# include "Node.hpp"

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
    
    void Solve(const Puzzle<TValue>& field, const Puzzle<TValue>& finishField)
	{
    	Node<TValue> currentNode(field, finishField, nullptr);
    	
    	while (true)
		{
    		if (currentNode.GetField() == finishField)
				return;
    		
    		// check each connected to current node and if closedNodes doesn't contain it, add connected node to openNodes
    		
    		closedNodes_.insert(currentNode);
    		
    		if (openNodes_.GetSize() == 0)
				return; //Error
    		
    		currentNode = openNodes_.Pop();
		}


//    	Node<TValue> a(field), b(field);
//    	if (a == b)
//			closedNodes_.insert(a);
//		Puzzle<TValue> puzzle(3);
//		closedNodes_.insert(Node<TValue>(puzzle));
//		std::cout << *closedNodes_.find(a) << std::endl;
//		std::cout << *closedNodes_.find(puzzle) << std::endl;
	}

private:
	std::unordered_set<Node<TValue>, HashNodeByField<TValue>> closedNodes_;

    using PriorityQueue = std::priority_queue<Node<TValue>>;
    PriorityQueue openNodes_;
	
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
