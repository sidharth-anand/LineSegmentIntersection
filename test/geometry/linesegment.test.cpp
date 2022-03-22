#include <gtest/gtest.h>

#include <geometry/linesegment.h>
#include <geometry/point.h>
TEST(LineSegment, DefaultConstructor)
{
    LineSegmentI ls;
    EXPECT_EQ(ls.getStart(), PointI());
    EXPECT_EQ(ls.getEnd(), PointI());
}
TEST(LineSegment, Constructor)
{
    LineSegmentI ls(PointI(1, 2), PointI(3, 4));
    EXPECT_EQ(ls.getStart(), PointI(1, 2));
    EXPECT_EQ(ls.getEnd(), PointI(3, 4));
}
TEST(LineSegment, MoveConstructor)
{
    LineSegmentI ls(PointI(1, 2), PointI(3, 4));
    LineSegmentI ls2(std::move(ls));
    EXPECT_EQ(ls2.getStart(), PointI(1, 2));
    EXPECT_EQ(ls2.getEnd(), PointI(3, 4));
}
TEST(LineSegment, CopyConstructor)
{
    LineSegmentI ls(PointI(1, 2), PointI(3, 4));
    LineSegmentI ls2(ls);
    EXPECT_EQ(ls2.getStart(), PointI(1, 2));
    EXPECT_EQ(ls2.getEnd(), PointI(3, 4));
}
TEST(LineSegment, PairConstructor)
{
    LineSegmentI ls(PointI(1, 2), PointI(3, 4));
    EXPECT_EQ(ls.getStart(), PointI(1, 2));
    EXPECT_EQ(ls.getEnd(), PointI(3, 4));
}
TEST(LineSegment, GetStart)
{
    LineSegmentI ls(PointI(1, 2), PointI(3, 4));
    EXPECT_EQ(ls.getStart(), PointI(1, 2));
}
TEST(LineSegment, GetEnd)
{
    LineSegmentI ls(PointI(1, 2), PointI(3, 4));
    EXPECT_EQ(ls.getEnd(), PointI(3, 4));
}
TEST(LineSegment, SetStart)
{
    LineSegmentI ls(PointI(1, 2), PointI(3, 4));
    ls.setStart(PointI(5, 6));
    EXPECT_EQ(ls.getStart(), PointI(5, 6));
}
TEST(LineSegment, SetEnd)
{
    LineSegmentI ls(PointI(1, 2), PointI(3, 4));
    ls.setEnd(PointI(5, 6));
    EXPECT_EQ(ls.getEnd(), PointI(5, 6));
}
TEST(LineSegment, GetPoints)
{
    LineSegmentI ls(PointI(1, 2), PointI(3, 4));
    std::pair<PointI, PointI> points = ls.getPoints();
    EXPECT_EQ(points.first, PointI(1, 2));
    EXPECT_EQ(points.second, PointI(3, 4));
}
TEST(LineSegment, AssignmentOperator)
{
    LineSegmentI ls(PointI(1, 2), PointI(3, 4));
    LineSegmentI ls2;
    ls2 = ls;
    EXPECT_EQ(ls2.getStart(), PointI(1, 2));
    EXPECT_EQ(ls2.getEnd(), PointI(3, 4));
}
TEST(LineSegment, MoveAssignmentOperator)
{
    LineSegmentI ls(PointI(1, 2), PointI(3, 4));
    LineSegmentI ls2;
    ls2 = std::move(ls);
    EXPECT_EQ(ls2.getStart(), PointI(1, 2));
    EXPECT_EQ(ls2.getEnd(), PointI(3, 4));
}
TEST(LineSegment, CopyAssignmentOperator)
{
    LineSegmentI ls(PointI(1, 2), PointI(3, 4));
    LineSegmentI ls2;
    ls2 = ls;
    EXPECT_EQ(ls2.getStart(), PointI(1, 2));
    EXPECT_EQ(ls2.getEnd(), PointI(3, 4));
}
TEST(LineSegment, EqualityOperator)
{
    LineSegmentI ls(PointI(1, 2), PointI(3, 4));
    LineSegmentI ls2(PointI(1, 2), PointI(3, 4));
    EXPECT_TRUE(ls == ls2);
}
TEST(LineSegment, InequalityOperator)
{
    LineSegmentI ls(PointI(1, 2), PointI(3, 4));
    LineSegmentI ls2(PointI(1, 2), PointI(3, 5));
    EXPECT_TRUE(ls != ls2);
}
