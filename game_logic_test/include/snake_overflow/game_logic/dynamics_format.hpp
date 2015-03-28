#pragma once

#include "snake_overflow/game_logic/dynamics.hpp"
#include "snake_overflow/game_logic/direction_format.hpp"
#include "snake_overflow/game_logic/position_format.hpp"
#include "util/value_ref.hpp"
#include <iostream>

namespace snake_overflow { namespace game_logic
{

inline std::ostream& operator << (std::ostream& out, 
                                  util::value_ref<dynamics> d)
{
    auto const pos = get_dynamics_position(d);

    auto const dir = get_dynamics_direction(d);

    out << "[" << pos << ", " << dir << "]";

    return out;
}

} }