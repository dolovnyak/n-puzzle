#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_set>

#include "Exceptions.hpp"
#include "Puzzle.hpp"

enum FieldParserState {
    BEGIN,
    SIZE,
    FIELD,
    END
};

template<class T>
class Parser {
public:
    Puzzle<T> *Parse(std::istream &is) {
        Puzzle<T> *field = nullptr;
        for (int row = 0; current_state_ != FieldParserState::END;) {
            const auto &parseStateFunction = functions_map_.find(current_state_);
            if (parseStateFunction != functions_map_.end()) {
                if (parseStateFunction->second(is, row, field))
                    current_state_ = static_cast<FieldParserState>(static_cast<int>(current_state_) + 1);
            } else {
                throw std::logic_error("No mapped parse function for state " + std::to_string(current_state_));
            }
        }

        return field;
    }

    Parser() = default;

private:
    FieldParserState current_state_ = FieldParserState::BEGIN;

private:
    typedef bool (*ParseStateFunction)(std::istream &, int &, Puzzle<T> *&);

    static bool ParseBeginState(std::istream &is, int &row, Puzzle<T> *&field) {
        if (!is) {
            throw ParseException(row, 0, "Stream is broken.");
        }

        std::stringstream ss;
        std::string line;

        getline(is, line);
        ss << line;

        if (ss.peek() == -1) {
            throw ParseException(row, 0, "Empty line.");
        } else if (ss.peek() == '#') {
            // Just ignore line.
            ++row;
            return false;
        } else if (ss) {
            int size;
            ss >> size;

            if (!ss) {
                throw ParseException(row, std::max(static_cast<int>(ss.tellp()) - 1, 0), "Size expected, but not provided.");
            }

            if (size <= 2) {
                throw ParseException(row, std::max(static_cast<int>(ss.tellp()) - static_cast<int>(std::to_string(size).size()), 0), "Size > 2 expected.");
            }

            field = new Puzzle<T>(size);
            ++row;
            return true;
        } else {
            throw ParseException(row, static_cast<int>(ss.tellp()) - 1, "Size > 2 expected.");
        }
    }

    static bool ParseSizeState(std::istream &is, int &row, Puzzle<T> *&field) {
        std::string line;
        std::unordered_set<T> valid_cells;
        for (T i = 0; static_cast<size_t>(i) < field->GetSize() * field->GetSize(); ++i) {
            valid_cells.insert(i);
        }

        for (size_t fieldRow = 0; fieldRow < field->GetSize(); ++fieldRow) {
            std::stringstream ss;

            if (!is) {
                throw ParseException(row, 0, "Stream is broken.");
            }

            getline(is, line);
            ss << line;

            if (ss.peek() == -1) {
                throw ParseException(row, 0, "Empty line.");
            } else if (ss.peek() == '#') {
                // Just ignore line.
                --fieldRow;
            } else if (ss) {
                T item;
                for (size_t column = 0; column < field->GetSize(); ++column) {
                    ss >> item;
                    if (!ss) {
                        throw ParseException(row, static_cast<int>(ss.tellp()) + 3, "Next item expected.");
                    } else if (ss && ss.peek() != ' ' && ss.peek() != -1) {
                        throw ParseException(row, std::max(static_cast<int>(ss.tellp()) - 1, 0), "Next item expected.");
                    } else if (valid_cells.count(item) == 0) {
                        throw ParseException(row, std::max(static_cast<int>(ss.tellp()) - 1, 0), "Invalid cell.");
                    } else {
                        ss.ignore(1);
                        field->At(fieldRow, column) = item;
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
                        throw ParseException(row, ss.tellp(), "Unknown symbol.");
                    }
                }
            } else {
                throw ParseException(row, ss.tellp());
            }

            ++row;
        }

        return true;
    }

    static bool ParseFieldState(std::istream &is, int &row, [[maybe_unused]] Puzzle<T> *&field) {
        if (!is) {
            return true;
        }

        std::string line;
        getline(is, line);

        if (!line.empty() && line[0] != '#') {
            throw ParseException(row, 0, "Unknown symbol.");
        } else {
            // Just ignore line.
            ++row;
            return false;
        }
    }

private:
    static const std::map<FieldParserState, Parser<T>::ParseStateFunction> functions_map_;
};

template<class T>
const std::map<FieldParserState, typename Parser<T>::ParseStateFunction> Parser<T>::functions_map_ = {
        {FieldParserState::BEGIN, Parser<T>::ParseBeginState},
        {FieldParserState::SIZE,  Parser<T>::ParseSizeState},
        {FieldParserState::FIELD, Parser<T>::ParseFieldState},
};