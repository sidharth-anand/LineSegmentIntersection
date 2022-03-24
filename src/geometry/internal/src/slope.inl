#include<string>

Slope::Slope()
{
    value = 0;
    type = "";
}

Slope::Slope(T x0, T y0, T x1, T y1){
    if(x0 == x1)
        type = "infinity"
    else {
        type = "normal";
        value = (y1 - y0) / (x1 - x0);
    }

    return ;
}