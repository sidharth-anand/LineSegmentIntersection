#include <internal/include/slope.h>

Slope::Slope()
    : value(0.f)
    , type(Type::Finite)
{

}

Slope::Slope(double value, Type type)
    : value(value)
    , type(type)
{

}