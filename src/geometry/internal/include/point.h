#pragma once

#include <memory>

template <typename T> // TODO: Add arithemtic concept for T
class Point
{
public:
                            Point();
                            Point(T x, T y);
                            Point(const Point &other);
                            Point(Point &&other);
    explicit                Point(std::pair<T, T> point);

    const T&                getX() const;
    void                    setX(const T &x);

    const T&                getY() const;
    const T&                setY(const T &y);

    std::pair<T, T>         getCoordinates() const;

    Point<T>&               operator=(const Point<T> &other);
    Point<T>&               operator=(Point<T> &&other);
    Point<T>&               operator=(std::pair<T, T> other);

    bool                    operator==(const Point<T> &other) const;
    bool                    operator!=(const Point<T> &other) const;

    Point<T>                operator+(const Point<T> &other) const;
    Point<T>                operator-(const Point<T> &other) const;

    Point<T>                operator*(const T &other) const;
    Point<T>                operator/(const T &other) const;

private:
    T                       mX;
    T                       mY;
};

#include <internal/src/point.inl>