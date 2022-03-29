#pragma once

#include <cstdlib>

/**
 * @brief Simple structure to select the first value from a given pair of objects.
 *
 * @tparam Pair Generic type of the pair.
 */
template <class Pair>
struct Select1
{
    const typename Pair::first_type& operator()( const Pair& x ) const
    {
        return x.first;
    }
};