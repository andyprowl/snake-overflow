#pragma once

#include "snake_overflow/canonical_direction.hpp"
#include <cassert>
#include <iostream>

namespace snake_overflow
{

inline std::ostream& operator << (std::ostream& out, 
                                  util::value_ref<canonical_direction> dir)
{
    switch (dir.way)
    {
        case orientation::negative: out << "-"; break;
        case orientation::positive: out << "+"; break;
        default: assert(false); break;
    }

    switch (dir.axis)
    {
        case canonical_axis::x: out << "x"; break;
        case canonical_axis::y: out << "y"; break;
        case canonical_axis::z: out << "z"; break;
        default: assert(false); break;
    }

    return out;
}

}