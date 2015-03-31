#include "stdafx.hpp"

#include "snake_overflow/canonical_direction.hpp"
#include "snake_overflow/point.hpp"
#include <cassert>

namespace snake_overflow
{

canonical_direction::canonical_direction(canonical_axis const axis, 
                                         orientation const way)
    : axis{axis}
    , way{way}
{
}

canonical_direction canonical_direction::positive_x()
{
    return {canonical_axis::x, orientation::positive};
}

canonical_direction canonical_direction::negative_x()
{
    return {canonical_axis::x, orientation::negative};
}

canonical_direction canonical_direction::positive_y()
{
    return {canonical_axis::y, orientation::positive};
}

canonical_direction canonical_direction::negative_y()
{
    return {canonical_axis::y, orientation::negative};
}

canonical_direction canonical_direction::positive_z()
{
    return {canonical_axis::z, orientation::positive};
}

canonical_direction canonical_direction::negative_z()
{
    return {canonical_axis::z, orientation::negative};
}

bool operator == (util::value_ref<canonical_direction> lhs, 
                  util::value_ref<canonical_direction> rhs)
{
    return ((lhs.axis == rhs.axis) && (lhs.way == rhs.way));
}

bool operator != (util::value_ref<canonical_direction> lhs, 
                  util::value_ref<canonical_direction> rhs)
{
    return !(lhs == rhs);
}

point get_direction_vector(util::value_ref<canonical_direction> dir)
{
    switch (dir.axis)
    {
        case canonical_axis::x: 
        {
            return (dir.way == orientation::positive) ? point{1, 0, 0} 
                                                      : point{-1, 0, 0};
        }

        case canonical_axis::y: 
        {
            return (dir.way == orientation::positive) ? point{0, 1, 0} 
                                                      : point{0, -1, 0};
        }

        case canonical_axis::z:
        {
            return (dir.way == orientation::positive) ? point{0, 0, 1} 
                                                      : point{0, 0, -1};
        }

        default:
        {
            assert(false); 
            return {0, 0, 0};
        }
    }
}

canonical_direction get_direction_from_vector(util::value_ref<point> v)
{
    if (!is_unit(v))
    {
        throw bad_direction_vector_exception{};
    }

    if ((v.y == 0) && (v.z == 0))
    {
        return (v.x > 0) ? canonical_direction::positive_x()
                         : canonical_direction::negative_x();
    }
    else if ((v.x == 0) && (v.z == 0))
    {
        return (v.y > 0) ? canonical_direction::positive_y()
                         : canonical_direction::negative_y();
    }
    else
    {
        return (v.z > 0) ? canonical_direction::positive_z()
                         : canonical_direction::negative_z();
    }
}

canonical_direction get_opposite_direction(
    util::value_ref<canonical_direction> const dir)
{
    auto opposite_way = (dir.way == orientation::negative)
                      ? orientation::positive
                      : orientation::negative;

    return {dir.axis, opposite_way};
}

std::vector<canonical_direction> get_all_canonical_directions()
{
    return {canonical_direction::positive_x(),
            canonical_direction::negative_x(),
            canonical_direction::positive_y(),
            canonical_direction::negative_y(),
            canonical_direction::positive_z(),
            canonical_direction::negative_z()};
}

}