#pragma once

#include <iostream>
#include <memory>
#include <optional>
#include <limits>

#include <internal/include/point.h>
#include <internal/include/slope.h>

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
     * @brief Construct a new LineSegment with the given points.
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
    const Point<T>&                 getStart() const;

    /**
     * @brief Set the start point of the LineSegment to a different value.
     *
     * @return Point<T> The new starting Point to switch to.
     */
    void                            setStart( const Point<T>& start );

    /**
     * @brief Get the end point of the LineSegment.
     *
     * @return Point<T> The end Point.
     */
    const Point<T>&                 getEnd() const;


    /**
     * @brief Set the end point of the LineSegment to a different value.
     *
     * @param start Point<T> The new ending %Point to swtich to.
     */
    void                            setEnd( const Point<T>& end );

    /**
     * @brief Get the start and end points of the LineSegment as a pair.
     *
     * @return std::pair<Point<T>, Point<T>> The pair of points (start, end) used to construct the LineSegment.
     */
    std::pair<Point<T>, Point<T> >   getPoints() const;

    /**
     * @brief Calculates the slope of the line segment. Slope is calculated using the formula: (y2 - y1 / x2 - x1).
     *
     * @return const Slope& The slope of the line segment.
     */
    const Slope&                    getSlope() const;

    /**
     * @brief LineSegment assignment operator using a constant LineSegment.
     *
     * @param other The LineSegment to use to assign this LineSegment.
     */
    LineSegment<T>&                 operator =( const LineSegment<T>& other );

    /**
     * @brief LineSegment assignment operator using a LineSegment.
     *
     * @param other The LineSegment to use to assign this LineSegment.
     */
    LineSegment<T>&                 operator =( LineSegment<T>&& other );

    /**
     * @brief LineSegment assignment operator using a pair of the start and end points.
     *
     * @param other The pair of points (start, end) to assign to create a new LineSegment with the same start and end points.
     */
    LineSegment<T>&                 operator =( std::pair<Point<T>, Point<T> > other );


    /**
     * @brief Computes the high of a line segment.
     *
     * High of the line segment is:
     *  - Undefined if line segment doesn't cross the vertical line with the abcissa of the given poin.
     *  - If line segment is vertical:
     *      - The Y coordinate of the point if the line segment contains the point
     *      - The Y coordinate of the left endpoint if the point is laying below the line segment.
     *      - The Y coordinate of the right endpoint if the point is lying abouve the line segment.
     *  - The Y coordiante of the crossing point of the segment and the vertcal line with abcissa of the given point.
     *
     * @param point Point to use in the compoarison
     * @return T High of the  line segment.
     */
    T                               high( const Point<T>& point ) const;

    /**
     * @brief Returns the order of the line segment relative to a given point
     *
     * A line segment is less than another line segment if its high is less than the other line segment's high.
     *
     * @param other Line segment to compare with
     * @param point Sweeping point to use in the comparison
     * @return true If this segment is less than the other segment
     * @return false If this segment is greater than or equal the other segment
     */
    bool                            less( const LineSegment<T>& other, const Point<T>& point ) const;

    /**
     * @brief Checks whether the given line segment intersects with this line segment at a unique point and returns the point of intersection if it does.
     *
     * @param other Other line segment to check whether it intersects with this line segment.
     * @return std::optional<Point<T>> If the line segments intersect, the point of intersection is returned. Otherwise, an empty optional is returned.
     */
    std::optional<Point<T> >         intersects( const LineSegment<T>& other ) const;

    /**
     * @brief Checks whether the given point has the same coordinates as the end point of this line segment.
     *
     * @param point Point to check whether it is the end point of this line segment.
     * @return true If the given point has the same coordinates as the end point of this line segment.
     * @return false If the given point does not  have the same coordinates as the end point of this line segment.
     */
    bool                            isRightEnd( const Point<T>& point ) const;

    /**
     * @brief Checks whether the given point has the same coordinates as the start point of this line segment.
     *
     * @param point Point to check whether it is the start point of this line segment.
     * @return true If the given point has the same coordinates as the start point of this line segment.
     * @return false If the given point does not have the same coordinates as the start point of this line segment.
     */
    bool                            isLeftEnd( const Point<T>& point ) const;

    /**
     * @brief Checks whether the given point lies on this line segment.
     *
     * @param point Point to check whether it lies on this line segment.
     * @return true If the given point lies on this line segment.
     * @return false If the given point does not lie on this line segment.
     */
    bool                            contains( const Point<T>& point ) const;

    template <typename R>
    friend std::istream&            operator >>(std::istream& stream, LineSegment<R>& segment);

private:

    void                            orderPoints();

    /**
     * @brief Internal function to calculate the slope of the line segment. Slope is calculated using the formula: (y2 - y1 / x2 - x1).
     *
     * Does not return any value and instead sets the slope member variable (mSlope).
     *
     */
    void                            calculateSlope();

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

    /**
     * @brief The slope of the line segment
     *
     */
    Slope mSlope;
};

#include <internal/src/linesegment.inl>

using LineSegmentI = LineSegment<int>;
using LineSegmentF = LineSegment<float>;
using LineSegmentD = LineSegment<double>;
using LineSegmentR = LineSegment<Rational>;