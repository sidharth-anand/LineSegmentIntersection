#pragma once

#include <internal/include/linesegment.h>

/**
 * @brief Type definition for a line segment with the start and end points having integer coordinates
 *
 */
typedef LineSegment<int>      LineSegmentI;

/**
 * @brief Type definition for a line segment with the start and end points having floating point coordinates
 *
 */
typedef LineSegment<float>    LineSegmentF;

/**
 * @brief Type definition for a line segment with the start and end points having double floating point coordinates
 *
 */
typedef LineSegment<double>   LineSegmentD;