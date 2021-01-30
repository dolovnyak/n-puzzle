#pragma once

#include <exception>
#include <utility>

class ParseException : public std::exception {
public:
    explicit ParseException(std::string message)
            : message_(std::move(message)) {}

    [[nodiscard]] const char *what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};
