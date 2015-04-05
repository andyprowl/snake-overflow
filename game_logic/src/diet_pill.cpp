#include "stdafx.hpp"

#include "snake_overflow/diet_pill.hpp"
#include "snake_overflow/snake.hpp"

namespace snake_overflow
{

diet_pill::diet_pill(position const placement, 
                     game& parent_game, 
                     int const lifetime,
                     int const slim_power)
    : consumable_item{placement, parent_game, lifetime}
    , slim_power{slim_power}
{
}

int diet_pill::get_slim_power() const
{
    return this->slim_power;
}

void diet_pill::handle_picking(snake& s)
{
    make_snake_shrink_by_slim_power(s);
}

void diet_pill::make_snake_shrink_by_slim_power(snake& s) const
{
    s.shrink(this->slim_power);
}

}