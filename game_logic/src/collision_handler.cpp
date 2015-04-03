#include "stdafx.hpp"

#include "snake_overflow/collision_handler.hpp"
#include "snake_overflow/dead_snake_flag.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/terrain.hpp"

namespace snake_overflow
{

collision_handler::collision_handler(snake& hero, 
                                     dead_snake_flag& dead_flag)
    : hero{hero}
    , dead_flag{dead_flag}
{
    register_snake_movement_handler();
}

void collision_handler::register_snake_movement_handler()
{
    auto& body = this->hero.get_body();

    this->on_movement_connection = body.register_movement_handler(
        [this] (util::value_ref<footprint> fp)
    {
        auto const pos = get_footprint_position(fp);

        on_snake_movement(hero, pos);
    });
}

void collision_handler::on_snake_movement(snake& hero, 
                                          util::value_ref<position> pos) const
{
    handle_item_collision(hero, pos);

    handle_self_collision(hero, pos);
}

void collision_handler::handle_item_collision(
    snake& hero, 
    util::value_ref<position> pos) const
{
    auto& t = hero.get_terrain();

    auto const i = find_item(pos, t);
    if (i == nullptr)
    {
        return;
    }

    i->pick(hero);
}

void collision_handler::handle_self_collision(
    snake& hero, 
    util::value_ref<position> pos) const
{
    auto& body = hero.get_body();

    if (body.is_position_in_tail(pos))
    {
        this->dead_flag.set();
    }
}

}