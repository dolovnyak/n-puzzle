#include "gtest/gtest.h"

#include "Puzzle.hpp"
#include "Parser.hpp"
#include "Solver.hpp"

void SolvableCheckerTestWrapper(const std::string &input, bool expectedResult) {
    std::stringstream iss;
    iss << input;

    Parser field_parser;
    Puzzle *field = field_parser.Parse(iss);
    Solver solver(Heuristics::Type::Hamming, OpenSetComparator::AStarSearch);
    ASSERT_EQ(solver.IsSolvable(*field), expectedResult);
    delete field;
}

TEST(SolverTests, Solvable1) {
    const std::string input = "3\n"
                              "1 8 2\n"
                              "0 4 3\n"
                              "7 6 5\n";

    SolvableCheckerTestWrapper(input, true);
}

TEST(SolverTests, Solvable2) {
    const std::string input = "4\n"
                              "13 2 10 3\n"
                              "1 12 8 4\n"
                              "5 0 9 6\n"
                              "15 14 11 7\n";

    SolvableCheckerTestWrapper(input, true);
}

TEST(SolverTests, Solvable3) {
    const std::string input = "4\n"
                              "6 13 7 10\n"
                              "8 9 11 0\n"
                              "15 2 12 5\n"
                              "14 3 1 4\n";

    SolvableCheckerTestWrapper(input, true);
}

TEST(SolverTests, NotSolvable3) {
    const std::string input = "4\n"
                              "3 9 1 15\n"
                              "14 11 4 6\n"
                              "13 0 10 12\n"
                              "2 7 8 5";

    SolvableCheckerTestWrapper(input, false);
}