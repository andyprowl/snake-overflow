#include "stdafx.hpp"

#include "snake_overflow/dead_snake_flag.hpp"

namespace snake_overflow
{

dead_snake_flag::dead_snake_flag(bool const is_dead)
    : is_dead{is_dead}
{
}

void dead_snake_flag::set()
{
    this->is_dead = true;
}

dead_snake_flag::operator bool () const
{
    return this->is_dead;
}

}