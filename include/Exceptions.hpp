#pragma once

#include <exception>
#include <utility>

class ParseException : public std::exception {
public:
    ParseException(size_t row, size_t column)
            : row_(row),
              column_(column),
              message_("Parse error at position [" + std::to_string(row_) + "," + std::to_string(column_) + "]") {}

    ParseException(size_t row, size_t column, std::string  message)
            : row_(row),
              column_(column),
              message_(std::move(message)) {}

    [[nodiscard]] const char *what() const noexcept override {
        return message_.c_str();
    }

    [[nodiscard]] size_t GetRow() const {
        return row_;
    }

    [[nodiscard]] size_t GetColumn() const {
        return column_;
    }

private:
    size_t row_;
    size_t column_;
    std::string message_;
};
