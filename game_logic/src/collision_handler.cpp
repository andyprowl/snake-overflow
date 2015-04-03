#include "stdafx.hpp"

#include "snake_overflow/collision_handler.hpp"
#include "snake_overflow/game.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/snake.hpp"

namespace snake_overflow
{

collision_handler::collision_handler(game& g)
    : parent_game{g}
    , ground{g.get_terrain()}
{
    register_snake_movement_handler();
}

void collision_handler::register_snake_movement_handler()
{
    auto& s = this->parent_game.get_snake();

    this->on_movement_connection = s.register_movement_handler(
        [this, &s] (util::value_ref<footprint> fp)
    {
        auto const pos = get_footprint_position(fp);

        on_snake_movement(s, pos);
    });
}

void collision_handler::on_snake_movement(snake& s, 
                                          util::value_ref<position> pos) const
{
    handle_item_collision(s, pos);

    handle_self_collision(s, pos);
}

void collision_handler::handle_item_collision(
    snake& s, 
    util::value_ref<position> pos) const
{
    auto const i = find_item(pos, this->ground);
    if (i == nullptr)
    {
        return;
    }

    i->pick(s);
}

void collision_handler::handle_self_collision(
    snake& s, 
    util::value_ref<position> pos) const
{
    if (s.is_position_in_tail(pos))
    {
        this->parent_game.is_game_over = true;
    }
}

}