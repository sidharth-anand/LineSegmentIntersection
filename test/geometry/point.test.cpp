#include <gtest/gtest.h>

#include <geometry/point.h>

TEST(Point, DefaultConstructor)
{
    PointI p;
    EXPECT_EQ(p.getX(), 0);
    EXPECT_EQ(p.getY(), 0);
}

TEST(Point, Constructor)
{
    PointI p(1, 2);
    EXPECT_EQ(p.getX(), 1);
    EXPECT_EQ(p.getY(), 2);
}

TEST(Point, MoveConstructor)
{
    PointI p1(1, 2);
    PointI p2(std::move(p1));
    EXPECT_EQ(p2.getX(), 1);
    EXPECT_EQ(p2.getY(), 2);
}

TEST(Point, CopyConstructor)
{
    PointI p1(1, 2);
    PointI p2(p1);
    EXPECT_EQ(p2.getX(), 1);
    EXPECT_EQ(p2.getY(), 2);
}

TEST(Point, PairConstructor)
{
    PointI p(1, 2);
    EXPECT_EQ(p.getX(), 1);
    EXPECT_EQ(p.getY(), 2);
}

TEST(Point, GetX)
{
    PointI p(1, 2);
    EXPECT_EQ(p.getX(), 1);
}

TEST(Point, GetY)
{
    PointI p(1, 2);
    EXPECT_EQ(p.getY(), 2);
}

TEST(Point, SetX)
{
    PointI p(1, 2);
    p.setX(3);
    EXPECT_EQ(p.getX(), 3);
}

TEST(Point, SetY)
{
    PointI p(1, 2);
    p.setY(3);
    EXPECT_EQ(p.getY(), 3);
}

TEST(Point, GetCoordinates)
{
    PointI p(1, 2);
    EXPECT_EQ(p.getCoordinates(), std::make_pair(1, 2));
}

TEST(Point, AssignmentOperator)
{
    PointI p1(1, 2);
    PointI p2;
    p2 = p1;
    EXPECT_EQ(p2.getX(), 1);
    EXPECT_EQ(p2.getY(), 2);
}

TEST(Point, MoveAssignmentOperator)
{
    PointI p1(1, 2);
    PointI p2;
    p2 = std::move(p1);
    EXPECT_EQ(p2.getX(), 1);
    EXPECT_EQ(p2.getY(), 2);
}

TEST(Point, CopyAssignmentOperator)
{
    PointI p1(1, 2);
    PointI p2;
    p2 = p1;
    EXPECT_EQ(p2.getX(), 1);
    EXPECT_EQ(p2.getY(), 2);
}


TEST(Point, PointAddition)
{
    PointI p1(1, 2);
    PointI p2(3, 4);

    PointI p3 = p1 + p2;

    EXPECT_EQ(p3.getX(), 4);
    EXPECT_EQ(p3.getY(), 6);
}

TEST(Point, PointSubtraction)
{
    PointI p1(1, 2);
    PointI p2(3, 4);

    PointI p3 = p1 - p2;

    EXPECT_EQ(p3.getX(), -2);
    EXPECT_EQ(p3.getY(), -2);
}

TEST(Point, PointScalarMultiplication)
{
    PointI p1(1, 2);
    int scalar = 3;
    PointI p2 = p1 * scalar;

    EXPECT_EQ(p2.getX(), 3);
    EXPECT_EQ(p2.getY(), 6);
}

TEST(Point, PointScalarDivision)
{
    PointI p1(1, 2);
    int scalar = 3;
    PointI p2 = p1 / scalar;

    EXPECT_EQ(p2.getX(), 1 / 3);
    EXPECT_EQ(p2.getY(), 2 / 3);
}

TEST(Point, PointEquality)
{
    PointI p1(1, 2);
    PointI p2(1, 2);

    EXPECT_EQ(p1, p2);
}

TEST(Point, PointInequality)
{
    PointI p1(1, 2);
    PointI p2(2, 2);

    EXPECT_NE(p1, p2);
}

TEST(Point, PointLessThan)
{
    PointI p1(1, 2);
    PointI p2(2, 2);

    EXPECT_LT(p1, p2);
}

TEST(Point, PointGreaterThan)
{
    PointI p1(1, 2);
    PointI p2(2, 2);

    EXPECT_GT(p2, p1);
}

TEST(Point, LessThanOrEqualTo)
{
    PointI p1(1, 2);
    PointI p2(2, 2);
    PointI p3(1, 2);

    EXPECT_LE(p1, p2);
    EXPECT_LE(p1, p3);
}

TEST(Point, GreaterThanOrEqualTo)
{
    PointI p1(1, 2);
    PointI p2(2, 2);
    PointI p3(1, 2);

    EXPECT_GE(p2, p1);
    EXPECT_GE(p3, p1);
}

TEST(Point, PointAssignment)
{
    PointI p1(1, 2);
    PointI p2(3, 4);

    p1 = p2;

    EXPECT_EQ(p1, p2);
}

TEST(Point, PointEqualityOperator)
{
    PointI p1(1, 2);
    PointI p2(1, 2);

    EXPECT_TRUE(p1 == p2);
}

TEST(Point, PointInequalityOperator)
{
    PointI p1(1, 2);
    PointI p2(2, 2);

    EXPECT_TRUE(p1 != p2);
}

TEST(Point, PointLessThanOperator)
{
    PointI p1(1, 2);
    PointI p2(2, 2);

    EXPECT_TRUE(p1 < p2);
}

TEST(Point, PointGreaterThanOperator)
{
    PointI p1(1, 2);
    PointI p2(2, 2);

    EXPECT_TRUE(p2 > p1);
}

TEST(Point, LessThanOrEqualToOperator)
{
    PointI p1(1, 2);
    PointI p2(2, 2);
    PointI p3(1, 2);

    EXPECT_TRUE(p1 <= p2);
    EXPECT_TRUE(p1 <= p3);
}

TEST(Point, GreaterThanOrEqualToOperator)
{
    PointI p1(1, 2);
    PointI p2(2, 2);
    PointI p3(1, 2);

    EXPECT_TRUE(p2 >= p1);
    EXPECT_TRUE(p3 >= p1);
}
