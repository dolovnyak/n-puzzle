#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_set>

#include "Exceptions.hpp"
#include "Puzzle.hpp"

class Parser {
public:
    Puzzle *Parse(std::istream &is) {
        State current_state = State::BEGIN;

        size_t size;
        std::vector<int> cells;
        while (current_state != State::END) {
            const auto &parseStateFunction = functions_map_.find(current_state);
            if (parseStateFunction != functions_map_.end()) {
                if (parseStateFunction->second(is, size, cells))
                    current_state = static_cast<State>(static_cast<int>(current_state) + 1);
            } else {
                throw std::logic_error("No mapped parse function for state " + std::to_string(current_state));
            }
        }

        return new Puzzle(size, cells);
    }

    Parser() = default;

private:
    enum State {
        BEGIN,
        SIZE,
        FIELD,
        END
    };

private:
    typedef bool (*ParseStateFunction)(std::istream &, size_t &, std::vector<int> &);

    static bool ParseBeginState(std::istream &is, size_t &size, std::vector<int> &puzzle);
    static bool ParseSizeState(std::istream &is, size_t &size, std::vector<int> &puzzle);
    static bool ParseFieldState(std::istream &is, size_t &size, std::vector<int> &puzzle);

private:
    static const std::map<State, Parser::ParseStateFunction> functions_map_;
};