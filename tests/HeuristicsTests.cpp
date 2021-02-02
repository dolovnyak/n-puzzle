#include "gtest/gtest.h"

#include "Heuristics.hpp"
#include "Puzzle.hpp"
#include "Parser.hpp"


class HeuristicsTests : public ::testing::Test {
public:
    static Puzzle CreatePuzzle(const std::string& input) {
        Parser parser;
        std::stringstream iss;
        iss << input;
        return parser.Parse(iss);
    }

    static void TestHeuristics(
            const std::string &input,
            const std::string &target,
            Heuristics::HeuristicsFunction heuristics_function,
            int expected) {
        Puzzle puzzle = HeuristicsTests::CreatePuzzle(input);
        Puzzle target_puzzle = HeuristicsTests::CreatePuzzle(target);

        int heuristics = heuristics_function(puzzle, target_puzzle);
        ASSERT_EQ(heuristics, expected);
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

    TestHeuristics(field, target_field, Heuristics::GetHammingDistance, 1);
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

    TestHeuristics(field, target_field, Heuristics::GetHammingDistance, 2);
}

TEST_F(HeuristicsTests, Hamming3) {
    const std::string field = "3\n"
                              "4 1 3\n"
                              "2 5 7\n"
                              "0 6 8\n";

    const std::string target_field = "3\n"
                                     "1 2 3\n"
                                     "8 0 4\n"
                                     "7 6 5\n";

    TestHeuristics(field, target_field, Heuristics::GetHammingDistance, 6);
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

    TestHeuristics(field, target_field, Heuristics::GetManhattanDistance, 1);
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

    TestHeuristics(field, target_field, Heuristics::GetManhattanDistance, 2);
}

TEST_F(HeuristicsTests, Manhattan3) {
    const std::string field = "3\n"
                              "1 2 5\n"
                              "3 0 6\n"
                              "7 4 8\n";

    const std::string target_field = "3\n"
                                     "1 2 3\n"
                                     "4 5 6\n"
                                     "7 8 0\n";

    TestHeuristics(field, target_field, Heuristics::GetManhattanDistance, 8);
}

TEST_F(HeuristicsTests, LinearConflics1) {
	const std::string field = "3\n"
							  "4 2 5\n"
							  "1 0 6\n"
							  "3 8 7\n";
	
	const std::string target_field = "3\n"
									 "1 2 3\n"
									 "4 5 6\n"
									 "7 8 0\n";
	
	TestHeuristics(field, target_field, Heuristics::GetLinearConflicts, 14);
}

TEST_F(HeuristicsTests, LinearConflics2) {
	// manhattan - 8, linear - (3 4), (4 1), (1 3) (1 2) - 4 * 2
	const std::string field = "4\n"
							  "3  4  1  2\n"
							  "12 13 14 5\n"
							  "11 0  15 6\n"
							  "10 9  8  7\n";
	
	const std::string target_field = "4\n"
									 "1  2  3  4\n"
									 "12 13 14 5\n"
									 "11 0  15 6\n"
									 "10 9  8  7\n";
	
	TestHeuristics(field, target_field, Heuristics::GetLinearConflicts, 16);
}