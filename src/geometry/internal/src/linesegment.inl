#include "linesegment.h"
template <typename T>
LineSegment<T>::LineSegment()
    : mStart()
    , mEnd()
{
    calculateSlope();
}

template <typename T>
LineSegment<T>::LineSegment(const Point<T> &start, const Point<T> &end)
    : mStart(start)
    , mEnd(end)
{
    calculateSlope();
}

template <typename T>
LineSegment<T>::LineSegment(Point<T> &&start, Point<T> &&end)
    : mStart(std::move(start))
    , mEnd(std::move(end))
{
    calculateSlope();
}

template <typename T>
LineSegment<T>::LineSegment(const LineSegment<T> &other)
    : mStart(other.mStart)
    , mEnd(other.mEnd)
{
    calculateSlope();
}

template <typename T>
LineSegment<T>::LineSegment(LineSegment<T> &&other)
    : mStart(std::move(other.mStart))
    , mEnd(std::move(other.mEnd))
{
    calculateSlope();
}

template <typename T>
LineSegment<T>::LineSegment(std::pair<Point<T>, Point<T>> points)
    : mStart(points.first),
    mEnd(points.second)
{
    calculateSlope();
}

template <typename T>
const Point<T> &LineSegment<T>::getStart() const
{
    return mStart;
}

template <typename T>
void LineSegment<T>::setStart(const Point<T> &start)
{
    mStart = start;
    calculateSlope();
}

template <typename T>
const Point<T> &LineSegment<T>::getEnd() const
{
    return mEnd;
}

template <typename T>
void LineSegment<T>::setEnd(const Point<T> &end)
{
    mEnd = end;
    calculateSlope();
}

template <typename T>
std::pair<Point<T>, Point<T>> LineSegment<T>::getPoints() const
{
    return std::make_pair(mStart, mEnd);
}

template <typename T>
T LineSegment<T>::high(const Point<T>& point) const
{
    if (mSlope.type == Slope::Type::Infinite)
    {
        T py, ly, ry;

        py = point.getY();
        ly = getStart().getY();
        ry = getEnd().getY();

        if (py < ly)
            return ly;
        else if (py > ry)
            return ry;
        else 
            return py;
    }
    else 
    {
        T xa, xb, ya, yb;

        xa = getStart().getX();
        xb = getEnd().getX();

        ya = getStart().getY();
        yb = getEnd().getY();

        return (yb - ya) / (xb - xa) * (point.getX() - xa) + ya;
    }
}

template<typename T>
bool LineSegment<T>::less(const LineSegment<T>& other, const Point<T>& point) const
{
    return (high(point) < other.high(point) || (high(point) == other.high(point) && mSlope.value < other.mSlope.value));
}

template <typename T>
std::optional<Point<T>> LineSegment<T>::intersects(const LineSegment<T>& other) const
{
    Point sLeft = other.getStart();
    Point sRight = other.getEnd();

    T xa = getStart().getX();
    T ya = getStart().getY();

    T xb = getEnd().getX();
    T yb = getEnd().getY();

    T xc = sLeft.getX();
    T yc = sLeft.getY();

    T xd = sRight.getX();
    T yd = sRight.getY();

    T delta = (xb - xa) * (yc - yd) - (yb - ya) * (xc - xd);
    if (delta == 0)
        return {};

    T r = ((xc - xa) * (yc - yd) - (yc - ya) * (xc - xd)) / delta;
    T s = ((yc - ya) * (xb - xa) - (xc - xa) * (yb - ya)) / delta;

    if (r < 0 || r > 1 || s < 0 || s > 1)
        return {};

    T x = xa + r * (xb - xa);
    T y = ya + r * (yb - ya);

    return Point<T>(x, y);
}

template <typename T>
bool LineSegment<T>::isRightEnd(const Point<T>& point) const
{
    return (point.getX() == getEnd().getX() && point.getY() == getEnd().getY());
}

template <typename T>
bool LineSegment<T>::isLeftEnd(const Point<T>& point) const
{
    return (point.getX() == getStart().getX() && point.getY() == getStart().getY());
}

template<typename T>
bool LineSegment<T>::contains(const Point<T>& point) const
{
    return !isRightEnd(point) && !isLeftEnd(point);
}

template<typename T>
inline void LineSegment<T>::calculateSlope()
{
    if (mStart.getX() == mEnd.getX())
    {
        mSlope.value = 0;
        mSlope.type = Slope::Type::Infinite;
    }
    else
    {
        mSlope.value = (mEnd.getY() - mStart.getY()) / (mEnd.getX() - mStart.getX());
        mSlope.type = Slope::Type::Finite;
    }
}

template <typename T>
LineSegment<T> &LineSegment<T>::operator=(const LineSegment<T> &other)
{
    mStart = other.mStart;
    mEnd = other.mEnd;

    calculateSlope();

    return *this;
}

template <typename T>
LineSegment<T> &LineSegment<T>::operator=(LineSegment<T> &&other)
{
    mStart = std::move(other.mStart);
    mEnd = std::move(other.mEnd);

    calculateSlope();

    return *this;
}

template <typename T>
LineSegment<T> &LineSegment<T>::operator=(std::pair<Point<T>, Point<T>> other)
{
    mStart = other.first;
    mEnd = other.second;

    calculateSlope();

    return *this;
}

template <typename T>
bool operator==(const LineSegment<T> &lhs, const LineSegment<T> &rhs)
{
    return lhs.getPoints() == rhs.getPoints();
}

template <typename T>
bool operator!=(const LineSegment<T> &lhs, const LineSegment<T> &rhs)
{
    return !(lhs == rhs);
}