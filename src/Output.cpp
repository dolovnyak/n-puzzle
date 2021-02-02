#include <sstream>

#include "Output.hpp"

void Output::PrintSolveSteps(const Solver::SolverResult &solver_result) {
    if (solver_result.GetSolution().empty()) {
        throw std::logic_error("Incorrect solution size.");
    }
    for (size_t i = solver_result.GetSolution().size(); i > 0; --i)
        std::cout << *solver_result.GetSolution()[i - 1] << std::endl;
    std::cout << "Time used: " << solver_result.GetTotalTime() / 1000 << "." << solver_result.GetTotalTime() % 1000 << "s" << std::endl;
    std::cout << "Open nodes ever: " << solver_result.GetTotalOpenNodesCount() << std::endl;
    std::cout << "Maximum number of nodes: " << solver_result.GetTotalNodesCount() << std::endl;
    std::cout << "Moves to solve puzzle: " << solver_result.GetSolution().size() << std::endl;
}
