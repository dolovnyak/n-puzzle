#include "Node.hpp"

#include <utility>

Node::Node(const Puzzle &puzzle,
           Heuristics::Type heuristic_type,
           const Puzzle &target_puzzle,
           std::shared_ptr<Node> parent)
        : puzzle_(puzzle),
          parent_(std::move(parent)),
          depth_(parent_ != nullptr ? parent_->depth_ + 1 : 0),
          heuristic_(CalculateHeuristics(puzzle, heuristic_type, target_puzzle)) {}

Node::Node(const Puzzle &puzzle,
           Heuristics::Type heuristic_type,
           const Puzzle &target_puzzle)
        : puzzle_(puzzle),
          parent_(nullptr),
          depth_(0),
          heuristic_(CalculateHeuristics(puzzle, heuristic_type, target_puzzle)) {}

const Puzzle &Node::GetPuzzle() const {
    return puzzle_;
}

[[nodiscard]] int Node::GetHeuristic() const {
    return heuristic_;
}

[[nodiscard]] int Node::GetDepth() const {
    return depth_;
}

[[nodiscard]] std::shared_ptr<Node> Node::GetParent() const {
    return parent_;
}

int Node::CalculateHeuristics(const Puzzle &puzzle, Heuristics::Type type, const Puzzle &target_puzzle) {
    switch (type) {
        case Heuristics::Type::Hamming:
            return Heuristics::GetHammingDistance(puzzle, target_puzzle);
        case Heuristics::Type::Manhattan:
            return Heuristics::GetManhattanDistance(puzzle, target_puzzle);
        case Heuristics::Type::LinearConflicts:
            return Heuristics::GetLinearConflicts(puzzle, target_puzzle);
    }
}
