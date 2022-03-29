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

bool Slope::operator <(const Slope& other) const
{
    return type != Type::Infinite && (other.type == Type::Infinite || value < other.value);
}