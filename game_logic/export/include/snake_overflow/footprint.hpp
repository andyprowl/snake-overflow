#pragma once

#include "snake_overflow/movement_profile.hpp"
#include "snake_overflow/point.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow
{

struct position;

struct footprint
{

public:

    footprint(util::value_ref<point> location,
              util::value_ref<movement_profile> profile);

public:

    point location;

    movement_profile profile;

};

bool operator == (util::value_ref<footprint> lhs, 
                  util::value_ref<footprint> rhs);

bool operator != (util::value_ref<footprint> lhs, 
                  util::value_ref<footprint> rhs);

position get_footprint_position(util::value_ref<footprint> d);

canonical_direction get_footprint_direction(util::value_ref<footprint> d);

point get_footprint_direction_vector(util::value_ref<footprint> d);

}