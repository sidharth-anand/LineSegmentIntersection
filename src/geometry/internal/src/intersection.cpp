#include <iostream>
#include <algorithm>

#include <internal/include/intersection.h>


void findNeighbours(const PointR& point, const LineSegmentTree& tree, LineSegmentR*& above, LineSegmentR*& below)
{
    PointR sweepPoint = point;
    LineSegmentR sweepLine = LineSegment(sweepPoint, sweepPoint);


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


LineSegmentR* findLeftmost(std::vector<LineSegmentR*>& segments, const PointR& point)
{
    LineSegmentR* min = *segments.begin();


    for(auto segment : segments)
    {
        if(segment->less(*min, point))
            min = segment;
    }

    return min;
}


LineSegmentR* findRightmost(std::vector<LineSegmentR*>& segments, const PointR& point)
{
    LineSegmentR* max = *segments.begin();


    for(auto segment : segments)
    {
        if(max->less(*segment, point))
            max = segment;
    }

    return max;
}


LineSegmentR* findLeftNeighbour(LineSegmentR* line, const LineSegmentTree& tree)


{
    auto it = tree.find(line);

    if(it == tree.begin())
        return nullptr;
    else
        return (*--it).first;
}


LineSegmentR* findRightNeighbour(LineSegmentR* line, const LineSegmentTree& tree)

{
    auto it = tree.find(line);
    
    if(++it == tree.end())
        return nullptr;
    else
        return (*it).first;
}


void computeNewEvent(LineSegmentR* a, LineSegmentR* b, PointR point, StatusQueue& statusQueue)

{
    if (a == nullptr || b == nullptr)
        return;


    std::optional<PointR> intersection = a->intersects(*b);

    if(intersection && point < intersection && statusQueue.find(intersection.value()) == statusQueue.end())
        statusQueue.insert({intersection.value(), std::vector<LineSegmentR*>()});
}

std::pair<std::vector<LineSegmentR*>, std::vector<LineSegmentR*>> getIntersectionSets(const PointR& point, LineSegmentTree& tree)
{
    std::vector<LineSegmentR*> i;
    std::vector<LineSegmentR*> r;


    if(tree.empty())
        return {i, r};


    LineSegmentR segment(point, point);

 
    for (auto it = std::reverse_iterator(tree.upperBound(&segment)); it != tree.rend() && (*it).first->high(point) == point.getY(); it++)
    {
        if ((*it).first->contains(point))
            i.push_back((*it).first);
        else if ((*it).first->isRightEnd(point))
            r.push_back((*it).first);
    }

    return {i, r};
}


EventQueue bentleyOttmann(std::vector<LineSegmentR>& set)

{
    EventQueue eventQueue;
    StatusQueue statusQueue;

    for (auto it = set.begin(); it != set.end(); it++)
    {

        auto exists = statusQueue.insert({ it->getStart(), std::vector<LineSegmentR*>({ &(*it) }) });
        if (exists.second == false)
            exists.first->second.push_back(&(*it));

        statusQueue.insert({it->getEnd(), std::vector<LineSegmentR*>()});
    }

    PointR sweepPoint;

    const auto comparator = [&sweepPoint](LineSegmentR* a, LineSegmentR* b) -> bool 


    {
        return a->less(*b, sweepPoint);
    };

    LineSegmentTree tree(comparator);

    while(statusQueue.size() > 0)
    {

        PointR point = statusQueue.begin()->first;
        std::vector<LineSegmentR*> leftSet = statusQueue.begin()->second;

        statusQueue.erase(statusQueue.begin());

        sweepPoint = point;


        std::pair<std::vector<LineSegmentR*>, std::vector<LineSegmentR*>> intersectionSets = getIntersectionSets(point, tree);

        if(leftSet.size() + intersectionSets.first.size() + intersectionSets.second.size() > 1)
        {
            EventQueue::Iterator it = eventQueue.insert({point, std::vector<LineSegmentR*>()}).first;

            
            for(const auto& segment: leftSet)
                it->second.push_back(segment);

            for(const auto& segment: intersectionSets.first)
                it->second.push_back(segment);
            
            for(const auto& segment: intersectionSets.second)
                it->second.push_back(segment);
        }

        for(const auto& segment : intersectionSets.first)
            tree.erase(segment);

        for(const auto& segment : intersectionSets.second)
            tree.erase(segment);

        sweepPoint = point;

        for(const auto& segment : leftSet)
            tree.insert({segment, sweepPoint});

        for(const auto& segment : intersectionSets.first)
            tree.insert({segment, sweepPoint});

        if(leftSet.size() + intersectionSets.first.size() == 0)
        {

            LineSegmentR* a;
            LineSegmentR* b;


            findNeighbours(point, tree, a, b);
            computeNewEvent(a, b, point, statusQueue);
        }
        else
        {

            std::vector<LineSegmentR*> segments(leftSet.size() + intersectionSets.first.size());
            std::set_union(leftSet.begin(), leftSet.end(), intersectionSets.first.begin(), intersectionSets.first.end(), segments.begin());

            LineSegmentR* left = findLeftmost(segments, point);
            LineSegmentR* right = findRightmost(segments, point);
            LineSegmentR* leftNeighbour = findLeftNeighbour(left, tree);
            LineSegmentR* rightNeighbour = findRightNeighbour(right, tree);


            computeNewEvent(left, leftNeighbour, point, statusQueue);
            computeNewEvent(right, rightNeighbour, point, statusQueue);
        }
    }

    return eventQueue; 
}
