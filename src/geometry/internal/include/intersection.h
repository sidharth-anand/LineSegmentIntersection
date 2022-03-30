#pragma once

#include <functional>
#include <vector>

#include <internal/include/point.h>
#include <internal/include/linesegment.h>

#include <structures/rbtree.h>

//TODO: Use smart pointers instead of LineSegmentD*
//TODO: Clean up to use return values instead of modyfing reference params


using EventQueue = RBTree<PointR, std::vector<LineSegmentR*>>;
using StatusQueue = RBTree<PointR, std::vector<LineSegmentR*>>;

using LineSegmentComparator = std::function<bool(LineSegmentR*, LineSegmentR*)>;
using LineSegmentTree = RBTree<LineSegmentR*, PointR, LineSegmentComparator>;

void findNeighbours(const PointR& point, const LineSegmentTree& tree, LineSegmentR*& above, LineSegmentR*& below);

LineSegmentR* findLeftmost(std::vector<LineSegmentR*>& segments, const PointR& point);
LineSegmentR* findRightmost(std::vector<LineSegmentR*>& segments, const PointR& point);

LineSegmentR* findLeftNeighbour(LineSegmentR* line, const LineSegmentTree& tree);
LineSegmentR* findRightNeighbour(LineSegmentR* line, const LineSegmentTree& tree);

void computeNewEvent(LineSegmentR* a, LineSegmentR* b, PointR point, StatusQueue& statusQueue);

std::pair<std::vector<LineSegmentR*>, std::vector<LineSegmentR*>> getIntersectionSets(const PointR& point, LineSegmentTree& tree);

EventQueue bentleyOttmann(std::vector<LineSegmentR>& segments);

