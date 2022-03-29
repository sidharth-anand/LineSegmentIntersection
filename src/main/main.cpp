#include <iostream>
#include <vector>

#include <geometry/point.h>
#include <geometry/linesegment.h>
#include <geometry/intersection.h>

int main()
{
    std::vector<LineSegmentD> lines = {
        LineSegmentD({-2, -2}, {2, 2}),
        LineSegmentD({-1, 1}, {1, -1}),
        LineSegmentD({-3, 0}, {3, 0}),
        LineSegmentD({0, 4}, {8, 6}),
        LineSegmentD({6, 8}, {2, 2})
    };

    auto events = bentleyOttmann(lines);

    for (const auto& event : events)
    {
        std::cout << event.first << ": ";
        for (const auto& line : event.second)
            std::cout << *line << ", ";

        std::cout << "\n";
    }

    return 0;
}