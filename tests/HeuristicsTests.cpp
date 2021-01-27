#include "gtest/gtest.h"

#include "Heuristics.hpp"
#include "Puzzle.hpp"
#include "Parser.hpp"

Puzzle<int> *CreatePuzzle(const std::string& input) {
    Parser<int> parser;
    std::stringstream iss;
    iss << input;
    return parser.Parse(iss);
}

TEST(HeuristicsTests, Hamming1) {
    const std::string field = "3\n"
                              "1 2 3\n"
                              "4 5 6\n"
                              "7 0 8\n";

    const std::string target_field = "3\n"
                                     "1 2 3\n"
                                     "4 5 6\n"
                                     "7 8 0\n";

    Puzzle<int> *puzzle = CreatePuzzle(field);
    Puzzle<int> *target_puzzle = CreatePuzzle(target_field);

    int h = Heuristics<int>::GetHammingDistance(*puzzle, *target_puzzle);
    ASSERT_EQ(h, 1);

    delete puzzle;
    delete target_puzzle;
}

TEST(HeuristicsTests, Hamming2) {
    const std::string field = "3\n"
                              "1 2 3\n"
                              "4 5 6\n"
                              "0 7 8\n";

    const std::string target_field = "3\n"
                                     "1 2 3\n"
                                     "4 5 6\n"
                                     "7 8 0\n";

    Puzzle<int> *puzzle = CreatePuzzle(field);
    Puzzle<int> *target_puzzle = CreatePuzzle(target_field);

    int h = Heuristics<int>::GetHammingDistance(*puzzle, *target_puzzle);
    ASSERT_EQ(h, 2);

    delete puzzle;
    delete target_puzzle;
}

TEST(HeuristicsTests, Manhattan1) {
    const std::string field = "3\n"
                              "1 2 3\n"
                              "4 5 6\n"
                              "7 0 8\n";

    const std::string target_field = "3\n"
                                     "1 2 3\n"
                                     "4 5 6\n"
                                     "7 8 0\n";

    Puzzle<int> *puzzle = CreatePuzzle(field);
    Puzzle<int> *target_puzzle = CreatePuzzle(target_field);

    int h = Heuristics<int>::GetManhattanDistance(*puzzle, *target_puzzle);
    ASSERT_EQ(h, 1);

    delete puzzle;
    delete target_puzzle;
}

TEST(HeuristicsTests, Manhattan2) {
    const std::string field = "3\n"
                              "1 2 3\n"
                              "4 5 6\n"
                              "0 8 7\n";

    const std::string target_field = "3\n"
                                     "1 2 3\n"
                                     "4 5 6\n"
                                     "7 8 0\n";

    Puzzle<int> *puzzle = CreatePuzzle(field);
    Puzzle<int> *target_puzzle = CreatePuzzle(target_field);

    int h = Heuristics<int>::GetManhattanDistance(*puzzle, *target_puzzle);
    ASSERT_EQ(h, 2);

    delete puzzle;
    delete target_puzzle;
}