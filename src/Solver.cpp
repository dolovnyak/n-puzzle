#include "Solver.hpp"

#include <chrono>

void Solver::AddChild(const std::shared_ptr<Node> &parent,
                      SolverState &state,
                      const Move &move) {
    Puzzle new_puzzle;
    if (move.IsMovable(parent->GetPuzzle())) {
        new_puzzle = move.Execute(parent->GetPuzzle());
    } else {
        return;
    }

    std::shared_ptr<Node> node(new Node(new_puzzle, heuristics_type_, state.target_puzzle, parent));

    if (state.closed_nodes.find(node) == state.closed_nodes.end()) {
        state.open_nodes.push(node);
        ++state.total_open_nodes_count;
    }
}

void Solver::AddChildren(const std::shared_ptr<Node> &parent,
                         SolverState &state) {
    AddChild(parent, state, Move(-1, 0));
    AddChild(parent, state, Move(1, 0));
    AddChild(parent, state, Move(0, -1));
    AddChild(parent, state, Move(0, 1));
}

static inline std::vector<std::shared_ptr<Node>> GetSolution(std::shared_ptr<Node> final_node) {
    std::vector<std::shared_ptr<Node>> nodes;

    while (final_node) {
        nodes.push_back(std::make_unique<Node>(*final_node));
        final_node = final_node->GetParent();
    }

    return nodes;
}

bool Solver::IsSolvable(const Puzzle &puzzle, const Puzzle &target) {
    int inversions = Puzzle::CountInversions(puzzle);
    int target_inversions = Puzzle::CountInversions(target);

    if (puzzle.GetSize() % 2 == 1) {
        return inversions % 2 == target_inversions % 2;
    } else {
        size_t row = puzzle.GetSize() - std::get<0>(puzzle.GetPosition(0));
        size_t target_row = target.GetSize() - std::get<0>(target.GetPosition(0));
        return (row % 2 == target_row % 2) == (inversions % 2 == target_inversions % 2);
    }
}

Solver::Solver(Heuristics::Type heuristics_type, Algorithm::Type algorithm_type)
        : heuristics_type_(heuristics_type),
          algorithm_type_(algorithm_type) {}

Solver::SolverResult Solver::Solve(const Puzzle &puzzle, const Puzzle &target) {
    auto start = std::chrono::high_resolution_clock::now();

    SolverState state(algorithm_type_, target);

    state.open_nodes.push(std::make_unique<Node>(puzzle, heuristics_type_, target));
    ++state.total_open_nodes_count;

    while (true) {
        if (state.open_nodes.empty()) {
            throw std::runtime_error("Map is incorrect.");
        }

        std::shared_ptr<Node> current_node = state.open_nodes.top();
        state.open_nodes.pop();
        state.closed_nodes.insert(current_node);

        if (current_node->GetPuzzle() == target) {
            auto finish = std::chrono::high_resolution_clock::now();
            return SolverResult(std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count(),
                                state.total_open_nodes_count,
                                state.open_nodes.size() + state.closed_nodes.size(),
                                GetSolution(current_node));
        }

        AddChildren(current_node, state);
    }
}

Solver::SolverResult::SolverResult(const size_t total_milliseconds,
                                   const size_t total_open_nodes_count,
                                   const size_t total_nodes_count,
                                   std::vector<std::shared_ptr<Node>> solution)
        : total_milliseconds_(total_milliseconds),
          total_open_nodes_count_(total_open_nodes_count),
          total_nodes_count_(total_nodes_count),
          solution_(std::move(solution)) {}
