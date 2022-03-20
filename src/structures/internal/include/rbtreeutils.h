#pragma once

#include <cstdlib>

template <class Pair>
struct Select1
{
    const typename Pair::first_type& operator()(const Pair& x) const
    {
        return x.first;
    }
};