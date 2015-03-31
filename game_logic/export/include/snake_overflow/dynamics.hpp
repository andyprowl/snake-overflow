#pragma once

#include "snake_overflow/footprint.hpp"
#include "snake_overflow/maneuvre.hpp"

namespace snake_overflow
{

struct dynamics
{

public:

    dynamics(util::value_ref<footprint> step, maneuvre action);

    footprint step;

    maneuvre action;

};

}