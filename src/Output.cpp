#include <sstream>

#include "Output.hpp"

void Output::VisualizeParseException(std::istream &is, const ParseException &ex) noexcept {
    // Print exception message with position of invalid field part.
    std::cout << ex.what() << std::endl;

    std::string line;
    size_t row;
    for (row = 0; getline(is, line); ++row) {
        std::stringstream ss;
        ss << line;

        size_t column;
        for (column = 0; ss.peek() != -1; ++column) {
            // Read stream by char.
            char s;
            ss.read(&s, 1);

            // If found exact invalid position - print next word highlighted.
            // Otherwise just print next char.
            if (row == ex.GetRow() && column == ex.GetColumn()) {
                std::cout << BACKGROUND_RED << FOREGROUND_WHITE;
                std::cout << s;
                while (ss.peek() != -1 && ss.peek() != ' ') {
                    ss >> s;
                    std::cout << s;
                }
                std::cout << RESET;
            } else {
                std::cout << s;
            }
        }

        // If invalid column is greater, than last column, but row is exact
        // same, print whitespaces until reach target column and then print
        // single highlighted whitespace.
        if (row == ex.GetRow()) {
            while (column < ex.GetColumn()) {
                ++column;
                std::cout << " ";
            }
            if (column == ex.GetColumn()) {
                std::cout << BACKGROUND_RED << FOREGROUND_WHITE;
                std::cout << " ";
                std::cout << RESET;
            }
        }

        std::cout << std::endl;
    }

    // If invalid row is greater, than last row, print newlines until reach
    // target row and then print single highlighted whitespace.
    while (row < ex.GetRow()) {
        ++row;
        std::cout << std::endl;
    }
    if (row == ex.GetRow()) {
        std::cout << BACKGROUND_RED << FOREGROUND_WHITE;
        std::cout << " ";
        std::cout << RESET;
        std::cout << std::endl;
    }
}