#include "stdafx.hpp"

#include "snake_overflow/position.hpp"

namespace snake_overflow
{

position::position(util::value_ref<point> location,
                   block_face const face)
    : location{location}
    , face{face}
{
}

bool operator == (util::value_ref<position> lhs, 
                  util::value_ref<position> rhs)
{
    return ((lhs.location == rhs.location) &&
            (lhs.face == rhs.face));
}

bool operator != (util::value_ref<position> lhs, 
                  util::value_ref<position> rhs)
{
    return !(lhs == rhs);
}

}