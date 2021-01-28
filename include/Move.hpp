#pragma once

#include "Puzzle.hpp"

class IMove {
public:
    [[nodiscard]] virtual Puzzle *Execute(const Puzzle &puzzle) const = 0;
};

class MoveLeft : public IMove {
public:
    [[nodiscard]] Puzzle *Execute(const Puzzle &puzzle) const override;
};

class MoveRight : public IMove {
public:
    [[nodiscard]] Puzzle *Execute(const Puzzle &puzzle) const override;
};

class MoveDown : public IMove {
public:
    [[nodiscard]] Puzzle *Execute(const Puzzle &puzzle) const override;
};

class MoveUp : public IMove {
public:
    [[nodiscard]] Puzzle *Execute(const Puzzle &puzzle) const override;
};