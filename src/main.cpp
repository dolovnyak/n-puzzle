#include <iostream>
#include <fstream>

#include "argparse/argparse.hpp"

#include "Parser.hpp"
#include "Puzzle.hpp"
#include "Solver.hpp"
#include "Output.hpp"

static Heuristics::Type fromStringToHeuristicType(const std::string &value) {
	std::string lowerCaseValue = value;
	std::transform(lowerCaseValue.begin(), lowerCaseValue.end(), lowerCaseValue.begin(),
				   [](unsigned char c){ return std::tolower(c); });
    if (lowerCaseValue == "manhattan")
        return Heuristics::Manhattan;
    if (lowerCaseValue == "hamming")
        return Heuristics::Hamming;
    if (lowerCaseValue == "linear_conflicts")
        return Heuristics::LinearConflicts;

    throw std::runtime_error("Heuristic name isn't correct.");
}

static OpenSetComparator::Type fromStringToAlgorithmType(const std::string &value) {
	std::string lowerCaseValue = value;
	std::transform(lowerCaseValue.begin(), lowerCaseValue.end(), lowerCaseValue.begin(),
				   [](unsigned char c){ return std::tolower(c); });
    if (lowerCaseValue == "a-star")
        return OpenSetComparator::Type::AStarSearch;
    if (lowerCaseValue == "greedy")
        return OpenSetComparator::Type::GreedySearch;
    if (lowerCaseValue == "uniform")
        return OpenSetComparator::Type::UniformSearch;

    throw std::runtime_error("Algorithm name isn't correct.");
}

int main(int argc, char **argv) {
    argparse::ArgumentParser argumentParser("n-puzzle");

    argumentParser.add_argument("start_puzzle")
            .required()
            .help("specify the start puzzle file.");
    
	argumentParser.add_argument("target_puzzle")
			.required()
			.help("specify the target puzzle file.");
	
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

    auto startPuzzleFile = argumentParser.get<std::string>("start_puzzle");
	auto targetPuzzleFile = argumentParser.get<std::string>("target_puzzle");
	std::ifstream startPuzzleStream(startPuzzleFile);
	std::ifstream targetPuzzleStream(targetPuzzleFile);
    if (!startPuzzleStream) {
        std::cout << "Can't open file: " << startPuzzleFile << std::endl;
        exit(0);
    }
	if (!targetPuzzleStream) {
		std::cout << "Can't open file: " << startPuzzleFile << std::endl;
		exit(0);
	}
	
	Parser parser;
	Output output;
	Puzzle *startPuzzle;
    Puzzle *targetPuzzle;
    
    try {
		startPuzzle = parser.Parse(startPuzzleStream);
		targetPuzzle = parser.Parse(targetPuzzleStream);
        if (startPuzzle == nullptr) {
            throw std::logic_error("Parser returned nullptr.");
        }
	}
	catch (ParseException &parseException) {
		std::cout << parseException.what();
		startPuzzleStream.close();
	}
	
	try {
		Solver solver(argumentParser.get<Heuristics::Type>("-h"),
					  argumentParser.get<OpenSetComparator::Type>("-a"));
		
		if (Solver::IsSolvable(*startPuzzle, *targetPuzzle)) {
			const auto& result = solver.Solve(*startPuzzle, *targetPuzzle);
			output.PrintSolveSteps(result);
		}
		else {
			std::cout << "Oops! Your puzzle startPuzzleStream not solvable..." << std::endl;
		}
		
		delete startPuzzle;
		delete targetPuzzle;
	}
    catch (const std::exception &e) {
        std::cout << e.what();
    }

    exit(0);
}
