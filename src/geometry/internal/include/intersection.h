#pragma once

#include <functional>
#include <vector>

#include <internal/include/point.h>
#include <internal/include/linesegment.h>

#include <structures/rbtree.h>

using EventQueue = RBTree<PointD, std::vector<LineSegmentD*>>;
using StatusQueue = RBTree<PointD, std::vector<LineSegmentD*>>;

using LineSegmentComparator = std::function<bool(LineSegmentD*, LineSegmentD*)>;
using LineSegmentTree = RBTree<LineSegmentD*, PointD, LineSegmentComparator>;

void findNeighbours(const PointD& point, LineSegmentTree& tree, LineSegmentD*& above, LineSegmentD*& below);

LineSegmentD* findLeftmost(std::vector<LineSegmentD*>& segments, const PointD& point);
LineSegmentD* findRightmost(std::vector<LineSegmentD*>& segments, PointD point);

LineSegmentD* findLeftNeighbour(LineSegmentD* line, LineSegmentTree& tree);
LineSegmentD* findRightNeighbour(LineSegmentD* line, LineSegmentTree& tree);

void computeNewEvent(LineSegmentD* a, LineSegmentD* b, PointD point, StatusQueue& statusQueue);

std::pair<std::vector<LineSegmentD*>, std::vector<LineSegmentD*>> getSets(const PointD& point, LineSegmentTree& tree);

EventQueue bentleyOttmann(const std::vector<LineSegmentD>& segments);