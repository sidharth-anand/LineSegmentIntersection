#pragma once

#include <functional>
#include <vector>

#include <internal/include/point.h>
#include <internal/include/linesegment.h>

#include <structures/rbtree.h>

//TODO: Use smart pointers instead of LineSegmentD*
//TODO: Clean up to use return values instead of modyfing reference params

using EventQueue = RBTree<PointD, std::vector<LineSegmentD*>>;
using StatusQueue = RBTree<PointD, std::vector<LineSegmentD*>>;

using LineSegmentComparator = std::function<bool(LineSegmentD*, LineSegmentD*)>;
using LineSegmentTree = RBTree<LineSegmentD*, PointD, LineSegmentComparator>;

void findNeighbours(const PointD& point, const LineSegmentTree& tree, LineSegmentD*& above, LineSegmentD*& below);

LineSegmentD* findLeftmost(std::vector<LineSegmentD*>& segments, const PointD& point);
LineSegmentD* findRightmost(std::vector<LineSegmentD*>& segments, const PointD& point);

LineSegmentD* findLeftNeighbour(LineSegmentD* line, const LineSegmentTree& tree);
LineSegmentD* findRightNeighbour(LineSegmentD* line, const LineSegmentTree& tree);

void computeNewEvent(LineSegmentD* a, LineSegmentD* b, PointD point, StatusQueue& statusQueue);

std::pair<std::vector<LineSegmentD*>, std::vector<LineSegmentD*>> getIntersectionSets(const PointD& point, LineSegmentTree& tree);

EventQueue bentleyOttmann(std::vector<LineSegmentD>& segments);