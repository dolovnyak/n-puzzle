#pragma once

#include <iostream>
#include <vector>

template<class T>
class Puzzle {
public:
    explicit Puzzle(size_t size) : size_(size), cells_(size * size) {}

    Puzzle() : size_(0) {}

    Puzzle(const Puzzle<T> &field);

    Puzzle<T> &operator=(const Puzzle<T> &field);

    bool operator==(const Puzzle<T> &field) const;

    friend std::ostream &operator<<(std::ostream &os, const Puzzle<T> &field) {
        for (size_t row = 0; row < field.GetSize(); ++row) {
            for (size_t column = 0; column < field.GetSize(); ++column) {
                if (column != 0) {
                    os << " ";
                }
                os << const_cast<Puzzle &>(field).At(row, column);
            }
            os << std::endl;
        }
        return os;
    }

    [[nodiscard]] size_t GetSize() const;

    [[nodiscard]] size_t GetHash() const;

    [[nodiscard]] int GetIndexByValue(T value) const;
    
	void GetIndexByValue(T value, int *row, int *column) const;

    [[nodiscard]] T &At(int pos);

    [[nodiscard]] T &At(int row, int column);

private:
    size_t size_;
    std::vector<T> cells_;
};

template<class T>
size_t Puzzle<T>::GetSize() const {
    return size_;
}

template<class T>
T &Puzzle<T>::At(int pos) {
    return cells_[pos];
}

template<class T>
T &Puzzle<T>::At(int row, int column) {
    return cells_[row * size_ + column];
}

template<class T>
Puzzle<T>::Puzzle(const Puzzle<T> &field) {
    size_ = field.size_;
    cells_ = field.cells_;
}

template<class T>
Puzzle<T> &Puzzle<T>::operator=(const Puzzle<T> &field) {
    if (this == &field)
        return *this;

    size_ = field.size_;
    cells_ = field.cells_;

    return *this;
}

template<class T>
bool Puzzle<T>::operator==(const Puzzle<T> &field) const {
    for (size_t i = 0; i < cells_.size(); i++) {
        if (cells_[i] != field.cells_[i])
            return false;
    }

    return true;
}

template<class T>
size_t Puzzle<T>::GetHash() const {
    size_t hash = 0;

    for (size_t i = 0; i < cells_.size(); i++)
        hash += (i + 1) * cells_[i];

    return hash;
}

template<class T>
int Puzzle<T>::GetIndexByValue(T value) const {
    for (size_t i = 0; i < cells_.size(); i++) {
        if (cells_[i] == value)
            return i;
    }
    throw std::exception(); //TODO handle or remake
}

template<class T>
void Puzzle<T>::GetIndexByValue(T value, int *row, int *column) const {
	for (size_t i = 0; i < size_; i++) {
		for (size_t j = 0; j < size_; j++) {
			if (cells_[i * size_ + j] == value) {
				*row = i;
				*column = j;
				return;
			}
		}
	}
	throw std::exception(); //TODO handle or remake
}
