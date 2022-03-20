#include <gtest/gtest.h>

#include <geometry/point.h>

TEST(Point, PointAddition) {
    PointI p1(1, 2);
    PointI p2(3, 4);

    PointI p3 = p1 + p2;

    EXPECT_EQ(p3.getX(), 4);
    EXPECT_EQ(p3.getY(), 6);
}