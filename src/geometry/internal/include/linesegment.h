#pragma once

#include <memory>
#include <optional>

#include <internal/include/point.h>
#include <internal/include/slope.h>

#include <math/rational.h>

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
    const Slope&                    getSlope() const;

    LineSegment<T>&                 operator =(const LineSegment<T>& other);
    LineSegment<T>&                 operator =(LineSegment<T>&& other);
    LineSegment<T>&                 operator =(std::pair<Point<T>, Point<T>> other);

    T                               high(const Point<T>& point) const;
    bool                            less(const LineSegment<T>& other, const Point<T>& point) const;

    std::optional<Point<T>>         intersects(const LineSegment<T>& other) const;

    bool                            isRightEnd(const Point<T>& point) const;
    bool                            isLeftEnd(const Point<T>& point) const;

    bool                            contains(const Point<T>& point) const;

private:
    void                            orderPoints();
    void                            calculateSlope();

private:
    Point<T>                        mStart;
    Point<T>                        mEnd;
    Slope                           mSlope;
};

#include <internal/src/linesegment.inl>

using LineSegmentI = LineSegment<int>;
using LineSegmentF = LineSegment<float>;
using LineSegmentD = LineSegment<double>;
using LineSegmentR = LineSegment<Rational>;