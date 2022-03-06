template <typename T>
Point<T>::Point()
    : mX(0), mY(0)
{
}

template <typename T>
Point<T>::Point(T x, T y)
    : mX(x), mY(y)
{
}

template <typename T>
Point<T>::Point(T &&x, T &&y)
    : mX(std::move(x)), mY(std::move(y))
{
}

template <typename T>
Point<T>::Point(const Point &other)
    : mX(other.mX), mY(other.mY)
{
}

template <typename T>
Point<T>::Point(Point &&other)
    : mX(std::move(other.mX)), mY(std::move(other.mY))
{
}

template <typename T>
Point<T>::Point(std::pair<T, T> point)
    : mX(point.first), mY(point.second)
{
}

template <typename T>
const T &Point<T>::getX() const
{
    return mX;
}

template <typename T>
void Point<T>::setX(const T &x)
{
    mX = x;
}

template <typename T>
const T &Point<T>::getY() const
{
    return mY;
}

template <typename T>
const T &Point<T>::setY(const T &y)
{
    mY = y;
}

template <typename T>
std::pair<T, T> Point<T>::getCoordinates() const
{
    return std::make_pair(mX, mY);
}

template <typename T>
Point<T> &Point<T>::operator=(const Point<T> &other)
{
    mX = other.mX;
    mY = other.mY;
    return *this;
}

template <typename T>
Point<T> &Point<T>::operator=(Point<T> &&other)
{
    mX = std::move(other.mX);
    mY = std::move(other.mY);
    return *this;
}

template <typename T>
Point<T> &Point<T>::operator=(std::pair<T, T> other)
{
    mX = other.first;
    mY = other.second;
    return *this;
}

template <typename T>
bool Point<T>::operator==(const Point<T> &other) const
{
    return mX == other.mX && mY == other.mY;
}

template <typename T>
bool Point<T>::operator!=(const Point<T> &other) const
{
    return !(*this == other);
}

template <typename T>
Point<T> Point<T>::operator+(const Point<T> &other) const
{
    return Point(mX + other.mX, mY + other.mY);
}

template <typename T>
Point<T> Point<T>::operator-(const Point<T> &other) const
{
    return Point(mX - other.mX, mY - other.mY);
}

template <typename T>
Point<T> Point<T>::operator*(const T &other) const
{
    return Point(mX * other, mY * other);
}

template <typename T>
Point<T> Point<T>::operator/(const T &other) const
{
    return Point(mX / other, mY / other);
}

template <typename T>
bool operator==(const Point<T> &lhs, const Point<T> &rhs)
{
    return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}

template <typename T>
bool operator!=(const Point<T> &lhs, const Point<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const Point<T> &lhs, const Point<T> &rhs)
{
    return lhs.getY() < rhs.getY() || (lhs.getY() == rhs.getY() && lhs.getX() < rhs.getX());
}

template <typename T>
bool operator>(const Point<T> &lhs, const Point<T> &rhs)
{
    return rhs < lhs;
}

template <typename T>
bool operator<=(const Point<T> &lhs, const Point<T> &rhs)
{
    return !(rhs < lhs);
}

template <typename T>
bool operator>=(const Point<T> &lhs, const Point<T> &rhs)
{
    return !(lhs < rhs);
}
