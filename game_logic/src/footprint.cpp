#include "stdafx.hpp"

#include "snake_overflow/footprint.hpp"
#include "snake_overflow/position.hpp"

namespace snake_overflow
{

footprint::footprint(util::value_ref<point> location,
                     util::value_ref<movement_profile> profile)
    : location{location}
    , profile{profile}
{
}

bool operator == (util::value_ref<footprint> lhs, 
                  util::value_ref<footprint> rhs)
{
    return ((lhs.profile == rhs.profile) && (lhs.location == rhs.location));
}

bool operator != (util::value_ref<footprint> lhs, 
                  util::value_ref<footprint> rhs)
{
    return !(lhs == rhs);
}

position get_footprint_position(util::value_ref<footprint> d)
{
    return {d.location, d.profile.face};
}

canonical_direction get_footprint_direction(util::value_ref<footprint> d)
{
    return d.profile.direction;
}

point get_footprint_direction_vector(util::value_ref<footprint> d)
{
    auto const dir = get_footprint_direction(d);

    return get_direction_vector(dir);
}

}