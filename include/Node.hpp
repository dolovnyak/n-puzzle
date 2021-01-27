#pragma once

#include "Puzzle.hpp"
#include "Heuristics.hpp"

template<class T>
class Node {
public:
    explicit Node(int heuristic);

    Node(const Puzzle<T> &field,
         const Puzzle<T> &target_field,
         typename Heuristics<T>::HeuristicFunction heuristic_function,
         Node *parent);

    Node(const Puzzle<T> &field,
         const Puzzle<T> &target_field,
         typename Heuristics<T>::HeuristicFunction heuristic_function);

    Node<T> &operator=(const Node<T> &node);

    bool operator==(const Node<T> &node) const;

    bool operator<(const Node<T> &node) const;

    bool operator>(const Node<T> &node) const;

    const Puzzle<T> &GetField() const;

    [[nodiscard]] int GetHeuristic() const;

    [[nodiscard]] int GetDepth() const;

    [[nodiscard]] int GetScore() const;

private:
    Puzzle<T> field_;
    Node *parent_;

    int depth_;
    int heuristic_;
    int score_;
};

template<class T>
Node<T>::Node(const Puzzle<T> &field,
              const Puzzle<T> &target_field,
              typename Heuristics<T>::HeuristicFunction heuristic_function,
              Node *parent)
        :  field_(field),
           parent_(parent),
           depth_(parent_ != nullptr ? parent_->depth_ + 1 : 0),
           heuristic_(heuristic_function(field, target_field)),
           score_(depth_ + heuristic_) {}

template<class T>
Node<T>::Node(const Puzzle<T> &field,
              const Puzzle<T> &target_field,
              typename Heuristics<T>::HeuristicFunction heuristic_function)
        : field_(field),
          parent_(nullptr),
          depth_(0),
          heuristic_(heuristic_function(field, target_field)),
          score_(depth_ + heuristic_) {}

template<class T>
bool Node<T>::operator==(const Node<T> &node) const {
    return field_ == node.field_;
}

template<class T>
const Puzzle<T> &Node<T>::GetField() const {
    return field_;
}

template<class T>
[[nodiscard]] int Node<T>::GetScore() const {
    return score_;
}

template<class T>
[[nodiscard]] int Node<T>::GetHeuristic() const {
    return heuristic_;
}

template<class T>
[[nodiscard]] int Node<T>::GetDepth() const {
    return depth_;
}

template<class T>
bool Node<T>::operator<(const Node<T> &node) const {
    return heuristic_ < node.heuristic_;
}

template<class T>
bool Node<T>::operator>(const Node<T> &node) const {
    return heuristic_ > node.heuristic_;
}

template<class T>
Node<T> &Node<T>::operator=(const Node<T> &node) {
    if (this == &node)
        return *this;

    parent_ = node.parent_;
    heuristic_ = node.heuristic_;
    depth_ = node.depth_;
    score_ = node.score_;
    field_ = node.field_;

    return *this;
}

template<class T>
Node<T>::Node(int heuristic) : heuristic_(heuristic), depth_(0), score_(0) {}

template<class T>
struct HashNodeByField {
public:
    size_t operator()(const Node<T> &node) const {
        return node.GetField().GetHash();
    }
};

template<class T>
std::ostream &operator<<(std::ostream &os, const Node<T> &node) {
    os << node.GetField();
    return os;
}