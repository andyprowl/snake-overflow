#include "stdafx.hpp"

#include "snake_overflow/fruit.hpp"
#include "snake_overflow/snake.hpp"

namespace snake_overflow
{

fruit::fruit(position const placement, int const nutrition_value)
    : placement{placement}
    , nutrition_value{nutrition_value}
{
}

position fruit::get_position() const
{
    return this->placement;
}

void fruit::pick(snake& s)
{
    s.grow(this->nutrition_value);
}

}