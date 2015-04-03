#include "stdafx.hpp"

#include "snake_overflow/game_boolean_parameter.hpp"
#include "snake_overflow/game_over_flag.hpp"

namespace snake_overflow
{

game_boolean_parameter::game_boolean_parameter(bool const value, 
                                               game_over_flag& game_over)
    : value{value}
    , game_over{game_over}
{
}

game_boolean_parameter& game_boolean_parameter::operator = (bool const value)
{
    if (this->game_over)
    {
        throw game_over_exception{};
    }

    this->value = value;

    return *this;
}

game_boolean_parameter::operator bool () const
{
    return this->value;
}

}