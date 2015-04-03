#include "stdafx.hpp"

#include "snake_overflow/snake_boolean_parameter.hpp"
#include "snake_overflow/dead_snake_flag.hpp"

namespace snake_overflow
{

snake_boolean_parameter::snake_boolean_parameter(bool const value, 
                                                 dead_snake_flag& dead_snake)
    : value{value}
    , dead_snake{dead_snake}
{
}

snake_boolean_parameter& snake_boolean_parameter::operator = (bool const value)
{
    if (this->dead_snake)
    {
        throw dead_snake_exception{};
    }

    this->value = value;

    return *this;
}

snake_boolean_parameter::operator bool () const
{
    return this->value;
}

}