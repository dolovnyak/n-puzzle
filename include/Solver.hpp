#pragma once

#include <cmath>
#include <vector>
#include <queue>
#include <unordered_set>

#include "Puzzle.hpp"
#include "Node.hpp"

enum MoveState
{
	Left = 0,
	Right,
	Top,
	Bot
};

template<class T>
class Solver {
public:
    Solver() : default_t_(T{}) {}

    bool IsSolvable(const Puzzle<T> &field) {
        int inversions = CountInversions(field);
        if (field.GetSize() % 2 != 0) {
            return inversions % 2 == 0;
        } else {
            int zeroRow = GetZeroRow(field);
            return (inversions + zeroRow) % 2 == 1;
        }
    }

    Puzzle<T> NewFieldByMoveEmptyCell(Puzzle<T> field, MoveState moveState)
	{
    	int row = 0 , column = 0;
    	
    	field.GetIndexByValue(0, &row, &column);
    	switch (moveState)
		{
			case MoveState::Left:
				if (column != 0) {
					field.At(row, column) = field.At(row, column - 1);
					field.At(row, column - 1) = 0;
				}
				break;
			case MoveState::Right:
				if (column < field.GetSize() - 1) {
					field.At(row, column) = field.At(row, column + 1);
					field.At(row, column + 1) = 0;
				}
				break;
			case MoveState::Top:
				if (row != 0) {
					field.At(row, column) = field.At(row - 1, column);
					field.At(row - 1, column) = 0;
				}
				break;
			case MoveState::Bot:
				if (row < field.GetSize() - 1) {
					field.At(row, column) = field.At(row + 1, column);
					field.At(row + 1, column) = 0;
				}
				break;
			default:
				break;
		}
		
		return field;
	}
    
    void AddChildrenToOpenNodes(Node<T> *node)
	{
    	Node<T> *tmpNode;
		
    	for (int i = 0; i < 4; i++)
		{
			Puzzle<T> field = NewFieldByMoveEmptyCell(node->GetField(), (MoveState)i);
			tmpNode = new Node<T>(field, target_field_, heuristic_function_, node);
			if (closed_nodes_.find(tmpNode) != closed_nodes_.end())
				delete tmpNode;
			else
			{
//				std::cout << field << std::endl;
				open_nodes_.push(tmpNode);
			}
		}
	}
    
    void Solve(const Puzzle<T> &field, const Puzzle<T> &target_field,
			   typename Heuristics<T>::HeuristicFunction heuristic_function) {
				target_field_ = target_field;
    	heuristic_function_ = heuristic_function;
    	
		open_nodes_.push(new Node<T>(field, target_field, heuristic_function));
		Node<T>* current_node;
		std::cout << *open_nodes_.top() << std::endl;
	
		while (true) {
			if (open_nodes_.empty())
			{
				std::cout << "AAAAA" << std::endl;
				return; //Error
			}
				
			current_node = open_nodes_.top();
			open_nodes_.pop();
			closed_nodes_.insert(current_node);
			
			std::cout << *current_node << std::endl;
			
			if (current_node->GetField() == target_field_)
			{
				std::cout << *current_node;
				std::cout << "closed nodes: " << closed_nodes_.size() << std::endl;
				std::cout << "open nodes: " << open_nodes_.size() << std::endl;
				std::cout << std::endl;
				while (current_node != nullptr)
				{
					std::cout << *current_node << std::endl;
					current_node = current_node->GetParent();
				}
				return;
			}
			
			AddChildrenToOpenNodes(current_node);
        }
    }

private:
    std::unordered_set<Node<T>*, HashNodeByField<T>, EqualNodeByField<T>> closed_nodes_;
    std::priority_queue<Node<T>*, std::vector<Node<T>*>, GreaterNodeByScore<T>> open_nodes_;
	typename Heuristics<T>::HeuristicFunction heuristic_function_;
	Puzzle<T> target_field_;
    T default_t_;

    int CountInversions(const Puzzle<T> &field) {
        int inversions = 0;

        size_t internalSize = field.GetSize() * field.GetSize();
        for (size_t i = 0; i < internalSize; ++i) {
            for (size_t j = i + 1; j < internalSize; ++j) {
                T vi = const_cast<Puzzle<T> &>(field).At(i);
                T vj = const_cast<Puzzle<T> &>(field).At(j);
                if (vi != default_t_ && vj != default_t_ && vi > vj) {
                    ++inversions;
                }
            }
        }

        return inversions;
    }

    int GetZeroRow(const Puzzle<T> &field) {
        int size = field.GetSize();

        for (int row = size - 1; row >= 0; --row) {
            for (int column = 0; column < size; ++column) {
                if (const_cast<Puzzle<T> &>(field).At(row, column) == default_t_) {
                    return size - row;
                }
            }
        }

        throw std::logic_error("Not found zero element");
    }
};
