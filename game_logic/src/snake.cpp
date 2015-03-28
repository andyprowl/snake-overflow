#include "stdafx.hpp"

#include "snake_overflow/game_logic/position.hpp"
#include "snake_overflow/game_logic/snake.hpp"
#include "snake_overflow/game_logic/direction.hpp"
#include "util/sequence.hpp"

namespace snake_overflow { namespace game_logic
{

snake::snake(territory& habitat,
             util::value_ref<dynamics> initial_dynamics, 
             int const initial_length)
    : habitat{habitat}
{
    for (auto const i : util::sequence(0, initial_length))
    {
        this->body.push_back({{0, 0, i}, surface::front});
    }
}

std::vector<position> snake::get_body() const
{
    return this->body;
}

} }