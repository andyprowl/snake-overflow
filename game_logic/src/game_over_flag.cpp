#include "stdafx.hpp"

#include "snake_overflow/dead_snake_flag.hpp"
#include "snake_overflow/game_over_flag.hpp"

namespace snake_overflow
{

game_over_flag::game_over_flag(bool const is_over, dead_snake_flag& snake_death)
    : is_over{is_over}
    , snake_death{snake_death}
{
    this->snake_death.register_death_event_handler([this]
    {
        on_snake_death();
    });
}

void game_over_flag::set()
{
    this->snake_death.set();

    set_flag_and_fire_event();
}

game_over_flag::operator bool () const
{
    return (this->is_over || this->snake_death);
}

boost::signals2::connection game_over_flag::register_game_over_event_handler(
    game_over_event_handler h)
{
    return this->on_game_over.connect(std::move(h));
}

void game_over_flag::on_snake_death()
{
    set_flag_and_fire_event();
}

void game_over_flag::set_flag_and_fire_event()
{
    auto old_value = this->is_over;

    this->is_over = true;

    if (!old_value)
    {
        this->on_game_over();
    }    
}

}