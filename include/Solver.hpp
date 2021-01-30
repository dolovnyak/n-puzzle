#pragma once

#include <cmath>
#include <vector>
#include <queue>
#include <unordered_set>

#include "Puzzle.hpp"
#include "Node.hpp"
#include "Move.hpp"

using OpenNodes = std::priority_queue<Node *, std::vector<Node *>, std::function<bool(Node *, Node *)>>;
using ClosedNodes = std::unordered_set<Node *, HashNodeByPuzzle, EqualNodeByPuzzle>;

class Solver {
public:
    class SolverResult {
    public:
        SolverResult(size_t total_open_nodes_count,
                     size_t total_nodes_count,
                     std::vector<Node *> solution);

        [[nodiscard]] size_t GetTotalOpenNodesCount() const {
            return total_open_nodes_count_;
        }

        [[nodiscard]] size_t GetTotalNodesCount() const {
            return total_nodes_count_;
        }

        [[nodiscard]] const std::vector<Node *> &GetSolution() const {
            return solution_;
        }

        virtual ~SolverResult() {
            for (Node *node : solution_) {
                delete node;
            }
            solution_.clear();
        }

    private:
        size_t total_open_nodes_count_;
        size_t total_nodes_count_;
        std::vector<Node *> solution_;
    };

    Solver(Heuristics::Type heuristicsType, OpenSetComparator::Type algorithmType);

    static bool IsSolvable(const Puzzle &puzzle, const Puzzle &target);

    SolverResult Solve(const Puzzle &puzzle);

private:
    struct SolverState {
        size_t total_open_nodes_count;
        OpenNodes open_nodes;
        ClosedNodes closed_nodes;

        explicit SolverState(OpenSetComparator::Type algorithm_type)
                : total_open_nodes_count(0),
                  open_nodes(OpenNodes{OpenSetComparator(algorithm_type)}),
                  closed_nodes() {}

        virtual ~SolverState() {
            while (!open_nodes.empty()) {
                delete open_nodes.top();
                open_nodes.pop();
            }
            for (Node *node : closed_nodes) {
                delete node;
            }
            closed_nodes.clear();
        }
    };

    Heuristics::Type heuristics_type_;
    OpenSetComparator::Type algorithm_type_;

    void AddChild(Node *parent,
                  SolverState &state,
                  const Move &move);

    void AddChildren(Node *parent,
                     SolverState &state);
};
