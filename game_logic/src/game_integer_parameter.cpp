#include "stdafx.hpp"

#include "snake_overflow/game_integer_parameter.hpp"
#include "snake_overflow/game_over_flag.hpp"
#include <algorithm>

namespace snake_overflow
{

game_integer_parameter::game_integer_parameter(
    int const value, 
    game_over_flag& game_over,
    boost::optional<int> minimum_value,
    boost::optional<int> maximum_value)
    : value{value}
    , game_over{game_over}
    , minimum_value{minimum_value}
    , maximum_value{maximum_value}
{
}

game_integer_parameter& game_integer_parameter::operator = (
    int const new_value)
{
    throw_if_game_over();

    this->value = cap_value(new_value);
    
    return *this;
}

game_integer_parameter& game_integer_parameter::operator += (int const delta)
{
    return (*this = this->value + delta);
}

game_integer_parameter& game_integer_parameter::operator -= (
    int const delta)
{
    return (*this += (-delta));
}

game_integer_parameter::operator int () const
{
    return this->value;
}

void game_integer_parameter::throw_if_game_over() const
{
    if (this->game_over)
    {
        throw game_over_exception{};
    }
}

int game_integer_parameter::cap_value(int const v) const
{
    auto min_capped = cap_to_minimum(v);

    return cap_to_maximum(min_capped);
}

int game_integer_parameter::cap_to_minimum(int const v) const
{
    if (this->minimum_value)
    {
        return std::max(*(this->minimum_value), v);
    }
    else
    {
        return v;
    }
}

int game_integer_parameter::cap_to_maximum(int const v) const
{
    if (this->maximum_value)
    {
        return std::min(*(this->maximum_value), v);
    }
    else
    {
        return v;
    }
}

}