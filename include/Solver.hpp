#pragma once

#include <cmath>
#include <vector>
#include <queue>
#include <unordered_set>

#include "Puzzle.hpp"
#include "Node.hpp"

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

    void Solve(const Puzzle<T> &field, const Puzzle<T> &target_field) {
        Node<T> current_node(field, target_field, nullptr);

        while (true) {
            if (current_node.GetField() == target_field)
                return;

            // check each connected to current node and if closedNodes doesn't contain it, add connected node to openNodes

            closed_nodes_.insert(current_node);

            if (open_nodes_.empty())
                return; //Error

            current_node = open_nodes_.top();
            open_nodes_.pop();
        }


//    	Node<T> a(field), b(field);
//    	if (a == b)
//			closed_nodes_.insert(a);
//		Puzzle<T> puzzle(3);
//		closed_nodes_.insert(Node<T>(puzzle));
//		std::cout << *closed_nodes_.find(a) << std::endl;
//		std::cout << *closed_nodes_.find(puzzle) << std::endl;
    }

private:
    std::unordered_set<Node<T>, HashNodeByField<T>> closed_nodes_;
    std::priority_queue<Node<T>, std::vector<Node<T>>, std::greater<Node<T>>> open_nodes_;

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
