#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>

#include "argparse/argparse.hpp"

#include "Parser.hpp"
#include "Puzzle.hpp"
#include "Solver.hpp"
#include "Output.hpp"

static Heuristics::Type fromStringToHeuristicType(const std::string &value) {
    if (boost::iequals(value, "manhattan"))
        return Heuristics::Manhattan;
    if (boost::iequals(value, "hamming"))
        return Heuristics::Hamming;
    if (boost::iequals(value, "linear_conflicts"))
        return Heuristics::LinearConflicts;

    throw std::runtime_error("Heuristic name isn't correct.");
}

static OpenSetComparator::Type fromStringToAlgorithmType(const std::string &value) {
    if (boost::iequals(value, "a-star"))
        return OpenSetComparator::Type::AStarSearch;
    if (boost::iequals(value, "greedy"))
        return OpenSetComparator::Type::GreedySearch;
    if (boost::iequals(value, "uniform"))
        return OpenSetComparator::Type::UniformSearch;

    throw std::runtime_error("Algorithm name isn't correct.");
}

int main(int argc, char **argv) {
    argparse::ArgumentParser argumentParser("n-puzzle");

    argumentParser.add_argument("input_file")
            .required()
            .help("specify the input file.");

    argumentParser.add_argument("-h", "--heuristics")
            .default_value(Heuristics::Manhattan)
            .help("specify the heuristics function. (Manhattan, Hamming, LinearConflicts), default - Manhattan")
            .action([](const std::string &value) { return fromStringToHeuristicType(value); });

    argumentParser.add_argument("-a", "--algorithm")
            .default_value(OpenSetComparator::Type::AStarSearch)
            .help("specify the algorithm. (Greedy, AStar, Uniform), default - AStar")
            .action([](const std::string &value) { return fromStringToAlgorithmType(value); });

    try {
        argumentParser.parse_args(argc, argv);
    }
    catch (const std::runtime_error &err) {
        std::cout << err.what() << std::endl;
        std::cout << std::endl;
        std::cout << argumentParser;
        exit(0);
    }

    auto inputFile = argumentParser.get<std::string>("input_file");
    std::ifstream is(inputFile);
    if (!is) {
        std::cout << "Can't open file: " << inputFile << std::endl;
        exit(0);
    }

    Parser parser;
    Output output;
    try {
        Puzzle *puzzle = parser.Parse(is);
        if (puzzle == nullptr) {
            throw std::logic_error("Parser returned nullptr.");
        }

        Solver solver(argumentParser.get<Heuristics::Type>("-h"),
                      argumentParser.get<OpenSetComparator::Type>("-a"));

        if (solver.IsSolvable(*puzzle)) {
            const auto &result = solver.Solve(*puzzle);
            output.PrintSolveSteps(result);
        } else {
            std::cout << "Oops! Your puzzle is not solvable..." << std::endl;
        }

        delete puzzle;
    }
    catch (ParseException &parseException) {
        std::cout << parseException.what();
        is.close();

        is.open(inputFile);
        output.PrintParseException(is, parseException);
    }
    catch (const std::exception &e) {
        std::cout << e.what();
    }

    exit(0);
}
