#include <queue>
#include <vector>

#include "gtest/gtest.h"

TEST(PriorityQueueTests, Test1) {
    std::priority_queue<int, std::vector<int>, std::greater<>> pq;
    pq.push(2);
    pq.push(3);
    pq.push(1);
    ASSERT_EQ(pq.top(), 1);
}