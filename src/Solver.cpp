#include "Solver.hpp"

void Solver::AddChild(Node *parent,
                      SolverState &state,
                      const Move &move) {
    Puzzle *new_puzzle = move.Execute(parent->GetPuzzle());

    // Corner zero cell positions
    if (new_puzzle == nullptr) {
        return;
    }

    Node *temp = new Node(*new_puzzle, heuristics_type_, state.target_puzzle, parent);
    delete new_puzzle;

    if (state.closed_nodes.find(temp) != state.closed_nodes.end()) {
        delete temp;
    } else {
        state.open_nodes.push(temp);
        ++state.total_open_nodes_count;
    }
}

void Solver::AddChildren(Node *parent,
                         SolverState &state) {
    AddChild(parent, state, Move(-1, 0));
    AddChild(parent, state, Move(1, 0));
    AddChild(parent, state, Move(0, -1));
    AddChild(parent, state, Move(0, 1));
}

static inline std::vector<Node *> GetSolution(Node *final_node) {
    std::vector<Node *> nodes;

    while (final_node) {
        nodes.push_back(new Node(*final_node));
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
    SolverState state(algorithm_type_, target);

    state.open_nodes.push(new Node(puzzle, heuristics_type_, target));
    ++state.total_open_nodes_count;

    Node *current_node;
    while (true) {
        if (state.open_nodes.empty()) {
            throw std::runtime_error("Map is incorrect.");
        }

        current_node = state.open_nodes.top();
        state.open_nodes.pop();
        state.closed_nodes.insert(current_node);

        if (current_node->GetPuzzle() == target) {
            return SolverResult(state.total_open_nodes_count,
                                state.open_nodes.size() + state.closed_nodes.size(),
                                GetSolution(current_node));
        }

        AddChildren(current_node, state);
    }
}

Solver::SolverResult::SolverResult(const size_t total_open_nodes_count,
                                   const size_t total_nodes_count,
                                   std::vector<Node *> solution)
        : total_open_nodes_count_(total_open_nodes_count),
          total_nodes_count_(total_nodes_count),
          solution_(std::move(solution)) {}
