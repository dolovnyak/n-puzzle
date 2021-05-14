#include "gtest/gtest.h"

#include <fstream>

#include "Puzzle.hpp"
#include "Parser.hpp"
#include "Solver.hpp"

std::vector<std::string> solvable_input_files = {
        "solvable3_1.txt",
        "solvable3_2.txt",
        "solvable3_3.txt",
        "solvable3_4.txt",
        "solvable3_5.txt",
        "solvable4_1.txt",
        "solvable4_2.txt",
        "solvable4_3.txt",
        "solvable4_4.txt",
        "solvable4_5.txt",
        "solvable5_1.txt",
        "solvable5_2.txt",
        "solvable5_3.txt",
        "solvable5_4.txt",
        "solvable5_5.txt",
        "solvable6_1.txt",
        "solvable6_2.txt",
        "solvable6_3.txt",
        "solvable6_4.txt",
        "solvable6_5.txt",
};

std::vector<std::string> unsolvable_input_files = {
        "unsolvable3_1.txt",
        "unsolvable3_2.txt",
        "unsolvable3_3.txt",
        "unsolvable3_4.txt",
        "unsolvable3_5.txt",
        "unsolvable4_1.txt",
        "unsolvable4_2.txt",
        "unsolvable4_3.txt",
        "unsolvable4_4.txt",
        "unsolvable4_5.txt",
        "unsolvable5_1.txt",
        "unsolvable5_2.txt",
        "unsolvable5_3.txt",
        "unsolvable5_4.txt",
        "unsolvable5_5.txt",
        "unsolvable6_1.txt",
        "unsolvable6_2.txt",
        "unsolvable6_3.txt",
        "unsolvable6_4.txt",
        "unsolvable6_5.txt",
};

class SolvableTests : public ::testing::Test {
public:
    static void CheckIsSolvable(const std::string &filename, bool solvable) {
        std::ifstream is("resources/" + filename);
        Puzzle p = Parser::Parse(is);
        Puzzle tp = Puzzle::GetSnailPuzzle(p.GetSize());
        bool s = Solver::IsSolvable(p, tp);
        std::cout << filename << ": " << s << std::endl;
        ASSERT_EQ(s, solvable);
    }
};

TEST_F(SolvableTests, Solvable) {
    for (const auto &filename : solvable_input_files) {
        CheckIsSolvable(filename, true);
    }
}

TEST_F(SolvableTests, Unsolvable) {
    for (const auto &filename : unsolvable_input_files) {
        CheckIsSolvable(filename, false);
    }
}

class SolveTests : public ::testing::Test {
public:
    static void CheckSolve(
            const std::string &filename,
            Heuristics::Type heuristics_type,
            Algorithm::Type algorithm_type) {
        ASSERT_NO_THROW(
                Parser parser;
                std::ifstream is("resources/" + filename);
                Puzzle p = parser.Parse(is);
                Puzzle tp = Puzzle::GetSnailPuzzle(p.GetSize());
                Solver solver(heuristics_type, algorithm_type);
                auto res = solver.Solve(p, tp);
        );
    }

    static void CheckSolve(const std::string &filename) {
        for (auto h = Heuristics::Type::Hamming;
             h <= Heuristics::Type::LinearConflicts;
             h = static_cast<Heuristics::Type>(static_cast<int>(h) + 1)) {
            for (auto algo = Algorithm::Type::GreedySearch;
                 algo <= Algorithm::Type::AStarSearch;
                 algo = static_cast<Algorithm::Type>(static_cast<int>(h) + 1)) {
                CheckSolve(filename, Heuristics::Type::Hamming, Algorithm::Type::AStarSearch);
            }
        }
    }
};

TEST_F(SolveTests, Puzzle_3_1) {
    CheckSolve(solvable_input_files[0], Heuristics::LinearConflicts, Algorithm::GreedySearch);
}

TEST_F(SolveTests, Puzzle_3_2) {
    CheckSolve(solvable_input_files[1], Heuristics::LinearConflicts, Algorithm::GreedySearch);
}

TEST_F(SolveTests, Puzzle_3_3) {
    CheckSolve(solvable_input_files[2], Heuristics::LinearConflicts, Algorithm::GreedySearch);
}