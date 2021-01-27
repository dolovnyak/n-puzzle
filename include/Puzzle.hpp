#ifndef PUZZLE_HPP_
# define PUZZLE_HPP_

# include <iostream>
# include <vector>
# include "PuzzleCell.hpp"

template<typename TValue>
class Puzzle {
public:
    explicit Puzzle(size_t size) : size_(size), cells_(size * size) {}
    Puzzle() : size_(0) {}
	Puzzle(const Puzzle<TValue>& field);
 
	Puzzle<TValue>& operator=(const Puzzle<TValue>& field);
	bool operator==(const Puzzle<TValue>& field) const;
	
	friend std::ostream &operator<<(std::ostream &os, const Puzzle<TValue> &field) {
        for (size_t row = 0; row < field.GetSize(); ++row) {
            for (size_t column = 0; column < field.GetSize(); ++column) {
                if (column != 0) {
                    os << " ";
                }
                os << const_cast<Puzzle &>(field).At(row, column).value;
            }
            os << std::endl;
        }
        return os;
    }

    [[nodiscard]] size_t GetSize() const;
	[[nodiscard]] size_t GetHash() const;
	[[nodiscard]] size_t GetIndexByValue(TValue value) const;
	[[nodiscard]] TValue GetCellValue(int pos) const;
	[[nodiscard]] PuzzleCell<TValue> &At(int pos);
    [[nodiscard]] PuzzleCell<TValue> &At(int row, int column);

private:
    size_t size_;
    std::vector<PuzzleCell<TValue>> cells_;
};


template<typename TValue>
size_t Puzzle<TValue>::GetSize() const {
    return size_;
}

template<typename TValue>
PuzzleCell<TValue> &Puzzle<TValue>::At(int pos) {
    return cells_[pos];
}

template<typename TValue>
TValue Puzzle<TValue>::GetCellValue(int pos) const
{
	return cells_[pos].value;
}

template<typename TValue>
PuzzleCell<TValue> &Puzzle<TValue>::At(int row, int column) {
    return cells_[row * size_ + column];
}

template<typename TValue>
Puzzle<TValue>::Puzzle(const Puzzle<TValue>& field)
{
	size_ = field.size_;
	cells_ = field.cells_;
}

template<typename TValue>
Puzzle<TValue>& Puzzle<TValue>::operator=(const Puzzle<TValue>& field)
{
	if (this == &field)
		return *this;
	
	size_ = field.size_;
	cells_ = field.cells_;
	
	return *this;
}

template<typename TValue>
bool Puzzle<TValue>::operator==(const Puzzle<TValue>& field) const
{
	for (size_t i = 0; i < cells_.size(); i++)
	{
		if (cells_[i].value != field.cells_[i].value)
			return false;
	}
	
	return true;
}

template<typename TValue>
size_t Puzzle<TValue>::GetHash() const
{
	size_t hash = 0;
	
	for (size_t i = 0; i < cells_.size(); i++)
		hash += (i + 1) * cells_[i].value;
	
	return hash;
}

template<typename TValue>
size_t Puzzle<TValue>::GetIndexByValue(TValue value) const
{
	for (size_t i = 0; i < cells_.size(); i++)
	{
		if (cells_[i].value == value)
			return i;
	}
	throw std::exception(); //TODO handle or remake
}

#endif // PUZZLE_HPP_