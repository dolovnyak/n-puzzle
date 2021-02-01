#include <iostream>
#include <fstream>

#include "argparse/argparse.hpp"

#include "Parser.hpp"
#include "Puzzle.hpp"
#include "Solver.hpp"
#include "Output.hpp"

unsigned char ToLower(unsigned char c) {
    return std::tolower(c);
}

static Heuristics::Type GetHeuristicsType(const std::string &value) {
    std::string lowerCaseValue = value;
    std::transform(lowerCaseValue.begin(), lowerCaseValue.end(), lowerCaseValue.begin(), ToLower);
    if (lowerCaseValue == "manhattan")
        return Heuristics::Manhattan;
    if (lowerCaseValue == "hamming")
        return Heuristics::Hamming;
    if (lowerCaseValue == "linear_conflicts")
        return Heuristics::LinearConflicts;

    throw std::runtime_error("Heuristic name isn't correct.");
}

static Algorithm::Type GetAlgorithmType(const std::string &value) {
    std::string lowerCaseValue = value;
    std::transform(lowerCaseValue.begin(), lowerCaseValue.end(), lowerCaseValue.begin(), ToLower);
    if (lowerCaseValue == "a-star")
        return Algorithm::Type::AStarSearch;
    if (lowerCaseValue == "greedy")
        return Algorithm::Type::GreedySearch;
    if (lowerCaseValue == "uniform")
        return Algorithm::Type::UniformSearch;

    throw std::runtime_error("Algorithm name isn't correct.");
}

static inline std::ifstream GetStream(const std::string &filename) {
    std::ifstream is(filename);
    if (!is) {
        std::cout << "Can't open file: " << filename << std::endl;
        exit(0);
    }
    return is;
}

int main(int argc, char **argv) {
    argparse::ArgumentParser argparse("n-puzzle");

    argparse.add_argument("start_puzzle")
            .required()
            .help("specify the start puzzle file.");

    argparse.add_argument("-t", "--target_puzzle_filename")
            .help("specify the target puzzle file.");

    argparse.add_argument("-h", "--heuristics")
            .default_value(Heuristics::Manhattan)
            .help("specify the heuristics function [manhattan, hamming, linear_conflicts]. Default - manhattan")
            .action([](const std::string &value) { return GetHeuristicsType(value); });

    argparse.add_argument("-a", "--algorithm")
            .default_value(Algorithm::Type::AStarSearch)
            .help("specify the algorithm [greedy, a-star, uniform]. Default - a-star")
            .action([](const std::string &value) { return GetAlgorithmType(value); });

    try {
        argparse.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cout << err.what() << std::endl;
        std::cout << std::endl;
        std::cout << argparse;
        exit(0);
    }

    try {
        Puzzle input_puzzle;
        Puzzle target_puzzle;

        std::ifstream input_puzzle_stream = GetStream(argparse.get<std::string>("start_puzzle"));

        input_puzzle = Parser::Parse(input_puzzle_stream);

        if (argparse.present("-t")) {
            std::ifstream target_puzzle_stream = GetStream(argparse.get<std::string>("-t"));
            target_puzzle = Parser::Parse(target_puzzle_stream);
        } else {
            target_puzzle = Puzzle::GetSnailPuzzle(input_puzzle.GetSize());
        }

        Solver solver(argparse.get<Heuristics::Type>("-h"),
                      argparse.get<Algorithm::Type>("-a"));

        if (Solver::IsSolvable(input_puzzle, target_puzzle)) {
            const auto &result = solver.Solve(input_puzzle, target_puzzle);
            Output::PrintSolveSteps(result);
        } else {
            std::cout << "Oops! Your puzzle input_puzzle_stream not solvable..." << std::endl;
        }
    } catch (std::exception &ex) {
        std::cout << ex.what();
    }

    exit(0);
}
