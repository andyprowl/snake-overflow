#include "stdafx.hpp"

#include "snake_overflow/game_logic/direction.hpp"
#include "snake_overflow/game_logic/point3d.hpp"
#include <cassert>

namespace snake_overflow { namespace game_logic
{

direction::direction(cartesian_axis axis, orientation way)
    : axis{axis}
    , way{way}
{
}

direction direction::positive_x()
{
    return {cartesian_axis::x, orientation::positive};
}

direction direction::negative_x()
{
    return {cartesian_axis::x, orientation::negative};
}

direction direction::positive_y()
{
    return {cartesian_axis::y, orientation::positive};
}

direction direction::negative_y()
{
    return {cartesian_axis::y, orientation::negative};
}

direction direction::positive_z()
{
    return {cartesian_axis::z, orientation::positive};
}

direction direction::negative_z()
{
    return {cartesian_axis::z, orientation::negative};
}

bool operator == (util::value_ref<direction> lhs, 
                  util::value_ref<direction> rhs)
{
    return ((lhs.axis == rhs.axis) && (lhs.way == rhs.way));
}

bool operator != (util::value_ref<direction> lhs, 
                  util::value_ref<direction> rhs)
{
    return !(lhs == rhs);
}

point3d get_direction_vector(util::value_ref<direction> dir)
{
    switch (dir.axis)
    {
        case cartesian_axis::x: 
        {
            return (dir.way == orientation::positive) 
                 ? point3d{1, 0, 0} 
                 : point3d{-1, 0, 0};
        }

        case cartesian_axis::y: 
        {
            return (dir.way == orientation::positive) 
                 ? point3d{0, 1, 0} 
                 : point3d{0, -1, 0};
        }

        case cartesian_axis::z:
        {
            return (dir.way == orientation::positive) 
                 ? point3d{0, 0, 1} 
                 : point3d{0, 0, -1};
        }

        default:
        {
            assert(false); 
            return {0, 0, 0};
        }
    }
}

direction get_opposite_direction(direction const d)
{
    auto opposite_way = (d.way == orientation::negative)
                      ? orientation::positive
                      : orientation::negative;

    return {d.axis, opposite_way};
}

} }