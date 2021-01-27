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
        Node<T> currentNode(field, target_field, nullptr);

        while (true) {
            if (currentNode.GetField() == target_field)
                return;

            // check each connected to current node and if closedNodes doesn't contain it, add connected node to openNodes

            closedNodes_.insert(currentNode);

            if (openNodes_.GetSize() == 0)
                return; //Error

            currentNode = openNodes_.Pop();
        }


//    	Node<T> a(field), b(field);
//    	if (a == b)
//			closedNodes_.insert(a);
//		Puzzle<T> puzzle(3);
//		closedNodes_.insert(Node<T>(puzzle));
//		std::cout << *closedNodes_.find(a) << std::endl;
//		std::cout << *closedNodes_.find(puzzle) << std::endl;
    }

private:
    std::unordered_set<Node<T>, HashNodeByField<T>> closedNodes_;
    std::priority_queue<Node<T>, std::vector<Node<T>>, std::greater<Node<T>>> openNodes_;

    int CountInversions(const Puzzle<T> &field) {
        int inversions = 0;

        T defaulT = T{};
        size_t internalSize = field.GetSize() * field.GetSize();
        for (size_t i = 0; i < internalSize; ++i) {
            for (size_t j = i + 1; j < internalSize; ++j) {
                T vi = const_cast<Puzzle<T> &>(field).At(i).value;
                T vj = const_cast<Puzzle<T> &>(field).At(j).value;
                if (vi != defaulT && vj != defaulT && vi > vj) {
                    ++inversions;
                }
            }
        }

        return inversions;
    }

    int GetZeroRow(const Puzzle<T> &field) {
        int size = field.GetSize();

        T defaulT = T{};
        for (int row = size - 1; row >= 0; --row) {
            for (int column = 0; column < size; ++column) {
                if (const_cast<Puzzle<T> &>(field).At(row, column).value == defaulT) {
                    return size - row;
                }
            }
        }

        throw std::logic_error("Not found zero element");
    }
};
