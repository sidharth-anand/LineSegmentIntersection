#include <iostream>
#include <vector>

#include <math/rational.h>

#include <geometry/point.h>
#include <geometry/linesegment.h>
#include <geometry/intersection.h>

int main()
{

    std::vector<LineSegmentR> lines = {
        LineSegmentR({Rational(-2), Rational(-2)}, {Rational(2), Rational(2)}),
        // LineSegmentR({-1, 1}, {1, -1}),
        // LineSegmentR({-3, 0}, {3, 0}),
        // LineSegmentR({0, 4}, {8, 6}),
        // LineSegmentR({6, 8}, {2, 2})

    };

    auto events = bentleyOttmann(lines);


    for (const auto &event : events)
    {
        std::cout << event.first << ": ";
        for (const auto &line : event.second)

            std::cout << *line << ", ";

        std::cout << "\n";
    }

    return 0;
}