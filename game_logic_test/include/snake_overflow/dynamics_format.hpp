#pragma once

#include "snake_overflow/dynamics.hpp"
#include "snake_overflow/direction_format.hpp"
#include "snake_overflow/position_format.hpp"
#include "util/value_ref.hpp"
#include <iostream>

namespace snake_overflow
{

inline std::ostream& operator << (std::ostream& out, 
                                  util::value_ref<dynamics> d)
{
    auto const pos = get_dynamics_position(d);

    auto const dir = get_dynamics_direction(d);

    out << "[" << pos << ", " << dir << "]";

    return out;
}

}