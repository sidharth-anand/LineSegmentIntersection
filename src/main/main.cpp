#include <iostream>
#include <vector>

#include <geometry/point.h>
#include <geometry/linesegment.h>
#include <geometry/intersection.h>

#include <structures/rbtree.h>

int main()
{
    RBTree<PointD, std::vector<LineSegmentD>> eventQueue;
    RBTree<PointD, LineSegmentD> statusQueue;

    std::vector<LineSegmentD> lines = {
        LineSegmentD({-1, -1}, {1, 1}),
        LineSegmentD({-1, 1}, {1, -1}),
    };
    auto events = bentley_ottoman(lines);

    for (auto event : events)
        std::cout << event.first.getX() << " " << event.first.getY() << "\n";

    return 0;
}