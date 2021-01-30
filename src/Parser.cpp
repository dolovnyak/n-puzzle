#include "Parser.hpp"

const std::map<Parser::State, Parser::ParseStateFunction> Parser::functions_map_ = {
        {Parser::State::BEGIN, Parser::ParseBeginState},
        {Parser::State::SIZE,  Parser::ParseSizeState},
        {Parser::State::FIELD, Parser::ParseFieldState},
};

bool Parser::ParseFieldState(
        std::istream &is,
        [[maybe_unused]] size_t &size,
        [[maybe_unused]] std::vector<int> &cells) {
    if (!is) {
        return true;
    }

    std::string line;
    getline(is, line);

    if (!line.empty() && line[0] != '#') {
        throw ParseException("Unknown symbol.");
    } else {
        // Just ignore line.
        return false;
    }
}

bool Parser::ParseSizeState(std::istream &is, size_t &size,
                            [[maybe_unused]] std::vector<int> &cells) {
    std::string line;
    std::unordered_set<int> valid_cells;
    for (size_t i = 0; i < size * size; ++i) {
        valid_cells.insert(i);
    }

    cells.resize(size * size);
    for (size_t fieldRow = 0; fieldRow < size; ++fieldRow) {
        std::stringstream ss;

        if (!is) {
            throw ParseException("Stream is broken.");
        }

        getline(is, line);
        ss << line;

        if (ss.peek() == -1) {
            throw ParseException("Empty line.");
        } else if (ss.peek() == '#') {
            // Just ignore line.
            --fieldRow;
        } else if (!ss) {
            throw ParseException("Stream is broken.");
        } else {
            int item;
            for (size_t column = 0; column < size; ++column) {
                ss >> item;
                if (!ss) {
                    throw ParseException("Next item expected.");
                } else if (ss && ss.peek() != ' ' && ss.peek() != -1) {
                    throw ParseException("Next item expected.");
                } else if (valid_cells.count(item) == 0) {
                    throw ParseException("Invalid cell.");
                } else {
                    ss.ignore(1);
                    cells[fieldRow * size + column] = item;
                    valid_cells.erase(item);
                }
            }
            if (ss.peek() != -1) {
                char c;
                ss.read(&c, 1);
                while (c == ' ') {
                    ss.read(&c, 1);
                }
                if (!ss || c != '#') {
                    throw ParseException("Unknown symbol.");
                }
            }
        }
    }

    return true;
}

bool Parser::ParseBeginState(std::istream &is, size_t &size,
                             [[maybe_unused]] std::vector<int> &cells) {
    if (!is) {
        throw ParseException("Stream is broken.");
    }

    std::stringstream ss;
    std::string line;

    getline(is, line);
    ss << line;

    if (ss.peek() == -1) {
        throw ParseException("Empty line.");
    } else if (ss.peek() == '#') {
        // Just ignore line.
        return false;
    } else if (!ss) {
        throw ParseException("Stream is broken.");
    } else {
        int s;
        ss >> s;

        if (!ss) {
            throw ParseException("Size expected, but not provided.");
        }

        if (s <= 2) {
            throw ParseException("Size > 2 expected.");
        }

        size = static_cast<size_t>(s);
        return true;
    }
}
