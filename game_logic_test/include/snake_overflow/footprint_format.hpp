#pragma once

#include "snake_overflow/footprint.hpp"
#include "snake_overflow/direction_format.hpp"
#include "snake_overflow/position_format.hpp"
#include "util/value_ref.hpp"
#include <iostream>

namespace snake_overflow
{

inline std::ostream& operator << (std::ostream& out, 
                                  util::value_ref<footprint> d)
{
    auto const pos = get_footprint_position(d);

    auto const dir = get_footprint_direction(d);

    out << "[" << pos << ", " << dir << "]";

    return out;
}

}