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

    Parser<int> field_parser;
    try {
        Puzzle<int> *field = field_parser.Parse(is);
        if (field == nullptr) {
            throw std::logic_error("Parser returned nullptr.");
        }

        Solver<int> solver;
        if (solver.IsSolvable(*field)) {

            Puzzle<int> finishField(field->GetSize());
            for (size_t i = 0; i < field->GetSize() * field->GetSize() - 1; i++)
                finishField.At(i) = i + 1;
            finishField.At(finishField.GetSize() * finishField.GetSize() - 1) = 0;

            solver.Solve(*field, finishField, Heuristics<int>::GetHammingDistance); //TODO choose heuristic from user input
        } else {
            std::cout << "Oops! Your field is not solvable..." << std::endl;
        }

        delete field;
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
