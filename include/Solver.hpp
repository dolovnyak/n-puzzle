#pragma once

#include <cmath>
#include <utility>
#include <vector>
#include <queue>
#include <unordered_set>

#include "Puzzle.hpp"
#include "Node.hpp"
#include "Move.hpp"

struct ClosedNodesHasher {
public:
    size_t operator()(const std::shared_ptr<Node> &node) const {
        return node->GetPuzzle().GetHash();
    }
};

struct ClosedNodesComparator {
public:
    size_t operator()(const std::shared_ptr<Node> &firstNode, const std::shared_ptr<Node> &secondNode) const {
        return firstNode->GetPuzzle() == secondNode->GetPuzzle();
    }
};

using OpenNodesCompareFunc = std::function<bool(std::shared_ptr<Node>, std::shared_ptr<Node>)>;
using OpenNodes = std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, OpenNodesCompareFunc>;
using ClosedNodes = std::unordered_set<std::shared_ptr<Node>, ClosedNodesHasher, ClosedNodesComparator>;

class Solver {
public:
    class SolverResult {
    public:
        SolverResult(size_t total_open_nodes_count,
                     size_t total_nodes_count,
                     std::vector<std::shared_ptr<Node>> solution);

        [[nodiscard]] size_t GetTotalOpenNodesCount() const {
            return total_open_nodes_count_;
        }

        [[nodiscard]] size_t GetTotalNodesCount() const {
            return total_nodes_count_;
        }

        [[nodiscard]] const std::vector<std::shared_ptr<Node>> &GetSolution() const {
            return solution_;
        }

    private:
        size_t total_open_nodes_count_;
        size_t total_nodes_count_;
        std::vector<std::shared_ptr<Node>> solution_;
    };

    Solver(Heuristics::Type heuristics_type, Algorithm::Type algorithm_type);

    static bool IsSolvable(const Puzzle &puzzle, const Puzzle &target);

    SolverResult Solve(const Puzzle &puzzle, const Puzzle &target);

private:
    struct SolverState {
        size_t total_open_nodes_count = 0;
        OpenNodes open_nodes;
        ClosedNodes closed_nodes;
        Puzzle target_puzzle;

        explicit SolverState(Algorithm::Type algorithm_type, Puzzle target)
                : open_nodes(OpenNodes{Algorithm(algorithm_type)}),
                  closed_nodes(),
                  target_puzzle(std::move(target)) {}
    };

    Heuristics::Type heuristics_type_;
    Algorithm::Type algorithm_type_;

    void AddChild(const std::shared_ptr<Node> &parent,
                  SolverState &state,
                  const Move &move);

    void AddChildren(const std::shared_ptr<Node> &parent,
                     SolverState &state);
};
