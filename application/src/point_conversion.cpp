#include "stdafx.hpp"

#include "snake_overflow/point_conversion.hpp"

namespace snake_overflow
{

cinder::Vec3i vector_from_point(util::value_ref<point> p)
{
    return {p.x, p.y, p.z};
}

}