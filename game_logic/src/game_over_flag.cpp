#include "stdafx.hpp"

#include "snake_overflow/game_over_flag.hpp"

namespace snake_overflow
{

game_over_flag::game_over_flag(bool const is_over)
    : is_over{is_over}
{
}

game_over_flag& game_over_flag::operator = (bool const over)
{
    if ((this->is_over) && !over)
    {
        throw game_over_exception{};
    }

    this->is_over = over;

    return *this;
}

game_over_flag::operator bool () const
{
    return this->is_over;
}

}