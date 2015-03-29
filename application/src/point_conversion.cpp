#include "stdafx.hpp"

#include "snake_overflow/point_conversion.hpp"

namespace snake_overflow
{

float as_float(int const i)
{
    return static_cast<float>(i);
}

cinder::Vec3f vec3f_from_point(util::value_ref<point> p)
{
    return {as_float(p.x), as_float(p.y), as_float(p.z)};
}

}