#pragma once

#include <iostream>
#include <memory>


#include <math/rational.h>


/**
 * @brief A standard container for a point made up of an X and Y coordinate.
 *
 * This Point is a simple class that contains an X and Y coordinate. It contains getters and setters for the coordinates and defines assignment, equality, inequality, and arithmetic operators for itself.
 *
 * @tparam T A generic paramter used to represent the data type used to represent the coordinates.
 */

template <typename T> // TODO: Add arithemtic concept for T
class Point
{
public:



    /**
     * @brief Construct a new POint object with null X and Y coordinates.
     *
     */
    Point();

    /**
     * @brief Construct a new Point object with the given coordinates
     *
     * @param x The X coordinate
     * @param y The Y coordinate
     */
    Point( T x, T y );

    /**
     * @brief Construct a new Point object with the same values as another given Point.
     *
     * @param other
     */
    Point( const Point& other );

    /**
     * @brief Construct a new Point object with the same values as another given Point.
     *
     * @param other
     */
    Point( Point&& other );

    /**
     * @brief Construct a new Point object using a pair of the X and Y coordinates.
     *
     * @param point Pair of coordinates (X, Y) to use to construct the Point
     */
    explicit Point( std::pair<T, T> point );

    /**
     * @brief Get the X coordinate
     *
     * @return The current X coordinate
     */
    const T&                getX() const;

    /**
     * @brief Set the X coordinate
     *
     * @param x The X coordinate to set
     */
    void                    setX( const T& x );

    /**
     * @brief Get the Y coordinate
     *
     * @return The current Y coordinate
     */
    const T&                getY() const;

    /**
     * @brief Set the Y coordinate
     *
     * @param y The Y coordinate to set
     */
    void                    setY( const T& y );

    /**
     * @brief Get the X and Y coordinates as a pair
     *
     * @return Pair of coordinates (X, Y) used to construct the point
     */
    std::pair<T, T>         getCoordinates() const;

    /**
     * @brief Set the X and Y coordinates to new values
     *
     * @param x The new X coordinate to set
     * @param y The new Y coordinate to set
     */
    void                    setCoordinates( const T& x, const T& y );

    /**
     * @brief Point Assignemnt operator using another Point
     *
     * @param other The Point object to copy coordinates from and assign to the current Point
     */
    Point<T>&               operator=( const Point<T>& other );

    /**
     * @brief Point Assignemnt operator using another Point
     *
     * @param other The Point object to copy coordinates from and assign to the current Point
     */
    Point<T>&               operator=( Point<T>&& other );

    /**
     * @brief Point Assignemnt operator using a pair of coordinates
     *
     * @param other Pair of coordinates (x, y) used to construct the point and assign
     */
    Point<T>&               operator=( std::pair<T, T> other );

    /**
     * @brief Equality operator for Point objects
     *
     * @param other The point to check equality against
     * @return true when the X and Y coordindates of both the points are equal
     * @return false when the X and Y coordindates of both the points are not equal
     */
    bool operator==( const Point<T>& other ) const;

    /**
     * @brief Inequality operator for Point objects
     *
     * @param other The point to check equality against
     * @return true when the X and Y coordindates of both the points are not equal
     * @return false when the X and Y coordindates of both the points are equal
     */
    bool operator!=( const Point<T>& other ) const;

    /**
     * @brief Arithmetic addition operator for Point objects
     *
     * Adds the X and Y coordinates of the other point to the current point
     *
     * @param other The point to add to this point
     * @return Point<T> with the addition of the X and Y coordinates of the two points
     */
    Point<T>                operator+( const Point<T>& other ) const;

    /**
     * @brief Arithmetic subtraction operator for Point objects
     *
     * Subtracts the X and Y coordinates of the other point from the current point (this point minus the other point)
     *
     * @param other The point to subtract from this point
     * @return Point<T> with the result of subtraction of the two points
     */
    Point<T>                operator-( const Point<T>& other ) const;

    /**
     * @brief Arithmetic multiplication operator for Point objects
     *
     * Multiplies the X and Y coordinates of the other point with the current point
     *
     * @param other The point to multiplie this point with
     * @return Point<T> with the result of multiplication of the two points
     */
    Point<T>                operator*( const T& other ) const;

    /**
     * @brief Arithmetic division operator for Point objects
     *
     * Divides the X and Y coordinates of the other point from the current point (this point divided by the other point)
     *
     * @param other The point to divide by this point
     * @return Point<T> with the result of division of the two points
     */
    Point<T>                operator/( const T& other ) const;

private:
    /**
     * @brief Internal reference to the current X coordinate
     */
    T mX;

    /**
     * @brief Internal reference to the current Y coordinate
     */
    T mY;
};

#include <internal/src/point.inl>

using PointI = Point<int>;
using PointF = Point<float>;

using PointD = Point<double>;
using PointR = Point<Rational>;
