#include <iostream>
#include <fstream>

#include "argparse/argparse.hpp"

#include "Parser.hpp"
#include "Puzzle.hpp"
#include "Solver.hpp"
#include "Output.hpp"

int main(int argc, char **argv) {
    argparse::ArgumentParser program("n-puzzle");

    program.add_argument("-i", "--input")
            .required()
            .help("specify the input file.");

    program.add_argument("-h", "--heuristics")
            .required()
            .help("specify the heuristics function.");

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error &err) {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }

    if (!program.present("-i")) {
        program.help();
        return 0;
    }

    auto inputFile = program.get<std::string>("-i");
    std::ifstream is(inputFile);
    if (!is) {
        std::cout << "Can't open file: " << inputFile << std::endl;
        return 0;
    }

    Parser parser;
    try {
        Puzzle *puzzle = parser.Parse(is);
        if (puzzle == nullptr) {
            throw std::logic_error("Parser returned nullptr.");
        }

        // TODO user heuristics
        Solver solver(Heuristics::Type::Hamming);
        if (Solver::IsSolvable(*puzzle)) {
            std::vector<int> cells(puzzle->GetSize() * puzzle->GetSize());
            for (size_t i = 0; i < puzzle->GetSize() * puzzle->GetSize() - 1; i++)
                cells[i] = i + 1;
            cells.back() = 0;
            Puzzle target_puzzle(puzzle->GetSize(), cells);

            solver.Solve(*puzzle, target_puzzle);
        } else {
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

    return 0;
}
