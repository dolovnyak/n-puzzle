#include <queue>
#include <vector>

#include "gtest/gtest.h"

#include "Node.hpp"

TEST(PriorityQueueTests, TestInt) {
    std::priority_queue<int, std::vector<int>, std::greater<>> pq;
    pq.push(2);
    pq.push(3);
    pq.push(1);
    pq.push(4);
    ASSERT_EQ(pq.top(), 1);
}

//TEST(PriorityQueueTests, TestNode) {
//    std::priority_queue<Node, std::vector<Node<int>>, std::greater<>> pq;
//    pq.push(Node<int>(2));
//    pq.push(Node<int>(3));
//    pq.push(Node<int>(1));
//    pq.push(Node<int>(4));
//    ASSERT_EQ(pq.top().GetHeuristic(), 1);
//}