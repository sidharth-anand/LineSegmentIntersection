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

    bool        operator <(const Slope& other) const;

public:
    double      value;
    Type        type;
};
