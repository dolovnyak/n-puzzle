#pragma once

#include "Puzzle.hpp"
#include "Heuristics.hpp"

class Node {
public:
    Node(const Puzzle &puzzle,
         Heuristics::Type heuristic_type,
         const Puzzle &target_puzzle,
         std::shared_ptr<Node> parent);

    Node(const Puzzle &puzzle,
         Heuristics::Type heuristic_type,
         const Puzzle &target_puzzle);

    [[nodiscard]] const Puzzle &GetPuzzle() const;

    [[nodiscard]] int GetHeuristic() const;

    [[nodiscard]] int GetDepth() const;

    [[nodiscard]] std::shared_ptr<Node> GetParent() const;

public:
    friend std::ostream &operator<<(std::ostream &os, const Node &node) {
        os << "h: " << node.heuristic_;
        os << ", d: " << node.depth_;
        os << ", s: " << node.heuristic_ + node.depth_; // TODO add time
        os << std::endl;
        os << node.GetPuzzle();
        return os;
    }

private:
    Puzzle puzzle_;
    std::shared_ptr<Node> parent_;

    int depth_;
    int heuristic_;

private:
    static int CalculateHeuristics(const Puzzle &puzzle, Heuristics::Type type, const Puzzle &target_puzzle);
};

class Algorithm {
public:
    enum Type {
        GreedySearch,
        UniformSearch,
        AStarSearch
    };

    explicit Algorithm(Type type)
            : type_(type) {}

    size_t operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const {
        switch (type_) {
            case Type::GreedySearch:
                return lhs->GetHeuristic() > rhs->GetHeuristic();
            case Type::UniformSearch:
                return lhs->GetDepth() > rhs->GetDepth();
            case Type::AStarSearch:
                return lhs->GetHeuristic() + lhs->GetDepth() > rhs->GetHeuristic() + rhs->GetDepth();
        }
    }

private:
    Type type_;
};
