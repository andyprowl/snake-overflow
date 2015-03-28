#pragma once

#include "snake_overflow/game_logic/canonical_direction.hpp"
#include <cassert>
#include <iostream>

namespace snake_overflow { namespace game_logic
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

} }