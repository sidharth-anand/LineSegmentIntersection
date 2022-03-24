#pragma once

#include <memory>

#include <internal/include/point.h>
#include <internal/include/slope.h>

template <typename T>
class LineSegment
{
public:
                                    LineSegment();
                                    LineSegment(const Point<T>& start, const Point<T>& end);
                                    LineSegment(Point<T>&& start, Point<T>&& end);
                                    LineSegment(const LineSegment<T>& other);
                                    LineSegment(LineSegment<T>&& other);
    explicit                        LineSegment(std::pair<Point<T>, Point<T>> points);

    const Point<T>&                 getStart() const;
    void                            setStart(const Point<T>& start);

    const Point<T>&                 getEnd() const;
    void                            setEnd(const Point<T>& end);

    std::pair<Point<T>, Point<T>>   getPoints() const;

    LineSegment<T>&                 operator =(const LineSegment<T>& other);
    LineSegment<T>&                 operator =(LineSegment<T>&& other);
    LineSegment<T>&                 operator =(std::pair<Point<T>, Point<T>> other);

    T                               high(const Point<T>& point) const;
    bool                            less(const LineSegment<T>& other, const Point<T>& point);

    bool                            intersect(const LineSegment<T>& other, Point<T>& point);

    bool                            is_rend(const Point<T>& point);
    bool                            is_lend(const Point<T>& point);
    bool                            contains(const Point<T>& point);

private:
    Point<T>                        mStart;
    Point<T>                        mEnd;
    Slope<T>                        mSlope;
};

#include <internal/src/linesegment.inl>