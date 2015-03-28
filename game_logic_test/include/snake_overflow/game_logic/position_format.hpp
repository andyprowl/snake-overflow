#pragma once

#include "snake_overflow/game_logic/position.hpp"
#include "snake_overflow/game_logic/point_format.hpp"
#include "snake_overflow/game_logic/block_face_format.hpp"
#include <cassert>
#include <iostream>

namespace snake_overflow { namespace game_logic
{

inline std::ostream& operator << (std::ostream& out, 
                                  util::value_ref<position> pos)
{
    out << "{" << pos.location << ", " << pos.face << "}";

    return out;
}

} }