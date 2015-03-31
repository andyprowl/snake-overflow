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