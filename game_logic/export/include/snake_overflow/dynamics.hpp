#pragma once

#include "snake_overflow/maneuvre.hpp"
#include "snake_overflow/movement_profile.hpp"
#include "snake_overflow/point.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow
{

struct position;

struct dynamics
{

public:

    dynamics(util::value_ref<point> location,
             util::value_ref<movement_profile> profile);

public:

    point location;

    movement_profile profile;

    maneuvre action;

};

bool operator == (util::value_ref<dynamics> lhs, util::value_ref<dynamics> rhs);

bool operator != (util::value_ref<dynamics> lhs, util::value_ref<dynamics> rhs);

position get_dynamics_position(util::value_ref<dynamics> d);

canonical_direction get_dynamics_direction(util::value_ref<dynamics> d);

point get_dynamics_direction_vector(util::value_ref<dynamics> d);

}