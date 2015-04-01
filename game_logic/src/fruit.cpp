#include "stdafx.hpp"

#include "snake_overflow/fruit.hpp"
#include "snake_overflow/game.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/terrain.hpp"

namespace snake_overflow
{

fruit::fruit(position const placement, 
             game& parent_game, 
             int const nutrition_value)
    : placement{placement}
    , parent_game{parent_game}
    , nutrition_value{nutrition_value}
{
}

position fruit::get_position() const
{
    return this->placement;
}

void fruit::pick(snake& s)
{
    make_snake_grow_by_nutrition_value(s);

    add_nutrition_value_to_game_score();

    remove_from_terrain_and_cause_self_destruction();
}

void fruit::make_snake_grow_by_nutrition_value(snake& s) const
{
    s.grow(this->nutrition_value);
}

void fruit::add_nutrition_value_to_game_score() const
{
    this->parent_game.add_points(this->nutrition_value);
}

void fruit::remove_from_terrain_and_cause_self_destruction()
{
    auto& t = this->parent_game.get_terrain();

    t.remove_item(*this);
}

}
