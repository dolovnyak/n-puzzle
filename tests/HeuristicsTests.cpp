#include "gtest/gtest.h"

#include "Heuristics.hpp"
#include "Puzzle.hpp"
#include "Parser.hpp"


class HeuristicsTests : public ::testing::Test {
public:
    static Puzzle *CreatePuzzle(const std::string& input) {
        Parser parser;
        std::stringstream iss;
        iss << input;
        return parser.Parse(iss);
    }
};

TEST_F(HeuristicsTests, Hamming1) {
    const std::string field = "3\n"
                              "1 2 3\n"
                              "4 5 6\n"
                              "7 0 8\n";

    const std::string target_field = "3\n"
                                     "1 2 3\n"
                                     "4 5 6\n"
                                     "7 8 0\n";

    Puzzle *puzzle = HeuristicsTests::CreatePuzzle(field);
    Puzzle *target_puzzle = HeuristicsTests::CreatePuzzle(target_field);

    int h = Heuristics::GetHammingDistance(*puzzle);
    ASSERT_EQ(h, 1);

    delete puzzle;
    delete target_puzzle;
}

TEST_F(HeuristicsTests, Hamming2) {
    const std::string field = "3\n"
                              "1 2 3\n"
                              "4 5 6\n"
                              "0 7 8\n";

    const std::string target_field = "3\n"
                                     "1 2 3\n"
                                     "4 5 6\n"
                                     "7 8 0\n";

    Puzzle *puzzle = HeuristicsTests::CreatePuzzle(field);
    Puzzle *target_puzzle = HeuristicsTests::CreatePuzzle(target_field);

    int h = Heuristics::GetHammingDistance(*puzzle);
    ASSERT_EQ(h, 2);

    delete puzzle;
    delete target_puzzle;
}

TEST_F(HeuristicsTests, Manhattan1) {
    const std::string field = "3\n"
                              "1 2 3\n"
                              "4 5 6\n"
                              "7 0 8\n";

    const std::string target_field = "3\n"
                                     "1 2 3\n"
                                     "4 5 6\n"
                                     "7 8 0\n";

    Puzzle *puzzle = HeuristicsTests::CreatePuzzle(field);
    Puzzle *target_puzzle = HeuristicsTests::CreatePuzzle(target_field);

    int h = Heuristics::GetManhattanDistance(*puzzle);
    ASSERT_EQ(h, 1);

    delete puzzle;
    delete target_puzzle;
}

TEST_F(HeuristicsTests, Manhattan2) {
    const std::string field = "3\n"
                              "1 2 3\n"
                              "4 5 6\n"
                              "0 8 7\n";

    const std::string target_field = "3\n"
                                     "1 2 3\n"
                                     "4 5 6\n"
                                     "7 8 0\n";

    Puzzle *puzzle = HeuristicsTests::CreatePuzzle(field);
    Puzzle *target_puzzle = HeuristicsTests::CreatePuzzle(target_field);

    int h = Heuristics::GetManhattanDistance(*puzzle);
    ASSERT_EQ(h, 2);

    delete puzzle;
    delete target_puzzle;
}