#include <iostream>
#include <vector>

#include <geometry/point.h>
#include <geometry/linesegment.h>

#include <structures/rbtree.h>

int main()
{
    RBTree<PointD, std::vector<LineSegmentD>> eventQueue;
    RBTree<PointD, LineSegmentD> statusQueue;

    return 0;
}