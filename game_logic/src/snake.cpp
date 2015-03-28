#include "stdafx.hpp"

#include "snake_overflow/game_logic/direction.hpp"
#include "snake_overflow/game_logic/position.hpp"
#include "snake_overflow/game_logic/snake.hpp"
#include "snake_overflow/game_logic/territory.hpp"
#include "util/repeat.hpp"
#include "util/sequence.hpp"

namespace snake_overflow { namespace game_logic
{

snake::snake(territory& habitat,
             util::value_ref<dynamics> initial_dynamics, 
             int const initial_length)
    : habitat{habitat}
    , current_dynamics{initial_dynamics}
    , growth{0}
{
    this->body.push_back(initial_dynamics.pos);

    grow(initial_length - 1);

    util::repeat(initial_length - 1, [this] { advance(); });
}

std::vector<position> snake::get_body() const
{
    return {std::cbegin(this->body), std::cend(this->body)};
}

direction snake::get_direction() const
{
    return this->current_dynamics.dir;
}

void snake::advance()
{
    this->current_dynamics = this->habitat.compute_step(this->current_dynamics);

    this->body.push_back(this->current_dynamics.pos);

    if (this->growth > 0)
    {
        this->growth--;
    }
    else
    {
        this->body.pop_front();
    }
}

void snake::grow(int const size)
{
    this->growth += size;
}

} }