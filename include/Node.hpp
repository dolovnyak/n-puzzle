#ifndef NODE_HPP
#define NODE_HPP

#include "Puzzle.hpp"
#include "Heuristics.hpp"

template<typename T>
class Node
{
public:
	Node(const Puzzle<T>& field, const Puzzle<T>& finishField, Node* parent);
	
	Node<T>& operator=(const Node<T>& node);
	
	bool operator==(const Node<T>& node) const;
	bool operator<(const Node<T>& node) const;
	
	const Puzzle<T>& GetField() const;
	const T& GetScore() const;
	
private:
	Node* parent_;
	T heuristic_;
	T depth_;
	T score_;
	Puzzle<T> field_;
};

template<typename T>
Node<T>::Node(const Puzzle<T>& field, const Puzzle<T>& finishField, Node* parent) : field_(field), parent_(parent)
{
	if (parent_ == nullptr)
		depth_ = 0;
	else
		depth_ = parent->depth_ + 1;
	
	heuristic_ = find_hamming_distance_heuristic(field_, finishField);
	score_ = depth_ + heuristic_;
}

template<typename T>
bool Node<T>::operator==(const Node<T>& node) const
{
	return field_ == node.field_;
}

template<typename T>
const Puzzle<T>& Node<T>::GetField() const
{
	return field_;
}

template<typename T>
const T& Node<T>::GetScore() const
{
}

template<typename T>
bool Node<T>::operator<(const Node<T>& node) const
{
	return heuristic_ < node.heuristic_;
}

template<typename T>
Node<T>& Node<T>::operator=(const Node<T>& node)
{
	if (this == &node)
		return *this;
	
	parent_ = node.parent_;
	heuristic_ = node.heuristic_;
	depth_ = node.depth_;
	score_ = node.score_;
	field_ = node.field_;
	
	return *this;
}

template<typename T>
struct HashNodeByField
{
public:
	size_t operator()(const Node<T>& node) const
	{
		return node.GetField().GetHash();
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Node<T>& node)
{
	os << node.GetField();
	return os;
}

#endif
