#include <iostream>
#include <fstream>

#include "argparse/argparse.hpp"

#include "Parser.hpp"
#include "Puzzle.hpp"
#include "Solver.hpp"
#include "Output.hpp"

static Heuristics::Type fromStringToHeuristicType(const std::string &value)
{
	if (value == "Manhattan")
		return Heuristics::Manhattan;
	if (value == "Hamming")
		return Heuristics::Hamming;
	if (value == "LinearConflicts")
		return Heuristics::LinearConflicts;
		
	throw std::runtime_error("Heuristic name doesn't correct");
}

static OpenSetComparator::Type fromStringToAlgorithmType(const std::string &value)
{
	if (value == "AStar")
		return OpenSetComparator::Type::AStarSearch;
	if (value == "Greedy")
		return OpenSetComparator::Type::GreedySearch;
	if (value == "Uniform")
		return OpenSetComparator::Type::UniformSearch;
	
	throw std::runtime_error("Algorithm name doesn't correct");
}

int main(int argc, char **argv) {
    argparse::ArgumentParser argumentParser("n-puzzle");
	
	argumentParser.add_argument("input_file")
            .required()
            .help("specify the input file.");

    argumentParser.add_argument("-h", "--heuristics")
			.default_value(Heuristics::Manhattan)
            .help("specify the heuristics function. (Manhattan, Hamming, LinearConflicts), default - Manhattan")
            .action([](const std::string& value) { return fromStringToHeuristicType(value); });
    
	argumentParser.add_argument("-a", "--algorithm")
			.default_value(OpenSetComparator::Type::AStarSearch)
			.help("specify the algorithm. (Greedy, AStar, Uniform), default - AStar")
			.action([](const std::string& value) { return fromStringToAlgorithmType(value); });
	
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
    try {
        Puzzle *puzzle = parser.Parse(is);
        if (puzzle == nullptr) {
            throw std::logic_error("Parser returned nullptr.");
        }

        if (Solver::IsSolvable(*puzzle)) {
				Solver::Solve(*puzzle,
							  argumentParser.get<Heuristics::Type>("-h"),
							  argumentParser.get<OpenSetComparator::Type>("-a"));
        }
        else {
            std::cout << "Oops! Your puzzle is not solvable..." << std::endl;
        }

        delete puzzle;
    }
    catch (ParseException &parseException) {
        std::cout << parseException.what();
        is.close();

        is.open(inputFile);
        Output output;
        output.VisualizeParseException(is, parseException);
    }
    catch (const std::exception &e) {
		std::cout << e.what();
	}
	
    return 0;
}
