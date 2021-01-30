#include "gtest/gtest.h"

#include <fstream>

#include "Puzzle.hpp"
#include "Parser.hpp"
#include "Solver.hpp"


class SolvableTests : public ::testing::Test {
public:
    const static std::vector<std::string> solvable_input_files;
    const static std::vector<std::string> unsolvable_input_files;

    static void CheckIsSolvable(const std::string &filename, bool solvable) {
        Parser parser;
        std::ifstream is("../../resources/fields/" + filename);
        Puzzle *p = parser.Parse(is);
        Puzzle tp = Puzzle::GetSnailPuzzle(p->GetSize());
        bool s = Solver::IsSolvable(*p, tp);
        std::cout << filename << ": " << s << std::endl;
        ASSERT_EQ(s, solvable);
        delete p;
    }
};

const std::vector<std::string> SolvableTests::solvable_input_files = {
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

const std::vector<std::string> SolvableTests::unsolvable_input_files = {
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

//void SolvableCheckerTestWrapper(const std::string &input, bool expectedResult) {
//    std::stringstream iss;
//    iss << input;
//
//    Parser field_parser;
//    Puzzle *field = field_parser.Parse(iss);
//    Solver solver(Heuristics::Type::Hamming, OpenSetComparator::AStarSearch);
//    ASSERT_EQ(solver.IsSolvable(*field, Puzzle::GetSnailPuzzle(field->GetSize())), expectedResult);
//    delete field;
//}

//TEST(SolverTests, Solvable) {
//
////    SolvableCheckerTestWrapper(input, true);
//}
//
//TEST(SolverTests, Solvable2) {
//    const std::string input = "4\n"
//                              "1 2 3 4\n"
//                              "12 13 14 5\n"
//                              "11 0 15 6\n"
//                              "10 9 8 7\n";
//
//    SolvableCheckerTestWrapper(input, true);
//}
//
//TEST(SolverTests, Solvable3) {
//    const std::string input = "4\n"
//                              "6 13 7 10\n"
//                              "8 9 11 0\n"
//                              "15 2 12 5\n"
//                              "14 3 1 4\n";
//
//    SolvableCheckerTestWrapper(input, true);
//}
//
//TEST(SolverTests, NotSolvable1) {
//    const std::string input = "3\n"
//                              "1 2 3\n"
//                              "7 8 4\n"
//                              "0 6 5\n";
//
//    SolvableCheckerTestWrapper(input, true);
//}
//
//TEST(SolverTests, NotSolvable2) {
//    const std::string input = "4\n"
//                              "1 2 3 4\n"
//                              "12 13 14 5\n"
//                              "11 0 15 6\n"
//                              "10 9 8 7\n";
//
//    SolvableCheckerTestWrapper(input, true);
//}
//
//TEST(SolverTests, NotSolvable3) {
//    const std::string input = "4\n"
//                              "6 13 7 10\n"
//                              "8 9 11 0\n"
//                              "15 2 12 5\n"
//                              "14 3 1 4\n";
//
//    SolvableCheckerTestWrapper(input, true);
//}