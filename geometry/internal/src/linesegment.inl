template <typename T>
LineSegment<T>::LineSegment()
    : mStart(), mEnd()
{
}

template <typename T>
LineSegment<T>::LineSegment(const Point<T> &start, const Point<T> &end)
    : mStart(start), mEnd(end)
{
}

template <typename T>
LineSegment<T>::LineSegment(Point<T> &&start, Point<T> &&end)
    : mStart(std::move(start)), mEnd(std::move(end))
{
}

template <typename T>
LineSegment<T>::LineSegment(const LineSegment<T> &other)
    : mStart(other.mStart), mEnd(other.mEnd)
{
}

template <typename T>
LineSegment<T>::LineSegment(LineSegment<T> &&other)
    : mStart(std::move(other.mStart)), mEnd(std::move(other.mEnd))
{
}

template <typename T>
LineSegment<T>::LineSegment(std::pair<Point<T>, Point<T>> points)
    : mStart(points.first), mEnd(points.second)
{
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
}

template <typename T>
std::pair<Point<T>, Point<T>> LineSegment<T>::getPoints() const
{
    return std::make_pair(mStart, mEnd);
}

template <typename T>
LineSegment<T> &LineSegment<T>::operator=(const LineSegment<T> &other)
{
    mStart = other.mStart;
    mEnd = other.mEnd;
    return *this;
}

template <typename T>
LineSegment<T> &LineSegment<T>::operator=(LineSegment<T> &&other)
{
    mStart = std::move(other.mStart);
    mEnd = std::move(other.mEnd);
    return *this;
}

template <typename T>
LineSegment<T> &LineSegment<T>::operator=(std::pair<Point<T>, Point<T>> other)
{
    mStart = other.first;
    mEnd = other.second;
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
