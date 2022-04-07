template <typename T>
LineSegment<T>::LineSegment()
    : mStart()
    , mEnd()
{
    orderPoints();
    calculateSlope();
}

template <typename T>
LineSegment<T>::LineSegment(const Point<T> &start, const Point<T> &end)
    : mStart(start)
    , mEnd(end)
{
    orderPoints();
    calculateSlope();
}

template <typename T>
LineSegment<T>::LineSegment(Point<T> &&start, Point<T> &&end)
    : mStart(std::move(start))
    , mEnd(std::move(end))
{
    orderPoints();
    calculateSlope();
}

template <typename T>
LineSegment<T>::LineSegment(const LineSegment<T> &other)
    : mStart(other.mStart)
    , mEnd(other.mEnd)
{
    orderPoints();
    calculateSlope();
}

template <typename T>
LineSegment<T>::LineSegment(LineSegment<T> &&other)
    : mStart(std::move(other.mStart))
    , mEnd(std::move(other.mEnd))
{
    orderPoints();
    calculateSlope();
}

template <typename T>
LineSegment<T>::LineSegment(std::pair<Point<T>, Point<T>> points)
    : mStart(points.first),

      mEnd(points.second)

{
    orderPoints();
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

    orderPoints();
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

    orderPoints();
    calculateSlope();
}

template <typename T>
std::pair<Point<T>, Point<T>> LineSegment<T>::getPoints() const
{
    return std::make_pair(mStart, mEnd);
}

template<typename T>
const Slope& LineSegment<T>::getSlope() const
{
    return mSlope;
}

template <typename T>
T LineSegment<T>::high(const Point<T>& point) const
{
    if (mSlope.type == Slope::Type::Infinite)
    {
        T py = point.getY();

        T ly = getStart().getY();
        T ry = getEnd().getY();

        if (py < ly)
            return ly;
        else if (py > ry)
            return ry;
        else 
            return py;
    }
    
    return mSlope.value * (point.getX() - mStart.getX()) + mStart.getY();
}

template<typename T>
bool LineSegment<T>::less(const LineSegment<T>& other, const Point<T>& point) const
{
    return high(point) < other.high(point) || (high(point) == other.high(point) && mSlope < other.getSlope());
}

template <typename T>
std::optional<Point<T>> LineSegment<T>::intersects(const LineSegment<T>& other) const
{
    // return std::nullopt if the lines are parallel
    // return std::nullopt if the lines are the same
    // return Point<T> if the lines intersect
    // use the cramer's rule to solve for the intersection

    if (mSlope.value == other.getSlope().value)
        return {};
    
    if (mSlope.type == Slope::Type::Infinite)
    {
        if (other.getSlope().type == Slope::Type::Infinite)
            return {};
        else
        {
            T x = mStart.getX();
            T y = other.getSlope().value * (x - other.getStart().getX()) + other.getStart().getY();
            return Point<T>(x, y);
        }
    }
    else if (other.getSlope().type == Slope::Type::Infinite)
    {
        T x = other.getStart().getX();
        T y = mSlope.value * (x - mStart.getX()) + mStart.getY();
        return Point<T>(x, y);
    }
    else
    {
        T x = (other.getStart().getY() - mStart.getY() + mSlope.value * mStart.getX() - other.getSlope().value * other.getStart().getX()) / (mSlope.value - other.getSlope().value);
        T y = mSlope.value * (x - mStart.getX()) + mStart.getY();
        return Point<T>(x, y);
    }
}

template <typename T>
bool LineSegment<T>::isRightEnd(const Point<T>& point) const
{
    return point == mEnd;
}

template <typename T>
bool LineSegment<T>::isLeftEnd(const Point<T>& point) const
{
    return point == mStart;
}

template<typename T>
bool LineSegment<T>::contains(const Point<T>& point) const
{
    return !isRightEnd(point) && !isLeftEnd(point);
}

template <typename T>
void LineSegment<T>::orderPoints()
{
    if (mEnd < mStart)
        std::swap(mStart, mEnd);
}

template<typename T>
void LineSegment<T>::calculateSlope()
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

template <typename T>

std::ostream &operator<<(std::ostream &stream, const LineSegment<T> segment)

{
    stream << segment.getStart() << " -> " << segment.getEnd();
    return stream;
}