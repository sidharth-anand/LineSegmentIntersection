#pragma once

#include <memory>

#include <internal/include/point.h>

/**
 * @brief A standard container for a line segment made up of two points, a start and an end.
 *
 * This LineSegment is a simple class that contains two points, a start and an end. It contains getters and setters for the points and defines assignment operators for itself.
 *
 * @tparam T: A generic paramter used to represent the data type used to represent each of the points.
 */
template <typename T>
class LineSegment
{
public:
    /**
     * @brief Construct a new LineSegment object with null inital start and end points.
     *
     */
    LineSegment();

    /**
     * @brief Construct a new LineSegment with the given points.
     *
     * @param start the first %Point.
     * @param end The second %Point.
     */
    LineSegment( const Point<T>& start, const Point<T>& end );

    /**
     * @brief Construct a new LineSegment object.
     *
     * @param start the first %Point.
     * @param end The second %Point.
     */
    LineSegment( Point<T>&& start, Point<T>&& end );

    /**
     * @brief Construct a new LineSegment object by copying another given LineSegment.
     *
     * @param other The LineSegment to copy to construct this LineSegment.
     */
    LineSegment( const LineSegment<T>& other );

    /**
     * @brief Construct a new LineSegment object by copying another given LineSegment.
     *
     * @param other The LineSegment to copy to construct this LineSegment.
     */
    LineSegment( LineSegment<T>&& other );

    /**
     * @brief Construct a new Line Segment object with a pair of the start and end %Points.
     *
     * @param points The pair of %Points (start, end) to use to construct this LineSegment.
     */
    explicit LineSegment( std::pair<Point<T>, Point<T> > points );

    /**
     * @brief Get the start point of the LineSegment.
     *
     * @return Point<T> The starting Point.
     */
    const Point<T> &getStart() const;

    /**
     * @brief Set the start point of the LineSegment to a different value.
     *
     * @return Point<T> The new starting Point to switch to.
     */
    void setStart( const Point<T>& start );

    /**
     * @brief Get the end point of the LineSegment.
     *
     * @return Point<T> The end Point.
     */
    const Point<T> &getEnd() const;

    /**
     * @brief Set the end point of the LineSegment to a different value.
     *
     * @param start Point<T> The new ending %Point to swtich to.
     */
    void setEnd( const Point<T>& end );

    /**
     * @brief Get the start and end points of the LineSegment as a pair.
     *
     * @return std::pair<Point<T>, Point<T>> The pair of points (start, end) used to construct the LineSegment.
     */
    std::pair<Point<T>, Point<T> > getPoints() const;

    /**
     * @brief LineSegment assignment operator using a constant LineSegment.
     *
     * @param other The LineSegment to use to assign this LineSegment.
     */
    LineSegment<T> &operator=( const LineSegment<T>& other );

    /**
     * @brief LineSegment assignment operator using a LineSegment.
     *
     * @param other The LineSegment to use to assign this LineSegment.
     */
    LineSegment<T> &operator=( LineSegment<T>&& other );

    /**
     * @brief LineSegment assignment operator using a pair of the start and end points.
     *
     * @param other The pair of points (start, end) to assign to create a new LineSegment with the same start and end points.
     */
    LineSegment<T> &operator=( std::pair<Point<T>, Point<T> > other );

private:
    /**
     * @brief The start point of the line segment
     */
    Point<T> mStart;

    /**
     * @brief The end point of the line segment
     *
     */
    Point<T> mEnd;
};

#include <internal/src/linesegment.inl>