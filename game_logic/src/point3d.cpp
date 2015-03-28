#include "stdafx.hpp"

#include "snake_overflow/game_logic/point3d.hpp"
#include <tuple>

namespace snake_overflow { namespace game_logic
{

point3d::point3d(int x, int y, int z)
    : x{x}
    , y{y}
    , z{z}
{
}

point3d point3d::operator + () const
{
    return *this;
}

point3d point3d::operator - () const
{
    return {-(this->x), -(this->y), -(this->z)};
}

point3d point3d::x_unit()
{
    return {1, 0, 0};
}

point3d point3d::y_unit()
{
    return {0, 1, 0};
}

point3d point3d::z_unit()
{
    return {0, 0, 1};
}

bool is_unit(util::value_ref<point3d> p)
{
    return (p.x + p.y + p.z == 1);
}

bool operator == (util::value_ref<point3d> lhs, util::value_ref<point3d> rhs)
{
    return (std::make_tuple(lhs.x, lhs.y, lhs.z) ==
            std::make_tuple(rhs.x, rhs.y, rhs.z));
}

bool operator != (util::value_ref<point3d> lhs, util::value_ref<point3d> rhs)
{
    return !(lhs == rhs);
}

point3d operator + (util::value_ref<point3d> lhs, 
                    util::value_ref<point3d> rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

point3d operator - (util::value_ref<point3d> lhs, 
                    util::value_ref<point3d> rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

} }