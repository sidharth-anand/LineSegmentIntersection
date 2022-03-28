#pragma once

#include <memory>
#include <string>

struct Slope
{
public:
    enum class Type
    {
        Finite,
        Infinite,
    };

public:
                Slope();
    explicit    Slope(double value, Type type = Type::Finite);

public:
    double      value;
    Type        type;
};
