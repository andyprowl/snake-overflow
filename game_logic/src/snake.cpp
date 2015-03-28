#include "stdafx.hpp"

#include "snake_overflow/game_logic/snake.hpp"
#include "snake_overflow/game_logic/position.hpp"
#include "math/sequence.hpp"

namespace snake_overflow { namespace game_logic
{

snake::snake(territory& habitat,
             util::value_ref<position> start_position, 
             int const initial_length,
             util::value_ref<math::point3d> initial_direction)
    : habitat{habitat}
{
    for (auto const i : math::sequence(0, initial_length))
    {
        this->body.push_back({{0, 0, i}, surface::front});
    }
}

std::vector<position> snake::get_body() const
{
    return this->body;
}

} }