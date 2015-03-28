#pragma once

#include "snake_overflow/game_logic/direction.hpp"
#include <cassert>
#include <iostream>

namespace snake_overflow { namespace game_logic
{

inline std::ostream& operator << (std::ostream& out, direction dir)
{
    switch (dir.way)
    {
        case orientation::negative: out << "-"; break;
        case orientation::positive: out << "+"; break;
        default: assert(false); break;
    }

    switch (dir.axis)
    {
        case cartesian_axis::x: out << "x"; break;
        case cartesian_axis::y: out << "y"; break;
        case cartesian_axis::z: out << "z"; break;
        default: assert(false); break;
    }

    return out;
}

} }