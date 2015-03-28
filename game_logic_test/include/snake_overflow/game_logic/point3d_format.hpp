#pragma once

#include "snake_overflow/game_logic/point3d.hpp"
#include <cassert>
#include <iostream>

namespace snake_overflow { namespace game_logic
{

inline std::ostream& operator << (std::ostream& out, 
                                  util::value_ref<point3d> p)
{
    out << "(" << p.x << ", " << p.y << ", " << p.z << ")";

    return out;
}

} }