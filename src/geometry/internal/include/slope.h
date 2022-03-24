#pragma once
#include <memory>
#include <string>

template <typename T>
class Slope
{
public:
                            Slope();
                            Slope(T x0, T y0, T x1, T y1);
    double                  value;
    std::string             type;
                            

private:
    
};
