#pragma once

#include <cstdlib>

/**
 * @brief Structure for a selected node in the red-black tree
 *
 * @tparam Pair
 */
template <class Pair>
struct Select1
{
    const typename Pair::first_type& operator()( const Pair& x ) const
    {
        return x.first;
    }
};