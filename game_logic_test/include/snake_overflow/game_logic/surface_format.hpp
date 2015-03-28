#pragma once

#include "snake_overflow/game_logic/surface.hpp"
#include <cassert>
#include <iostream>

namespace snake_overflow { namespace game_logic
{

inline std::ostream& operator << (std::ostream& out, surface s)
{
    switch (s)
    {
        case surface::front: out << "front"; break;
        case surface::back: out << "back"; break;
        case surface::left: out << "left"; break;
        case surface::right: out << "right"; break;
        case surface::top: out << "top"; break;
        case surface::bottom: out << "bottom"; break;
        default: assert(false); break;
    }

    return out;
}

} }