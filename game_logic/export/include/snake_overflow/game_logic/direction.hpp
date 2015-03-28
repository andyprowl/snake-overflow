#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow { namespace game_logic
{

struct point3d;

enum class cartesian_axis
{
    x,
    y,
    z
};

enum class orientation
{
    positive,
    negative
};

struct direction
{

public:

    direction(cartesian_axis axis, orientation way);

public:

    cartesian_axis axis;

    orientation way;

};

bool operator == (util::value_ref<direction> lhs, 
                  util::value_ref<direction> rhs);

bool operator != (util::value_ref<direction> lhs, 
                  util::value_ref<direction> rhs);

point3d get_direction_vector(util::value_ref<direction> dir);

} }