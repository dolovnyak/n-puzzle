#ifndef PARSER_HPP_
# define PARSER_HPP_

# include <iostream>
# include <sstream>
# include <string>
# include <map>

# include "Exceptions.hpp"
# include "Puzzle.hpp"

enum FieldParserState {
    BEGIN,
    SIZE,
    FIELD,
    END
};

template<typename TValue>
class Parser {
public:
    Puzzle<TValue> *Parse(std::istream &is) {
        Puzzle<TValue> *field = nullptr;
        for (int row = 0; current_state_ != FieldParserState::END;) {
            const auto &parseStateFunction = functions_map_.find(current_state_);
            if (parseStateFunction != functions_map_.end()) {
                if (ParseStateWrapper(is, row, field, parseStateFunction->second)) {
                    current_state_ = static_cast<FieldParserState>(static_cast<int>(current_state_) + 1);
                }
            } else {
                throw std::logic_error("No mapped parse function for state " + std::to_string(current_state_));
            }
        }

        return field;
    }

    Parser() : current_state_(FieldParserState::BEGIN) {}

private:
    FieldParserState current_state_;

private:
    typedef std::tuple<bool, int> (*ParseStateFunction)(std::istream &, int &, Puzzle<TValue> *&);

    static bool ParseStateWrapper(std::istream &is, int &row, Puzzle<TValue> *&field, ParseStateFunction parse_state_function) {
        const auto&[stateDone, errorColumn] = parse_state_function(is, row, field);
        if (stateDone && errorColumn >= 0) {
            throw ParseException(row, errorColumn);
        }
        return stateDone;
    }

    static std::tuple<bool, int> ParseBeginState(std::istream &is, int &row, Puzzle<TValue> *&field) {
        if (!is) {
            return std::make_tuple(true, 0);
        }

        std::stringstream ss;
        std::string line;

        getline(is, line);
        ss << line;

        if (ss.peek() == -1) {
            return std::make_tuple(true, 0);
        } else if (ss.peek() == '#') {
            // Just ignore line.
            ++row;
            return std::make_tuple(false, -1);
        } else if (ss) {
            int size;
            ss >> size;

            if (!ss) {
                return std::make_tuple(true, std::max(static_cast<int>(ss.tellp()) - 1, 0));
            }

            if (size <= 1) {
                return std::make_tuple(true, std::max(static_cast<int>(ss.tellp()) - static_cast<int>(std::to_string(size).size()), 0));
            }

            field = new Puzzle<TValue>(size);
            ++row;
            return std::make_tuple(true, -1);
        } else {
            return std::make_tuple(true, static_cast<int>(ss.tellp()) - 1);
        }
    }

    static std::tuple<bool, int> ParseSizeState(std::istream &is, int &row, Puzzle<TValue> *&field) {
        std::string line;

        for (size_t fieldRow = 0; fieldRow < field->GetSize(); ++fieldRow) {
            std::stringstream ss;

            if (!is) {
                return std::make_tuple(true, 0);
            }

            getline(is, line);
            ss << line;

            if (ss.peek() == -1) {
                return std::make_tuple(true, 0);
            } else if (ss.peek() == '#') {
                // Just ignore line.
                --fieldRow;
            } else if (ss) {
                TValue item;
                for (size_t column = 0; column < field->GetSize(); ++column) {
                    ss >> item;
                    if (!ss) {
                        return std::make_tuple(true, static_cast<int>(ss.tellp()) + 3);
                    } else if (ss && ss.peek() != ' ' && ss.peek() != -1) {
                        return std::make_tuple(true, static_cast<int>(ss.tellp()) - 1);
                    } else {
                        ss.ignore(1);
                        field->At(fieldRow, column) = PuzzleCell<TValue>(item);
                    }
                }
                if (ss.peek() != -1) {
                    char c;
                    ss.read(&c, 1);
                    while (c == ' ') {
                        ss.read(&c, 1);
                    }
                    if (!ss || c != '#') {
                        return std::make_tuple(true, ss.tellp());
                    }
                }
            } else {
                return std::make_tuple(true, ss.tellp());;
            }

            ++row;
        }

        return std::make_tuple(true, -1);
    }

    static std::tuple<bool, int> ParseFieldState(std::istream &is, int &row, [[maybe_unused]] Puzzle<TValue> *&field) {
        if (!is) {
            return std::make_tuple(true, -1);
        }

        std::string line;
        getline(is, line);

        if (!line.empty() && line[0] != '#') {
            return std::make_tuple(true, 0);
        } else {
            // Just ignore line.
            ++row;
            return std::make_tuple(false, -1);
        }
    }

private:
    static const std::map<FieldParserState, Parser<TValue>::ParseStateFunction> functions_map_;
};

template<typename TValue>
const std::map<FieldParserState, typename Parser<TValue>::ParseStateFunction> Parser<TValue>::functions_map_ = {
        {FieldParserState::BEGIN, Parser<TValue>::ParseBeginState},
        {FieldParserState::SIZE,  Parser<TValue>::ParseSizeState},
        {FieldParserState::FIELD, Parser<TValue>::ParseFieldState},
};

#endif // PARSER_HPP_