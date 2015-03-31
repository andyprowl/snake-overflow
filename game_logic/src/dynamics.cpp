#include "stdafx.hpp"

#include "snake_overflow/dynamics.hpp"

namespace snake_overflow
{

dynamics::dynamics(util::value_ref<footprint> step, maneuvre const action)
    : step{step}
    , action{action}
{
}

}