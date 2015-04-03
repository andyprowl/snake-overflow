#include "stdafx.hpp"

#include "snake_overflow/dead_snake_flag.hpp"
#include "snake_overflow/game_over_flag.hpp"

namespace snake_overflow
{

game_over_flag::game_over_flag(bool const is_over, dead_snake_flag& snake_death)
    : is_over{is_over}
    , snake_death{snake_death}
{
}

void game_over_flag::set()
{
    this->is_over = true;

    this->snake_death.set();
}

game_over_flag::operator bool () const
{
    return (this->is_over || this->snake_death);
}

}