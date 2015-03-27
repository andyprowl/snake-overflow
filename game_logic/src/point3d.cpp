#include "stdafx.hpp"

#include "math/point3d.hpp"
#include <tuple>

namespace math
{

point3d::point3d(int x, int y, int z)
    : x{x}
    , y{y}
    , z{z}
{
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

}