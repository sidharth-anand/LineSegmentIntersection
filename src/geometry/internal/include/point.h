#pragma once

#include <iostream>
#include <memory>

#include <math/rational.h>

template <typename T> // TODO: Add arithemtic concept for T
class Point
{
public:
                            Point();
                            Point(T x, T y);
                            Point(const Point &other);
                            Point(Point &&other);
                            explicit Point(std::pair<T, T> point);

    const T&                getX() const;
    void                    setX(const T &x);

    const T&                getY() const;
    void                    setY(const T &y);

    std::pair<T, T>         getCoordinates() const;
    void                    setCoordinates(const T &x, const T &y);

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

using PointI = Point<int>;
using PointF = Point<float>;
using PointD = Point<double>;
using PointR = Point<Rational>;