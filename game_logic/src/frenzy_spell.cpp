#include "stdafx.hpp"

#include "snake_overflow/frenzy_spell.hpp"
#include "snake_overflow/snake.hpp"

namespace snake_overflow
{

frenzy_spell::frenzy_spell(int const duration)
    : duration{duration}
    , already_applied{false}
{
}

void frenzy_spell::affect(snake& s)
{
    --(this->duration);

    increment_speed_if_starting_to_affect(s);

    if (this->duration == 0)
    {
        stop_affecting_snake_and_cause_self_destruction(s);
    }
}

int frenzy_spell::get_duration() const
{
    return this->duration;
}

void frenzy_spell::increment_speed_if_starting_to_affect(snake& s)
{
    if (this->already_applied)
    {
        return;
    }
    
    s.speed += 1;

    this->already_applied = true;
}

void frenzy_spell::stop_affecting_snake_and_cause_self_destruction(
    snake& s) const
{
    s.speed -= 1;

    s.remove_spell(*this);
}

}