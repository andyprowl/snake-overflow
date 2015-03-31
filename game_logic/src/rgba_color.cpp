#include "stdafx.hpp"

#include "snake_overflow/rgba_color.hpp"

namespace snake_overflow
{

rgba_color::rgba_color(unsigned char const r, 
                       unsigned char const g, 
                       unsigned char const b, 
                       unsigned char const alpha)
    : r{r}
    , g{g}
    , b{b}
    , alpha{alpha}
{
}

rgba_color rgba_color::black()
{
    return {0, 0, 0, 255};
}

rgba_color rgba_color::red()
{
    return {255, 0, 0, 255};
}

rgba_color rgba_color::green()
{
    return {0, 255, 0, 255};
}

rgba_color rgba_color::blue()
{
    return {0, 0, 255, 255};
}

rgba_color rgba_color::yellow()
{
    return {255, 255, 0, 255};
}

rgba_color rgba_color::purple()
{
    return {255, 0, 255, 255};
}

rgba_color rgba_color::cyan()
{
    return {0, 255, 255, 255};
}

rgba_color rgba_color::white()
{
    return {255, 255, 255, 255};
}

bool operator == (util::value_ref<rgba_color> lhs, 
                  util::value_ref<rgba_color> rhs)
{
    return ((lhs.r == rhs.r) && 
            (lhs.g == rhs.g) && 
            (lhs.b == rhs.b) && 
            (lhs.alpha == rhs.alpha));
}

bool operator != (util::value_ref<rgba_color> lhs, 
                  util::value_ref<rgba_color> rhs)
{
    return !(lhs == rhs);
}

}