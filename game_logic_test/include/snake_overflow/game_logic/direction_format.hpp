#pragma once

#include "snake_overflow/game_logic/direction.hpp"
#include <cassert>
#include <iostream>

namespace snake_overflow { namespace game_logic
{

inline std::ostream& operator << (std::ostream& out, direction dir)
{
    switch (dir)
    {
        case direction::forward: out << "forward"; break;
        case direction::backward: out << "backward"; break;
        case direction::left: out << "left"; break;
        case direction::right: out << "right"; break;
        default: assert(false); break;
    }

    return out;
}

} }