#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <geometry/intersection.h>

#include <geometry/linesegment.h>

using ::testing::UnorderedElementsAreArray;

std::vector<PointR> getIntersectionsBrute(const std::vector<LineSegmentR> &lines)
{
	std::vector<PointR> intersections;

	for (size_t i = 0; i < lines.size(); ++i)
	{
		for (size_t j = i + 1; j < lines.size(); ++j)
		{
			std::optional<PointR> intersection = lines[i].intersects(lines[j]);
			if (intersection)
				intersections.push_back(intersection.value());
		}
	}

	return intersections;
}

TEST(bentleyOttmann, TestDegenerateColinear01)
{
	std::vector<LineSegmentR> lines = {
		LineSegmentR({Rational(-9, 10), Rational(9, 10)}, {Rational(1, 1), Rational(-1, 1)}),
		LineSegmentR({Rational(-1, 1), Rational(1, 1)}, {Rational(9, 10), Rational(-9, 10)}),
		LineSegmentR({Rational(-9, 10), Rational(4, 5)}, {Rational(9, 10), Rational(-1, 1)}),
		LineSegmentR({Rational(-1, 1), Rational(9, 10)}, {Rational(4, 5), Rational(-9, 10)}),
		LineSegmentR({Rational(-9, 10), Rational(7, 10)}, {Rational(4, 5), Rational(-1, 1)}),
		LineSegmentR({Rational(-1, 1), Rational(4, 5)}, {Rational(7, 10), Rational(-9, 10)}),
		LineSegmentR({Rational(-9, 10), Rational(3, 5)}, {Rational(7, 10), Rational(-1, 1)}),
		LineSegmentR({Rational(-1, 1), Rational(7, 10)}, {Rational(3, 5), Rational(-9, 10)}),
		LineSegmentR({Rational(9, 10), Rational(-4, 5)}, {Rational(-9, 10), Rational(1, 1)}),
		LineSegmentR({Rational(1, 1), Rational(-9, 10)}, {Rational(-4, 5), Rational(9, 10)}),
		LineSegmentR({Rational(9, 10), Rational(-7, 10)}, {Rational(-4, 5), Rational(1, 1)}),
		LineSegmentR({Rational(1, 1), Rational(-4, 5)}, {Rational(-7, 10), Rational(9, 10)}),
		LineSegmentR({Rational(9, 10), Rational(-3, 5)}, {Rational(-7, 10), Rational(1, 1)}),
		LineSegmentR({Rational(1, 1), Rational(-7, 10)}, {Rational(-3, 5), Rational(9, 10)}),
		LineSegmentR({Rational(3, 10), Rational(3, 10)}, {Rational(1, 1), Rational(1, 1)}),
		LineSegmentR({Rational(1, 5), Rational(1, 5)}, {Rational(9, 10), Rational(9, 10)}),
		LineSegmentR({Rational(2, 5), Rational(3, 10)}, {Rational(1, 1), Rational(9, 10)}),
		LineSegmentR({Rational(3, 10), Rational(1, 5)}, {Rational(9, 10), Rational(4, 5)}),
		LineSegmentR({Rational(1, 2), Rational(3, 10)}, {Rational(1, 1), Rational(4, 5)}),
		LineSegmentR({Rational(2, 5), Rational(1, 5)}, {Rational(9, 10), Rational(7, 10)}),
		LineSegmentR({Rational(3, 5), Rational(3, 10)}, {Rational(1, 1), Rational(7, 10)}),
		LineSegmentR({Rational(1, 2), Rational(1, 5)}, {Rational(9, 10), Rational(3, 5)}),
		LineSegmentR({Rational(4, 5), Rational(9, 10)}, {Rational(1, 5), Rational(3, 10)}),
		LineSegmentR({Rational(9, 10), Rational(1, 1)}, {Rational(3, 10), Rational(2, 5)}),
		LineSegmentR({Rational(7, 10), Rational(9, 10)}, {Rational(1, 5), Rational(2, 5)}),
		LineSegmentR({Rational(4, 5), Rational(1, 1)}, {Rational(3, 10), Rational(1, 2)}),
		LineSegmentR({Rational(3, 5), Rational(9, 10)}, {Rational(1, 5), Rational(1, 2)}),
		LineSegmentR({Rational(7, 10), Rational(1, 1)}, {Rational(3, 10), Rational(3, 5)}),
		LineSegmentR({Rational(-9, 10), Rational(-9, 10)}, {Rational(-1, 5), Rational(-1, 5)}),
		LineSegmentR({Rational(-1, 1), Rational(-1, 1)}, {Rational(-3, 10), Rational(-3, 10)}),
		LineSegmentR({Rational(-4, 5), Rational(-9, 10)}, {Rational(-1, 5), Rational(-3, 10)}),
		LineSegmentR({Rational(-9, 10), Rational(-1, 1)}, {Rational(-3, 10), Rational(-2, 5)}),
		LineSegmentR({Rational(-7, 10), Rational(-9, 10)}, {Rational(-1, 5), Rational(-2, 5)}),
		LineSegmentR({Rational(-4, 5), Rational(-1, 1)}, {Rational(-3, 10), Rational(-1, 2)}),
		LineSegmentR({Rational(-3, 5), Rational(-9, 10)}, {Rational(-1, 5), Rational(-1, 2)}),
		LineSegmentR({Rational(-7, 10), Rational(-1, 1)}, {Rational(-3, 10), Rational(-3, 5)}),
		LineSegmentR({Rational(-2, 5), Rational(-3, 10)}, {Rational(-1, 1), Rational(-9, 10)}),
		LineSegmentR({Rational(-3, 10), Rational(-1, 5)}, {Rational(-9, 10), Rational(-4, 5)}),
		LineSegmentR({Rational(-1, 2), Rational(-3, 10)}, {Rational(-1, 1), Rational(-4, 5)}),
		LineSegmentR({Rational(-2, 5), Rational(-1, 5)}, {Rational(-9, 10), Rational(-7, 10)}),
		LineSegmentR({Rational(-3, 5), Rational(-3, 10)}, {Rational(-1, 1), Rational(-7, 10)}),
		LineSegmentR({Rational(-1, 2), Rational(-1, 5)}, {Rational(-9, 10), Rational(-3, 5)}),
	};
	std::vector<PointR> intersections = getIntersectionsBrute(lines);
	auto events = bentleyOttmann(lines);
	std::vector<PointR> results;
	for (const auto &event : events)
		results.push_back(event.first);
	EXPECT_THAT(results, UnorderedElementsAreArray(intersections));
}
