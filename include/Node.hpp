#pragma once

#include "Puzzle.hpp"
#include "Heuristics.hpp"

class Node {
public:
    Node(const Puzzle &puzzle,
         Heuristics::Type heuristic_type,
         const Puzzle &target_puzzle,
         Node *parent);
			
    Node(const Puzzle &puzzle,
         Heuristics::Type heuristic_type,
         const Puzzle &target_puzzle);

    Node(const Node &node);

    Node &operator=(const Node &node);

    [[nodiscard]] const Puzzle &GetPuzzle() const;

    [[nodiscard]] int GetHeuristic() const;

    [[nodiscard]] int GetDepth() const;

    [[nodiscard]] Node *GetParent() const;

public:
    friend std::ostream &operator<<(std::ostream &os, const Node &node) {
        os << "h: " << node.heuristic_;
        os << ", d: " << node.depth_;
        os << ", s: " << node.heuristic_ + node.depth_; // TODO is it really necessary
        os << std::endl;
        os << node.GetPuzzle();
        return os;
    }

private:
    Puzzle puzzle_;
    Node *parent_;

    int depth_;
    int heuristic_;

private:
    static int CalculateHeuristics(const Puzzle &puzzle, Heuristics::Type type, const Puzzle &target_puzzle);
};

class OpenSetComparator {
public:
    enum Type {
        GreedySearch,
        UniformSearch,
        AStarSearch
    };

    explicit OpenSetComparator(Type type) : type_(type) {}

    size_t operator()(const Node *lhs, const Node *rhs) const {
        switch (type_) {
            case Type::GreedySearch:
                return lhs->GetDepth() > rhs->GetDepth();
            case Type::UniformSearch:
                return lhs->GetHeuristic() > rhs->GetHeuristic();
            case Type::AStarSearch:
                return lhs->GetHeuristic() + lhs->GetDepth() > rhs->GetHeuristic() + rhs->GetDepth();
        }
    }

private:
    Type type_;
};

struct HashNodeByPuzzle {
public:
    size_t operator()(const Node *node) const {
        return node->GetPuzzle().GetHash();
    }
};

struct EqualNodeByPuzzle {
public:
    size_t operator()(const Node *firstNode, const Node *secondNode) const {
        return firstNode->GetPuzzle() == secondNode->GetPuzzle();
    }
};
