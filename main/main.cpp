#include <iostream>
#include <string>

#include <geometry/point.h>
#include <geometry/linesegment.h>

#include <structures/rbtree.h>

int main()
{
    RBTree<Point<int>, LineSegment<int>> tree = {   {Point<int>(1, 1), LineSegment(Point<int>(1, 1), Point<int>(2, 2))},
                                                    {Point<int>(2, 2), LineSegment(Point<int>(2, 2), Point<int>(3, 3))},
                                                    {Point<int>(3, 3), LineSegment(Point<int>(3, 3), Point<int>(4, 4))}     };
    tree.insert({Point<int>(0, 0), LineSegment(Point<int>(0, 0), Point<int>(1, 1))});

    tree.erase(Point<int>(2, 2));
    tree[Point<int>(2, 2)] = LineSegment(Point<int>(5, 5), Point<int>(3, 3));

    return 0;
}