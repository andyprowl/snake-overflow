#include "stdafx.hpp"

#include "snake_overflow/game_logic/dynamics.hpp"
#include "snake_overflow/game_logic/position.hpp"

namespace snake_overflow { namespace game_logic
{

dynamics::dynamics(util::value_ref<point> location,
                   util::value_ref<movement_profile> profile)
    : location{location}
    , profile{profile}
{
}

bool operator == (util::value_ref<dynamics> lhs, util::value_ref<dynamics> rhs)
{
    return ((lhs.profile == rhs.profile) && (lhs.location == rhs.location));
}

bool operator != (util::value_ref<dynamics> lhs, util::value_ref<dynamics> rhs)
{
    return !(lhs == rhs);
}

position get_dynamics_position(util::value_ref<dynamics> d)
{
    return {d.location, d.profile.face};
}

canonical_direction get_dynamics_direction(util::value_ref<dynamics> d)
{
    return d.profile.direction;
}

point get_dynamics_direction_vector(util::value_ref<dynamics> d)
{
    auto const dir = get_dynamics_direction(d);

    return get_direction_vector(dir);
}

} }