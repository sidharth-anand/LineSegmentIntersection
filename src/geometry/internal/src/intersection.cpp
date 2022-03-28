#include <iostream>
#include <algorithm>

#include <internal/include/intersection.h>

void findNeighbours(const PointD& point, LineSegmentTree& tree, LineSegmentD*& above, LineSegmentD*& below)
{
    PointD sweepPoint = point;
    LineSegmentD sweepLine = LineSegment(sweepPoint, sweepPoint);

    auto it = tree.upperBound(&sweepLine);

    if(it == tree.end())
        above = nullptr;
    else
        above = (*it).first;

    if (it == tree.begin())
        below = nullptr;
    else
        below = (*--it).first;
}

LineSegmentD* findLeftmost(std::vector<LineSegmentD*>& segments, const PointD& point)
{
    LineSegmentD* min = *segments.begin();

    for(auto segment : segments)
    {
        if(segment->less(*min, point))
            min = segment;
    }

    return min;
}

LineSegmentD* findRightmost(std::vector<LineSegmentD*>& segments, PointD point)
{
    LineSegmentD* max = *segments.begin();

    for(auto segment : segments)
    {
        if(max->less(*segment, point))
            max = segment;
    }

    return max;
}

LineSegmentD* findLeftNeighbour(LineSegmentD* line, LineSegmentTree& tree)
{
    auto it = tree.find(line);

    if(it == tree.begin())
        return nullptr;
    else
        return (*--it).first;
}

LineSegmentD* findRightNeighbour(LineSegmentD* line, LineSegmentTree& tree)
{
    auto it = tree.find(line);
    
    if(++it == tree.end())
        return nullptr;
    else
        return (*it).first;
}

void computeNewEvent(LineSegmentD* a, LineSegmentD* b, PointD point, StatusQueue& statusQueue)
{
    if (a == nullptr || b == nullptr)
        return;

    std::optional<PointD> intersection = a->intersects(*b);

    if(intersection)
    {
        if(point < intersection && statusQueue.find(intersection.value()) == statusQueue.end())
            statusQueue.insert({intersection.value(), std::vector<LineSegmentD*>()});
    }
}

std::pair<std::vector<LineSegmentD*>, std::vector<LineSegmentD*>> getSets(const PointD& point, LineSegmentTree& tree)
{
    std::vector<LineSegmentD*> i;
    std::vector<LineSegmentD*> r;

    if(tree.empty())
        return {i, r};

    LineSegmentD* segment = new LineSegment(PointD(point.getX(), point.getY()), PointD(point.getX(), point.getY()));

    auto it = tree.upperBound(segment);
    LineSegmentTree::ReverseIterator rit(it);

    PointD q;

    for (auto it : tree)
    {
        if (it.first->high(point) != point.getY())
            break;

        if (it.first->contains(point))
            i.push_back(it.first);
        else if (it.first->isRightEnd(point))
            r.push_back(it.first);
    }

    return {i, r};
}

EventQueue bentleyOttmann(const std::vector<LineSegmentD>& set)
{
    EventQueue eventQueue;
    StatusQueue statusQueue;

    for(auto line : set)
    {
        PointD left = line.getStart();
        PointD right = line.getEnd();

        statusQueue.insert({right, std::vector<LineSegmentD*>()});

        if (statusQueue.find(left) == statusQueue.end())
            statusQueue.insert({left, std::vector<LineSegmentD*>({&line})});
        else
            statusQueue.find(left)->second.push_back(&line);
    }

    const auto comparator = [](LineSegmentD* a, LineSegmentD* b) -> bool 
    {
        const PointD comparisonPoint(0, 0);
        return a->less(*b, comparisonPoint);
    };

    LineSegmentTree tree(comparator);

    while(statusQueue.size())
    {
        PointD point = statusQueue.begin()->first;
        std::vector<LineSegmentD*> leftSet = {statusQueue.begin()->second};
        statusQueue.erase(statusQueue.begin());

        PointD sweepPoint = point;

        std::pair<std::vector<LineSegmentD*>, std::vector<LineSegmentD*>> intersectionSets = getSets(point, tree);

        if(leftSet.size() + intersectionSets.first.size() + intersectionSets.second.size() > 1)
        {
            EventQueue::Iterator it = eventQueue.insert({point, std::vector<LineSegmentD*>()}).first;
            
            for(auto segment: leftSet)
                it->second.push_back(segment);

            for(auto segment: intersectionSets.first)
                it->second.push_back(segment);
            
            for(auto segment: intersectionSets.second)
                it->second.push_back(segment);
        }

        for(auto segment: intersectionSets.first)
            tree.erase(segment);

        for(auto segment: intersectionSets.second)
            tree.erase(segment);

        sweepPoint = point;

        for(auto segment: leftSet)
            tree.insert({segment, sweepPoint});

        for(auto segment: intersectionSets.first)
            tree.insert({segment, sweepPoint});

        if(leftSet.size() + intersectionSets.first.size() == 0)
        {
            LineSegmentD* a;
            LineSegmentD* b;

            findNeighbours(point, tree, a, b);
            computeNewEvent(a, b, point, statusQueue);
        }
        else
        {
            std::vector<LineSegmentD*> segments(leftSet.size() + intersectionSets.first.size());
            std::set_union(leftSet.begin(), leftSet.end(), intersectionSets.first.begin(), intersectionSets.first.end(), segments.begin());

            LineSegmentD* left = findLeftmost(segments, point);
            LineSegmentD* right = findRightmost(segments, point);
            LineSegmentD* leftNeighbour = findLeftNeighbour(left, tree);
            LineSegmentD* rightNeighbour = findRightNeighbour(right, tree);

            computeNewEvent(left, leftNeighbour, point, statusQueue);
            computeNewEvent(right, rightNeighbour, point, statusQueue);
        }
    }

    return eventQueue; 
}
