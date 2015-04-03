#include "stdafx.hpp"

#include "snake_overflow/fruit.hpp"
#include "snake_overflow/game.hpp"
#include "snake_overflow/snake.hpp"

namespace snake_overflow
{

fruit::fruit(position const placement, 
             game& parent_game, 
             int const nutrition_value)
    : consumable_item{placement, parent_game}
    , nutrition_value{nutrition_value}
{
}

void fruit::handle_picking(snake& s)
{
    make_snake_grow_by_nutrition_value(s);

    add_nutrition_value_to_game_score();
}

void fruit::make_snake_grow_by_nutrition_value(snake& s) const
{
    s.grow(this->nutrition_value);
}

void fruit::add_nutrition_value_to_game_score() const
{
    this->parent_game.score += this->nutrition_value;
}

}
