#include "stdafx.hpp"

#include "snake_overflow/point.hpp"
#include <algorithm>
#include <array>
#include <tuple>

namespace snake_overflow
{

point::point(int const x, int const y, int const z)
    : x{x}
    , y{y}
    , z{z}
{
}

point point::operator + () const
{
    return *this;
}

point point::operator - () const
{
    return {-(this->x), -(this->y), -(this->z)};
}

point point::x_unit()
{
    return {1, 0, 0};
}

point point::y_unit()
{
    return {0, 1, 0};
}

point point::z_unit()
{
    return {0, 0, 1};
}

bool is_unit(util::value_ref<point> p)
{
    auto coords = std::array<int, 3>{std::abs(p.x), 
                                     std::abs(p.y), 
                                     std::abs(p.z)};

    return ((std::count(std::cbegin(coords), std::cend(coords), 1) == 1) &&
           (coords[0] + coords[1] + coords[2] == 1));
}

bool operator == (util::value_ref<point> lhs, util::value_ref<point> rhs)
{
    return (std::make_tuple(lhs.x, lhs.y, lhs.z) ==
            std::make_tuple(rhs.x, rhs.y, rhs.z));
}

bool operator != (util::value_ref<point> lhs, util::value_ref<point> rhs)
{
    return !(lhs == rhs);
}

point operator + (util::value_ref<point> lhs, 
                    util::value_ref<point> rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

point operator - (util::value_ref<point> lhs, 
                    util::value_ref<point> rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

point operator * (util::value_ref<point> p, int const factor)
{
    return {p.x * factor, p.y * factor, p.z * factor};
}

point operator * (int const factor, util::value_ref<point> p)
{

    return p * factor;
}

}