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

template <typename T>
T LineSegment<T>::high(const Point<T>& point) const
{
    if(mSlope.type == "infinity"){
        T py, ly, ry;
        py = point.getY();
        ly = getStart().getY();
        ry = getEnd().getY();

        if(py < ly){
            return ly;
        }
        else if(py > ry){
            return ry;
        }
        else{
            return py;
        }
    }
    else{
        T xa, xb, ya, yb;
        xa = getStart().getX();
        xb = getEnd().getX();
        ya = getStart().getY();
        yb = getEnd().getY();
        return (yb - ya)/(xb - xa) * (point.getX() - xa) + ya;
    }
}

template<typename T>
bool LineSegment<T>::less(const LineSegment<T>& other, const Point<T>& point){
    return (high(point) < other.high(point) || (high(point) == other.high(point) && mSlope.value < other.mSlope.value));
}

template <typename T>
bool LineSegment<T>::intersect(const LineSegment<T>& other, Point<T>& point){
    Point s_left = other.getStart();
    Point s_right = other.getEnd();

    T xa = getStart().getX();
    T ya = getStart().getY();
    T xb = getEnd().getX();
    T yb = getEnd().getY();
    T xc = s_left.getX();
    T yc = s_left.getY();
    T xd = s_right.getX();
    T yd = s_right.getY();

    T delta = (xb - xa)*(yc - yd) - (yb - ya)*(xc - xd);
    if (delta == 0) {
        return false;
    }

    T r = ((xc - xa)*(yc - yd) - (yc - ya)*(xc - xd)) / delta;
    T s = ((yc - ya)*(xb - xa) - (xc - xa)*(yb - ya)) / delta;

    if (r < 0 || r > 1 || s < 0 || s > 1) {
        return false;
    }

    T x = xa + r*(xb - xa);
    T y = ya + r*(yb - ya);
    point.setCoordinates(x, y);

    return true;
}

template <typename T>
bool LineSegment<T>::is_rend(const Point<T>& point){
    return (point.getX() == getEnd().getX() && point.getY() == getEnd().getY());
}

template <typename T>
bool LineSegment<T>::is_lend(const Point<T>& point){
    return (point.getX() == getStart().getX() && point.getY() == getStart().getY());
}

template<typename T>
bool LineSegment<T>::contains(const Point<T>& point){
    ((! is_rend(point)) && (! is_lend(point)));
}