#pragma once

#include "snake_overflow/position.hpp"
#include "snake_overflow/point_format.hpp"
#include "snake_overflow/block_face_format.hpp"
#include <cassert>
#include <iostream>

namespace snake_overflow
{

inline std::ostream& operator << (std::ostream& out, 
                                  util::value_ref<position> pos)
{
    out << "{" << pos.location << ", " << pos.face << "}";

    return out;
}

}