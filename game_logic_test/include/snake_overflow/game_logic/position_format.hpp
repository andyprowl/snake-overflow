#pragma once

#include "snake_overflow/game_logic/position.hpp"
#include "snake_overflow/game_logic/point3d_format.hpp"
#include "snake_overflow/game_logic/surface_format.hpp"
#include <cassert>
#include <iostream>

namespace snake_overflow { namespace game_logic
{

inline std::ostream& operator << (std::ostream& out, 
                                  util::value_ref<position> pos)
{
    out << "{" << pos.block_origin << ", " << pos.block_surface << "}";

    return out;
}

} }