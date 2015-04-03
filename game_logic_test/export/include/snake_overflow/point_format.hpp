#pragma once

#include "snake_overflow/point.hpp"
#include <cassert>
#include <iostream>

namespace snake_overflow
{

inline std::ostream& operator << (std::ostream& out, 
                                  util::value_ref<point> p)
{
    out << "(" << p.x << ", " << p.y << ", " << p.z << ")";

    return out;
}

}