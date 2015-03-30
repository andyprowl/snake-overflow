#include "stdafx.hpp"

#include "snake_overflow/canonical_direction.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/movement_profile.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/terrain.hpp"
#include "util/repeat.hpp"
#include "util/sequence.hpp"

namespace snake_overflow
{

snake::snake(terrain const& habitat,
             util::value_ref<dynamics> initial_dynamics, 
             int const initial_length)
    : habitat{habitat}
    , current_dynamics{initial_dynamics}
    , growth{0}
{
    this->trail.push_back(initial_dynamics);

    grow(initial_length - 1);

    util::repeat(initial_length - 1, [this] { advance(); });
}

std::vector<dynamics> snake::get_trail() const
{
    return {std::cbegin(this->trail), std::cend(this->trail)};
}

canonical_direction snake::get_direction() const
{
    return get_dynamics_direction(this->current_dynamics);
}

int snake::get_length() const
{
    return static_cast<int>(this->trail.size());
}

void snake::advance()
{
    this->current_dynamics = this->habitat.compute_step(this->current_dynamics);

    this->trail.push_back(current_dynamics);

    if (this->growth > 0)
    {
        this->growth--;
    }
    else
    {
        this->trail.pop_front();
    }
}

void snake::grow(int const size)
{
    this->growth += size;
}

void snake::turn_left()
{    
    auto const current_profile = this->current_dynamics.profile;

    auto const new_profile = get_left_turn_profile(current_profile);

    this->current_dynamics.profile = new_profile;

    this->trail.back().action = maneuvre::turn_left;
}

void snake::turn_right()
{
    auto const current_profile = this->current_dynamics.profile;

    auto const new_profile = get_right_turn_profile(current_profile);

    this->current_dynamics.profile = new_profile;

    this->trail.back().action = maneuvre::turn_right;
}

}