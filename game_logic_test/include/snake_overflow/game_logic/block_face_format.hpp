#pragma once

#include "snake_overflow/game_logic/block_face.hpp"
#include <cassert>
#include <iostream>

namespace snake_overflow { namespace game_logic
{

inline std::ostream& operator << (std::ostream& out, block_face const s)
{
    switch (s)
    {
        case block_face::front: out << "front"; break;
        case block_face::back: out << "back"; break;
        case block_face::left: out << "left"; break;
        case block_face::right: out << "right"; break;
        case block_face::top: out << "top"; break;
        case block_face::bottom: out << "bottom"; break;
        default: assert(false); break;
    }

    return out;
}

} }