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