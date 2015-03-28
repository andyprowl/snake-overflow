#pragma once

#include "math/point3d.hpp"
#include <cassert>
#include <iostream>

namespace math
{

inline std::ostream& operator << (std::ostream& out, 
                                  util::value_ref<point3d> p)
{
    out << "(" << p.x << ", " << p.y << ", " << p.z << ")";

    return out;
}

}