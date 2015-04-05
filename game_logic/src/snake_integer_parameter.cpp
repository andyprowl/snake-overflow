#include "stdafx.hpp"

#include "snake_overflow/snake_integer_parameter.hpp"
#include "snake_overflow/dead_snake_flag.hpp"
#include <algorithm>

namespace snake_overflow
{

snake_integer_parameter::snake_integer_parameter(
    int const value, 
    dead_snake_flag& death_flag,
    boost::optional<int> minimum_value,
    boost::optional<int> maximum_value)
    : value{value}
    , death_flag{death_flag}
    , minimum_value{minimum_value}
    , maximum_value{maximum_value}
{
}

snake_integer_parameter& snake_integer_parameter::operator = (
    int const new_value)
{
    throw_if_snake_is_dead();

    this->value = cap_value(new_value);
    
    return *this;
}

snake_integer_parameter& snake_integer_parameter::operator += (int const delta)
{
    return (*this = this->value + delta);
}

snake_integer_parameter& snake_integer_parameter::operator -= (
    int const delta)
{
    return (*this += (-delta));
}

snake_integer_parameter::operator int () const
{
    return this->value;
}

void snake_integer_parameter::throw_if_snake_is_dead() const
{
    if (this->death_flag)
    {
        throw dead_snake_exception{};
    }
}

int snake_integer_parameter::cap_value(int const v) const
{
    auto min_capped = cap_to_minimum(v);

    return cap_to_maximum(min_capped);
}

int snake_integer_parameter::cap_to_minimum(int const v) const
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

int snake_integer_parameter::cap_to_maximum(int const v) const
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