#pragma once

#include <cmath>
#include <vector>
#include <queue>
#include <unordered_set>

#include "Puzzle.hpp"
#include "Node.hpp"
#include "Move.hpp"

class Solver {
public:
    explicit Solver(Heuristics::Type heuristics_type);

    static bool IsSolvable(const Puzzle &puzzle);

    using OpenNodes = std::priority_queue<Node *, std::vector<Node *>, OpenSetComparator>;
    using ClosedNodes = std::unordered_set<Node *, HashNodeByPuzzle, EqualNodeByPuzzle>;

    void AddChildrenNode(const Puzzle &puzzle,
                         const Puzzle &target_puzzle,
                         OpenNodes &open_nodes,
                         ClosedNodes &closed_nodes,
                         const IMove &move) const {
        Puzzle *new_puzzle = move.Execute(puzzle);

        // Corner zero cell positions
        if (new_puzzle == nullptr) {
            return;
        }

        Node *temp = new Node(*new_puzzle, target_puzzle, heuristics_type_);
        delete new_puzzle;

        if (closed_nodes.find(temp) != closed_nodes.end()) {
            delete temp;
        } else {
            open_nodes.push(temp);
        }
    }

    void AddChildrenNodes(const Puzzle &puzzle,
                          const Puzzle &target_puzzle,
                          OpenNodes &open_nodes,
                          ClosedNodes &closed_nodes) const {
        AddChildrenNode(puzzle, target_puzzle, open_nodes, closed_nodes, MoveLeft());
        AddChildrenNode(puzzle, target_puzzle, open_nodes, closed_nodes, MoveRight());
        AddChildrenNode(puzzle, target_puzzle, open_nodes, closed_nodes, MoveDown());
        AddChildrenNode(puzzle, target_puzzle, open_nodes, closed_nodes, MoveUp());
    }

    void Solve(const Puzzle &puzzle, const Puzzle &target_puzzle) {
        ClosedNodes closed_nodes_;
        OpenNodes open_nodes;

        open_nodes.push(new Node(puzzle, target_puzzle, heuristics_type_));
        
        Node *current_node;
        std::cout << *open_nodes.top() << std::endl;

        while (true) {
            if (open_nodes.empty()) {
                std::cout << "AAAAA" << std::endl;
                return; //Error
            }

            current_node = open_nodes.top();
            open_nodes.pop();
            closed_nodes_.insert(current_node);

            std::cout << *current_node << std::endl;

            if (current_node->GetPuzzle() == target_puzzle) {
                std::cout << *current_node;
                std::cout << "closed nodes: " << closed_nodes_.size() << std::endl;
                std::cout << "open nodes: " << open_nodes.size() << std::endl;
                std::cout << std::endl;
                while (current_node != nullptr) {
                    std::cout << *current_node << std::endl;
                    current_node = current_node->GetParent();
                }
                return;
            }

            AddChildrenNodes(current_node->GetPuzzle(), target_puzzle, open_nodes, closed_nodes_);
        }
    }

private:
    Heuristics::Type heuristics_type_;

    static int CountInversions(const Puzzle &puzzle);
    static int GetZeroRow(const Puzzle &puzzle);
};
